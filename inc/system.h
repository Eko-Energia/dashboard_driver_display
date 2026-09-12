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

    Q_PROPERTY(double totalKm READ totalKm NOTIFY valuesChanged)
    Q_PROPERTY(double speedKmh READ speedKmh NOTIFY valuesChanged)
    Q_PROPERTY(double avgPowerW READ avgPowerW NOTIFY valuesChanged)
    double totalKm() const { return totalKm_; }
    double speedKmh() const { return speedKmh_; }
    double avgPowerW() const { return avgPowerW_; }
signals:
    void valuesChanged();
public slots:
    void readSnapshot(const QJsonObject& snapshot);
    void readUpdate(const QJsonObject& update);
    void readMileageUpdate(double totalKm);
    void readSpeedUpdate(double speedKmh);
    void readEnergyUpdate(double avgPowerW, double intervalS);

private:
    QHash<QString, CANframe> systemValues_;
    double totalKm_ = 0.0;
    double speedKmh_ = 0.0;
    double avgPowerW_ = 0.0;
};

#endif // SYSTEM_H
