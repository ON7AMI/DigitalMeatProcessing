#include "btwtarieven.h"

#include <QString>
#include <QtCore>
#include <QtSql>
#include <QSqlDatabase>
#include <QSettings>
#include <QApplication>

//==================================================================================================
//  Properties
//
//==================================================================================================
//
// btwtarief_id serial NOT NULL,
// tarief character varying,
// percentage numeric(18,2),
// geldig_vanaf date,
// geldig_tot date,
//

//void BTWTarieven::

void BTWTarieven::setBTWTarief_ID( int _id)
{
    BTWTarief_ID = _id;
}

int BTWTarieven::getBTWTarief_ID()
{
    return BTWTarief_ID;
}

int BTWTarieven::getBTWTariefByPercent(double _percentage)
{
    if(_percentage == 0.0)
        return 1;
    else if (_percentage == 6.0)
        return 2;
    else if (_percentage == 12.0)
        return 3;
    else if (_percentage == 21.0)
        return 4;
    else
        return 0;
}

void BTWTarieven::setTarief(QString _tarief)
{
    Tarief = _tarief;
}

QString BTWTarieven::getTarief()
{
    return Tarief;
}

void BTWTarieven::setPercentage(double _percentage)
{
    Percentage = _percentage;
}

double BTWTarieven::getPercentage()
{
    return Percentage;
}

void BTWTarieven::setGeldigVanaf(QDate _geldigVanaf)
{
    GeldigVanaf = _geldigVanaf;
}

QDate BTWTarieven::getGeldigVanaf()
{
    return GeldigVanaf;
}

void BTWTarieven::setGeldigTot(QDate _geldigTot)
{
    GeldigTot = _geldigTot;
}

QDate BTWTarieven::getGeldigTot()
{
    return GeldigTot;
}


//================================================================================================
//  Constructors
//


BTWTarieven::BTWTarieven()
{
    BTWTarief_ID = 0;
    Tarief = "";
    Percentage = 0;
    GeldigVanaf = QDate::currentDate();
    GeldigTot = QDate(2099, 1, 1);

}

BTWTarieven::BTWTarieven(int _id)
{
    BTWTarief_ID = _id;
    read();
}

//=================================================================================================
//  Methods
//

void BTWTarieven::read()
{
    QString myQuery;
    QSqlQuery qry;
    bool status;

    myQuery = "SELECT * FROM common.btw_tarieven WHERE btwtarief_id = :v_btwtarief_id; ";

    qry.prepare(myQuery);
    qry.bindValue(":v_btwtarief_id", BTWTarief_ID);
    status = qry.exec();
    if (status )
    {
        status = qry.next();
        if (status )
        {
            BTWTarief_ID = qry.value("btwtarief_id").toInt();
            Tarief = qry.value("tarief").toString();
            Percentage = qry.value("percentage").toDouble();
            GeldigVanaf = qry.value("geldig_vanaf").toDate();
            GeldigTot = qry.value("geldig_tot").toDate();
        }
        else
        {
            qDebug() << "Error bij lezen BTW record (of geen record gevonden)- " << qry.lastError().text();
        }
    }
    else
    {
        BTWTarief_ID = 0;
        qDebug() << "Database error BTWTarieven: " << qry.lastError().databaseText() << "\nQuerry error: " << qry.lastError().text();
    }
}


void BTWTarieven::save()
{

    QString myQuery;
    QSqlQuery qry;

    if (BTWTarief_ID == 0)
    {
        myQuery ="INSERT INTO common.btw_tarieven "
                 "(tarief, percentage, geldig_vanaf, geldig_tot) "
                 "VALUES (:v_tarief, :v_percentage, :v_geldig_vanaf, :v_geldig_tot);";
        qry.prepare(myQuery);

    }
    else
    {
        myQuery = "UPDATE common.btw_tarieven "
                  "SET  "
                      "tarief = :v_tarief, "
                      "percentage = :v_percentage, "
                      "geldig_vanaf = :v_geldig_vanaf, "
                      "geldig_tot = :v_geldig_tot "
                  "WHERE btwtarief_id = :v_btwtarief_id;";

        qry.prepare(myQuery);
        qry.bindValue(":v_btwtarief_id", BTWTarief_ID);
    }

    qry.bindValue(":v_tarief", Tarief);
    qry.bindValue(":v_percentage", Percentage);
    qry.bindValue(":v_geldig_vanaf", GeldigVanaf);
    qry.bindValue(":v_geldig_tot", GeldigTot);

    if (qry.exec())
    {
        if (BTWTarief_ID == 0)
        {
            BTWTarief_ID = qry.lastInsertId().toInt();
        }
    }
    else
    {
        qDebug() << "Database error BTWTarief: " << qry.lastError().databaseText() << "\nQuerry error: " << qry.lastError().text();
    }

}


//====================================================================================================
//   Static Methods
//

void BTWTarieven::getAllBTWTarieven(QSqlQueryModel *model)
{
    model->setQuery("SELECT btwtarief_id, tarief, percentage, geldig_vanaf, geldig_tot  FROM common.btw_tarieven ORDER BY tarief;");
}

void BTWTarieven::getBTWTarievenKeuze(QSqlQueryModel *model)
{
    QString myQuery = "SELECT btwtarief_id, tarief FROM common.btw_tarieven ORDER BY tarief;";
    QSqlQuery qry;
    qry.prepare(myQuery);
    qry.exec();
    model->setQuery(qry);
}
int BTWTarieven::getDefaultBTW()
{
    QString myQuery;
    QSqlQuery qry;
    bool status;
    int defBTW;

    myQuery = "SELECT btwtarief_id FROM common.btw_tarieven WHERE defa; ";

    qry.prepare(myQuery);
    status = qry.exec();
    if (status )
    {
        status = qry.next();
        if (status )
        {
            defBTW = qry.value("btwtarief_id").toInt();
        }
        else
        {
            qDebug() << "Error bij lezen default BTW (of geen record gevonden)- " << qry.lastError().text();
        }
    }
    else
    {
        defBTW = 0;
        qDebug() << "Database error BTWTarieven: " << qry.lastError().databaseText() << "\nQuerry error: " << qry.lastError().text();
    }
    return defBTW;
}

double BTWTarieven::getBTWPercentage(int _id)
{
    QString myQuery;
    QSqlQuery qry;
    bool status;
    double percentage = 0;

    myQuery = "SELECT percentage FROM common.btw_tarieven WHERE btwtarief_id = :v_btwtarief_id; ";

    qry.prepare(myQuery);
    qry.bindValue(":v_btwtarief_id", _id);
    status = qry.exec();
    if (status )
    {
        status = qry.next();
        if (status )
        {
            percentage = qry.value("percentage").toDouble();
        }
        else
        {
            qDebug() << "Error bij lezen BTW Percentage (of geen record gevonden)- " << qry.lastError().text();
        }
    }
    else
    {
        percentage = 0;
        qDebug() << "Database error BTWTarieven: " << qry.lastError().databaseText() << "\nQuerry error: " << qry.lastError().text();
    }
    return percentage;
}
