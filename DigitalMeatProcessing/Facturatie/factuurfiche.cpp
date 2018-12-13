#include "factuurfiche.h"
#include "ui_factuurfiche.h"
#include "factuurregel.h"
#include "CommonObjects/postcodes.h"
#include "CommonObjects/landen.h"
#include "Relaties/findrelaties.h"
#include "CommonObjects/printpagebackground.h"
#include "factuurvanticket.h"


#include <QApplication>
#include <QSettings>
#include <QLocale>
#include <QDialog>
#include <QDateTime>
#include <QtPrintSupport/QPrintDialog>
#include <QtPrintSupport/QPrintPreviewDialog>
#include <QtPrintSupport/QPrinter>
#include <QtSerialPort/QSerialPort>
#include <QtSerialPort/QSerialPortInfo>
#include <QPainter>
#include <QFontDialog>
#include <QResource>
#include <QMessageBox>
#include <QSpacerItem>
#include <QGridLayout>


FactuurFiche::FactuurFiche(int _id, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::FactuurFiche)
{
    ui->setupUi(this);

    rel = new Relaties();
    ClearRelZoekFields();
    ui->tbTotBTW->setText("");
    ui->tbTotEx->setText("");
    ui->tbTotIn->setText("");


    if (_id == 0)
    {
        // Nieuwe factuur
        this->setWindowTitle("Factuurfiche: Nieuwe factuur.");
        //ui->lbDatum->setText(QString("Datum : %1").arg(QDate::currentDate().toString("dd/MM/yyyy")));
        ui->dtpDatum->setDate(QDate::currentDate());

        ui->btnRegelToevoegen->setEnabled(false);
        ui->btnOpslaan->setEnabled(false);
        ui->btnPrinten->setEnabled(false);

        fh = new FactuurHeader();
    }
    else
    {
        // Bestaande faktuur openen
        fh = new FactuurHeader(_id);
        rel = new Relaties(fh->getKlant_ID());
        if (fh->getPrinted())
        {
            // Alle aanpassingen blockeren
            ui->btnRegelToevoegen->setEnabled(false);
            ui->btnOpslaan->setEnabled(false);
            ui->btnPrinten->setEnabled(true);
            ui->btnWis_Lev->setEnabled(false);
            ui->btnZoek_Lev->setEnabled(false);

        }
        ui->tbNummer->setText(QString::number(fh->getKlant_ID()));
        ui->tbNaam->setText(fh->getKlantNaam());
        ui->tbStraat->setText(fh->getKlantAdres());
        ui->tbPostcode->setText(fh->getKlantPostcode());
        ui->tbGemeente->setText(fh->getKlantGemeente());
        ui->tbBTW_Nummer->setText(rel->getBTWNummer());
        ui->tbEMail->setText(rel->getEMail_1());
        //ui->lbDatum->setText(QString("Datum : %1").arg(fh->getTijdstip().toString("dd/MM/yyyy")));
        ui->dtpDatum->setDate(fh->getTijdstip());
        ui->lbFactuur->setText(QString("Factuurnr.: %1%2").arg(fh->getTijdstip().toString("yyyy")).arg(fh->getVolgnummer(), 6, 'g', -1,'0'));

        FillRegels();
    }
}

FactuurFiche::~FactuurFiche()
{
    delete ui;
    delete rel;
    delete fh;
}

