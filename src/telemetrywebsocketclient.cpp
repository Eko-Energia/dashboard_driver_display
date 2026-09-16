#include "telemetrywebsocketclient.h"
#include <QJsonObject>
#include <QJsonValue>
#include <QDebug>
#include "functions.h"

TelemetryWebSocketClient::TelemetryWebSocketClient(QUrl serverURL, QObject *parent)
    : WebSocketClient(serverURL, parent)
{
    snapshotWindow_.setSingleShot(true);
    snapshotWindow_.setInterval(kSnapshotWindowMs);
    connect(&snapshotWindow_, &QTimer::timeout, this, [this]() {
        if (snapshotErrorCount_ > 0) {
            emit snapshotErrorsReceived(snapshotErrorCount_);
        }
        snapshotErrorCount_ = 0;
    });
}

void TelemetryWebSocketClient::onConnected()
{
    qDebug() << "Telemetry WebSocket connected";
    // Nowe polaczenie to nowa paczka snapshotowa - liczymy ja od zera, nawet jesli
    // poprzednie okno nie zdazylo sie domknac (szybki reconnect).
    snapshotErrorCount_ = 0;
    snapshotWindow_.start();
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
        /*{
              "type": "energy_update",
              "avg_power_kw": 1.25,
              "consumption_kwh_per_km": 0.0821,   // albo null
              "energy_kwh": 1.0523,               // nieuzywane przez ekran
              "distance_km": 12.8134,             // nieuzywane przez ekran
              "interval_s": 900.0,
              "coverage": 0.987
            }*/
        // consumption_kwh_per_km bywa nullem, a QJsonValue::toDouble() zwrocilby wtedy
        // po cichu 0.0 - czyli "jedziemy za darmo" zamiast "nie wiadomo". Stad jawna
        // flaga waznosci zamiast wartosci wartowniczej.
        const QJsonValue consumption = received_JSON.value("consumption_kwh_per_km");
        const bool consumptionValid = consumption.isDouble();

        emit energyUpdateReceived(received_JSON["avg_power_kw"].toDouble(),
                                  consumptionValid ? consumption.toDouble() : 0.0,
                                  consumptionValid,
                                  received_JSON["coverage"].toDouble(),
                                  received_JSON["interval_s"].toDouble());
    }
    else if (type == "error_update") {
        /*{
              "type": "error_update",
              "frame": "MPPT_NODE",
              "code": 2000,
              "name": "Voltage out of range"
            }*/
        if (snapshotWindow_.isActive()) {
            ++snapshotErrorCount_;
        } else {
            emit errorUpdateReceived(received_JSON["frame"].toString(),
                                     received_JSON["code"].toDouble(),
                                     received_JSON["name"].toString());
        }
    }
    else {
        qDebug() << "Telemetry: otrzymano niespodziewany typ wiadomosci" << type;
    }
}
