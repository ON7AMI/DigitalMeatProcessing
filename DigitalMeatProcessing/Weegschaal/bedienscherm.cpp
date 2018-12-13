#include "bedienscherm.h"
#include "ui_bedienscherm.h"
#include "tickerow.h"
#include "klantenscherm.h"
#include "CommonObjects/btwtarieven.h"
#include "CommonObjects/personeel.h"
#include "ArtikelBeheer/comeenheden.h"
#include "ArtikelBeheer/producten.h"
#include "ArtikelBeheer/soorten.h"
#include "ArtikelBeheer/details.h"
#include "ArtikelBeheer/specificaties.h"
#include "CommonObjects/numkeyboard.h"

#include <QObject>
#include <QDebug>
#include <QApplication>
#include <QSettings>
#include <QLocale>
#include <QDialog>
#include <QDateTime>
#include <QKeyEvent>
#include <QMessageBox>
#include <QSpacerItem>
#include <QGridLayout>
#include <QSqlRecord>
#include <QSqlField>
#include <QListWidgetItem>
#include <QInputDialog>
#include <QDesktopWidget>
#include <QPrinter>
#include <QPainter>
#include <QRect>

BedienScherm::BedienScherm(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::BedienScherm)
{
    ui->setupUi(this);

    QDesktopWidget w;
    int numscreens;
    numscreens = w.numScreens();
//    numscreens = w.screenCount();
//    numscreens = w.screenNumber(this);
    QRect screenres = QApplication::desktop()->screenGeometry(0/*screenNumber*/);
    screenres = QApplication::desktop()->screenGeometry(1/*screenNumber*/);
    this->setWindowFlags(Qt::Window | Qt::FramelessWindowHint);
    this->showFullScreen();

    m_sSettingsFile = QApplication::applicationDirPath() + "/appSettings.ini";
    QSettings settings(m_sSettingsFile, QSettings::NativeFormat);

    ws = new Weegschaal();
    ws->Tarra = 0;
    ws->NummerWeegschaal = settings.value("Diverse/NummerKassa").toInt();
    ws->HuidigeGebruiker = 0;
    ws->Bestelling = 0;

    UncheckPersoneelsButtons();

    QString PortNaam = settings.value("Weegschaal/Winkel", "").toString();

    sp.setPortName(PortNaam);
    sp.setBaudRate(QSerialPort::Baud9600);
    sp.setDataBits(QSerialPort::Data8);
    sp.setFlowControl(QSerialPort::NoFlowControl);
    sp.setParity(QSerialPort::NoParity);
    sp.setStopBits(QSerialPort::OneStop);

    WeegTimer = new QTimer(this);
    connect(WeegTimer, SIGNAL(timeout()), this, SLOT(LeesWeegschaal()));
    WeegTimer->start(450);

    DisplayTimer = new QTimer(this);
    connect(DisplayTimer, SIGNAL(timeout()), this, SLOT(SchrijfDisplay()));
    DisplayTimer->start(500);

    PersoneelTimer = new QTimer(this);
    connect(PersoneelTimer, SIGNAL(timeout()), this, SLOT(CheckPresoneelsWissel()));
    PersoneelTimer->start(715);

    ui->tbDiversePrijs->setVisible(false);
    ui->tbDiversePrijs->installEventFilter(this);

    ws->PrijsPerEenheid = 0;
    ws->ProductBenaming = "";
    ws->VerkoopsEenheid = "Kg";
    ws->Promo = false;
    ui->lbPromo->setVisible(ws->Promo);
    ui->tbArtikelnummer->installEventFilter(this);
    ui->tbAantal->setText("1");
    ui->tbAantal->installEventFilter(this);

    ArtikelFase = 1;
    ws->Product_ID = 0;
    ws->Soort_ID = 0;
    ws->Detail_ID = 0;
    ui->frm_art_1->setVisible(false);
    ui->frm_art_2->setVisible(false);
    ui->frm_art_3->setVisible(false);
    ui->frm_art_4->setVisible(false);

    btngrpKiesArtikel = new QButtonGroup();
    FillArtikelButtonGroup();
    HideAllButtons();
    ShowProductButtons();
    connect(btngrpKiesArtikel, SIGNAL(buttonClicked(int)), this, SLOT(onGroupArtikelButtonClicked(int)));

    ShowPersoneelButtons();
    ws->PersID = 0;
    ws->PersNaam = "";
    ws->PersWissel = 0;
    ui->lbVerkoperNaam->setText(QString("U wordt geholpen door: %1").arg(ws->PersNaam));


    if (numscreens >= 2)
    {
        kls = new KlantenScherm(ws, this);
        kls->show();
    }
}


BedienScherm::~BedienScherm()
{
    kls->close();


    delete ui;
    delete ws;

    delete WeegTimer;
    delete DisplayTimer;
    delete art;
    delete lotnr;
    delete ws;
    delete ticket;
    delete ticketline;
    delete WeegTimer;
    delete DisplayTimer;
    delete btngrpKiesArtikel;
    delete CurObj;
    delete kls;
}

void BedienScherm::CheckPresoneelsWissel()
{
    int id = Personeel::getSalesmenOnBalance(ws->NummerWeegschaal);
    if (id != ws->PersID)
    {
        Personeel per(id);
        ws->PersID = per.getPersoneel_ID();
        ws->PersNaam = per.getVoornaam();
        ui->lbVerkoperNaam->setText(QString("U wordt geholpen door: %1").arg(ws->PersNaam));
        // check op open ticket
        CheckOpenTicket();
        ws->PersWissel++;
        UncheckPersoneelsButtons();
        CheckPersoneelsButton(id);
        CheckOpenTicket();
        FillTicket();
    }
}


void BedienScherm::FillArtikelButtonGroup()
{
    btngrpKiesArtikel->addButton(ui->btnKies_1,1);
    btngrpKiesArtikel->addButton(ui->btnKies_2,2);
    btngrpKiesArtikel->addButton(ui->btnKies_3,3);
    btngrpKiesArtikel->addButton(ui->btnKies_4,4);
    btngrpKiesArtikel->addButton(ui->btnKies_5,5);
    btngrpKiesArtikel->addButton(ui->btnKies_6,6);
    btngrpKiesArtikel->addButton(ui->btnKies_7,7);
    btngrpKiesArtikel->addButton(ui->btnKies_8,8);
    btngrpKiesArtikel->addButton(ui->btnKies_9,9);
    btngrpKiesArtikel->addButton(ui->btnKies_10,10);
    btngrpKiesArtikel->addButton(ui->btnKies_11,11);
    btngrpKiesArtikel->addButton(ui->btnKies_12,12);
    btngrpKiesArtikel->addButton(ui->btnKies_13,13);
    btngrpKiesArtikel->addButton(ui->btnKies_14,14);
    btngrpKiesArtikel->addButton(ui->btnKies_15,15);
    btngrpKiesArtikel->addButton(ui->btnKies_16,16);
    btngrpKiesArtikel->addButton(ui->btnKies_17,17);
    btngrpKiesArtikel->addButton(ui->btnKies_18,18);
    btngrpKiesArtikel->addButton(ui->btnKies_19,19);
    btngrpKiesArtikel->addButton(ui->btnKies_20,20);
    btngrpKiesArtikel->addButton(ui->btnKies_21,21);
    btngrpKiesArtikel->addButton(ui->btnKies_22,22);
    btngrpKiesArtikel->addButton(ui->btnKies_23,23);
    btngrpKiesArtikel->addButton(ui->btnKies_24,24);
    btngrpKiesArtikel->addButton(ui->btnKies_25,25);
    btngrpKiesArtikel->addButton(ui->btnKies_26,26);
    btngrpKiesArtikel->addButton(ui->btnKies_27,27);
    btngrpKiesArtikel->addButton(ui->btnKies_28,28);
    btngrpKiesArtikel->addButton(ui->btnKies_29,29);
    btngrpKiesArtikel->addButton(ui->btnKies_30,30);
    btngrpKiesArtikel->addButton(ui->btnKies_31,31);
    btngrpKiesArtikel->addButton(ui->btnKies_32,32);
    btngrpKiesArtikel->addButton(ui->btnKies_33,33);
    btngrpKiesArtikel->addButton(ui->btnKies_34,43);
    btngrpKiesArtikel->addButton(ui->btnKies_35,53);
    btngrpKiesArtikel->addButton(ui->btnKies_36,63);
    btngrpKiesArtikel->addButton(ui->btnKies_37,73);
    btngrpKiesArtikel->addButton(ui->btnKies_38,83);
    btngrpKiesArtikel->addButton(ui->btnKies_39,93);
    btngrpKiesArtikel->addButton(ui->btnKies_40,40);
}

void BedienScherm::CheckOpenTicket()
{
    int curticket = Ticket::CheckOpenTicket(ws->PersID);
    if (curticket == 0)
    {
        // Geen openstaande tickets
        ws->TicketID = 0;
        ws->Bestelling = 0;
        ws->TicketNummer = "";
        ui->btnNieuw->setEnabled(true);
        ui->btnLaatsteTicket->setEnabled(true);
        ui->btnNaarKassa->setEnabled(false);
        ui->btnAnnuleer->setEnabled(false);
        ui->btnToevoegen->setEnabled(false);
        ui->btnSchrapLijn->setEnabled(false);
    }
    else
    {
        // Haal bestaand ticket
        ticket = new Ticket(curticket);
        ws->TicketID = curticket;
        ws->TicketNummer = ticket->getVolgnummer();
        ws->Bestelling = ticket->getBestelling();
        ui->btnNieuw->setEnabled(false);
        ui->btnLaatsteTicket->setEnabled(false);
        ui->btnNaarKassa->setEnabled(true);
        ui->btnAnnuleer->setEnabled(true);
        ui->btnToevoegen->setEnabled(true);
        ui->btnSchrapLijn->setEnabled(false);
    }
    FillTicket();
}

