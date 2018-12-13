#ifndef GEBRUIKERS_H
#define GEBRUIKERS_H

#include <QObject>
#include <QtCore>
#include <QtSql>
#include <QSqlDatabase>
#include <QSettings>
#include <QApplication>

class Gebruikers
{
public:
    Gebruikers();
    static void getAllGebruikers(QSqlQueryModel* model);
    static void CleanDagboek();
};

#endif // GEBRUIKERS_H
