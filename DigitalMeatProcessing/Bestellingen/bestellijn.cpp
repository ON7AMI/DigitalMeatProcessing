#include "bestellijn.h"

#include <QString>
#include <QtCore>
#include <QtSql>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSettings>
#include <QApplication>


//=========================================================
//
// Lijnen leveranciersbestellingen
//
//----------------------------------------------------------
//
// bestellijn_id serial NOT NULL,
// bestel_header_id integer,
// artikel_id integer,
// leverancier_referentie_id integer,
// opmerking character varying,
// hoeveelheid_besteld numeric(20,4),
// hoeveelheid_geleverd numeric(20,4),
// prijs numeric(20,4),
// tijdstip timestamp without time zone,
// bestelling_af boolean,
// tijd_bestelling_af timestamp without time zone,
//
//----------------------------------------------------------
//
//   Properties
//
//----------------------------------------------------------

int BestelLijn::getBestelLijn_ID() { return BestelLijn_ID; }
void BestelLijn::setBestelLijn_ID(int _id) { BestelLijn_ID = _id;}

int BestelLijn::getBestelHeader_ID() { return BestelHeader_ID; }
void BestelLijn::setBestelHeader_ID(int _id) { BestelHeader_ID = _id; }

int BestelLijn::getArtikel_ID() { return Artikel_ID; }
void BestelLijn::setArtikel_ID(int _id) { Artikel_ID = _id; }

int BestelLijn::getLeverancierReferentie_ID() { return LeverancierReferentie_ID; }
void BestelLijn::setLeverancierReferentie_ID(int _id) { LeverancierReferentie_ID = _id; }

QString BestelLijn::getOpmerking() { return Opmerking; }
void BestelLijn::setOpmerking(QString _opm) { Opmerking = _opm; }

double BestelLijn::getHoeveelheidBesteld() { return HoeveelheidBesteld; }
void BestelLijn::setHoeveelheidBesteld(double _hoeveel) { HoeveelheidBesteld = _hoeveel; }

double BestelLijn::getHoeveelheidGeleverd() { return HoeveelheidGeleverd; }
void BestelLijn::setHoeveelheidGeleverd(double _hoeveel) { HoeveelheidGeleverd = _hoeveel; }

double BestelLijn::getPrijs() { return Prijs; }
void BestelLijn::setPrijs(double _prijs) { Prijs = _prijs; }

QDateTime BestelLijn::getTijdstip() { return Tijdstip; }
void BestelLijn::setTijdstip(QDateTime _tijd) { Tijdstip = _tijd; }

bool BestelLijn::getBestellingAf() { return BestellingAf; }
void BestelLijn::setBestellingAf(bool _af) { BestellingAf = _af; }

QDateTime BestelLijn::getTijdBestellingAf() { return TijdBestellingAf; }
void BestelLijn::setTijdBestellingAf(QDateTime _tijd) { TijdBestellingAf = _tijd; }


//----------------------------------------------------------
//
//   Constructors
//
//----------------------------------------------------------

BestelLijn::BestelLijn()
{
    clear();
}

BestelLijn::BestelLijn(int _id)
{
    clear();
    BestelLijn_ID = _id;
    read();
}

//-----------------------------------------------------------
//
//   Methodes
//
//-----------------------------------------------------------

void BestelLijn::clear()
{
    BestelLijn_ID = 0;
    BestelHeader_ID = 0;
    Artikel_ID = 0;
    LeverancierReferentie_ID = 0;
    Opmerking = "";
    HoeveelheidBesteld = 0;
    HoeveelheidGeleverd = 0;
    Prijs = 0;
    Tijdstip = QDateTime::currentDateTime();
    BestellingAf = false;
    TijdBestellingAf = QDateTime::currentDateTime().addYears(100);
}

