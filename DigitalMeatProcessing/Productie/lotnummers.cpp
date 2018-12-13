#include "lotnummers.h"
#include "ui_lotnummers.h"
#include "samengesteldelotnummers.h"
#include "zoeklotopartikel.h"
#include "Relaties/findrelaties.h"
#include "CommonObjects/postcodes.h"
#include "ArtikelBeheer/artikelen.h"
#include "ArtikelBeheer/producten.h"
#include "ArtikelBeheer/soorten.h"
#include "ArtikelBeheer/details.h"
#include "ArtikelBeheer/specificaties.h"
#include "CommonObjects/stocklocaties.h"


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


Lotnummers::Lotnummers(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Lotnummers)
{
    initialised = false;
    ui->setupUi(this);
    //this->showFullScreen();

    ui->tbOpmerking->setText("");
    ui->dtpEigTgv->setDate(QDate::currentDate().addYears(100));
    ui->dtpInStock->setDate(QDate::currentDate());
    ui->dtpLevProdDatum->setDate(QDate::currentDate());
    ui->dtpLevTgv->setDate(QDate::currentDate().addYears(100));
    ui->dtpUiStock->setDate(QDate::currentDate().addYears(100));
    ui->cbActief->setChecked(true);

    ClearArtikelFields();
    LockArtikelFields(true);

    ClearLevFields();
    LockLevFields(true);

    LockAllFields(true);

    ui->actionAfsluiten->setEnabled(true);
    ui->actionNieuw->setEnabled(true);
    ui->actionBewerken->setEnabled(false);
    ui->actionLotnummer_opslaan->setEnabled(false);
    ui->actionPrint_Label->setEnabled(false);

    CurrentLotnummer = "";
    CurrentArt = 0;
    CurrentLev = 0;
    CurPrd_ID = 0;

    FillStockLocatieKeuze();
    FillProductkeuze();

    lot = new LotnummerData();
    ui->tbLotnummer->setText("");
    ui->tbLotnummer->setFocus();
    ui->tbLotnummer->setStyleSheet("color: rgb(255, 0, 0);");
    lot = new LotnummerData();
    initialised = true;
}

void Lotnummers::ClearLevZoekFields()
{
    ui->tbNummer->setText("");
    ui->tbNaam->setText("");
    ui->tbStraat->setText("");
    ui->tbGemeente->setText("");
    ui->tbEMail->setText("");
}

void Lotnummers::ClearLevFields()
{
    ClearLevZoekFields();

    ui->tbLevSlachthuis->setText("");
    ui->tbLevLotnr->setText("");
    ui->tbLevSanitel->setText("");
    ui->tbLevDocument->setText("");
    ui->tbLevRegel->setText("");
}

void Lotnummers::LockLevZoekFields(bool _lock)
{
    ui->tbNummer->setEnabled(!_lock);
    ui->tbNaam->setEnabled(!_lock);
    ui->tbStraat->setEnabled(!_lock);
    ui->tbGemeente->setEnabled(!_lock);
    ui->tbEMail->setEnabled(!_lock);
}

void Lotnummers::LockLevFields(bool _lock)
{
    LockLevZoekFields(_lock);

    ui->tbLevSlachthuis->setEnabled(!_lock);
    ui->tbLevLotnr->setEnabled(!_lock);
    ui->tbLevSanitel->setEnabled(!_lock);
    ui->tbLevDocument->setEnabled(!_lock);
    ui->tbLevRegel->setEnabled(!_lock);

}

Lotnummers::~Lotnummers()
{
    delete ui;
    delete rel;
    delete art;
    delete prd_model;
    delete srt_model;
    delete det_model;
    delete spec_model;
    delete loc_model;
    delete bevat_model;
    delete lot;
}

void Lotnummers::FillStockLocatieKeuze()
{
   loc_model = new QSqlQueryModel();
   StockLocaties::getAllStockLocaties(loc_model);
   ui->cbxLocatie->setModel(loc_model);
   ui->cbxLocatie->setModelColumn(1);
}

void Lotnummers::FillProductkeuze()
{
    prd_model = new QSqlQueryModel();
    Producten::getProductenKeuze(prd_model);
    ui->cbxProduct->setModel(prd_model);
    ui->cbxProduct->setModelColumn(1);
}

