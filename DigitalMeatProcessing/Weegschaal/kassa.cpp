#include "kassa.h"
#include "ui_kassa.h"

#include <math.h>

#include "tickerow.h"
#include "ticket.h"
#include "CommonObjects/numkeyboard.h"
#include "Boekhouding/kasboek.h"
#include "Productie/lotnummerdata.h"

#include <QSqlQueryModel>
#include <QSqlRecord>
#include <QListWidgetItem>
#include <QMessageBox>
#include <QSpacerItem>
#include <QGridLayout>
#include <QPrinterInfo>
#include <QApplication>
#include <QSettings>
#include <QList>
#include <QDebug>
#include <QPrinter>
#include <QPainter>
#include <QTimer>
#include <QtMath>


Kassa::Kassa(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Kassa)
{
    ui->setupUi(this);

    this->setWindowFlags(Qt::Window | Qt::FramelessWindowHint);
    this->showFullScreen();

    ticket = new Ticket();

    UitgaveReden_model = new QSqlQueryModel();
    Kasboek::getUitgaveRedenen(UitgaveReden_model);
    ui->cbxReden->setModel(UitgaveReden_model);


    ClearFields();
    ui->btnUitgaven->setEnabled(true);
    ui->lbAfrekenen->setEnabled(true);

    ui->cbxReden->setEnabled(false);
    ui->tbBedragUitgave->setEnabled(false);

    ui->btnBankcontact->setEnabled(false);
    ui->btnContant->setEnabled(false);
    ui->btnKredietkaart->setEnabled(false);
    ui->btnMaaltijdcheque->setEnabled(false);
    ui->btnMCmin->setEnabled(false);
    ui->btnMCPlus->setEnabled(false);
    ui->btntegoedbon->setEnabled(false);
    ui->btnNaarFactuur->setEnabled(false);
    ui->tbBankcontact->setEnabled(false);
    ui->tbContant->setEnabled(false);
    ui->tbKredietkaart->setEnabled(false);
    ui->tbMaaltijdcheque->setEnabled(false);
    ui->tbMCwaarde->setEnabled(false);
    ui->tbTegoedbon->setEnabled(false);
    ui->tbNaarFactuur->setEnabled(false);
    ui->tbOntvangen->setText("0");
    ui->tbTerug->setText("0");

    ui->btnSelect_0->setEnabled(true);
    ui->btnSelect_1->setEnabled(true);
    ui->btnSelect_2->setEnabled(true);
    ui->btnSelect_3->setEnabled(true);
    ui->btnSelect_4->setEnabled(true);
    ui->btnSelect_5->setEnabled(true);
    ui->btnSelect_6->setEnabled(true);
    ui->btnSelect_7->setEnabled(true);

    FillTicketsList();

    DisplayTimer = new QTimer(this);
    connect(DisplayTimer, SIGNAL(timeout()), this, SLOT(SchrijfDisplay()));
    DisplayTimer->start(2000);


}

Kassa::~Kassa()
{
    delete ui;
    delete ticket;
    delete ticketRow;
    delete DisplayTimer;
}

void Kassa::SchrijfDisplay()
{
    FillTicketsList();
}

void Kassa::ClearFields()
{
    ui->lcdTeBetalen->display("0.00");
    ui->lbTotaal->setText("0.00");
    ui->lbReedsBetaald->setText("0.00");
    ui->lbRest->setText("0.00");
    ui->tbContant->setText("0.00");
    ui->tbKredietkaart->setText("0.00");
    ui->tbMaaltijdcheque->setText("0.00");
    ui->tbMCwaarde->setText("0.00");
    ui->lbMCaantal->setText("x 0");
    ui->tbBankcontact->setText("0.00");
    ui->tbTegoedbon->setText("0.00");
    ui->tbNaarFactuur->setText("0.00");
}

