#include "ticket.h"

#include <QDebug>
#include <QSqlError>
#include <QString>
#include <QtCore>
#include <QtSql>
#include <QSqlDatabase>
#include <QSettings>
#include <QApplication>


//========================================================================
//
//   Properties kassa ticket
//
//------------------------------------------------------------------------
//
// ticket_id serial NOT NULL,
// tijdstip timestamp,
// volgnummer character varying(20),
// verkoper_id integer,
// verkoper_naam character varying(50),
// totaal_ex_btw numeric(20,4),
// totaal_btw numeric(20,4),
// totaal_incl_btw numeric(20,4),
// naar_kas boolean,
// betaald boolean,
// naar_factuur boolean,
// factuurklant_id int,
// factuur_id integer,
// betaalwijze integer,
// CONSTRAINT pk_ticket_id PRIMARY KEY (ticket_id)
//

int Ticket::getTicket_ID() { return Ticket_ID; }
void Ticket::setTicket_ID(int _id) { Ticket_ID = _id; }

QDateTime Ticket::getTijdstip() { return Tijdstip; }
void Ticket::setTijdstip(QDateTime _tijd) { Tijdstip = _tijd; }

QString Ticket::getVolgnummer() { return Volgnummer; }
void Ticket::setVolgnummer(QString _nr) { Volgnummer = _nr; }

int Ticket::getVerkoper_ID() { return Verkoper_ID; }
void Ticket::setVerkoper_ID(int _id) { Verkoper_ID = _id; }

QString Ticket::getVerkoper_Naam() { return Verkoper_Naam; }
void Ticket::setVerkoper_Naam(QString _naam) { Verkoper_Naam = _naam; }

double Ticket::getTotaal_Ex_BTW() { return Totaal_Ex_BTW; }
void Ticket::setTotaal_Ex_BTW(double _bedrag) { Totaal_Ex_BTW = _bedrag; }

double Ticket::getTotaal_BTW() { return Totaal_BTW; }
void Ticket::setTotaal_BTW(double _bedrag) { Totaal_BTW = _bedrag; }

double Ticket::getTotaal_Incl_BTW() { return Totaal_Incl_BTW; }
void Ticket::setTotaal_Incl_BTW(double _bedrag) { Totaal_Incl_BTW = _bedrag; }

bool Ticket::getNaar_Kas() { return Naar_Kas; }
void Ticket::setNaar_Kas(bool _set) { Naar_Kas = _set; }

bool Ticket::getBetaald() { return Betaald; }
void Ticket::setBetaald(bool _set) { Betaald = _set; }

bool Ticket::getNaar_Factuur() { return Naar_Factuur; }
void Ticket::setNaar_Factuur(bool _set) { Naar_Factuur = _set; }

int Ticket::getFactuurKlant_ID() { return FactuurKlant_ID; }
void Ticket::setFactuurKlant_ID(int _id) { FactuurKlant_ID = _id; }

int Ticket::getFactuur_ID() { return Factuur_ID; }
void Ticket::setFactuur_ID(int _id) { Factuur_ID = _id; }

int Ticket::getBetaalwijze() { return Betaalwijze; }
void Ticket::setBetaalwijze(int _id) { Betaalwijze = _id; }

double Ticket::getBetaalwijze_Bedrag() { return Betaalwijze_Bedrag; }
void Ticket::setBetaalwijze_Bedrag(double _bedrag) { Betaalwijze_Bedrag = _bedrag; }

int Ticket::getBetaalwijze2() { return Betaalwijze2; }
void Ticket::setBetaalwijze2(int _id) { Betaalwijze2 = _id; }

double Ticket::getBetaalwijze2_Bedrag() { return Betaalwijze2_Bedrag; }
void Ticket::setBetaalwijze2_Bedrag(double _bedrag) { Betaalwijze2_Bedrag = _bedrag; }

int Ticket::getBestelling() { return Bestelling; }
void Ticket::setBestelling(int _id) { Bestelling = _id; }

