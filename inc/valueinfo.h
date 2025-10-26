#ifndef VALUEINFO_H
#define VALUEINFO_H

#include <QObject>
#include <QVariant>
#include <iostream>
#include <QMetaType>

class ValueInfo : public QObject {
    Q_OBJECT
    Q_PROPERTY(QVariant value READ value WRITE setValue NOTIFY valueChanged)

public:
    explicit ValueInfo(QMetaType type, QVariant defaultValue = 0, QObject *parent = nullptr);
    // Jakby byl jakis problem z typami ValueInfo to bym sie przyjrzal konstruktorowi. 
    QVariant value() const {return value_;}
    void setValue(QVariant newValue);
    void setGear(uint newGear); // Nie wiem narazie jak biegi zaimplementowac
signals:
    void valueChanged();

private:
    QVariant value_;
    const QMetaType type_;
};

#endif // VALUEINFO_H
