#include "prijzenconcurentie.h"
#include "artikelen.h"

#include <QString>
#include <QtCore>
#include <QtSql>
#include <QSqlDatabase>


//==================================================================================================
//  Properties
//
//==================================================================================================
//
// prijs_id serial NOT NULL,
// artikel_id integer,
// relatie_id integer,
// datum_aankoop date,
// prijs numeric(20,4),
// datum_invoer date,
//
//
void PrijzenConcurentie::setPrijs_ID( int _id ) { Prijs_ID = _id; }
int PrijzenConcurentie::getPrijs_ID() { return Prijs_ID; }

void PrijzenConcurentie::setArtikel_ID( int _id ) { Artikel_ID = _id; }
int PrijzenConcurentie::getArtikel_ID() { return Artikel_ID; }

void PrijzenConcurentie::setRelatie_ID( int _id ) { Relatie_ID = _id; }
int PrijzenConcurentie::getRelatie_ID() { return Relatie_ID; }

void PrijzenConcurentie::setDatumAankoop( QDate _datum ) { DatumAankoop = _datum; }
QDate PrijzenConcurentie::getDatumAankoop() { return DatumAankoop; }

void PrijzenConcurentie::setPrijs( double _prijs ) { Prijs = _prijs; }
double PrijzenConcurentie::getPrijs() { return Prijs; }

void PrijzenConcurentie::setDatumInvoer( QDate _datum ) { DatumInvoer = _datum; }
QDate PrijzenConcurentie::getDatumInvoer() { return DatumInvoer; }

//================================================================================================
//  Constructors
//


PrijzenConcurentie::PrijzenConcurentie()
{
    clear();
}

PrijzenConcurentie::PrijzenConcurentie(int _id )
{
    Prijs_ID = _id;
    read();
}


//=================================================================================================
//  Methods
//


void PrijzenConcurentie::save()
{
    QString myQuery;
    QSqlQuery qry;

    if (Prijs_ID == 0)
    {
        myQuery = "INSERT INTO artikelbeheer.prijs_concurenten "
                      "( artikel_id, relatie_id, datum_aankoop, prijs, datum_invoer ) "
                  "VALUES (:v_artikel_id, :v_relatie_id, :v_datum_aankoop, "
                          ":v_prijs, :v_datum_invoer); ";

        qry.prepare(myQuery);

    }
    else
    {
        myQuery =
        "UPDATE artikelbeheer.prijs_concurenten "
        "SET artikel_id = :v_artikel_id, "
            "relatie_id = :v_relatie_id, datum_aankoop = :v_datum_aankoop, "
            "prijs = :v_prijs, datum_invoer = :v_datum_invoer "
        "WHERE (prijs_id = :v_prijs_id);";

        qry.prepare(myQuery);
        qry.bindValue(":v_prijs_id", Prijs_ID);
    }

    qry.bindValue(":v_artikel_id", Artikel_ID);
    qry.bindValue(":v_relatie_id", Relatie_ID);
    qry.bindValue(":v_datum_aankoop", DatumAankoop);
    qry.bindValue(":v_prijs", Prijs);
    qry.bindValue(":v_datum_invoer", DatumInvoer);

    if (qry.exec())
    {
        if (Prijs_ID == 0)
        {
            Prijs_ID = qry.lastInsertId().toInt();
        }
    }
    else
    {
        qDebug() << "Database error (PrijzenConcurentie): " << qry.lastError().databaseText() << "\nQuerry error: " << qry.lastError().text();
    }

}

void PrijzenConcurentie::read()
{
    QString myQuery;
    QSqlQuery qry;
    bool status;

    myQuery = "SELECT * FROM artikelbeheer.prijs_concurenten WHERE prijs_id = :v_prijs_id; ";

    qry.prepare(myQuery);
    qry.bindValue(":v_prijs_id", Prijs_ID);
    status = qry.exec();
    if (status )
    {
        status = qry.next();
        if (status )
        {
            Prijs_ID = qry.value("prijs_id").toInt();
            Artikel_ID = qry.value("artikel_id").toInt();
            Relatie_ID = qry.value("relatie_id").toInt();
            DatumAankoop = qry.value("datum_aankoop").toDate();
            Prijs = qry.value("prijs").toDouble();
            DatumInvoer = qry.value("datum_invoer").toDate();
        }
        else
        {
            qDebug() << "Error bij lezen PrijzenConcurentie record (of geen record gevonden)- " << qry.lastError().text();
        }
    }
    else
    {
        Prijs_ID = 0;
        qDebug() << "Database error (PrijzenConcurentie): " << qry.lastError().databaseText() << "\nQuerry error: " << qry.lastError().text();
    }
}

void PrijzenConcurentie::clear()
{
    Prijs_ID = 0;
    Artikel_ID = 0;
    Relatie_ID = 0;
    DatumAankoop = QDate::currentDate();
    Prijs = 0;
    DatumInvoer = QDate::currentDate();
}

//====================================================================================================
//   Static Methods
//


void PrijzenConcurentie::getPrijzenPerArtikel( QSqlQueryModel* _model, int _art_id )
{
    QString myQuery;
    QSqlQuery qry;

    myQuery =
    "SELECT "
      "prijs_concurenten.prijs_id, "
      "prijs_concurenten.artikel_id, "
      "prijs_concurenten.datum_aankoop, "
      "concat(relaties.naam , ' ', relaties.voornaam) as conc_naam, "
      "prijs_concurenten.prijs "
    "FROM "
      "artikelbeheer.prijs_concurenten, "
      "relaties.relaties "
    "WHERE "
      "prijs_concurenten.relatie_id = relaties.relatie_id AND "
      "prijs_concurenten.artikel_id = :v_artikel_id "
    "ORDER BY "
      "prijs_concurenten.datum_aankoop DESC ; ";

    qry.prepare(myQuery);
    qry.bindValue(":v_artikel_id", _art_id);
    qry.exec();
    _model->setQuery(qry);
}

void PrijzenConcurentie::deletePrijs(int _id)
{
    QString myQuery;
    QSqlQuery qry;

    myQuery =
    "DELETE FROM artikelbeheer.prijs_concurenten "
    "WHERE "
      "prijs_concurenten.prijs_id = :v_prijs_id; ";

    qry.prepare(myQuery);
    qry.bindValue(":v_prijs_id", _id);
    bool status = qry.exec();
    if (!status)
    {
        qDebug() << "Error bij wissen PrijzenConcurentie record- " << qry.lastError().text();
    }
}
