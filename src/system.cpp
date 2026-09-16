#include "system.h"
#include <QDebug>
#include <QJsonObject>
#include <QJsonValue>
#include <QJsonArray>
#include <QVariant>

const QString System::kPackFrame = QStringLiteral("BMSMaster_JK_Pack");
const QString System::kPackVoltageSignal = QStringLiteral("BMSMaster_JK_PackVoltage");
const QString System::kPackCurrentSignal = QStringLiteral("BMSMaster_JK_PackCurrent");
const QString System::kPackSocSignal = QStringLiteral("BMSMaster_JK_SOC");
const QString System::kPackStatusFlagsSignal = QStringLiteral("BMSMaster_JK_StatusFlags");

System::System(QObject *parent) : QObject(parent) {
    QList<CANframe> frames = loadSubscriptions();

    for (const CANframe& frame : frames) {
        systemValues_.insert(frame.getName(), frame);
    }

    qDebug() << "System initialized with frames:" << systemValues_;

}
void System::updateValues(const QString& frameName, const QString& signalName, const QString& value){
    if (frameName.isEmpty() || signalName.isEmpty() || value.isEmpty()) {
        qWarning() << "System::UpdateValues: Próba aktualizacji pustymi danymi!"
                   << "Frame:" << frameName
                   << "Signal:" << signalName;
        return;
    }

    if(systemValues_.contains(frameName)){
        CANframe& frame = systemValues_[frameName];
        frame.updateSignal(signalName, value);
        //qDebug() << "Zaktualizowano ramke:" << frameName << "sygnal:" << signalName << "nowa wartosc:" << value;
    }
    else{
        qDebug() << "System nie zawiera ramki o nazwie:" << frameName;
    }
}

void System::readSnapshot(const QJsonObject& snapshot)
{
    if (!snapshot.contains("data") || !snapshot["data"].isObject()){
        qDebug() << "System::readSnapshot - brak danych lub niepoprawny format";
        return;
    }

    // Zostaje struktura "data", ktora ma pod soba ramki, po ktorych mozna przeiterowac
    QJsonObject obj = snapshot["data"].toObject();

    // Moc pakietu przeliczamy dopiero po przejsciu calej wiadomosci - napiecie, prad i
    // flagi musza pochodzic z tego samego odczytu, a nie z polowy zaktualizowanej ramki.
    bool packTouched = false;

    for (auto it = obj.constBegin(); it != obj.constEnd(); ++it) {
        //qDebug() << "Przetwarzanie ramki:" << it.key();

        // Zwraca zawartosc danej ramki -> liste pod signals i timestamp ( nie tworzy kopi )
        QJsonObject frameObj = it.value().toObject();
        QString frameName = it.key();
        // Wyciecie listy sygnalow
        QJsonArray signalsList = frameObj.value("signals").toArray();

        for (auto sigIt = signalsList.constBegin(); sigIt != signalsList.constEnd(); ++sigIt) {
            // Pojedyczny sygnal
            QJsonObject currentSig = sigIt->toObject();
            QString name = currentSig.value("name").toString();

            // it.key() to nazwa obecnej ramki
            if(systemValues_.contains(frameName) && systemValues_[it.key()].containsSignal(name)){
                QString value = currentSig.value("value").toVariant().toString();
                //qDebug() << it.key() << name << value;
                updateValues(it.key(), name, value);
                if (frameName == kPackFrame) {
                    packTouched = true;
                }
            }
        }
    }

    if (packTouched) {
        updatePackFromFrame();
    }

    emit valuesChanged();
}

void System::readUpdate(const QJsonObject& update){ // poprawic do nowej wersji swag ekranu
    // Kazdy update daje tylko jedna ramke
    QString frame_name = update.value("message_name").toString();
    // Pod entry jest lista sygnalow i timestamp (nie wazny)
    QJsonObject entry = update.value("entry").toObject();
    QJsonArray signals_list = entry.value("signals").toArray();

    bool packTouched = false;

    for (auto it = signals_list.constBegin(); it != signals_list.constEnd(); ++it) {
        if (!it->isObject())
            continue;

        QJsonObject signalObj = it->toObject();
        QString name = signalObj.value("name").toString();

        if(systemValues_.contains(frame_name) && systemValues_[frame_name].containsSignal(name)){
            QString value = signalObj.value("value").toVariant().toString();
            updateValues(frame_name, name, value);
            if (frame_name == kPackFrame) {
                packTouched = true;
            }
        }
    }

    if (packTouched) {
        updatePackFromFrame();
    }

    emit valuesChanged();
}

