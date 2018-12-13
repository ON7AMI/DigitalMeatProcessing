#ifndef ADDBTWTARIEF_H
#define ADDBTWTARIEF_H

#include "btwtarieven.h"

#include <QDialog>
#include <QSqlQueryModel>

namespace Ui {
class AddBTWTarief;
}

class AddBTWTarief : public QDialog
{
    Q_OBJECT

public:
    explicit AddBTWTarief(QWidget *parent = 0);
    ~AddBTWTarief();

private slots:
    void on_btnStop_clicked();
    void on_btnNieuw_clicked();
    void on_btnBewerk_clicked();
    void on_btnOpslaan_clicked();

private:
    Ui::AddBTWTarief *ui;
    BTWTarieven *BTW;

    QSqlQueryModel *BTW_Model;

};

#endif // ADDBTWTARIEF_H
