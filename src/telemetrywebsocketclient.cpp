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
        /*{
              "type": "mileage_update",
              "total_km": 156.4232
            }*/
    }
    else if (type == "speed_update") {
        emit speedUpdateReceived(received_JSON["speed_kmh"].toDouble());
        /*{
              "type": "speed_update",
              "speed_kmh": 25.45
            }*/
    }
    else if (type == "energy_update") {
        emit energyUpdateReceived(received_JSON["avg_power_w"].toDouble(), received_JSON["interval_s"].toDouble());
        /*{
              "type": "energy_update",
              "avg_power_w": 1250.35,
              "interval_s": 3600.0
            }*/
        // Teoretycznie energia udostepnia interwal na ktorym liczona jest srednia wiec w przyszlosci mozna to napisac dynamiczniej
        // Zeby juz QT interpretowalo sobie czy srednia jest na minute godzine cokolwiek
    }
    else if (type == "error_update") {
        emit errorUpdateReceived(received_JSON["code"].toDouble(), received_JSON["name"].toString());
    }
    /*{
          "type": "error_update",
          "frame": "MOTOR_LEFT_NODE",
          "code": 2000,
          "name": "Voltage out of range"
        }*/

    else {
        qDebug() << "Telemetry: otrzymano niespodziewany typ wiadomosci" << type;
    }
}
