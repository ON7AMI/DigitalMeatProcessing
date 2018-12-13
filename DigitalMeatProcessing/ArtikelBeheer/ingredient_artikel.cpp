#include "ingredient_artikel.h"
#include "artikelen.h"

#include <QString>
#include <QtCore>
#include <QtSql>
#include <QSqlDatabase>

//==================================================================================================
//  Properties
//
//==================================================================================================
//
// ingredient__artikel_id serial NOT NULL,
// artikel_id integer,
// hoeveelheid numeric(20,4),
//

void Ingredient_Artikel::setIngredient_Artikel_ID(int _id) { Ingredient_Artikel_ID = _id; }
int Ingredient_Artikel::getIngredient_Artikel_ID() { return Ingredient_Artikel_ID; }

void Ingredient_Artikel::setArtikel_ID(int _id) { Artikel_ID = _id; }
int Ingredient_Artikel::getArtikel_ID() { return Artikel_ID; }

void Ingredient_Artikel::setIngredient_ID(int _id) { Ingredient_ID = _id; }
int Ingredient_Artikel::getIngredient_ID() { return Ingredient_ID; }

void Ingredient_Artikel::setHoeveelheid(double _hoeveel) { Hoeveelheid = _hoeveel; }
double Ingredient_Artikel::getHoeveelheid() { return Hoeveelheid; }

//================================================================================================
//  Constructors
//

Ingredient_Artikel::Ingredient_Artikel()
{
    clear();
}

Ingredient_Artikel::Ingredient_Artikel(int _id)
{
    Ingredient_Artikel_ID = _id;
    read();
}

//=================================================================================================
//  Methods
//

void Ingredient_Artikel::save()
{
    QString myQuery;
    QSqlQuery qry;

    if (Ingredient_Artikel_ID == 0)
    {
        myQuery = "INSERT INTO artikelbeheer.ingredienten_artikel "
                              "(artikel_id, ingredient_id, hoeveelheid) "
                  "VALUES (:v_artikel_id, :v_ingredient_id, :v_hoeveelheid);";

        qry.prepare(myQuery);

    }
    else
    {
        myQuery =
                "UPDATE artikelbeheer.ingredienten_artikel "
                "SET artikel_id = :v_artikel_id, "
                    "ingredient_id = :v_ingredient_id, "
                    "hoeveelheid = :v_hoeveelheid "
                "WHERE (ingredient__artikel_id = :v_ingredient__artikel_id);";

        qry.prepare(myQuery);
        qry.bindValue(":v_ingredient__artikel_id", Ingredient_Artikel_ID);
    }

    qry.bindValue(":v_artikel_id", Artikel_ID);
    qry.bindValue(":v_ingredient_id", Ingredient_ID);
    qry.bindValue(":v_hoeveelheid", Hoeveelheid);

    if (qry.exec())
    {
        if (Ingredient_Artikel_ID == 0)
        {
            Ingredient_Artikel_ID = qry.lastInsertId().toInt();
        }
    }
    else
    {
        qDebug() << "Database error (Ingredienten per artikel): " << qry.lastError().databaseText() << "\nQuerry error: " << qry.lastError().text();
    }

}

void Ingredient_Artikel::read()
{
    QString myQuery;
    QSqlQuery qry;
    bool status;

    myQuery = "SELECT * FROM artikelbeheer.ingredienten_artikel "
              "WHERE ingredient__artikel_id=:v_ingredient__artikel_id; ";

    qry.prepare(myQuery);
    qry.bindValue(":v_ingredient__artikel_id", Ingredient_Artikel_ID);
    status = qry.exec();
    if (status )
    {
        status = qry.next();
        if (status )
        {
            Ingredient_Artikel_ID = qry.value("ingredient__artikel_id").toInt();
            Artikel_ID = qry.value("artikel_id").toInt();
            Ingredient_ID = qry.value("ingredient_id").toInt();
            Hoeveelheid = qry.value("hoeveelheid").toDouble();
        }
        else
        {
            qDebug() << "Error bij lezen Ingredienten per artikel record (of geen record gevonden)- " << qry.lastError().text();
        }
    }
    else
    {
        Ingredient_Artikel_ID = 0;
        qDebug() << "Database error (Ingredienten per artikel): " << qry.lastError().databaseText() << "\nQuerry error: " << qry.lastError().text();
    }
}

void Ingredient_Artikel::clear()
{
    Ingredient_Artikel_ID = 0;
    Artikel_ID = 0;
    Hoeveelheid = 0;
}

//====================================================================================================
//   Static Methods
//


void Ingredient_Artikel::deleteIngredientenPerArtikel(int _id)
{
    QString myQuery;
    QSqlQuery qry;

    myQuery =
    "DELETE FROM artikelbeheer.ingredienten_artikel "
    "WHERE "
      "(ingredient__artikel_id=:v_ingredient__artikel_id); ";

    qry.prepare(myQuery);
    qry.bindValue(":v_ingredient__artikel_id", _id);
    bool status = qry.exec();
    if (!status)
    {
        qDebug() << "Error bij wissen Ingredienten per artikel record- " << qry.lastError().text();
    }
}

void Ingredient_Artikel::getIngredientenPerArtikel(QSqlQueryModel *_model, int _art_id)
{
    QString myQuery;
    QSqlQuery qry;

    myQuery =
    "SELECT "
      "ingredienten_artikel.ingredient__artikel_id, "
      "ingredienten_artikel.artikel_id, "
      "ingredienten.ingredient_omschrijving, "
      "ingredienten_artikel.hoeveelheid "
    "FROM "
      "artikelbeheer.ingredienten_artikel, "
      "artikelbeheer.ingredienten "
    "WHERE "
      "ingredienten_artikel.ingredient_id = ingredienten.ingredient_id AND "
      "ingredienten_artikel.artikel_id = :v_artikel_id "
    "ORDER BY "
      "ingredienten.ingredient_omschrijving ASC ; ";

    qry.prepare(myQuery);
    qry.bindValue(":v_artikel_id", _art_id);
    qry.exec();
    _model->setQuery(qry);
}
