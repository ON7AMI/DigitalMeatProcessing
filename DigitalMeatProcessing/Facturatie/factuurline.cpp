#include "factuurline.h"

#include <QString>
#include <QtCore>
#include <QtSql>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSettings>
#include <QApplication>


//=========================================================
//
// Lijnen Facturatie
//
//----------------------------------------------------------
//
// factuur_line_id serial NOT NULL,
// factuur_id integer,
// artikel_id integer,
// artikel_code character varying,
// omschrijving character varying,
// aantal numeric(20,4),
// eenheid character varying,
// eenheidsprijs numeric(20,4),
// korting_percent numeric(20,4),
// btw_percent numeric(20,4),
//
//----------------------------------------------------------
//
//   Properties
//
//----------------------------------------------------------

int FactuurLine::getFactuurLine_ID() { return FactuurLine_ID; }
void FactuurLine::setFactuurLine_ID(int _id) { FactuurLine_ID = _id; }

int FactuurLine::getFactuur_ID() { return Factuur_ID; }
void FactuurLine::setFactuur_ID(int _id) { Factuur_ID = _id; }

int FactuurLine::getArtikel_ID() { return Artikel_ID; }
void FactuurLine::setArtikel_ID(int _id) { Artikel_ID = _id; }

QString FactuurLine::getArtikelCode() { return ArtikelCode; }
void FactuurLine::setArtikelCode(QString _code) { ArtikelCode = _code; }

QString FactuurLine::getOmschrijving() { return Omschrijving; }
void FactuurLine::setOmschrijving(QString _omschr) { Omschrijving = _omschr; }

double FactuurLine::getAantal() { return Aantal; }
void FactuurLine::setAantal(double _aant) { Aantal = _aant; }

QString FactuurLine::getEenheid() { return Eenheid; }
void FactuurLine::setEenheid(QString _eenh) { Eenheid = _eenh; }

double FactuurLine::getEenheidsprijs() { return Eenheidsprijs; }
void FactuurLine::setEenheidsprijs(double _prijs) { Eenheidsprijs = _prijs; }

double FactuurLine::getKortingPercent() { return KortingPercent; }
void FactuurLine::setKortingPercent(double _kort) { KortingPercent = _kort; }

double FactuurLine::getBTW_Percent() { return BTW_Percent; }
void FactuurLine::setBTW_Percent(double _btw) { BTW_Percent = _btw; }


//----------------------------------------------------------
//
//   Constructors
//
//----------------------------------------------------------


FactuurLine::FactuurLine()
{
    clear();
}


FactuurLine::FactuurLine(int _id)
{
    clear();
    FactuurLine_ID = _id;
    read();
}

//-----------------------------------------------------------
//
//   Methodes
//
//-----------------------------------------------------------

void FactuurLine::clear()
{
    FactuurLine_ID = 0;
    Factuur_ID = 0;
    Artikel_ID = 0;
    ArtikelCode = "";
    Omschrijving = "";
    Aantal = 0.0;
    Eenheid = "";
    Eenheidsprijs = 0.0;
    KortingPercent = 0.0;
    BTW_Percent = 0.0;
}


void FactuurLine::read()
{
    QString myQuery;
    QSqlQuery qry;

    myQuery = "SELECT * FROM verkoop.factuur_line WHERE factuur_line_id = :vfactuur_line_id ; ";

    qry.prepare(myQuery);
    qry.bindValue(":vfactuur_line_id", FactuurLine_ID);

    if (qry.exec())
    {
        if (qry.next())
        {
            QryRead(&qry);
        }
        else
        {
            FactuurLine_ID = 0;
            qDebug() << "Error bij lezen Factuurlijn record (of geen record gevonden)- " << qry.lastError().text();
        }
    }
    else
    {
        FactuurLine_ID = 0;
        qDebug() << "Database error Factuurlijn: " << qry.lastError().databaseText() << "\nQuerry error: " << qry.lastError().text();
    }
}

