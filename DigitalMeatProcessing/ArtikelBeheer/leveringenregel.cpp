#include "leveringenregel.h"

#include "ui_leveringenregel.h"
#include "CommonObjects/btwtarieven.h"
#include "ArtikelBeheer/producten.h"
#include "ArtikelBeheer/soorten.h"
#include "ArtikelBeheer/details.h"
#include "ArtikelBeheer/specificaties.h"
#include "ArtikelBeheer/comeenheden.h"
#include "Bestellingen/leveringenheader.h"

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
#include <QDebug>
#include <QtMath>


LeveringenRegel::LeveringenRegel(int _id, LeveringenHeader* _lh, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::LeveringenRegel)
{
    initialised = false;
    ui->setupUi(this);

    lh = _lh;
    vorigeVKP = 0;
    vorigeMarge = 0;


    ClearAllFields();
    FillBTWKeuze();
    FillEenheidKeuze();
    FillProductkeuze();

    // background-color: rgb(245, 241, 241);
    ui->tbGewenstePrijs->setValidator(new QDoubleValidator());
    ui->tbGewenstePrijs->setStyleSheet("background-color: rgb(245, 241, 241);");
    ui->tbGewenstePrijs->setReadOnly(true);
    ui->tbGewensteMarge->setValidator(new QDoubleValidator());
    ui->tbGewensteMarge->setStyleSheet("background-color: rgb(245, 241, 241);");
    ui->tbGewensteMarge->setReadOnly(true);
    ui->btnPrijsOvernemn->setVisible(false);
    ui->btnPrijsAanpassen->setVisible(true);
    ui->btnPrijsOpslaan->setVisible(false);
    ui->btnPrijsAnnuleren->setVisible(false);
    ui->btnMargeOvernemen->setVisible(false);

    ui->tbEenheidsprijs->setValidator(new QDoubleValidator());
    ui->tbHoeveelheid->setValidator(new QDoubleValidator());

    if(_id == 0)
    {
        // Nieuwe regel
        ll = new LeveringenLine(0);
        lc = new LeverancierCodes();
        CurrentLeArtID = 0;
        ui->tbArtikelnummer->setFocus();
        ui->tbArtikelnummer->selectAll();
        initialised = true;
    }
    else
    {
        // Bestaande regel
        ll = new LeveringenLine(_id);
        lc = new LeverancierCodes( ll->getLevArt_ID(), lh->getLeverancier_ID()) ;
        CurrentLeArtID = ll->getLevArt_ID();
        art = new Artikelen(ll->getArt_ID());
        QString artcode = art->getCode();
        initialised = true;
        FillFields();
    }
}

LeveringenRegel::~LeveringenRegel()
{
    delete ui;
    delete ll;
    delete lc;
    delete BTW_model;
    delete Eenh_model;
    delete art;
}

void LeveringenRegel::FillProductkeuze()
{
    prd_model = new QSqlQueryModel();
    Producten::getProductenKeuze(prd_model);
    ui->cbxProduct->setModel(prd_model);
    ui->cbxProduct->setModelColumn(1);
}

void LeveringenRegel::FillSoortkeuze()
{
    srt_model = new QSqlQueryModel();
    Soorten::getSoortenKeuze(srt_model, CurPrd_ID);
    ui->cbxSoort->setModel((srt_model));
    ui->cbxSoort->setModelColumn(1);
}

void LeveringenRegel::FillDetailKeuze()
{
    det_model = new QSqlQueryModel();
    Details::getDetailKeuze(det_model, CurPrd_ID, CurSrt_ID);
    ui->cbxDetail->setModel(det_model);
    ui->cbxDetail->setModelColumn(1);

}

void LeveringenRegel::FillSpecificatieKeuze()
{
    spec_model = new QSqlQueryModel();
    Specificaties::getSpecificatieKeuze(spec_model, CurPrd_ID, CurSrt_ID, CurDet_ID);
    ui->cbxSpecificatie->setModel(spec_model);
    ui->cbxSpecificatie->setModelColumn(1);
}