void FactuurFiche::on_btnZoek_Lev_clicked()
{
    bool ok;
    int rel_id;

    rel_id = ui->tbNummer->text().toInt(&ok);
    if (ok)
    {
        rel = new Relaties(rel_id);
        if (rel->getRelatie_ID() == 0)
        {
            QMessageBox *msgBox = new QMessageBox(this);
            msgBox->setText("Relatie - Fout");
            msgBox->setWindowModality(Qt::WindowModal);
            msgBox->setInformativeText("Relatie met dit nummer bestaat niet");
            msgBox->setStandardButtons(QMessageBox::Ok);
            QSpacerItem *hs = new QSpacerItem(400, 0, QSizePolicy::Minimum, QSizePolicy::Expanding);
            QGridLayout *gl = (QGridLayout*)msgBox->layout();
            gl->addItem(hs, gl->rowCount(), 0, 1, gl->columnCount());

            msgBox->exec();
        }
        else
        {
            ui->tbNaam->setText(rel->getNaam() + " " + rel->getVoornaam());
            ui->tbStraat->setText(rel->getAdres());
            ui->tbGemeente->setText(Postcodes::getGemeente(rel->getGemeente_ID()));
            ui->tbPostcode->setText(Postcodes::getPocode(rel->getGemeente_ID()));
            ui->tbEMail->setText(rel->getEMail_1());
            ui->tbBTW_Nummer->setText(rel->getBTWNummer());

            CurrentRel = rel->getRelatie_ID();
        }
    }
    else
    {
        FindRelaties *fr = new FindRelaties(
                    ui->tbNaam->text(),
                    ui->tbStraat->text(),
                    ui->tbGemeente->text(),
                    ui->tbEMail->text());
        fr->exec();
        rel_id = fr->getID();
        rel = new Relaties(rel_id);
        if (rel->getRelatie_ID() != 0)
        {
            ui->tbNummer->setText( QString("%1").arg(rel->getRelatie_ID()));
            ui->tbNaam->setText(rel->getNaam() + " " + rel->getVoornaam());
            ui->tbStraat->setText(rel->getAdres());
            ui->tbGemeente->setText(Postcodes::getGemeente(rel->getGemeente_ID()));
            ui->tbPostcode->setText(Postcodes::getPocode(rel->getGemeente_ID()));
            ui->tbEMail->setText(rel->getEMail_1());
            ui->tbBTW_Nummer->setText(rel->getBTWNummer());

            CurrentRel =  rel->getRelatie_ID();
        }
    }
    if (rel->getRelatie_ID() != 0)
    {
        ui->btnRegelToevoegen->setEnabled(true);
        ui->btnOpslaan->setEnabled(true);
        ui->btnPrinten->setEnabled(true);
    }
}

void FactuurFiche::on_btnWis_Lev_clicked()
{
    ClearRelZoekFields();
}

void FactuurFiche::ClearRelZoekFields()
{
    ui->tbNummer->setText("");
    ui->tbNaam->setText("");
    ui->tbStraat->setText("");
    ui->tbGemeente->setText("");
    ui->tbEMail->setText("");
    ui->tbPostcode->setText("");
    ui->tbBTW_Nummer->setText("");
}

void FactuurFiche::on_btnRegelToevoegen_clicked()
{
    if (fh->getFactuur_ID() == 0)
    {
        // Eerste regel van Nieuwe factuur
        fh->setKlant_ID(rel->getRelatie_ID());
        fh->setKlantNaam(rel->getNaam() + " " + rel->getVoornaam());
        fh->setKlantAdres(rel->getAdres());
        fh->setKlantGemeente(Postcodes::getGemeente(rel->getGemeente_ID()));
        fh->setKlantPostcode(Postcodes::getPocode(rel->getGemeente_ID()));
        fh->setKlantLand(Landen::getLandByCode(rel->getLandCode()));
        fh->setKlantLand(Landen::getLandByCode(rel->getLandCode()));
        fh->setTijdstip(ui->dtpDatum->date());
        fh->save();
        //ui->lbDatum->setText(QString("Datum : %1").arg(fh->getTijdstip().toString("dd/MM/yyyy")));
        ui->dtpDatum->setDate(fh->getTijdstip());
        ui->lbFactuur->setText(QString("Factuurnr.: %1%2").arg(fh->getTijdstip().toString("yyyy")).arg(fh->getVolgnummer(), 6, 'g', -1,'0'));
    }
    // Open regelinvoer
    FactuurRegel fr(fh->getFactuur_ID(), 0, this);
    fr.exec();
    // dataview bijwerken
    FillRegels();
}

