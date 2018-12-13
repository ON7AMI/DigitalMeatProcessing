#include "lotnummerdata.h"

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
// lotnummer_id serial NOT NULL,
// lotnummer character varying,
// opmerkingen character varying,
// datum_instock date,
// datum_eig_tgv date,
// datum_uitstock date,
// actief boolean,
// artikel_id integer,
// hoeveelheid_in numeric(20,4),
// hoeveelheid_uit numeric(20,4),
// hoeveelheid_afval numeric(20,4),
// houdbaarheid integer,
// verpakking character varying,
// recept_productie integer,
// lev_id integer,
// lev_lotnr character varying,
// lev_slachthuis character varying,
// lev_sanitel character varying,
// lev_prod_datum date,
// lev_tgv date,
// lev_document character varying,
// lev_regel character varying,
// locatie_id int

int LotnummerData::getLotnummer_id() { return Lotnummer_id; }
void LotnummerData::setLotnummer_id(int _id) { Lotnummer_id = _id; }

QString LotnummerData::getLotnummer() { return Lotnummer; }
void LotnummerData::setLotnummer(QString _lotnr) { Lotnummer = _lotnr; }

QString LotnummerData::getOpmerkingen() { return Opmerkingen; }
void LotnummerData::setOpmerkingen(QString _opm) { Opmerkingen = _opm; }

QDate LotnummerData::getDatumInstock() { return DatumInstock; }
void LotnummerData::setDatumInstock(QDate _in) { DatumInstock = _in; }

QDate LotnummerData::getDatumEigTgv() { return DatumEigTgv; }
void LotnummerData::setDatumEigTgv(QDate _tgv) { DatumEigTgv = _tgv; }

QDate LotnummerData::getDatumUitstock() { return DatumUitstock; }
void LotnummerData::setDatumUitstock(QDate _uit) { DatumUitstock = _uit; }

bool LotnummerData::getActief() { return Actief; }
void LotnummerData::setActief(bool _actief) { Actief = _actief; }

int LotnummerData::getArtikel_ID() { return Artikel_ID; }
void LotnummerData::setArtikel_ID(int _id) { Artikel_ID = _id; }

double LotnummerData::getHoeveelheidIn() { return HoeveelheidIn; }
void LotnummerData::setHoeveelheidIn(double _in) { HoeveelheidIn = _in; }

double LotnummerData::getHoeveelheidUit() { return HoeveelheidUit; }
void LotnummerData::setHoeveelheidUit(double _uit) { HoeveelheidUit = _uit; }

double LotnummerData::getHoeveelheidAfval() { return HoeveelheidAfval; }
void LotnummerData::setHoeveelheidAfval(double _afval) { HoeveelheidAfval = _afval; }

int LotnummerData::getHoudbaarheid() { return Houdbaarheid; }
void LotnummerData::setHoudbaarheid(int _houd) { Houdbaarheid = _houd; }

QString LotnummerData::getVerpakking() { return Verpakking; }
void LotnummerData::setVerpakking(QString _verp) { Verpakking = _verp; }

int LotnummerData::getReceptProductie() { return ReceptProductie; }
void LotnummerData::setReceptProductie(int _recept) { ReceptProductie = _recept; }

int LotnummerData::getLev_ID() { return Lev_ID; }
void LotnummerData::setLev_ID(int _lev) { Lev_ID = _lev; }

QString LotnummerData::getLevLotnr() { return LevLotnr; }
void LotnummerData::setLevLotnr(QString _lotnr) { LevLotnr = _lotnr; }

QString LotnummerData::getLevSlachthuis() { return LevSlachthuis; }
void LotnummerData::setLevSlachthuis(QString _slachthuis) { LevSlachthuis = _slachthuis; }

QString LotnummerData::getLevSanitel() { return LevSanitel; }
void LotnummerData::setLevSanitel(QString _sanitel) { LevSanitel = _sanitel; }

QDate LotnummerData::getLevProdDatum() { return LevProdDatum; }
void LotnummerData::setLevProdDatum(QDate _dat) { LevProdDatum = _dat; }

QDate LotnummerData::getLevTgv() { return LevTgv; }
void LotnummerData::setLevTgv(QDate _tgv) { LevTgv = _tgv; }

