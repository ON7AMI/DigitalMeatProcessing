#include "leveringenheader.h"

#include <QString>
#include <QtCore>
#include <QtSql>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSettings>
#include <QApplication>

//    levering_header_id serial NOT NULL,
//    leverancier_id integer,
//    opmerking character varying,
//    leverancier_referentie character varying,
//    onze_referentie character varying,
//    leverancier_factuur character varying,
//    onze_factuur character varying,
//    tijdstip date,
//    create_at timestamp without time zone,
//    modify_at timestamp without time zone,
//
//----------------------------------------------------------
//
//   Properties
//
//----------------------------------------------------------

int LeveringenHeader::getLeveringenHeader_ID() { return LeveringenHeader_ID; }
void LeveringenHeader::setLeveringenHeader_ID(int _id) { LeveringenHeader_ID = _id; }

int LeveringenHeader::getLeverancier_ID() { return Leverancier_ID; }
void LeveringenHeader::setLeverancier_ID(int _id) { Leverancier_ID = _id; }

QString LeveringenHeader::getOpmerkingen() { return Opmerkingen; }
void LeveringenHeader::setOpmerkingen(QString _opm) { Opmerkingen = _opm; }

QString LeveringenHeader::getLeverancierReferentie() { return LeverancierReferentie; }
void LeveringenHeader::setLeverancierReferentie(QString _levref) { LeverancierReferentie = _levref; }

QString LeveringenHeader::getOnzeReferentie() { return OnzeReferentie; }
void LeveringenHeader::setOnzeReferentie(QString _oref) { OnzeReferentie = _oref; }

QString LeveringenHeader::getLeverancierFactuur() { return LeverancierFactuur; }
void LeveringenHeader::setLeverancierFactuur(QString _levfact) { LeverancierFactuur = _levfact; }

QString LeveringenHeader::getOnzeFactuur() { return OnzeFactuur; }
void LeveringenHeader::setOnzeFactuur(QString _ofact) { OnzeFactuur = _ofact; }

QDate LeveringenHeader::getTijdstip() { return Tijdstip; }
void LeveringenHeader::setTijdstip(QDate _tijdstip) { Tijdstip = _tijdstip; }

QDateTime LeveringenHeader::getCreatedAt() { return CreatedAt; }
void LeveringenHeader::setCreatedAt(QDateTime _createat) { CreatedAt = _createat; }

QDateTime LeveringenHeader::getModifyAt() { return ModifyAt; }
void LeveringenHeader::setModifyAt(QDateTime _modifyat) { ModifyAt = _modifyat; }


//----------------------------------------------------------
//
//   Constructors
//
//----------------------------------------------------------


LeveringenHeader::LeveringenHeader()
{
    clear();
}

LeveringenHeader::LeveringenHeader(int _id)
{
    clear();
    LeveringenHeader_ID = _id;
    read();
}

//-----------------------------------------------------------
//
//   Methodes
//
//-----------------------------------------------------------

void LeveringenHeader::clear()
{
    LeveringenHeader_ID = 0;
    Leverancier_ID = 0;
    Opmerkingen = "";
    LeverancierReferentie = "";
    OnzeReferentie = "";
    LeverancierFactuur = "";
    OnzeFactuur = "";
    Tijdstip = QDate::currentDate();
    CreatedAt = QDateTime::currentDateTime();
    ModifyAt = QDateTime::currentDateTime();

}

void LeveringenHeader::read()
{
    QString myQuery;
    QSqlQuery qry;

    myQuery = "SELECT * FROM aankoop.levering_header "
              "WHERE levering_header_id = :v_levering_header_id; ";

    qry.prepare(myQuery);
    qry.bindValue(":v_levering_header_id", LeveringenHeader_ID);

    if (qry.exec())
    {
        if (qry.next())
        {
            QryRead(&qry);
        }
        else
        {
            LeveringenHeader_ID = 0;
            qDebug() << "Error bij lezen LeveringenHeader record (of geen record gevonden)- " << qry.lastError().text();
        }
    }
    else
    {
        LeveringenHeader_ID = 0;
        qDebug() << "Database error LeveringenHeader: " << qry.lastError().databaseText() << "\nQuerry error: " << qry.lastError().text();
    }
}