void FactuurLine::QryRead(QSqlQuery *qry)
{
    FactuurLine_ID = qry->value("factuur_line_id").toInt();
    Factuur_ID = qry->value("factuur_id").toInt();
    Artikel_ID = qry->value("artikel_id").toInt();
    ArtikelCode = qry->value("artikel_code").toString();
    Omschrijving = qry->value("omschrijving").toString();
    Aantal = qry->value("aantal").toDouble();
    Eenheid = qry->value("eenheid").toString();
    Eenheidsprijs = qry->value("eenheidsprijs").toDouble();
    KortingPercent = qry->value("korting_percent").toDouble();
    BTW_Percent = qry->value("btw_percent").toDouble();
}

void FactuurLine::save()
{
    QString myQuery;
    QSqlQuery qry;

    if (FactuurLine_ID == 0)
    {
        myQuery =
                "INSERT INTO verkoop.factuur_line( "
                    "factuur_id, artikel_id, artikel_code, omschrijving, "
                    "aantal, eenheid, eenheidsprijs, korting_percent, btw_percent) "
                "VALUES (:v_factuur_id, :v_artikel_id, :v_artikel_code, :v_omschrijving, "
                    ":v_aantal, :v_eenheid, :v_eenheidsprijs, :v_korting_percent, :v_btw_percent);";

        qry.prepare(myQuery);

    }
    else
    {
        myQuery =
                "UPDATE verkoop.factuur_line "
                "SET factuur_id = :v_factuur_id, artikel_id = :v_artikel_id, artikel_code = :v_artikel_code, "
                    "omschrijving = :v_omschrijving, aantal = :v_aantal, eenheid = :v_eenheid, "
                    "eenheidsprijs = :v_eenheidsprijs, korting_percent = :v_korting_percent, "
                    "btw_percent = :v_btw_percent "
                "WHERE (factuur_line_id = :v_factuur_line_id); ";

        qry.prepare(myQuery);
        qry.bindValue(":v_factuur_line_id", FactuurLine_ID);
    }

    qry.bindValue(":v_factuur_id", Factuur_ID);
    qry.bindValue(":v_artikel_id", Artikel_ID);
    qry.bindValue(":v_artikel_code", ArtikelCode);
    qry.bindValue(":v_omschrijving", Omschrijving);
    qry.bindValue(":v_aantal", Aantal);
    qry.bindValue(":v_eenheid", Eenheid);
    qry.bindValue(":v_eenheidsprijs", Eenheidsprijs);
    qry.bindValue(":v_korting_percent", KortingPercent);
    qry.bindValue(":v_btw_percent", BTW_Percent);

    if (qry.exec())
    {
        if (FactuurLine_ID == 0)
        {
            FactuurLine_ID = qry.lastInsertId().toInt();
        }
    }
    else
    {
        qDebug() << "Database error Factuurlijn: " << qry.lastError().databaseText() << "\nQuerry error: " << qry.lastError().text();
    }
}


void FactuurLine::wis()
{
    QString myQuery;
    QSqlQuery qry;

    myQuery = "DELETE FROM verkoop.factuur_line WHERE factuur_line_id = :vfactuur_line_id ; ";

    qry.prepare(myQuery);
    qry.bindValue(":vfactuur_line_id", FactuurLine_ID);

    if (! qry.exec())
    {
        FactuurLine_ID = 0;
        qDebug() << "Error deleting Factuurlijn: " << qry.lastError().databaseText() << "\nQuerry deleting error: " << qry.lastError().text();
    }
}





