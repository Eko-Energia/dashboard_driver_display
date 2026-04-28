#ifndef SYSTEM_H
#define SYSTEM_H

#include <QHash>
#include <QString>
#include <QObject>
#include <QVariant>
#include <QVariantMap>
#include "functions.h"
class System : public QObject
{
    Q_OBJECT
    Q_PROPERTY(bool dataTick READ dataTick NOTIFY valuesChanged)
public:
    explicit System(QObject *parent = nullptr);
    Q_INVOKABLE QString values(const QString& frameName,const QString& signalName) const;
    void updateValues(const QString& frameName, const QString& signalName, const QString& value);
    bool dataTick() const { return true; } // Zawsze zwraca true, aby sygnalizować zmianę danych
    // dataTick jest uzywany jedynie do wykrywania ze nastapila zmiana danych po valuesChanged, co bedzie powodowac ponowne wywolanie values() w qml
signals:
    void valuesChanged();
public slots:
    void readSnapshot(const QJsonObject& snapshot);
    void readUpdate(QJsonObject& update);

private:
    QHash<QString, CANframe> systemValues_;
};

#endif // SYSTEM_H
