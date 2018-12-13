#include "leveringenline.h"

#include <QString>
#include <QtCore>
#include <QtSql>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSettings>
#include <QApplication>

// levering_line_id serial NOT NULL,
// levering_header_id integer,
// lev_art_id integer,
// art_id integer,
// artikel_code character varying,
// omschrijving character varying,
// aantal numeric(20,4),
// eenheid integer,
// eenheidsprijs numeric(20,4),
// btw_code integer,
// opmerking character varying,
// create_at timestamp without time zone,
// modify_at timestamp without time zone,
//
//----------------------------------------------------------
//
//   Properties
//
//----------------------------------------------------------

int LeveringenLine::getLeveringLine_ID() { return LeveringLine_ID; }
void LeveringenLine::setLeveringLine_ID(int _id) { LeveringLine_ID = _id; }

int LeveringenLine::getLeveringHeader_ID() { return LeveringHeader_ID; }
void LeveringenLine::setLeveringHeader_ID(int _id) { LeveringHeader_ID = _id; }

int LeveringenLine::getLevArt_ID() { return LevArt_ID; }
void LeveringenLine::setLevArt_ID(int _id) { LevArt_ID = _id; }

int LeveringenLine::getArt_ID() { return Art_ID; }
void LeveringenLine::setArt_ID(int _id) { Art_ID = _id; }

QString LeveringenLine::getArtikelCode() { return ArtikelCode; }
void LeveringenLine::setArtikelCode(QString _code) { ArtikelCode = _code; }

QString LeveringenLine::getArtikelOmschrijving() { return ArtikelOmschrijving; }
void LeveringenLine::setArtikelOmschrijving(QString _oms) { ArtikelOmschrijving = _oms; }

double LeveringenLine::getAantal() { return Aantal; }
void LeveringenLine::setAantal(double _aantal) { Aantal = _aantal; }

int LeveringenLine::getEenheid() { return Eenheid; }
void LeveringenLine::setEenheid(int _eenheid) { Eenheid = _eenheid; }

double LeveringenLine::getEenheidsprijs() { return Eenheidsprijs; }
void LeveringenLine::setEenheidsprijs(double _prijs) { Eenheidsprijs = _prijs; }

int LeveringenLine::getBtwCode() { return BtwCode; }
void LeveringenLine::setBtwCode(int _code)  { BtwCode = _code; }

QString LeveringenLine::getOpmerking() { return Opmerking; }
void LeveringenLine::setOpmerking(QString _opm) { Opmerking = _opm; }

QDateTime LeveringenLine::getCreateAt() { return CreateAt; }
void LeveringenLine::setCreateAt(QDateTime _time) { CreateAt = _time; }

QDateTime LeveringenLine::getModifyAt() { return ModifyAt; }
void LeveringenLine::setModifyAt(QDateTime _time) { ModifyAt = _time; }



//----------------------------------------------------------
//
//   Constructors
//
//----------------------------------------------------------

LeveringenLine::LeveringenLine()
{
    clear();
}

LeveringenLine::LeveringenLine(int _id)
{
    clear();
    LeveringLine_ID = _id;
    read();
}


//-----------------------------------------------------------
//
//   Methodes
//
//-----------------------------------------------------------

void LeveringenLine::clear()
{
    LeveringLine_ID = 0;
    LeveringHeader_ID = 0;
    LevArt_ID = 0;
    Art_ID = 0;
    ArtikelCode = "";
    ArtikelOmschrijving = "";
    Aantal = 0.0;
    Eenheid = 0;
    Eenheidsprijs = 0.0;
    BtwCode = 0;
    Opmerking = "";
    CreateAt = QDateTime::currentDateTime();
    ModifyAt = QDateTime::currentDateTime();

}

