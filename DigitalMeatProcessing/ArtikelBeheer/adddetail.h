#ifndef ADDDETAIL_H
#define ADDDETAIL_H

#include "details.h"
#include <QDialog>
#include <QSqlQueryModel>

namespace Ui {
class adddetail;
}

class AddDetail : public QDialog
{
    Q_OBJECT

public:
    explicit AddDetail(QWidget *parent = 0);
    ~AddDetail();

    void setIDs(int _product_id, int _soort_id);

private slots:
    void on_btnStop_clicked();
    void on_btnNieuw_clicked();
    void on_btnBewerk_clicked();
    void on_btnOpslaan_clicked();

private:
    Ui::adddetail *ui;
    int Product_ID;
    int Soort_ID;
    Details *det;

    QSqlQueryModel *prd_model;
    QSqlQueryModel *Soort_Model;
    QSqlQueryModel *Detail_Model;
};

#endif // ADDDETAIL_H
