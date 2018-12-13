#ifndef KASSA_H
#define KASSA_H

#include "ticket.h"
#include "tickerow.h"
#include "ticketline.h"

#include <QDialog>
#include <QTimer>

namespace Ui {
class Kassa;
}

class Kassa : public QDialog
{
    Q_OBJECT

public:
    explicit Kassa(QWidget *parent = 0);
    ~Kassa();

private slots:
    void SchrijfDisplay();
    void on_btnStop_clicked();
    void on_btnPrintTicket_clicked();
    void on_lbAfrekenen_clicked();
    void on_btnContant_clicked();
    void on_btnBankcontact_clicked();
    void on_btnKredietkaart_clicked();
    void on_btntegoedbon_clicked();
    void on_btnMaaltijdcheque_clicked();
    void on_btnMCPlus_clicked();
    void on_btnMCmin_clicked();
    void on_btnUitgaven_clicked();
    void on_btnReken_clicked();
    void on_btnKladPrint_clicked();
    void on_btnSelect_0_clicked();
    void on_btnSelect_1_clicked();
    void on_btnSelect_2_clicked();
    void on_btnSelect_3_clicked();
    void on_btnSelect_4_clicked();
    void on_btnSelect_5_clicked();
    void on_btnSelect_6_clicked();
    void on_btnSelect_7_clicked();

    void on_btnAnuleren_clicked();

    void on_btnNaarFactuur_clicked();

private:
    Ui::Kassa *ui;
    Ticket* ticket;
    TickeRow* ticketRow;
    QTimer* DisplayTimer;
    QSqlQueryModel* UitgaveReden_model;


    QString SoortDoc;
    int SelectedTicketID;
    QString m_sSettingsFile;

    double TeBetalen;
    double ReedsBetaald;
    double Rest;
    // double NogTeOntvangen;
    double Contant;
    double Bankcontact;
    double Kredietkaart;
    double Maaltijdcheques;
    double MCeenheidsprijs;
    double Factuur;
    int MCaantal;
    double Tegoedbon;
    QDateTime timestamp;

    void FillTicketsList();
    void FillTicket();
    void ClearFields();
    void UpdateDisplay();
    void HerrekenBetaling();
    void PrintTicket();
    void BoekKasboek();
    void PasStockAan();
    void Afrekenen();

};

#endif // KASSA_H