void BedienScherm::FillTicket()
{
    ui->lbTicketNr->setText( QString("Ticket nummer: %1").arg(ws->TicketNummer));
    ui->lstwTicket->clear();

    QVariant nr;
    TickeRow* tr;
    QListWidgetItem *item;

    QSqlQueryModel* mod = new QSqlQueryModel();
    TicketLine::getLinesByTicketID(ws->TicketID, mod);

    double totaal = 0;

    if (mod->rowCount() > 0)
        ui->btnSchrapLijn->setEnabled(true);

    for(int i = 0; i < mod->rowCount() ; i++)
    {
        tr = new TickeRow();
        tr->setOmschrijving(mod->record(i).value("art_omschrijving").toString());
        tr->setHoeveelheid(QString("%1 %2").arg(mod->record(i).value("hoeveelheid").toDouble(), 0, 'f', 3).
                           arg(mod->record(i).value("eenheid").toString()));
        tr->setPrijs(QString("%1 €").arg(mod->record(i).value("prijs_incl_btw").toDouble(), 0,'f',2));
        totaal += mod->record(i).value("prijs_incl_btw").toDouble();
        item = new QListWidgetItem();
        item->setSizeHint(QSize(0,65));
        //item->setStatusTip("test1");
        nr = mod->record(i).value("ticket_line_id").toInt();
        item->setData(Qt::UserRole, nr);
        ui->lstwTicket->insertItem(0,item);
        ui->lstwTicket->setItemWidget(item,tr);
    }
    ui->lbToaal->setText(QString("%1 €").arg(totaal, 0,'f',2));
    //ui->grboxBestelling->setTitle(QString("Bestelling nr.: %1").arg(ws->Bestelling));
    ui->tbBestelling->setText(QString("%1").arg(ws->Bestelling));
}



void BedienScherm::onGroupArtikelButtonClicked(int _id)
{
    QString artnr;
    switch (ArtikelFase) {
    case 1:
        artnr = "000000";
        artnr = artnr.replace(0,1,btngrpKiesArtikel->button(_id)->toolTip());
        ui->tbArtikelnummer->setText(artnr);
        ArtikelFase = 2;
        ui->frm_art_1->setVisible(true);
        ui->lbProduct_2->setText(btngrpKiesArtikel->button(_id)->text());
        ws->Product_ID = Producten::getProduct_IDbyCode(btngrpKiesArtikel->button(_id)->toolTip());
        HideAllButtons();
        ShowSoortButtons();
        break;

    case 2:
        artnr = ui->tbArtikelnummer->text();
        artnr = artnr.replace(2,1,btngrpKiesArtikel->button(_id)->toolTip());
        ui->tbArtikelnummer->setText(artnr);
        ArtikelFase = 3;
        ui->frm_art_2->setVisible(true);
        ui->lbSoort->setText(btngrpKiesArtikel->button(_id)->text());
        ws->Soort_ID = Soorten::getSoort_IDbyCode(btngrpKiesArtikel->button(_id)->toolTip(), ws->Product_ID);
        HideAllButtons();
        ShowDetailButtons();
        break;

    case 3:
        artnr = ui->tbArtikelnummer->text();
        artnr = artnr.replace(4,2,btngrpKiesArtikel->button(_id)->toolTip());
        ui->tbArtikelnummer->setText(artnr);
        ArtikelFase = 4;
        ui->frm_art_3->setVisible(true);
        ui->lbDetails->setText(btngrpKiesArtikel->button(_id)->text());
        ws->Detail_ID = Details::getDetail_IDbyCode(btngrpKiesArtikel->button(_id)->toolTip(), ws->Product_ID, ws->Soort_ID);
        HideAllButtons();
        ShowSpecificatieButtons();
        break;

    case 4:
        artnr = ui->tbArtikelnummer->text();
        artnr = artnr.replace(7,2,btngrpKiesArtikel->button(_id)->toolTip());
        ui->tbArtikelnummer->setText(artnr);
        ArtikelFase = 4;
        ui->frm_art_4->setVisible(true);
        ui->lbSpecificaties->setText(btngrpKiesArtikel->button(_id)->text());
        on_btnZoek_Art_clicked();
        break;

    default:
        break;
    }
}

void BedienScherm::HideAllButtons()
{
    int i = 0;
    foreach (QAbstractButton* pb, btngrpKiesArtikel->buttons()) {
        btngrpKiesArtikel->setId(pb,i++);
        pb->setVisible(false);
    }
}


void BedienScherm::ShowDetailButtons()
{
    QSqlQueryModel sModel;
    Details::getAllDetails(&sModel, ws->Product_ID, ws->Soort_ID);
    QString btnTekst = "";
    for(int i = 0; i < sModel.rowCount() && i < btngrpKiesArtikel->buttons().count(); i++)
    {
        btngrpKiesArtikel->button(i)->setVisible(true);
        btnTekst = QString("%1.\n%2").arg(sModel.record(i).value("detail_code").toString()).arg(sModel.record(i).value("detail_benaming").toString());
        btngrpKiesArtikel->button(i)->setText(btnTekst);
        btngrpKiesArtikel->button(i)->setToolTip(sModel.record(i).value("detail_code").toString());
    }
}

void BedienScherm::ShowSpecificatieButtons()
{
    QSqlQueryModel sModel;
    Specificaties::getAllSpecificaties(&sModel, ws->Product_ID, ws->Soort_ID, ws->Detail_ID);
    QString btnTekst = "";
    for(int i = 0; i < sModel.rowCount() && i < btngrpKiesArtikel->buttons().count(); i++)
    {
        btngrpKiesArtikel->button(i)->setVisible(true);
        btnTekst = QString("%1.\n%2").arg(sModel.record(i).value("specificatie_code").toString()).arg(sModel.record(i).value("specificatie_benaming").toString());
        btngrpKiesArtikel->button(i)->setText(btnTekst);
        btngrpKiesArtikel->button(i)->setToolTip(sModel.record(i).value("specificatie_code").toString());
    }
}

void BedienScherm::ShowProductButtons()
{
    QSqlQueryModel pModel;
    Producten::getAllProducten(&pModel);
    QString btnTekst = "";
    for(int i = 0; i < pModel.rowCount() && i < btngrpKiesArtikel->buttons().count(); i++)
    {
        btngrpKiesArtikel->button(i)->setVisible(true);
        btnTekst = QString("%1.\n%2").arg(pModel.record(i).value("product_code").toString()).arg(pModel.record(i).value("product_benaming").toString());
        btngrpKiesArtikel->button(i)->setText(btnTekst);
        btngrpKiesArtikel->button(i)->setToolTip(pModel.record(i).value("product_code").toString());
    }
}

void BedienScherm::ShowSoortButtons()
{
    QSqlQueryModel sModel;
    Soorten::getAllSoorten(&sModel, ws->Product_ID);
    QString btnTekst = "";
    for(int i = 0; i < sModel.rowCount() && i < btngrpKiesArtikel->buttons().count(); i++)
    {
        btngrpKiesArtikel->button(i)->setVisible(true);
        btnTekst = QString("%1.\n%2").arg(sModel.record(i).value("soort_code").toString()).arg(sModel.record(i).value("soort_benaming").toString());
        btngrpKiesArtikel->button(i)->setText(btnTekst);
        btngrpKiesArtikel->button(i)->setToolTip(sModel.record(i).value("soort_code").toString());
    }
}


