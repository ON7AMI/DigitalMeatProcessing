#include "dagrapport.h"
#include "betaalmiddel.h"
#include "ui_dagrapport.h"

#include "Weegschaal/ticketline.h"
#include "Weegschaal/ticket.h"
#include "Boekhouding/kasboek.h"
#include "CommonObjects/printpagebackground.h"
#include "CommonObjects/landen.h"
#include "CommonObjects/postcodes.h"
#include "CommonObjects/gebruikers.h"
#include "Facturatie/factuurheader.h"
#include "Facturatie/factuurline.h"
#include "Facturatie/factuurfiche.h"


#include <QBuffer>
#include <QFileDialog>
#include <QModelIndex>
#include <QPushButton>
#include <QTableView>
#include <QTableWidgetItem>
#include <QSqlRecord>
#include <QSqlField>
#include <QPrinter>
#include <QPrintDialog>
#include <QPainter>
#include <QMessageBox>
#include <QSpacerItem>
#include <QGridLayout>



Dagrapport::Dagrapport(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dagrapport)
{
    ui->setupUi(this);

    Gebruikers::CleanDagboek();

    ui->dtpDatum->setDate(QDate::currentDate());

    ui->btnFacturatie->setEnabled(false);

    FillScreen();
}

Dagrapport::~Dagrapport()
{
    delete ui;
    delete OmzetPerRubiek_Model;
    delete OmzetPerBTW_Model;
    delete Kasboek_Model;
    delete Uitgaven_Model;
}

void Dagrapport::on_btnStop_clicked()
{
    this->close();
}

void Dagrapport::FillScreen()
{
    double tot_in, tot_uit;
    tot_in = 0;
    tot_uit = 0;

    ui->lbAantalVerkopen->setText(QString("Aantal verkopen: %1").arg(Ticket::getAantalTickets(ui->dtpDatum->dateTime())));

    OmzetPerRubiek_Model = new QSqlQueryModel();
    TicketLine::getOmzetPerRubiek(ui->dtpDatum->dateTime(), OmzetPerRubiek_Model);
    ui->tvPerProduct->setModel(OmzetPerRubiek_Model);
    ui->tvPerProduct->setColumnWidth(0,40);
    ui->tvPerProduct->setColumnWidth(1,120);
    ui->tvPerProduct->setColumnWidth(2,70);
    ui->tvPerProduct->setColumnWidth(3,130);
    ui->tvPerProduct->setColumnWidth(4,130);
    ui->tvPerProduct->setColumnWidth(5,130);
    ui->tvPerProduct->setAlternatingRowColors(true);

    OmzetPerBTW_Model = new QSqlQueryModel();
    Ticket::getOmzetPerBTW(ui->dtpDatum->dateTime(), OmzetPerBTW_Model);
    ui->tvPerBTW->setModel(OmzetPerBTW_Model);
    ui->tvPerBTW->setColumnWidth(0,160);
    ui->tvPerBTW->setColumnWidth(1,70);
    ui->tvPerBTW->setColumnWidth(2,130);
    ui->tvPerBTW->setColumnWidth(3,130);
    ui->tvPerBTW->setColumnWidth(4,130);
    ui->tvPerBTW->setAlternatingRowColors(true);

    ui->tbTotaal->setText(QString("%1 €").arg(Ticket::getOmzetTotaa(ui->dtpDatum->dateTime()), 0, 'f', 2));
    ui->tbTicketTotaal->setText(QString("%1 €").arg(Ticket::getTicketTotaal(ui->dtpDatum->dateTime()), 0, 'f', 2));

    Kasboek_Model = new QSqlQueryModel();
    datum = ui->dtpDatum->dateTime();
    Kasboek::getKassaTotalen(ui->dtpDatum->dateTime(), Kasboek_Model);
    ui->tvKasboek->setModel(Kasboek_Model);
    ui->tvKasboek->setColumnWidth(0,120);
    ui->tvKasboek->setColumnWidth(1,100);
    ui->tvKasboek->setColumnWidth(2,100);
    ui->tvKasboek->setAlternatingRowColors(true);

    for(int i = 0; i < Kasboek_Model->rowCount() ; i++)
    {
        tot_in += Kasboek_Model->record(i).value("inkomsten").toDouble();
        tot_uit += Kasboek_Model->record(i).value("uitgaven").toDouble();
    }
    ui->tbTotIn->setText(QString("%1 €").arg(tot_in, 0, 'f', 2));
    ui->tbTotUit->setText(QString("%1 €").arg(tot_uit, 0, 'f', 2));

    Uitgaven_Model = new QSqlQueryModel();
    Kasboek::GetUitgaveTotalen(ui->dtpDatum->dateTime(), Uitgaven_Model);
    ui->tvUitgaven->setModel(Uitgaven_Model);
    ui->tvUitgaven->setColumnWidth(0,160);
    ui->tvUitgaven->setColumnWidth(1,120);

    if (TicketLine::isTeFacturerenPerRubiek(ui->dtpDatum->dateTime()))
    {
        ui->btnFacturatie->setEnabled(true);
    }
    else
    {
        ui->btnFacturatie->setEnabled(false);
    }
}

