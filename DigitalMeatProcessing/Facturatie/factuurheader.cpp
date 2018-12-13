#include "factuurheader.h"


#include <QString>
#include <QtCore>
#include <QtSql>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSettings>
#include <QApplication>


//=========================================================
//
// Factuurhoofding
//
//----------------------------------------------------------
//
// factuur_id serial NOT NULL,
// tijdstip timestamp without time zone,
// volgnummer integer,
// klant_id integer,
// klant_naam character varying,
// klant_adres character varying,
// klant_postcode character varying,
// klant_gemeente character varying,
// klant_land character varying,
// korting_bedrag numeric(20,4),
// printed boolean DEFAULT false,
//
//----------------------------------------------------------
//
//   Properties
//
//----------------------------------------------------------

int FactuurHeader::getFactuur_ID() { return Factuur_ID; }
void FactuurHeader::setFactuur_ID( int _id ) { Factuur_ID = _id; }

QDate FactuurHeader::getTijdstip() { return Tijdstip; }
void FactuurHeader::setTijdstip( QDate _tijd ) { Tijdstip = _tijd; }

int FactuurHeader::getVolgnummer() { return Volgnummer; }
void FactuurHeader::setVolgnummer( int _volgnr ) { Volgnummer = _volgnr; }

int FactuurHeader::getKlant_ID() { return Klant_ID; }
void FactuurHeader::setKlant_ID( int _id ) { Klant_ID = _id; }

QString FactuurHeader::getKlantNaam() { return KlantNaam; }
void FactuurHeader::setKlantNaam( QString _naam ) { KlantNaam = _naam; }

QString FactuurHeader::getKlantAdres() { return KlantAdres; }
void FactuurHeader::setKlantAdres( QString _adres ) { KlantAdres = _adres; }

QString FactuurHeader::getKlantPostcode() { return KlantPostcode; }
void FactuurHeader::setKlantPostcode( QString _code ) { KlantPostcode = _code; }

QString FactuurHeader::getKlantGemeente() { return KlantGemeente; }
void FactuurHeader::setKlantGemeente( QString _gem ) { KlantGemeente = _gem; }

QString FactuurHeader::getKlantLand() { return KlantLand; }
void FactuurHeader::setKlantLand( QString _land ) { KlantLand = _land; }

double FactuurHeader::getKortingBedrag() { return KortingBedrag; }
void FactuurHeader::setKortingBedrag( double _bedr ) { KortingBedrag = _bedr; }

bool FactuurHeader::getPrinted() { return Printed; }
void FactuurHeader::setPrinted( bool _printed ) { Printed = _printed; }


//----------------------------------------------------------
//
//   Constructors
//
//----------------------------------------------------------

FactuurHeader::FactuurHeader()
{
    clear();
}

FactuurHeader::FactuurHeader(int _id)
{
    clear();
    Factuur_ID = _id;
    read();
}


//-----------------------------------------------------------
//
//   Methodes
//
//-----------------------------------------------------------

void FactuurHeader::clear()
{
    Factuur_ID = 0;
    Tijdstip = QDate::currentDate();
    Volgnummer = 0;
    Klant_ID = 0;
    KlantNaam = "";
    KlantAdres = "";
    KlantPostcode = "";
    KlantGemeente = "";
    KlantLand = "";
    KortingBedrag = 0.0;
    Printed = false;
}


void FactuurHeader::read()
{
    QString myQuery;
    QSqlQuery qry;

    myQuery = "SELECT * FROM verkoop.factuur_header WHERE factuur_id = :v_factuur_id; ";

    qry.prepare(myQuery);
    qry.bindValue(":v_factuur_id", Factuur_ID);

    if (qry.exec())
    {
        if (qry.next())
        {
            QryRead(&qry);
        }
        else
        {
            Factuur_ID = 0;
            qDebug() << "Error bij lezen FactuurHeader record (of geen record gevonden)- " << qry.lastError().text();
        }
    }
    else
    {
        Factuur_ID = 0;
        qDebug() << "Database error FactuurHeader: " << qry.lastError().databaseText() << "\nQuerry error: " << qry.lastError().text();
    }
}

void FactuurHeader::QryRead(QSqlQuery *qry)
{
    Factuur_ID = qry->value("factuur_id").toInt();
    Tijdstip = qry->value("tijdstip").toDate();
    Volgnummer = qry->value("volgnummer").toInt();
    Klant_ID = qry->value("klant_id").toInt();
    KlantNaam = qry->value("klant_naam").toString();
    KlantAdres = qry->value("klant_adres").toString();
    KlantPostcode = qry->value("klant_postcode").toString();
    KlantGemeente = qry->value("klant_gemeente").toString();
    KlantLand = qry->value("klant_land").toString();
    KortingBedrag = qry->value("korting_bedrag").toDouble();
    Printed = qry->value("printed").toBool();
}