QString LotnummerData::getLevDocument() { return LevDocument; }
void LotnummerData::setLevDocument(QString _doc) { LevDocument = _doc; }

QString LotnummerData::getLevRegel() { return LevRegel; }
void LotnummerData::setLevRegel(QString _reg) { LevRegel = _reg; }

int LotnummerData::getLocatie_ID() { return Locatie_ID; }
void LotnummerData::setLocatie_ID( int _id ) { Locatie_ID = _id; }

QDateTime LotnummerData::getLocatieVeranderdOp() { return LocatieVeranderdOp; }
void LotnummerData::setLocatieVeranderdOp(QDateTime _nu) { LocatieVeranderdOp = _nu; }

//================================================================================================
//  Constructors
//


LotnummerData::LotnummerData()
{
    clear();
}

LotnummerData::LotnummerData(int _id)
{
   Lotnummer_id = _id;
   read();
}

LotnummerData::LotnummerData(QString _lotnr)
{
    read(_lotnr);
}



//=================================================================================================
//  Methods
//

void LotnummerData::clear()
{
    Lotnummer_id = 0;
    Lotnummer = "";
    Opmerkingen = "";
    DatumInstock = QDate::currentDate();
    DatumEigTgv = QDate::currentDate();
    DatumUitstock = QDate::currentDate();
    Actief = true;
    Artikel_ID = 0;
    HoeveelheidIn = 0;
    HoeveelheidUit = 0;
    HoeveelheidAfval = 0;
    Houdbaarheid = 0;
    Verpakking = "";
    ReceptProductie = 0;
    Lev_ID = 0;
    LevLotnr = "";
    LevSlachthuis = "";
    LevSanitel = "";
    LevProdDatum = QDate::currentDate();
    LevTgv = QDate::currentDate();
    LevDocument = "";
    LevRegel = "";
    Locatie_ID = 0;
    LocatieVeranderdOp = QDateTime::currentDateTime();
}

void LotnummerData::read()
{
    QString myQuery;
    QSqlQuery qry;
    bool status;

    myQuery = "SELECT * FROM productie.lotnummerdata WHERE lotnummer_id = :v_lotnummer_id; ";

    qry.prepare(myQuery);
    qry.bindValue(":v_lotnummer_id", Lotnummer_id);
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
            Lotnummer_id = 0;
            qDebug() << "Error bij lezen Lotnummer record (of geen record gevonden)- " << qry.lastError().text();
        }
    }
    else
    {
        Lotnummer_id = 0;
        qDebug() << "Database error lotnummers: " << qry.lastError().databaseText() << "\nQuerry error: " << qry.lastError().text();
    }

}

void LotnummerData::read(QString _lotnr)
{
    QString myQuery;
    QSqlQuery qry;
    bool status;

    myQuery = "SELECT * FROM productie.lotnummerdata WHERE lotnummer = :v_lotnummer; ";

    qry.prepare(myQuery);
    qry.bindValue(":v_lotnummer", _lotnr);

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
            Lotnummer_id = 0;
            qDebug() << "Error bij lezen Lotnummer record (of geen record gevonden)- " << qry.lastError().text();
        }
    }
    else
    {
        Lotnummer_id = 0;
        qDebug() << "Database error lotnummers: " << qry.lastError().databaseText() << "\nQuerry error: " << qry.lastError().text();
    }

}


