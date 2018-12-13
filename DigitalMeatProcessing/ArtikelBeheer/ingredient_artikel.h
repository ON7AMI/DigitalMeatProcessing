#ifndef INGREDIENT_ARTIKEL_H
#define INGREDIENT_ARTIKEL_H

#include <QSqlQueryModel>

class Ingredient_Artikel
{
public:
    Ingredient_Artikel();
    Ingredient_Artikel(int _id);

    void setIngredient_Artikel_ID(int _id);         int getIngredient_Artikel_ID();
    void setArtikel_ID(int _id);                    int getArtikel_ID();
    void setIngredient_ID(int _id);                 int getIngredient_ID();
    void setHoeveelheid(double _hoeveel);           double getHoeveelheid();

    void save();

public: // static
    static void getIngredientenPerArtikel( QSqlQueryModel* _model, int _art_id );
    static void deleteIngredientenPerArtikel(int _id);

private:
    int Ingredient_Artikel_ID;
    int Artikel_ID;
    int Ingredient_ID;
    double Hoeveelheid;

    void read();
    void clear();
};

#endif // INGREDIENT_ARTIKEL_H