void BedienScherm::ShowPersoneelButtons()
{
    QSqlQueryModel sModel;
    Personeel::getAllActiveSalesmen(&sModel);
    QString btnTekst = "";
    int AantalPers = sModel.rowCount();

    if (AantalPers >=1 )
    {
        ui->btnPer1->setVisible(true);
        btnTekst = QString("%1.\n%2").arg(sModel.record(0).value("volgnummer").toString()).arg(sModel.record(0).value("voornaam").toString());
        ui->btnPer1->setText(btnTekst);
        ui->btnPer1->setToolTip(sModel.record(0).value("personeel_id").toString());
    }
    else
    {
        ui->btnPer1->setVisible(false);
        btnTekst = "";
        ui->btnPer1->setText(btnTekst);
        ui->btnPer1->setToolTip("0");
    }

    if (AantalPers >=2 )
    {
        ui->btnPer2->setVisible(true);
        btnTekst = QString("%1.\n%2").arg(sModel.record(1).value("volgnummer").toString())
                .arg(sModel.record(1).value("voornaam").toString());
        ui->btnPer2->setText(btnTekst);
        ui->btnPer2->setToolTip(sModel.record(1).value("personeel_id").toString());
    }
    else
    {
        ui->btnPer2->setVisible(false);
        btnTekst = "";
        ui->btnPer2->setText(btnTekst);
        ui->btnPer2->setToolTip("0");
    }

    if (AantalPers >=3 )
    {
        ui->btnPer3->setVisible(true);
        btnTekst = QString("%1.\n%2").arg(sModel.record(2).value("volgnummer").toString())
                .arg(sModel.record(2).value("voornaam").toString());
        ui->btnPer3->setText(btnTekst);
        ui->btnPer3->setToolTip(sModel.record(2).value("personeel_id").toString());
    }
    else
    {
        ui->btnPer3->setVisible(false);
        btnTekst = "";
        ui->btnPer3->setText(btnTekst);
        ui->btnPer3->setToolTip("0");
    }

    if (AantalPers >=4 )
    {
        ui->btnPer4->setVisible(true);
        btnTekst = QString("%1.\n%2").arg(sModel.record(3).value("volgnummer").toString())
                .arg(sModel.record(3).value("voornaam").toString());
        ui->btnPer4->setText(btnTekst);
        ui->btnPer4->setToolTip(sModel.record(3).value("personeel_id").toString());
    }
    else
    {
        ui->btnPer4->setVisible(false);
        btnTekst = "";
        ui->btnPer4->setText(btnTekst);
        ui->btnPer4->setToolTip("0");
    }

    if (AantalPers >=5 )
    {
        ui->btnPer5->setVisible(true);
        btnTekst = QString("%1.\n%2").arg(sModel.record(4).value("volgnummer").toString())
                .arg(sModel.record(4).value("voornaam").toString());
        ui->btnPer5->setText(btnTekst);
        ui->btnPer5->setToolTip(sModel.record(4).value("personeel_id").toString());
    }
    else
    {
        ui->btnPer5->setVisible(false);
        btnTekst = "";
        ui->btnPer5->setText(btnTekst);
        ui->btnPer5->setToolTip("0");
    }

    if (AantalPers >=6 )
    {
        ui->btnPer6->setVisible(true);
        btnTekst = QString("%1.\n%2").arg(sModel.record(5).value("volgnummer").toString())
                .arg(sModel.record(5).value("voornaam").toString());
        ui->btnPer6->setText(btnTekst);
        ui->btnPer6->setToolTip(sModel.record(5).value("personeel_id").toString());
    }
    else
    {
        ui->btnPer6->setVisible(false);
        btnTekst = "";
        ui->btnPer6->setText(btnTekst);
        ui->btnPer6->setToolTip("0");
    }
}

bool BedienScherm::eventFilter(QObject *obj, QEvent *ev)
{
    bool result = false;
    CurObj = 0;

    if (true) //(ev->type() == QEvent::FocusIn)
    {
        if (obj == ui->tbDiversePrijs)
        {
            if ((ev->type() == QEvent::MouseButtonPress) || (ev->type() == QEvent::TouchBegin))
            {
                qDebug() << "diverse prijs";
                CurObj = obj;
                CurObjNaam = obj->objectName();
            }
        }
        else if (obj == ui->tbArtikelnummer)
        {
            if ((ev->type() == QEvent::MouseButtonPress) || (ev->type() == QEvent::TouchBegin))
            {
                qDebug() << "artikelnummer";
                CurObj = obj;
                CurObjNaam = obj->objectName();
            }
        }
        else if (obj == ui->tbAantal)
        {
            if ((ev->type() == QEvent::MouseButtonPress) || (ev->type() == QEvent::TouchBegin))
            {
                qDebug() << "test1";
                CurObj = obj;
                CurObjNaam = obj->objectName();
            }
        }
        else
        {
            result = QDialog::eventFilter(obj, ev);
        }
    }
    else
        result = QDialog::eventFilter(obj, ev);

    if (CurObj != 0)
    {
        NumKeyboard* kb = new NumKeyboard(CurObj, this);
        kb->exec();
        if (obj == ui->tbDiversePrijs)
        {
            ws->PrijsPerEenheid = ui->tbDiversePrijs->text().toDouble();
            ws->PrijsPerEenheidExclBTW = ws->PrijsPerEenheid / (1+ws->BTWPercentage/100);
            ui->tbDiversePrijs->setVisible(false);
        }
    }
    return result;

}


void BedienScherm::LeesWeegschaal()
{
    QString prData = "";
    QByteArray data;
    if (sp.open(QIODevice::ReadWrite))
    {
        prData = "READ\r\n";
        sp.write(prData.toLatin1(),prData.length());
        if(!sp.waitForBytesWritten(2000))
            qDebug() << "timeout zenden" ;

        data.clear();
        if (sp.waitForReadyRead(2000))
        {
            while(sp.waitForReadyRead(10))
                data  += sp.readAll();
        }
        else
        {
            qDebug() << "timeout ontvangen";
        }
        QString antw(data);
        prData = antw;
        ws->status = antw.mid(0,2);
        ws->weegmethode = antw.mid(3,2);
        ws->gewicht = antw.mid(6,8);
        ws->Gewicht = antw.mid(6,8).toDouble();
        ws->eenheid = antw.mid(15,2);
        sp.close();
    }
    else
    {
        qDebug() << "Fout Seriele poort: " << sp.errorString() ;
    }
    ws->Aantal = ui->tbAantal->text().toInt();
}

void BedienScherm::SchrijfDisplay()
{
    double prijs;
    if (ws->VerkoopsEenheid == "Kg")
    {
        ui->lcdGewicht->display(QString("%1").arg((ws->Gewicht - ws->Tarra),10,'f',3));
        prijs = ws->PrijsPerEenheid * (ws->Gewicht - ws->Tarra);
    }
    else
    {
        ui->lcdGewicht->display(ws->Aantal);
        prijs = ws->PrijsPerEenheid * ws->Aantal;
    }
    ui->lbStatus->setText(ws->status);
    if (ws->status == "ST")
    {
        ui->frmStable->setStyleSheet("background-color: rgb(0, 255, 0);");
    }
    else
    {
        ui->frmStable->setStyleSheet("background-color: rgb(255, 0, 0);");
    }
    ui->lbPromo->setVisible(ws->Promo);
    ui->lbProduct->setText(ws->ProductBenaming);
    ui->lbKg->setText(ws->VerkoopsEenheid);
    ui->lbPrijspereenheid->setText(QString("Prijs per %1 aan %2 €.").arg(ws->VerkoopsEenheid).arg(ws->PrijsPerEenheid,0,'f',2));

    ui->lcdPrijs->display(QString("%1").arg(prijs,10,'f',2));
    ui->lcdklok->display(QString("%1").arg(QTime::currentTime().toString("hh:mm")));
}

void BedienScherm::on_btnStop_clicked()
{
    this->close();
}

bool BedienScherm::AdjustSamenstelling(QString _code)
{
    bool gelukt = true;
    return gelukt;
}

void BedienScherm::on_tbArtikelnummer_editingFinished()
{
    if (!AdjustSamenstelling(ui->tbArtikelnummer->text().remove(char('.'))))
    {
        QMessageBox msgBox;
        msgBox.setText("<strong>Onbekend Artikel !</strong>");
        msgBox.setInformativeText("De onderliggende categorieën van dit artikel bestaan niet.\nU moet die eerst aanmaken.");
        msgBox.setStandardButtons(QMessageBox::Cancel);
        msgBox.setDefaultButton(QMessageBox::Cancel);
        msgBox.setIcon(QMessageBox::Critical);
        msgBox.setWindowTitle("Opgepast !");
        //msgBox.setStyleSheet("min-width: 150px;");
        QSpacerItem *hs = new QSpacerItem(400, 0, QSizePolicy::Minimum, QSizePolicy::Expanding);
        QGridLayout *gl = (QGridLayout*)msgBox.layout();
        gl->addItem(hs, gl->rowCount(), 0, 1, gl->columnCount());
        msgBox.exec();
        ui->tbArtikelnummer->setText("000000");
        AdjustSamenstelling("000000");
    }
    if (ui->tbArtikelnummer->text() != "0.0.00.00")
    {
        on_btnZoek_Art_clicked();
    }

}

