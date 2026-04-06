#include "websocketclient.h"
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>
#include <QDebug>  // Do wypisywania informacji w konsoli
#include <QTimer>
#include "functions.h"

WebSocketClient::WebSocketClient(QUrl serverURL,QObject *parent)
    : addres(serverURL), QObject(parent)
{
    connect(&m_socket, &QWebSocket::connected,
            this, &WebSocketClient::onConnected);

    connect(&m_socket, &QWebSocket::textMessageReceived,
            this, &WebSocketClient::onTextMessageReceived);

    connect(&m_socket, &QWebSocket::disconnected,
            this, &WebSocketClient::onDisconnected);

    connect(&m_socket, &QWebSocket::binaryMessageReceived,this, &WebSocketClient::onBinaryMessageReceived);
}

void WebSocketClient::connectToServer(const QUrl url)
{
    qDebug() << "Connecting to WebSocket:" << this->addres; // przy wywolaniu z custom url nie wyswietli sie poprawny adres ale nie zakladam narazie takiego uzycia
    m_socket.open(this->addres);
}

void WebSocketClient::sendMessage(const QString& message)
{
    m_socket.sendTextMessage(message);
}

void WebSocketClient::onConnected()
{
    qDebug() << "WebSocket connected";
    QStringList subs = loadSubscriptions();
    subscribeMessages(subs);
}

void WebSocketClient::onTextMessageReceived(const QString& message)
{
    QJsonObject received_JSON = text_to_JSON(message);

    if(received_JSON["type"] == "update"){
        emit updateReceived(received_JSON);
    }
    else if(received_JSON["type"] == "snapshot"){
        emit snapshotReceived(received_JSON);
    }
    else{
        qDebug() << "Otrzymano niespodziewany typ wiadomosci";
    }
}

void WebSocketClient::onDisconnected()
{
    qDebug() << "WebSocket disconnected";

    QTimer::singleShot(1000, this, [this]() {
        qDebug() << "Reconnecting WebSocket";
        this->connectToServer(); 
    });
}

void WebSocketClient::subscribeMessages(const QStringList& messageNames)
{
    QJsonArray array;
    for (const QString& name : messageNames) {
        array.append(name);
    }
    QJsonObject obj;
    obj["type"] = "subscribe";       // typ wiadomości
    obj["message_names"] = array;    // lista nazw wiadomości
    QJsonDocument doc(obj);
    QString jsonString = doc.toJson(QJsonDocument::Compact);

    m_socket.sendTextMessage(jsonString);

    qDebug() << "Sent subscribe message:" << jsonString;
}

void WebSocketClient::onBinaryMessageReceived(const QByteArray &data){
    qDebug() << "to jest test";
}