void Lotnummers::FillSoortkeuze()
{
    srt_model = new QSqlQueryModel();
    Soorten::getSoortenKeuze(srt_model, CurPrd_ID);
    ui->cbxSoort->setModel((srt_model));
    ui->cbxSoort->setModelColumn(1);
}

void Lotnummers::FillDetailKeuze()
{
    det_model = new QSqlQueryModel();
    Details::getDetailKeuze(det_model, CurPrd_ID, CurSrt_ID);
    ui->cbxDetail->setModel(det_model);
    ui->cbxDetail->setModelColumn(1);

}

void Lotnummers::FillSpecificatieKeuze()
{
    spec_model = new QSqlQueryModel();
    Specificaties::getSpecificatieKeuze(spec_model, CurPrd_ID, CurSrt_ID, CurDet_ID);
    ui->cbxSpecificatie->setModel(spec_model);
    ui->cbxSpecificatie->setModelColumn(1);
}

void Lotnummers::on_actionNieuw_triggered()
{
    CurrentLotnummer="";
    lot = new LotnummerData();
    QDateTime now = QDateTime::currentDateTimeUtc();
    CurrentLotnummer.sprintf("%04d%02d%02d%02d%02d%02d",
            now.date().year(),
            now.date().month(),
            now.date().day(),
            now.time().hour(),
            now.time().minute(),
            now.time().second());

    ui->tbLotnummer->setText(CurrentLotnummer);

    ui->cbActief->setChecked(true);
    ui->tbAfval->setText("0");
    ui->tbIn->setText("0");
    ui->tbUit->setText("0");

    //if (bevat_model != NULL)
    //    bevat_model->clear();
    bevat_model = new QSqlQueryModel();
    //bevat_model->clear();
    LotnummerdBevat::getBevatPerLotnummer(bevat_model, lot->getLotnummer_id());
    ui->tvLotnummers->setModel(bevat_model);
    LockAllFields(false);
    ui->actionAfsluiten->setEnabled(true);
    ui->actionNieuw->setEnabled(true);
    ui->actionBewerken->setEnabled(true);
    ui->actionLotnummer_opslaan->setEnabled(true);
    ui->actionPrint_Label->setEnabled(true);
    ui->tbLotnummer->setStyleSheet("color: rgb(255, 0, 0);");

}

void Lotnummers::LockAllFields(bool _lock)
{
    LockArtikelFields(_lock);
    LockLevFields(_lock);

    ui->tbOpmerking->setEnabled(!_lock);
    ui->dtpEigTgv->setEnabled(!_lock);
    ui->dtpInStock->setEnabled(!_lock);
    ui->dtpLevProdDatum->setEnabled(!_lock);
    ui->dtpLevTgv->setEnabled(!_lock);
    ui->dtpUiStock->setEnabled(!_lock);
    ui->cbActief->setEnabled(!_lock);

    ui->btnZoek_Art->setEnabled(!_lock);
    ui->btnWis_Art->setEnabled(!_lock);

    ui->btnZoek_Recept->setEnabled(!_lock);

    ui->grBevat->setEnabled(!_lock);

    ui->cbxLocatie->setEnabled(!_lock);

    ui->btnZoek_Lev->setEnabled(!_lock);
    ui->btnWis_Lev->setEnabled(!_lock);

    ui->btnAfval->setEnabled(!_lock);
}