double Ticket::getBetaalwijze3_Bedrag() { return Betaalwijze3_Bedrag; }
void Ticket::setBetaalwijze3_Bedrag(double _bedrag) { Betaalwijze3_Bedrag = _bedrag; }

//=================================================================================
//
// Constructors
//
//---------------------------------------------------------------------------------



Ticket::Ticket()
{
    clear();
}

Ticket::Ticket(int _id)
{
    Ticket_ID = _id;
    read();
}

Ticket::Ticket(QString _volgnr)
{
   read(_volgnr);
}

//=================================================================================
//
//  Methods
//
//---------------------------------------------------------------------------------

void Ticket::clear()
{
    Ticket_ID = 0;
    Tijdstip = QDateTime::currentDateTime();
    Volgnummer = "";
    Verkoper_ID = 0;
    Verkoper_Naam = "";
    Totaal_Ex_BTW = 0;
    Totaal_BTW = 0;
    Totaal_Incl_BTW = 0;
    Naar_Kas = false;
    Betaald = false;
    Naar_Factuur = false;
    FactuurKlant_ID = 0;
    Factuur_ID = 0;
    Betaalwijze = 0;
    Betaalwijze_Bedrag = 0;
    Betaalwijze2 = 0;
    Betaalwijze2_Bedrag = 0;
    Bestelling = 0;
    Betaalwijze3_Bedrag = 0;
}

void Ticket::read()
{
    QString myQuery;
    QSqlQuery qry;

    myQuery = "SELECT * FROM verkoop.ticket_header WHERE ticket_id = :v_ticket_id; ";

    qry.prepare(myQuery);
    qry.bindValue(":v_ticket_id", Ticket_ID);
    if (qry.exec())
    {
        if (qry.next())
        {
            read_qry(qry);
        }
        else
        {
            Ticket_ID = 0;
            qDebug() << "Error bij lezen TicketHeader (of geen record gevonden)- " << qry.lastError().text();
        }
    }
    else
    {
        Ticket_ID = 0;
        qDebug() << "Database error TicketHeader: " << qry.lastError().databaseText() << "\nQuerry error: " << qry.lastQuery();
    }
}

void Ticket::read(QString _volgnr)
{
    QString myQuery;
    QSqlQuery qry;

    myQuery = "SELECT * FROM verkoop.ticket_header WHERE volgnummer = :v_volgnummer; ";

    qry.prepare(myQuery);
    qry.bindValue(":v_volgnummer", _volgnr);
    if (qry.exec())
    {
        if (qry.next())
        {
            read_qry(qry);
        }
        else
        {
            Ticket_ID = 0;
            qDebug() << "Error bij lezen TicketHeader (of geen record gevonden)- " << qry.lastError().text();
        }
    }
    else
    {
        Ticket_ID = 0;
        qDebug() << "Database error TicketHeader: " << qry.lastError().databaseText() << " Query: " << qry.lastQuery() ;
    }
}


void Ticket::read_qry(QSqlQuery qry)
{
    Ticket_ID = qry.value("ticket_id").toInt();
    Tijdstip = qry.value("tijdstip").toDateTime();
    Volgnummer = qry.value("volgnummer").toString();
    Verkoper_ID = qry.value("verkoper_id").toInt();
    Verkoper_Naam = qry.value("verkoper_naam").toString();
    Totaal_Ex_BTW = qry.value("totaal_ex_btw").toDouble();
    Totaal_BTW = qry.value("totaal_btw").toDouble();
    Totaal_Incl_BTW = qry.value("totaal_incl_btw").toDouble();
    Naar_Kas = qry.value("naar_kas").toBool();
    Betaald = qry.value("betaald").toBool();
    Naar_Factuur = qry.value("naar_factuur").toBool();
    FactuurKlant_ID = qry.value("factuurklant_id").toInt();
    Factuur_ID = qry.value("factuur_id").toInt();
    Betaalwijze = qry.value("betaalwijze").toInt();
    Betaalwijze_Bedrag = qry.value("betaalwijze_bedrag").toDouble();
    Betaalwijze2 = qry.value("betaalwijze2").toInt();
    Betaalwijze2_Bedrag = qry.value("betaalwijze2_bedrag").toDouble();
    Bestelling = qry.value("betaalwijze3").toInt();
    Betaalwijze3_Bedrag = qry.value("betaalwijze3_bedrag").toDouble();

}

