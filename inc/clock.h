#ifndef CLOCK_H
#define CLOCK_H

#include <QObject>
#include <QTimer>
#include <QString>

class Clock : public QObject {
    Q_OBJECT
    Q_PROPERTY(QString time READ time NOTIFY timeChanged)
    Q_PROPERTY(QString date READ date NOTIFY dateChanged)

public:
    explicit Clock(QObject *parent = nullptr);

    QString time() const;
    QString date() const;

signals:
    void timeChanged();
    void dateChanged();

private slots:
    void updateDateTime();

private:
    QTimer timer_;
    QString date_;
    QString time_;
};



#endif // CLOCK_H
