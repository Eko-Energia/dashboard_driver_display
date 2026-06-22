#include "system.h"
#include <QDebug>
#include <QJsonObject>
#include <QJsonValue>
#include <QJsonArray>
#include <QVariant>

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
            }            
        }
    }

    emit valuesChanged();
}

void System::readUpdate(const QJsonObject& update){ // poprawic do nowej wersji swag ekranu
    // Kazdy update daje tylko jedna ramke
    QString frame_name = update.value("message_name").toString();
    // Pod entry jest lista sygnalow i timestamp (nie wazny)
    QJsonObject entry = update.value("entry").toObject();
    QJsonArray signals_list = entry.value("signals").toArray();

    for (auto it = signals_list.constBegin(); it != signals_list.constEnd(); ++it) {
        if (!it->isObject())
            continue;

        QJsonObject signalObj = it->toObject();
        QString name = signalObj.value("name").toString();

        if(systemValues_.contains(frame_name) && systemValues_[frame_name].containsSignal(name)){
            QString value = signalObj.value("value").toVariant().toString();
            updateValues(frame_name, name, value);
        }
    }
    emit valuesChanged();
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