void Ticket::save()
{
    QString myQuery;
    QSqlQuery qry;

    if (Ticket_ID == 0)
    {
        myQuery =
                "INSERT INTO verkoop.ticket_header "
                        "( tijdstip, volgnummer, verkoper_id, verkoper_naam, "
                        "totaal_ex_btw, totaal_btw, totaal_incl_btw, naar_kas, betaald, "
                        "naar_factuur, factuurklant_id, factuur_id, betaalwijze, betaalwijze_bedrag, "
                        "betaalwijze2, betaalwijze2_bedrag, betaalwijze3, betaalwijze3_bedrag) "
                "VALUES ( :v_tijdstip, :v_volgnummer, :v_verkoper_id, :v_verkoper_naam, "
                        ":v_totaal_ex_btw, :v_totaal_btw, :v_totaal_incl_btw, :v_naar_kas, :v_betaald, "
                        ":v_naar_factuur, :v_factuurklant_id, :v_factuur_id, :v_bw1, :v_bw1_b, "
                        ":v_bw2, :v_bw2_b, :v_bw3, :v_bw3_b); ";

        qry.prepare(myQuery);

    }
    else
    {
        myQuery =
                "UPDATE verkoop.ticket_header "
                "SET   tijdstip = :v_tijdstip, volgnummer = :v_volgnummer, "
                      "verkoper_id = :v_verkoper_id, verkoper_naam = :v_verkoper_naam, "
                      "totaal_ex_btw = :v_totaal_ex_btw, totaal_btw = :v_totaal_btw, "
                      "totaal_incl_btw = :v_totaal_incl_btw, naar_kas = :v_naar_kas, "
                      "betaald = :v_betaald, naar_factuur = :v_naar_factuur, factuurklant_id = :v_factuurklant_id, "
                      "factuur_id = :v_factuur_id, "
                      "betaalwijze = :v_bw1, betaalwijze_bedrag = :v_bw1_b, "
                      "betaalwijze2 = :v_bw2, betaalwijze2_bedrag = :v_bw2_b, "
                      "betaalwijze3 = :v_bw3, betaalwijze3_bedrag = :v_bw3_b "
                "WHERE (ticket_id = :v_ticket_id); ";

        qry.prepare(myQuery);
        qry.bindValue(":v_ticket_id", Ticket_ID);
    }
    //QString tijd = Tijdstip.toString("yyyy-MM-dd hh:mm");
    qry.bindValue(":v_ticket_id", Ticket_ID);
    qry.bindValue(":v_tijdstip", Tijdstip);
    qry.bindValue(":v_volgnummer", Volgnummer);
    qry.bindValue(":v_verkoper_id", Verkoper_ID);
    qry.bindValue(":v_verkoper_naam", Verkoper_Naam);
    qry.bindValue(":v_totaal_ex_btw", Totaal_Ex_BTW);
    qry.bindValue(":v_totaal_btw", Totaal_BTW);
    qry.bindValue(":v_totaal_incl_btw", Totaal_Incl_BTW);
    qry.bindValue(":v_naar_kas", Naar_Kas);
    qry.bindValue(":v_betaald", Betaald);
    qry.bindValue(":v_naar_factuur", Naar_Factuur);
    qry.bindValue(":v_factuurklant_id", FactuurKlant_ID);
    qry.bindValue(":v_factuur_id", Factuur_ID);
    qry.bindValue(":v_bw1", Betaalwijze);
    //qry.bindValue("v_bw1_b", Betaalwijze_Bedrag);
    qry.bindValue(":v_bw2", Betaalwijze2);
    //qry.bindValue("v_bw2_b", Betaalwijze2_Bedrag);
    qry.bindValue(":v_bw3", Bestelling);
    //qry.bindValue("v_bw3_b", Betaalwijze3_Bedrag);


    if (qry.exec())
    {
        if (Ticket_ID == 0)
        {
            Ticket_ID = qry.lastInsertId().toInt();
        }
    }
    else
    {
        qDebug() << "Database error Ticketheader: " << qry.lastError().text()  << " Query: " << qry.lastQuery();
    }
}