void Lotnummers::on_actionPrint_Label_triggered()
{

    m_sSettingsFile = QApplication::applicationDirPath() + "/appSettings.ini";
    QSettings settings(m_sSettingsFile, QSettings::NativeFormat);

    QString PortNaam = settings.value("Printers/LotnrPr1", "").toString();

    QSerialPort sp(PortNaam);
    sp.setBaudRate(QSerialPort::Baud9600);
    sp.setDataBits(QSerialPort::Data8);
    sp.setFlowControl(QSerialPort::NoFlowControl);
    sp.setParity(QSerialPort::NoParity);
    sp.setStopBits(QSerialPort::OneStop);
    QString prData = "";
    if (sp.open(QIODevice::WriteOnly))
    {
        prData = "\n";
        sp.write(prData.toLatin1(),prData.length());
        prData = "N\n";
        sp.write(prData.toLatin1(),prData.length());
        prData = "A70,10,0,2,2,2,N,\"Den Eeuwigen Beenhouwer\"\n";
        sp.write(prData.toLatin1(),prData.length());
        prData = "LO60,45,700,3\n";
        sp.write(prData.toLatin1(),prData.length());
        prData = QString("B70,60,0,3,3,7,75,B,\"%1\"\n").arg(ui->tbLotnummer->text());
        sp.write(prData.toLatin1(),prData.length());
        prData = QString("B70,170,0,3,3,7,75,B,\"%1\"\n").arg(ui->tbArtikelnummer->text().remove(char('.')));
        sp.write(prData.toLatin1(),prData.length());
        prData = QString("A450,180,0,4,1,1,N,\"Prod: %1\"\n").arg(ui->dtpInStock->text());
        sp.write(prData.toLatin1(),prData.length());
        prData = QString("A450,220,0,4,1,1,N,\"tgv.: %1\"\n").arg(ui->dtpEigTgv->text());
        sp.write(prData.toLatin1(),prData.length());
        prData = QString("A70,300,0,4,1,1,N,\"Art: %1\"\n").arg(ui->tbArtikelNaam->text());
        sp.write(prData.toLatin1(),prData.length());
        prData = QString("A70,330,0,4,1,1,N,\"Lev: %1 bon: %2/%3\"\n").arg(ui->tbNaam->text().left(20), ui->tbLevDocument->text(),ui->tbLevRegel->text());
        sp.write(prData.toLatin1(),prData.length());
        prData = "P1\n";
        sp.write(prData.toLatin1(),prData.length());
        sp.flush();
        sp.close();
    }
    else
    {
        qDebug() << "Fout Seriele poort: " << sp.errorString() ;
    }

}

void Lotnummers::on_btnZoek_Lev_clicked()
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
            ui->tbEMail->setText(rel->getEMail_1());

            CurrentLev = rel->getRelatie_ID();

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
            ui->tbEMail->setText(rel->getEMail_1());

            CurrentLev =  rel->getRelatie_ID();
        }
    }
}

void Lotnummers::on_cbxProduct_currentIndexChanged(int index)
{
    QString artnr = ui->tbArtikelnummer->text();
    int _prod_id = ui->cbxProduct->model()->data( ui->cbxProduct->model()->index(index, 0 )).toInt(); //ui->cbxProduct->currentIndex()
    CurPrd_ID = _prod_id;
    // Aanpassen van het artikel nummer
    Producten prod(_prod_id);
    artnr = artnr.replace(0,1,prod.getProduct_Code());
    ui->tbArtikelnummer->setText(artnr);

    // Aanpassen Soort-Keuzelijst
    FillSoortkeuze();
}

void Lotnummers::on_cbxSoort_currentIndexChanged(int index)
{
    QString artnr = ui->tbArtikelnummer->text();
    int _srt_id = ui->cbxSoort->model()->data( ui->cbxSoort->model()->index(index, 0 )).toInt();
    CurSrt_ID = _srt_id;
    // Aanpassen van het artikel nummer
    Soorten srt(_srt_id);
    artnr = artnr.replace(2,1,srt.getSoortCode());
    ui->tbArtikelnummer->setText(artnr);

    // Aanpassen Detail-Keuzelijst
    FillDetailKeuze();
}

void Lotnummers::on_cbxDetail_currentIndexChanged(int index)
{
    QString artnr = ui->tbArtikelnummer->text();
    int _det_id = ui->cbxDetail->model()->data( ui->cbxDetail->model()->index(index, 0 )).toInt();
    CurDet_ID = _det_id;
    // Aanpassen van het artikel nummer
    Details det(_det_id);
    artnr = artnr.replace(4,2,det.getDetailCode());
    ui->tbArtikelnummer->setText(artnr);

    // Aanpassen Ras-Keuzelijst
    FillSpecificatieKeuze();
}


void Lotnummers::on_cbxSpecificatie_currentIndexChanged(int index)
{
    QString artnr = ui->tbArtikelnummer->text();
    int _spec_id = ui->cbxSpecificatie->model()->data( ui->cbxSpecificatie->model()->index(index, 0 )).toInt();
    CurSpec_ID = _spec_id;
    // Aanpassen van het artikel nummer
    Specificaties spec(_spec_id);
    artnr = artnr.replace(7,2,spec.getSpecificatieCode());
    ui->tbArtikelnummer->setText(artnr);
}

