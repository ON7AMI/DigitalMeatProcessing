#ifndef BKHCATEGORIE_H
#define BKHCATEGORIE_H

#include <QObject>
#include <QtCore>
#include <QtSql>
#include <QSqlDatabase>
#include <QSettings>
#include <QApplication>


class BKHCategorie
{
public:
    BKHCategorie();

public:     // statics
    static void getAllBKHCategorie( QSqlQueryModel* model);

};

#endif // BKHCATEGORIE_H
