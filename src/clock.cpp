#include "clock.h"
#include <QTime>
#include <QDate>

Clock::Clock(QObject *parent) : QObject(parent) {
    updateDateTime();
    connect(&timer_, &QTimer::timeout, this, &Clock::updateDateTime);
    timer_.start(60000);
}

QString Clock::time() const {
    return time_;
}

QString Clock::date() const {
    return date_;
}

void Clock::updateDateTime() {
    QString currentTime = QTime::currentTime().toString("HH:mm");
    QString currentDate = QDate::currentDate().toString("yyyy-MM-dd");
    if(currentTime != time_){
        time_ = currentTime;
        emit timeChanged();
    }
    if (currentDate != date_) {
        date_ = currentDate;
        emit dateChanged();
    }
}