//=================================================================================
//
//   Statics
//
//---------------------------------------------------------------------------------

void Ticket::LogTicketControle(int _id)
{
    QString myQuery;
    QSqlQuery qry;

    myQuery = "INSERT INTO verkoop.ticket_controle (ticket_id, tijdstip)"
              "VALUES (:v_ticket_id, :v_tijdstip); ";

    qry.prepare(myQuery);
    qry.bindValue(":v_ticket_id", _id);
    qry.bindValue(":v_tijdstip",QDateTime::currentDateTime());
    if (!qry.exec())
    {
        qDebug() << "Database error TicketControle: " << qry.lastError().databaseText() << " Query: " << qry.lastQuery() ;
    }

}

int Ticket::CheckOpenTicket(int _persID)
{
    QString myQuery;
    QSqlQuery qry;
    int _Ticket_ID = 0;

    myQuery = "SELECT ticket_id FROM verkoop.ticket_header WHERE (verkoper_id = :v_verkoper_id) AND (naar_kas = FALSE); ";

    qry.prepare(myQuery);
    qry.bindValue(":v_verkoper_id", _persID);
    if (qry.exec())
    {
        if (qry.next())
        {
            _Ticket_ID = qry.value("ticket_id").toInt();
        }
        else
        {
            _Ticket_ID = 0;
            qDebug() << "Error bij lezen CheckOpenTicket (of geen record gevonden)- " << qry.lastError().text();
        }
    }
    else
    {
        _Ticket_ID = 0;
        qDebug() << "Database error CheckOpenTicket: " << qry.lastError().databaseText() << " Query: " << qry.lastQuery() ;
    }
   return _Ticket_ID;
}

void Ticket::deleteTicket(int _id)
{
    QSqlQuery myquery;
    myquery.prepare("DELETE FROM verkoop.ticket_line WHERE ticket_id = :v_ticket_id;");

    myquery.bindValue(":v_ticket_id", _id);

    if (!myquery.exec())
    {
        qDebug() << "Fout in deleteTicket - Lines: " << myquery.lastError() << " query: " << myquery.lastQuery();
    }
    else
    {
        myquery.prepare("DELETE FROM verkoop.ticket_header WHERE ticket_id = :v_ticket_id;");

        myquery.bindValue(":v_ticket_id", _id);

        if (!myquery.exec())
        {
            qDebug() << "Fout in deleteTicket: " << myquery.lastError() << " query: " << myquery.lastQuery();
        }

    }

}

int Ticket::CheckLastOpenTicket(int _persID)
{
    QString myQuery;
    QSqlQuery qry;
    int _Ticket_ID = 0;

    myQuery = "SELECT ticket_id FROM verkoop.ticket_header WHERE (verkoper_id = :v_verkoper_id) AND (naar_kas = TRUE) AND (betaald = FALSE); ";

    qry.prepare(myQuery);
    qry.bindValue(":v_verkoper_id", _persID);
    if (qry.exec())
    {
        if (qry.next())
        {
            _Ticket_ID = qry.value("ticket_id").toInt();
        }
        else
        {
            _Ticket_ID = 0;
            qDebug() << "Error bij lezen CheckLastOpenTicket (of geen record gevonden)- " << qry.lastError().text();
        }
    }
    else
    {
        _Ticket_ID = 0;
        qDebug() << "Database error CheckLastOpenTicket: " << qry.lastError().databaseText() << " Query: " << qry.lastQuery() ;
    }
   return _Ticket_ID;
}

void Ticket::TeBetalenTickets(QSqlQueryModel* _model)
{
    QSqlQuery myquery;
    myquery.prepare("SELECT * "
                    "FROM verkoop.ticket_header "
                    "WHERE (naar_kas = TRUE) AND (betaald = FALSE)  "
                    "ORDER BY tijdstip;");

    if (myquery.exec())
    {
        _model->setQuery(myquery);
        //_model->query();
    }
    else
    {
        //_model = 0;
        qDebug() << "Fout in TeBetalenTickets: " << myquery.lastError() << " query: " << myquery.lastQuery();
    }
}

