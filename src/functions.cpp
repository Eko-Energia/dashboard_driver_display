#include "functions.h"
#include <QByteArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonValue>
#include <QFile>

QJsonObject text_to_JSON(const QString& message){
    QByteArray byteArray = message.toUtf8();
    QJsonParseError parseError;
    QJsonDocument jsonDoc = QJsonDocument::fromJson(byteArray, &parseError);
    if(parseError.error != QJsonParseError::NoError){
        qWarning() << ">Błąd parsowania JSON:" << parseError.errorString();
        return {};
    }
    QJsonObject jsonObj = jsonDoc.object();
    return jsonObj;
}
QStringList loadSubscriptions(){
    QStringList subs; // Lista subskrypcji pozniej uzyta do budowy slownika
    QFile file("qrc:/subs.txt"); //pozniej trzeba dokladna lokacje podac
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qWarning() << "Błąd przy otwarciu pliku subskrypcji";
        return subs;
    }

    QTextStream in(&file);

    while (!in.atEnd()) {
        QString line = in.readLine().trimmed();

        // pomijamy puste linie i komentarze
        if (line.isEmpty() || line.startsWith('#'))
            continue;

        subs.append(line);
    }

    return subs;
}
