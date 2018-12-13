#include "ticketline.h"

#include <QDebug>
#include <QSqlError>
#include <QString>
#include <QtCore>
#include <QtSql>
#include <QSqlDatabase>
#include <QSettings>
#include <QApplication>

//=====================================================================
//
// Properties
//
//---------------------------------------------------------------------
//
// ticket_line_id serial NOT NULL,
// ticket_id integer,
// tijdstip timestamp without time zone,
// art_id integer,
// art_code character varying,
// art_omschrijving character varying,
// lotnr_id integer,
// lotnr_code character varying,
// hoeveelheid numeric(20,4),
// eenheid character varying,
// eenheidsprijs numeric(20,4),
// btw_perc numeric(20,4),
// prijs_ex_btw numeric(20,4),
// prijs_btw numeric(20,4),
// prijs_incl_btw numeric(20,4),
//

int TicketLine::getTicketLineID() { return TicketLineID; }
void TicketLine::setTicketLineID(int _id) { TicketLineID = _id; }

int TicketLine::getTicketID() { return TicketID; }
void TicketLine::setTicketID(int _id) { TicketID = _id; }

QDateTime TicketLine::getTijdstip() { return Tijdstip; }
void TicketLine::setTijdstip(QDateTime _tijd) { Tijdstip = _tijd; }

int TicketLine::getArtID() { return ArtID; }
void TicketLine::setArtID(int _id) { ArtID = _id; }

QString TicketLine::getArtCode() { return ArtCode; }
void TicketLine::setArtCode(QString _code) { ArtCode = _code; }

QString TicketLine::getArtOmschrijving() { return ArtOmschrijving; }
void TicketLine::setArtOmschrijving(QString _omschr) { ArtOmschrijving = _omschr; }

int TicketLine::getLotnrID() { return LotnrID; }
void TicketLine::setLotnrID(int _id) { LotnrID = _id; }

QString TicketLine::getLotnrCode() { return LotnrCode; }
void TicketLine::setLotnrCode(QString _code) { LotnrCode = _code; }

double TicketLine::getHoeveelheid() { return Hoeveelheid; }
void TicketLine::setHoeveelheid(double _aantal) { Hoeveelheid = _aantal; }

QString TicketLine::getEenheid() { return Eenheid; }
void TicketLine::setEenheid(QString _eenh) { Eenheid = _eenh; }

double TicketLine::getEenheidsprijs() { return Eenheidsprijs; }
void TicketLine::setEenheidsprijs(double _bedrag) { Eenheidsprijs = _bedrag; }

double TicketLine::getBTWperc() { return BTWperc; }
void TicketLine::setBTWperc(double _bedrag) { BTWperc = _bedrag; }

double TicketLine::getPrijsExBTW() { return PrijsExBTW; }
void TicketLine::setPrijsExBTW(double _bedrag) { PrijsExBTW = _bedrag; }

double TicketLine::getPrijsBTW() { return PrijsBTW; }
void TicketLine::setPrijsBTW(double _bedrag) { PrijsBTW = _bedrag; }

double TicketLine::getPrijsInclBTW() { return PrijsInclBTW; }
void TicketLine::setPrijsInclBTW(double _bedrag) { PrijsInclBTW = _bedrag; }


//========================================================================================
//
//   Constructors
//
//----------------------------------------------------------------------------------------

TicketLine::TicketLine()
{
    clear();
}

TicketLine::TicketLine(int _id)
{
    TicketLineID = _id;
    read();
}

//=========================================================================================
//
//   Methods
//
//-----------------------------------------------------------------------------------------

void TicketLine::clear()
{
    TicketLineID = 0;
    TicketID = 0;
    Tijdstip = QDateTime::currentDateTime();
    ArtID = 0;
    ArtCode = "";
    ArtOmschrijving = "";
    LotnrID = 0;
    LotnrCode = "";
    Hoeveelheid = 0;
    Eenheid = "";
    Eenheidsprijs = 0;
    BTWperc = 0;
    PrijsExBTW = 0;
    PrijsBTW = 0;
    PrijsInclBTW = 0;
}

void TicketLine::read()
{
    QString myQuery;
    QSqlQuery qry;

    myQuery = "SELECT * FROM verkoop.ticket_line WHERE ticket_line_id = :v_line_ticket_id; ";

    qry.prepare(myQuery);
    qry.bindValue(":v_ticket_line_id", TicketLineID);
    if (qry.exec())
    {
        if (qry.next())
        {
            read_qry(qry);
        }
        else
        {
            TicketLineID = 0;
            qDebug() << "Error bij lezen TicketLine (of geen record gevonden)- " << qry.lastError().text();
        }
    }
    else
    {
        TicketLineID = 0;
        qDebug() << "Database error TicketHeader: " << qry.lastError().databaseText() << "\nQuerry error: " << qry.lastQuery();
    }
}


