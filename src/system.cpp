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
    if(systemValues_.contains(frameName)){  
        CANframe& frame = systemValues_[frameName];
        frame.updateSignal(signalName, value);
        emit valuesChanged();
    }
    else{
        qDebug() << "System nie zawiera ramki o nazwie:" << &frameName;
    }
}

void System::readSnapshot(QJsonObject& snapshot)
{
    if (!snapshot.contains("data") || !snapshot["data"].isObject())
        return;

    QJsonObject obj = snapshot["data"].toObject();
    qDebug() << "Otrzymany SNAPSHOT" << obj;
    
    for (auto it = obj.begin(); it != obj.end(); ++it) {
        QJsonObject frameObj = it.value().toObject();
        QJsonObject signalsList = frameObj["signals"].toObject();
        for (auto sigIt = signalsList.begin(); sigIt != signalsList.end(); ++sigIt) {
            QJsonObject currentSig = sigIt.value().toObject();
            QString name = currentSig["name"].toString();
            QString value = currentSig["value"].toString();
            updateValues(it.key(), name, value);
        }
    }
}

void System::readUpdate(QJsonObject& update){ // poprawic do nowej wersji swag ekranu
    qDebug() << "UPDATE";

    QJsonObject entry = update.value("entry").toObject();
    QJsonArray signals_list = entry.value("signals").toArray();

    qDebug() << "Otrzymany UPDATE" << entry;

    for (auto it = signals_list.begin(); it != signals_list.end(); ++it) {

        if (!it->isObject())
            continue;

        QJsonObject signalObj = it->toObject();
        QString name = signalObj.value("name").toString();

        if (systemValues_.contains(name)) {
            double value = signalObj.value("value").toDouble();
            QString strValue = QString::number(value);
            //systemValues_[name] = strValue; taktyczny kom zeby nie wywalalo 
            emit valuesChanged();
            qDebug() << "Nowa wartosc :"<< name << systemValues_[name];
        }
    }
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

