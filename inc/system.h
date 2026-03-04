#ifndef SYSTEM_H
#define SYSTEM_H

#include <QHash>
#include <QString>
#include <QObject>
#include <QVariant>
#include <QVariantMap>
class System : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QVariantMap values READ values NOTIFY valuesChanged)
public:
    explicit System(QObject *parent = nullptr);
    QVariantMap values() const;

signals:
    void valuesChanged();
public slots:
    void readSnapshot(QJsonObject& snapshot);
    void readUpdate(QJsonObject& update);

private:
    QHash<QString, QString> systemValues_;
};

#endif // SYSTEM_H