void TicketLine::read_qry(QSqlQuery qry)
{
    TicketLineID = qry.value("ticket_line_id").toInt();
    TicketID = qry.value("ticket_id").toInt();
    Tijdstip = qry.value("tijdstip").toDateTime();
    ArtID = qry.value("art_id").toInt();
    ArtCode = qry.value("art_code").toString();
    ArtOmschrijving = qry.value("art_omschrijving").toString();
    LotnrID = qry.value("lotnr_id").toInt();
    LotnrCode = qry.value("lotnr_code").toString();
    Hoeveelheid = qry.value("hoeveelheid").toDouble();
    Eenheid = qry.value("eenheid").toString();
    Eenheidsprijs = qry.value("eenheidsprijs").toDouble();
    BTWperc = qry.value("btw_perc").toDouble();
    PrijsExBTW = qry.value("prijs_ex_btw").toDouble();
    PrijsBTW = qry.value("prijs_btw").toDouble();
    PrijsInclBTW = qry.value("prijs_incl_btw").toDouble();
}

void TicketLine::save()
{
    QString myQuery;
    QSqlQuery qry;

    if (TicketLineID == 0)
    {
        myQuery =
                "INSERT INTO verkoop.ticket_line"
                        "(ticket_id, tijdstip, art_id, art_code, art_omschrijving, "
                        "lotnr_id, lotnr_code, hoeveelheid, eenheid, eenheidsprijs, btw_perc, "
                        "prijs_ex_btw, prijs_btw, prijs_incl_btw) "
                "VALUES "
                        "(:v_ticket_id, :v_tijdstip, :v_art_id, :v_art_code, :v_art_omschrijving, "
                        ":v_lotnr_id, :v_lotnr_code, :v_hoeveelheid, :v_eenheid, :v_eenheidsprijs, :v_btw_perc, "
                        ":v_prijs_ex_btw, :v_prijs_btw, :v_prijs_incl_btw) ";
        qry.prepare(myQuery);

    }
    else
    {
        myQuery =
                "UPDATE verkoop.ticket_line "
                "SET   ticket_id = :v_ticket_id, tijdstip = :v_tijdstip, art_id = :v_art_id, art_code = :v_art_code, "
                      "art_omschrijving = :v_art_omschrijving, lotnr_id = :v_lotnr_id, lotnr_code = :v_lotnr_code, hoeveelheid = :v_hoeveelheid, "
                      "eenheid = :v_eenheid, eenheidsprijs = :v_eenheidsprijs, btw_perc = :v_btw_perc, prijs_ex_btw = :v_prijs_ex_btw, prijs_btw = :v_prijs_btw, "
                      "prijs_incl_btw = :v_prijs_incl_btw "
                "WHERE (ticket_line_id = :v_ticket_line_id); ";

        qry.prepare(myQuery);
        qry.bindValue(":v_ticke_linet_id", TicketLineID);
    }

    //qry.bindValue(":v_tijdstip", Tijdstip);
    qry.bindValue(":v_ticket_id", TicketID);
    qry.bindValue(":v_tijdstip", Tijdstip);
    qry.bindValue(":v_art_id", ArtID);
    qry.bindValue(":v_art_code", ArtCode);
    qry.bindValue(":v_art_omschrijving", ArtOmschrijving);
    qry.bindValue(":v_lotnr_id", LotnrID);
    qry.bindValue(":v_lotnr_code", LotnrCode);
    qry.bindValue(":v_hoeveelheid", Hoeveelheid);
    qry.bindValue(":v_eenheid",Eenheid);
    qry.bindValue(":v_eenheidsprijs", Eenheidsprijs);
    qry.bindValue(":v_btw_perc", BTWperc);
    qry.bindValue(":v_prijs_ex_btw", PrijsExBTW);
    qry.bindValue(":v_prijs_btw", PrijsBTW);
    qry.bindValue(":v_prijs_incl_btw", PrijsInclBTW);


    if (qry.exec())
    {
        if (TicketLineID == 0)
        {
            TicketLineID = qry.lastInsertId().toInt();
        }
    }
    else
    {
        qDebug() << "Database error Soorten: " << qry.lastError().text() << " Query= " << qry.lastQuery();
    }

}