void Dagrapport::on_btnRefresch_clicked()
{
    FillScreen();
}

void Dagrapport::on_dtpDatum_editingFinished()
{
    //FillScreen();
}

void Dagrapport::on_btnPrint_clicked()
{
    QPrinter pr;

    QPrintDialog prDialog(&pr, this);

    prDialog.setWindowTitle("Print Dagrapport");
    if (prDialog.exec() != QDialog::Accepted)
    {
        return;
    }

    pr.setFullPage(true);

    QPainter painter(&pr);

    int aLW = 2100;
    int aLH = 2970;

    painter.setWindow(0,0,aLW,aLH);

    int aPW = pr.width();
    int aPH = pr.height();

    painter.setViewport(0, 0, aPW, aPH);

    PrintPageBackground::Print(&pr, &painter);

    QFont f_artikel("Century Schoolbook L",40,QFont::Bold);
    QFont f_lijn("Century Schoolbook L",30);
    QFont f_btw("Droid Sans Mono",25);

    QPen pen(Qt::black);
    QPen penDonker("#4d2800");
    QPen penWit(Qt::white);

    pen.setWidth(3);
    painter.setPen(pen);

    // Document tittel
    QRect LR = QRect(0, 400, 2000, 100 );
    painter.setFont(f_artikel);
    painter.drawText(LR, Qt::AlignRight | Qt::AlignTop,
                     QString("Dagrapport voor: %1").arg(ui->dtpDatum->date().toString("dddd dd/MM/yyyy")));


    painter.drawText(150, 570, QString("Aantal verkopen: %1").arg(Ticket::getAantalTickets(ui->dtpDatum->dateTime())));

    // Afdruk blok verkopen
    // tabel tittels
    LR = QRect(250, 600, 1580, 120);
    QRect rCode = QRect(250,660,100,60);
    QRect rBenaming = QRect(350,660,300,60);
    QRect rPerc = QRect(650,660,180,60);
    QRect rEx = QRect(830,660,330,60);
    QRect rBtw = QRect(1160,660,330,60);
    QRect rIn = QRect(1490,660,330,60);


    painter.fillRect(LR, QBrush(QColor("#4d2800"), Qt::SolidPattern));
    painter.setFont(f_lijn);
    painter.setPen(penWit);
    LR.setHeight(60);
    painter.drawText(LR, Qt::AlignHCenter | Qt::AlignVCenter,"Verkopen per product");
    painter.drawText(rCode,Qt::AlignHCenter | Qt::AlignVCenter,"Code");
    painter.drawText(rBenaming,Qt::AlignHCenter | Qt::AlignVCenter,"Benaming");
    painter.drawText(rPerc,Qt::AlignHCenter | Qt::AlignVCenter,"BTW %");
    painter.drawText(rEx,Qt::AlignHCenter | Qt::AlignVCenter,"Excl.BTW");
    painter.drawText(rBtw,Qt::AlignHCenter | Qt::AlignVCenter,"BTW");
    painter.drawText(rIn,Qt::AlignHCenter | Qt::AlignVCenter,"Incl.BTW");
    LR.setTop(LR.top() + 60);LR.setHeight(60);
    painter.setPen(penDonker);
    // Vul Tabel Op
    OmzetPerRubiek_Model = new QSqlQueryModel();
    TicketLine::getOmzetPerRubiek(ui->dtpDatum->dateTime(), OmzetPerRubiek_Model);
    int rijen = OmzetPerRubiek_Model->rowCount();
    int teller = 0;
    for(int i = 0 ; i < rijen /*OmzetPerBTW_Model->rowCount() */; i++)
    {
        teller++;
        LR.setTop(LR.top() + 60);LR.setHeight(60);
        if (teller % 2 == 0)
        {
            painter.fillRect(LR, QBrush(QColor("#ffdab3"), Qt::SolidPattern));
        }
        else
        {
            painter.fillRect(LR, QBrush(QColor(Qt::white), Qt::SolidPattern));
        }
        rCode.setTop(rCode.top() + 60);             rCode.setHeight(60);
        rBenaming.setTop(rBenaming.top() + 60);     rBenaming.setHeight(60);
        rPerc.setTop(rPerc.top() + 60);             rPerc.setHeight(60);
        rEx.setTop(rEx.top() + 60);                 rEx.setHeight(60);
        rBtw.setTop(rBtw.top() + 60);               rBtw.setHeight(60);
        rIn.setTop(rIn.top() + 60);                 rIn.setHeight(60);

        painter.setFont(f_btw);
        painter.drawText(rCode,Qt::AlignHCenter|Qt::AlignVCenter,QString("%1")
                         .arg(OmzetPerRubiek_Model->record(i).field("code").value().toInt()));
        painter.drawText(rBenaming,Qt::AlignLeft|Qt::AlignVCenter,QString("%1")
                         .arg(OmzetPerRubiek_Model->record(i).field("benaming").value().toString()));
        painter.drawText(rPerc,Qt::AlignHCenter|Qt::AlignVCenter,QString("%1")
                         .arg(OmzetPerRubiek_Model->record(i).field("perc").value().toDouble(), 0, 'f', 2));
        painter.drawText(rEx,Qt::AlignRight|Qt::AlignVCenter,QString("%1")
                         .arg(OmzetPerRubiek_Model->record(i).field("ex").value().toDouble(), 0, 'f', 2));
        painter.drawText(rBtw,Qt::AlignRight|Qt::AlignVCenter,QString("%1")
                         .arg(OmzetPerRubiek_Model->record(i).field("btw").value().toDouble(), 0, 'f', 2));
        painter.drawText(rIn,Qt::AlignRight|Qt::AlignVCenter,QString("%1")
                         .arg(OmzetPerRubiek_Model->record(i).field("incl").value().toDouble(), 0, 'f', 2));

    }

    // Opbrengsten per BTW code

    LR.setTop(LR.top() + 60);LR.setHeight(60);
    painter.fillRect(LR, QBrush(QColor("#4d2800"), Qt::SolidPattern));
    rCode.setTop(rCode.top() + 60);             rCode.setHeight(60);
    rBenaming.setTop(rBenaming.top() + 60);     rBenaming.setHeight(60);
    rPerc.setTop(rPerc.top() + 60);             rPerc.setHeight(60);
    rEx.setTop(rEx.top() + 60);                 rEx.setHeight(60);
    rBtw.setTop(rBtw.top() + 60);               rBtw.setHeight(60);
    rIn.setTop(rIn.top() + 60);                 rIn.setHeight(60);

    painter.setFont(f_lijn);
    painter.setPen(penWit);
    rCode.setWidth(400);
    painter.drawText(rCode,Qt::AlignHCenter | Qt::AlignVCenter,"Per BTW tarief:");
    painter.drawText(rPerc,Qt::AlignHCenter | Qt::AlignVCenter,"BTW %");
    painter.drawText(rEx,Qt::AlignHCenter | Qt::AlignVCenter,"Excl.BTW");
    painter.drawText(rBtw,Qt::AlignHCenter | Qt::AlignVCenter,"BTW");
    painter.drawText(rIn,Qt::AlignHCenter | Qt::AlignVCenter,"Incl.BTW");
    painter.setPen(penDonker);

    OmzetPerBTW_Model = new QSqlQueryModel();
    Ticket::getOmzetPerBTW(ui->dtpDatum->dateTime(), OmzetPerBTW_Model);
    rijen = OmzetPerBTW_Model->rowCount();
    teller = 0;
    for (int i = 0 ; i < rijen ; i++)
    {
        teller++;
        LR.setTop(LR.top() + 60);LR.setHeight(60);
        if (teller % 2 == 0)
        {
            painter.fillRect(LR, QBrush(QColor("#ffdab3"), Qt::SolidPattern));
        }
        else
        {
            painter.fillRect(LR, QBrush(QColor(Qt::white), Qt::SolidPattern));
        }
        rCode.setTop(rCode.top() + 60);             rCode.setHeight(60);
        rPerc.setTop(rPerc.top() + 60);             rPerc.setHeight(60);
        rEx.setTop(rEx.top() + 60);                 rEx.setHeight(60);
        rBtw.setTop(rBtw.top() + 60);               rBtw.setHeight(60);
        rIn.setTop(rIn.top() + 60);                 rIn.setHeight(60);

        painter.setFont(f_btw);
        painter.drawText(rPerc,Qt::AlignHCenter|Qt::AlignVCenter,QString("%1")
                         .arg(OmzetPerBTW_Model->record(i).field("perc").value().toDouble(), 0, 'f', 2));
        painter.drawText(rEx,Qt::AlignRight|Qt::AlignVCenter,QString("%1")
                         .arg(OmzetPerBTW_Model->record(i).field("ex").value().toDouble(), 0, 'f', 2));
        painter.drawText(rBtw,Qt::AlignRight|Qt::AlignVCenter,QString("%1")
                         .arg(OmzetPerBTW_Model->record(i).field("btw").value().toDouble(), 0, 'f', 2));
        painter.drawText(rIn,Qt::AlignRight|Qt::AlignVCenter,QString("%1")
                         .arg(OmzetPerBTW_Model->record(i).field("incl").value().toDouble(), 0, 'f', 2));

    }

    LR.setTop(LR.top() + 60);LR.setHeight(60);
    painter.fillRect(LR, QBrush(QColor("#4d2800"), Qt::SolidPattern));
    rCode.setTop(rCode.top() + 60);             rCode.setHeight(60);
    rPerc.setTop(rPerc.top() + 60);             rPerc.setHeight(60);
    rEx.setTop(rEx.top() + 60);                 rEx.setHeight(60);
    rBtw.setTop(rBtw.top() + 60);               rBtw.setHeight(60);
    rIn.setTop(rIn.top() + 60);                 rIn.setHeight(60);

    painter.setFont(f_lijn);
    painter.setPen(penWit);
    rCode.setWidth(400);
    painter.drawText(rCode,Qt::AlignHCenter | Qt::AlignVCenter,"Totaal betaalde Tickets:");
    painter.drawText(rPerc,Qt::AlignHCenter | Qt::AlignLeft,QString("%1 €").arg(Ticket::getTicketTotaal(ui->dtpDatum->dateTime()), 0, 'f', 2));
    painter.drawText(rBtw,Qt::AlignHCenter | Qt::AlignVCenter,"Totaal Lijnen:");
    painter.drawText(rIn,Qt::AlignHCenter | Qt::AlignLeft,QString("%1 €").arg(Ticket::getOmzetTotaa(ui->dtpDatum->dateTime()), 0, 'f', 2));

    int TweedeDeel = LR.top() + 100;

    LR = QRect(1100, TweedeDeel, 900, 120);
    painter.fillRect(LR,QBrush(QColor("#4d2800"), Qt::SolidPattern));
    LR.setHeight(60);
    painter.setFont(f_lijn);
    painter.setPen(penWit);
    painter.drawText(LR, Qt::AlignHCenter|Qt::AlignVCenter, "Kasboek");
    LR.setTop(LR.top() + 60);LR.setHeight(60);
    rBenaming = QRect(1100, TweedeDeel+60, 400, 60);
    rIn = QRect(1500, TweedeDeel+60, 250, 60);
    rEx = QRect(1750, TweedeDeel+60, 250, 60);
    painter.drawText(rBenaming, Qt::AlignHCenter|Qt::AlignVCenter, "Betaalwijze:");
    painter.drawText(rIn, Qt::AlignHCenter|Qt::AlignVCenter, "Inkomsten");
    painter.drawText(rEx, Qt::AlignHCenter|Qt::AlignVCenter, "Uitgaven");

    Kasboek_Model = new QSqlQueryModel();
    Kasboek::getKassaTotalen(ui->dtpDatum->dateTime(), Kasboek_Model);
    rijen = Kasboek_Model->rowCount();
    teller = 0;
    painter.setPen(penDonker);
    double in, uit;
    in = 0;  uit = 0;
    for (int i = 0 ; i < rijen ; i++)
    {
        teller++;
        LR.setTop(LR.top() + 60);LR.setHeight(60);
        if (teller % 2 == 0)
        {
            painter.fillRect(LR, QBrush(QColor("#ffdab3"), Qt::SolidPattern));
        }
        else
        {
            painter.fillRect(LR, QBrush(QColor(Qt::white), Qt::SolidPattern));
        }
        rBenaming.setTop(rBenaming.top() + 60);     rBenaming.setHeight(60);
        rEx.setTop(rEx.top() + 60);                 rEx.setHeight(60);
        rIn.setTop(rIn.top() + 60);                 rIn.setHeight(60);

        painter.setFont(f_btw);
        painter.drawText(rBenaming,Qt::AlignHCenter|Qt::AlignVCenter,QString("%1")
                         .arg(Kasboek_Model->record(i).field("omschrijving").value().toString()));
        painter.drawText(rEx,Qt::AlignRight|Qt::AlignVCenter,QString("%1")
                         .arg(Kasboek_Model->record(i).field("uitgaven").value().toDouble(), 0, 'f', 2));
        painter.drawText(rIn,Qt::AlignRight|Qt::AlignVCenter,QString("%1")
                         .arg(Kasboek_Model->record(i).field("inkomsten").value().toDouble(), 0, 'f', 2));
        in += Kasboek_Model->record(i).value("inkomsten").toDouble();
        uit += Kasboek_Model->record(i).value("uitgaven").toDouble();
    }
    LR.setTop(LR.top() + 60);LR.setHeight(60);
    painter.fillRect(LR, QBrush(QColor("#4d2800"), Qt::SolidPattern));
    rBenaming.setTop(rBenaming.top() + 60);         rBenaming.setHeight(60);
    rEx.setTop(rEx.top() + 60);                 rEx.setHeight(60);
    rIn.setTop(rIn.top() + 60);                 rIn.setHeight(60);

    painter.setFont(f_lijn);
    painter.setPen(penWit);
    painter.drawText(rBenaming,Qt::AlignHCenter | Qt::AlignVCenter,"Totalen:");
    painter.drawText(rEx,Qt::AlignHCenter | Qt::AlignRight, QString("%1 €").arg(uit, 0, 'f', 2));
    painter.drawText(rIn,Qt::AlignHCenter | Qt::AlignRight,QString("%1 €").arg(in, 0, 'f', 2));

    // Uitgaven =========================================================

    LR = QRect(150, TweedeDeel, 900, 120);
    painter.fillRect(LR,QBrush(QColor("#4d2800"), Qt::SolidPattern));
    LR.setHeight(60);
    painter.setFont(f_lijn);
    painter.setPen(penWit);
    painter.drawText(LR, Qt::AlignHCenter|Qt::AlignVCenter, "Detail uitgaven:");
    LR.setTop(LR.top() + 60);LR.setHeight(60);
    rBenaming = QRect(150, TweedeDeel+60, 500, 60);
    rEx = QRect(650, TweedeDeel+60, 300, 60);
    painter.drawText(rBenaming, Qt::AlignHCenter|Qt::AlignVCenter, "Omschrijving/reden:");
    painter.drawText(rEx, Qt::AlignHCenter|Qt::AlignVCenter, "Bedrag");

    Uitgaven_Model = new QSqlQueryModel();
    Kasboek::GetUitgaveTotalen(ui->dtpDatum->dateTime(), Uitgaven_Model);
    rijen = Uitgaven_Model->rowCount();
    teller = 0;
    painter.setPen(penDonker);
    in = 0;  uit = 0;
    for (int i = 0 ; i < rijen ; i++)
    {
        teller++;
        LR.setTop(LR.top() + 60);LR.setHeight(60);
        if (teller % 2 == 0)
        {
            painter.fillRect(LR, QBrush(QColor("#ffdab3"), Qt::SolidPattern));
        }
        else
        {
            painter.fillRect(LR, QBrush(QColor(Qt::white), Qt::SolidPattern));
        }
        rBenaming.setTop(rBenaming.top() + 60);     rBenaming.setHeight(60);
        rEx.setTop(rEx.top() + 60);                 rEx.setHeight(60);
        rIn.setTop(rIn.top() + 60);                 rIn.setHeight(60);

        painter.setFont(f_btw);
        painter.drawText(rBenaming,Qt::AlignHCenter|Qt::AlignVCenter,QString("%1")
                         .arg(Uitgaven_Model->record(i).field("reden").value().toString()));
        painter.drawText(rEx,Qt::AlignRight|Qt::AlignVCenter,QString("%1")
                         .arg(Uitgaven_Model->record(i).field("bedrag").value().toDouble(), 0, 'f', 2));
    }
    LR.setTop(LR.top() + 60);LR.setHeight(60);
    painter.fillRect(LR, QBrush(QColor("#4d2800"), Qt::SolidPattern));
    rBenaming.setTop(rBenaming.top() + 60);         rBenaming.setHeight(60);
    rEx.setTop(rEx.top() + 60);                 rEx.setHeight(60);
    rIn.setTop(rIn.top() + 60);                 rIn.setHeight(60);

    painter.setFont(f_lijn);
    painter.setPen(penWit);


    painter.end();
}