void BedienScherm::CheckLotnummer()
{
    if ((art->getCode() == "000001")
            || (art->getCode() == "000002")
            || (art->getCode() == "000003")
            || (art->getCode() == "000004")
            || (art->getCode() == "000005")
            || (art->getCode() == "000006")
            || (art->getCode() == "000007")
            || (art->getCode() == "000008")
            || (art->getCode() == "000009"))
    {
        ws->Lotnr = "";
        ws->LotnrID = 0;
    }
    else
    {
        int lot = LotnummerData::getLotInWinkel(art->getArtikel_ID());
        if (lot == 0)
        {
            // geen lotnummer voorhanden
            bool ok;
            // vraag om te scannen
            QString text = QInputDialog::getText(this, tr("Geen lotnummer gevonden !"),
                                                 tr("Scan nu het lotnummer om te verkopen.\nof druk 'cancel' om zonder lotnummer te verkopen"),
                                                 QLineEdit::Normal, "Scan Barcode", &ok);
            if (ok && !text.isEmpty())
            {
                // ja open zet in winkel en vul gegevens in
                lotnr = new LotnummerData(text);
                if (lotnr->getLotnummer_id() == 0)
                {
                    // lotnummer niet gevonden verkoop zonder lotnummer
                    // meld
                    QMessageBox msgBox;
                    msgBox.setText("<strong>Onbekend Lotnummer !</strong>");
                    msgBox.setInformativeText("Het opgegeven lotnummer is niet gevonden.\nHet artikel zal verkochtworden zonder lotnummer.");
                    msgBox.setStandardButtons(QMessageBox::Cancel);
                    msgBox.setDefaultButton(QMessageBox::Cancel);
                    msgBox.setIcon(QMessageBox::Critical);
                    msgBox.setWindowTitle("Opgepast !");
                    QSpacerItem *hs = new QSpacerItem(400, 0, QSizePolicy::Minimum, QSizePolicy::Expanding);
                    QGridLayout *gl = (QGridLayout*)msgBox.layout();
                    gl->addItem(hs, gl->rowCount(), 0, 1, gl->columnCount());
                    msgBox.exec();
                    ws->Lotnr = "";
                    ws->LotnrID = 0;
                }
                else
                {
                    if (lotnr->getArtikel_ID() == art->getArtikel_ID())
                    {
                        ws->LotnrID = lotnr->getLotnummer_id();
                        ws->Lotnr = lotnr->getLotnummer();
                        lotnr->setLocatie_ID(13);
                        lotnr->setLocatieVeranderdOp(QDateTime::currentDateTime());
                        lotnr->save();
                    }
                    else
                    {
                        QMessageBox msgBox;
                        msgBox.setText("<strong>Lotnummer van ander artikel !</strong>");
                        msgBox.setInformativeText("Het opgegeven lotnummer hoort niet bij dit artikel.\nHet artikel zal verkochtworden zonder lotnummer.");
                        msgBox.setStandardButtons(QMessageBox::Cancel);
                        msgBox.setDefaultButton(QMessageBox::Cancel);
                        msgBox.setIcon(QMessageBox::Critical);
                        msgBox.setWindowTitle("Opgepast !");
                        QSpacerItem *hs = new QSpacerItem(400, 0, QSizePolicy::Minimum, QSizePolicy::Expanding);
                        QGridLayout *gl = (QGridLayout*)msgBox.layout();
                        gl->addItem(hs, gl->rowCount(), 0, 1, gl->columnCount());
                        msgBox.exec();
                        ws->Lotnr = "";
                        ws->LotnrID = 0;
                    }
                }
            }
            else
            {
                // neen verkoop zonder lotnummer
                ws->Lotnr = "";
                ws->LotnrID = 0;
            }
        }
        else
        {
            lotnr = new LotnummerData(lot);
            ws->LotnrID = lot;
            ws->Lotnr = lotnr->getLotnummer();
        }
    }
}

void BedienScherm::on_btnZoek_Art_clicked()
{
    QString code;
    int id;
    code = ui->tbArtikelnummer->text().remove(char('.'));
    id = Artikelen::getArtikelIDByCode(code);
    if (id == 0)
    {
        // Artikel onbekend, wil je het aanmaken
        QMessageBox msgBox;
        msgBox.setText("<strong>Onbekend Artikel !</strong>");
        msgBox.setInformativeText("Artikel onbekend");
        msgBox.setStandardButtons(QMessageBox::Cancel);
        msgBox.setDefaultButton(QMessageBox::Cancel);
        msgBox.setIcon(QMessageBox::Warning);
        msgBox.setWindowTitle("Opgepast !");
        QSpacerItem *hs = new QSpacerItem(400, 0, QSizePolicy::Minimum, QSizePolicy::Expanding);
        QGridLayout *gl = (QGridLayout*)msgBox.layout();
        gl->addItem(hs, gl->rowCount(), 0, 1, gl->columnCount());
        msgBox.exec();
        //ClearArtikelFields();
    }
    else
    {
        art = new Artikelen(id);
        CheckLotnummer();
        FillArtikelFields();
        CurrentArt = id;
    }
}

void BedienScherm::FillArtikelFields()
{
    ws->Artikel_ID = art->getArtikel_ID();
    ws->ArtikelCode = art->getCode();
    ws->BTWPercentage = BTWTarieven::getBTWPercentage(art->getBTWVerkoop());
    ws->ProductBenaming = art->getBenaming();
    ws->VerkoopsEenheid = ComEenheden::getComEenheidsCode(art->getEenheidVerkoop());

    if ((art->getCode() == "000001")
            || (art->getCode() == "000002")
            || (art->getCode() == "000003")
            || (art->getCode() == "000004")
            || (art->getCode() == "000005")
            || (art->getCode() == "000006")
            || (art->getCode() == "000007")
            || (art->getCode() == "000008")
            || (art->getCode() == "000009"))
    {
        ui->tbDiversePrijs->setVisible(true);
    }
    else
    {
        ui->tbDiversePrijs->setVisible(false);
        if ((art->getPromoVan() <= QDate::currentDate()) & (art->getPromoTot() >= QDate::currentDate()))
        {
            ws->Promo = true;
            ws->PrijsPerEenheidExclBTW = art->getPromoPrijs();
            ws->PrijsPerEenheid = art->getPromoPrijs() * (1 + ws->BTWPercentage/100);
        }
        else
        {
            ws->Promo = false;
            ws->PrijsPerEenheidExclBTW = art->getVerkoopPrijs();
            ws->PrijsPerEenheid = art->getVerkoopPrijs() * (1 + ws->BTWPercentage/100);
        }
    }
    ui->tbAantal->setText("1");
}

void BedienScherm::on_btnWis_Art_clicked()
{
    ArtikelFase = 1;
    ws->Product_ID = 0;
    ws->Soort_ID = 0;
    ws->Detail_ID = 0;
    HideAllButtons();
    ui->frm_art_1->setVisible(false);
    ui->frm_art_2->setVisible(false);
    ui->frm_art_3->setVisible(false);
    ui->frm_art_4->setVisible(false);
    ShowProductButtons();
}

void BedienScherm::on_btnScan_clicked()
{
    bool ok;
    QString text = QInputDialog::getText(this, tr("Barcode"),
                                                  tr("Barcode:"),QLineEdit::Normal, "Scan Barcode", &ok);
    if (ok && !text.isEmpty())
    {
        if (text.length() == 6)
        {
            // Eigen artikelnummer gescand
            int id;
            id = Artikelen::getArtikelIDByCode(text);
            if (id == 0)
            {
                // Artikel onbekend, wil je het aanmaken
                QMessageBox msgBox;
                msgBox.setText("<strong>Onbekend Artikel !</strong>");
                msgBox.setInformativeText("Artikel onbekend");
                msgBox.setStandardButtons(QMessageBox::Cancel);
                msgBox.setDefaultButton(QMessageBox::Cancel);
                msgBox.setIcon(QMessageBox::Warning);
                msgBox.setWindowTitle("Opgepast !");
                QSpacerItem *hs = new QSpacerItem(400, 0, QSizePolicy::Minimum, QSizePolicy::Expanding);
                QGridLayout *gl = (QGridLayout*)msgBox.layout();
                gl->addItem(hs, gl->rowCount(), 0, 1, gl->columnCount());
                msgBox.exec();
                //ClearArtikelFields();
            }
            else
            {
                art = new Artikelen(id);
                CheckLotnummer();
                FillArtikelFields();
                ui->tbArtikelnummer->setText(art->getCode());
                CurrentArt = id;
            }
        }
        else
        {
            // zoek artikel met vreemde barcode
            art = new Artikelen("Barcode", text);
            CheckLotnummer();
            if (art->getArtikel_ID() == 0)
            {
                // Artikel onbekend, wil je het aanmaken
                QMessageBox msgBox;
                msgBox.setText("<strong>Onbekend Artikel !</strong>");
                msgBox.setInformativeText("Artikel onbekend");
                msgBox.setStandardButtons(QMessageBox::Cancel);
                msgBox.setDefaultButton(QMessageBox::Cancel);
                msgBox.setIcon(QMessageBox::Warning);
                msgBox.setWindowTitle("Opgepast !");
                QSpacerItem *hs = new QSpacerItem(400, 0, QSizePolicy::Minimum, QSizePolicy::Expanding);
                QGridLayout *gl = (QGridLayout*)msgBox.layout();
                gl->addItem(hs, gl->rowCount(), 0, 1, gl->columnCount());
                msgBox.exec();
                //ClearArtikelFields();
            }
            else
            {
                ui->frm_art_1->setVisible(false);
                ui->frm_art_2->setVisible(false);
                ui->frm_art_3->setVisible(false);
                ui->frm_art_4->setVisible(false);

                FillArtikelFields();
                ui->tbArtikelnummer->setText(art->getCode());
                CurrentArt = art->getArtikel_ID();
            }
        }
    }
}

void BedienScherm::on_btnTarra_clicked()
{
    ws->Tarra = ws->Gewicht;
}

void BedienScherm::on_btnNieuw_clicked()
{
    if (ws->PersID != 0)
    {
        ticket = new Ticket();
        ticket->setVerkoper_ID(ws->PersID);
        ticket->setVerkoper_Naam(ws->PersNaam);
        ticket->setTijdstip(QDateTime::currentDateTime());
        ticket->setNaar_Factuur(false);
        ticket->setNaar_Kas(false);
        ticket->setBetaald(false);
        ticket->setBestelling(0);
        QString CurrentTicketnumber;
        QDateTime now = QDateTime::currentDateTime();
        CurrentTicketnumber.sprintf("%04d%02d%02d%02d%02d%02d%03d",
                now.date().year(),
                now.date().month(),
                now.date().day(),
                now.time().hour(),
                now.time().minute(),
                now.time().second(),
                now.time().msec());

        ticket->setVolgnummer(CurrentTicketnumber);
        ticket->save();
        ws->TicketID = ticket->getTicket_ID();
        ws->Bestelling = ticket->getBestelling();
        ws->TicketNummer = CurrentTicketnumber;
        FillTicket();
        ui->btnNieuw->setEnabled(false);
        ui->btnLaatsteTicket->setEnabled(false);
        ui->btnNaarKassa->setEnabled(true);
        ui->btnAnnuleer->setEnabled(true);
        ui->btnToevoegen->setEnabled(true);
        ui->btnSchrapLijn->setEnabled(false);
    }
    else
    {
        QMessageBox msgBox;
        msgBox.setText("<strong>Geen verkoper gekozen !</strong>");
        msgBox.setInformativeText("Er is geen verkoper gekozen,\ngelieve dit eerst te doen ! ! !");
        msgBox.setStandardButtons(QMessageBox::Cancel);
        msgBox.setDefaultButton(QMessageBox::Cancel);
        msgBox.setIcon(QMessageBox::Critical);
        msgBox.setWindowTitle("Opgepast !");
        QSpacerItem *hs = new QSpacerItem(400, 0, QSizePolicy::Minimum, QSizePolicy::Expanding);
        QGridLayout *gl = (QGridLayout*)msgBox.layout();
        gl->addItem(hs, gl->rowCount(), 0, 1, gl->columnCount());
        msgBox.exec();
    }
}