void LeveringenLine::read()
{
    QString myQuery;
    QSqlQuery qry;

    myQuery = "SELECT * FROM aankoop.levering_line "
              "WHERE levering_line_id = :v_levering_line_id; ";

    qry.prepare(myQuery);
    qry.bindValue(":v_levering_line_id", LeveringLine_ID);

    if (qry.exec())
    {
        if (qry.next())
        {
            QryRead(&qry);
        }
        else
        {
            LeveringLine_ID = 0;
            qDebug() << "Error bij lezen LeveringLine record (of geen record gevonden)- " << qry.lastError().text();
        }
    }
    else
    {
        LeveringLine_ID = 0;
        qDebug() << "Database error LeveringLine: " << qry.lastError().databaseText() << "\nQuerry error: " << qry.lastError().text();
    }
}

void LeveringenLine::QryRead(QSqlQuery *qry)
{
    LeveringLine_ID = qry->value("levering_line_id").toInt();
    LeveringHeader_ID = qry->value("levering_header_id").toInt();
    LevArt_ID = qry->value("lev_art_id").toInt();
    Art_ID = qry->value("art_id").toInt();
    ArtikelCode = qry->value("artikel_code").toString();
    ArtikelOmschrijving = qry->value("omschrijving").toString();
    Aantal = qry->value("aantal").toDouble();
    Eenheid = qry->value("eenheid").toInt();
    Eenheidsprijs = qry->value("eenheidsprijs").toDouble();
    BtwCode = qry->value("btw_code").toInt();
    Opmerking = qry->value("opmerking").toString();
    CreateAt = qry->value("create_at").toDateTime();
    ModifyAt = qry->value("modify_at").toDateTime();
}

void LeveringenLine::save()
{
    QString myQuery;
    QSqlQuery qry;

    if (LeveringLine_ID == 0)
    {
        myQuery =
                "INSERT INTO aankoop.levering_line( "
                            "levering_header_id, "
                            "lev_art_id, "
                            "art_id, "
                            "artikel_code, "
                            "omschrijving, "
                            "aantal, "
                            "eenheid, "
                            "eenheidsprijs, "
                            "btw_code, "
                            "opmerking, "
                            "create_at, "
                            "modify_at) "
                    "VALUES (:v_levering_header_id, "
                            ":v_lev_art_id, "
                            ":v_art_id, "
                            ":v_artikel_code, "
                            ":v_omschrijving, "
                            ":v_aantal, "
                            ":v_eenheid, "
                            ":v_eenheidsprijs, "
                            ":v_btw_code, "
                            ":v_opmerking,  "
                            ":v_create_at, "
                            ":v_modify_at); ";

        qry.prepare(myQuery);
        qry.bindValue(":v_create_at", QDateTime::currentDateTime());
        qry.bindValue(":v_modify_at", QDateTime::currentDateTime());
    }
    else
    {
        myQuery =
                "UPDATE  aankoop.levering_line "
                   "SET  levering_header_id = :v_levering_header_id, "
                        "lev_art_id = :v_lev_art_id, "
                        "art_id = :v_art_id, "
                        "artikel_code = :v_artikel_code, "
                        "omschrijving = :v_omschrijving, "
                        "aantal = :v_aantal, "
                        "eenheid = :v_eenheid, "
                        "eenheidsprijs = :v_eenheidsprijs, "
                        "btw_code = :v_btw_code, "
                        "opmerking = :v_opmerking, "
                        "modify_at = :v_modify_at "
                 "WHERE (levering_line_id = :v_levering_line_id);";

        qry.prepare(myQuery);
        qry.bindValue(":v_levering_line_id", LeveringLine_ID);
        qry.bindValue(":v_modify_at", QDateTime::currentDateTime());
    }

    qry.bindValue(":v_levering_header_id",LeveringHeader_ID);
    qry.bindValue(":v_lev_art_id",LevArt_ID);
    qry.bindValue(":v_art_id",Art_ID);
    qry.bindValue(":v_artikel_code",ArtikelCode);
    qry.bindValue(":v_omschrijving",ArtikelOmschrijving);
    qry.bindValue(":v_aantal",Aantal);
    qry.bindValue(":v_eenheid",Eenheid);
    qry.bindValue(":v_eenheidsprijs",Eenheidsprijs);
    qry.bindValue(":v_btw_code",BtwCode);
    qry.bindValue(":v_opmerking",Opmerking);

    if (qry.exec())
    {
        if (LeveringLine_ID == 0)
        {
            LeveringLine_ID = qry.lastInsertId().toInt();
        }
    }
    else
    {
        qDebug() << "Database error LeveringLine: " << qry.lastError().databaseText() << "\nQuerry error: " << qry.lastError().text();
    }
}