void LotnummerData::QryRead(QSqlQuery* qry)
{
    Lotnummer_id = qry->value("lotnummer_id").toInt();
    Lotnummer = qry->value("lotnummer").toString();
    Opmerkingen = qry->value("opmerkingen").toString();
    DatumInstock = qry->value("datum_instock").toDate();
    DatumEigTgv = qry->value("datum_eig_tgv").toDate();
    DatumUitstock = qry->value("datum_uitstock").toDate();
    Actief = qry->value("actief").toBool();
    Artikel_ID = qry->value("artikel_id").toInt();
    HoeveelheidIn = qry->value("hoeveelheid_in").toDouble();
    HoeveelheidUit = qry->value("hoeveelheid_uit").toDouble();
    HoeveelheidAfval = qry->value("hoeveelheid_afval").toDouble();
    Houdbaarheid = qry->value("houdbaarheid").toInt();
    Verpakking = qry->value("verpakking").toString();
    ReceptProductie = qry->value("recept_productie").toInt();
    Lev_ID = qry->value("lev_id").toInt();
    LevLotnr = qry->value("lev_lotnr").toString();
    LevSlachthuis = qry->value("lev_slachthuis").toString();
    LevSanitel = qry->value("lev_sanitel").toString();
    LevProdDatum = qry->value("lev_prod_datum").toDate();
    LevTgv = qry->value("lev_tgv").toDate();
    LevDocument = qry->value("lev_document").toString();
    LevRegel = qry->value("lev_regel").toString();
    Locatie_ID = qry->value("locatie_id").toInt();
    LocatieVeranderdOp = qry->value("locatie_veranderd_op").toDateTime();
}

void LotnummerData::save()
{
    QString myQuery;
    QSqlQuery qry;

    if (Lotnummer_id == 0)
    {
        myQuery =
        "INSERT INTO productie.lotnummerdata( "
                "lotnummer, opmerkingen, datum_instock, datum_eig_tgv, "
                "datum_uitstock, actief, artikel_id, hoeveelheid_in, hoeveelheid_uit, "
                "hoeveelheid_afval, houdbaarheid, verpakking, recept_productie, "
                "lev_id, lev_lotnr, lev_slachthuis, lev_sanitel, lev_prod_datum, "
                "lev_tgv, lev_document, lev_regel, locatie_id, locatie_veranderd_op) "
        "VALUES (:v_lotnummer, :v_opmerkingen, :v_datum_instock, :v_datum_eig_tgv, "
                ":v_datum_uitstock, :v_actief, :v_artikel_id, :v_hoeveelheid_in, :v_hoeveelheid_uit, "
                ":v_hoeveelheid_afval, :v_houdbaarheid, :v_verpakking, :v_recept_productie, "
                ":v_lev_id, :v_lev_lotnr, :v_lev_slachthuis, :v_lev_sanitel, :v_lev_prod_datum, "
                ":v_lev_tgv, :v_lev_document, :v_lev_regel, :v_locatie_id, :v_locatie_veranderd_op); ";


        qry.prepare(myQuery);

    }
    else
    {
        myQuery =
                "UPDATE productie.lotnummerdata "
                "SET lotnummer = :v_lotnummer, "
                    "opmerkingen = :v_opmerkingen, datum_instock = :v_datum_instock, "
                    "datum_eig_tgv = :v_datum_eig_tgv, datum_uitstock = :v_datum_uitstock, "
                    "actief = :v_actief, artikel_id = :v_artikel_id, hoeveelheid_in = :v_hoeveelheid_in, "
                    "hoeveelheid_uit = :v_hoeveelheid_uit, hoeveelheid_afval = :v_hoeveelheid_afval, "
                    "houdbaarheid = :v_houdbaarheid, verpakking = :v_verpakking, "
                    "recept_productie = recept_productie, lev_id = :v_lev_id, lev_lotnr = :v_lev_lotnr, "
                    "lev_slachthuis = :v_lev_slachthuis, "
                    "lev_sanitel = :v_lev_sanitel, lev_prod_datum = :v_lev_prod_datum, "
                    "lev_tgv = :v_lev_tgv, lev_document = :v_lev_document, lev_regel = :v_lev_regel, "
                    "locatie_id = :v_locatie_id, locatie_veranderd_op=:v_locatie_veranderd_op "
                 "WHERE (lotnummer_id = :v_lotnummer_id); ";


        qry.prepare(myQuery);
        qry.bindValue(":v_lotnummer_id", Lotnummer_id);
    }

    qry.bindValue(":v_lotnummer", Lotnummer);
    qry.bindValue(":v_opmerkingen", Opmerkingen);
    qry.bindValue(":v_datum_instock", DatumInstock);
    qry.bindValue(":v_datum_eig_tgv", DatumEigTgv);
    qry.bindValue(":v_datum_uitstock", DatumUitstock);
    qry.bindValue(":v_actief", Actief);
    qry.bindValue(":v_artikel_id", Artikel_ID);
    qry.bindValue(":v_hoeveelheid_in", HoeveelheidIn);
    qry.bindValue(":v_hoeveelheid_uit", HoeveelheidUit);
    qry.bindValue(":v_hoeveelheid_afval", HoeveelheidAfval);
    qry.bindValue(":v_houdbaarheid", Houdbaarheid);
    qry.bindValue(":v_verpakking", Verpakking);
    qry.bindValue(":v_recept_productie", ReceptProductie);
    qry.bindValue(":v_lev_id", Lev_ID);
    qry.bindValue(":v_lev_lotnr", LevLotnr);
    qry.bindValue(":v_lev_slachthuis", LevSlachthuis);
    qry.bindValue(":v_lev_sanitel", LevSanitel);
    qry.bindValue(":v_lev_prod_datum", LevProdDatum);
    qry.bindValue(":v_lev_tgv", LevTgv);
    qry.bindValue(":v_lev_document", LevDocument);
    qry.bindValue(":v_lev_regel", LevRegel);
    qry.bindValue(":v_locatie_id", Locatie_ID);
    qry.bindValue(":v_locatie_veranderd_op", LocatieVeranderdOp);

    if (qry.exec())
    {

        if (Lotnummer_id == 0)
        {
            Lotnummer_id = qry.lastInsertId().toInt();
            myQuery = "INSERT INTO productie.lotnummer_locatie("
                        "tijdstip, locatie_id, lotnr_id) "
                      "VALUES (current_timestamp, :v_loc_id, :v_lotnr_id);";
            qry.prepare(myQuery);
            qry.bindValue(":v_loc_id", Locatie_ID);
            qry.bindValue(":v_lotnr_id", Lotnummer_id);
            if ( !qry.exec())
            {
                qDebug() << "Database error locatie lotnr: " << qry.lastError().databaseText() << "\nQuerry error: " << qry.lastQuery();
            }
        }
    }
    else
    {
        qDebug() << "Database error Lotnummers: " << qry.lastError().databaseText() << "\nQuerry error: " << qry.lastError().text();
    }
}