void System::updatePackFromFrame()
{
    if (!systemValues_.contains(kPackFrame)) {
        return;
    }

    const CANframe& frame = systemValues_.value(kPackFrame);
    if (!frame.containsSignal(kPackVoltageSignal)
        || !frame.containsSignal(kPackCurrentSignal)
        || !frame.containsSignal(kPackStatusFlagsSignal)) {
        qWarning() << "System: ramka" << kPackFrame
                   << "nie ma kompletu sygnalow potrzebnych do mocy pakietu - sprawdz subs.txt";
        return;
    }

    // Przy bledzie komunikacji z JK napiecie, prad i SOC sa zamrozone. Zerowanie ich
    // wygladaloby jak zdjecie nogi z pedalu i rozladowana bateria, wiec zostawiamy
    // ostatni wiarygodny odczyt i podnosimy flage - QML go przygasza.
    bool flagsOk = false;
    const int statusFlags = static_cast<int>(frame.getSigVal(kPackStatusFlagsSignal).toDouble(&flagsOk));
    if (!flagsOk || (statusFlags & kJkCommErrorBit)) {
        packStale_ = true;
        return;
    }

    bool voltageOk = false;
    bool currentOk = false;
    const double packVoltage = frame.getSigVal(kPackVoltageSignal).toDouble(&voltageOk);
    // BMS podaje prad z odwrotnym znakiem niz opisuje CM_ SG_ 140 w CAN_DB.dbc,
    // wiec odwracamy go tu, u zrodla - tak samo jak rpi_utilities.
    const double packCurrent = -frame.getSigVal(kPackCurrentSignal).toDouble(&currentOk);
    if (!voltageOk || !currentOk) {
        packStale_ = true;
        return;
    }

    // Po odwroceniu znaku dodatni prad to rozladowanie, czyli dodatnia moc = pobor,
    // ujemna = ladowanie/rekuperacja. Dokladnie ta sama konwencja co w
    // rpi_utilities/src/rpi_utilities/energy.py.
    packPowerKw_ = packVoltage * packCurrent / 1000.0;

    if (frame.containsSignal(kPackSocSignal)) {
        bool socOk = false;
        const double soc = frame.getSigVal(kPackSocSignal).toDouble(&socOk);
        if (socOk) {
            packSoc_ = soc;
        }
    }

    packStale_ = false;
}

void System::readMileageUpdate(double totalKm)
{
    totalKm_ = totalKm;
    emit valuesChanged();
}

void System::readSpeedUpdate(double speedKmh)
{
    qDebug() <<"Otrzymano update predkosci" << speedKmh;
    speedKmh_ = speedKmh;
    emit valuesChanged();
}

void System::readEnergyUpdate(double avgPowerKw,
                              double consumptionKwhPerKm,
                              bool consumptionValid,
                              double coverage,
                              double intervalS)
{
    avgPowerKw_ = avgPowerKw;
    consumptionKwhPerKm_ = consumptionKwhPerKm;
    consumptionValid_ = consumptionValid;
    energyCoverage_ = coverage;
    if (intervalS > 0.0) {
        energyIntervalS_ = intervalS;
    }
    emit valuesChanged();
}

void System::readErrorUpdate(const QString& frame, double code, const QString& name)
{
    emit errorReceived(frame, code, name);
}

void System::readSnapshotErrors(int count)
{
    emit snapshotErrorsReceived(count);
}

QString System::values(const QString& frameName,const QString& signalName) const
{
    if (systemValues_.contains(frameName)){
        return systemValues_.value(frameName).getSigVal(signalName);
    }
    else{
        qDebug() << "System nie zawiera ramki o nazwie:" << frameName;
        return QString();
    }
}
