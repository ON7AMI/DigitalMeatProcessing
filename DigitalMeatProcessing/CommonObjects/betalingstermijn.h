#ifndef BETALINGSTERMIJN_H
#define BETALINGSTERMIJN_H


#include <QObject>
#include <QtCore>
#include <QtSql>
#include <QSqlDatabase>
#include <QSettings>
#include <QApplication>


class BetalingsTermijn
{
public:
    BetalingsTermijn();


public:     // statics
    static void getAllBetalingsTermijn( QSqlQueryModel* );


};

#endif // BETALINGSTERMIJN_H