void LeveringenRegel::on_btnZoek_Art_clicked()
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
            art = new Artikelen();
            ClearArtikelFields();
        }
        else
        {
            art = new Artikelen(id);
            lc = new LeverancierCodes(art->getArtikel_ID(), lh->getLeverancier_ID());
            CurrentLeArtID = lc->getLevRef_ID();
            if (CurrentLeArtID == 0)
            {
                // LeveranciersArtikel onbekend, wil je het aanmaken
                QMessageBox msgBox;
                msgBox.setText("<strong>Onbekend Leverancier Artikel !\nWilt u het nu aanmaken?</strong>");
                msgBox.setInformativeText("Artikel onbekend");
                msgBox.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
                msgBox.setDefaultButton(QMessageBox::Yes);
                msgBox.setIcon(QMessageBox::Question);
                msgBox.setWindowTitle("Opgepast !");
                QSpacerItem *hs = new QSpacerItem(400, 0, QSizePolicy::Minimum, QSizePolicy::Expanding);
                QGridLayout *gl = (QGridLayout*)msgBox.layout();
                gl->addItem(hs, gl->rowCount(), 0, 1, gl->columnCount());
                if (msgBox.exec() == QMessageBox::Yes)
                {
                    lc = new LeverancierCodes();
                    lc->setArt_ID(art->getArtikel_ID());
                    lc->setLev_ID(lh->getLeverancier_ID());
                    LevCodeFiche* lcf = new LevCodeFiche(lc);
                    lcf->exec();
                    CurrentLeArtID = lc->getLevRef_ID();
                    lcf->deleteLater();
                }
            }
            ll->setArt_ID(art->getArtikel_ID());
            ll->setArtikelCode(art->getCode());
            ll->setArtikelOmschrijving(art->getBenaming());
            ll->setBtwCode(art->getBTWVerkoop());
            ll->setEenheid(art->getEenheidVerkoop());


            FillFields();
            CurrentArt = id;
            ui->tbEenheidsprijs->setFocus();
            ui->tbEenheidsprijs->selectAll();
        }
    }

}

void LeveringenRegel::ClearArtikelFields()
{
    ui->tbArtikelCode->setText("");
    ui->tbArtikelNaam->setText("");
    ui->tbArtikelnummer->setText("0.0.00.00");
    ui->tbEenheidsprijs->setText("0.00");
    ui->tbHoeveelheid->setText("0.00");
    FillProductkeuze();
    Bereken();
}

void LeveringenRegel::ClearAllFields()
{
    ui->tbLevArtikelCode->setText("");
    ui->tbLevArtikelNaam->setText("");
    ui->tbArtikelCode->setText("");
    ui->tbArtikelNaam->setText("");
    ui->tbEenheidsprijs->setText("");
    ui->tbHoeveelheid->setText("");

    ui->tb_code->setText("");
    ui->tb_omschr->setText("");
    ui->tb_EP->setText("");
    ui->tb_Hoeveel->setText("");
    ui->tb_Eenh->setText("");
    ui->tb_PrKo->setText("");
    ui->tb_BTW_P->setText("");
    ui->tb_BTW_B->setText("");
    ui->tb_LP->setText("");

    ui->tb_code_vk->setText("");
    ui->tb_omschr_vk->setText("");
    ui->tb_EP_vk->setText("");
    ui->tb_Hoeveel_vk->setText("");
    ui->tb_Eenh_vk->setText("");
    ui->tb_PrKo_vk->setText("");
    ui->tb_BTW_P_vk->setText("");
    ui->tb_BTW_B_vk->setText("");
    ui->tb_LP_vk->setText("");

    ui->tbHuidigeMarge->setText("");
    ui->tbGewensteMarge->setText("");
    ui->tbGewenstePrijs->setText("");

}

void LeveringenRegel::FillBTWKeuze()
{
    BTW_model = new QSqlQueryModel();
    BTWTarieven::getBTWTarievenKeuze(BTW_model);
    ui->cbxBTW->setModel(BTW_model);
    ui->cbxBTW->setModelColumn(1);
}

void LeveringenRegel::FillEenheidKeuze()
{
    Eenh_model = new QSqlQueryModel();
    ComEenheden::getComEenhedenKeuze(Eenh_model);
    ui->cbxEenheid->setModel(Eenh_model);
    ui->cbxEenheid->setModelColumn(1);
}