void FactuurLine::getLinesByFactuurID(int _id, QSqlQueryModel* _model)
{
    QString myQuery =
         "SELECT artikel_code, omschrijving, eenheidsprijs, aantal, eenheid,  "
            "round((eenheidsprijs * aantal),2) as bruto, "
            "round(((eenheidsprijs * aantal) * (korting_percent / 100)),2) as kort, "
            "(round((eenheidsprijs * aantal),2) - round(((eenheidsprijs * aantal) * (korting_percent / 100)),2)) as excl, "
            "round(btw_percent, 2) as perc, "
            "round(((round((eenheidsprijs * aantal),2) - round(((eenheidsprijs * aantal) * (korting_percent / 100)),2))* btw_percent/100),2) as BTW, "
            "round(((round((eenheidsprijs * aantal),2) - round(((eenheidsprijs * aantal) * (korting_percent / 100)),2))* btw_percent/100),2) + "
            "(round((eenheidsprijs * aantal),2) - round(((eenheidsprijs * aantal) * (korting_percent / 100)),2))  as incl, "
            "factuur_line_id "
         "FROM verkoop.factuur_line "
         "WHERE factuur_id = :v_factuur_id "
         "ORDER BY factuur_line_id;";

    QSqlQuery qry;
    qry.prepare(myQuery);
    qry.bindValue(":v_factuur_id", _id);
    qry.exec();
    _model->setQuery(qry);
}

void FactuurLine::getBTWBlockByFactuurID(int _id, QSqlQueryModel* _model)
{
    QString myQuery =
         "SELECT perc, sum(excl) as mvh, sum(btw) as btw, sum(incl) as tot "
         "FROM (SELECT artikel_code, omschrijving, eenheidsprijs, aantal, eenheid,  "
                    "round((eenheidsprijs * aantal),2) as bruto, "
                    "round(((eenheidsprijs * aantal) * (korting_percent / 100)),2) as kort, "
                    "(round((eenheidsprijs * aantal),2) - round(((eenheidsprijs * aantal) * (korting_percent / 100)),2)) as excl, "
                    "round(btw_percent, 2) as perc, "
                    "round(((round((eenheidsprijs * aantal),2) - round(((eenheidsprijs * aantal) * (korting_percent / 100)),2))* btw_percent/100),2) as BTW, "
                    "round(((round((eenheidsprijs * aantal),2) - round(((eenheidsprijs * aantal) * (korting_percent / 100)),2))* btw_percent/100),2) + "
                    "(round((eenheidsprijs * aantal),2) - round(((eenheidsprijs * aantal) * (korting_percent / 100)),2))  as incl "
                "FROM verkoop.factuur_line "
                "WHERE factuur_id = :v_factuur_id) as lines "
         "GROUP BY perc "
         "ORDER BY perc;";

    QSqlQuery qry;
    qry.prepare(myQuery);
    qry.bindValue(":v_factuur_id", _id);
    qry.exec();
    _model->setQuery(qry);
}

void FactuurLine::getTotalsByFactuurID(int _id, QSqlQueryModel* _model)
{
    QString myQuery =
         "SELECT sum(mvh) as tot_mvh, sum(btw) as tot_btw, sum (tot) as tot_tot "
         "FROM (SELECT perc, sum(excl) as mvh, sum(btw) as btw, sum(incl) as tot "
            "FROM (SELECT artikel_code, omschrijving, eenheidsprijs, aantal, eenheid,  "
                        "round((eenheidsprijs * aantal),2) as bruto, "
                        "round(((eenheidsprijs * aantal) * (korting_percent / 100)),2) as kort, "
                        "(round((eenheidsprijs * aantal),2) - round(((eenheidsprijs * aantal) * (korting_percent / 100)),2)) as excl, "
                        "round(btw_percent, 2) as perc, "
                        "round(((round((eenheidsprijs * aantal),2) - round(((eenheidsprijs * aantal) * (korting_percent / 100)),2))* btw_percent/100),2) as BTW, "
                        "round(((round((eenheidsprijs * aantal),2) - round(((eenheidsprijs * aantal) * (korting_percent / 100)),2))* btw_percent/100),2) + "
                        "(round((eenheidsprijs * aantal),2) - round(((eenheidsprijs * aantal) * (korting_percent / 100)),2))  as incl "
                    "FROM verkoop.factuur_line "
                    "WHERE factuur_id = :v_factuur_id) as lines "
            "GROUP BY perc "
            "ORDER BY perc) as complete;";

    QSqlQuery qry;
    qry.prepare(myQuery);
    qry.bindValue(":v_factuur_id", _id);
    qry.exec();
    _model->setQuery(qry);
    // int rows = _model->rowCount();
    // int t = rows;
}