void FactuurHeader::save()
{
    QString myQuery;
    QSqlQuery qry;

    if (Factuur_ID == 0)
    {
        myQuery =
                "INSERT INTO verkoop.factuur_header( "
                    "tijdstip, volgnummer, klant_id, klant_naam, klant_adres, "
                    "klant_postcode, klant_gemeente, klant_land, korting_bedrag, printed) "
                "VALUES ("
                    ":v_tijdstip, :v_volgnummer, :v_klant_id, :v_klant_naam, :v_klant_adres, "
                    ":v_klant_postcode, :v_klant_gemeente, :v_klant_land, :v_korting_bedrag, :v_printed);";

        qry.prepare(myQuery);
        Volgnummer = getLastFactuurNummer()+1;
        qry.bindValue(":v_volgnummer",Volgnummer);

    }
    else
    {
        myQuery =
                "UPDATE verkoop.factuur_header "
                "SET tijdstip = :v_tijdstip, volgnummer = :v_volgnummer, "
                    "klant_id = :v_klant_id, klant_naam = :v_klant_naam, "
                    "klant_adres = :v_klant_adres, klant_postcode = :v_klant_postcode, "
                    "klant_gemeente = :v_klant_gemeente, klant_land = :v_klant_land, "
                    "korting_bedrag = :v_korting_bedrag, printed = :v_printed "
                "WHERE (factuur_id = :v_factuur_id);";

        qry.prepare(myQuery);
        qry.bindValue(":v_factuur_id", Factuur_ID);
        qry.bindValue(":v_volgnummer",Volgnummer);
    }

    qry.bindValue(":v_tijdstip",Tijdstip);
    qry.bindValue(":v_klant_id",Klant_ID);
    qry.bindValue(":v_klant_naam",KlantNaam);
    qry.bindValue(":v_klant_adres",KlantAdres);
    qry.bindValue(":v_klant_postcode",KlantPostcode);
    qry.bindValue(":v_klant_gemeente",KlantGemeente);
    qry.bindValue(":v_klant_land",KlantLand);
    qry.bindValue(":v_korting_bedrag",KortingBedrag);
    qry.bindValue(":v_printed",Printed);

    if (qry.exec())
    {
        if (Factuur_ID == 0)
        {
            Factuur_ID = qry.lastInsertId().toInt();
        }
    }
    else
    {
        qDebug() << "Database error FactuurHeader: " << qry.lastError().databaseText() << "\nQuerry error: " << qry.lastError().text();
    }
}


//====================================================================================================
//   Static Methods
//


int FactuurHeader::getLastFactuurNummer()
{
    int last = 0;
    QString myQuery;
    QSqlQuery qry;

    myQuery = "SELECT max(volgnummer) as last FROM verkoop.factuur_header WHERE EXTRACT(YEAR FROM tijdstip) = :v_jaar; ";

    qry.prepare(myQuery);
    qry.bindValue(":v_jaar",QDate::currentDate().year());

    if (qry.exec())
    {
        if (qry.next())
        {
            last = qry.value("last").toInt();
        }
        else
        {
            last = 0;
            qDebug() << "Error bij lezen laatste factuurnummer record (of geen record gevonden)- " << qry.lastError().text();
        }
    }
    else
    {
        last = 0;
        qDebug() << "Database error laatsqte factuurnummer: " << qry.lastError().databaseText() << "\nQuerry error: " << qry.lastError().text();
    }
    return last;
}

void FactuurHeader::getLaatsteFacturen(QSqlQueryModel* _model)
{
    QString myQuery =
            "SELECT factuur_id as id, date_part('year',tijdstip) as jaar, volgnummer as nummer, date(tijdstip) as datum, "
                    "klant_naam as naam "
            "FROM verkoop.factuur_header "
            "ORDER BY factuur_id DESC "
            "LIMIT 100;";
    QSqlQuery qry;
    qry.prepare(myQuery);

    qry.exec();
    _model->setQuery(qry);
    _model->query();

}

void FactuurHeader::getLaatsteFacturen(QSqlQueryModel* _model, int _num)
{
    QString myQuery =
            "SELECT factuur_id as id, date_part('year',tijdstip) as jaar, volgnummer as nummer, date(tijdstip) as datum, "
                    "klant_naam as naam "
            "FROM verkoop.factuur_header "
            "WHERE volgnummer = :v_num "
            "ORDER BY factuur_id DESC "
            "LIMIT 100;";
    QSqlQuery qry;
    qry.prepare(myQuery);
    qry.bindValue(":v_num",_num);

    if (qry.exec())
    {
        _model->setQuery(qry);
        _model->query();
    }
    else
    {
        _model = 0;
        qDebug() << "Database error factuurkeuzelijst op factuurnummer: " << qry.lastError().databaseText() << "\nQuerry error: " << qry.lastError().text();
    }

}
