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

CANframe parseLine(const QString& line){
    QStringList sections = line.split('|');

    if(sections.size() < 2){
        qWarning() << "Bledny zapis ramki w subs.txt" << line;
        return CANframe("INCORRECT_FRAME");
    }

    QString CANframeName = sections[0].trimmed();
    QStringList CANsignals = sections[1].split(',');

    CANframe frame(CANframeName);

    for(const QString& signalName : CANsignals){
        frame.addSignal(CANsignal(signalName.trimmed()));
    }

    return frame;
}

QList<CANframe> loadSubscriptions(){
    QStringList subs;
    QFile file(":/subs.txt"); // w trakcie kompilacji ma byc w tym samym folderze co .qrc
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qWarning() << "Błąd przy otwarciu pliku subskrypcji";
        return { CANframe("INCORRECT_FRAME") };
    }
    
    QTextStream in(&file);
    QList<CANframe> output;

    while (!in.atEnd()) {
        QString line = in.readLine().trimmed();
        // pomijamy puste linie i komentarze
        if (line.isEmpty() || line.startsWith('#'))
            continue;
        CANframe t_frame = parseLine(line);
        output.append(t_frame);
    }

    return output;
}