void FactuurFiche::on_btnOpslaan_clicked()
{
    fh->setKlant_ID(rel->getRelatie_ID());
    fh->setKlantNaam(rel->getNaam() + " " + rel->getVoornaam());
    fh->setKlantAdres(rel->getAdres());
    fh->setKlantGemeente(Postcodes::getGemeente(rel->getGemeente_ID()));
    fh->setKlantPostcode(Postcodes::getPocode(rel->getGemeente_ID()));
    fh->setKlantLand(Landen::getLandByCode(rel->getLandCode()));
    fh->setTijdstip(ui->dtpDatum->date());
    fh->save();
    //ui->lbDatum->setText(QString("Datum : %1").arg(fh->getTijdstip().toString("dd/MM/yyyy")));
    ui->dtpDatum->setDate(fh->getTijdstip());
    ui->lbFactuur->setText(QString("Factuurnr.: %1%2").arg(fh->getTijdstip().toString("yyyy")).arg(fh->getVolgnummer(), 6, 'g', -1,'0'));
}

void FactuurFiche::FillRegels()
{
    QSqlQueryModel *reg_model = new QSqlQueryModel();
    FactuurLine::getLinesByFactuurID( fh->getFactuur_ID(), reg_model);

    reg_model->setHeaderData(0, Qt::Horizontal, tr("Code"));
    reg_model->setHeaderData(1, Qt::Horizontal, tr("Omschr."));
    reg_model->setHeaderData(2, Qt::Horizontal, tr("Eenh.pr."));
    reg_model->setHeaderData(3, Qt::Horizontal, tr("Hoeveelh."));
    reg_model->setHeaderData(4, Qt::Horizontal, tr("Eenh."));
    reg_model->setHeaderData(5, Qt::Horizontal, tr("Bruto"));
    reg_model->setHeaderData(6, Qt::Horizontal, tr("Korting"));
    reg_model->setHeaderData(7, Qt::Horizontal, tr("Excl."));
    reg_model->setHeaderData(8, Qt::Horizontal, tr("%BTW"));
    reg_model->setHeaderData(9, Qt::Horizontal, tr("BTW"));
    reg_model->setHeaderData(10, Qt::Horizontal, tr("Incl."));


    //result = tableModel->data(1,2).toString();
    ui->tvRegels->setModel(reg_model);

    ui->tvRegels->setColumnWidth(0,61);
    ui->tvRegels->setColumnWidth(1,206);
    ui->tvRegels->setColumnWidth(2,66);
    ui->tvRegels->setColumnWidth(3,56);
    ui->tvRegels->setColumnWidth(4,46);
    ui->tvRegels->setColumnWidth(5,66);
    ui->tvRegels->setColumnWidth(6,66);
    ui->tvRegels->setColumnWidth(7,66);
    ui->tvRegels->setColumnWidth(8,51);
    ui->tvRegels->setColumnWidth(9,66);
    ui->tvRegels->setColumnWidth(10,66);

    ui->tvRegels->verticalHeader()->setDefaultSectionSize(20);
    ui->tvRegels->setAlternatingRowColors(true);

    QSqlQueryModel *btw_model = new QSqlQueryModel();
    FactuurLine::getBTWBlockByFactuurID( fh->getFactuur_ID(), btw_model);

    btw_model->setHeaderData(0, Qt::Horizontal, tr("Tarief"));
    btw_model->setHeaderData(1, Qt::Horizontal, tr("M.V.H."));
    btw_model->setHeaderData(2, Qt::Horizontal, tr("BTW."));
    btw_model->setHeaderData(3, Qt::Horizontal, tr("Totaal:"));


    //result = tableModel->data(1,2).toString();
    ui->tvBTWBlock->setModel(btw_model);

    ui->tvBTWBlock->setColumnWidth(0,80);
    ui->tvBTWBlock->setColumnWidth(1,80);
    ui->tvBTWBlock->setColumnWidth(2,80);
    ui->tvBTWBlock->setColumnWidth(3,80);

    ui->tvBTWBlock->verticalHeader()->setDefaultSectionSize(20);
    ui->tvBTWBlock->setAlternatingRowColors(true);

    QSqlQueryModel *tot_model = new QSqlQueryModel();
    FactuurLine::getTotalsByFactuurID( fh->getFactuur_ID(), tot_model);

    ui->tbTotBTW->setText(QString("%1").arg(tot_model->record(0).value("tot_btw").toDouble(), 0, 'f', 2));
    ui->tbTotEx->setText(QString("%1").arg(tot_model->record(0).value("tot_mvh").toDouble(), 0, 'f', 2));
    ui->tbTotIn->setText(QString("%1").arg(tot_model->record(0).value("tot_tot").toDouble(), 0, 'f', 2));

}

