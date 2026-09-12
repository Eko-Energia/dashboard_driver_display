#include "telemetrywebsocketclient.h"
#include <QJsonObject>
#include <QDebug>
#include "functions.h"

TelemetryWebSocketClient::TelemetryWebSocketClient(QUrl serverURL, QObject *parent)
    : WebSocketClient(serverURL, parent)
{
}

void TelemetryWebSocketClient::onConnected()
{
    qDebug() << "Telemetry WebSocket connected";
}

void TelemetryWebSocketClient::onTextMessageReceived(const QString& message)
{
    QJsonObject received_JSON = text_to_JSON(message);
    QString type = received_JSON["type"].toString();

    if (type == "mileage_update") {
        emit mileageUpdateReceived(received_JSON["total_km"].toDouble());
    }
    else if (type == "speed_update") {
        emit speedUpdateReceived(received_JSON["speed_kmh"].toDouble());
    }
    else {
        qDebug() << "Telemetry: otrzymano niespodziewany typ wiadomosci" << type;
    }
}