void Ticket::getOmzetPerBTW(QDateTime _dag, QSqlQueryModel* _model)
{
    QSqlQuery myquery;
    myquery.prepare(

        "select  ' ' as Per_BTWtarief,"
            "to_char(tab1.perc, '90.99') as perc, "
            "to_char(sum(ex),'999999990.99') as ex, "
            "to_char(sum(btw),'999999990.99') as btw, "
            "to_char(sum(incl),'999999990.99') as incl "
        "from "
            "(SELECT substring(v.art_code,1 ,1) as code, p.product_benaming as benaming, "
                   "v.btw_perc as perc, "
                   "round(sum(v.prijs_incl_btw)/(1+v.btw_perc/100),2) as ex, "
                   "round(round(sum(v.prijs_incl_btw)/(1+v.btw_perc/100),2)*v.btw_perc/100,2) as btw, "
                   "round(sum(v.prijs_incl_btw), 2) as incl "
            "FROM verkoop.ticket_line as v, artikelbeheer.producten as p "
            "WHERE (v.tijdstip >= :v_van and v.tijdstip < :v_tot) and substring(v.art_code,1 ,1) = p.product_code "
            "GROUP BY substring(v.art_code,1 ,1),p.product_benaming, v.btw_perc "
            "ORDER BY substring(v.art_code,1 ,1)) as tab1 "
        "group by perc; "




//    "SELECT ' ' as Per_BTWtarief, "
//           "to_char(v.btw_perc, '90.99') as perc, to_char(sum(prijs_ex_btw),'999999990.99') as ex, "
//           "to_char(sum(v.prijs_btw),'999999990.99') as btw, to_char(sum(v.prijs_incl_btw),'999999990.99') as incl "
//    "FROM verkoop.ticket_line as v, verkoop.ticket_header as h "
//    "WHERE (v.tijdstip >= :v_van and v.tijdstip < :v_tot) "
//        "AND (v.ticket_id =h.ticket_id) "
//        "AND (h.verkoper_naam <> 'Kassa') "
//    "GROUP BY v.btw_perc "
//    "ORDER BY v.btw_perc; "
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
        qDebug() << "Fout in getOmzetPerBTW: " << myquery.lastError() << " query: " << myquery.lastQuery();
    }
}

double Ticket::getOmzetTotaa(QDateTime _dag)
{
    double Bedrag = 0;
    QSqlQuery myquery;
    myquery.prepare(
                "SELECT sum(v.prijs_incl_btw) as incl "
                "FROM verkoop.ticket_line as v, "
                     "verkoop.ticket_header as h "
                "WHERE (v.tijdstip >= :v_van and v.tijdstip < :v_tot) "
                     "AND (v.ticket_id =h.ticket_id) "
                     "AND (h.verkoper_naam <> 'Kassa'); "
                );

    myquery.bindValue(":v_van", _dag.date());
    myquery.bindValue(":v_tot", _dag.addDays(1).date());

    if (myquery.exec())
    {
        if (myquery.next())
        {
            Bedrag = myquery.value("incl").toDouble();
        }
        else
        {
            Bedrag = 0;
            qDebug() << "Error bij lezen getOmzetTotaa (of geen record gevonden)- " << myquery.lastError().text();
        }
    }
    else
    {
        Bedrag = 0;
        qDebug() << "Database error getOmzetTotaa: " << myquery.lastError().databaseText() << " Query: " << myquery.lastQuery() ;
    }
   return Bedrag;
}

