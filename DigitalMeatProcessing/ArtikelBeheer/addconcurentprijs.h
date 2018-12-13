#ifndef ADDCONCURENTPRIJS_H
#define ADDCONCURENTPRIJS_H

#include "Relaties/relaties.h"
#include "prijzenconcurentie.h"

#include <QDialog>
#include <QSqlQueryModel>
#include <QDate>

namespace Ui {
class AddConcurentPrijs;
}

class AddConcurentPrijs : public QDialog
{
    Q_OBJECT

public:
    explicit AddConcurentPrijs(int _id, QWidget *parent = 0);
    ~AddConcurentPrijs();

private slots:
    void on_btnStop_clicked();
    void on_btnNew_clicked();
    void on_btnZoek_clicked();
    void on_btnSave_clicked();
    void on_btnEdit_clicked();
    void on_btnWis_clicked();
    void on_btnDelete_clicked();

private:
    Ui::AddConcurentPrijs *ui;

    QSqlQueryModel* tv_model;
    QSqlQueryModel* Gemeenten_model;

    PrijzenConcurentie* pc;
    Relaties* rel;
    int Artikelen_ID;

    void FillTabel();
};

#endif // ADDCONCURENTPRIJS_H
