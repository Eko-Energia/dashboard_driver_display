#pragma once

#include "websocketclient.h"

// Klient websocket do serwera telemetrii (przebieg/predkosc z GPS), oddzielnego od
// glownego serwera CAN (websocketclient.h). Serwer ten nie obsluguje mechanizmu
// subskrypcji ramek, dlatego onConnected nie wysyla zadania subskrypcji, a wiadomosci
// maja inny format ("mileage_update"/"speed_update") niz "snapshot"/"update".
class TelemetryWebSocketClient : public WebSocketClient
{
    Q_OBJECT

public:
    explicit TelemetryWebSocketClient(QUrl serverURL, QObject *parent = nullptr);

signals:
    void mileageUpdateReceived(double totalKm);
    void speedUpdateReceived(double speedKmh);

protected slots:
    void onConnected() override;
    void onTextMessageReceived(const QString& message) override;
};