double Ticket::getTicketTotaal(QDateTime _dag)
{
    double Bedrag = 0;
    QSqlQuery myquery;
    myquery.prepare(
                "SELECT sum(h.totaal_incl_btw) as incl "
                "FROM verkoop.ticket_header as h "
                "WHERE (h.tijdstip_betaald >= :v_van and h.tijdstip_betaald < :v_tot) "
                     "AND (h.verkoper_naam <> 'Kassa'); "
                );

    myquery.bindValue(":v_van", _dag.date());
    myquery.bindValue(":v_tot", _dag.addDays(1).date());

    if (myquery.exec())
    {
        if (myquery.next())
        {
            Bedrag = myquery.value("incl").toDouble();
        }
        else
        {
            Bedrag = 0;
            qDebug() << "Error bij lezen getOmzetTotaa (of geen record gevonden)- " << myquery.lastError().text();
        }
    }
    else
    {
        Bedrag = 0;
        qDebug() << "Database error getOmzetTotaa: " << myquery.lastError().databaseText() << " Query: " << myquery.lastQuery() ;
    }
   return Bedrag;
}

int Ticket::getAantalTickets(QDateTime _dag)
{
    int Aantal = 0;
    QSqlQuery myquery;
    myquery.prepare(
    "SELECT count(v.ticket_id) as aantal "
    "FROM verkoop.ticket_header as v "
    "WHERE (v.tijdstip >= :v_van and v.tijdstip < :v_tot) AND "
          "(v.verkoper_naam <> 'Kassa'); "
                );

    myquery.bindValue(":v_van", _dag.date());
    myquery.bindValue(":v_tot", _dag.addDays(1).date());

    if (myquery.exec())
    {
        if (myquery.next())
        {
            Aantal = myquery.value("aantal").toInt();
        }
        else
        {
            Aantal = 0;
            qDebug() << "Error bij lezen getAantalTickets (of geen record gevonden)- " << myquery.lastError().text();
        }
    }
    else
    {
        Aantal = 0;
        qDebug() << "Database error getAantalTickets: " << myquery.lastError().databaseText() << " Query: " << myquery.lastQuery() ;
    }
   return Aantal;
}

int Ticket::getBestellingByNumber(int _nr)
{
    int _id = 0;
    QSqlQuery myquery;
    myquery.prepare(
    "SELECT ticket_id "
    "FROM verkoop.ticket_header "
    "WHERE (betaalwijze3 = :v_bestelnr) AND (verkoper_id = 99); "
                );

    myquery.bindValue(":v_bestelnr", _nr);

    if (myquery.exec())
    {
        if (myquery.next())
        {
            _id = myquery.value("ticket_id").toInt();
        }
        else
        {
            _id = 0;
            qDebug() << "Error bij lezen getBestellingByNummer (of geen record gevonden)- " << myquery.lastError().text();
        }
    }
    else
    {
        _id = 0;
        qDebug() << "Database error getBestellingByNummer: " << myquery.lastError().databaseText() << " Query: " << myquery.lastQuery() ;
    }
   return _id;

}

void Ticket::getTeFactureren(QSqlQueryModel *_model)
{
    QSqlQuery myquery;
    myquery.prepare(
           "SELECT ticket_id, tijdstip, volgnummer, verkoper_naam, cast(totaal_incl_btw as money) "
           "FROM verkoop.ticket_header "
           "WHERE naar_factuur = true and factuurklant_id = 0 and verkoper_id <> 0 "
           "ORDER BY ticket_id ;"
                );
    if (myquery.exec())
    {
        _model->setQuery(myquery);
    }
    else
    {
        qDebug() << "Fout in getTeFactureren: " << myquery.lastError() << " query: " << myquery.lastQuery();
    }
}

void Ticket::TicketToFactuur(int _FactuurID, int _TicketID, int _KlantID)
{
    QSqlQuery myquery;
    myquery.prepare(
             "SELECT verkoop.ticket_to_factuur(:v_faktuur_id, :v_ticket_id, :v_klant_id);"
                );

    myquery.bindValue(":v_faktuur_id", _FactuurID);
    myquery.bindValue(":v_ticket_id", _TicketID);
    myquery.bindValue(":v_klant_id", _KlantID);

    if (!myquery.exec())
    {
        qDebug() << "Fout in getTeFactureren: " << myquery.lastError() << " query: " << myquery.lastQuery();
    }
}