void BedienScherm::on_btnToevoegen_clicked()
{
    if ((ws->Artikel_ID != 0 ) && (ws->TicketID != 0))
    {
        // onthoud voor label

        LabelProduct = ws->ProductBenaming;

        if (ws->VerkoopsEenheid == "Kg")
            LabelHoeveel = QString("%1 Kg").arg(ws->Gewicht, 0, 'f', 3);
        else
            LabelHoeveel = QString("%1 %2").arg(ws->Aantal).arg(ws->VerkoopsEenheid);

        // Maak nieuwe record.
        art = new Artikelen(ws->Artikel_ID);
        ticketline = new TicketLine();
        ticketline->setArtID(art->getArtikel_ID());
        ticketline->setArtCode(art->getCode());
        ticketline->setArtOmschrijving(art->getBenaming());
        ticketline->setBTWperc(ws->BTWPercentage);
        ticketline->setEenheid(ws->VerkoopsEenheid);
        ticketline->setEenheidsprijs(ws->PrijsPerEenheidExclBTW);
        double hoeveel = (ws->VerkoopsEenheid == "Kg" ? (ws->Gewicht - ws->Tarra) : ws->Aantal);
        ticketline->setHoeveelheid(hoeveel);
        ticketline->setLotnrCode(ws->Lotnr);
        ticketline->setLotnrID(ws->LotnrID);
        ticketline->setPrijsBTW((hoeveel * ws->PrijsPerEenheidExclBTW) * ws->BTWPercentage / 100);
        ticketline->setPrijsExBTW((hoeveel * ws->PrijsPerEenheidExclBTW));
        ticketline->setPrijsInclBTW((hoeveel * ws->PrijsPerEenheidExclBTW) * ( 1 + ws->BTWPercentage / 100));
        LabelPrijs = QString("%1 €").arg(((hoeveel * ws->PrijsPerEenheidExclBTW) * ( 1 + ws->BTWPercentage / 100)), 0, 'f', 2);
        ticketline->setTicketID(ws->TicketID);
        ticketline->setTijdstip(QDateTime::currentDateTime());
        ticketline->save();
        ws->Aantal = 1;
        ui->tbAantal->setText("1");
        ws->ArtikelCode = "000000";
        ws->Artikel_ID = 0;
        ui->tbArtikelnummer->setText("000000");
        on_btnWis_Art_clicked();
        ws->VerkoopsEenheid = "Kg";
        ws->PersWissel++;
        FillTicket();
    }
    else
    {
        QMessageBox msgBox;
        msgBox.setText("<strong>Onbekend artikelnummer !</strong>");
        msgBox.setInformativeText("Dit artikelnummer blijkt niet te bestaan,\ngelieve dit eerst aan te maken ! ! !");
        msgBox.setStandardButtons(QMessageBox::Cancel);
        msgBox.setDefaultButton(QMessageBox::Cancel);
        msgBox.setIcon(QMessageBox::Critical);
        msgBox.setWindowTitle("Opgepast !");
        QSpacerItem *hs = new QSpacerItem(400, 0, QSizePolicy::Minimum, QSizePolicy::Expanding);
        QGridLayout *gl = (QGridLayout*)msgBox.layout();
        gl->addItem(hs, gl->rowCount(), 0, 1, gl->columnCount());
        msgBox.exec();
    }
}

void BedienScherm::on_btnTarra_2_clicked()
{
    bool ok;
    QString text = QInputDialog::getText(this, tr("Nieuw lotnummer toevoegen !"),
                                         tr("Scan nu het lotnummer om te verkopen.\nof druk 'cancel'"),
                                         QLineEdit::Normal, "Scan Barcode", &ok);
    if (ok && !text.isEmpty())
    {
        // ja open zet in winkel en vul gegevens in
        lotnr = new LotnummerData(text);
        if (lotnr->getLotnummer_id() == 0)
        {
            // lotnummer niet gevonden verkoop zonder lotnummer
            // meld
            QMessageBox msgBox;
            msgBox.setText("<strong>Onbekend Lotnummer !</strong>");
            msgBox.setInformativeText("Het opgegeven lotnummer is niet gevonden.\nLaat nakijken wat er verkeerd is ! ! !");
            msgBox.setStandardButtons(QMessageBox::Cancel);
            msgBox.setDefaultButton(QMessageBox::Cancel);
            msgBox.setIcon(QMessageBox::Critical);
            msgBox.setWindowTitle("Opgepast !");
            QSpacerItem *hs = new QSpacerItem(400, 0, QSizePolicy::Minimum, QSizePolicy::Expanding);
            QGridLayout *gl = (QGridLayout*)msgBox.layout();
            gl->addItem(hs, gl->rowCount(), 0, 1, gl->columnCount());
            msgBox.exec();
        }
        else
        {
            lotnr->setLocatie_ID(13);
            lotnr->setLocatieVeranderdOp(QDateTime::currentDateTime());
            lotnr->save();
        }
    }
}

void BedienScherm::on_btnSchrapLijn_clicked()
{
    QMessageBox msgBox;
    msgBox.setText("<strong>Regel Wissen !</strong>");
    msgBox.setInformativeText("Bent u zeker deze ticket regel te willen wissen?");
    msgBox.setStandardButtons(QMessageBox::Cancel | QMessageBox::Ok);
    msgBox.setDefaultButton(QMessageBox::Cancel);
    msgBox.setIcon(QMessageBox::Question);
    msgBox.setWindowTitle("Opgepast !");
    QSpacerItem *hs = new QSpacerItem(400, 0, QSizePolicy::Minimum, QSizePolicy::Expanding);
    QGridLayout *gl = (QGridLayout*)msgBox.layout();
    gl->addItem(hs, gl->rowCount(), 0, 1, gl->columnCount());
    if (msgBox.exec() == QMessageBox::Ok)
    {
        int nr = 0;
        nr = ui->lstwTicket->currentItem()->data(Qt::UserRole).toInt();
        TicketLine::deleteTicketLine(nr);
        FillTicket();
        ws->PersWissel++;
    }
}

void BedienScherm::on_btnAnnuleer_clicked()
{
    QMessageBox msgBox;
    msgBox.setText("<strong>Regel Wissen !</strong>");
    msgBox.setInformativeText("Bent u zeker dit volledige ticket te willen wissen?");
    msgBox.setStandardButtons(QMessageBox::Cancel | QMessageBox::Ok);
    msgBox.setDefaultButton(QMessageBox::Cancel);
    msgBox.setIcon(QMessageBox::Question);
    msgBox.setWindowTitle("Opgepast !");
    QSpacerItem *hs = new QSpacerItem(400, 0, QSizePolicy::Minimum, QSizePolicy::Expanding);
    QGridLayout *gl = (QGridLayout*)msgBox.layout();
    gl->addItem(hs, gl->rowCount(), 0, 1, gl->columnCount());
    if (msgBox.exec() == QMessageBox::Ok)
    {
        int nr = 0;
        nr = ws->TicketID;
        Ticket::deleteTicket(nr);
        CheckOpenTicket();
        ws->PersWissel++;
    }
}

void BedienScherm::on_btnNaarKassa_clicked()
{
    double ex, btw, incl;
    TicketLine::getTicketTotalen(ticket->getTicket_ID(), ex, btw, incl);
    ticket->setTotaal_Ex_BTW(ex);
    ticket->setTotaal_BTW(btw);
    ticket->setTotaal_Incl_BTW(incl);
    ticket->setNaar_Kas(true);
    ticket->save();
    CheckOpenTicket();
    ws->PersWissel++;
}

void BedienScherm::on_btnLaatsteTicket_clicked()
{
    int nr = Ticket::CheckLastOpenTicket(ws->PersID);
    if (nr != 0)
    {
        ticket = new Ticket(nr);
        ticket->setNaar_Kas(false);
        ticket->save();
        CheckOpenTicket();
        ws->PersWissel++;
    }
}