void Lotnummers::on_btnZoek_Art_clicked()
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
        ClearArtikelFields();
    }
    else
    {
        art = new Artikelen(id);
        FillArtikelFields();
        CurrentArt = id;
    }
}

void Lotnummers::ClearArtikelFields()
{
    ui->tbArtikelnummer->setText("000000");
    ui->tbArtikelNaam->setText("");
    ui->tbHoudbaarheid->setText("0");
    ui->tbVerpakking->setText("");
    ui->tbAfval->setText("0");
    ui->tbIn->setText("0");
    ui->tbUit->setText("0");
    ui->cbxProduct->setCurrentIndex(0);
}

void Lotnummers::LockArtikelFields(bool _lock)
{
    ui->tbArtikelnummer->setEnabled(!_lock);
    ui->tbArtikelNaam->setEnabled(!_lock);
    ui->tbHoudbaarheid->setEnabled(!_lock);
    ui->tbVerpakking->setEnabled(!_lock);
    ui->tbAfval->setEnabled(!_lock);
    ui->tbIn->setEnabled(!_lock);
    ui->tbUit->setEnabled(!_lock);
    ui->cbxRecept->setEnabled(!_lock);
    ui->cbxProduct->setEnabled(!_lock);
    ui->cbxSoort->setEnabled(!_lock);
    ui->cbxDetail->setEnabled(!_lock);
    ui->cbxSpecificatie->setEnabled(!_lock);
}


void Lotnummers::FillArtikelFields()
{
    ui->tbArtikelNaam->setText(art->getBenaming());

    ui->tbHoudbaarheid->setText(QString("%1").arg(art->getHoudbaarheid()));
    QDate prod, houd;
    prod = ui->dtpInStock->date();
    houd = prod.addDays(art->getHoudbaarheid());
    ui->dtpEigTgv->setDate(houd);
    ui->tbVerpakking->setText("");
    ui->tbAfval->setText("0");
    ui->tbIn->setText("0");
    ui->tbUit->setText("0");
}

void Lotnummers::on_tbArtikelnummer_editingFinished()
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

bool Lotnummers::AdjustSamenstelling(QString _code)
{
    bool gelukt = true;
    int index;
    QString Zoek;

    Zoek = _code.mid(0,1); Zoek.append(".");
    index = ui->cbxProduct->findText(Zoek, Qt::MatchStartsWith);
    if (index != -1)
    {
        ui->cbxProduct->setCurrentIndex(index);
        Zoek = _code.mid(1,1); Zoek.append(".");
        index = ui->cbxSoort->findText(Zoek, Qt::MatchStartsWith);
        if (index != -1)
        {
            ui->cbxSoort->setCurrentIndex(index);
            Zoek = _code.mid(2,2); Zoek.append(".");
            index = ui->cbxDetail->findText(Zoek, Qt::MatchStartsWith);
            if (index != -1)
            {
                ui->cbxDetail->setCurrentIndex(index);
                Zoek = _code.mid(4,2); Zoek.append(".");
                index = ui->cbxSpecificatie->findText(Zoek, Qt::MatchStartsWith);
                if (index != -1)
                {
                    ui->cbxSpecificatie->setCurrentIndex(index);
                }
                else
                {
                    gelukt = false;
                }
            }
            else
            {
                gelukt = false;
            }
        }
        else
        {
            gelukt = false;
        }
    }
    else
    {
        gelukt = false;
    }
    return gelukt;
}

