#ifndef FUNCTIONS_H
#define FUNCTIONS_H
#include <QJsonObject>
#include <QString>
QJsonObject text_to_JSON(const QString& message);
QStringList loadSubscriptions(); // Domyslnie bedzie w tym samym folderze

#endif // FUNCTIONS_H
