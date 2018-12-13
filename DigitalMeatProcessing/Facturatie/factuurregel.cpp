#include "factuurregel.h"
#include "math.h"

#include "ui_factuurregel.h"
#include "CommonObjects/btwtarieven.h"
#include "ArtikelBeheer/producten.h"
#include "ArtikelBeheer/soorten.h"
#include "ArtikelBeheer/details.h"
#include "ArtikelBeheer/specificaties.h"
#include "ArtikelBeheer/comeenheden.h"

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

FactuurRegel::FactuurRegel(int _factuurID, int _id, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::FactuurRegel)
{
    ui->setupUi(this);
    art = new Artikelen();
    CurrentFactuurID = _factuurID;
    BTW_model = new QSqlQueryModel();
    Eenh_model = new QSqlQueryModel();

    FillBTWKeuze();
    FillEenheidKeuze();
    ClearArtikelFields();
    FillProductkeuze();


    if (_id == 0)
    {
        // Nieuwe regel


        fl = new FactuurLine();
        ui->tbArtikelnummer->setFocus();
        ui->tbArtikelnummer->selectAll();

    }
    else
    {
        // Bestaande regel
        fl = new FactuurLine(_id);
        FillRecord();
    }
}

FactuurRegel::~FactuurRegel()
{
    delete ui;
    delete art;
    delete BTW_model;
    delete Eenh_model;
}

void FactuurRegel::FillProductkeuze()
{
    prd_model = new QSqlQueryModel();
    Producten::getProductenKeuze(prd_model);
    ui->cbxProduct->setModel(prd_model);
    ui->cbxProduct->setModelColumn(1);
}

void FactuurRegel::FillSoortkeuze()
{
    srt_model = new QSqlQueryModel();
    Soorten::getSoortenKeuze(srt_model, CurPrd_ID);
    ui->cbxSoort->setModel((srt_model));
    ui->cbxSoort->setModelColumn(1);
}

void FactuurRegel::FillDetailKeuze()
{
    det_model = new QSqlQueryModel();
    Details::getDetailKeuze(det_model, CurPrd_ID, CurSrt_ID);
    ui->cbxDetail->setModel(det_model);
    ui->cbxDetail->setModelColumn(1);

}

void FactuurRegel::FillSpecificatieKeuze()
{
    spec_model = new QSqlQueryModel();
    Specificaties::getSpecificatieKeuze(spec_model, CurPrd_ID, CurSrt_ID, CurDet_ID);
    ui->cbxSpecificatie->setModel(spec_model);
    ui->cbxSpecificatie->setModelColumn(1);
}


void FactuurRegel::on_btnZoek_Art_clicked()
{
    QString code;
    int id;
    code = ui->tbArtikelnummer->text().remove(char('.'));
    if (code != "000000")
    {
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
            ui->tbEenheidsprijs->setFocus();
            ui->tbEenheidsprijs->selectAll();
        }
    }
}

void FactuurRegel::ClearArtikelFields()
{
    ui->tbArtikelCode->setText("");
    ui->tbArtikelNaam->setText("");
    ui->tbArtikelnummer->setText("0.0.00.00");
    ui->tbEenheidsprijs->setText("0.00");
    ui->tbHoeveelheid->setText("0.00");
    ui->tbKorting->setText("0.00");

    ui->tb_BTW_B->setText("0.00");
    ui->tb_BTW_P->setText("0.00");
    ui->tb_code->setText("");
    ui->tb_Eenh->setText("");
    ui->tb_EP->setText("0.00");
    ui->tb_Hoeveel->setText("0.00");
    ui->tb_Ko->setText("0.00");
    ui->tb_LP->setText("0.00");
    ui->tb_omschr->setText("");
    ui->tb_Pr->setText("0.00");
    ui->tb_PrKo->setText("0.00");
}

