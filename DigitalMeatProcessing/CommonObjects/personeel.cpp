#include "personeel.h"

#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>

//=========================================================================
//
//  Personeelsbestand - Properties
//
//-------------------------------------------------------------------------
//
// personeel_id serial NOT NULL,
// voornaam character varying,
// naam character varying,
// verkoper boolean,
// actief boolean,
//

int Personeel::getPersoneel_ID() { return Personeel_ID; }
void Personeel::setPersoneel_ID(int _id) { Personeel_ID = _id; }

QString Personeel::getVoornaam() { return Voornaam; }
void Personeel::setVoornaam(QString _vn) { Voornaam = _vn; }

QString Personeel::getNaam() { return Naam; }
void Personeel::setNaam(QString _n) { Naam = _n; }

bool Personeel::getVerkoper() { return Verkoper; }
void Personeel::setVerkoper(bool _set) { Verkoper = _set; }

bool Personeel::getActief() { return Actief; }
void Personeel::setActief(bool _set) { Actief = _set; }


//---------------------------------------------------------------------------
//
//   Constructors
//
//---------------------------------------------------------------------------



Personeel::Personeel()
{
    clear();
}

Personeel::Personeel(int _id)
{
    Personeel_ID = _id;
    read();
}

//---------------------------------------------------------------------------
//
//   Methods
//
//---------------------------------------------------------------------------

void Personeel::clear()
{
    Personeel_ID = 0;
    Voornaam = "";
    Naam = "";
    Verkoper = false;
    Actief = false;
}

void Personeel::read()
{
    QString myQuery;
    QSqlQuery qry;

    myQuery = "SELECT * FROM common.personeel WHERE personeel_id = :v_personeel_id; ";

    qry.prepare(myQuery);
    qry.bindValue(":v_personeel_id", Personeel_ID);
    if ( qry.exec() )
    {
        if (qry.next())
        {
            Personeel_ID = qry.value("personeel_id").toInt();
            Voornaam = qry.value("voornaam").toString();
            Naam = qry.value("naam").toString();
            Verkoper = qry.value("verkoper").toBool();
            Actief = qry.value("actief").toBool();
        }
        else
        {
            Personeel_ID = 0;
            qDebug() << "Error bij lezen Personeel-record (of geen record gevonden)- " << qry.lastError().text();
        }
    }
    else
    {
        Personeel_ID = 0;
        qDebug() << "Database error personeel: " << qry.lastError().databaseText() << "\nQuerry error: " << qry.lastError().text();
    }
}

//---------------------------------------------------------------------------
//
//   Statics
//
//---------------------------------------------------------------------------

void Personeel::getAllActiveSalesmen(QSqlQueryModel*model)
{
    QSqlQuery myquery;
    myquery.prepare("SELECT personeel_id, voornaam, naam, volgnummer "
                    "FROM common.personeel "
                    "WHERE (verkoper = TRUE) AND (actief = TRUE)  "
                    "ORDER BY volgnummer;");
    if (myquery.exec())
    {
        model->setQuery(myquery);
        model->query();
    }
    else
    {
        model = 0;
        qDebug() << "Fout in getAllActiveSalesmen: " << myquery.lastError() << " query: " << myquery.lastQuery();
    }
}

void Personeel::setSalesmenOnBalance(int _id, int balans)
{
    QSqlQuery qry;
    qry.prepare("SELECT common.set_salesmen_on_balance(:v_id, :v_balance);");
    qry.bindValue(":v_id", _id);
    qry.bindValue(":v_balance", balans);
    if (!qry.exec())
    {
        qDebug() << "Fout in setSalesmenOnBalance: " << qry.lastError() << " query: " << qry.lastQuery();
    }
}

int Personeel::getSalesmenOnBalance(int balans)
{
    QSqlQuery qry;
    int _id = 0;
    qry.prepare("SELECT personeel_id "
                "FROM common.personeel "
                "WHERE (kassa = :v_balance);");
    qry.bindValue(":v_balance", balans);
    if (qry.exec())
    {
        if (qry.next())
        {
            _id = qry.value("personeel_id").toInt();
        }
        else
        {
            qDebug() << "Error bij lezen getSalesmenOnBalance-record (of geen record gevonden)- " << qry.lastError().text();
        }
    }
    else
    {
        qDebug() << "Fout in getSalesmenOnBalance: " << qry.lastError() << " query: " << qry.lastQuery();
    }
    return _id;
}