void BedienScherm::on_btnPrintLabel_clicked()
{
    m_sSettingsFile = QApplication::applicationDirPath() + "/appSettings.ini";
    QSettings settings(m_sSettingsFile, QSettings::NativeFormat);

    QString PrinterNaam = settings.value("Printers/LabelPrinterWinkel1", "").toString();

    // Zebra_Technologies_ZTC_GC420d_
    QPrinter pr(QPrinter::HighResolution);
    pr.setPrinterName(PrinterNaam);;
    pr.setPageSizeMM(QSize(76.2,30.8));
    pr.setOrientation(QPrinter::Portrait);
    pr.setResolution(600);
    pr.setPageMargins(0,0,0,0,QPrinter::Millimeter);

    double x_scale = pr.physicalDpiX();
    double y_scale = pr.physicalDpiY();
    x_scale = 200/25.4;
    y_scale = 200/25.4;

    QFont f_artikel("Century Schoolbook L",4,QFont::Bold);
    QFont f_lijn("Century Schoolbook L",4);
    QFont f_codes("Droid Sans Mono",2.9);
    QFont f_codesvet("Droid Sans Mono",3,QFont::Bold);
    QFont f_blok("Bitstream Charter", 3);

    QPen pen(Qt::black);
    pen.setWidth(2);

    QRect LR = QRect(17 * x_scale , 0, 71 * x_scale , 10 * y_scale);
    QRect Blok = QRect(38 * x_scale , 3 * y_scale, 50 * x_scale , 10 * y_scale);
    QPainter painter(&pr);

    // Print het logo
    QImage pixmap1(":/icons/icons/Logo_zww.png");
    painter.drawImage(QRect(17 * x_scale, 2 * y_scale, 22 * x_scale, 22 * y_scale),pixmap1);

    painter.setFont(f_blok);
    painter.drawText(Blok, Qt::AlignLeft | Qt::AlignHCenter, "Met liefde, voor u geproduceerd");
    Blok.setTop(7 * y_scale); Blok.setHeight(10 * y_scale);
    painter.drawText(Blok, Qt::AlignLeft | Qt::AlignHCenter, QString("Gekocht op: %1").arg(QDate::currentDate().toString("dddd dd/MM/yyyy")));
    Blok.setTop(11 * y_scale); Blok.setHeight(10 * y_scale);
    painter.drawText(Blok, Qt::AlignLeft | Qt::AlignHCenter, "Leg mij in de ijskast.");


    painter.setFont(f_artikel);
    LR.setTop(25 * y_scale); LR.setHeight(10 * y_scale);
    painter.drawText(LR, Qt::AlignLeft | Qt::AlignHCenter, LabelProduct);

    painter.setFont(f_lijn);
    LR.setTop(31 * y_scale); LR.setHeight(10 * y_scale);
    painter.drawText(LR, Qt::AlignRight, LabelPrijs);
    LR.setTop(31 * y_scale); LR.setHeight(10 * y_scale);
    painter.drawText(LR, Qt::AlignLeft , LabelHoeveel);


    painter.setPen(pen);
    painter.drawLine(17 * x_scale ,38 * y_scale , 88 * x_scale ,38 * y_scale);
    painter.setFont(f_codes);
    LR.setTop(40 * y_scale); LR.setHeight(10 * y_scale);
    painter.drawText(LR, Qt::AlignLeft | Qt::AlignHCenter, "Kauwstraat 28 - 9550 St.Lievens Esse");
    LR.setTop(43 * y_scale); LR.setHeight(10 * y_scale);
    painter.drawText(LR, Qt::AlignLeft | Qt::AlignHCenter, "054 25 44 66 - info@deneeuwigenbeenhouwer.be");
    painter.setFont(f_codesvet);
    LR.setTop(46 * y_scale); LR.setHeight(10 * y_scale);
    painter.drawText(LR, Qt::AlignLeft | Qt::AlignHCenter, "www.deneeuwigenbeenhouwer.be");

    painter.end();


}

void BedienScherm::UncheckPersoneelsButtons()
{
    ui->btnPer1->setChecked(false);
    ui->btnPer2->setChecked(false);
    ui->btnPer3->setChecked(false);
    ui->btnPer4->setChecked(false);
    ui->btnPer5->setChecked(false);
    ui->btnPer6->setChecked(false);
}

void BedienScherm::CheckPersoneelsButton(int _id)
{
    if (ui->btnPer1->toolTip().toInt() == _id)
        ui->btnPer1->setChecked(true);
    else if (ui->btnPer2->toolTip().toInt() == _id)
        ui->btnPer2->setChecked(true);
    else if (ui->btnPer3->toolTip().toInt() == _id)
        ui->btnPer3->setChecked(true);
    else if (ui->btnPer4->toolTip().toInt() == _id)
        ui->btnPer4->setChecked(true);
    else if (ui->btnPer5->toolTip().toInt() == _id)
        ui->btnPer5->setChecked(true);
    else if (ui->btnPer6->toolTip().toInt() == _id)
        ui->btnPer6->setChecked(true);
}

void BedienScherm::on_btnPer1_clicked()
{
    UncheckPersoneelsButtons();
    ui->btnPer1->setChecked(true);
    Personeel::setSalesmenOnBalance(ui->btnPer1->toolTip().toInt(), ws->NummerWeegschaal);
}

void BedienScherm::on_btnPer2_clicked()
{
    UncheckPersoneelsButtons();
    ui->btnPer2->setChecked(true);
    Personeel::setSalesmenOnBalance(ui->btnPer2->toolTip().toInt(), ws->NummerWeegschaal);
}

void BedienScherm::on_btnPer3_clicked()
{
    UncheckPersoneelsButtons();
    ui->btnPer3->setChecked(true);
    Personeel::setSalesmenOnBalance(ui->btnPer3->toolTip().toInt(), ws->NummerWeegschaal);
}

void BedienScherm::on_btnPer4_clicked()
{
    UncheckPersoneelsButtons();
    ui->btnPer4->setChecked(true);
    Personeel::setSalesmenOnBalance(ui->btnPer4->toolTip().toInt(), ws->NummerWeegschaal);
}

void BedienScherm::on_btnPer5_clicked()
{
    UncheckPersoneelsButtons();
    ui->btnPer5->setChecked(true);
    Personeel::setSalesmenOnBalance(ui->btnPer5->toolTip().toInt(), ws->NummerWeegschaal);
}

void BedienScherm::on_btnPer6_clicked()
{
    UncheckPersoneelsButtons();
    ui->btnPer6->setChecked(true);
    Personeel::setSalesmenOnBalance(ui->btnPer6->toolTip().toInt(), ws->NummerWeegschaal);
}

void BedienScherm::on_btnBestelNummer_clicked()
{
    if (ws->TicketID != 0)
    {
        CurObj = ui->tbBestelling;

        NumKeyboard* kb = new NumKeyboard(CurObj, this);
        kb->exec();
        int bestelling = ui->tbBestelling->text().toInt();
        if (bestelling != 0)
        {
            if (Ticket::getBestellingByNumber(bestelling) == 0)
            {
                ws->Bestelling = bestelling;
                ticket->setBestelling(bestelling);
                ticket->save();
            }
            else
            {
                QMessageBox msgBox;
                msgBox.setText("<strong>Reeds bestaand bestelnummer !</strong>");
                msgBox.setInformativeText("Dit bestelnummer is reeds in gebruik, je moet een onbestaand nummer kiezen");
                msgBox.setStandardButtons(QMessageBox::Ok);
                msgBox.setDefaultButton(QMessageBox::Ok);
                msgBox.setIcon(QMessageBox::Warning);
                msgBox.setWindowTitle("Opgepast !");
                QSpacerItem *hs = new QSpacerItem(400, 0, QSizePolicy::Minimum, QSizePolicy::Expanding);
                QGridLayout *gl = (QGridLayout*)msgBox.layout();
                gl->addItem(hs, gl->rowCount(), 0, 1, gl->columnCount());
                msgBox.exec();
                ui->tbBestelling->setText("0");
                ws->Bestelling = 0;
            }
        }
    }
    else
    {
        QMessageBox msgBox;
        msgBox.setText("<strong>Ontbrekend Ticket !</strong>");
        msgBox.setInformativeText("U hebt nog geen ticket aangemaakt, je moet dit eerst doen");
        msgBox.setStandardButtons(QMessageBox::Ok);
        msgBox.setDefaultButton(QMessageBox::Ok);
        msgBox.setIcon(QMessageBox::Warning);
        msgBox.setWindowTitle("Opgepast !");
        QSpacerItem *hs = new QSpacerItem(400, 0, QSizePolicy::Minimum, QSizePolicy::Expanding);
        QGridLayout *gl = (QGridLayout*)msgBox.layout();
        gl->addItem(hs, gl->rowCount(), 0, 1, gl->columnCount());
        msgBox.exec();
    }
}

void BedienScherm::on_btnBestellingOpslaan_clicked()
{
    if (ws->Bestelling == 0)
    {
        // Nog geen nummer opgegeven, wens je dat nu te doen
        QMessageBox msgBox;
        msgBox.setText("<strong>Ontbrekend bestelnummer !</strong>");
        msgBox.setInformativeText("U hebt nog geen bestelnummer opgegeven, je moet dit eerst doen");
        msgBox.setStandardButtons(QMessageBox::Ok);
        msgBox.setDefaultButton(QMessageBox::Ok);
        msgBox.setIcon(QMessageBox::Warning);
        msgBox.setWindowTitle("Opgepast !");
        QSpacerItem *hs = new QSpacerItem(400, 0, QSizePolicy::Minimum, QSizePolicy::Expanding);
        QGridLayout *gl = (QGridLayout*)msgBox.layout();
        gl->addItem(hs, gl->rowCount(), 0, 1, gl->columnCount());
        msgBox.exec();
    }
    else
    {
        double ex, btw, incl;
        TicketLine::getTicketTotalen(ticket->getTicket_ID(), ex, btw, incl);
        ticket->setTotaal_Ex_BTW(ex);
        ticket->setTotaal_BTW(btw);
        ticket->setTotaal_Incl_BTW(incl);
        ticket->setVerkoper_ID(99);
        ticket->setVerkoper_Naam("Bestelling");
        QDateTime dat;
        dat = QDateTime::fromString("1900-01-01","yyyy-MM-dd");
        ticket->setTijdstip(dat);
        TicketLine::setTimePerTicketID(ticket->getTicket_ID(), dat);
        ticket->save();
        CheckOpenTicket();
        ws->PersWissel++;
    }
}

