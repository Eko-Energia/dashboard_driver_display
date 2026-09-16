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
    // --- telemetria z rpi_utilities (port 8081) ---
    // Jednostki zostaja takie, jakie nadaje producent - zadnej konwersji po drodze.
    // Kazde przeliczenie to kolejne miejsce, w ktorym jednostka moze sie rozjechac
    // z nazwa pola (tak jak wczesniej avg_power_kw czytane jako avg_power_w).
    // Formatowanie do postaci czytelnej dla kierowcy robi QML.
    Q_PROPERTY(double avgPowerKw READ avgPowerKw NOTIFY valuesChanged)
    Q_PROPERTY(double consumptionKwhPerKm READ consumptionKwhPerKm NOTIFY valuesChanged)
    Q_PROPERTY(bool consumptionValid READ consumptionValid NOTIFY valuesChanged)
    Q_PROPERTY(double energyCoverage READ energyCoverage NOTIFY valuesChanged)
    Q_PROPERTY(double energyIntervalS READ energyIntervalS NOTIFY valuesChanged)
    // --- pakiet JK, liczone z surowych ramek (port 8080) ---
    Q_PROPERTY(double packPowerKw READ packPowerKw NOTIFY valuesChanged)
    Q_PROPERTY(double packSoc READ packSoc NOTIFY valuesChanged)
    Q_PROPERTY(bool packStale READ packStale NOTIFY valuesChanged)

    double totalKm() const { return totalKm_; }
    double speedKmh() const { return speedKmh_; }
    double avgPowerKw() const { return avgPowerKw_; }
    // Wazne tylko gdy consumptionValid() - inaczej producent przyslal null i nie ma
    // czego pokazac (na postoju dystans w oknie zbiega do zera).
    double consumptionKwhPerKm() const { return consumptionKwhPerKm_; }
    bool consumptionValid() const { return consumptionValid_; }
    // Jaka czesc okna jest faktycznie pokryta danymi (0..1). Po starcie programu i po
    // przerwie w transmisji obie srednie licza sie z krotszego przedzialu niz nominalny.
    double energyCoverage() const { return energyCoverage_; }
    // Okno czasowe (w sekundach), z ktorego liczona jest srednia - po nim QML dobiera podpis (15min/30min/h)
    double energyIntervalS() const { return energyIntervalS_; }

    double packPowerKw() const { return packPowerKw_; }
    double packSoc() const { return packSoc_; }
    // true, gdy ostatnia ramka pakietu miala ustawiony bit bledu komunikacji z JK -
    // packPowerKw i packSoc trzymaja wtedy ostatni wiarygodny odczyt, a nie biezacy.
    bool packStale() const { return packStale_; }

signals:
    void valuesChanged();
    void errorReceived(const QString& frame, double code, const QString& name);
    void snapshotErrorsReceived(int count);
public slots:
    void readSnapshot(const QJsonObject& snapshot);
    void readUpdate(const QJsonObject& update);
    void readMileageUpdate(double totalKm);
    void readSpeedUpdate(double speedKmh);
    void readEnergyUpdate(double avgPowerKw,
                          double consumptionKwhPerKm,
                          bool consumptionValid,
                          double coverage,
                          double intervalS);
    void readErrorUpdate(const QString& frame, double code, const QString& name);
    void readSnapshotErrors(int count);

private:
    // Ramka BMSMaster_JK_Pack (CAN_DB.dbc, ID 140, cykl 1000 ms) - jedyne zrodlo
    // danych bateryjnych na ekranie. Ta sama, z ktorej rpi_utilities licza zuzycie.
    static const QString kPackFrame;
    static const QString kPackVoltageSignal;
    static const QString kPackCurrentSignal;
    static const QString kPackSocSignal;
    static const QString kPackStatusFlagsSignal;
    // StatusFlags bit 6 = blad komunikacji BMS Mastera z JK (CM_ BO_ 140 w CAN_DB.dbc).
    // Napiecie, prad i SOC z takiej ramki sa zamrozone, a nie zmierzone.
    static constexpr int kJkCommErrorBit = 1 << 6;

    void updatePackFromFrame();

    QHash<QString, CANframe> systemValues_;
    double totalKm_ = 0.0;
    double speedKmh_ = 0.0;
    double avgPowerKw_ = 0.0;
    double consumptionKwhPerKm_ = 0.0;
    bool consumptionValid_ = false;
    double energyCoverage_ = 0.0;
    // Domyslna dlugosc okna zgodna z ENERGY_INTERVAL_S w rpi_utilities/config.py -
    // i tak zostanie nadpisana pierwszym energy_update.
    double energyIntervalS_ = 900.0;
    double packPowerKw_ = 0.0;
    double packSoc_ = 0.0;
    bool packStale_ = false;
};

#endif // SYSTEM_H