void BestelLijn::read()
{
    QString myQuery;
    QSqlQuery qry;

    myQuery = "SELECT * FROM aankoop.bestel_line WHERE bestellijn_id = :v_bestelline_id; ";

    qry.prepare(myQuery);
    qry.bindValue(":v_bestelline_id", BestelLijn_ID);

    if (qry.exec())
    {
        if (qry.next())
        {
            QryRead(&qry);
        }
        else
        {
            BestelHeader_ID = 0;
            qDebug() << "Error bij lezen BestelLijn record (of geen record gevonden)- " << qry.lastError().text();
        }
    }
    else
    {
        BestelHeader_ID = 0;
        qDebug() << "Database error BestelLijn: " << qry.lastError().databaseText() << "\nQuerry error: " << qry.lastError().text();
    }
}

void BestelLijn::QryRead(QSqlQuery *qry)
{
    BestelLijn_ID = qry->value("bestellijn_id").toInt();
    BestelHeader_ID = qry->value("bestel_header_id").toInt();
    Artikel_ID = qry->value("artikel_id").toInt();
    LeverancierReferentie_ID = qry->value("leverancier_referentie_id").toInt();
    Opmerking = qry->value("opmerking").toString();
    HoeveelheidBesteld = qry->value("hoeveelheid_besteld").toDouble();
    HoeveelheidGeleverd = qry->value("hoeveelheid_geleverd").toDouble();
    Prijs = qry->value("prijs").toDouble();
    Tijdstip = qry->value("tijdstip").toDateTime();
    BestellingAf = qry->value("bestelling_af").toBool();
    TijdBestellingAf = qry->value("tijd_bestelling_af").toDateTime();
}

void BestelLijn::save()
{
    QString myQuery;
    QSqlQuery qry;

    if (BestelLijn_ID == 0)
    {
        myQuery =
            "INSERT INTO aankoop.bestel_lijn "
                "( bestel_header_id, artikel_id, "
                "leverancier_referentie_id, opmerking, hoeveelheid_besteld, "
                "hoeveelheid_geleverd, prijs, tijdstip, bestelling_af, tijd_bestelling_af) "
            "VALUES (:v_bestel_header_id, :v_artikel_id, "
                ":v_leverancier_referentie_id, :v_opmerking, :v_hoeveelheid_besteld, "
                ":v_hoeveelheid_geleverd, :v_prijs, :v_tijdstip, :v_bestelling_af, "
                ":v_tijd_bestelling_af);";

        qry.prepare(myQuery);

    }
    else
    {
        myQuery =
            "UPDATE aankoop.bestel_lijn "
            "SET bestel_header_id = :v_bestel_header_id, "
                "artikel_id = :v_artikel_id, leverancier_referentie_id = :v_leverancier_referentie_id, "
                "opmerking = :v_opmerking, hoeveelheid_besteld = :v_hoeveelheid_besteld, "
                "hoeveelheid_geleverd = :v_hoeveelheid_geleverd, prijs = :v_prijs, "
                "tijdstip = :v_tijdstip, bestelling_af = :v_bestelling_af, "
                "tijd_bestelling_af = :v_tijd_bestelling_af "
            "WHERE (bestellijn_id = :v_bestellijn_id);";

        qry.prepare(myQuery);
        qry.bindValue(":v_bestellijn_id", BestelLijn_ID);
    }

    qry.bindValue(":v_bestel_header_id", BestelHeader_ID);
    qry.bindValue(":v_artikel_id", Artikel_ID);
    qry.bindValue(":v_leverancier_referentie_id", LeverancierReferentie_ID);
    qry.bindValue(":v_opmerking", Opmerking);
    qry.bindValue(":v_hoeveelheid_besteld", HoeveelheidBesteld);
    qry.bindValue(":v_hoeveelheid_geleverd", HoeveelheidGeleverd);
    qry.bindValue(":v_prijs", Prijs);
    qry.bindValue(":v_tijdstip", Tijdstip);
    qry.bindValue(":v_bestelling_af", BestellingAf);
    qry.bindValue(":v_tijd_bestelling_af", TijdBestellingAf);

    if (qry.exec())
    {
        if (BestelLijn_ID == 0)
        {
            BestelLijn_ID = qry.lastInsertId().toInt();
        }
    }
    else
    {
        qDebug() << "Database error BestelHeader: " << qry.lastError().databaseText() << "\nQuerry error: " << qry.lastError().text();
    }
}
