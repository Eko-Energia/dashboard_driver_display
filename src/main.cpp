#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QVariant>
#include <iostream>
#include <iomanip>
#include <thread>
#include "system.h"
#include "websocketclient.h"
#include "clock.h"
#include "functions.h"

int main(int argc, char *argv[]) {
    QGuiApplication app(argc, argv);
    QQmlApplicationEngine engine;

    WebSocketClient client(QUrl("ws://0.0.0.0:8080"));
    System system;
    Clock clock;

    QObject::connect(&client, &WebSocketClient::snapshotReceived, &system, &System::readSnapshot);
    QObject::connect(&client, &WebSocketClient::updateReceived, &system, &System::readUpdate);

    client.connectToServer();

    engine.rootContext()->setContextProperty("clock", &clock);
    engine.rootContext()->setContextProperty("system", &system);

    engine.load(QUrl("qrc:/qml/Main.qml"));
    if (engine.rootObjects().isEmpty()) {return -1;}


    return app.exec();
}

