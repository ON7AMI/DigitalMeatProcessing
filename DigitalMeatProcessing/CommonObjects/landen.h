#ifndef LANDEN_H
#define LANDEN_H

#include <QObject>
#include <QtCore>
#include <QtSql>
#include <QSqlDatabase>
#include <QSettings>
#include <QApplication>


class Landen
{
public:
    Landen();

public:     // statics
    static void getAllLanden( QSqlQueryModel* );
    static QString getLandByCode(QString _code);


};

#endif // LANDEN_H