void Lotnummers::ReadFields()
{
    // lotnummer character varying,
    lot->setLotnummer(ui->tbLotnummer->text());
    // opmerkingen character varying,
    lot->setOpmerkingen(ui->tbOpmerking->text());
    // datum_instock date,
    lot->setDatumInstock(ui->dtpInStock->date());
    // datum_eig_tgv date,
    lot->setDatumEigTgv(ui->dtpEigTgv->date());
    // datum_uitstock date,
    lot->setDatumUitstock(ui->dtpUiStock->date());
    // actief boolean,
    lot->setActief(ui->cbActief->isChecked());
    // artikel_id integer,
    lot->setArtikel_ID(CurrentArt);
    // hoeveelheid_in numeric(20,4)
    lot->setHoeveelheidIn(ui->tbIn->text().toDouble());
    // hoeveelheid_uit numeric(20,4),
    lot->setHoeveelheidUit(ui->tbUit->text().toDouble());
    // hoeveelheid_afval numeric(20,4),
    lot->setHoeveelheidAfval(ui->tbAfval->text().toDouble());
    // houdbaarheid integer,
    lot->setHoudbaarheid(ui->tbHoudbaarheid->text().toInt());
    // verpakking character varying,
    lot->setVerpakking(ui->tbVerpakking->text());
    // recept_productie integer,
    lot->setReceptProductie(0);
//  TODO
//    lot->setReceptProductie(
//                ui->cbxRecept->model()->data( ui->cbxRecept->model()->
//                index(ui->cbxRecept->currentIndex(), 0 )).toInt()
//                );
    // lev_id integer,
    lot->setLev_ID(CurrentLev);
    // lev_lotnr character varying,
    lot->setLevLotnr(ui->tbLevLotnr->text());
    // lev_slachthuis character varying,
    lot->setLevSlachthuis(ui->tbLevSlachthuis->text());
    // lev_sanitel character varying,
    lot->setLevSanitel(ui->tbLevSanitel->text());
    // lev_prod_datum date,
    lot->setLevProdDatum(ui->dtpLevProdDatum->date());
    // lev_tgv date,
    lot->setLevTgv(ui->dtpLevTgv->date());
    // lev_document character varying,
    lot->setLevDocument(ui->tbLevDocument->text());
    // lev_regel character varying,
    lot->setLevRegel(ui->tbLevRegel->text());
    // locatie_id int
    lot->setLocatie_ID(
                ui->cbxLocatie->model()->data( ui->cbxLocatie->model()->
                index(ui->cbxLocatie->currentIndex(), 0 )).toInt()
                );


}

void Lotnummers::FillFields()
{
    this->setWindowTitle(QString("Lotnummer met id: %1").arg(lot->getLotnummer_id()));
    // lotnummer character varying,
    ui->tbLotnummer->setText(lot->getLotnummer());
    CurrentLotnummer = lot->getLotnummer();
    // opmerkingen character varying,
    ui->tbOpmerking->setText(lot->getOpmerkingen());
    // datum_instock date,
    ui->dtpInStock->setDate(lot->getDatumInstock());
    // datum_eig_tgv date,
    ui->dtpEigTgv->setDate(lot->getDatumEigTgv());
    // datum_uitstock date,
    ui->dtpUiStock->setDate(lot->getDatumUitstock());
    // actief boolean,
    ui->cbActief->setChecked(lot->getActief());
    // artikel_id integer,
    CurrentArt = lot->getArtikel_ID();
    art = new Artikelen(CurrentArt);
    ui->tbArtikelnummer->setText(art->getCode());
    ui->tbArtikelNaam->setText(art->getBenaming());
    ui->tbHoudbaarheid->setText(QString("%1").arg(art->getHoudbaarheid()));
    AdjustSamenstelling(art->getCode());
    // hoeveelheid_in numeric(20,4),
    ui->tbIn->setText(QString("%1").arg(lot->getHoeveelheidIn()));
    // hoeveelheid_uit numeric(20,4),
    ui->tbUit->setText(QString("%1").arg(lot->getHoeveelheidUit()));
    // hoeveelheid_afval numeric(20,4),
    ui->tbAfval->setText(QString("%1").arg(lot->getHoeveelheidAfval()));
    // houdbaarheid integer,
    ui->tbHoudbaarheid->setText(QString::number(lot->getHoudbaarheid()));
    // verpakking character varying,
    ui->tbVerpakking->setText(lot->getVerpakking());
    // recept_productie integer,

    // lev_id integer,
    CurrentLev = lot->getLev_ID();
    rel = new Relaties(CurrentLev);
    ui->tbNummer->setText( QString("%1").arg(rel->getRelatie_ID()));
    ui->tbNaam->setText(rel->getNaam() + " " + rel->getVoornaam());
    ui->tbStraat->setText(rel->getAdres());
    ui->tbGemeente->setText(Postcodes::getGemeente(rel->getGemeente_ID()));
    ui->tbEMail->setText(rel->getEMail_1());

    // lev_lotnr character varying,
    ui->tbLevLotnr->setText(lot->getLevLotnr());
    // lev_slachthuis character varying,
    ui->tbLevSlachthuis->setText(lot->getLevSlachthuis());
    // lev_sanitel character varying,
    ui->tbLevSanitel->setText(lot->getLevSanitel());
    // lev_prod_datum date,
    ui->dtpLevProdDatum->setDate(lot->getLevProdDatum());
    // lev_tgv date,
    ui->dtpLevTgv->setDate(lot->getLevTgv());
    // lev_document character varying,
    ui->tbLevDocument->setText(lot->getLevDocument());
    // lev_regel character varying,
    ui->tbLevRegel->setText(lot->getLevRegel());
    // locatie_id int
    ui->cbxLocatie->setCurrentIndex(
                (lot->getLocatie_ID() == 0 ? 0 :
                ui->cbxLocatie->model()->match(
                ui->cbxLocatie->model()->index(0, 0),
                Qt::DisplayRole,
                QVariant::fromValue(lot->getLocatie_ID()),
                -1,
                Qt::MatchFixedString)[0].row()));
    ui->tbLotnummer->setStyleSheet("color: rgb(255, 0, 0);");
    FillBevatTable();
}

