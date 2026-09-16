#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QVariant>
#include <iostream>
#include <iomanip>
#include <thread>
#include "system.h"
#include "websocketclient.h"
#include "telemetrywebsocketclient.h"
#include "clock.h"
#include "functions.h"

int main(int argc, char *argv[]) {
    QGuiApplication app(argc, argv);
    QQmlApplicationEngine engine;

    WebSocketClient client(QUrl("ws://localhost:8080"));
    TelemetryWebSocketClient telemetryClient(QUrl("ws://localhost:8081"));
    System system;
    Clock clock;
//  Obsluga polaczenia bezposrednio z can-receiverem
    QObject::connect(&client, &WebSocketClient::snapshotReceived, &system, &System::readSnapshot);
    QObject::connect(&client, &WebSocketClient::updateReceived, &system, &System::readUpdate);
// Polaczenie z rpi_utils
    QObject::connect(&telemetryClient, &TelemetryWebSocketClient::mileageUpdateReceived, &system, &System::readMileageUpdate);
    QObject::connect(&telemetryClient, &TelemetryWebSocketClient::speedUpdateReceived, &system, &System::readSpeedUpdate);
    QObject::connect(&telemetryClient, &TelemetryWebSocketClient::energyUpdateReceived, &system, &System::readEnergyUpdate);
    QObject::connect(&telemetryClient, &TelemetryWebSocketClient::errorUpdateReceived, &system, &System::readErrorUpdate);
    QObject::connect(&telemetryClient, &TelemetryWebSocketClient::snapshotErrorsReceived, &system, &System::readSnapshotErrors);

    client.connectToServer();
    telemetryClient.connectToServer();

    engine.rootContext()->setContextProperty("clock", &clock);
    engine.rootContext()->setContextProperty("system", &system);

    engine.load(QUrl("qrc:/qml/Main.qml"));
    if (engine.rootObjects().isEmpty()) {return -1;}


    return app.exec();
}