void LeveringenRegel::Bereken()
{
    double EP, Aant, Excl, BtwP, BtwB, LP;

    if (initialised)
    {
        ui->tb_code->setText(ui->tbLevArtikelCode->text());
        ui->tb_omschr->setText(ui->tbLevArtikelNaam->text());

        // aankoop
        EP = ui->tbEenheidsprijs->text().toDouble();
        ll->setEenheidsprijs(EP);
        ui->tb_EP->setText(ui->tbEenheidsprijs->text());

        Aant = ui->tbHoeveelheid->text().toDouble();
        ll->setAantal(Aant);
        ui->tb_Hoeveel->setText(ui->tbHoeveelheid->text());

        int eenh = ui->cbxEenheid->model()->data( ui->cbxEenheid->model()->index(ui->cbxEenheid->currentIndex(), 0 )).toInt();
        ll->setEenheid(eenh);
        ui->tb_Eenh->setText(ComEenheden::getComEenheidsCode(eenh));

        Excl = EP * Aant;
        ui->tb_PrKo->setText(QString("%1").arg(Excl, 0, 'f', 2));

        int BTWCode = ui->cbxBTW->model()->data( ui->cbxBTW->model()->index(ui->cbxBTW->currentIndex(), 0 )).toInt();
        BtwP = BTWTarieven::getBTWPercentage(BTWCode);
        ll->setBtwCode(BTWCode);
        ui->tb_BTW_P->setText(QString("%1").arg(BtwP, 0, 'f', 2));

        BtwB = Excl *(BtwP / 100);
        ui->tb_BTW_B->setText(QString("%1").arg(BtwB, 0, 'f', 2));

        LP = Excl * (1 + BtwP/100);
        ui->tb_LP->setText(QString("%1").arg(LP, 0, 'f', 2));

        // Verkoop
        ui->tb_code_vk->setText(ui->tbArtikelCode->text());
        ui->tb_omschr_vk->setText(ui->tbArtikelNaam->text());

        EP = art->getVerkoopPrijs();
        ui->tb_EP_vk->setText( QString("%1").arg(EP, 0, 'f', 2) );

        Aant = ui->tbHoeveelheid->text().toDouble();
        ui->tb_Hoeveel_vk->setText(QString("%1").arg(Aant, 0, 'f', 2));

        eenh = art->getEenheidVerkoop();
        ui->tb_Eenh_vk->setText(ComEenheden::getComEenheidsCode(eenh));

        Excl = EP * Aant;
        ui->tb_PrKo_vk->setText(QString("%1").arg(Excl, 0, 'f', 2));

        BtwP = BTWTarieven::getBTWPercentage(art->getBTWAankoop());
        ui->tb_BTW_P_vk->setText(QString("%1").arg(BtwP, 0, 'f', 2));

        BtwB = Excl *(BtwP / 100);
        ui->tb_BTW_B_vk->setText(QString("%1").arg(BtwB, 0, 'f', 2));

        LP = Excl * (1 + BtwP/100);
        ui->tb_LP_vk->setText(QString("%1").arg(LP, 0, 'f', 2));

        ui->tbGewensteMarge->setText( QString("%1").arg(art->getMinWinstfactor(), 0, 'f', 2));
        double winst = art->getVerkoopPrijs() / ll->getEenheidsprijs();
        double prijs = ll->getEenheidsprijs() * art->getMinWinstfactor();
        ui->tbGewenstePrijs->setText(QString("%1").arg(prijs, 0, 'f', 2));
        ui->tbHuidigeMarge->setText(QString("%1").arg(winst, 0, 'f', 2));
    }
}