void Lotnummers::on_actionLotnummer_opslaan_triggered()
{
    ReadFields();
    if (lot->getArtikel_ID() == 0)
    {
        QMessageBox msgBox;
        msgBox.setText("<strong>Geen artikel opgegeven !</strong>");
        msgBox.setInformativeText("(Vergeten op zoeken klikken?");
        msgBox.setStandardButtons(QMessageBox::Cancel);
        msgBox.setDefaultButton(QMessageBox::Cancel);
        msgBox.setIcon(QMessageBox::Warning);
        msgBox.setWindowTitle("Opgepast !");
        QSpacerItem *hs = new QSpacerItem(400, 0, QSizePolicy::Minimum, QSizePolicy::Expanding);
        QGridLayout *gl = (QGridLayout*)msgBox.layout();
        gl->addItem(hs, gl->rowCount(), 0, 1, gl->columnCount());
        msgBox.exec();
    }
    else if (lot->getLev_ID() == 0)
    {
        QMessageBox msgBox;
        msgBox.setText("<strong>Geen leverancier opgegeven !</strong>");
        msgBox.setInformativeText("Je kan de leverancier opzoeken");
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
        lot->save();
        ui->tbLotnummer->setStyleSheet("color: rgb(0, 0, 255);");
    }
}

void Lotnummers::on_tbLotnummer_editingFinished()
{
    if((!ui->tbLotnummer->text().trimmed().isEmpty()) &
            (ui->tbLotnummer->text() != CurrentLotnummer))
    {
        ui->tbLotnummer->setStyleSheet("color: rgb(255, 0, 0);");
        lot = new LotnummerData(ui->tbLotnummer->text().trimmed());
        if (lot->getLotnummer_id() == 0)
        {
            ui->tbLotnummer->setText("");
            QMessageBox msgBox;
            msgBox.setText("<strong>Onbekend Lotnummer !</strong>");
            msgBox.setInformativeText("Het ingegeven lotnummer is onbekend,\ngelieve enkel bestaande lotnummers op te geven.");
            msgBox.setStandardButtons(QMessageBox::Cancel);
            msgBox.setDefaultButton(QMessageBox::Cancel);
            msgBox.setIcon(QMessageBox::Critical);
            msgBox.setWindowTitle("Opgepast !");
            //msgBox.setStyleSheet("min-width: 150px;");
            QSpacerItem *hs = new QSpacerItem(400, 0, QSizePolicy::Minimum, QSizePolicy::Expanding);
            QGridLayout *gl = (QGridLayout*)msgBox.layout();
            gl->addItem(hs, gl->rowCount(), 0, 1, gl->columnCount());
            msgBox.exec();

            ui->tbLotnummer->setFocus();
        }
        else
        {
            FillFields();
            ui->actionAfsluiten->setEnabled(true);
            ui->actionNieuw->setEnabled(true);
            ui->actionBewerken->setEnabled(true);
            ui->actionLotnummer_opslaan->setEnabled(true);
            ui->actionPrint_Label->setEnabled(true);
            FillBevatTable();
        }
    }
}

void Lotnummers::on_actionAfsluiten_triggered()
{
    this->close();
}

