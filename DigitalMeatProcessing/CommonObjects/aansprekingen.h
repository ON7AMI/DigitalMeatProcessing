#ifndef AANSPREKINGEN_H
#define AANSPREKINGEN_H

#include <QObject>
#include <QtCore>
#include <QtSql>
#include <QSqlDatabase>
#include <QSettings>
#include <QApplication>

class Aansprekingen
{
public:
    Aansprekingen();


public:
    static void getAllAansprekingen( QSqlQueryModel* );

};

#endif // AANSPREKINGEN_H