void LeveringenRegel::FillFields()
{
    LeverancierCodes* lc = new LeverancierCodes(ll->getArt_ID(), lh->getLeverancier_ID());

    ui->tbLevArtikelCode->setText(lc->getLev_Ref());
    ui->tbLevArtikelNaam->setText(lc->getLev_Omschr());
    ui->tbArtikelCode->setText(ll->getArtikelCode());
    ui->tbArtikelNaam->setText(ll->getArtikelOmschrijving());
    ui->tbEenheidsprijs->setText(QString("%1").arg(ll->getEenheidsprijs(), 0, 'f', 2));
    ui->tbHoeveelheid->setText(QString("%1").arg(ll->getAantal(), 0, 'f', 2));

    int BTWCode = ll->getBtwCode();
    int EenheidsID = ll->getEenheid();
    ui->cbxBTW->setCurrentIndex(
                (BTWCode == 0 ? 0 :
                ui->cbxBTW->model()->match(
                ui->cbxBTW->model()->index(0, 0),
                Qt::DisplayRole,
                QVariant::fromValue(BTWCode),
                -1,
                Qt::MatchFixedString)[0].row()));

    ui->cbxEenheid->setCurrentIndex(
                (EenheidsID == 0 ? 0 :
                ui->cbxEenheid->model()->match(
                ui->cbxEenheid->model()->index(0, 0),
                Qt::DisplayRole,
                QVariant::fromValue(EenheidsID),
                -1,
                Qt::MatchFixedString)[0].row()));

    Bereken();
}

void LeveringenRegel::on_btnAnnuleren_clicked()
{
    this->close();
}

void LeveringenRegel::on_tbLevArtikelCode_editingFinished()
{
    Bereken();
}

void LeveringenRegel::on_tbLevArtikelNaam_editingFinished()
{
    Bereken();
}

void LeveringenRegel::on_tbArtikelCode_editingFinished()
{
    Bereken();
}

void LeveringenRegel::on_tbEenheidsprijs_editingFinished()
{
    Bereken();
}

void LeveringenRegel::on_tbHoeveelheid_editingFinished()
{
    Bereken();
}

void LeveringenRegel::on_cbxBTW_currentIndexChanged(int index)
{
    Bereken();
}

void LeveringenRegel::on_cbxEenheid_currentIndexChanged(int index)
{
    Bereken();
}

void LeveringenRegel::on_tbArtikelnummer_editingFinished()
{
    QString code;
    code = ui->tbArtikelnummer->text().remove(char('.'));
    if (code != "000000")
    {
        on_btnZoek_Art_clicked();
    }
}

void LeveringenRegel::on_btnOvernemen_clicked()
{
    ReadFields();
    ll->save();
    this->close();
}

void LeveringenRegel::ReadFields()
{
    ll->setLeveringHeader_ID(lh->getLeveringenHeader_ID());
    ll->setLevArt_ID(CurrentLeArtID);
    ll->setArtikelCode(art->getCode());
    ll->setArtikelOmschrijving(art->getBenaming());
    ll->setArt_ID(art->getArtikel_ID());
    //ll->setEenheidsprijs();
    //ll->setOpmerking();
}

void LeveringenRegel::on_cbxProduct_currentIndexChanged(int index)
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

void LeveringenRegel::on_cbxSoort_currentIndexChanged(int index)
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

void LeveringenRegel::on_cbxDetail_currentIndexChanged(int index)
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

void LeveringenRegel::on_cbxSpecificatie_currentIndexChanged(int index)
{
    QString artnr = ui->tbArtikelnummer->text();
    int _spec_id = ui->cbxSpecificatie->model()->data( ui->cbxSpecificatie->model()->index(index, 0 )).toInt();
    CurSpec_ID = _spec_id;
    // Aanpassen van het artikel nummer
    Specificaties spec(_spec_id);
    artnr = artnr.replace(7,2,spec.getSpecificatieCode());
    ui->tbArtikelnummer->setText(artnr);
}

void LeveringenRegel::on_btnWis_Art_clicked()
{
    ClearArtikelFields();
}

void LeveringenRegel::on_btnWissen_clicked()
{
    if (ll->getLeveringLine_ID() != 0)
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
            ll->wis();
            this->close();
        }
    }
}

