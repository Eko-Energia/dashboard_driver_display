#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QVariant>
#include <iostream>
#include <iomanip>
#include <thread>
#include "system.h"

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
    
    System system(&engine, "vcan0" );

    std::thread systemThread([&system]() {
        system.start();
    });
    systemThread.detach();
    
    engine.load(QUrl("qrc:/qml/Main.qml"));
    if (engine.rootObjects().isEmpty()) {return -1;}

    

    int appResult = app.exec();

    return appResult;
}
