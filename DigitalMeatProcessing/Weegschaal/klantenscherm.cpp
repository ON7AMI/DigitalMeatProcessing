#include "klantenscherm.h"
#include "ui_klantenscherm.h"
#include "tickerow.h"


#include <QObject>
#include <QDebug>
#include <QApplication>
#include <QSettings>
#include <QLocale>
#include <QDialog>
#include <QDateTime>
#include <QDesktopWidget>
#include <QSqlRecord>
#include <QSqlField>
#include <QListWidgetItem>
#

KlantenScherm::KlantenScherm(Weegschaal* _ws, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::KlantenScherm)
{
    ui->setupUi(this);
    QRect screenres = QApplication::desktop()->screenGeometry(1/*screenNumber*/);
    this->move(QPoint(screenres.x(), screenres.y()));
    //this->setWindowFlags(Qt::Window | Qt::FramelessWindowHint);
    this->showFullScreen();
    VorigePersWissel = -1;
    PixTeller = 0;
    PixSwitch = 0;
    ws = _ws;

    DisplayTimer = new QTimer(this);
    connect(DisplayTimer, SIGNAL(timeout()), this, SLOT(SchrijfDisplay()));
    DisplayTimer->start(500);

    effect1 = new QGraphicsOpacityEffect(this);
    effect2 = new QGraphicsOpacityEffect(this);

    ui->lbPix_1->setGraphicsEffect(effect1);
    ui->lbPix_2->setGraphicsEffect(effect2);
    PixDir = new QDir();
    PixTimer = new QTimer(this);
    connect(PixTimer, SIGNAL(timeout()), this, SLOT(ShowPictures()));
    PixTimer->start(15000);

}

KlantenScherm::~KlantenScherm()
{
    delete ui;
    delete ws;
    delete DisplayTimer;
    delete PixTimer;
}

void KlantenScherm::SchrijfDisplay()
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
    ui->lbProduct->setText(ws->ProductBenaming);
    ui->lbKg->setText(ws->VerkoopsEenheid);
    ui->lbPrijspereenheid->setText(QString("Prijs per %1 aan %2 €.").arg(ws->VerkoopsEenheid).arg(ws->PrijsPerEenheid,0,'f',2));
    ui->lbPromo->setVisible(ws->Promo);
    ui->lcdPrijs->display(QString("%1").arg(prijs,10,'f',2));
    if (VorigePersWissel != ws->PersWissel)
    {
        ui->lbVerkoperNaam->setText(QString("U wordt geholpen door: %1").arg(ws->PersNaam));
        ui->lbGeholpen->setText(QString("U wordt geholpen door: %1").arg(ws->PersNaam));
        FillTicket();
        VorigePersWissel = ws->PersWissel;
    }
}

void KlantenScherm::FillTicket()
{
    ui->lbTicketNr->setText( QString("Ticket nummer: %1").arg(ws->TicketNummer));
    ui->lstwTicket->clear();

    QVariant nr;
    TickeRow* tr;
    QListWidgetItem *item;

    QSqlQueryModel* mod = new QSqlQueryModel();
    TicketLine::getLinesByTicketID(ws->TicketID, mod);

    double totaal = 0;

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
    ui->lbToaal->setText(QString("Totaal:  %1 €").arg(totaal, 0,'f',2));
}


void KlantenScherm::ShowPictures()
{
    QString m_sSettingsFile = QApplication::applicationDirPath() + "/appSettings.ini";
    QSettings settings(m_sSettingsFile, QSettings::NativeFormat);

    QString AfbeeldingMap = settings.value("Diverse/KassaAfbeeldingenMap", "").toString();

    QString path;
    if (PixTeller == 0)
    {
        QStringList extentions;
        extentions.append("*.jpg");
        extentions.append("*.gif");
        extentions.append("*.png");
        PixDir->setNameFilters(extentions);
        PixDir->setFilter(QDir::Files | QDir::NoDotAndDotDot | QDir::NoSymLinks);
        PixDir->setPath(AfbeeldingMap);
        PixTeller = PixDir->entryList().count();
    }

    if (PixTeller <= PixDir->entryList().count())
    {
        path =PixDir->dirName();
        QString filename = QString("%1/%2").arg(AfbeeldingMap).arg(PixDir->entryList()[--PixTeller]);

        //if (!filename.isEmpty())
        animation1 = new QPropertyAnimation(effect1, "opacity");
        animation2 = new QPropertyAnimation(effect2, "opacity");

        if (PixSwitch == 0)
        {
            QPixmap image(filename);
            ui->lbPix_1->setPixmap(image.scaled(ui->lbPix_1->width(), ui->lbPix_1->height(), Qt::KeepAspectRatio));
            //ui->lbPix_1->setVisible(true);
            //ui->lbPix_2->setVisible(true);
            animation2->setDuration(1000);
            animation2->setStartValue(1.0);
            animation2->setEndValue(0.0);
            //animation2->setEasingCurve(QEasingCurve::OutQuad);
            animation2->start();
            //ui->lbPix_1->setVisible(false);
            animation1->setDuration(1000);
            animation1->setStartValue(0.0);
            animation1->setEndValue(1.0);
            //animation1->setEasingCurve(QEasingCurve::OutQuad);
            animation1->start();
            PixSwitch = 1;
        }
        else
        {
            QPixmap image(filename);
            ui->lbPix_2->setPixmap(image.scaled(ui->lbPix_1->width(), ui->lbPix_1->height(), Qt::KeepAspectRatio));
            animation1->setDuration(1000);
            animation1->setStartValue(1.0);
            animation1->setEndValue(0.0);
            //animation1->setEasingCurve(QEasingCurve::OutQuad);
            animation1->start();
            //animation1->start(QAbstractAnimation::DeleteWhenStopped);
            //ui->lbPix_2->setVisible(false);
            animation2->setDuration(1000);
            animation2->setStartValue(0.0);
            animation2->setEndValue(1.0);
            //animation2->setEasingCurve(QEasingCurve::OutQuad);
            animation2->start();

            PixSwitch = 0;
        }
    }
    else
    {
        PixTeller = 0;
    }

}