void LeveringenRegel::on_btnPrijsAanpassen_clicked()
{
    // background-color: rgb(245, 241, 241);
    vorigeVKP = art->getVerkoopPrijs();
    vorigeMarge = art->getMinWinstfactor();
    ui->tbGewenstePrijs->setStyleSheet("");
    ui->tbGewenstePrijs->setReadOnly(false);
    ui->tbGewensteMarge->setStyleSheet("");
    ui->tbGewensteMarge->setReadOnly(false);
    ui->btnPrijsOvernemn->setVisible(true);
    ui->btnPrijsAanpassen->setVisible(false);
    ui->btnPrijsOpslaan->setVisible(true);
    ui->btnPrijsAnnuleren->setVisible(true);
    ui->btnMargeOvernemen->setVisible(true);
}

void LeveringenRegel::on_btnPrijsOpslaan_clicked()
{
    // background-color: rgb(245, 241, 241);
    ui->tbGewenstePrijs->setStyleSheet("background-color: rgb(245, 241, 241);");
    ui->tbGewenstePrijs->setReadOnly(true);
    ui->tbGewensteMarge->setStyleSheet("background-color: rgb(245, 241, 241);");
    ui->tbGewensteMarge->setReadOnly(true);
    ui->btnPrijsOvernemn->setVisible(false);
    ui->btnPrijsAanpassen->setVisible(true);
    ui->btnPrijsOpslaan->setVisible(false);
    ui->btnPrijsAnnuleren->setVisible(false);
    ui->btnMargeOvernemen->setVisible(false);
    if (qFabs(art->getVerkoopPrijs() - vorigeVKP) >= 0.02)
    {
        art->setPrikkerGewenst(true);
        art->setPrikkerAfgedrukt(false);
    }
    art->save();
}

void LeveringenRegel::on_btnPrijsOvernemn_clicked()
{
    art->setVerkoopPrijs(ui->tbGewenstePrijs->text().toDouble());
    Bereken();
}

void LeveringenRegel::on_tbGewenstePrijs_editingFinished()
{
    bool validate;
    double np = ui->tbGewenstePrijs->text().toDouble(&validate);
    if(!validate)
    {
        QMessageBox msgBox;
        msgBox.setText("<strong>Geldig getal ingeven !</strong>");
        msgBox.setInformativeText("Foute invoer");
        msgBox.setStandardButtons(QMessageBox::Cancel);
        msgBox.setDefaultButton(QMessageBox::Cancel);
        msgBox.setIcon(QMessageBox::Warning);
        msgBox.setWindowTitle("Opgepast !");
        QSpacerItem *hs = new QSpacerItem(400, 0, QSizePolicy::Minimum, QSizePolicy::Expanding);
        QGridLayout *gl = (QGridLayout*)msgBox.layout();
        gl->addItem(hs, gl->rowCount(), 0, 1, gl->columnCount());
        msgBox.exec();
        ui->tbGewenstePrijs->setFocus();
    }
    else
    {
        art->setVerkoopPrijs(np);
        Bereken();
    }
}

void LeveringenRegel::on_btnPrijsAnnuleren_clicked()
{
    art->setVerkoopPrijs(vorigeVKP);
    art->setMinWinstfactor(vorigeMarge);
    Bereken();
}

void LeveringenRegel::on_btnMargeOvernemen_clicked()
{
    art->setMinWinstfactor(ui->tbHuidigeMarge->text().toDouble());
    Bereken();
}

void LeveringenRegel::on_tbGewensteMarge_editingFinished()
{
    bool validate;
    double nm = ui->tbGewensteMarge->text().toDouble(&validate);
    if(!validate)
    {
        QMessageBox msgBox;
        msgBox.setText("<strong>Geldig getal ingeven !</strong>");
        msgBox.setInformativeText("Foute invoer");
        msgBox.setStandardButtons(QMessageBox::Cancel);
        msgBox.setDefaultButton(QMessageBox::Cancel);
        msgBox.setIcon(QMessageBox::Warning);
        msgBox.setWindowTitle("Opgepast !");
        QSpacerItem *hs = new QSpacerItem(400, 0, QSizePolicy::Minimum, QSizePolicy::Expanding);
        QGridLayout *gl = (QGridLayout*)msgBox.layout();
        gl->addItem(hs, gl->rowCount(), 0, 1, gl->columnCount());
        msgBox.exec();
        ui->tbGewensteMarge->setFocus();
    }
    else
    {
        art->setMinWinstfactor(nm);
        Bereken();
    }
}
