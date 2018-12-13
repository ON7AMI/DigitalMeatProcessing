#ifndef INGREDIENTEN_H
#define INGREDIENTEN_H

#include <QObject>
#include <QSqlQueryModel>

class Ingredienten
{
public:
    Ingredienten();
    Ingredienten(int _id);

    void setIngredient_ID(int _id);         int getIngredient_ID();
    void setOmschrijving(QString _omschr);  QString getOmschrijving();

    void save();
    void clear();

private:
    int Ingredient_ID;          // ingredient_id serial NOT NULL,
    QString Omschrijving;       // ingredient_omschrijving character varying,

    void read();

public:   // statics
    static void getAllIngredienten(QSqlQueryModel* _model);
    static void deleteIngredient(int _id);

};

#endif // INGREDIENTEN_H
