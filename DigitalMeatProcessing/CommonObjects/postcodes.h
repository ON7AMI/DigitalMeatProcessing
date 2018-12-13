#ifndef POSTCODES_H
#define POSTCODES_H

#include <QtCore>
#include <QtSql>
#include <QSqlDatabase>
#include <QSettings>
#include <QApplication>

class Postcodes
{
public:
    Postcodes();

    static QString getPocode(int _id);
    static QString getGemeente(int _id);
    static void getPostcodesPerLand(QSqlQueryModel*, QString _LandCode);
    static void getGemeentesPerLand(QSqlQueryModel*, QString _LandCode);
    static void getGemeentesPerLandEnPostcode(QSqlQueryModel*, QString _LandCode, QString _Postcode);
    static void getGemeentesPostcodes(QSqlQueryModel*, QString _Postcode);

};

#endif // POSTCODES_H
