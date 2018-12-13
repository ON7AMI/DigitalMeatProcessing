#ifndef KORTINGSCATEGORIE_H
#define KORTINGSCATEGORIE_H


#include <QObject>
#include <QtCore>
#include <QtSql>
#include <QSqlDatabase>
#include <QSettings>
#include <QApplication>

class KortingsCategorie
{
public:
    KortingsCategorie();


public:     // statics
    static void getAllKortingsCategorie( QSqlQueryModel* );

};

#endif // KORTINGSCATEGORIE_H