void Kassa::FillTicketsList()
{
    QString regel;
    int AantalRijen = 0;
    QSqlQueryModel* _mod = new QSqlQueryModel();
    Ticket::TeBetalenTickets(_mod);

    AantalRijen = _mod->rowCount();

    if (AantalRijen >= 1)
    {
        regel = QString("Tijdstip: %1\nVerkoper: %2\nBedrag: %3\n-------------")
                .arg(_mod->record(0).value("tijdstip").toString())
                .arg(_mod->record(0).value("verkoper_naam").toString())
                .arg(_mod->record(0).value("totaal_incl_btw").toDouble(), 0,'f',2);
        int id = _mod->record(0).value("ticket_id").toInt();
        ui->btnSelect_0->setText(regel);
        ui->btnSelect_0->setStatusTip(QString::number(id));
    }
    else
    {
        ui->btnSelect_0->setText("");
        ui->btnSelect_0->setStatusTip("0");
    }

    if (AantalRijen >= 2)
    {
        regel = QString("Tijdstip: %1\nVerkoper: %2\nBedrag: %3\n-------------")
                .arg(_mod->record(1).value("tijdstip").toString())
                .arg(_mod->record(1).value("verkoper_naam").toString())
                .arg(_mod->record(1).value("totaal_incl_btw").toDouble(), 0,'f',2);
        int id = _mod->record(1).value("ticket_id").toInt();
        ui->btnSelect_1->setText(regel);
        ui->btnSelect_1->setStatusTip(QString::number(id));
    }
    else
    {
        ui->btnSelect_1->setText("");
        ui->btnSelect_1->setStatusTip("0");
    }

    if (AantalRijen >= 3)
    {
        regel = QString("Tijdstip: %1\nVerkoper: %2\nBedrag: %3\n-------------")
                .arg(_mod->record(2).value("tijdstip").toString())
                .arg(_mod->record(2).value("verkoper_naam").toString())
                .arg(_mod->record(2).value("totaal_incl_btw").toDouble(), 0,'f',2);
        int id = _mod->record(2).value("ticket_id").toInt();
        ui->btnSelect_2->setText(regel);
        ui->btnSelect_2->setStatusTip(QString::number(id));
    }
    else
    {
        ui->btnSelect_2->setText("");
        ui->btnSelect_2->setStatusTip("0");
    }

    if (AantalRijen >= 4)
    {
        regel = QString("Tijdstip: %1\nVerkoper: %2\nBedrag: %3\n-------------")
                .arg(_mod->record(3).value("tijdstip").toString())
                .arg(_mod->record(3).value("verkoper_naam").toString())
                .arg(_mod->record(3).value("totaal_incl_btw").toDouble(), 0,'f',2);
        int id = _mod->record(3).value("ticket_id").toInt();
        ui->btnSelect_3->setText(regel);
        ui->btnSelect_3->setStatusTip(QString::number(id));
    }
    else
    {
        ui->btnSelect_3->setText("");
        ui->btnSelect_3->setStatusTip("0");
    }

    if (AantalRijen >= 5)
    {
        regel = QString("Tijdstip: %1\nVerkoper: %2\nBedrag: %3\n-------------")
                .arg(_mod->record(4).value("tijdstip").toString())
                .arg(_mod->record(4).value("verkoper_naam").toString())
                .arg(_mod->record(4).value("totaal_incl_btw").toDouble(), 0,'f',2);
        int id = _mod->record(4).value("ticket_id").toInt();
        ui->btnSelect_4->setText(regel);
        ui->btnSelect_4->setStatusTip(QString::number(id));
    }
    else
    {
        ui->btnSelect_4->setText("");
        ui->btnSelect_4->setStatusTip("0");
    }

    if (AantalRijen >= 6)
    {
        regel = QString("Tijdstip: %1\nVerkoper: %2\nBedrag: %3\n-------------")
                .arg(_mod->record(5).value("tijdstip").toString())
                .arg(_mod->record(5).value("verkoper_naam").toString())
                .arg(_mod->record(5).value("totaal_incl_btw").toDouble(), 0,'f',2);
        int id = _mod->record(5).value("ticket_id").toInt();
        ui->btnSelect_5->setText(regel);
        ui->btnSelect_5->setStatusTip(QString::number(id));
    }
    else
    {
        ui->btnSelect_5->setText("");
        ui->btnSelect_5->setStatusTip("0");
    }

    if (AantalRijen >= 7)
    {
        regel = QString("Tijdstip: %1\nVerkoper: %2\nBedrag: %3\n-------------")
                .arg(_mod->record(6).value("tijdstip").toString())
                .arg(_mod->record(6).value("verkoper_naam").toString())
                .arg(_mod->record(6).value("totaal_incl_btw").toDouble(), 0,'f',2);
        int id = _mod->record(6).value("ticket_id").toInt();
        ui->btnSelect_6->setText(regel);
        ui->btnSelect_6->setStatusTip(QString::number(id));
    }
    else
    {
        ui->btnSelect_6->setText("");
        ui->btnSelect_6->setStatusTip("0");
    }

    if (AantalRijen >= 8)
    {
        regel = QString("Tijdstip: %1\nVerkoper: %2\nBedrag: %3\n-------------")
                .arg(_mod->record(7).value("tijdstip").toString())
                .arg(_mod->record(7).value("verkoper_naam").toString())
                .arg(_mod->record(7).value("totaal_incl_btw").toDouble(), 0,'f',2);
        int id = _mod->record(7).value("ticket_id").toInt();
        ui->btnSelect_7->setText(regel);
        ui->btnSelect_7->setStatusTip(QString::number(id));
    }
    else
    {
        ui->btnSelect_7->setText("");
        ui->btnSelect_7->setStatusTip("0");
    }

}

void Kassa::on_btnStop_clicked()
{
    this->close();
}

void Kassa::FillTicket()
{
    ui->lbTicketNr->setText( QString("Ticket nummer: %1").arg(ticket->getVolgnummer()));
    ui->lstwTicket->clear();

    QVariant nr;
    TickeRow* tr;
    QListWidgetItem *item;

    QSqlQueryModel* mod = new QSqlQueryModel();
    TicketLine::getLinesByTicketID(ticket->getTicket_ID(), mod);

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
    delete mod;
    TeBetalen = ticket->getTotaal_Incl_BTW();
    Rest = TeBetalen - ReedsBetaald;
    UpdateDisplay();
}

void Kassa::UpdateDisplay()
{
    ui->lbTotaal->setText(QString("Totaal te betalen: %1 €").arg(TeBetalen, 0,'f',2));
    ui->lbReedsBetaald->setText(QString("Reeds betaald: %1 €").arg(ReedsBetaald, 0,'f',2));
    ui->lbRest->setText(QString("Rest nog te betalen: %1 €").arg(Rest, 0,'f',2));
    ui->lcdTeBetalen->display(QString("%1").arg(Rest, 0,'f',2));
}


