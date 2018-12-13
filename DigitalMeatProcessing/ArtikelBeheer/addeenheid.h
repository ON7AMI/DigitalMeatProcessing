#ifndef ADDEENHEID_H
#define ADDEENHEID_H

#include "comeenheden.h"

#include <QDialog>
#include <QSqlQueryModel>


namespace Ui {
class AddEenheid;
}

class AddEenheid : public QDialog
{
    Q_OBJECT

public:
    explicit AddEenheid(QWidget *parent = 0);
    ~AddEenheid();



private slots:
    void on_btnStop_clicked();
    void on_btnNieuw_clicked();
    void on_btnBewerk_clicked();
    void on_btnOpslaan_clicked();

private:
    Ui::AddEenheid *ui;
    ComEenheden *ce;

    QSqlQueryModel *ce_Model;
};

#endif // ADDEENHEID_H
