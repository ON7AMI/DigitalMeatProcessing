#ifndef LEVERINGENLIJST_H
#define LEVERINGENLIJST_H

#include <QDialog>
#include <QSqlQueryModel>
#include <QDateTime>

namespace Ui {
class LeveringenLijst;
}

class LeveringenLijst : public QDialog
{
    Q_OBJECT

public:
    explicit LeveringenLijst(QWidget *parent = 0);
    ~LeveringenLijst();

private slots:
    void on_btnExit_clicked();

    void on_btnRefresh_clicked();

    void on_dtpTotDatum_editingFinished();

    void on_dtpVanDatum_editingFinished();

    void on_btnZoek_clicked();

    void on_btnAdd_clicked();

    void on_tvLeveringenLijst_doubleClicked(const QModelIndex &index);

private:
    Ui::LeveringenLijst *ui;

    void FillTable();
    void RefreshTable();
    QSqlQueryModel* Leveringenen_model;
    int Lev_ID;
    int SelLev_ID;
    QDate StartDatum;
    QDate EindDatum;
};

#endif // LEVERINGENLIJST_H
