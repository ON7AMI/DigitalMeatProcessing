#include "kasboek.h"

#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>


//=========================================================
//
//   Properties
//
//---------------------------------------------------------
//
// kasboek_id serial NOT NULL,
// bedrag_in numeric(18,2),
// bedrag_uit numeric(18,2),
// betaalmiddel_id integer,
// soort character varying,
// ticket_id integer,
// omschrijving character varying,
// tijdstip timestamp without time zone,
//
//
int Kasboek::getKasboek_ID() { return Kasboek_ID; }
void Kasboek::setKasboek_ID(int _id) { Kasboek_ID = _id; }

double Kasboek::getBedragIn() { return BedragIn; }
void Kasboek::setBedragIn(double _bedrag) { BedragIn = _bedrag; }

double Kasboek::getBedragUit() { return BedragUit; }
void Kasboek::setBedragUit(double _bedrag) { BedragUit = _bedrag; }

int Kasboek::getBetaalmiddel_ID() { return Betaalmiddel_ID; }
void Kasboek::setBetaalmiddel_ID(int _id) { Betaalmiddel_ID = _id; }

QString Kasboek::getSoort() { return Soort; }
void Kasboek::setSoort(QString _soort) { Soort = _soort; }        // O = Ontvangst - U = uitgave

int Kasboek::getTicket_ID() { return Ticket_ID; }
void Kasboek::setTicket_ID(int _id) { Ticket_ID = _id; }

QString Kasboek::getOmschrijving() { return Omschrijving; }
void Kasboek::setOmschrijving(QString _omschr) { Omschrijving = _omschr; }

QDateTime Kasboek::getTijdstip() { return Tijdstip; }
void Kasboek::setTijdstip(QDateTime _tijd) { Tijdstip = _tijd; }


//=============================================================
//
//   Constructors
//
//-------------------------------------------------------------

Kasboek::Kasboek()
{
    clear();
}

Kasboek::Kasboek(int _id)
{
    clear();
    Kasboek_ID = _id;
    read();
}


//=================================================================================
//
//  Methods
//
//---------------------------------------------------------------------------------

void Kasboek::clear()
{
    Kasboek_ID = 0;
    BedragIn = 0.0;
    BedragUit = 0.0;
    Betaalmiddel_ID = 0;
    Soort = "";
    Ticket_ID = 0;
    Omschrijving = "";
    Tijdstip = QDateTime::currentDateTime();
}

void Kasboek::read()
{
    QString myQuery;
    QSqlQuery qry;

    myQuery = "SELECT * FROM boekhouding.kasboek WHERE kasboek_id = :v_kasboek_id; ";

    qry.prepare(myQuery);
    qry.bindValue(":v_kasboek_id", Kasboek_ID);
    if (qry.exec())
    {
        if (qry.next())
        {
            read_qry(qry);
        }
        else
        {
            Kasboek_ID = 0;
            qDebug() << "Error bij lezen Kasboek (of geen record gevonden)- " << qry.lastError().text();
        }
    }
    else
    {
        Kasboek_ID = 0;
        qDebug() << "Database error Kasboek: " << qry.lastError().databaseText() << "\nQuerry error: " << qry.lastQuery();
    }
}

void Kasboek::read_qry(QSqlQuery qry)
{
    Kasboek_ID = qry.value("kasboek_id").toInt();
    BedragIn = qry.value("bedrag_in").toDouble();
    BedragUit = qry.value("bedrag_uit").toDouble();
    Betaalmiddel_ID = qry.value("betaalmiddel_id").toInt();
    Soort = qry.value("soort").toString();
    Ticket_ID = qry.value("ticket_id").toInt();
    Omschrijving = qry.value("omschrijving").toString();
    Tijdstip = qry.value("tijdstip").toDateTime();
}

void Kasboek::save()
{
    QString myQuery;
    QSqlQuery qry;

    if (Kasboek_ID == 0)
    {
        myQuery =
            "INSERT INTO boekhouding.kasboek"
                  "(bedrag_in, bedrag_uit, betaalmiddel_id, soort, ticket_id, omschrijving, tijdstip) "
            "VALUES (:v_bedrag_in, :v_bedrag_uit, :v_betaalmiddel_id, :v_soort, :v_ticket_id, :v_omschrijving, :v_tijdstip);";

        qry.prepare(myQuery);

    }
    else
    {
        myQuery =
            "UPDATE boekhouding.kasboek "
            "SET kasboek_id = :v_kasboek_id, bedrag_in = :v_bedrag_in, bedrag_uit = :v_bedrag_uit, "
                "betaalmiddel_id = :v_betaalmiddel_id, soort = :v_soort, "
                "ticket_id = :v_ticket_id, omschrijving = :v_omschrijving, "
                "tijdstip = :v_tijdstip "
            "WHERE (kasboek_id = :v_kasboek_id);";

        qry.prepare(myQuery);
        qry.bindValue(":v_kasboek_id", Kasboek_ID);
    }
    qry.bindValue(":v_bedrag_in", BedragIn);
    qry.bindValue(":v_bedrag_uit", BedragUit);
    qry.bindValue(":v_betaalmiddel_id", Betaalmiddel_ID);
    qry.bindValue(":v_soort", Soort);
    qry.bindValue(":v_ticket_id", Ticket_ID);
    qry.bindValue(":v_omschrijving", Omschrijving);
    qry.bindValue(":v_tijdstip", Tijdstip);

    if (qry.exec())
    {
        if (Kasboek_ID == 0)
        {
            Kasboek_ID = qry.lastInsertId().toInt();
        }
    }
    else
    {
        qDebug() << "Database error Kasboek: " << qry.lastError().text()  << " Query: " << qry.lastQuery();
    }
}