void FactuurFiche::on_btnPrinten_clicked()
{
    if (fh->getFactuur_ID() == 0)
        on_btnOpslaan_clicked();

    QPrinter pr;

    QPrintDialog prDialog(&pr, this);

    prDialog.setWindowTitle("Print Factuur");
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

    PrintPageBackground::PrintFactuur(&pr, &painter);

    QFont f_artikel("Century Schoolbook L",35,QFont::Bold);
    QFont f_adres("Century Schoolbook L",30,QFont::Normal);
    QFont f_lijn("Droid Sans Mono",20);
    QFont f_btw("Droid Sans Mono",25);

    QPen pen(Qt::black);

    pen.setWidth(3);
    painter.setPen(pen);

    // Document tittel
    QRect LR = QRect(150, 700, 1800, 100 );
    painter.setFont(f_artikel);
    painter.drawText(LR, Qt::AlignLeft | Qt::AlignTop,
                     QString("Factuur nr: %1%2 van %3")
                     .arg(fh->getTijdstip().toString("yyyy"))
                     .arg(fh->getVolgnummer(), 6, 'g', -1,'0')
                     .arg(fh->getTijdstip().toString("dd/MM/yyyy")));

    // Tabel tekenen
    LR = QRect(150, 800, 1800, 60);
    painter.fillRect(LR, QBrush(QColor("#e6e6e6"), Qt::SolidPattern));

    painter.drawLine(150,800,1950,800);
    painter.drawLine(150,860,1950,860);
    painter.drawLine(150,2300,1950,2300);
    painter.drawLine(150,800,150,2300);
    painter.drawLine(1950,800,1950,2300);

    pen.setWidth(2);
    painter.drawLine(285,800,285,2300);
    painter.drawLine(739,800,739,2300);
    painter.drawLine(885,800,885,2300);
    painter.drawLine(1008,800,1008,2300);
    painter.drawLine(1109,800,1109,2300);
    painter.drawLine(1255,800,1255,2300);
    painter.drawLine(1401,800,1401,2300);
    painter.drawLine(1546,800,1546,2300);
    painter.drawLine(1659,800,1659,2300);
    painter.drawLine(1804,800,1804,2300);

    // vouwmarkeringen
    painter.drawLine(0,920,100,920);
    painter.drawLine(0,2000,100,2000);

    // Titelblokje tabel
    painter.setFont(f_lijn);

    LR = QRect(150, 800, 135, 60);
    painter.drawText(LR, Qt::AlignHCenter | Qt::AlignVCenter,"Code:");

    LR = QRect(285, 800, 454, 60);
    painter.drawText(LR, Qt::AlignHCenter | Qt::AlignVCenter,"Omschrijving:");

    LR = QRect(739, 800, 146, 60);
    painter.drawText(LR, Qt::AlignHCenter | Qt::AlignVCenter,"Eenh.Pr.");

    LR = QRect(885, 800, 123, 60);
    painter.drawText(LR, Qt::AlignHCenter | Qt::AlignVCenter,"Aantal:");

    LR = QRect(1008, 800, 101, 60);
    painter.drawText(LR, Qt::AlignHCenter | Qt::AlignVCenter,"Eenh.");

    LR = QRect(1109, 800, 146, 60);
    painter.drawText(LR, Qt::AlignHCenter | Qt::AlignVCenter,"Bruto:");

    LR = QRect(1255, 800, 146, 60);
    painter.drawText(LR, Qt::AlignHCenter | Qt::AlignVCenter,"");

    LR = QRect(1401, 800, 146, 60);
    painter.drawText(LR, Qt::AlignHCenter | Qt::AlignVCenter,"Excl.");

    LR = QRect(1546, 800, 112, 60);
    painter.drawText(LR, Qt::AlignHCenter | Qt::AlignVCenter,"% BTW");

    LR = QRect(1659, 800, 146, 60);
    painter.drawText(LR, Qt::AlignHCenter | Qt::AlignVCenter,"BTW bedr.");

    LR = QRect(1804, 800, 146, 60);
    painter.drawText(LR, Qt::AlignHCenter | Qt::AlignVCenter,"Incl.");


    // Adres blok
    painter.setFont(f_adres);

    painter.drawText(1100,350,"Aan:");
    painter.drawText(1250,350, fh->getKlantNaam());
    painter.drawText(1250,410,fh->getKlantAdres());
    painter.drawText(1250,470,fh->getKlantPostcode());
    painter.drawText(1400,470,fh->getKlantGemeente());
    painter.drawText(1250,530,fh->getKlantLand());
    painter.drawText(1100,650, QString("BTW nr.: %1").arg(rel->getBTWNummer()));

    // Factuurregels.
    QSqlQueryModel *reg_model = new QSqlQueryModel();
    FactuurLine::getLinesByFactuurID( fh->getFactuur_ID(), reg_model);

    painter.setFont(f_lijn);

    int regpos = 865;
    int regspace = 55;
    for(int teller = 0 ; teller < reg_model->rowCount(); teller++)
    {
        LR = QRect(150, regpos, 135, regspace);
        painter.drawText(LR, Qt::AlignHCenter | Qt::AlignVCenter,
             reg_model->record(teller).value("artikel_code").toString());

        LR = QRect(295, regpos, 454, regspace);
        painter.drawText(LR, Qt::AlignLeft | Qt::AlignVCenter,
             reg_model->record(teller).value("omschrijving").toString());

        LR = QRect(739, regpos, 136, regspace);
        painter.drawText(LR, Qt::AlignRight | Qt::AlignVCenter,
            QString("%1").arg(reg_model->record(teller).value("eenheidsprijs").toDouble(), 0, 'f', 2));

        LR = QRect(885, regpos, 123, regspace);
        painter.drawText(LR, Qt::AlignHCenter | Qt::AlignVCenter,
            QString("%1").arg(reg_model->record(teller).value("aantal").toDouble(), 0, 'f', 2));

        LR = QRect(1008, regpos, 101, regspace);
        painter.drawText(LR, Qt::AlignHCenter | Qt::AlignVCenter,
            QString("%1").arg(reg_model->record(teller).value("eenheid").toString()));

        LR = QRect(1109, regpos, 136, regspace);
        painter.drawText(LR, Qt::AlignRight | Qt::AlignVCenter,
            QString("%1").arg(reg_model->record(teller).value("bruto").toDouble(), 0, 'f', 2));

        if (reg_model->record(teller).value("kort").toDouble() >= 0.01)
        {
            LR = QRect(1255, regpos, 136, regspace);
            painter.drawText(LR, Qt::AlignRight | Qt::AlignVCenter,
                 QString("-%1").arg(reg_model->record(teller).value("kort").toDouble(), 0, 'f', 2));
        }

        LR = QRect(1401, regpos, 136, regspace);
        painter.drawText(LR, Qt::AlignRight | Qt::AlignVCenter,
            QString("%1").arg(reg_model->record(teller).value("excl").toDouble(), 0, 'f', 2));

        LR = QRect(1546, regpos, 112, regspace);
        painter.drawText(LR, Qt::AlignHCenter | Qt::AlignVCenter,
            QString("%1").arg(reg_model->record(teller).value("perc").toDouble(), 0, 'f', 2));

        LR = QRect(1659, regpos, 136, regspace);
        painter.drawText(LR, Qt::AlignRight | Qt::AlignVCenter,
            QString("%1").arg(reg_model->record(teller).value("BTW").toDouble(), 0, 'f', 2));

        LR = QRect(1804, regpos, 136, regspace);
        painter.drawText(LR, Qt::AlignRight | Qt::AlignVCenter,
             QString("%1").arg(reg_model->record(teller).value("incl").toDouble(), 0, 'f', 2));

        regpos = regpos + regspace;
    }

    // Algemene voorwaarden
    LR = QRect(150, 2310, 1800, 40);
    painter.drawText(LR, Qt::AlignLeft | Qt::AlignVCenter,"De algemene voorwaarden, opgenomen op de achterzijde, maken integraal deel uit van de overeenkomst, met ");
    LR = QRect(150, 2350, 1800, 40);
    painter.drawText(LR, Qt::AlignLeft | Qt::AlignVCenter,"uitsluiting van de eigen voorwaarden van de klant. Er kan alleen schriftelijk van worden afgeweken. De klant");
    LR = QRect(150, 2390, 1800, 40);
    painter.drawText(LR, Qt::AlignLeft | Qt::AlignVCenter,"erkent uitdrukkelijk deze voorwaarden gelezen te hebben en ze integraal zonder voorbehoud goed te keuren.");

    // BTW Blokje
    LR = QRect(150, 2450, 800, 60);
    painter.fillRect(LR, QBrush(QColor("#e6e6e6"), Qt::SolidPattern));
    painter.drawRect(LR);
    painter.drawLine(150, 2750, 950, 2750);

    painter.drawLine(150, 2450, 150, 2750);
    painter.drawLine(350, 2450, 350, 2750);
    painter.drawLine(550, 2450, 550, 2750);
    painter.drawLine(750, 2450, 750, 2750);
    painter.drawLine(950, 2450, 950, 2750);

    LR = QRect(150,2450,200,60);
    painter.drawText(LR, Qt::AlignHCenter | Qt::AlignVCenter, "Tarief:");
    LR = QRect(350,2450,200,60);
    painter.drawText(LR, Qt::AlignHCenter | Qt::AlignVCenter, "M.V.H.:");
    LR = QRect(550,2450,200,60);
    painter.drawText(LR, Qt::AlignHCenter | Qt::AlignVCenter, "BTW:");
    LR = QRect(750,2450,200,60);
    painter.drawText(LR, Qt::AlignHCenter | Qt::AlignVCenter, "Inclusief:");

    QSqlQueryModel *btw_model = new QSqlQueryModel();
    FactuurLine::getBTWBlockByFactuurID( fh->getFactuur_ID(), btw_model);

    regpos = 2510;
    regspace = 50;

    for (int teller = 0; teller < btw_model->rowCount(); teller++)
    {
        if (btw_model->record(teller).value("mvh").toDouble() >= 0.01)
        {
            LR = QRect(150,regpos,190,regspace);
            painter.drawText(LR, Qt::AlignRight | Qt::AlignVCenter,
                QString("%1 %").arg(btw_model->record(teller).value("perc").toDouble(), 0, 'f', 2));
            LR = QRect(350,regpos,190,regspace);
            painter.drawText(LR, Qt::AlignRight | Qt::AlignVCenter,
                QString("%1").arg(btw_model->record(teller).value("mvh").toDouble(), 0, 'f', 2));
            LR = QRect(550,regpos,190,regspace);
            painter.drawText(LR, Qt::AlignRight | Qt::AlignVCenter,
                QString("%1").arg(btw_model->record(teller).value("btw").toDouble(), 0, 'f', 2));
            LR = QRect(750,regpos,190,regspace);
            painter.drawText(LR, Qt::AlignRight | Qt::AlignVCenter,
                QString("%1").arg(btw_model->record(teller).value("tot").toDouble(), 0, 'f', 2));
            regpos = regpos + regspace;
        }
    }

    // Totaal factuur
    painter.setFont(f_adres);

    QSqlQueryModel *tot_model = new QSqlQueryModel();
    FactuurLine::getTotalsByFactuurID( fh->getFactuur_ID(), tot_model);

    LR = QRect(1220, 2450, 500, 100);
    painter.drawText(LR, Qt::AlignLeft | Qt::AlignVCenter, "Totaal excl. BTW :");
    LR = QRect(1630, 2450, 300, 100);
    painter.drawText(LR, Qt::AlignRight | Qt::AlignVCenter,
        QString("%1 €").arg(tot_model->record(0).value("tot_mvh").toDouble(), 0, 'f', 2));

    LR = QRect(1220, 2550, 500, 100);
    painter.drawText(LR, Qt::AlignLeft | Qt::AlignVCenter, "Totaal bedrag BTW :");
    LR = QRect(1630, 2550, 300, 100);
    painter.drawText(LR, Qt::AlignRight | Qt::AlignVCenter,
        QString("%1 €").arg(tot_model->record(0).value("tot_btw").toDouble(), 0, 'f', 2));

    LR = QRect(1200, 2650, 750, 100);
    painter.fillRect(LR, QBrush(QColor("#e6e6e6"), Qt::SolidPattern));
    painter.drawRect(LR);
    LR = QRect(1220, 2650, 500, 100);
    painter.drawText(LR, Qt::AlignLeft | Qt::AlignVCenter, "Te Betalen incl. BTW :");
    LR = QRect(1630, 2650, 300, 100);
    painter.drawText(LR, Qt::AlignRight | Qt::AlignVCenter,
        QString("%1 €").arg(tot_model->record(0).value("tot_tot").toDouble(), 0, 'f', 2));



    painter.end();

}

