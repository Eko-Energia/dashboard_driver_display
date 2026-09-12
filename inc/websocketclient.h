#pragma once

#include <QObject>
#include <QWebSocket>
#include <QUrl>

class WebSocketClient : public QObject
{
    Q_OBJECT

public:
    explicit WebSocketClient(QUrl serverURL, QObject *parent = nullptr);
    void connectToServer();
    void sendMessage(const QString& message);
    void subscribeMessages(const QStringList& messageNames);
signals:

    void snapshotReceived(QJsonObject& snapshot);
    void updateReceived(QJsonObject& update);

protected slots:
    virtual void onConnected();
    virtual void onTextMessageReceived(const QString& message);

private slots:
    void onDisconnected();
    void onBinaryMessageReceived(const QByteArray& data);

private:
    QWebSocket m_socket;
    QUrl addres;
};
