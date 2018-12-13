#ifndef ADDSPECIFICATIE_H
#define ADDSPECIFICATIE_H

#include "specificaties.h"
#include <QDialog>
#include <QSqlQueryModel>


namespace Ui {
class AddSpecificatie;
}

class AddSpecificatie : public QDialog
{
    Q_OBJECT

public:
    explicit AddSpecificatie(QWidget *parent = 0);
    ~AddSpecificatie();

    void setIDs(int _product_id, int _soort_id, int _detail_id);

private slots:
    void on_btnNieuw_clicked();
    void on_btnBewerk_clicked();
    void on_btnOpslaan_clicked();
    void on_btnStop_clicked();

private:
    Ui::AddSpecificatie *ui;
    int Product_ID;
    int Soort_ID;
    int Detail_ID;
    Specificaties *spec;

    QSqlQueryModel *prd_model;
    QSqlQueryModel *Soort_Model;
    QSqlQueryModel *Detail_Model;
    QSqlQueryModel *Spec_Model;
};

#endif // ADDSPECIFICATIE_H
