#include "lotnummerdbevat.h"


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
// lotnr_id serial NOT NULL,
// bevat_lotnummer_id integer,
// hoeveelheid_in numeric(20,4),
//

int LotnummerdBevat::getBevat_ID() { return Bevat_ID; }
void LotnummerdBevat::setBevat_ID(int _id) { Bevat_ID = _id; }

int LotnummerdBevat::getLotnr_ID() { return Lotnr_ID; }
void LotnummerdBevat::setLotnr_ID(int _id) { Lotnr_ID = _id; }

int LotnummerdBevat::getBetvatLotnummer() { return BevatLotnummer; }
void LotnummerdBevat::setBevatLotnummer(int _id) { BevatLotnummer = _id; }

double LotnummerdBevat::getHoeveelheidIn() { return HoeveelheidIn; }
void LotnummerdBevat::setHoeveelheidIn(double geb) { HoeveelheidIn = geb; }


//================================================================================================
//  Constructors
//

LotnummerdBevat::LotnummerdBevat()
{
    clear();
}

LotnummerdBevat::LotnummerdBevat(int _id)
{
    Bevat_ID = _id;
    read();
}



//=================================================================================================
//  Methods
//

void LotnummerdBevat::clear()
{
    Bevat_ID = 0;
    Lotnr_ID = 0;
    BevatLotnummer = 0;
    HoeveelheidIn = 0;
}

void LotnummerdBevat::read()
{
    QString myQuery;
    QSqlQuery qry;
    bool status;

    myQuery = "SELECT * FROM productie.lotnummers_bevat WHERE bevat_id = :v_bevat_id; ";

    qry.prepare(myQuery);
    qry.bindValue(":v_bevat_id", Bevat_ID);
    status = qry.exec();
    if (status )
    {
        status = qry.next();
        if (status )
        {
            QryRead(&qry);
        }
        else
        {
            Bevat_ID= 0;
            qDebug() << "Error bij lezen LotnummerBevat record (of geen record gevonden)- " << qry.lastError().text();
        }
    }
    else
    {
        Bevat_ID = 0;
        qDebug() << "Database error lotnummerBevat: " << qry.lastError().databaseText() << "\nQuerry error: " << qry.lastError().text();
    }

}

void LotnummerdBevat::QryRead(QSqlQuery *qry)
{
    Bevat_ID = qry->value("bevat_id").toInt();
    Lotnr_ID = qry->value("lotnr_id").toInt();
    BevatLotnummer = qry->value("bevat_lotnummer_id").toInt();
    HoeveelheidIn = qry->value("hoeveelheid_in").toDouble();
}

void LotnummerdBevat::save()
{
    QString myQuery;
    QSqlQuery qry;

    if (Bevat_ID == 0)
    {
        myQuery =
        "INSERT INTO productie.lotnummers_bevat( "
                "lotnr_id, bevat_lotnummer_id, hoeveelheid_in) "
        "VALUES (:v_lotnr_id, :v_bevat_lotnummer_id, :v_hoeveelheid_in);";

        qry.prepare(myQuery);
    }
    else
    {
        myQuery =
                "UPDATE productie.lotnummers_bevat "
                "SET lotnr_id = :v_lotnr_id, "
                    "bevat_lotnummer_id = :v_bevat_lotnummer_id, "
                    "hoeveelheid_in = :v_hoeveelheid_in "
                "WHERE (bevat_id = :v_bevat_id);";


        qry.prepare(myQuery);
        qry.bindValue(":v_bevat_id", Bevat_ID);
    }
    qry.bindValue(":v_lotnr_id", Lotnr_ID);
    qry.bindValue(":v_bevat_lotnummer_id", BevatLotnummer);
    qry.bindValue(":v_hoeveelheid_in", HoeveelheidIn);

    if (qry.exec())
    {
        if (Bevat_ID == 0)
        {
            Bevat_ID = qry.lastInsertId().toInt();
        }
    }
    else
    {
        qDebug() << "Database error LotnummersBevat: " << qry.lastError().databaseText() << "\nQuerry error: " << qry.lastError().text();
    }
}

//===============================================================
//
//    Statics
//
//---------------------------------------------------------------
//

void LotnummerdBevat::getBevatPerLotnummer(QSqlQueryModel *qm, int _id)
{
    QSqlQuery qry;
    QString query;
    query =
             "SELECT "
                "b.bevat_id, "
                "l.lotnummer, "
                "a.code, "
                "a.benaming, "
                "b.hoeveelheid_in "
             "FROM "
                "productie.lotnummers_bevat as b, "
                "productie.lotnummerdata as l, "
                "artikelbeheer.artikelen as a "
             "WHERE "
                "b.bevat_lotnummer_id = l.lotnummer_id AND "
                "l.artikel_id = a.artikel_id AND "
                "b.lotnr_id = :v_id "
             "ORDER BY "
                "l.lotnummer ASC;";
    qry.prepare(query);
    qry.bindValue(":v_id", _id);
    if (!qry.exec())
    {
        qDebug() << qry.lastError() << " - " << qry.lastQuery();
    }
    qm->setQuery(qry);
}

void LotnummerdBevat::deleteRow(int _id)
{
    QString myQuery;
    QSqlQuery qry;

    myQuery =
    "DELETE FROM productie.lotnummers_bevat "
    "WHERE "
      "bevat_id = :v_id; ";

    qry.prepare(myQuery);
    qry.bindValue(":v_id", _id);
    bool status = qry.exec();
    if (!status)
    {
        qDebug() << "Error bij wissen Lotnummer(Bevat record- " << qry.lastError().text();
    }

}