void Kasboek::getKassaBetaalmiddelen(QDateTime _tijd, QSqlQueryModel *_model)
{
    QSqlQuery myquery;
    myquery.prepare(
    "SELECT kasboek_id as ID, tijdstip::time, bedrag_in,  b.omschrijving, "
           "k.omschrijving as ticketcode "
    "FROM boekhouding.kasboek k "
    "LEFT join boekhouding.betaalwijze b on k.betaalmiddel_id = b.betaalwijze_id "
    "WHERE soort = 'O' and tijdstip > :v_van and tijdstip < :v_tot "
    "ORDER BY tijdstip;"
    );

    myquery.bindValue(":v_van", _tijd.date());
    myquery.bindValue(":v_tot", _tijd.addDays(1).date());

    if (myquery.exec())
    {
        _model->setQuery(myquery);
        //_model->query();
    }
    else
    {
        //_model = 0;
        qDebug() << "Fout in getKassaTotalen: " << myquery.lastError() << " query: " << myquery.lastQuery();
    }
}

void Kasboek::getKassaTotalen(QDateTime _dag, QSqlQueryModel* _model)
{
    QSqlQuery myquery;
    myquery.prepare(
    "SELECT b.omschrijving, to_char(sum(k.bedrag_in),'999990.99') as inkomsten, to_char(sum(k.bedrag_uit),'999990.99') as uitgaven "
    "FROM boekhouding.kasboek as k, boekhouding.betaalwijze as b "
    "WHERE (k.tijdstip >= :v_van and k.tijdstip < :v_tot) AND (b.betaalwijze_id = k.betaalmiddel_id) "
    "GROUP BY b.omschrijving;"
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
        qDebug() << "Fout in getKassaTotalen: " << myquery.lastError() << " query: " << myquery.lastQuery();
    }
}

void Kasboek::GetUitgaveTotalen(QDateTime _dag, QSqlQueryModel* _model)
{
    QSqlQuery myquery;
    myquery.prepare(
                "SELECT l.art_omschrijving as reden, to_char(t.totaal_incl_btw,'999999990.99') as bedrag "
                "FROM verkoop.ticket_header as t "
                "LEFT JOIN boekhouding.kasboek as k ON t.ticket_id = k.ticket_id "
                "LEFT JOIN verkoop.ticket_line as l on t.ticket_id = l.ticket_id "
                "WHERE verkoper_naam = 'Kassa' "
                "AND (k.tijdstip >= :v_van and k.tijdstip < :v_tot);"
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
        qDebug() << "Fout in getKassaTotalen: " << myquery.lastError() << " query: " << myquery.lastQuery();
    }

}

void Kasboek::getBetaalmiddelen(QSqlQueryModel *_model)
{
    QSqlQuery myquery;
    myquery.prepare(
    "SELECT betaalwijze_id, omschrijving "
    "FROM boekhouding.betaalwijze "
    "ORDER BY omschrijving;"
                );

    if (myquery.exec())
    {
        _model->setQuery(myquery);
    }
    else
    {
        //_model = 0;
        qDebug() << "Fout in getBetaalmiddelen: " << myquery.lastError() << " query: " << myquery.lastQuery();
    }
}


void Kasboek::getUitgaveRedenen(QSqlQueryModel *_model)
{
    QSqlQuery myquery;
    myquery.prepare(
    "SELECT omschrijving "
    "FROM boekhouding.reden_uitgave; "
                );

    if (myquery.exec())
    {
        _model->setQuery(myquery);
    }
    else
    {
        //_model = 0;
        qDebug() << "Fout in getUitgaveRedenen: " << myquery.lastError() << " query: " << myquery.lastQuery();
    }
}

QString Kasboek::getUitgaveTeken(QString Omschrijving)
{
    QString myQuery;
    QSqlQuery qry;
    QString teken = "n";

    myQuery = "SELECT invoer FROM boekhouding.reden_uitgave "
              "WHERE omschrijving = :v_omschrijving; ";

    qry.prepare(myQuery);
    qry.bindValue(":v_omschrijving", Omschrijving);
    if (qry.exec())
    {
        if (qry.next())
        {
            teken = qry.value("invoer").toString();
        }
        else
        {
            qDebug() << "Error bij lezen Teken Uitgave (of geen record gevonden)- " << qry.lastError().text();
        }
    }
    else
    {
        qDebug() << "Database error Uitgaveteken: " << qry.lastError().databaseText() << "\nQuerry error: " << qry.lastQuery();
    }
    return teken;
}
