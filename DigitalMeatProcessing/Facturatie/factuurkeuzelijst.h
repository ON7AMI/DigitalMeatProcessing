#ifndef FACTUURKEUZELIJST_H
#define FACTUURKEUZELIJST_H

#include <QDialog>
#include <QSqlQueryModel>

#include "factuurheader.h"

namespace Ui {
class FactuurKeuzeLijst;
}

class FactuurKeuzeLijst : public QDialog
{
    Q_OBJECT

public:
    explicit FactuurKeuzeLijst(QWidget *parent = 0);
    ~FactuurKeuzeLijst();

private slots:
    void on_tvFactuurLijst_doubleClicked(const QModelIndex &index);

    void on_pushButton_clicked();

private:
    Ui::FactuurKeuzeLijst *ui;

    void FillTable();
    QSqlQueryModel* Facturen_model;

};

#endif // FACTUURKEUZELIJST_H
