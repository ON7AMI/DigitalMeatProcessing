#include "bestelheader.h"

#include <QString>
#include <QtCore>
#include <QtSql>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSettings>
#include <QApplication>


//=========================================================
//
// Header leveranciersbestellingen
//
//----------------------------------------------------------
//
// bestel_header_id serial NOT NULL,
// leverancier_id integer,
// opmerking character varying,
// bestel_referentie character varying,
// tijdstip timestamp without time zone,
// bestelling_af boolean,
//
//----------------------------------------------------------
//
//   Properties
//
//----------------------------------------------------------

int BestelHeader::getBestelHeader_ID() { return BestelHeader_ID; }
void BestelHeader::setBestelHeader_ID(int _id) { BestelHeader_ID = _id; }

int BestelHeader::getLeverancier_ID() { return Leverancier_ID; }
void BestelHeader::setLeverancier_ID(int _id) { Leverancier_ID = _id; }

QString BestelHeader::getOpmerking() { return Opmerking; }
void BestelHeader::setOpmerking(QString _opm) { Opmerking = _opm; }

QString BestelHeader::getBestelReferentie() { return BestelReferentie; }
void BestelHeader::setBestelReferentie(QString _ref) { BestelReferentie = _ref; }

QDateTime BestelHeader::getTijdstip() { return Tijdstip;  }
void BestelHeader::setTijdstip(QDateTime _tijd) { Tijdstip = _tijd; }

bool BestelHeader::getBestellingAf() { return BestellingAf; }
void BestelHeader::setBestellingAf(bool _af) { BestellingAf = _af; }



//----------------------------------------------------------
//
//   Constructors
//
//----------------------------------------------------------

BestelHeader::BestelHeader()
{
    clear();
}

BestelHeader::BestelHeader(int _id)
{
    clear();
    BestelHeader_ID = _id;
    read();
}

//-----------------------------------------------------------
//
//   Methodes
//
//-----------------------------------------------------------

void BestelHeader::clear()
{
    BestelHeader_ID = 0;
    Leverancier_ID = 0;
    Opmerking = "";
    BestelReferentie = "";
    Tijdstip = QDateTime::currentDateTime();
    BestellingAf = false;
}

void BestelHeader::read()
{
    QString myQuery;
    QSqlQuery qry;

    myQuery = "SELECT * FROM aankoop.bestel_header WHERE bestel_header_id = :v_bestel_header_id; ";

    qry.prepare(myQuery);
    qry.bindValue(":v_bestel_header_id", BestelHeader_ID);

    if (qry.exec())
    {
        if (qry.next())
        {
            QryRead(&qry);
        }
        else
        {
            BestelHeader_ID = 0;
            qDebug() << "Error bij lezen BestelHeader record (of geen record gevonden)- " << qry.lastError().text();
        }
    }
    else
    {
        BestelHeader_ID = 0;
        qDebug() << "Database error BestelHeader: " << qry.lastError().databaseText() << "\nQuerry error: " << qry.lastError().text();
    }
}

void BestelHeader::QryRead(QSqlQuery *qry)
{
    BestelHeader_ID = qry->value("bestel_header_id").toInt();
    Leverancier_ID = qry->value("leverancier_id").toInt();
    Opmerking = qry->value("opmerking").toString();
    BestelReferentie = qry->value("bestel_referentie").toString();
    Tijdstip = qry->value("tijdstip").toDateTime();
    BestellingAf = qry->value("bestelling_af").toBool();
}

void BestelHeader::save()
{
    QString myQuery;
    QSqlQuery qry;

    if (BestelHeader_ID == 0)
    {
        myQuery =
                "INSERT INTO aankoop.bestel_header ("
                            "leverancier_id, opmerking, bestel_referentie, "
                            "tijdstip, bestelling_af) "
                "VALUES (:v_leverancier_id, :v_opmerking, :v_bestel_referentie, "
                        ":v_tijdstip, :v_bestelling_af );";

        qry.prepare(myQuery);

    }
    else
    {
        myQuery =
                "UPDATE aankoop.bestel_header "
                "SET leverancier_id = :v_leverancier_id, opmerking = :v_opmerking, "
                    "bestel_referentie = :v_bestel_referentie, tijdstip = :v_tijdstip, "
                    "bestelling_af = :v_bestelling_af "
                "WHERE (bestel_header_id = v_bestel_header_id); ";

        qry.prepare(myQuery);
        qry.bindValue(":v_bestel_header_id", BestelHeader_ID);
    }

    qry.bindValue(":v_leverancier_id", Leverancier_ID);
    qry.bindValue(":v_opmerking", Opmerking);
    qry.bindValue(":v_bestel_referentie", BestelReferentie);
    qry.bindValue(":v_tijdstip", Tijdstip);
    qry.bindValue(":v_bestelling_af", BestellingAf);

    if (qry.exec())
    {
        if (BestelHeader_ID == 0)
        {
            BestelHeader_ID = qry.lastInsertId().toInt();
        }
    }
    else
    {
        qDebug() << "Database error BestelHeader: " << qry.lastError().databaseText() << "\nQuerry error: " << qry.lastError().text();
    }
}