void BedienScherm::on_btnZoekBestelling_clicked()
{
    if (ws->TicketID == 0)
    {
        ui->tbBestelling->setText("");
        CurObj = ui->tbBestelling;

        NumKeyboard* kb = new NumKeyboard(CurObj, this);
        kb->exec();
        int bestelling = ui->tbBestelling->text().toInt();
        if (bestelling != 0)
        {
            ws->Bestelling = bestelling;
            // Zoek de bestelling
            ws->TicketID = Ticket::getBestellingByNumber(bestelling);

            if (ws->TicketID == 0)
            {
                QMessageBox msgBox;
                msgBox.setText("<strong>Ontbekend bestelnummer !</strong>");
                msgBox.setInformativeText("Dit bestelnummer blijkt niet te bestaan.");
                msgBox.setStandardButtons(QMessageBox::Ok);
                msgBox.setDefaultButton(QMessageBox::Ok);
                msgBox.setIcon(QMessageBox::Warning);
                msgBox.setWindowTitle("Opgepast !");
                QSpacerItem *hs = new QSpacerItem(400, 0, QSizePolicy::Minimum, QSizePolicy::Expanding);
                QGridLayout *gl = (QGridLayout*)msgBox.layout();
                gl->addItem(hs, gl->rowCount(), 0, 1, gl->columnCount());
                msgBox.exec();
            }
            else
            {
                ticket = new Ticket(ws->TicketID);
                ticket->setVerkoper_ID(ws->PersID);
                ticket->setVerkoper_Naam(ws->PersNaam);
                ticket->save();
                CheckOpenTicket();
                ws->PersWissel++;
            }

            //ticket->setBestelling(bestelling);
            //ticket->save();
        }
    }
    else
    {
        QMessageBox msgBox;
        msgBox.setText("<strong>Openstaand ticket !</strong>");
        msgBox.setInformativeText("U hebt nog een ticket open staan, je moet dit eerst afwerken.");
        msgBox.setStandardButtons(QMessageBox::Ok);
        msgBox.setDefaultButton(QMessageBox::Ok);
        msgBox.setIcon(QMessageBox::Warning);
        msgBox.setWindowTitle("Opgepast !");
        QSpacerItem *hs = new QSpacerItem(400, 0, QSizePolicy::Minimum, QSizePolicy::Expanding);
        QGridLayout *gl = (QGridLayout*)msgBox.layout();
        gl->addItem(hs, gl->rowCount(), 0, 1, gl->columnCount());
        msgBox.exec();
    }
}

void BedienScherm::PrintBestelTicket()
{
    QDateTime timestamp = QDateTime::currentDateTime();
    double bedrag = 0;
    //QList<QPrinterInfo> printerlist = QPrinterInfo::availablePrinters();
    //qDebug() << printerlist[1].printerName();

    m_sSettingsFile = QApplication::applicationDirPath() + "/appSettings.ini";
    QSettings settings(m_sSettingsFile, QSettings::NativeFormat);

    QString PrinterNaam = settings.value("Printers/TicketPrinter1", "").toString();

    QPrinter pr(QPrinter::HighResolution);
    pr.setPrinterName(PrinterNaam);;
    pr.setPageSizeMM(QSize(80,2000));
    pr.setOrientation(QPrinter::Portrait);
    pr.setPageMargins(2,2,2,2,QPrinter::Millimeter);

    int x_scale = pr.physicalDpiX() /25.4;
    int y_scale = pr.physicalDpiY() / 25.4;
    int y_pos = 0;

    QFont f_artikel("Century Schoolbook L",10,QFont::Bold);
    QFont f_bestelnr("Century Schoolbook L",48,QFont::Bold);
    QFont f_lijn("Century Schoolbook L",10);
    QFont f_codes("Droid Sans Mono",10);
    QFont f_btw("Droid Sans Mono",8);
    QFont f_barcode("free3of9",25);
    QFont f_bloktit("Bitstream Charter", 12, QFont::Bold);
    QFont f_blok("Bitstream Charter", 10);
    QFont f_blokvet("Bitstream Charter", 10, QFont::Bold);

    QPen pen(Qt::black);
    pen.setWidth(15);

    QRect LR = QRect(0, 0, 68 * x_scale, 10 * y_scale);

    QPainter painter(&pr);

    // Print het logo
    QImage pixmap1(":/icons/icons/Logo_zww.png");
    painter.drawImage(QRect(10 * x_scale, y_pos, 50 * x_scale, 50 * y_scale),pixmap1);

    // Print de datum
    y_pos += 50;
    painter.setPen(pen);
    painter.drawLine(0,y_pos * y_scale ,68 * x_scale ,y_pos * y_scale);
    y_pos += 1;
    LR.setTop(y_pos * y_scale); LR.setHeight(10 * y_scale);
    painter.drawText(LR, Qt::AlignHCenter | Qt::AlignTop, timestamp.toString("dddd dd/MM/yyyy hh:mm"));
    y_pos += 5;
    painter.drawLine(0,y_pos * y_scale ,68 * x_scale , y_pos * y_scale);

    painter.setFont(f_bestelnr);
    //y_pos += 5;
    LR.setTop(y_pos * y_scale); LR.setHeight(25 * y_scale);
    painter.drawText(LR, Qt::AlignHCenter | Qt::AlignTop, QString("%1")
                     .arg(ws->Bestelling, 0, 'f', 0));


    y_pos += 21;
    painter.drawLine(0,y_pos * y_scale ,68 * x_scale , y_pos * y_scale);
    y_pos += 3;

    if (true)
    {
        QSqlQueryModel* mod = new QSqlQueryModel();
        TicketLine::getLinesByTicketID(ticket->getTicket_ID(), mod);

        // Tickelijnen printen
        for(int i = 0; i < mod->rowCount() ; i++)
        {
            LR.setTop(y_pos * y_scale); LR.setHeight(10 * y_scale);
            painter.setFont(f_artikel);
            painter.drawText(LR,Qt::AlignLeft | Qt::AlignTop,mod->record(i).value("art_omschrijving").toString());
            y_pos += 5;

            LR.setTop(y_pos * y_scale); LR.setHeight(10 * y_scale);
            painter.setFont(f_lijn);
            painter.drawText(LR, Qt::AlignLeft | Qt::AlignTop, QString("%1 %2 aan %3 € per %4")
                             .arg(mod->record(i).value("hoeveelheid").toDouble(), 0, 'f', 3)
                             .arg(mod->record(i).value("eenheid").toString())
                             .arg((mod->record(i).value("eenheidsprijs").toDouble()*(1+mod->record(i).value("btw_perc").toDouble()/100)), 0, 'f', 2)
                             .arg(mod->record(i).value("eenheid").toString())
                             );
            painter.drawText(LR, Qt::AlignRight | Qt::AlignTop, QString("%1 €")
                             .arg(mod->record(i).value("prijs_incl_btw").toDouble(), 0, 'f', 2)
                             );
            y_pos += 6;
        }
        painter.drawLine(0,y_pos * y_scale ,68 * x_scale ,y_pos * y_scale);
        y_pos += 2;
        // BTW blokje
        // Titel:
        painter.setFont(f_btw);
        painter.drawText(0, y_pos * y_scale, 17 * x_scale, 10 * y_scale, Qt::AlignHCenter | Qt::AlignTop, QString("BTW%") );
        painter.drawText(17 * x_scale, y_pos * y_scale, 17 * x_scale, 10 * y_scale, Qt::AlignHCenter | Qt::AlignTop, QString("Ex.BTW") );
        painter.drawText(34 * x_scale, y_pos * y_scale, 17 * x_scale, 10 * y_scale, Qt::AlignHCenter | Qt::AlignTop, QString("BTW") );
        painter.drawText(51 * x_scale, y_pos * y_scale, 17 * x_scale, 10 * y_scale, Qt::AlignHCenter | Qt::AlignTop, QString("Incl.BTW") );
        y_pos += 4;

        painter.drawLine( 2 * x_scale, y_pos * y_scale ,16 * x_scale ,y_pos * y_scale);
        painter.drawLine(18 * x_scale, y_pos * y_scale ,33 * x_scale ,y_pos * y_scale);
        painter.drawLine(35 * x_scale, y_pos * y_scale ,50 * x_scale ,y_pos * y_scale);
        painter.drawLine(52 * x_scale, y_pos * y_scale ,67 * x_scale ,y_pos * y_scale);
        y_pos += 2;

        mod = new QSqlQueryModel();
        TicketLine::getBTWByTicketID(ticket->getTicket_ID(), mod);
        for(int i = 0; i < mod->rowCount() ; i++)
        {
            painter.drawText(0, y_pos * y_scale, 17 * x_scale, 10 * y_scale, Qt::AlignHCenter | Qt::AlignTop,
                             QString("%1\%").arg(mod->record(i).value("perc").toDouble(), 0, 'f', 2) );
            painter.drawText(17 * x_scale, y_pos * y_scale, 17 * x_scale, 10 * y_scale, Qt::AlignHCenter | Qt::AlignTop,
                             QString("%1").arg(mod->record(i).value("ex").toDouble(), 0, 'f', 2) );
            painter.drawText(34 * x_scale, y_pos * y_scale, 17 * x_scale, 10 * y_scale, Qt::AlignHCenter | Qt::AlignTop,
                             QString("%1").arg(mod->record(i).value("btw").toDouble(), 0, 'f', 2) );
            painter.drawText(51 * x_scale, y_pos * y_scale, 17 * x_scale, 10 * y_scale, Qt::AlignHCenter | Qt::AlignTop,
                             QString("%1").arg(mod->record(i).value("incl").toDouble(), 0, 'f', 2) );
            y_pos += 4;
        }
        painter.drawLine(0,y_pos * y_scale ,68 * x_scale ,y_pos * y_scale);
        y_pos += 1;
    }
    // ======== Totaal blok ===========

    LR.setTop(y_pos * y_scale); LR.setHeight(10 * y_scale);
    painter.setFont(f_artikel);
    painter.drawText(LR,Qt::AlignLeft | Qt::AlignTop, "Totaal incl.BTW:");
    painter.setFont(f_artikel);
    painter.drawText(LR,Qt::AlignRight | Qt::AlignTop, QString("%1 €").arg(ticket->getTotaal_Incl_BTW(), 0, 'f', 2));
    y_pos += 5;

    painter.setFont(f_lijn);
    LR.setTop(y_pos * y_scale); LR.setHeight(10 * y_scale);
    painter.drawText(LR,Qt::AlignLeft | Qt::AlignTop, "Bestelling nr.:");
    LR.setTop(y_pos * y_scale); LR.setHeight(10 * y_scale);
    painter.setFont(f_artikel);
    painter.drawText(LR,Qt::AlignRight | Qt::AlignTop, QString("%1").arg(ws->Bestelling, 0, 'f', 0));
    y_pos += 4;
    y_pos += 1;
    painter.drawLine(0,y_pos * y_scale ,68 * x_scale ,y_pos * y_scale);
    y_pos += 1;

    painter.setFont(f_blok);
    LR.setTop(y_pos * y_scale); LR.setHeight(10 * y_scale);
    painter.drawText(LR,Qt::AlignHCenter | Qt::AlignTop, QString("U werd geholpen door: %1").arg(ticket->getVerkoper_Naam()));
    y_pos += 4;

    painter.setFont(f_bloktit);
    LR.setTop(y_pos * y_scale); LR.setHeight(10 * y_scale);
    painter.drawText(LR,Qt::AlignHCenter | Qt::AlignTop, "Bedankt voor uw vertrouwen.");
    y_pos += 5;

    painter.setFont(f_blok);
    LR.setTop(y_pos * y_scale); LR.setHeight(10 * y_scale);
    painter.drawText(LR,Qt::AlignHCenter | Qt::AlignTop, "Kauwstraat 28 - 9550 Sint Lievens Esse");
    y_pos += 4;
    LR.setTop(y_pos * y_scale); LR.setHeight(10 * y_scale);
    painter.drawText(LR,Qt::AlignHCenter | Qt::AlignTop, "Tel: 054 25 44 66.");
    y_pos += 4;
    LR.setTop(y_pos * y_scale); LR.setHeight(10 * y_scale);
    painter.drawText(LR,Qt::AlignHCenter | Qt::AlignTop, "e-mail: info@deneeuwigenbeenhouwer.be");
    y_pos += 5;
    painter.setFont(f_blokvet);
    LR.setTop(y_pos * y_scale); LR.setHeight(10 * y_scale);
    painter.drawText(LR,Qt::AlignHCenter | Qt::AlignTop, "www.deneeuwigenbeenhouwer.be");
    y_pos += 5;
    painter.setFont(f_blok);
    LR.setTop(y_pos * y_scale); LR.setHeight(10 * y_scale);
    painter.drawText(LR,Qt::AlignHCenter | Qt::AlignTop, "BTW nr.: BE 0645.608.640");
    y_pos += 6;

    // Openingsuren
    painter.drawLine(0,y_pos * y_scale ,68 * x_scale ,y_pos * y_scale);
    y_pos += 1;
    painter.setFont(f_blok);
    LR.setTop(y_pos * y_scale); LR.setHeight(10 * y_scale);
    painter.drawText(LR,Qt::AlignHCenter | Qt::AlignTop, "Open: ma - za 8:00-13:00 en 14:00-19:00");
    y_pos += 6;
    LR.setTop(y_pos * y_scale); LR.setHeight(10 * y_scale);
    painter.drawText(LR,Qt::AlignHCenter | Qt::AlignTop, "op zondag 8:00 tot 13u00");
    y_pos += 6;
    LR.setTop(y_pos * y_scale); LR.setHeight(10 * y_scale);
    painter.drawText(LR,Qt::AlignHCenter | Qt::AlignTop, "GESLOTEN op DONDERDAG");
    y_pos += 6;

    // Print ticketnummer in klaatext en in barcode
    painter.drawLine(0,y_pos * y_scale ,68 * x_scale ,y_pos * y_scale);
    y_pos += 1;

    LR.setTop(y_pos * y_scale); LR.setHeight(10 * y_scale);
    painter.setFont(f_barcode);
    painter.drawText(LR, Qt::AlignHCenter | Qt::AlignTop,QString("*%1*").arg(ticket->getVolgnummer()));
    y_pos += 10;

    LR.setTop(y_pos * y_scale); LR.setHeight(10 * y_scale);
    painter.setFont(f_codes);
    painter.drawText(LR, Qt::AlignHCenter | Qt::AlignTop,QString("Ticket: -%1-").arg(ticket->getVolgnummer()));
    y_pos += 10;

    painter.end();

}

