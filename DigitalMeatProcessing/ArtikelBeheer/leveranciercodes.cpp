#include "leveranciercodes.h"

#include <QString>
#include <QtCore>
#include <QtSql>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSettings>
#include <QApplication>

// leverancier_referentie_id serial NOT NULL,
// leverancier_id integer,
// artikel_id integer,
// tijdstip timestamp without time zone,
// leverancier_referentie character varying,
// referentie_omschrijving character varying,
//
//----------------------------------------------------------
//
//   Properties
//
//----------------------------------------------------------

int LeverancierCodes::getLevRef_ID() { return LevRef_ID; }
void LeverancierCodes::setLevRef_ID(int _id) { LevRef_ID = _id; }

int LeverancierCodes::getLev_ID() { return Lev_ID; }
void LeverancierCodes::setLev_ID(int _id) { Lev_ID = _id; }

int LeverancierCodes::getArt_ID() { return Art_ID; }
void LeverancierCodes::setArt_ID(int _id) { Art_ID = _id; }

QDateTime LeverancierCodes::getCreatedAt() { return CreatedAt; }
void LeverancierCodes::setCreatedAt(QDateTime _time) { CreatedAt = _time; }

QString LeverancierCodes::getLev_Ref() { return Lev_Ref; }
void LeverancierCodes::setLev_Ref(QString _ref) { Lev_Ref = _ref; }

QString LeverancierCodes::getLev_Omschr() { return Lev_Omschr; }
void LeverancierCodes::setLev_Omschr(QString _omschr) { Lev_Omschr = _omschr; }



//----------------------------------------------------------
//
//   Constructors
//
//----------------------------------------------------------

LeverancierCodes::LeverancierCodes()
{
   clear();
}

LeverancierCodes::LeverancierCodes(int _id)
{
    clear();
    LevRef_ID = _id;
    read();
}

LeverancierCodes::LeverancierCodes(int _artid, int _levid)
{
    clear();
    Art_ID = _artid;
    Lev_ID = _levid;
    readArtID();
}


//-----------------------------------------------------------
//
//   Methodes
//
//-----------------------------------------------------------

void LeverancierCodes::clear()
{
    LevRef_ID = 0;
    Lev_ID = 0;
    Art_ID = 0;
    CreatedAt = QDateTime::currentDateTime();
    Lev_Ref = "";
    Lev_Omschr = "";
}

void LeverancierCodes::readArtID()
{
    QString myQuery;
    QSqlQuery qry;

    myQuery = "SELECT * FROM aankoop.leverancier_referenties "
              "WHERE artikel_id = :v_artikel_id "
                "AND leverancier_id = :v_leverancier_id; ";

    qry.prepare(myQuery);
    qry.bindValue(":v_leverancier_id", Lev_ID);
    qry.bindValue(":v_artikel_id", Art_ID);

    if (qry.exec())
    {
        if (qry.next())
        {
            QryRead(&qry);
        }
        else
        {
            LevRef_ID = 0;
            qDebug() << "Error bij lezen LeverancierReferentie record (of geen record gevonden)- " << qry.lastError().text();
        }
    }
    else
    {
        LevRef_ID = 0;
        qDebug() << "Database error LeverancierReferentie: " << qry.lastError().databaseText() << "\nQuerry error: " << qry.lastError().text();
    }

}

void LeverancierCodes::read()
{
    QString myQuery;
    QSqlQuery qry;

    myQuery = "SELECT * FROM aankoop.leverancier_referenties "
              "WHERE leverancier_referentie_id = :v_leverancier_referentie_id; ";

    qry.prepare(myQuery);
    qry.bindValue(":v_leverancier_referentie_id", LevRef_ID);

    if (qry.exec())
    {
        if (qry.next())
        {
            QryRead(&qry);
        }
        else
        {
            LevRef_ID = 0;
            qDebug() << "Error bij lezen LeverancierReferentie record (of geen record gevonden)- " << qry.lastError().text();
        }
    }
    else
    {
        LevRef_ID = 0;
        qDebug() << "Database error LeverancierReferentie: " << qry.lastError().databaseText() << "\nQuerry error: " << qry.lastError().text();
    }

}

void LeverancierCodes::save()
{
    QString myQuery;
    QSqlQuery qry;

    if (LevRef_ID == 0)
    {
        myQuery =
                "INSERT INTO aankoop.leverancier_referenties( "
                       "leverancier_id, "
                       "artikel_id, "
                       "tijdstip, "
                       "leverancier_referentie, "
                       "referentie_omschrijving) "
                "VALUES ( "
                       ":v_leverancier_id, "
                       ":v_artikel_id, "
                       ":v_tijdstip, "
                       ":v_leverancier_referentie, "
                       ":v_referentie_omschrijving);" ;
        qry.prepare(myQuery);
        qry.bindValue(":v_tijdstip", QDateTime::currentDateTime());
    }
    else
    {
        myQuery =
                "UPDATE aankoop.leverancier_referenties "
                "SET "
                    "leverancier_id = :v_leverancier_id, "
                    "artikel_id = :v_artikel_id, "
                    "tijdstip = :v_tijdstip, "
                    "leverancier_referentie = :v_leverancier_referentie, "
                    "referentie_omschrijving = :v_referentie_omschrijving "
                 "WHERE leverancier_referentie_id = :v_leverancier_referentie_id ;" ;

        qry.prepare(myQuery);
        qry.bindValue(":v_tijdstip",CreatedAt);
        qry.bindValue(":v_leverancier_referentie_id", LevRef_ID);
    }

    qry.bindValue(":v_leverancier_id",Lev_ID);
    qry.bindValue(":v_artikel_id",Art_ID);
    qry.bindValue(":v_leverancier_referentie",Lev_Ref);
    qry.bindValue(":v_referentie_omschrijving",Lev_Omschr);

    if (qry.exec())
    {
        if (LevRef_ID == 0)
        {
            LevRef_ID = qry.lastInsertId().toInt();
        }
    }
    else
    {
        qDebug() << "Database error leverancier_referenties: " << qry.lastError().databaseText() << "\nQuerry error: " << qry.lastError().text();
    }

}

void LeverancierCodes::QryRead(QSqlQuery *qry)
{
    LevRef_ID = qry->value("leverancier_referentie_id").toInt();
    Lev_ID = qry->value("leverancier_id").toInt();
    Art_ID = qry->value("artikel_id").toInt();
    CreatedAt = qry->value("tijdstip").toDateTime();
    Lev_Ref = qry->value("leverancier_referentie").toString();
    Lev_Omschr = qry->value("referentie_omschrijving").toString();
}

//-----------------------------------------------------------
//
//   Static Methodes
//
//-----------------------------------------------------------