void LeveringenHeader::QryRead(QSqlQuery *qry)
{
    LeveringenHeader_ID = qry->value("levering_header_id").toInt();
    Leverancier_ID = qry->value("leverancier_id").toInt();
    Opmerkingen = qry->value("opmerking").toString();
    LeverancierReferentie = qry->value("leverancier_referentie").toString();
    OnzeReferentie = qry->value("onze_referentie").toString();
    LeverancierFactuur = qry->value("leverancier_factuur").toString();
    OnzeFactuur = qry->value("onze_factuur").toString();
    Tijdstip = qry->value("tijdstip").toDate();
    CreatedAt = qry->value("create_at").toDateTime();
    ModifyAt = qry->value("modify_at").toDateTime();
}

void LeveringenHeader::save()
{
    QString myQuery;
    QSqlQuery qry;

    if (LeveringenHeader_ID == 0)
    {
        myQuery =
                "INSERT INTO aankoop.levering_header( "
                            "leverancier_id, opmerking, leverancier_referentie, "
                            "onze_referentie, leverancier_factuur, onze_factuur, tijdstip, "
                            "create_at, modify_at) "
                "VALUES (:v_leverancier_id, :v_opmerking, :v_leverancier_referentie, "
                        ":v_onze_referentie, :v_leverancier_factuur, :v_onze_factuur, :v_tijdstip, "
                        ":v_create_at, :v_modify_at); ";

        qry.prepare(myQuery);
        qry.bindValue(":v_create_at", QDateTime::currentDateTime());
        qry.bindValue(":v_modify_at", QDateTime::currentDateTime());
    }
    else
    {
        myQuery =
                "UPDATE aankoop.levering_header "
                "SET leverancier_id = :v_leverancier_id, "
                    "opmerking = :v_opmerking, "
                    "leverancier_referentie = :v_leverancier_referentie, "
                    "onze_referentie = :v_onze_referentie, "
                    "leverancier_factuur = :v_leverancier_factuur, "
                    "onze_factuur = :v_onze_factuur, "
                    "tijdstip = :v_tijdstip, "
                    "modify_at = :v_modify_at "
                "WHERE (levering_header_id = :v_levering_header_id);";

        qry.prepare(myQuery);
        qry.bindValue(":v_levering_header_id", LeveringenHeader_ID);
        qry.bindValue(":v_modify_at", QDateTime::currentDateTime());
    }

    qry.bindValue(":v_leverancier_id",Leverancier_ID);
    qry.bindValue(":v_opmerking",Opmerkingen);
    qry.bindValue(":v_leverancier_referentie",LeverancierReferentie);
    qry.bindValue(":v_onze_referentie",OnzeReferentie);
    qry.bindValue(":v_leverancier_factuur",LeverancierFactuur);
    qry.bindValue(":v_onze_factuur",OnzeFactuur);
    qry.bindValue(":v_tijdstip",Tijdstip);

    if (qry.exec())
    {
        if (LeveringenHeader_ID == 0)
        {
            LeveringenHeader_ID = qry.lastInsertId().toInt();
        }
    }
    else
    {
        qDebug() << "Database error LeveringHeader: " << qry.lastError().databaseText() << "\nQuerry error: " << qry.lastError().text();
    }
}


//-----------------------------------------------------------
//
//   Static Methodes
//
//-----------------------------------------------------------


void LeveringenHeader::getLaatsteLeveringen(QSqlQueryModel* _model, int Lev_ID, QDate StartDatum, QDate EindDatum)
{
    QString myQuery =
            "SELECT l.levering_header_id as id, "
                    "l.tijdstip as datum, "
                    "r.naam as naam, "
                    "l.leverancier_referentie as referentie, "
                    "l.leverancier_factuur as factuur, "
                    "l.opmerking as opmerking "
            "FROM aankoop.levering_header as l, "
                 "relaties.relaties as r "
            "WHERE l.leverancier_id = r.relatie_id "
              "AND l.tijdstip >= :v_van "
              "AND l.tijdstip <= :v_tot "
              "AND (l.leverancier_id = :v_lev_id OR :v_lev_id = 0) "
            "ORDER BY tijdstip DESC "
            "LIMIT 100;";
    QSqlQuery qry;
    qry.prepare(myQuery);
    qry.bindValue(":v_lev_id", Lev_ID);
    qry.bindValue(":v_van", StartDatum);
    qry.bindValue(":v_tot", EindDatum);

    if (qry.exec())
    {
        _model->setQuery(qry);
        _model->query();
    }
    else
    {
        _model = 0;
        qDebug() << "Database error Leveringkeuzelijst op datum: " << qry.lastError().databaseText() << "\nQuerry error: " << qry.lastError().text();
    }

}