void LeveringenLine::wis()
{
    QString myQuery;
    QSqlQuery qry;

    myQuery = "DELETE FROM aankoop.levering_line "
              "WHERE levering_line_id = :v_levering_line_id ; ";

    qry.prepare(myQuery);
    qry.bindValue(":v_levering_line_id", LeveringLine_ID);

    if (! qry.exec())
    {
        LeveringLine_ID = 0;
        qDebug() << "Error deleting Leverlijn: " << qry.lastError().databaseText() << "\nQuerry deleting error: " << qry.lastError().text();
    }
}

//-----------------------------------------------------------
//
//   Static Methodes
//
//-----------------------------------------------------------

void LeveringenLine::getLeveringLijnen(QSqlQueryModel* _model, int Lev_ID )
{
    QString myQuery =
            "SELECT l.levering_line_id as ID, r.leverancier_referentie as LevRef, "
                   "r.referentie_omschrijving as Lev_Omschr, "
                   "l.artikel_code as Code, "
                   "l.omschrijving as Omschrijving, l.aantal as Aantal, e.eenheids_code as Eenh, "
                   "l.eenheidsprijs as E_Prijs, "
                   "b.tarief as BTW, l.opmerking as Opmerking "
              "FROM aankoop.levering_line as l "
                   "LEFT JOIN aankoop.leverancier_referenties as r "
                        "ON r.leverancier_referentie_id = l.lev_art_id  "
                   "LEFT JOIN artikelbeheer.com_eenheden as e "
                        "ON e.eenheids_id = l.eenheid  "
                   "LEFT JOIN common.btw_tarieven as b "
                        "ON b.btwtarief_id = l.btw_code "
              "Where l.levering_header_id = :v_lev_id; ";
    QSqlQuery qry;
    qry.prepare(myQuery);
    qry.bindValue(":v_lev_id", Lev_ID);

    if (qry.exec())
    {
        _model->setQuery(qry);
        _model->query();
    }
    else
    {
        _model = 0;
        qDebug() << "Database error LeveringLijnen op Levering_ID: " << qry.lastError().databaseText() << "\nQuerry error: " << qry.lastError().text();
    }

}

void LeveringenLine::getLeverStatistiek(QSqlQueryModel* LeverStat, int _id)
{
    QString myQuery =
        "SELECT max(eenheidsprijs) as max_prijs, min(eenheidsprijs) as min_prijs, avg(eenheidsprijs) as gem_prijs , "
          "(select eenheidsprijs "
           "FROM aankoop.levering_line as l "
           "LEFT JOIN aankoop.levering_header AS h ON l.levering_header_id = h.levering_header_id "
           "WHERE art_id = :v_art_id "
           "order by h.tijdstip DESC "
           "LIMIT 1) as huidige_prijs "
          "FROM aankoop.levering_line "
          "WHERE art_id = :v_art_id; ";

    QSqlQuery qry;
    qry.prepare(myQuery);
    qry.bindValue(":v_art_id", _id);

    if (qry.exec())
    {
        LeverStat->setQuery(qry);
        LeverStat->query();
    }
    else
    {
        LeverStat = 0;
        qDebug() << "Database error LeveringLijnen op Levering_ID: " << qry.lastError().databaseText() << "\nQuerry error: " << qry.lastError().text();
    }

}