void Kassa::on_btnPrintTicket_clicked()
{
    double bet, tebet;
    bet = Contant + Bankcontact + Kredietkaart + Maaltijdcheques + Tegoedbon + Factuur;
    if (SoortDoc != "U")
        tebet = ticket->getTotaal_Incl_BTW();
    else
        tebet = 0;

    if (qFabs(bet - tebet) > 0.01)
    {
        QMessageBox msgBox;
        msgBox.setText("<strong>Openstaand bedrag !</strong>");
        msgBox.setInformativeText("U moet het te betalen bedrag volledig toewijzen aan de betaalmiddelen.\nWerk eerst de verschillen weg");
        msgBox.setStandardButtons(QMessageBox::Cancel);
        msgBox.setDefaultButton(QMessageBox::Cancel);
        msgBox.setIcon(QMessageBox::Warning);
        msgBox.setWindowTitle("Opgepast !");
        QSpacerItem *hs = new QSpacerItem(400, 0, QSizePolicy::Minimum, QSizePolicy::Expanding);
        QGridLayout *gl = (QGridLayout*)msgBox.layout();
        gl->addItem(hs, gl->rowCount(), 0, 1, gl->columnCount());
        msgBox.exec();
    }
    else
    {

        if ((Rest < -0.01) || (Rest > 0.01))
        {
            QMessageBox msgBox;
            msgBox.setText("<strong>Niet op NUL !</strong>");
            msgBox.setInformativeText("Het nog te ontvangen bedrag is niet nul.\nWerk eerst de verschillen weg");
            msgBox.setStandardButtons(QMessageBox::Cancel);
            msgBox.setDefaultButton(QMessageBox::Cancel);
            msgBox.setIcon(QMessageBox::Warning);
            msgBox.setWindowTitle("Opgepast !");
            QSpacerItem *hs = new QSpacerItem(400, 0, QSizePolicy::Minimum, QSizePolicy::Expanding);
            QGridLayout *gl = (QGridLayout*)msgBox.layout();
            gl->addItem(hs, gl->rowCount(), 0, 1, gl->columnCount());
            msgBox.exec();

        }
        else
        {
            PrintTicket();
            BoekKasboek();
            if (SoortDoc == "O")
            {
                PasStockAan();
            }

            ticket->setBetaald(true);
            if (Factuur != 0)
            {
                ticket->setNaar_Factuur(true);
            }
            ticket->save();

            Ticket::LogTicketControle(ticket->getTicket_ID());


            ClearFields();
            ui->lbTicketNr->setText( "Ticket nummer: ");
            ui->lstwTicket->clear();
            ticket = new Ticket();

            ui->btnUitgaven->setEnabled(true);
            ui->lbAfrekenen->setEnabled(true);

            ui->cbxReden->setEnabled(false);
            ui->tbBedragUitgave->setEnabled(false);

            ui->btnBankcontact->setEnabled(false);
            ui->btnContant->setEnabled(false);
            ui->btnKredietkaart->setEnabled(false);
            ui->btnMaaltijdcheque->setEnabled(false);
            ui->btnMCmin->setEnabled(false);
            ui->btnMCPlus->setEnabled(false);
            ui->btntegoedbon->setEnabled(false);
            ui->btnNaarFactuur->setEnabled(false);
            ui->tbBankcontact->setEnabled(false);
            ui->tbContant->setEnabled(false);
            ui->tbKredietkaart->setEnabled(false);
            ui->tbMaaltijdcheque->setEnabled(false);
            ui->tbMCwaarde->setEnabled(false);
            ui->tbTegoedbon->setEnabled(false);
            ui->tbNaarFactuur->setEnabled(false);
            ui->tbOntvangen->setText("0");
            ui->tbTerug->setText("0");

            ui->btnSelect_0->setEnabled(true);
            ui->btnSelect_1->setEnabled(true);
            ui->btnSelect_2->setEnabled(true);
            ui->btnSelect_3->setEnabled(true);
            ui->btnSelect_4->setEnabled(true);
            ui->btnSelect_5->setEnabled(true);
            ui->btnSelect_6->setEnabled(true);
            ui->btnSelect_7->setEnabled(true);


            FillTicketsList();
        }
    }
}

void Kassa::PasStockAan()
{
    QSqlQueryModel* mod = new QSqlQueryModel();
    TicketLine::getLinesByTicketID(ticket->getTicket_ID(), mod);

    // Tickelijnen printen
    for(int i = 0; i < mod->rowCount() ; i++)
    {
        int lot_id = mod->record(i).value("lotnr_id").toInt();
        if (lot_id != 0)
        {
            LotnummerData* lot = new LotnummerData(lot_id);
            lot->setHoeveelheidUit(lot->getHoeveelheidUit() + mod->record(i).value("hoeveelheid").toDouble());
            lot->save();
            delete lot;
        }
    }
}

void Kassa::BoekKasboek()
{
    if (Contant != 0)
    {
        Kasboek* kb = new Kasboek();
        kb->setBetaalmiddel_ID(1);
        kb->setTicket_ID(ticket->getTicket_ID());
        kb->setOmschrijving(ticket->getVolgnummer());
        kb->setSoort(SoortDoc);
        kb->setTijdstip(QDateTime::currentDateTime());
        if (Contant >= 0)
            kb->setBedragIn(Contant);
        else
            kb->setBedragUit(Contant);
        kb->save();
        delete kb;
    }

    if (Bankcontact != 0)
    {
        Kasboek* kb = new Kasboek();
        kb->setBetaalmiddel_ID(2);
        kb->setTicket_ID(ticket->getTicket_ID());
        kb->setOmschrijving(ticket->getVolgnummer());
        kb->setSoort(SoortDoc);
        kb->setTijdstip(QDateTime::currentDateTime());
        if (Bankcontact >= 0)
            kb->setBedragIn(Bankcontact);
        else
            kb->setBedragUit(Bankcontact);
        kb->save();
        delete kb;
    }

    if (Kredietkaart != 0)
    {
        Kasboek* kb = new Kasboek();
        kb->setBetaalmiddel_ID(3);
        kb->setTicket_ID(ticket->getTicket_ID());
        kb->setOmschrijving(ticket->getVolgnummer());
        kb->setSoort(SoortDoc);
        kb->setTijdstip(QDateTime::currentDateTime());
        if (Kredietkaart >= 0)
            kb->setBedragIn(Kredietkaart);
        else
            kb->setBedragUit(Kredietkaart);
        kb->save();
        delete kb;
    }

    if (Maaltijdcheques != 0)
    {
        Kasboek* kb = new Kasboek();
        kb->setBetaalmiddel_ID(4);
        kb->setTicket_ID(ticket->getTicket_ID());
        kb->setOmschrijving(ticket->getVolgnummer());
        kb->setSoort(SoortDoc);
        kb->setTijdstip(QDateTime::currentDateTime());
        if (Maaltijdcheques >= 0)
            kb->setBedragIn(Maaltijdcheques);
        else
            kb->setBedragUit(Maaltijdcheques);
        kb->save();
        delete kb;
    }

    if (Tegoedbon != 0)
    {
        Kasboek* kb = new Kasboek();
        kb->setBetaalmiddel_ID(5);
        kb->setTicket_ID(ticket->getTicket_ID());
        kb->setOmschrijving(ticket->getVolgnummer());
        kb->setSoort(SoortDoc);
        kb->setTijdstip(QDateTime::currentDateTime());
        if (Tegoedbon >= 0)
            kb->setBedragIn(Tegoedbon);
        else
            kb->setBedragUit(Tegoedbon);
        kb->save();
        delete kb;
    }

    if (Factuur != 0)
    {
        Kasboek* kb = new Kasboek();
        kb->setBetaalmiddel_ID(6);
        kb->setTicket_ID(ticket->getTicket_ID());
        kb->setOmschrijving(ticket->getVolgnummer());
        kb->setSoort(SoortDoc);
        kb->setTijdstip(QDateTime::currentDateTime());
        if (Factuur >= 0)
            kb->setBedragIn(Factuur);
        else
            kb->setBedragUit(Factuur);
        kb->save();
        delete kb;
    }

}

