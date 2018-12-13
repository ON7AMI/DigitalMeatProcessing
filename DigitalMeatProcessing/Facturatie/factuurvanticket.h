#ifndef FACTUURVANTICKET_H
#define FACTUURVANTICKET_H


#include <QDialog>

#include <QSqlQueryModel>

namespace Ui {
class FactuurVanTicket;
}

class FactuurVanTicket : public QDialog
{
    Q_OBJECT

public:
    explicit FactuurVanTicket(int _FactuurID, int _KlantID, QWidget *parent = 0);
    ~FactuurVanTicket();

private slots:
    void on_tvTeFactureren_clicked(const QModelIndex &index);

    void on_btnAnuleren_clicked();

    void on_btnOvernemen_clicked();

private:
    int FactuurID;
    int TicketID;
    int KlantID;
    Ui::FactuurVanTicket *ui;
    QSqlQueryModel* TeFacturerenModel;

    void FillTicket(int _id);
};

#endif // FACTUURVANTICKET_H