void FactuurRegel::FillRecord()
{
    ui->tbArtikelCode->setText(fl->getArtikelCode());
    ui->tbArtikelNaam->setText(fl->getOmschrijving());
    ui->tbEenheidsprijs->setText(QString("%1").arg(fl->getEenheidsprijs(), 0,'f',2));

    int BTWCode = BTWTarieven::getBTWTariefByPercent(fl->getBTW_Percent());
    ui->cbxBTW->setCurrentIndex(
                (BTWCode == 0 ? 0 :
                ui->cbxBTW->model()->match(
                ui->cbxBTW->model()->index(0, 0),
                Qt::DisplayRole,
                QVariant::fromValue(BTWCode),
                -1,
                Qt::MatchFixedString)[0].row()));

    ui->tbHoeveelheid->setText(QString("%1").arg(fl->getAantal(), 0,'f',2));

    // EENHEID
    int EenheidsID = ComEenheden::getComEenheidsID(fl->getEenheid());
    ui->cbxEenheid->setCurrentIndex(
                (EenheidsID == 0 ? 0 :
                ui->cbxEenheid->model()->match(
                ui->cbxEenheid->model()->index(0, 0),
                Qt::DisplayRole,
                QVariant::fromValue(EenheidsID),
                -1,
                Qt::MatchFixedString)[0].row()));

    ui->tbKorting->setText(QString("%1").arg(fl->getKortingPercent(), 0,'f',2));

    Bereken();
}

void FactuurRegel::FillArtikelFields()
{
    double Prijs;
    ui->tbArtikelCode->setText(art->getCode());
    ui->tbArtikelNaam->setText(art->getBenaming());
    if((art->getPromoVan() <= QDate::currentDate()) & (art->getPromoTot() >= QDate::currentDate()))
    {
        Prijs = art->getPromoPrijs();
        ui->cbPromo->setChecked(true);
    }
    else
    {
        Prijs = art->getVerkoopPrijs();
        ui->cbPromo->setChecked(false);
    }

    ui->tbEenheidsprijs->setText(QString("%1").arg(Prijs, 0,'f',2));
    ui->cbxBTW->setCurrentIndex(
                (art->getBTWVerkoop() == 0 ? 0 :
                ui->cbxBTW->model()->match(
                ui->cbxBTW->model()->index(0, 0),
                Qt::DisplayRole,
                QVariant::fromValue(art->getBTWVerkoop()),
                -1,
                Qt::MatchFixedString)[0].row()));

    ui->cbxEenheid->setCurrentIndex(
                (art->getEenheidVerkoop() == 0 ? 0 :
                ui->cbxEenheid->model()->match(
                ui->cbxEenheid->model()->index(0, 0),
                Qt::DisplayRole,
                QVariant::fromValue(art->getEenheidVerkoop()),
                -1,
                Qt::MatchFixedString)[0].row()));

    Bereken();
}

void FactuurRegel::FillBTWKeuze()
{
    BTW_model = new QSqlQueryModel();
    BTWTarieven::getBTWTarievenKeuze(BTW_model);
    ui->cbxBTW->setModel(BTW_model);
    ui->cbxBTW->setModelColumn(1);
}

void FactuurRegel::FillEenheidKeuze()
{
    Eenh_model = new QSqlQueryModel();
    ComEenheden::getComEenhedenKeuze(Eenh_model);
    ui->cbxEenheid->setModel(Eenh_model);
    ui->cbxEenheid->setModelColumn(1);
}

void FactuurRegel::Bereken()
{
    double EP, Aant, Bruto, KortP, KortB, Excl, BtwP, BtwB, LP;
    ui->tb_code->setText(ui->tbArtikelCode->text());
    ui->tb_omschr->setText(ui->tbArtikelNaam->text());

    EP = ui->tbEenheidsprijs->text().toDouble();
    ui->tb_EP->setText(ui->tbEenheidsprijs->text());

    Aant = ui->tbHoeveelheid->text().toDouble();
    ui->tb_Hoeveel->setText(ui->tbHoeveelheid->text());

    int eenh = ui->cbxEenheid->model()->data( ui->cbxEenheid->model()->index(ui->cbxEenheid->currentIndex(), 0 )).toInt();
    ui->tb_Eenh->setText(ComEenheden::getComEenheidsCode(eenh));

    Bruto = floor(EP * Aant * 100 + 0.5)/100;
    ui->tb_Pr->setText(QString("%1").arg(Bruto, 0, 'f', 2));

    KortP = ui->tbKorting->text().toDouble()/100;
    KortB = floor(Bruto * KortP *100 + 0.5)/100;
    ui->tb_Ko->setText(QString("%1").arg(KortB, 0, 'f', 2));

    Excl = Bruto - KortB;
    ui->tb_PrKo->setText(QString("%1").arg(Excl, 0, 'f', 2));

    BtwP = BTWTarieven::getBTWPercentage(ui->cbxBTW->model()->data( ui->cbxBTW->model()->index(ui->cbxBTW->currentIndex(), 0 )).toInt());
    ui->tb_BTW_P->setText(QString("%1").arg(BtwP, 0, 'f', 2));

    BtwB = Excl *(BtwP / 100);
    ui->tb_BTW_B->setText(QString("%1").arg(BtwB, 0, 'f', 2));

    LP = Excl * (1 + BtwP/100);
    ui->tb_LP->setText(QString("%1").arg(LP, 0, 'f', 2));

}

