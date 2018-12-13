#include "comeenheden.h"

#include <QString>
#include <QtCore>
#include <QtSql>
#include <QSqlDatabase>
#include <QSettings>
#include <QApplication>


//==================================================================================================
//  Properties
//

void ComEenheden::setEenheids_ID(int _id)
{
    Eenheids_ID = _id;
}

int ComEenheden::getEenheids_ID()
{
    return Eenheids_ID;
}

void ComEenheden::setEenheidsCode(QString _EenheidsCode)
{
    EenheidsCode = _EenheidsCode;
}

QString ComEenheden::getEenheidsCode()
{
    return EenheidsCode;
}

void ComEenheden::setEenheidsOmschrijving(QString _EenheidsOmschrijving)
{
    EenheidsOmschrijving = _EenheidsOmschrijving;
}

QString ComEenheden::getEenheidsOmschrijving()
{
    return EenheidsOmschrijving;
}


//================================================================================================
//  Constructors
//


ComEenheden::ComEenheden()
{
    Eenheids_ID = 0;
    EenheidsCode = "";
    EenheidsOmschrijving = "";
}

ComEenheden::ComEenheden(int _id)
{
    Eenheids_ID = _id;
    read();
}

//=================================================================================================
//  Methods
//

void ComEenheden::read()
{
    QString myQuery;
    QSqlQuery qry;
    bool status;

    myQuery = "SELECT * FROM artikelbeheer.com_eenheden WHERE eenheids_id = :v_eenheids_id; ";

    qry.prepare(myQuery);
    qry.bindValue(":v_eenheids_id", Eenheids_ID);
    status = qry.exec();
    if (status )
    {
        status = qry.next();
        if (status )
        {
            Eenheids_ID = qry.value("eenheids_id").toInt();
            EenheidsCode = qry.value("eenheids_code").toString();
            EenheidsOmschrijving = qry.value("eenheids_omschrijving").toString();
        }
        else
        {
            qDebug() << "Error bij lezen record (of geen record gevonden)- " << qry.lastError().text();
        }
    }
    else
    {
        Eenheids_ID = 0;
        qDebug() << "Database error (ComEenheid::read): " << qry.lastError().databaseText() << "\nQuerry error: " << qry.lastError().text();
    }

}

void ComEenheden::save()
{

    QString myQuery;
    QSqlQuery qry;

    if (Eenheids_ID == 0)
    {
        myQuery = "INSERT INTO artikelbeheer.com_eenheden "
                         "( eenheids_code, eenheids_omschrijving) "
                  "VALUES ( :v_eenheids_code, :v_eenheids_omschrijving);";
        qry.prepare(myQuery);

    }
    else
    {
        myQuery = "UPDATE artikelbeheer.com_eenheden "
                  "SET eenheids_code = :v_eenheids_code, "
                      "eenheids_omschrijving = :v_eenheids_omschrijving "
                  "WHERE eenheids_id = :v_eenheids_id; ";
        qry.prepare(myQuery);
        qry.bindValue(":v_eenheids_id", Eenheids_ID);
    }

    qry.bindValue(":v_eenheids_code", EenheidsCode);
    qry.bindValue(":v_eenheids_omschrijving", EenheidsOmschrijving);

    if (qry.exec())
    {
        if (Eenheids_ID == 0)
        {
            Eenheids_ID = qry.lastInsertId().toInt();
        }
    }
    else
    {
        qDebug() << "Database error (ComEenheden::save): " << qry.lastError().databaseText() << "\nQuerry error: " << qry.lastError().text();
    }

}

//====================================================================================================
//   Static Methods
//

void ComEenheden::getAllComEenheden(QSqlQueryModel *model)
{
    model->setQuery("SELECT * FROM artikelbeheer.com_eenheden ORDER BY eenheids_code");
}

void ComEenheden::getComEenhedenKeuze(QSqlQueryModel *model)
{
    QString myQuery = "SELECT eenheids_id, concat_ws('. ', eenheids_code::text, eenheids_omschrijving::text) AS naam FROM artikelbeheer.com_eenheden ORDER BY eenheids_code;";
    QSqlQuery qry;
    qry.prepare(myQuery);
    qry.exec();
    model->setQuery(qry);
}

QString ComEenheden::getComEenheidsCode(int _id)
{
    QString code = "";
    QString myQuery = "SELECT eenheids_code FROM artikelbeheer.com_eenheden WHERE eenheids_id = :v_eenheids_id;";
    QSqlQuery qry;
    qry.prepare(myQuery);
    qry.bindValue(":v_eenheids_id", _id);
    if (qry.exec())
    {
        if (qry.next())
        {
            code = qry.value("eenheids_code").toString();
        }
        else
        {
            qDebug() << "Error bij lezen Com Eenheid (of geen record gevonden)- " << qry.lastError().text();
        }
    }
    else
    {
        code = "";
        qDebug() << "Database error ComEenheid: " << qry.lastError().databaseText() << "\nQuerry error: " << qry.lastError().text();
    }
    return code;
}

int ComEenheden::getComEenheidsID(QString _code)
{
    int _id = 0;
    QString myQuery = "SELECT eenheids_id FROM artikelbeheer.com_eenheden WHERE eenheids_code = :v_eenheids_code;";
    QSqlQuery qry;
    qry.prepare(myQuery);
    qry.bindValue(":v_eenheids_code", _code);
    if (qry.exec())
    {
        if (qry.next())
        {
            _id = qry.value("eenheids_id").toInt();
        }
        else
        {
            qDebug() << "Error bij lezen Com Eenheid_id (of geen record gevonden)- " << qry.lastError().text();
        }
    }
    else
    {
        _id = 0;
        qDebug() << "Database error ComEenheid_id: " << qry.lastError().databaseText() << "\nQuerry error: " << qry.lastError().text();
    }
    return _id;
}