void Lotnummers::on_tbHoudbaarheid_editingFinished()
{
    int aantal;
    bool ok;
    aantal = ui->tbHoudbaarheid->text().toInt(&ok);
    if (!ok)
    {
        QMessageBox msgBox;
        msgBox.setText("<strong>Foutieve ingave !</strong>");
        msgBox.setInformativeText("U mag hier enkel een geldige waarde ingeven.\n Enkel gehele getallen zonder decimaal teken.");
        msgBox.setStandardButtons(QMessageBox::Cancel);
        msgBox.setDefaultButton(QMessageBox::Cancel);
        msgBox.setIcon(QMessageBox::Critical);
        msgBox.setWindowTitle("Opgepast !");
        //msgBox.setStyleSheet("min-width: 150px;");
        QSpacerItem *hs = new QSpacerItem(400, 0, QSizePolicy::Minimum, QSizePolicy::Expanding);
        QGridLayout *gl = (QGridLayout*)msgBox.layout();
        gl->addItem(hs, gl->rowCount(), 0, 1, gl->columnCount());
        msgBox.exec();
        ui->tbHoudbaarheid->setText("0");
        ui->tbHoudbaarheid->selectAll();
        ui->tbHoudbaarheid->setFocus();
    }
}

void Lotnummers::on_tbIn_editingFinished()
{
    double bedrag;
    bool ok;
    bedrag = ui->tbIn->text().toDouble(&ok);
    if (!ok)
    {
        MeldGetalError();
        ui->tbIn->setText("0.0");
        ui->tbIn->selectAll();
        ui->tbIn->setFocus();
    }
}

void Lotnummers::MeldGetalError()
{
    QMessageBox msgBox;
    msgBox.setText("<strong>Foutieve ingave !</strong>");
    msgBox.setInformativeText("U mag hier enkel een geldig getal ingeven.\n Getallen en het correcte decimaal teken.");
    msgBox.setStandardButtons(QMessageBox::Cancel);
    msgBox.setDefaultButton(QMessageBox::Cancel);
    msgBox.setIcon(QMessageBox::Critical);
    msgBox.setWindowTitle("Opgepast !");
    //msgBox.setStyleSheet("min-width: 150px;");
    QSpacerItem *hs = new QSpacerItem(400, 0, QSizePolicy::Minimum, QSizePolicy::Expanding);
    QGridLayout *gl = (QGridLayout*)msgBox.layout();
    gl->addItem(hs, gl->rowCount(), 0, 1, gl->columnCount());
    msgBox.exec();
}

void Lotnummers::on_tbUit_editingFinished()
{
    double bedrag;
    bool ok;
    bedrag = ui->tbUit->text().toDouble(&ok);
    if (!ok)
    {
        MeldGetalError();
        ui->tbUit->setText("0.0");
        ui->tbUit->selectAll();
        ui->tbUit->setFocus();
    }
}

void Lotnummers::on_tbAfval_editingFinished()
{
    double bedrag;
    bool ok;
    bedrag = ui->tbAfval->text().toDouble(&ok);
    if (!ok)
    {
        MeldGetalError();
        ui->tbAfval->setText("0.0");
        ui->tbAfval->selectAll();
        ui->tbAfval->setFocus();
    }
}

void Lotnummers::on_btnWis_Lev_clicked()
{
    ClearLevFields();
}

void Lotnummers::on_btnWis_Art_clicked()
{
    ClearArtikelFields();
}

void Lotnummers::on_btnAfval_clicked()
{
    QMessageBox msgBox;
    msgBox.setText("<strong>Opwerking lotnumme !</strong>");
    msgBox.setInformativeText("U gaat de rest van de voorraad als afval verwerken\nen het lot als niet actief markeren.\nIS HET DAT WAT U WENST TE DOEN ?");
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
        double afval = 0;
        afval = ui->tbIn->text().toDouble() - ui->tbUit->text().toDouble();
        ui->tbAfval->setText(QString("%1").arg(afval));
        ui->cbActief->setChecked(false);
        ui->dtpUiStock->setDate(QDate::currentDate());
        ReadFields();
        lot->setLocatie_ID(16);
        lot->save();
        LockAllFields(true);
    }
}

void Lotnummers::on_actionBewerken_triggered()
{
    LockAllFields(false);
}

