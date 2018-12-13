#ifndef FIRMA_H
#define FIRMA_H

#include <QObject>
#include <QtCore>
#include <QtSql>
#include <QSqlDatabase>
#include <QSettings>
#include <QApplication>


class Firma
{
public:
    Firma();


public:
    static void getAllFirmas(QSqlQueryModel* ) ;

};

#endif // FRIRMA_H
