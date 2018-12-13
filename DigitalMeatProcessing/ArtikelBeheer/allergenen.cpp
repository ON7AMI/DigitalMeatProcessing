#include "allergenen.h"
#include <QString>
#include <QtCore>
#include <QtSql>
#include <QSqlDatabase>
#include <QSettings>
#include <QApplication>


//==================================================================================================
//  Properties
//


void Allergenen::setAllergeen_ID( int _Allergeen_ID ) { Allergeen_ID = _Allergeen_ID; }
int Allergenen::getAllergeen_ID() { return Allergeen_ID; }

void Allergenen::setAllergeen_Benaming(QString _Allergeen_Benaming ) { Allergeen_Benaming = _Allergeen_Benaming; }
QString Allergenen::getAllergeen_Benaming() { return Allergeen_Benaming; }

void Allergenen::setAllergeen_Omschrijving( QString _Allergeen_Omschrijving ) { Allergeen_Omschrijving = _Allergeen_Omschrijving; }
QString Allergenen::getAllergeen_Omschrijving() { return Allergeen_Omschrijving; }

void Allergenen::setAllergeen_Afbeelding( QByteArray _Allergeen_Afbeelding ) { Allergeen_Afbeelding = _Allergeen_Afbeelding; }
QByteArray Allergenen::getAllergeen_Afbeelding() { return Allergeen_Afbeelding; }


//================================================================================================
//  Constructors
//


Allergenen::Allergenen()
{
    Allergeen_ID = 0;
    Allergeen_Benaming = "";
    Allergeen_Omschrijving = "";
    Allergeen_Afbeelding = NULL;
}

Allergenen::Allergenen(int _id)
{
    Allergeen_ID = _id;
    read();
}

//=================================================================================================
//  Methods
//

void Allergenen::read()
{
    QString myQuery;
    QSqlQuery qry;
    bool status;

    myQuery = "SELECT * FROM artikelbeheer.allergenen WHERE allergeen_id = :v_allergeen_id; ";

    qry.prepare(myQuery);
    qry.bindValue(":v_allergeen_id", Allergeen_ID);
    status = qry.exec();
    if (status )
    {
        status = qry.next();
        if (status )
        {
            Allergeen_ID = qry.value("allergeen_id").toInt();
            Allergeen_Benaming = qry.value("allergeen_benaming").toString();
            Allergeen_Omschrijving = qry.value("allergeen_omschrijving").toString();
            Allergeen_Afbeelding = QByteArray::fromBase64(qry.value("allergeen_afbeelding").toByteArray());
        }
        else
        {
            qDebug() << "Error bij lezen allergenen record (of geen record gevonden)- " << qry.lastError().text();
        }
    }
    else
    {
        Allergeen_ID = 0;
        qDebug() << "Database error (Allergenen): " << qry.lastError().databaseText() << "\nQuerry error: " << qry.lastError().text();
    }

}

void Allergenen::save()
{

    QString myQuery;
    QSqlQuery qry;

    if (Allergeen_ID == 0)
    {
        myQuery = "INSERT INTO artikelbeheer.allergenen "
                         "( allergeen_benaming, allergeen_omschrijving, allergeen_afbeelding ) "
                  "VALUES ( :v_allergeen_benaming, :v_allergeen_omschrijving, :v_allergeen_afbeelding );";
        qry.prepare(myQuery);

    }
    else
    {
        myQuery = "UPDATE artikelbeheer.allergenen "
                  "SET allergeen_benaming = :v_allergeen_benaming, "
                      "allergeen_omschrijving = :v_allergeen_omschrijving, "
                      "allergeen_afbeelding = :v_allergeen_afbeelding "
                  "WHERE allergeen_id = :v_allergeen_id; ";
        qry.prepare(myQuery);
        qry.bindValue(":v_allergeen_id", Allergeen_ID);
    }

    //QString foto_64 = Allergeen_Afbeelding.toBase64();

    qry.bindValue(":v_allergeen_benaming", Allergeen_Benaming);
    qry.bindValue(":v_allergeen_omschrijving", Allergeen_Omschrijving);
    qry.bindValue(":v_allergeen_afbeelding", Allergeen_Afbeelding.toBase64());

    if (qry.exec())
    {
        if (Allergeen_ID == 0)
        {
            Allergeen_ID = qry.lastInsertId().toInt();
        }
    }
    else
    {
        qDebug() << "Database error: " << qry.lastError().databaseText() << "\nQuerry error: " << qry.lastError().text();
    }

}


//====================================================================================================
//   Static Methods
//

void Allergenen::getAllAllergeen(QSqlQueryModel *model)
{
    model->setQuery("SELECT allergeen_id, allergeen_benaming, allergeen_omschrijving FROM artikelbeheer.allergenen ORDER BY allergeen_benaming");
}

void Allergenen::getAllergeenKeuze(QSqlQueryModel *model)
{
    QString myQuery = "SELECT allergeen_id, allergeen_benaming AS naam FROM artikelbeheer.allergenen ORDER BY allergeen_benaming;";
    QSqlQuery qry;
    qry.prepare(myQuery);
    qry.exec();
    model->setQuery(qry);
}
