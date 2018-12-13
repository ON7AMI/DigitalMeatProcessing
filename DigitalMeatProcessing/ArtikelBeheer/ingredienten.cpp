#include "ingredienten.h"

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
//
// ingredient_id serial NOT NULL,
// ingredient_omschrijving character varying,

void Ingredienten::setIngredient_ID(int _id){ Ingredient_ID = _id; }
int Ingredienten::getIngredient_ID(){ return Ingredient_ID; }

void Ingredienten::setOmschrijving(QString _omschr) { Omschrijving = _omschr; }
QString Ingredienten::getOmschrijving() {return Omschrijving; }


//================================================================================================
//  Constructors
//


Ingredienten::Ingredienten()
{
    clear();
}

Ingredienten::Ingredienten(int _id)
{
    Ingredient_ID = _id;
    read();
}

//=================================================================================================
//  Methods
//


void Ingredienten::clear()
{
    Ingredient_ID = 0;
    Omschrijving = "";
}

void Ingredienten::read()
{
    QString myQuery;
    QSqlQuery qry;
    bool status;

    myQuery = "SELECT * FROM artikelbeheer.ingredienten WHERE ingredient_id = :v_ingredient_id; ";

    qry.prepare(myQuery);
    qry.bindValue(":v_ingredient_id", Ingredient_ID);
    status = qry.exec();
    if (status )
    {
        status = qry.next();
        if (status )
        {
            Ingredient_ID = qry.value("ingredient_id").toInt();
            Omschrijving = qry.value("ingredient_omschrijving").toString();
        }
        else
        {
            qDebug() << "Error bij lezen Ingredienten record (of geen record gevonden)- " << qry.lastError().text();
        }
    }
    else
    {
        Ingredient_ID = 0;
        qDebug() << "Database error Ingredienten: " << qry.lastError().databaseText() << "\nQuerry error: " << qry.lastError().text();
    }

}

void Ingredienten::save()
{
    QString myQuery;
    QSqlQuery qry;

    if (Ingredient_ID == 0)
    {
        myQuery ="INSERT INTO artikelbeheer.ingredienten( "
                        "ingredient_omschrijving) "
                 "VALUES (:v_ingredient_omschrijving);";

        qry.prepare(myQuery);

    }
    else
    {
        myQuery = "UPDATE artikelbeheer.ingredienten "
                  "SET ingredient_omschrijving = :v_ingredient_omschrijving "
                  "WHERE (ingredient_id = :v_ingredient_id); ";

        qry.prepare(myQuery);
        qry.bindValue(":v_ingredient_id", Ingredient_ID);
    }

    qry.bindValue(":v_ingredient_omschrijving", Omschrijving);

    if (qry.exec())
    {
        if (Ingredient_ID == 0)
        {
            Ingredient_ID = qry.lastInsertId().toInt();
        }
    }
    else
    {
        qDebug() << "Database error Ingredienten: " << qry.lastError().databaseText() << "\nQuerry error: " << qry.lastError().text();
    }

}

//====================================================================================================
//   Static Methods
//

void Ingredienten::getAllIngredienten(QSqlQueryModel *_model)
{
    QString myQuery;
    QSqlQuery qry;

    myQuery = "SELECT * FROM artikelbeheer.ingredienten;";
    qry.prepare(myQuery);
    qry.exec();
    _model->setQuery(qry);
}

void Ingredienten::deleteIngredient(int _id)
{
    QString myQuery;
    QSqlQuery qry;

    myQuery =
    "DELETE FROM artikelbeheer.ingredienten "
    "WHERE "
      "ingredient_id = :v_ingredient_id; ";

    qry.prepare(myQuery);
    qry.bindValue(":v_ingredient_id", _id);
    bool status = qry.exec();
    if (!status)
    {
        qDebug() << "Error bij wissen Ingredienten record- " << qry.lastError().text();
    }
}
