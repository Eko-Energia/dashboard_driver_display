#pragma once

#include <QObject>
#include <QWebSocket>
#include <QUrl>

class WebSocketClient : public QObject
{
    Q_OBJECT

public:
    explicit WebSocketClient(QObject *parent = nullptr);
    void connectToServer(const QUrl& url);
    void sendMessage(const QString& message);
    void subscribeMessages(const QStringList& messageNames);
signals:

    void snapshotReceived(QJsonObject& snapshot);
    void updateReceived(QJsonObject& update);

private slots:
    void onConnected();
    void onTextMessageReceived(const QString& message);
    void onDisconnected();
    void onBinaryMessageReceived(const QByteArray& data);

private:
    QWebSocket m_socket;
};
