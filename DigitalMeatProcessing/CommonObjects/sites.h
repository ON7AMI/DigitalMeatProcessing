#ifndef SITES_H
#define SITES_H

#include <QObject>
#include <QtCore>
#include <QtSql>
#include <QSqlDatabase>
#include <QSettings>
#include <QApplication>

class Sites
{
public:
    Sites();

public:     // statics
    static void getAllSites( QSqlQueryModel* );

};

#endif // SITES_H