void FactuurFiche::on_btnEditLine_clicked()
{
   int Line_ID;
   //int row = ui->tvRegels->currentIndex().row();
   //QSqlRecord rec = ui->tvRegels->model()->data() //Facturen_model->record(row);
   Line_ID = ui->tvRegels->model()->data( ui->tvRegels->model()->index(ui->tvRegels->currentIndex().row(), 11 )).toInt();
   //Line_ID = rec.value(0).toInt();
   FactuurRegel fr(fh->getFactuur_ID(), Line_ID, this);
   fr.exec();
   // dataview bijwerken
   FillRegels();
}

void FactuurFiche::on_tvRegels_doubleClicked(const QModelIndex &index)
{
    int Line_ID;
    Line_ID = ui->tvRegels->model()->data( ui->tvRegels->model()->index(ui->tvRegels->currentIndex().row(), 11 )).toInt();
    FactuurRegel fr(fh->getFactuur_ID(), Line_ID, this);
    fr.exec();
    FillRegels();
}

void FactuurFiche::on_btnAddTicket_clicked()
{
    if ((rel->getRelatie_ID() <= 1))
    {
        QMessageBox *msgBox = new QMessageBox(this);
        msgBox->setText("Relatie - Fout");
        msgBox->setWindowModality(Qt::WindowModal);
        msgBox->setInformativeText("U Moet een klant kiezen");
        msgBox->setStandardButtons(QMessageBox::Ok);
        QSpacerItem *hs = new QSpacerItem(400, 0, QSizePolicy::Minimum, QSizePolicy::Expanding);
        QGridLayout *gl = (QGridLayout*)msgBox->layout();
        gl->addItem(hs, gl->rowCount(), 0, 1, gl->columnCount());
        msgBox->exec();
    }
    else
    {
        if (fh->getFactuur_ID() == 0)
            on_btnOpslaan_clicked();
        FactuurVanTicket *fvt = new FactuurVanTicket(fh->getFactuur_ID(), fh->getKlant_ID());
        fvt->exec();
        FillRegels();
    }
}