//==============================================================================================
//
//    Static
//
//-----------------------------------------------------------------------------------------------

void TicketLine::getLinesByTicketID(int _id, QSqlQueryModel* _model)
{
    QSqlQuery myquery;
    myquery.prepare("SELECT * "
                    "FROM verkoop.ticket_line "
                    "WHERE ticket_id = :v_ticket_id  "
                    "ORDER BY ticket_line_id;");

    myquery.bindValue(":v_ticket_id", _id);

    if (myquery.exec())
    {
        _model->setQuery(myquery);
        _model->query();
    }
    else
    {
        _model = 0;
        qDebug() << "Fout in getLinesByTicketID: " << myquery.lastError() << " query: " << myquery.lastQuery();
    }
}

void TicketLine::getBTWByTicketID(int _id, QSqlQueryModel* _model)
{
    QSqlQuery myquery;
    myquery.prepare(
                  "SELECT btw_perc as perc, "
                         "SUM(prijs_ex_btw) as ex, "
                         "SUM(prijs_btw) as btw, "
                         "SUM(prijs_incl_btw) as incl "
                  "FROM verkoop.ticket_line "
                  "WHERE ticket_id = :v_ticket_id "
                  "GROUP BY btw_perc "
                  "ORDER BY btw_perc;"

                );

    myquery.bindValue(":v_ticket_id", _id);

    if (myquery.exec())
    {
        _model->setQuery(myquery);
        _model->query();
    }
    else
    {
        _model = 0;
        qDebug() << "Fout in getBTWByTicketID: " << myquery.lastError() << " query: " << myquery.lastQuery();
    }
}

void TicketLine::deleteTicketLine(int _id)
{
    QSqlQuery myquery;
    myquery.prepare("DELETE FROM verkoop.ticket_line WHERE ticket_line_id = :v_ticket_line_id;");

    myquery.bindValue(":v_ticket_line_id", _id);

    if (!myquery.exec())
    {
        qDebug() << "Fout in deleteTicketLine: " << myquery.lastError() << " query: " << myquery.lastQuery();
    }
}

void TicketLine::getOmzetPerRubiek(QDateTime _dag, QSqlQueryModel* _model)
{
    QSqlQuery myquery;
    myquery.prepare(
    "SELECT substring(v.art_code,1 ,1) as code, p.product_benaming as benaming, "
           "to_char(v.btw_perc, '90.99') as perc, "
           "to_char(round(sum(v.prijs_incl_btw)/(1+v.btw_perc/100),2),'999999990.99') as ex, "
           "to_char(round(round(sum(v.prijs_incl_btw)/(1+v.btw_perc/100),2)*v.btw_perc/100,2),'999999990.99') as btw, "
           "to_char(sum(v.prijs_incl_btw),'999999990.99') as incl "
    "FROM verkoop.ticket_line as v, artikelbeheer.producten as p "
    "WHERE (v.tijdstip >= :v_van and v.tijdstip < :v_tot) and substring(v.art_code,1 ,1) = p.product_code "
    "GROUP BY substring(v.art_code,1 ,1),p.product_benaming, v.btw_perc "
    "ORDER BY substring(v.art_code,1 ,1);  "

                );

    myquery.bindValue(":v_van", _dag.date());
    myquery.bindValue(":v_tot", _dag.addDays(1).date());

    if (myquery.exec())
    {
        _model->setQuery(myquery);
        //_model->query();
    }
    else
    {
        //_model = 0;
        qDebug() << "Fout in getOmzetPerRubiek: " << myquery.lastError() << " query: " << myquery.lastQuery();
    }
}

bool TicketLine::isTeFacturerenPerRubiek(QDateTime _dag)
{
    QSqlQuery myquery;
    bool result = false;
    myquery.prepare(
        "SELECT * FROM verkoop.ticket_header "
        "WHERE (tijdstip >= :v_van and tijdstip < :v_tot) "
            "AND naar_factuur = FALSE AND factuur_id = 0 AND factuurklant_id = 0; "
                );

    myquery.bindValue(":v_van", _dag.date());
    myquery.bindValue(":v_tot", _dag.addDays(1).date());

    if (myquery.exec())
    {
        if (myquery.numRowsAffected() >= 1)
            result = true;
    }
    else
    {
        //_model = 0;
        qDebug() << "Fout in getOmzetPerRubiek: " << myquery.lastError() << " query: " << myquery.lastQuery();
    }
    return result;
}