void Lotnummers::on_btnNew_clicked()
{
    if (lot->getLotnummer_id() == 0)
    {
        on_actionLotnummer_opslaan_triggered();
    }
    SamengesteldeLotnummers sl(0, lot->getLotnummer_id());
    sl.exec();
    FillBevatTable();
}

void Lotnummers::FillBevatTable()
{
    bevat_model = new QSqlQueryModel();
    LotnummerdBevat::getBevatPerLotnummer(bevat_model, lot->getLotnummer_id());
    bevat_model->setHeaderData(1, Qt::Horizontal, tr("Lotnummer"));
    bevat_model->setHeaderData(2, Qt::Horizontal, tr("Artikelnr."));
    bevat_model->setHeaderData(3, Qt::Horizontal, tr("Benaming"));
    bevat_model->setHeaderData(4, Qt::Horizontal, tr("Hoeveel."));
    ui->tvLotnummers->setModel(bevat_model);
    ui->tvLotnummers->hideColumn(0);
    ui->tvLotnummers->setColumnWidth(1,120);
    ui->tvLotnummers->setColumnWidth(2,80);
    ui->tvLotnummers->setColumnWidth(3,200);
    ui->tvLotnummers->setColumnWidth(4,80);
    ui->tvLotnummers->verticalHeader()->setDefaultSectionSize(20);
    ui->tvLotnummers->setAlternatingRowColors(true);
}

void Lotnummers::on_btnDelete_clicked()
{
    QMessageBox msgBox;
    msgBox.setText("<strong>Gegevens Wissen!</strong>");
    msgBox.setInformativeText("Wilt u zeker deze gegevens wissen?");
    msgBox.setStandardButtons(QMessageBox::No | QMessageBox::Yes);
    msgBox.setDefaultButton(QMessageBox::No);
    msgBox.setIcon(QMessageBox::Critical);
    msgBox.setWindowTitle("Opgepast !");
    QSpacerItem *hs = new QSpacerItem(400, 0, QSizePolicy::Minimum, QSizePolicy::Expanding);
    QGridLayout *gl = (QGridLayout*)msgBox.layout();
    gl->addItem(hs, gl->rowCount(), 0, 1, gl->columnCount());
    if (msgBox.exec() == QMessageBox::Yes)
    {
        if (ui->tvLotnummers->model()->rowCount() > 0)
        {
            int _ID = ui->tvLotnummers->model()->data( ui->tvLotnummers->model()->index(ui->tvLotnummers->currentIndex().row(), 0)).toInt();
            LotnummerdBevat lb(_ID);
            int lot_id = lb.getBetvatLotnummer();
            LotnummerData lt(lot_id);
            double uit = lt.getHoeveelheidUit();
            uit = uit - lb.getHoeveelheidIn();
            lt.setHoeveelheidUit(uit);

            lt.save();
            if (lt.getLotnummer_id() == lot->getLotnummer_id())
            {
                ui->tbUit->setText(QString("%1").arg(uit));
            }
            LotnummerdBevat::deleteRow(_ID);
        }
        FillBevatTable();
        if (ui->tvLotnummers->model()->rowCount() > 0)
        {
            ui->tvLotnummers->selectRow(0);
        }
    }
}

void Lotnummers::on_btnEdit_clicked()
{
    int _ID = ui->tvLotnummers->model()->data( ui->tvLotnummers->model()->index(ui->tvLotnummers->currentIndex().row(), 0)).toInt();
    SamengesteldeLotnummers sl(_ID, lot->getLotnummer_id());
    sl.exec();
    FillBevatTable();
}

void Lotnummers::on_actionOp_artikelnr_triggered()
{
    ZoekLotOpArtikel* za = new ZoekLotOpArtikel();
    za->exec();
    if (za->getLotID() != 0)
    {
        int id = za->getLotID();
        lot = new LotnummerData(id);
        FillFields();
        ui->actionAfsluiten->setEnabled(true);
        ui->actionNieuw->setEnabled(true);
        ui->actionBewerken->setEnabled(true);
        ui->actionLotnummer_opslaan->setEnabled(true);
        ui->actionPrint_Label->setEnabled(true);
        FillBevatTable();
    }
    //delete za;
}


void Lotnummers::on_cbxLocatie_currentIndexChanged(int index)
{
    if (initialised)
    {
        lot->setLocatieVeranderdOp(QDateTime::currentDateTime());
    }

}
