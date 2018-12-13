#ifndef BETAALMIDDEL_H
#define BETAALMIDDEL_H

#include <QDialog>
#include <QSqlQueryModel>
#include <QDateTime>

#include "Boekhouding/kasboek.h"

namespace Ui {
class Betaalmiddel;
}

class Betaalmiddel : public QDialog
{
    Q_OBJECT

public:
    explicit Betaalmiddel(QDateTime datum ,QWidget *parent = 0);
    ~Betaalmiddel();

private slots:
    void on_btnSluiten_clicked();

    void on_tvLijst_doubleClicked(const QModelIndex &index);

    void on_btnOpslaan_clicked();

private:
    Ui::Betaalmiddel *ui;
    QDateTime Datum;
    QSqlQueryModel* Kasboek_Model;
    QSqlQueryModel* Betaalmiddel_Model;
    Kasboek* kb;

    void Fill();
};

#endif // BETAALMIDDEL_H
