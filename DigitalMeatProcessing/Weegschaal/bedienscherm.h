#ifndef BEDIENSCHERM_H
#define BEDIENSCHERM_H

#include "weegschaal.h"
#include "ticket.h"
#include "ticketline.h"
#include "klantenscherm.h"

#include "ArtikelBeheer/artikelen.h"
#include "ArtikelBeheer/producten.h"
#include "ArtikelBeheer/soorten.h"
#include "ArtikelBeheer/details.h"
#include "ArtikelBeheer/specificaties.h"
#include "Productie/lotnummerdata.h"

#include <QDialog>
#include <QtSerialPort/QSerialPortInfo>
#include <QtSerialPort/QSerialPort>
#include <QtSerialPort/QSerialPortInfo>
#include <QTimer>
#include <QButtonGroup>




namespace Ui {
class BedienScherm;
}

class BedienScherm : public QDialog
{
    Q_OBJECT

public:
    explicit BedienScherm(QWidget *parent = 0);
    ~BedienScherm();

protected:
    bool eventFilter(QObject *obj, QEvent *ev);

private slots:
    void on_btnStop_clicked();
    void LeesWeegschaal();
    void SchrijfDisplay();
    void on_tbArtikelnummer_editingFinished();
    void on_btnZoek_Art_clicked();
    void onGroupArtikelButtonClicked(int);
    void on_btnWis_Art_clicked();
    void on_btnScan_clicked();
    void on_btnTarra_clicked();
    void on_btnNieuw_clicked();
    void on_btnToevoegen_clicked();
    void on_btnTarra_2_clicked();
    void on_btnSchrapLijn_clicked();
    void on_btnAnnuleer_clicked();
    void on_btnNaarKassa_clicked();
    void on_btnLaatsteTicket_clicked();
    void on_btnPrintLabel_clicked();
    void CheckPresoneelsWissel();
    void on_btnPer1_clicked();
    void on_btnPer2_clicked();
    void on_btnPer3_clicked();
    void on_btnPer4_clicked();
    void on_btnPer5_clicked();
    void on_btnPer6_clicked();

    void on_btnBestelNummer_clicked();
    void on_btnBestellingOpslaan_clicked();
    void on_btnZoekBestelling_clicked();

    void on_btnPrintBestelling_clicked();

    void on_btnPrintBestelLabel_clicked();

private:
    Ui::BedienScherm *ui;
    QString test;

    Artikelen* art;
    int CurrentArt;
    LotnummerData* lotnr;

    int ArtikelFase;

    QString LabelProduct;
    QString LabelHoeveel;
    QString LabelPrijs;

    Weegschaal* ws;
    Ticket* ticket;
    TicketLine* ticketline;
    QString m_sSettingsFile;
    QSerialPort sp;
    QTimer* WeegTimer;
    QTimer* DisplayTimer;
    QTimer* PersoneelTimer;

    KlantenScherm* kls;

    QButtonGroup* btngrpKiesArtikel;
    QButtonGroup* btngrpPersoneel;

    QObject* CurObj;
    QString CurObjNaam;

    void FillArtikelFields();
    void FillTicket();
    void FillArtikelButtonGroup();
    bool AdjustSamenstelling(QString _code);
    void HideAllButtons();
    void ShowProductButtons();
    void ShowSoortButtons();
    void ShowDetailButtons();
    void ShowSpecificatieButtons();
    void ShowPersoneelButtons();
    void UncheckPersoneelsButtons();
    void CheckPersoneelsButton(int _id);
    void CheckOpenTicket();
    void CheckLotnummer();
    void PrintBestelTicket();
};

#endif // BEDIENSCHERM_H

