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
/*TODO

Ogarnac const correctnes w backendize
pousuwac zbedny kod, i dodac funkcje do debugowania
dokonczyc skrypt w bashu do testow
zrobic fajna dokumentajce
przetestowac wszystko i finito

zapytac ilony co z frontem / samemu sie wziac za to na powaznie

*/
int main(int argc, char *argv[]) {
    QGuiApplication app(argc, argv);
    QQmlApplicationEngine engine;

    WebSocketClient client;
    System system;
    Clock clock;

    QObject::connect(&client, &WebSocketClient::snapshotReceived, &system, &System::readSnapshot);
    QObject::connect(&client, &WebSocketClient::updateReceived, &system, &System::readUpdate);

    client.connectToServer(QUrl("ws://0.0.0.0:8080"));

    engine.rootContext()->setContextProperty("clock", &clock);
    engine.rootContext()->setContextProperty("system", &system);

    engine.load(QUrl("qrc:/qml/Main.qml"));
    if (engine.rootObjects().isEmpty()) {return -1;}

    return app.exec();
}

/*
    ramki co trzeba bedzie zasubskrybowac w kliencie:
    motor status - motorrpm (obroty), motortemp (temperatura)
    battery info - miedzy innymi stateofcharge % aladowania
    sensordata - speed, ambienttemp, jest tez cisnienie i wilgotnosc
    controlcommands - Powermode (tryb jazdy, eco sport bla bla bla), EcoMode (true/false, najwidoczniej do wyswietalania ze jest wlaczony)
    diagnosticinfo - errorcode

*/