void Dagrapport::on_btnFacturatie_clicked()
{
    QMessageBox msgBox;
    msgBox.setText("<strong>Dag-Facturatie !</strong>");
    msgBox.setInformativeText("Wil u zeker deze dag factureren\ndit is definitief en kan niet ongedaan gemaakt worden.\nIS HET DAT WAT U WENST TE DOEN ?");
    msgBox.setStandardButtons(QMessageBox::Cancel | QMessageBox::Ok);
    msgBox.setDefaultButton(QMessageBox::Cancel);
    msgBox.setIcon(QMessageBox::Question);
    msgBox.setWindowTitle("Opgepast !");
    //msgBox.setStyleSheet("min-width: 150px;");
    QSpacerItem *hs = new QSpacerItem(400, 0, QSizePolicy::Minimum, QSizePolicy::Expanding);
    QGridLayout *gl = (QGridLayout*)msgBox.layout();
    gl->addItem(hs, gl->rowCount(), 0, 1, gl->columnCount());
    if (msgBox.exec() == QMessageBox::Ok)
    {
        FactuurHeader* fh = new FactuurHeader();
        Relaties *rel = new Relaties(17);
        fh->setKlant_ID(rel->getRelatie_ID());
        fh->setKlantNaam(rel->getNaam());
        fh->setKlantAdres(rel->getAdres()+" "+rel->getNrBus());
        fh->setKlantGemeente(Postcodes::getGemeente(rel->getGemeente_ID()));
        fh->setKlantPostcode(Postcodes::getPocode(rel->getGemeente_ID()));
        fh->setKlantLand(Landen::getLandByCode(rel->getLandCode()));
        fh->setTijdstip(ui->dtpDatum->date());
        fh->save();
        QSqlQueryModel* TeFacturerenPerRubiek_Model = new QSqlQueryModel();
        TicketLine::getTeFacturerenPerRubiek(ui->dtpDatum->dateTime(), TeFacturerenPerRubiek_Model);
        for (int teller = 0; teller < TeFacturerenPerRubiek_Model->rowCount(); teller++)
        {
            FactuurLine* fl = new FactuurLine();
            fl->setFactuur_ID(fh->getFactuur_ID());
            fl->setArtikel_ID(0);
            fl->setArtikelCode(TeFacturerenPerRubiek_Model->record(teller).value("code").toString());
            fl->setOmschrijving(TeFacturerenPerRubiek_Model->record(teller).value("benaming").toString());
            fl->setEenheidsprijs(TeFacturerenPerRubiek_Model->record(teller).value("ex").toDouble());
            fl->setAantal(1);
            fl->setEenheid("-");
            fl->setBTW_Percent(TeFacturerenPerRubiek_Model->record(teller).value("perc").toDouble());
            fl->setKortingPercent(0);
            fl->save();
        }
        FactuurFiche ff(fh->getFactuur_ID());
        ff.exec();
        TicketLine::setTicketGefactureerd(ui->dtpDatum->dateTime(), fh->getKlant_ID(), fh->getFactuur_ID());

//        msgBox.setText("<strong>Dag-Facturatie !</strong>");
//        msgBox.setInformativeText("Is de facturatie gelukt\nKAN DE FACTUUR DEFINITIEF VERWERKT WORDEN?");
//        msgBox.setStandardButtons(QMessageBox::Cancel | QMessageBox::Ok);
//        msgBox.setDefaultButton(QMessageBox::Cancel);
//        msgBox.setIcon(QMessageBox::Question);
//        msgBox.setWindowTitle("Opgepast !");
//        //msgBox.setStyleSheet("min-width: 150px;");
//        QSpacerItem *hs = new QSpacerItem(400, 0, QSizePolicy::Minimum, QSizePolicy::Expanding);
//        QGridLayout *gl = (QGridLayout*)msgBox.layout();
//        gl->addItem(hs, gl->rowCount(), 0, 1, gl->columnCount());
//        if (msgBox.exec() == QMessageBox::Ok)
//        {
//            TicketLine::setTicketGefactureerd(ui->dtpDatum->dateTime(), fh->getKlant_ID(), fh->getFactuur_ID());
//        }
    }
}

void Dagrapport::on_pushButton_clicked()
{
    Betaalmiddel* bet = new Betaalmiddel(datum, this);
    bet->exec();
    delete bet;
    FillScreen();
}
