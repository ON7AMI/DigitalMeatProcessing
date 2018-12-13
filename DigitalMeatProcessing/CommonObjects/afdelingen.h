#ifndef AFDELINGEN_H
#define AFDELINGEN_H

#include <QObject>
#include <QtCore>
#include <QtSql>
#include <QSqlDatabase>
#include <QSettings>
#include <QApplication>


class Afdelingen
{
public:
    Afdelingen();

public:     // statics
    static void getAllAfdelingen( QSqlQueryModel* );

};

#endif // AFDELINGEN_H
