#pragma once

#include <QTimer>

#include "websocketclient.h"

// Klient websocket do serwera telemetrii (rpi_utilities, port 8081), oddzielnego od
// glownego serwera CAN (websocketclient.h). Serwer ten nie obsluguje mechanizmu
// subskrypcji ramek, dlatego onConnected nie wysyla zadania subskrypcji, a wiadomosci
// maja plaski format ("speed_update"/"mileage_update"/"energy_update"/"error_update")
// zamiast "snapshot"/"update". Kontrakt opisuja modele w rpi_utilities/src/rpi_utilities/models.py.
class TelemetryWebSocketClient : public WebSocketClient
{
    Q_OBJECT

public:
    explicit TelemetryWebSocketClient(QUrl serverURL, QObject *parent = nullptr);

signals:
    void mileageUpdateReceived(double totalKm);
    void speedUpdateReceived(double speedKmh);
    // consumptionValid == false, gdy producent przyslal null - na postoju dystans w
    // oknie zbiega do zera i kWh/km przestaje cokolwiek znaczyc. Jednostki zostaja
    // takie, jakie przyszly (kW, kWh/km); przeliczenie na Wh/km robi dopiero QML.
    void energyUpdateReceived(double avgPowerKw,
                              double consumptionKwhPerKm,
                              bool consumptionValid,
                              double coverage,
                              double intervalS);
    void errorUpdateReceived(const QString& frame, double code, const QString& name);
    // Zbiorcza informacja o bledach z paczki snapshotowej - patrz kSnapshotWindowMs.
    void snapshotErrorsReceived(int count);

protected slots:
    void onConnected() override;
    void onTextMessageReceived(const QString& message) override;

private:
    // Zaraz po polaczeniu rpi_utilities wysylaja komplet zapamietanych bledow
    // (Telemetry.snapshot()). Popup miesci ~4 wiersze, wiec taka paczka wypchnelaby
    // z niego wszystko biezace. Wiadomosci ErrorMessage nie maja znacznika czasu, a
    // snapshot idzie w kolejnosci pierwszego wystapienia ramki - nie da sie wiec
    // wybrac "najnowszych". Dlatego cala paczke zliczamy i pokazujemy jako jeden wiersz.
    static constexpr int kSnapshotWindowMs = 2000;

    QTimer snapshotWindow_;
    int snapshotErrorCount_ = 0;
};
