#include "system.h"
#include <QDebug>
#include <QJsonObject>
#include <QJsonValue>
#include <QJsonArray>
#include <QVariant>

System::System(QObject *parent) : QObject(parent) {
    systemValues_ = {
        {"StateOfCharge","0"} ,
        {"AmbientTemp","0"} ,
        {"Speed","0"} ,
        {"MotorPower","0"}
    };

}

void System::readSnapshot(QJsonObject& snapshot)
{
    qDebug() << "SNAPSZOT";

    if (!snapshot.contains("data") || !snapshot["data"].isObject())
        return;

    QJsonObject obj = snapshot["data"].toObject();

    for (auto it = obj.begin(); it != obj.end(); ++it) {
        if (it.key() == "BatteryInfo") {
            qDebug() << "WYKRYTO BATTERY INFO";
        }
    }
}

void System::readUpdate(QJsonObject& update){
    qDebug() << "UPDATE";

    QJsonObject entry = update.value("entry").toObject();
    QJsonArray signals_list = entry.value("signals").toArray();

    for (auto it = signals_list.begin(); it != signals_list.end(); ++it) {

        if (!it->isObject())
            continue;

        QJsonObject signalObj = it->toObject();
        QString name = signalObj.value("name").toString();

        if (systemValues_.contains(name)) {
            double value = signalObj.value("value").toDouble();
            QString strValue = QString::number(value);
            systemValues_[name] = strValue;
            emit valuesChanged();
            qDebug() << "Nowa wartosc :"<< name << systemValues_[name];
        }
    }
}

QVariantMap System::values() const
{
    QVariantMap map;
    for (auto it = systemValues_.begin(); it != systemValues_.end(); ++it)
        map[it.key()] = it.value();
    return map;
}