void BedienScherm::on_btnPrintBestelling_clicked()
{
    if (ws->Bestelling > 0)
    {
        PrintBestelTicket();
    }
}

void BedienScherm::on_btnPrintBestelLabel_clicked()
{
    m_sSettingsFile = QApplication::applicationDirPath() + "/appSettings.ini";
    QSettings settings(m_sSettingsFile, QSettings::NativeFormat);

    QString PrinterNaam = settings.value("Printers/LabelPrinterWinkel1", "").toString();

    // Zebra_Technologies_ZTC_GC420d_
    QPrinter pr(QPrinter::HighResolution);
    pr.setPrinterName(PrinterNaam);;
    pr.setPageSizeMM(QSize(76.2,30.8));
    pr.setOrientation(QPrinter::Portrait);
    pr.setResolution(600);
    pr.setPageMargins(0,0,0,0,QPrinter::Millimeter);

    double x_scale = pr.physicalDpiX();
    double y_scale = pr.physicalDpiY();
    x_scale = 200/25.4;
    y_scale = 200/25.4;

    QFont f_bestelnr("Century Schoolbook L",24,QFont::Bold);
    QFont f_codes("Droid Sans Mono",2.9);
    QFont f_codesvet("Droid Sans Mono",3,QFont::Bold);
    QFont f_blok("Bitstream Charter", 3);

    QPen pen(Qt::black);
    pen.setWidth(2);

    QRect LR = QRect(17 * x_scale , 0, 71 * x_scale , 10 * y_scale);
    QRect Blok = QRect(38 * x_scale , 3 * y_scale, 50 * x_scale , 10 * y_scale);
    QPainter painter(&pr);

    // Print het logo
    QImage pixmap1(":/icons/icons/Logo_zww.png");
    painter.drawImage(QRect(17 * x_scale, 2 * y_scale, 22 * x_scale, 22 * y_scale),pixmap1);

    painter.setFont(f_blok);
    painter.drawText(Blok, Qt::AlignLeft | Qt::AlignHCenter, "Met liefde, voor u geproduceerd");
    Blok.setTop(7 * y_scale); Blok.setHeight(10 * y_scale);
    painter.drawText(Blok, Qt::AlignLeft | Qt::AlignHCenter, "Leg mij in de ijskast.");

    QRect NR = QRect(17 * x_scale , 15 * y_scale , 71 * x_scale , 20 * y_scale);
    painter.setFont(f_bestelnr);
    painter.drawText(NR, Qt::AlignVCenter | Qt::AlignHCenter, QString("%1").arg(ws->Bestelling));

    painter.setPen(pen);
    painter.drawLine(17 * x_scale ,38 * y_scale , 88 * x_scale ,38 * y_scale);
    painter.setFont(f_codes);
    LR.setTop(40 * y_scale); LR.setHeight(10 * y_scale);
    painter.drawText(LR, Qt::AlignLeft | Qt::AlignHCenter, "Kauwstraat 28 - 9550 St.Lievens Esse");
    LR.setTop(43 * y_scale); LR.setHeight(10 * y_scale);
    painter.drawText(LR, Qt::AlignLeft | Qt::AlignHCenter, "054 25 44 66 - info@deneeuwigenbeenhouwer.be");
    painter.setFont(f_codesvet);
    LR.setTop(46 * y_scale); LR.setHeight(10 * y_scale);
    painter.drawText(LR, Qt::AlignLeft | Qt::AlignHCenter, "www.deneeuwigenbeenhouwer.be");

    painter.end();

}