void FactuurRegel::on_tbEenheidsprijs_editingFinished()
{
    Bereken();
}

void FactuurRegel::on_tbHoeveelheid_editingFinished()
{
    Bereken();
}

void FactuurRegel::on_tbKorting_editingFinished()
{
    Bereken();
}

void FactuurRegel::on_tbArtikelCode_editingFinished()
{
    Bereken();
}

void FactuurRegel::on_tbArtikelNaam_editingFinished()
{
    Bereken();
}

void FactuurRegel::on_cbxBTW_currentIndexChanged(int index)
{
    Bereken();
}

void FactuurRegel::on_cbxEenheid_currentIndexChanged(int index)
{
    Bereken();
}

void FactuurRegel::on_tbArtikelnummer_editingFinished()
{
    on_btnZoek_Art_clicked();
}

void FactuurRegel::on_btnAnnuleren_clicked()
{
    this->close();
}

void FactuurRegel::on_btnOvernemen_clicked()
{
    ReadFields();
    fl->save();
    this->close();
}

void FactuurRegel::ReadFields()
{
    fl->setFactuur_ID(CurrentFactuurID);
    fl->setArtikel_ID(CurrentArt);
    fl->setArtikelCode(ui->tbArtikelCode->text());
    fl->setOmschrijving(ui->tbArtikelNaam->text());
    fl->setAantal(ui->tbHoeveelheid->text().toDouble());
    fl->setEenheid(ui->tb_Eenh->text());
    fl->setEenheidsprijs(ui->tbEenheidsprijs->text().toDouble());
    fl->setKortingPercent(ui->tbKorting->text().toDouble());
    fl->setBTW_Percent(ui->tb_BTW_P->text().toDouble());
}

void FactuurRegel::on_cbxProduct_currentIndexChanged(int index)
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

void FactuurRegel::on_cbxSoort_currentIndexChanged(int index)
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

void FactuurRegel::on_cbxDetail_currentIndexChanged(int index)
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

void FactuurRegel::on_cbxSpecificatie_currentIndexChanged(int index)
{
    QString artnr = ui->tbArtikelnummer->text();
    int _spec_id = ui->cbxSpecificatie->model()->data( ui->cbxSpecificatie->model()->index(index, 0 )).toInt();
    CurSpec_ID = _spec_id;
    // Aanpassen van het artikel nummer
    Specificaties spec(_spec_id);
    artnr = artnr.replace(7,2,spec.getSpecificatieCode());
    ui->tbArtikelnummer->setText(artnr);
}

void FactuurRegel::on_btnWis_Art_clicked()
{
    ClearArtikelFields();
}

void FactuurRegel::on_btnWissen_clicked()
{
    if (fl->getFactuurLine_ID() != 0)
    {
        QMessageBox msgBox;
        msgBox.setText("<strong>Wil je deze regel echt wissen !</strong>");
        msgBox.setInformativeText("Wissen");
        msgBox.setStandardButtons(QMessageBox::No | QMessageBox::Yes);
        msgBox.setDefaultButton(QMessageBox::No);
        msgBox.setIcon(QMessageBox::Warning);
        msgBox.setWindowTitle("Opgepast !");
        QSpacerItem *hs = new QSpacerItem(400, 0, QSizePolicy::Minimum, QSizePolicy::Expanding);
        QGridLayout *gl = (QGridLayout*)msgBox.layout();
        gl->addItem(hs, gl->rowCount(), 0, 1, gl->columnCount());
        //msgBox.exec();
        if (msgBox.exec() == QMessageBox::Yes)
        {
            fl->wis();
            this->close();
        }
    }
}