//=================================================================================
//
//    Static
//
//---------------------------------------------------------------------------------

int LotnummerData::getLotInWinkel(int _art)
{
    QString myQuery;
    QSqlQuery qry;
    bool status;
    int lot_id = 0;

    myQuery = "SELECT lotnummer_id FROM productie.lotnummerdata "
              "WHERE (artikel_id = :v_artikel_id) AND (locatie_id = 13) AND (actief = TRUE) "
              "ORDER BY locatie_veranderd_op DESC; ";

    // locatie_id 13 is Winkel

    qry.prepare(myQuery);
    qry.bindValue(":v_artikel_id", _art);
    status = qry.exec();
    if (status )
    {
        status = qry.next();
        if (status )
        {
            lot_id = qry.value("lotnummer_id").toInt();
        }
        else
        {
            lot_id = 0;
            qDebug() << "Error bij lezen Lotnummer record (of geen record gevonden)- " << qry.lastError().text();
        }
    }
    else
    {
        lot_id = 0;
        qDebug() << "Database error lotnummers: " << qry.lastError().databaseText() << "\nQuerry error: " << qry.lastError().text();
    }
    return lot_id;
}

void LotnummerData::getLotnrByArticle(int _art, QSqlQueryModel *_mod)
{
    QString myQuery =
            "SELECT t.lotnummer_id, t.lotnummer, t.opmerkingen, c.omschrijving as locatie, t.datum_instock as prod_datum, "
                   "t.datum_eig_tgv as te_gebruiken_tot, t.hoeveelheid_in as start, t.hoeveelheid_uit as verbruikt "
            "FROM productie.lotnummerdata as t, common.locatie as c "
            "WHERE (artikel_id = :v_artikel_id) AND (actief = TRUE) AND "
                  "(c.locatie_id = t.locatie_id);"
            ;
    QSqlQuery qry;
    qry.prepare(myQuery);
    qry.bindValue(":v_artikel_id", _art);
    qry.exec();
    _mod->setQuery(qry);

}
