#include "blinker.h"
#include <QTimer>

Blinker::Blinker(QObject* parent) : QObject(parent) , currentState_(false), blinkState_(false) {
    timer_.setInterval(500);
    connect(&timer_, &QTimer::timeout, this, &Blinker::blinkEdit); // Łączy sygnal timeout ze slotem klasy
}

void Blinker::newState(bool updated) {
    if(updated == currentState_) { return; }

    currentState_ = updated ;
    emit stateChanged();

    if(currentState_){ timer_.start(); }

    else{
        timer_.stop();
        blinkState_ = false;
    }

}

void Blinker::blinkEdit(){
    blinkState_ = !blinkState_;
    emit blinkChanged();
}
