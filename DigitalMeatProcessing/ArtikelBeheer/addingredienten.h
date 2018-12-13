#ifndef ADDINGREDIENTEN_H
#define ADDINGREDIENTEN_H

#include "ingredienten.h"
#include "ingredient_artikel.h"

#include <QDialog>
#include <QSqlQueryModel>
#include <QDate>

namespace Ui {
class AddIngredienten;
}

class AddIngredienten : public QDialog
{
    Q_OBJECT

public:
    //explicit AddIngredienten(QWidget *parent = 0);
    explicit AddIngredienten(int _artID, QWidget *parent = 0);
    ~AddIngredienten();

private slots:
    void on_btnStop_clicked();
    void on_btnNew_clicked();
    void on_btnEdit_clicked();
    void on_btnSave_clicked();
    void on_btnToevoegen_clicked();
    void on_btnDelete_clicked();

    void on_tbHoeveelheid_editingFinished();

private:
    Ui::AddIngredienten *ui;

    QSqlQueryModel* tv_model;
    QSqlQueryModel* ing_model;

    Ingredient_Artikel* ing_art;
    Ingredienten* ing;
    int Artikel_ID;

    void FillTabel();
    void FillIngredienten();
};

#endif // ADDINGREDIENTEN_H