void Kassa::PrintTicket()
{
    timestamp = QDateTime::currentDateTime();
    double bedrag = 0;

    if (SoortDoc == "U")
    {

        bool ok;
        bedrag = ui->tbBedragUitgave->text().toDouble(&ok) ;

        if (!ok)
        {
            // je moet geldig getal invullen
            Contant = 0;
            QMessageBox msgBox;
            msgBox.setText("<strong>Foute ingave !</strong>");
            msgBox.setInformativeText("Je moet een geldig getal ingeven.\nEnkel cijfers, decimaal teken en het min-teken zijn toegelaten.");
            msgBox.setStandardButtons(QMessageBox::Cancel);
            msgBox.setDefaultButton(QMessageBox::Cancel);
            msgBox.setIcon(QMessageBox::Critical);
            msgBox.setWindowTitle("Opgepast !");
            QSpacerItem *hs = new QSpacerItem(400, 0, QSizePolicy::Minimum, QSizePolicy::Expanding);
            QGridLayout *gl = (QGridLayout*)msgBox.layout();
            gl->addItem(hs, gl->rowCount(), 0, 1, gl->columnCount());
            msgBox.exec();
            return;
        }

        if ((bedrag > 0) && (Kasboek::getUitgaveTeken(ui->cbxReden->currentText()) == "n"))
        {
            // je moet een negatief getal invullen
            Contant = 0;
            QMessageBox msgBox;
            msgBox.setText("<strong>Foute ingave !</strong>");
            msgBox.setInformativeText("Je moet een negatief getal ingeven.");
            msgBox.setStandardButtons(QMessageBox::Cancel);
            msgBox.setDefaultButton(QMessageBox::Cancel);
            msgBox.setIcon(QMessageBox::Critical);
            msgBox.setWindowTitle("Opgepast !");
            QSpacerItem *hs = new QSpacerItem(400, 0, QSizePolicy::Minimum, QSizePolicy::Expanding);
            QGridLayout *gl = (QGridLayout*)msgBox.layout();
            gl->addItem(hs, gl->rowCount(), 0, 1, gl->columnCount());
            msgBox.exec();
            return;
        }
        Contant = bedrag;
        ticket = new Ticket();
        ticket->setVerkoper_ID(0);
        ticket->setVerkoper_Naam("Kassa");
        ticket->setTijdstip(QDateTime::currentDateTime());
        ticket->setNaar_Factuur(false);
        ticket->setNaar_Kas(true);
        ticket->setBetaald(false);
        ticket->setTotaal_BTW(0);
        ticket->setTotaal_Ex_BTW(0);
        ticket->setTotaal_Incl_BTW(bedrag);
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
        TicketLine* tl = new TicketLine();
        tl->setArtCode("");
        tl->setArtID(0);
        tl->setArtOmschrijving(ui->cbxReden->currentText());
        tl->setBTWperc(0);
        tl->setEenheid("");
        tl->setEenheidsprijs(0);
        tl->setHoeveelheid(1);
        tl->setLotnrCode("");
        tl->setLotnrID(0);
        tl->setPrijsBTW(0);
        tl->setPrijsExBTW(0);
        tl->setPrijsInclBTW(bedrag);
        tl->setTicketID(ticket->getTicket_ID());
        tl->setTijdstip(QDateTime::currentDateTime());
        tl->save();

    }
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

    y_pos += 3;

    if (SoortDoc == "O")
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
    else
    {
        LR.setTop(y_pos * y_scale); LR.setHeight(10 * y_scale);
        painter.setFont(f_artikel);
        painter.drawText(LR,Qt::AlignLeft | Qt::AlignTop,ui->cbxReden->currentText());
        y_pos += 5;

        LR.setTop(y_pos * y_scale); LR.setHeight(10 * y_scale);
        painter.setFont(f_lijn);
        painter.drawText(LR, Qt::AlignLeft | Qt::AlignTop, "Betaald uit kas:");
        painter.drawText(LR, Qt::AlignRight | Qt::AlignTop, QString("%1 €")
                         .arg(bedrag, 0, 'f', 2)
                         );
        y_pos += 6;
        painter.drawLine(0,y_pos * y_scale ,68 * x_scale ,y_pos * y_scale);
        y_pos += 2;

    }
    // ======== Totaal blok ===========

    LR.setTop(y_pos * y_scale); LR.setHeight(10 * y_scale);
    painter.setFont(f_artikel);
    painter.drawText(LR,Qt::AlignLeft | Qt::AlignTop, "Totaal incl.BTW:");
    painter.setFont(f_artikel);
    painter.drawText(LR,Qt::AlignRight | Qt::AlignTop, QString("%1 €").arg(ticket->getTotaal_Incl_BTW(), 0, 'f', 2));
    y_pos += 5;

    painter.setFont(f_lijn);
    if (Factuur != 0)
    {
        LR.setTop(y_pos * y_scale); LR.setHeight(10 * y_scale);
        painter.drawText(LR,Qt::AlignLeft | Qt::AlignTop, "Te Factureren:");
        LR.setTop(y_pos * y_scale); LR.setHeight(10 * y_scale);
        painter.drawText(LR,Qt::AlignRight | Qt::AlignTop, QString("%1 €").arg(Factuur, 0, 'f', 2));
        y_pos += 4;
    }

    if (Tegoedbon !=0)
    {
        LR.setTop(y_pos * y_scale); LR.setHeight(10 * y_scale);
        painter.drawText(LR,Qt::AlignLeft | Qt::AlignTop, "Tegoed bon:");
        LR.setTop(y_pos * y_scale); LR.setHeight(10 * y_scale);
        painter.drawText(LR,Qt::AlignRight | Qt::AlignTop, QString("%1 €").arg(Tegoedbon, 0, 'f', 2));
        y_pos += 4;
    }

    if (Contant !=0)
    {
        LR.setTop(y_pos * y_scale); LR.setHeight(10 * y_scale);
        painter.drawText(LR,Qt::AlignLeft | Qt::AlignTop, "Betaald Cash:");
        LR.setTop(y_pos * y_scale); LR.setHeight(10 * y_scale);
        painter.drawText(LR,Qt::AlignRight | Qt::AlignTop, QString("%1 €").arg(Contant, 0, 'f', 2));
        y_pos += 4;
    }

    if (Bankcontact !=0)
    {
        LR.setTop(y_pos * y_scale); LR.setHeight(10 * y_scale);
        painter.drawText(LR,Qt::AlignLeft | Qt::AlignTop, "Betaald Bankcontact:");
        LR.setTop(y_pos * y_scale); LR.setHeight(10 * y_scale);
        painter.drawText(LR,Qt::AlignRight | Qt::AlignTop, QString("%1 €").arg(Bankcontact, 0, 'f', 2));
        y_pos += 4;
    }

    if (Kredietkaart !=0)
    {
        LR.setTop(y_pos * y_scale); LR.setHeight(10 * y_scale);
        painter.drawText(LR,Qt::AlignLeft | Qt::AlignTop, "Betaald Kredietkaart:");
        LR.setTop(y_pos * y_scale); LR.setHeight(10 * y_scale);
        painter.drawText(LR,Qt::AlignRight | Qt::AlignTop, QString("%1 €").arg(Kredietkaart, 0, 'f', 2));
        y_pos += 4;
    }

    if (Maaltijdcheques !=0)
    {
        LR.setTop(y_pos * y_scale); LR.setHeight(10 * y_scale);
        painter.drawText(LR,Qt::AlignLeft | Qt::AlignTop, "Maaltijdcheques:");
        LR.setTop(y_pos * y_scale); LR.setHeight(10 * y_scale);
        painter.drawText(LR,Qt::AlignRight | Qt::AlignTop, QString("%1 €").arg(Maaltijdcheques, 0, 'f', 2));
        y_pos += 4;
    }
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

void Kassa::on_lbAfrekenen_clicked()
{
    int _id = ticket->getTicket_ID();
    if (_id > 0)
    {
        Afrekenen();
    }
}

void Kassa::Afrekenen()
{
    ClearFields();
    SoortDoc = "O";
    Rest = TeBetalen = ticket->getTotaal_Incl_BTW();
    ReedsBetaald = 0;
    Contant = 0;
    Bankcontact = 0;
    Kredietkaart = 0;
    Factuur = 0;
    Maaltijdcheques = 0;
    MCeenheidsprijs = 0;
    MCaantal = 0;
    Tegoedbon = 0;

    ui->btnUitgaven->setEnabled(false);
    ui->lbAfrekenen->setEnabled(false);

    ui->cbxReden->setEnabled(false);
    ui->tbBedragUitgave->setEnabled(false);


    ui->btnBankcontact->setEnabled(true);
    ui->btnContant->setEnabled(true);
    ui->btnKredietkaart->setEnabled(true);
    ui->btnMaaltijdcheque->setEnabled(true);
    ui->btnMCmin->setEnabled(true);
    ui->btnMCPlus->setEnabled(true);
    ui->btntegoedbon->setEnabled(true);
    ui->btnNaarFactuur->setEnabled(true);
    ui->tbBankcontact->setEnabled(true);
    ui->tbContant->setEnabled(true);
    ui->tbKredietkaart->setEnabled(true);
    ui->tbMaaltijdcheque->setEnabled(true);
    ui->tbMCwaarde->setEnabled(true);
    ui->tbTegoedbon->setEnabled(true);
    ui->tbNaarFactuur->setEnabled(true);


    ui->btnSelect_0->setEnabled(false);
    ui->btnSelect_1->setEnabled(false);
    ui->btnSelect_2->setEnabled(false);
    ui->btnSelect_3->setEnabled(false);
    ui->btnSelect_4->setEnabled(false);
    ui->btnSelect_5->setEnabled(false);
    ui->btnSelect_6->setEnabled(false);
    ui->btnSelect_7->setEnabled(false);

    UpdateDisplay();
}

void Kassa::on_btnUitgaven_clicked()
{
    SoortDoc = "U";
    Rest = TeBetalen = 0;
    ReedsBetaald = 0;
    Rest = TeBetalen;
    Contant = 0;
    Bankcontact = 0;
    Kredietkaart = 0;
    Maaltijdcheques = 0;
    MCeenheidsprijs = 0;
    MCaantal = 0;
    Tegoedbon = 0;

    ui->lbAfrekenen->setEnabled(false);
    ui->btnUitgaven->setEnabled(false);

    ui->cbxReden->setEnabled(true);
    ui->tbBedragUitgave->setEnabled(true);


    ui->btnBankcontact->setEnabled(false);
    ui->btnContant->setEnabled(false);
    ui->btnKredietkaart->setEnabled(false);
    ui->btnMaaltijdcheque->setEnabled(false);
    ui->btnMCmin->setEnabled(false);
    ui->btnMCPlus->setEnabled(false);
    ui->btntegoedbon->setEnabled(false);
    ui->btnNaarFactuur->setEnabled(false);
    ui->tbBankcontact->setEnabled(false);
    ui->tbContant->setEnabled(false);
    ui->tbKredietkaart->setEnabled(false);
    ui->tbMaaltijdcheque->setEnabled(false);
    ui->tbMCwaarde->setEnabled(false);
    ui->tbTegoedbon->setEnabled(false);
    ui->lbAfrekenen->setEnabled(false);
    ui->tbNaarFactuur->setEnabled(false);

    ui->tbBedragUitgave->setText("-");
    NumKeyboard* nk = new NumKeyboard(ui->tbBedragUitgave);
    nk->exec();
}

void Kassa::HerrekenBetaling()
{
    ReedsBetaald = Contant + Bankcontact + Kredietkaart + Maaltijdcheques + Tegoedbon + Factuur;
    Rest = TeBetalen - ReedsBetaald;
}

void Kassa::on_btnContant_clicked()
{
    bool ok;
    Contant = 0;
    HerrekenBetaling();
    ui->tbContant->setText(QString("%1").arg(Rest, 0,'f',2));
    NumKeyboard nc(ui->tbContant,this);
    nc.exec();
    Contant = ui->tbContant->text().toDouble(&ok);
    if (!ok)
    {
        Contant = 0;
        QMessageBox msgBox;
        msgBox.setText("<strong>Foute ingave !</strong>");
        msgBox.setInformativeText("Je moet een geldig getal ingeven.\nEnkel cijfers, decimaal teken en het min-teken zijn toegelaten.");
        msgBox.setStandardButtons(QMessageBox::Cancel);
        msgBox.setDefaultButton(QMessageBox::Cancel);
        msgBox.setIcon(QMessageBox::Critical);
        msgBox.setWindowTitle("Opgepast !");
        QSpacerItem *hs = new QSpacerItem(400, 0, QSizePolicy::Minimum, QSizePolicy::Expanding);
        QGridLayout *gl = (QGridLayout*)msgBox.layout();
        gl->addItem(hs, gl->rowCount(), 0, 1, gl->columnCount());
        msgBox.exec();
    }
    ui->tbContant->setText(QString("%1").arg(Contant, 0,'f',2));
    HerrekenBetaling();
    UpdateDisplay();
}

void Kassa::on_btnBankcontact_clicked()
{
    bool ok;
    Bankcontact = 0;
    HerrekenBetaling();
    ui->tbBankcontact->setText(QString("%1").arg(Rest, 0,'f',2));
    NumKeyboard nc(ui->tbBankcontact,this);
    nc.exec();
    Bankcontact = ui->tbBankcontact->text().toDouble(&ok);
    if (!ok)
    {
        Bankcontact = 0;
        QMessageBox msgBox;
        msgBox.setText("<strong>Foute ingave !</strong>");
        msgBox.setInformativeText("Je moet een geldig getal ingeven.\nEnkel cijfers, decimaal teken en het min-teken zijn toegelaten.");
        msgBox.setStandardButtons(QMessageBox::Cancel);
        msgBox.setDefaultButton(QMessageBox::Cancel);
        msgBox.setIcon(QMessageBox::Critical);
        msgBox.setWindowTitle("Opgepast !");
        QSpacerItem *hs = new QSpacerItem(400, 0, QSizePolicy::Minimum, QSizePolicy::Expanding);
        QGridLayout *gl = (QGridLayout*)msgBox.layout();
        gl->addItem(hs, gl->rowCount(), 0, 1, gl->columnCount());
        msgBox.exec();
    }
    ui->tbBankcontact->setText(QString("%1").arg(Bankcontact, 0,'f',2));
    HerrekenBetaling();
    UpdateDisplay();
}

void Kassa::on_btnKredietkaart_clicked()
{
    bool ok;
    Kredietkaart = 0;
    HerrekenBetaling();
    ui->tbKredietkaart->setText(QString("%1").arg(Rest, 0,'f',2));
    NumKeyboard nc(ui->tbKredietkaart,this);
    nc.exec();
    Kredietkaart = ui->tbKredietkaart->text().toDouble(&ok);
    if (!ok)
    {
        Kredietkaart = 0;
        QMessageBox msgBox;
        msgBox.setText("<strong>Foute ingave !</strong>");
        msgBox.setInformativeText("Je moet een geldig getal ingeven.\nEnkel cijfers, decimaal teken en het min-teken zijn toegelaten.");
        msgBox.setStandardButtons(QMessageBox::Cancel);
        msgBox.setDefaultButton(QMessageBox::Cancel);
        msgBox.setIcon(QMessageBox::Critical);
        msgBox.setWindowTitle("Opgepast !");
        QSpacerItem *hs = new QSpacerItem(400, 0, QSizePolicy::Minimum, QSizePolicy::Expanding);
        QGridLayout *gl = (QGridLayout*)msgBox.layout();
        gl->addItem(hs, gl->rowCount(), 0, 1, gl->columnCount());
        msgBox.exec();
    }
    ui->tbKredietkaart->setText(QString("%1").arg(Kredietkaart, 0,'f',2));
    HerrekenBetaling();
    UpdateDisplay();
}

void Kassa::on_btntegoedbon_clicked()
{
    bool ok;
    Tegoedbon = 0;
    HerrekenBetaling();
    ui->tbTegoedbon->setText(QString(""));
    NumKeyboard nc(ui->tbTegoedbon,this);
    nc.exec();
    Tegoedbon = ui->tbTegoedbon->text().toDouble(&ok);
    if (!ok)
    {
        Tegoedbon = 0;
        QMessageBox msgBox;
        msgBox.setText("<strong>Foute ingave !</strong>");
        msgBox.setInformativeText("Je moet een geldig getal ingeven.\nEnkel cijfers, decimaal teken en het min-teken zijn toegelaten.");
        msgBox.setStandardButtons(QMessageBox::Cancel);
        msgBox.setDefaultButton(QMessageBox::Cancel);
        msgBox.setIcon(QMessageBox::Critical);
        msgBox.setWindowTitle("Opgepast !");
        QSpacerItem *hs = new QSpacerItem(400, 0, QSizePolicy::Minimum, QSizePolicy::Expanding);
        QGridLayout *gl = (QGridLayout*)msgBox.layout();
        gl->addItem(hs, gl->rowCount(), 0, 1, gl->columnCount());
        msgBox.exec();
    }
    ui->tbTegoedbon->setText(QString("%1").arg(Tegoedbon, 0,'f',2));
    HerrekenBetaling();
    UpdateDisplay();
}

void Kassa::on_btnMaaltijdcheque_clicked()
{
    bool ok;
    Maaltijdcheques = 0;
    MCeenheidsprijs = 0;
    MCaantal = 1;
    HerrekenBetaling();
    ui->tbMCwaarde->setText(QString(QString("%1").arg(Rest, 0,'f',2)));
    ui->lbMCaantal->setText(QString("x %1").arg(MCaantal));
    NumKeyboard nc(ui->tbMCwaarde,this);
    nc.exec();
    MCeenheidsprijs = ui->tbMCwaarde->text().toDouble(&ok);
    if (!ok)
    {
        MCeenheidsprijs = 0;
        QMessageBox msgBox;
        msgBox.setText("<strong>Foute ingave !</strong>");
        msgBox.setInformativeText("Je moet een geldig getal ingeven.\nEnkel cijfers, decimaal teken en het min-teken zijn toegelaten.");
        msgBox.setStandardButtons(QMessageBox::Cancel);
        msgBox.setDefaultButton(QMessageBox::Cancel);
        msgBox.setIcon(QMessageBox::Critical);
        msgBox.setWindowTitle("Opgepast !");
        QSpacerItem *hs = new QSpacerItem(400, 0, QSizePolicy::Minimum, QSizePolicy::Expanding);
        QGridLayout *gl = (QGridLayout*)msgBox.layout();
        gl->addItem(hs, gl->rowCount(), 0, 1, gl->columnCount());
        msgBox.exec();
    }
    MCaantal = static_cast<int>(Rest / MCeenheidsprijs);
    Maaltijdcheques = MCeenheidsprijs * MCaantal;
    ui->tbMaaltijdcheque->setText(QString("%1").arg(Maaltijdcheques, 0,'f',2));
    ui->lbMCaantal->setText(QString("x %1").arg(MCaantal));
    HerrekenBetaling();
    UpdateDisplay();
}

void Kassa::on_btnMCPlus_clicked()
{
    MCaantal++;
    Maaltijdcheques = MCeenheidsprijs * MCaantal;
    ui->tbMaaltijdcheque->setText(QString("%1").arg(Maaltijdcheques, 0,'f',2));
    ui->lbMCaantal->setText(QString("x %1").arg(MCaantal));
    HerrekenBetaling();
    UpdateDisplay();
}

void Kassa::on_btnMCmin_clicked()
{
    MCaantal--;
    Maaltijdcheques = MCeenheidsprijs * MCaantal;
    ui->tbMaaltijdcheque->setText(QString("%1").arg(Maaltijdcheques, 0,'f',2));
    ui->lbMCaantal->setText(QString("x %1").arg(MCaantal));
    HerrekenBetaling();
    UpdateDisplay();
}



void Kassa::on_btnReken_clicked()
{
    double ontvangen, terug;
    ui->tbOntvangen->setText("0");
    NumKeyboard nc(ui->tbOntvangen,this);
    nc.exec();
    ontvangen = ui->tbOntvangen->text().toDouble();
    terug = ontvangen - Contant;
    ui->tbOntvangen->setText(QString("%1").arg(ontvangen, 0,'f',2));
    ui->tbTerug->setText(QString("%1").arg(terug, 0,'f',2));
}

void Kassa::on_btnKladPrint_clicked()
{
    PrintTicket();
}

void Kassa::on_btnSelect_0_clicked()
{
    SelectedTicketID = ui->btnSelect_0->statusTip().toInt();
    if (SelectedTicketID != 0)
    {
        ticket = new Ticket(SelectedTicketID);
        Rest = TeBetalen = ticket->getTotaal_Incl_BTW();
        ReedsBetaald = 0;
        FillTicket();
    }
    SelectedTicketID = 0;
}

void Kassa::on_btnSelect_1_clicked()
{
    SelectedTicketID = ui->btnSelect_1->statusTip().toInt();
    if (SelectedTicketID != 0)
    {
        ticket = new Ticket(SelectedTicketID);
        Rest = TeBetalen = ticket->getTotaal_Incl_BTW();
        ReedsBetaald = 0;
        FillTicket();
    }
    SelectedTicketID = 0;
}

void Kassa::on_btnSelect_2_clicked()
{
    SelectedTicketID = ui->btnSelect_2->statusTip().toInt();
    if (SelectedTicketID != 0)
    {
        ticket = new Ticket(SelectedTicketID);
        Rest = TeBetalen = ticket->getTotaal_Incl_BTW();
        ReedsBetaald = 0;
        FillTicket();
    }
    SelectedTicketID = 0;
}

void Kassa::on_btnSelect_3_clicked()
{
    SelectedTicketID = ui->btnSelect_3->statusTip().toInt();
    if (SelectedTicketID != 0)
    {
        ticket = new Ticket(SelectedTicketID);
        Rest = TeBetalen = ticket->getTotaal_Incl_BTW();
        ReedsBetaald = 0;
        FillTicket();
    }
    SelectedTicketID = 0;
}

void Kassa::on_btnSelect_4_clicked()
{
    SelectedTicketID = ui->btnSelect_4->statusTip().toInt();
    if (SelectedTicketID != 0)
    {
        ticket = new Ticket(SelectedTicketID);
        Rest = TeBetalen = ticket->getTotaal_Incl_BTW();
        ReedsBetaald = 0;
        FillTicket();
    }
    SelectedTicketID = 0;
}

void Kassa::on_btnSelect_5_clicked()
{
    SelectedTicketID = ui->btnSelect_5->statusTip().toInt();
    if (SelectedTicketID != 0)
    {
        ticket = new Ticket(SelectedTicketID);
        Rest = TeBetalen = ticket->getTotaal_Incl_BTW();
        ReedsBetaald = 0;
        FillTicket();
    }
    SelectedTicketID = 0;
}

void Kassa::on_btnSelect_6_clicked()
{
    SelectedTicketID = ui->btnSelect_6->statusTip().toInt();
    if (SelectedTicketID != 0)
    {
        ticket = new Ticket(SelectedTicketID);
        Rest = TeBetalen = ticket->getTotaal_Incl_BTW();
        ReedsBetaald = 0;
        FillTicket();
    }
    SelectedTicketID = 0;
}

void Kassa::on_btnSelect_7_clicked()
{
    SelectedTicketID = ui->btnSelect_7->statusTip().toInt();
    if (SelectedTicketID != 0)
    {
        ticket = new Ticket(SelectedTicketID);
        Rest = TeBetalen = ticket->getTotaal_Incl_BTW();
        ReedsBetaald = 0;
        FillTicket();
    }
    SelectedTicketID = 0;
}

void Kassa::on_btnAnuleren_clicked()
{

    ClearFields();
    ui->lbTicketNr->setText( "Ticket nummer: ");
    ui->lstwTicket->clear();
    ticket = new Ticket();

    ui->btnUitgaven->setEnabled(true);
    ui->lbAfrekenen->setEnabled(true);


    ui->cbxReden->setEnabled(false);
    ui->tbBedragUitgave->setEnabled(false);

    ui->btnBankcontact->setEnabled(false);
    ui->btnContant->setEnabled(false);
    ui->btnKredietkaart->setEnabled(false);
    ui->btnMaaltijdcheque->setEnabled(false);
    ui->btnMCmin->setEnabled(false);
    ui->btnMCPlus->setEnabled(false);
    ui->btntegoedbon->setEnabled(false);
    ui->btnNaarFactuur->setEnabled(false);
    ui->tbBankcontact->setEnabled(false);
    ui->tbContant->setEnabled(false);
    ui->tbKredietkaart->setEnabled(false);
    ui->tbMaaltijdcheque->setEnabled(false);
    ui->tbMCwaarde->setEnabled(false);
    ui->tbTegoedbon->setEnabled(false);
    ui->tbNaarFactuur->setEnabled(false);
    ui->tbOntvangen->setText("0");
    ui->tbTerug->setText("0");

    ui->btnSelect_0->setEnabled(true);
    ui->btnSelect_1->setEnabled(true);
    ui->btnSelect_2->setEnabled(true);
    ui->btnSelect_3->setEnabled(true);
    ui->btnSelect_4->setEnabled(true);
    ui->btnSelect_5->setEnabled(true);
    ui->btnSelect_6->setEnabled(true);
    ui->btnSelect_7->setEnabled(true);


    FillTicketsList();
}

void Kassa::on_btnNaarFactuur_clicked()
{
    //bool ok;
    Factuur = 0;
    HerrekenBetaling();
    ui->tbNaarFactuur->setText(QString("%1").arg(Rest, 0,'f',2));
    Factuur = Rest;
    // NumKeyboard nc(ui->tbNaarFactuur,this);
    // nc.exec();
    //  = ui->tbKredietkaart->text().toDouble(&ok);
//    if (!ok)
//    {
//        Kredietkaart = 0;
//        QMessageBox msgBox;
//        msgBox.setText("<strong>Foute ingave !</strong>");
//        msgBox.setInformativeText("Je moet een geldig getal ingeven.\nEnkel cijfers, decimaal teken en het min-teken zijn toegelaten.");
//        msgBox.setStandardButtons(QMessageBox::Cancel);
//        msgBox.setDefaultButton(QMessageBox::Cancel);
//        msgBox.setIcon(QMessageBox::Critical);
//        msgBox.setWindowTitle("Opgepast !");
//        QSpacerItem *hs = new QSpacerItem(400, 0, QSizePolicy::Minimum, QSizePolicy::Expanding);
//        QGridLayout *gl = (QGridLayout*)msgBox.layout();
//        gl->addItem(hs, gl->rowCount(), 0, 1, gl->columnCount());
//        msgBox.exec();
//    }
//    ui->tbNaarFactuur->setText(QString("%1").arg(Factuur, 0,'f',2));
    HerrekenBetaling();
    UpdateDisplay();
}