void TicketLine::setTicketGefactureerd(QDateTime _dag, int _klant, int _factuur)
{
    QSqlQuery myquery;
    myquery.prepare(
        "UPDATE verkoop.ticket_header "
        "SET naar_factuur = TRUE,"
            "factuurklant_id = :v_factuurklant_id, "
            "factuur_id = :v_factuur_id "
        "WHERE (tijdstip >= :v_van and tijdstip < :v_tot) "
            "AND naar_factuur = FALSE AND factuur_id = 0 AND factuurklant_id = 0; "
                );

    myquery.bindValue(":v_van", _dag.date());
    myquery.bindValue(":v_tot", _dag.addDays(1).date());
    myquery.bindValue(":v_factuurklant_id", _klant);
    myquery.bindValue(":v_factuur_id", _factuur);

    if (myquery.exec())
    {
        //_model->setQuery(myquery);
        //_model->query();
    }
    else
    {
        //_model = 0;
        qDebug() << "Fout in getOmzetPerRubiek: " << myquery.lastError() << " query: " << myquery.lastQuery();
    }
}

void TicketLine::getTeFacturerenPerRubiek(QDateTime _dag, QSqlQueryModel* _model)
{
    QSqlQuery myquery;
    myquery.prepare(
    "SELECT substring(v.art_code,1 ,1) as code, p.product_benaming as benaming, "
           "to_char(v.btw_perc, '90.99') as perc, "
           "to_char(round(sum(v.prijs_incl_btw)/(1+v.btw_perc/100),2),'999999990.99') as ex, "
           "to_char(round(round(sum(v.prijs_incl_btw)/(1+v.btw_perc/100),2)*v.btw_perc/100,2),'999999990.99') as btw, "
           "to_char(sum(v.prijs_incl_btw),'999999990.99') as incl "
    "FROM verkoop.ticket_line as v, artikelbeheer.producten as p, verkoop.ticket_header as t "
    "WHERE (v.tijdstip >= :v_van and v.tijdstip < :v_tot) and (substring(v.art_code,1 ,1) = p.product_code) "
          "AND t.naar_factuur = FALSE AND t.factuur_id = 0 AND v.ticket_id = t.ticket_id AND t.factuurklant_id = 0"
    "GROUP BY substring(v.art_code,1 ,1),p.product_benaming, v.btw_perc "
    "ORDER BY substring(v.art_code,1 ,1);  "

                );

    myquery.bindValue(":v_van", _dag.date());
    myquery.bindValue(":v_tot", _dag.addDays(1).date());

    if (myquery.exec())
    {
        _model->setQuery(myquery);
        //_model->query();
    }
    else
    {
        //_model = 0;
        qDebug() << "Fout in getOmzetPerRubiek: " << myquery.lastError() << " query: " << myquery.lastQuery();
    }
}

void TicketLine::getTicketTotalen(int _id, double &_ex, double &_btw, double &_incl)
{
    QString myQuery;
    QSqlQuery qry;
    double ex, btw, incl ;

    myQuery = "SELECT sum(prijs_ex_btw) as ex, sum(prijs_btw) as btw, sum(prijs_incl_btw) as incl "
              "FROM verkoop.ticket_line "
              "WHERE ticket_id = :v_id; ";

    qry.prepare(myQuery);
    qry.bindValue(":v_id", _id);
    if (qry.exec())
    {
        if (qry.next())
        {
            ex = qry.value("ex").toDouble();
            btw = qry.value("btw").toDouble();
            incl = qry.value("incl").toDouble();
            _ex = ex;
            _btw = btw;
            _incl = incl;
        }
        else
        {
            qDebug() << "Error bij lezen getTicketTotalen (of geen record gevonden)- " << qry.lastError().text();
        }
    }
    else
    {
        qDebug() << "Database error getTicketTotalen: " << qry.lastError().databaseText() << "\nQuerry error: " << qry.lastQuery();
    }

}

void TicketLine::setTimePerTicketID(int _id, QDateTime _tijdstip)
{
    QString myQuery;
    QSqlQuery qry;

    myQuery = "UPDATE verkoop.ticket_line "
              "SET tijdstip= :v_dat "
              "WHERE ticket_id = :v_id; ";

    qry.prepare(myQuery);
    qry.bindValue(":v_id", _id);
    qry.bindValue(":v_dat", _tijdstip);
    if (!qry.exec())
    {
        qDebug() << "Database error getTicketTotalen: " << qry.lastError().databaseText() << "\nQuerry error: " << qry.lastQuery();
    }

}
