#include "artikelnummerbeheer.h"
#include "ui_artikelnummerbeheer.h"
#include "addproduct.h"
#include "addsoort.h"
#include "producten.h"
#include "allergenen.h"
#include "addspecificatie.h"
#include "addeenheid.h"
#include "addingredienten.h"
#include "selectallergenen.h"
#include "addconcurentprijs.h"
#include "prijzenconcurentie.h"
#include "ingredient_artikel.h"
#include "berekenbtw.h"
#include "../CommonObjects/addbtwtarief.h"

#include <QMessageBox>
#include <QSpacerItem>
#include <QGridLayout>
#include <QBuffer>
#include <QStandardItem>
#include <QStandardItemModel>
#include <QSqlRecord>
#include <QSqlField>


ArtikelnummerBeheer::ArtikelnummerBeheer(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ArtikelnummerBeheer)
{
    ui->setupUi(this);

    CurPrd_ID = 0;

    prd_model = new QSqlQueryModel();
    Producten::getProductenKeuze(prd_model);
    ui->cbxProduct->setModel(prd_model);
    ui->cbxProduct->setModelColumn(1);

    FillBTWVerkoopKeuze();
    FillBTWAankoopKeuze();
    FillEenheidAankoopKeuze();
    FillEenheidVerkoopKeuze();
    ClearFields();
    BlockKeuze(false);

    ui->actionFind->setEnabled(true);
    ui->actionNew->setEnabled(false);
    ui->actionAanpassen->setEnabled(false);
    ui->actionSave->setEnabled(false);
    ui->actionAfsluiten->setEnabled(true);
    ui->btnAllergenen->setEnabled(false);
    ui->btnIngredienten->setEnabled(false);
    ui->btnConcurentie->setEnabled(false);

    ui->btnCalcVKP->setEnabled(false);
    ui->btnCalcPromo->setEnabled(false);

    ui->btnWinstControle->setEnabled(false);

    ui->tbArtikelnummer->selectAll();
    ui->tbArtikelnummer->setFocus();
}

void ArtikelnummerBeheer::ClearFields()
{
    ui->tbBenaming->setText("");                                    ui->tbBenaming->setEnabled(false);
    ui->tbOmschrijving->setText("");                                ui->tbOmschrijving->setEnabled(false);
    ui->tbBarcode->setText("");                                     ui->tbBarcode->setEnabled(false);
    ui->tbExtPLU->setText("");                                      ui->tbExtPLU->setEnabled(false);
    ui->tbRFI->setText("");                                         ui->tbRFI->setEnabled(false);
    ui->tbExtraCode->setText("");                                   ui->tbExtraCode->setEnabled(false);

    ui->btnAfbeelding->setEnabled(false);

    ui->cbxEenheidVerkoop->setCurrentIndex(0);                      ui->cbxEenheidVerkoop->setEnabled(false);
    ui->cbxBTWVerkoop->setCurrentIndex(
                (BTWTarieven::getDefaultBTW() == 0 ? 0 :
                ui->cbxBTWVerkoop->model()->match(
                ui->cbxBTWVerkoop->model()->index(0, 0),
                Qt::DisplayRole,
                QVariant::fromValue(BTWTarieven::getDefaultBTW()),
                -1,
                Qt::MatchFixedString)[0].row()));
                                                                    ui->cbxBTWVerkoop->setEnabled(false);

    ui->tbVerkoopprijs->setText("");                                ui->tbVerkoopprijs->setEnabled(false);
    ui->tbStatVerkMin->setText("");                                 ui->tbStatVerkMin->setEnabled(false);
    ui->tbStatVerkGem->setText("");                                 ui->tbStatVerkGem->setEnabled(false);
    ui->tbStatVerkMax->setText("");                                 ui->tbStatVerkMax->setEnabled(false);
    ui->tbPromotiePrijs->setText("");                               ui->tbPromotiePrijs->setEnabled(false);
    ui->dtpPromVan->setDate(QDate::currentDate());                  ui->dtpPromVan->setEnabled(false);
    ui->dtpPromTot->setDate(QDate::currentDate());                  ui->dtpPromTot->setEnabled(false);
    ui->dtpLaatstePrijsUpdate->setDate(QDate::currentDate());       ui->dtpLaatstePrijsUpdate->setEnabled(false);

    ui->cbxEenheidAankoop->setCurrentIndex(0);                      ui->cbxEenheidAankoop->setEnabled(false);
    ui->cbxBTWAankoop->setCurrentIndex(
                (BTWTarieven::getDefaultBTW() == 0 ? 0 :
                ui->cbxBTWAankoop->model()->match(
                ui->cbxBTWAankoop->model()->index(0, 0),
                Qt::DisplayRole,
                QVariant::fromValue(BTWTarieven::getDefaultBTW()),
                -1,
                Qt::MatchFixedString)[0].row()));
                                                                    ui->cbxBTWAankoop->setEnabled(false);

    ui->tbLaatsteAankoopprijs->setText("");                         ui->tbLaatsteAankoopprijs->setEnabled(false);
    ui->tbStatAankMin->setText("");                                 ui->tbStatAankMin->setEnabled(false);
    ui->tbStatAankGem->setText("");                                 ui->tbStatAankGem->setEnabled(false);
    ui->tbStatAankMax->setText("");                                 ui->tbStatAankMax->setEnabled(false);

    ui->tbHuidigeVoorraad->setText("");                             ui->tbHuidigeVoorraad->setEnabled(false);
    ui->dtpLaatsteAankoop->setDate(QDate::currentDate());           ui->dtpLaatsteAankoop->setEnabled(false);
    ui->dtpLaatsteVerkoop->setDate(QDate::currentDate());           ui->dtpLaatsteVerkoop->setEnabled(false);
    ui->dtpLaatsteBestelling->setDate(QDate::currentDate());        ui->dtpLaatsteBestelling->setEnabled(false);
    ui->tbMinimumVoorraad->setText("");                             ui->tbMinimumVoorraad->setEnabled(false);
    ui->tbCritischeVoorraad->setText("");                           ui->tbCritischeVoorraad->setEnabled(false);
    ui->tbMaximumVoorraad->setText("");                             ui->tbMaximumVoorraad->setEnabled(false);
    ui->tbBesteldeVoorraad->setText("");                            ui->tbBesteldeVoorraad->setEnabled(false);

    ui->tbHoudbaarheid->setText("");                                ui->tbHoudbaarheid->setEnabled(false);
    ui->tbWettelijk->setText("");                                   ui->tbWettelijk->setEnabled(false);
    ui->tbOpmerkingen->setText("");                                 ui->tbOpmerkingen->setEnabled(false);
    ui->tbTemperatuur->setText("");                                 ui->tbTemperatuur->setEnabled(false);
    ui->tbVochtigheid->setText("");                                 ui->tbVochtigheid->setEnabled(false);

    ui->dtpActiefVan->setDate(QDate::currentDate());                ui->dtpActiefVan->setEnabled(false);
    ui->dtpActiefTot->setDate(QDate::currentDate().addYears(100));  ui->dtpActiefTot->setEnabled(false);

    ui->cbPrikkerAfgedrukt->setChecked(false);                      ui->cbPrikkerAfgedrukt->setEnabled(false);
    ui->cbPrikkergewenst->setChecked(false);                        ui->cbPrikkergewenst->setEnabled(false);
    ui->tbincl->setText("0");
    ui->tbMinWinstfactor->setText("");                              ui->tbMinWinstfactor->setEnabled(false);

    ui->dtpLaatstePrijscontrole->setDate(QDate::currentDate());     ui->dtpLaatstePrijscontrole->setEnabled(false);
}

void ArtikelnummerBeheer::FillEenheidAankoopKeuze()
{
    Eenha_model = new QSqlQueryModel();
    ComEenheden::getComEenhedenKeuze(Eenha_model);
    ui->cbxEenheidAankoop->setModel(Eenha_model);
    ui->cbxEenheidAankoop->setModelColumn(1);
}

void ArtikelnummerBeheer::FillEenheidVerkoopKeuze()
{
    Eenhv_model = new QSqlQueryModel();
    ComEenheden::getComEenhedenKeuze(Eenhv_model);
    ui->cbxEenheidVerkoop->setModel(Eenhv_model);
    ui->cbxEenheidVerkoop->setModelColumn(1);
}


void ArtikelnummerBeheer::FillBTWAankoopKeuze()
{
    BTWa_model = new QSqlQueryModel();
    BTWTarieven::getBTWTarievenKeuze(BTWa_model);
    ui->cbxBTWAankoop->setModel(BTWa_model);
    ui->cbxBTWAankoop->setModelColumn(1);
}

void ArtikelnummerBeheer::FillBTWVerkoopKeuze()
{
    BTWv_model = new QSqlQueryModel();
    BTWTarieven::getBTWTarievenKeuze(BTWv_model);
    ui->cbxBTWVerkoop->setModel(BTWv_model);
    ui->cbxBTWVerkoop->setModelColumn(1);
}

void ArtikelnummerBeheer::FillSoortkeuze()
{
    srt_model = new QSqlQueryModel();
    Soorten::getSoortenKeuze(srt_model, CurPrd_ID);
    ui->cbxSoort->setModel((srt_model));
    ui->cbxSoort->setModelColumn(1);
}

void ArtikelnummerBeheer::FillDetailKeuze()
{
    det_model = new QSqlQueryModel();
    Details::getDetailKeuze(det_model, CurPrd_ID, CurSrt_ID);
    ui->cbxDetail->setModel(det_model);
    ui->cbxDetail->setModelColumn(1);

}

void ArtikelnummerBeheer::FillSpecificatieKeuze()
{
    spec_model = new QSqlQueryModel();
    Specificaties::getSpecificatieKeuze(spec_model, CurPrd_ID, CurSrt_ID, CurDet_ID);
    ui->cbxSpecificatie->setModel(spec_model);
    ui->cbxSpecificatie->setModelColumn(1);
}

ArtikelnummerBeheer::~ArtikelnummerBeheer()
{
    delete ui;
    delete prd_model;
}

void ArtikelnummerBeheer::on_actionAfsluiten_triggered()
{
    this->close();
}

void ArtikelnummerBeheer::on_btnMaintProduct_clicked()
{
    AddProduct *prd_win;
    prd_win = new AddProduct();
    prd_win->exec();

    // Onthoud huidige keuze
    int _prod_id = ui->cbxProduct->model()->data( ui->cbxProduct->model()->index(ui->cbxProduct->currentIndex(), 0 )).toInt();

    // Lees de keuzelijst opnieuw in (met eventuele aanpassingen
    Producten::getProductenKeuze(prd_model);
    ui->cbxProduct->setModel(prd_model);
    ui->cbxProduct->setModelColumn(1);

    // Zet de huidige keuze op de eerder onthouden keuze
    ui->cbxProduct->setCurrentIndex((_prod_id == 0 ? 0 :
                ui->cbxProduct->model()->match(
                ui->cbxProduct->model()->index(0, 0),
                Qt::DisplayRole,
                QVariant::fromValue(_prod_id),
                -1,
                Qt::MatchFixedString)[0].row()));


    delete prd_win;
}

void ArtikelnummerBeheer::on_btnMaintSoort_clicked()
{
    // Soort-beheer openen voor een gekozen Product
    AddSoort *srt_win = new AddSoort();
    srt_win->setProductID(ui->cbxProduct->model()->data( ui->cbxProduct->model()->index(ui->cbxProduct->currentIndex(), 0 )).toInt());
    srt_win->setWindowTitle(QString("Soorten voor product %1").arg(ui->cbxProduct->currentText()));
    srt_win->exec();

    // Onthoud de huidige keuze
    int _srt_id = ui->cbxSoort->model()->data( ui->cbxSoort->model()->index(ui->cbxSoort->currentIndex(), 0 )).toInt();
    // Lees de keuzelijst opnieuw in
    FillSoortkeuze();
    // Stel de keuze weer in op de eerder onthouden keuze
    ui->cbxSoort->setCurrentIndex((_srt_id == 0 ? 0 :
                ui->cbxSoort->model()->match(
                ui->cbxSoort->model()->index(0, 0),
                Qt::DisplayRole,
                QVariant::fromValue(_srt_id),
                -1,
                Qt::MatchFixedString)[0].row()));

    delete srt_win;
}

void ArtikelnummerBeheer::on_btnMaintDetail_clicked()
{
    // Soort-beheer openen voor een gekozen Product
    AddDetail *det_win = new AddDetail();
    det_win->setIDs(ui->cbxProduct->model()->data( ui->cbxProduct->model()->index(ui->cbxProduct->currentIndex(), 0 )).toInt(),
                    ui->cbxSoort->model()->data( ui->cbxSoort->model()->index(ui->cbxSoort->currentIndex(), 0 )).toInt());
    det_win->setWindowTitle(QString("Details voor product %1 - %2").arg(ui->cbxProduct->currentText(),ui->cbxSoort->currentText()));
    det_win->exec();

    // Onthoud de huidige keuze
    int _det_id = ui->cbxDetail->model()->data( ui->cbxDetail->model()->index(ui->cbxDetail->currentIndex(), 0 )).toInt();
    // Lees de keuzelijst opnieuw in
    FillDetailKeuze();
    // Stel de keuze weer in op de eerder onthouden keuze
    ui->cbxDetail->setCurrentIndex((_det_id == 0 ? 0 :
                ui->cbxDetail->model()->match(
                ui->cbxDetail->model()->index(0, 0),
                Qt::DisplayRole,
                QVariant::fromValue(_det_id),
                -1,
                Qt::MatchFixedString)[0].row()));

    delete det_win;

}

void ArtikelnummerBeheer::on_btnMaintSpecificatie_clicked()
{
    AddSpecificatie *spe_win = new AddSpecificatie();
    spe_win->setIDs(ui->cbxProduct->model()->data( ui->cbxProduct->model()->index(ui->cbxProduct->currentIndex(), 0 )).toInt(),
                    ui->cbxSoort->model()->data( ui->cbxSoort->model()->index(ui->cbxSoort->currentIndex(), 0 )).toInt(),
                    ui->cbxDetail->model()->data( ui->cbxDetail->model()->index(ui->cbxDetail->currentIndex(), 0 )).toInt());

    spe_win->setWindowTitle(QString("%1 - %2 - %3").arg(ui->cbxProduct->currentText(),
                                                                             ui->cbxSoort->currentText(),
                                                                             ui->cbxDetail->currentText()));
    spe_win->exec();

    // Onthoud de huidige keuze
    int _spe_id = ui->cbxSpecificatie->model()->data( ui->cbxSpecificatie->model()->index(ui->cbxSpecificatie->currentIndex(), 0 )).toInt();
    // Lees de keuzelijst opnieuw in
    FillSpecificatieKeuze();
    // Stel de keuze weer in op de eerder onthouden keuze
    ui->cbxSpecificatie->setCurrentIndex((_spe_id == 0 ? 0 :
                ui->cbxSpecificatie->model()->match(
                ui->cbxSpecificatie->model()->index(0, 0),
                Qt::DisplayRole,
                QVariant::fromValue(_spe_id),
                -1,
                Qt::MatchFixedString)[0].row()));

    delete spe_win;

}

void ArtikelnummerBeheer::on_cbxProduct_currentIndexChanged(int index)
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

void ArtikelnummerBeheer::on_cbxSoort_currentIndexChanged(int index)
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

void ArtikelnummerBeheer::on_cbxDetail_currentIndexChanged(int index)
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

void ArtikelnummerBeheer::on_cbxSpecificatie_currentIndexChanged(int index)
{
    QString artnr = ui->tbArtikelnummer->text();
    int _spec_id = ui->cbxSpecificatie->model()->data( ui->cbxSpecificatie->model()->index(index, 0 )).toInt();
    CurSpec_ID = _spec_id;
    // Aanpassen van het artikel nummer
    Specificaties spec(_spec_id);
    artnr = artnr.replace(7,2,spec.getSpecificatieCode());
    ui->tbArtikelnummer->setText(artnr);
}

void ArtikelnummerBeheer::on_btnMaintEenheid_clicked()
{
    AddEenheid *ce_win = new AddEenheid();
    ce_win->exec();

    // Onthoud de huidige keuze
    int _id = ui->cbxEenheidAankoop->model()->data( ui->cbxEenheidAankoop->model()->index(ui->cbxEenheidAankoop->currentIndex(), 0 )).toInt();
    // Lees de keuzelijst opnieuw in
    FillEenheidAankoopKeuze();
    // Stel de keuze weer in op de eerder onthouden keuze
    ui->cbxEenheidAankoop->setCurrentIndex((_id == 0 ? 0 :
                ui->cbxEenheidAankoop->model()->match(
                ui->cbxEenheidAankoop->model()->index(0, 0),
                Qt::DisplayRole,
                QVariant::fromValue(_id),
                -1,
                Qt::MatchFixedString)[0].row()));

    _id = ui->cbxEenheidVerkoop->model()->data( ui->cbxEenheidVerkoop->model()->index(ui->cbxEenheidVerkoop->currentIndex(), 0 )).toInt();
    // Lees de keuzelijst opnieuw in
    FillEenheidVerkoopKeuze();
    // Stel de keuze weer in op de eerder onthouden keuze
    ui->cbxEenheidVerkoop->setCurrentIndex((_id == 0 ? 0 :
                ui->cbxEenheidVerkoop->model()->match(
                ui->cbxEenheidVerkoop->model()->index(0, 0),
                Qt::DisplayRole,
                QVariant::fromValue(_id),
                -1,
                Qt::MatchFixedString)[0].row()));


    delete ce_win;

}

void ArtikelnummerBeheer::on_btnMaintBTWtarief_clicked()
{
    AddBTWTarief *BTW_win = new AddBTWTarief();
    BTW_win->exec();

    // Onthoud de huidige keuze
    int _id = ui->cbxBTWAankoop->model()->data( ui->cbxBTWAankoop->model()->index(ui->cbxBTWAankoop->currentIndex(), 0 )).toInt();
    // Lees de keuzelijst opnieuw in
    FillBTWAankoopKeuze();
    // Stel de keuze weer in op de eerder onthouden keuze
    ui->cbxBTWAankoop->setCurrentIndex((_id == 0 ? 0 :
                ui->cbxBTWAankoop->model()->match(
                ui->cbxBTWAankoop->model()->index(0, 0),
                Qt::DisplayRole,
                QVariant::fromValue(_id),
                -1,
                Qt::MatchFixedString)[0].row()));

    _id = ui->cbxBTWVerkoop->model()->data( ui->cbxBTWVerkoop->model()->index(ui->cbxBTWVerkoop->currentIndex(), 0 )).toInt();

    // Lees de keuzelijst opnieuw in
    FillBTWVerkoopKeuze();
    // Stel de keuze weer in op de eerder onthouden keuze
    ui->cbxBTWVerkoop->setCurrentIndex((_id == 0 ? 0 :
                ui->cbxBTWVerkoop->model()->match(
                ui->cbxBTWVerkoop->model()->index(0, 0),
                Qt::DisplayRole,
                QVariant::fromValue(_id),
                -1,
                Qt::MatchFixedString)[0].row()));

    delete BTW_win;
}

void ArtikelnummerBeheer::BlockKeuze(bool block)
{
    ui->cbxProduct->setEnabled(!block);
    ui->btnMaintProduct->setEnabled(!block);
    ui->cbxSoort->setEnabled(!block);
    ui->btnMaintSoort->setEnabled(!block);
    ui->cbxDetail->setEnabled(!block);
    ui->btnMaintDetail->setEnabled(!block);
    ui->cbxSpecificatie->setEnabled(!block);
    ui->btnMaintSpecificatie->setEnabled(!block);
    ui->tbArtikelnummer->setEnabled(!block);
}

void ArtikelnummerBeheer::OpenEditFields(bool open)
{
    ui->tbBenaming->setEnabled(open);
    ui->tbOmschrijving->setEnabled(open);
    ui->tbBarcode->setEnabled(open);
    ui->tbExtPLU->setEnabled(open);
    ui->tbRFI->setEnabled(open);
    ui->tbExtraCode->setEnabled(open);

    ui->cbxEenheidVerkoop->setEnabled(open);

    ui->cbxBTWVerkoop->setEnabled(open);

    ui->tbVerkoopprijs->setEnabled(open);
    ui->tbPromotiePrijs->setEnabled(open);
    ui->dtpPromVan->setEnabled(open);
    ui->dtpPromTot->setEnabled(open);

    ui->cbxEenheidAankoop->setEnabled(open);

    ui->cbxBTWAankoop->setEnabled(open);

    ui->tbMinimumVoorraad->setEnabled(open);
    ui->tbCritischeVoorraad->setEnabled(open);
    ui->tbMaximumVoorraad->setEnabled(open);

    ui->tbHoudbaarheid->setEnabled(open);
    ui->tbWettelijk->setEnabled(open);
    ui->tbOpmerkingen->setEnabled(open);
    ui->tbTemperatuur->setEnabled(open);
    ui->tbVochtigheid->setEnabled(open);

    ui->dtpActiefVan->setEnabled(open);
    ui->dtpActiefTot->setEnabled(open);

    ui->tvAllergenen->setEnabled(open);
    ui->tvConcurentie->setEnabled(open);
    ui->tvIngredienten->setEnabled(open);

    ui->cbPrikkerAfgedrukt->setEnabled(open);
    ui->cbPrikkergewenst->setEnabled(open);

    ui->tbMinWinstfactor->setEnabled(open);


}

void ArtikelnummerBeheer::SetEditMode()
{
    ui->actionFind->setEnabled(false);
    ui->actionNew->setEnabled(false);
    ui->actionAanpassen->setEnabled(false);
    ui->actionSave->setEnabled(true);
    ui->actionAfsluiten->setEnabled(true);
    ui->btnAfbeelding->setEnabled(true);
    ui->btnAllergenen->setEnabled(true);
    ui->btnConcurentie->setEnabled(true);
    ui->btnIngredienten->setEnabled(true);

    ui->btnCalcVKP->setEnabled(true);
    ui->btnCalcPromo->setEnabled(true);


}


void ArtikelnummerBeheer::SetKijkMode()
{
    ui->actionFind->setEnabled(true);
    ui->actionNew->setEnabled(false);
    ui->actionAanpassen->setEnabled(true);
    ui->actionSave->setEnabled(false);
    ui->actionAfsluiten->setEnabled(true);
    ui->btnAfbeelding->setEnabled(false);
    ui->btnAllergenen->setEnabled(false);
    ui->btnConcurentie->setEnabled(false);
    ui->btnIngredienten->setEnabled(false);

    ui->btnCalcVKP->setEnabled(false);
    ui->btnCalcPromo->setEnabled(false);


}

void ArtikelnummerBeheer::FillFields()
{
    QPixmap image;

    ui->tbArtikelnummer->setText(art->getCode());
    ui->tbBenaming->setText(art->getBenaming());
    ui->tbOmschrijving->setText(art->getOmschrijving());
    ui->tbBarcode->setText(art->getBarcode());
    ui->tbExtPLU->setText(art->getExtPlu());
    ui->tbRFI->setText(art->getRFIcode());
    ui->tbExtraCode->setText(art->getExtraCode());

    image.loadFromData(art->getAfbeelding(), "PNG");
    ui->lbImg->setPixmap(image);


    ui->cbxEenheidVerkoop->setCurrentIndex(
                (art->getEenheidVerkoop() == 0 ? 0 :
                ui->cbxEenheidVerkoop->model()->match(
                ui->cbxEenheidVerkoop->model()->index(0, 0),
                Qt::DisplayRole,
                QVariant::fromValue(art->getEenheidVerkoop()),
                -1,
                Qt::MatchFixedString)[0].row()));

    ui->cbxBTWVerkoop->setCurrentIndex(
                (art->getBTWVerkoop() == 0 ? 0 :
                ui->cbxBTWVerkoop->model()->match(
                ui->cbxBTWVerkoop->model()->index(0, 0),
                Qt::DisplayRole,
                QVariant::fromValue(art->getBTWVerkoop()),
                -1,
                Qt::MatchFixedString)[0].row()));


    ui->tbVerkoopprijs->setText(QString::number(art->getVerkoopPrijs()));
    ui->tbStatVerkMin->setText(QString::number(art->getVP_Min()));
    ui->tbStatVerkGem->setText(QString::number(art->getVP_Mean()));
    ui->tbStatVerkMax->setText(QString::number(art->getVP_Max()));
    ui->dtpLaatstePrijsUpdate->setDate(art->getLastPriceUpdate());
    ui->tbPromotiePrijs->setText(QString::number(art->getPromoPrijs()));
    ui->dtpPromVan->setDate(art->getPromoVan());
    ui->dtpPromTot->setDate(art->getPromoTot());


    ui->cbxEenheidAankoop->setCurrentIndex(
                (art->getEenheidAankoop() == 0 ? 0 :
                ui->cbxEenheidAankoop->model()->match(
                ui->cbxEenheidAankoop->model()->index(0, 0),
                Qt::DisplayRole,
                QVariant::fromValue(art->getEenheidAankoop()),
                -1,
                Qt::MatchFixedString)[0].row()));

    ui->cbxBTWAankoop->setCurrentIndex(
                (art->getBTWVerkoop() == 0 ? 0 :
                ui->cbxBTWAankoop->model()->match(
                ui->cbxBTWAankoop->model()->index(0, 0),
                Qt::DisplayRole,
                QVariant::fromValue(art->getBTWAankoop()),
                -1,
                Qt::MatchFixedString)[0].row()));


    // TODO ui->tbLaatsteAankoopprijs->setText("");
    // TODO ui->tbStatAankMin->setText("");
    // TODO ui->tbStatAankGem->setText("");
    // TODO ui->tbStatAankMax->setText("");

    // TODO ui->tbHuidigeVoorraad->setText("");
    // TODO ui->dtpLaatsteAankoop->setDate(QDate::currentDate());
    // TODO ui->dtpLaatsteVerkoop->setDate(QDate::currentDate());
    // TODO ui->dtpLaatsteBestelling->setDate(QDate::currentDate());
    ui->tbMinimumVoorraad->setText(QString("%1").arg(art->getMinVoorraad()));
    ui->tbCritischeVoorraad->setText(QString("%1").arg(art->getCriticalVoorraad()));
    ui->tbMaximumVoorraad->setText(QString("%1").arg(art->getMaxVoorraad()));
    // TODO ui->tbBesteldeVoorraad->setText("");

    ui->tbHoudbaarheid->setText(QString("%1").arg(art->getHoudbaarheid()));
    ui->tbWettelijk->setText(art->getWettelijk());
    ui->tbOpmerkingen->setText(art->getOpmerking());
    ui->tbTemperatuur->setText(QString("%1").arg(art->getBewaarTemp()));
    ui->tbVochtigheid->setText(QString("%1").arg(art->getBewaarVocht()));

    ui->dtpActiefVan->setDate(art->getActiefVan());
    ui->dtpActiefTot->setDate(art->getActiefTot());

    ui->cbPrikkerAfgedrukt->setChecked(art->getPrikkerAfgedrukt());
    ui->cbPrikkergewenst->setChecked(art->getPrikkerGewenst());

    ui->tbincl->setText(QString("%1").arg(art->getVerkoopPrijs() * (1+BTWTarieven::getBTWPercentage( art->getBTWAankoop())/100), 9, 'f', 2));

    ui->tbMinWinstfactor->setText(QString::number(art->getMinWinstfactor()));
    ui->dtpLaatstePrijscontrole->setDate(art->getLaatstePrijscontrole());

    ui->btnWinstControle->setEnabled(true);

    FillAllergenen();
    FillConcurentPrijzen();
    FillIngredienten();
}

void ArtikelnummerBeheer::FillIngredienten()
{
    QSqlQueryModel *tv_model = new QSqlQueryModel();
    Ingredient_Artikel::getIngredientenPerArtikel(tv_model, art->getArtikel_ID());
    tv_model->setHeaderData(2, Qt::Horizontal, tr("Omschrijveng"));
    tv_model->setHeaderData(3, Qt::Horizontal, tr("Procent"));
    ui->tvIngredienten->setModel(tv_model);

    ui->tvIngredienten->hideColumn(0);
    ui->tvIngredienten->hideColumn(1);

    ui->tvIngredienten->setColumnWidth(2,200);
    ui->tvIngredienten->setColumnWidth(3,80);
    ui->tvIngredienten->verticalHeader()->setDefaultSectionSize(20);
    ui->tvIngredienten->setAlternatingRowColors(true);

}

void ArtikelnummerBeheer::FillConcurentPrijzen()
{
    QSqlQueryModel *tv_model = new QSqlQueryModel();
    PrijzenConcurentie::getPrijzenPerArtikel(tv_model, art->getArtikel_ID());
    tv_model->setHeaderData(2, Qt::Horizontal, tr("Datum"));
    tv_model->setHeaderData(3, Qt::Horizontal, tr("Naam Concurent"));
    tv_model->setHeaderData(4, Qt::Horizontal, tr("Prijs"));

    ui->tvConcurentie->setModel(tv_model);

    ui->tvConcurentie->hideColumn(0);
    ui->tvConcurentie->hideColumn(1);

    ui->tvConcurentie->setColumnWidth(2,60);
    ui->tvConcurentie->setColumnWidth(3,160);
    ui->tvConcurentie->setColumnWidth(4,60);
    ui->tvConcurentie->verticalHeader()->setDefaultSectionSize(20);
    ui->tvConcurentie->setAlternatingRowColors(true);
}

void ArtikelnummerBeheer::FillAllergenen()
{
    QSqlQueryModel *al_model = new QSqlQueryModel();
    art->getAllergenenlijst(al_model);

    al_model->setHeaderData(0, Qt::Horizontal, tr("Aanwezig"));


    //result = tableModel->data(1,2).toString();
    ui->tvAllergenen->setModel(al_model);

    ui->tvAllergenen->setColumnWidth(0,300);
    ui->tvAllergenen->verticalHeader()->setDefaultSectionSize(20);
    ui->tvAllergenen->setAlternatingRowColors(true);
}

void ArtikelnummerBeheer::ReadFields()
{
    QByteArray bytes;
    QBuffer buffer(&bytes);
    bool ok;
    buffer.open(QIODevice::WriteOnly);
    if (!ui->lbImg->pixmap()->isNull())
    {
        ui->lbImg->pixmap()->save(&buffer, "PNG");
    }
    art->setAfbeelding(bytes);
    art->setCode(ui->tbArtikelnummer->text().remove(char('.')));
    art->setBarcode(ui->tbBarcode->text());
    art->setExtPlu(ui->tbExtPLU->text());
    art->setRFIcode(ui->tbRFI->text());
    art->setExtraCode(ui->tbExtraCode->text());
    art->setBenaming(ui->tbBenaming->text());
    art->setOmschrijving(ui->tbOmschrijving->text());

    art->setEenheidVerkoop(
                ui->cbxEenheidVerkoop->model()->data( ui->cbxEenheidVerkoop->model()->
                index(ui->cbxEenheidVerkoop->currentIndex(), 0 )).toInt()
                );
    art->setBTWVerkoop(
                ui->cbxBTWVerkoop->model()->data( ui->cbxBTWVerkoop->model()->
                index(ui->cbxBTWVerkoop->currentIndex(), 0 )).toInt()
                );
    art->setVerkoopPrijs(ui->tbVerkoopprijs->text().toDouble());
    art->setPromoPrijs(ui->tbPromotiePrijs->text().toDouble());
    art->setPromoVan(ui->dtpPromVan->date());
    art->setPromoTot(ui->dtpPromTot->date());

    art->setEenheidAankoop(
                ui->cbxEenheidAankoop->model()->data( ui->cbxEenheidAankoop->model()->
                index(ui->cbxEenheidAankoop->currentIndex(), 0 )).toInt()
                );
    art->setBTWAankoop(
                ui->cbxBTWAankoop->model()->data( ui->cbxBTWAankoop->model()->
                index(ui->cbxBTWAankoop->currentIndex(), 0 )).toInt()
                );
    art->setMinVoorraad(ui->tbMinimumVoorraad->text().toDouble());
    art->setMaxVoorraad(ui->tbMaximumVoorraad->text().toDouble());
    art->setCriticalVoorraad(ui->tbCritischeVoorraad->text().toDouble());
    art->setHoudbaarheid(ui->tbHoudbaarheid->text().toInt());
    art->setWettelijk(ui->tbWettelijk->text());
    art->setOpmerking(ui->tbOpmerkingen->text());
    art->setBewaarTemp(ui->tbTemperatuur->text().toDouble());
    art->setBewaarVocht(ui->tbVochtigheid->text().toDouble());
    art->setActiefVan(ui->dtpActiefVan->date());
    art->setActiefTot(ui->dtpActiefTot->date());
    art->setPrikkerAfgedrukt(ui->cbPrikkerAfgedrukt->isChecked());
    art->setPrikkerGewenst(ui->cbPrikkergewenst->isChecked());
    art->setMinWinstfactor(ui->tbMinWinstfactor->text().toDouble());

}

void ArtikelnummerBeheer::on_actionFind_triggered()
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
        msgBox.setInformativeText("Artikel onbekend, wil je het aanmaken");
        msgBox.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
        msgBox.setDefaultButton(QMessageBox::No);
        msgBox.setIcon(QMessageBox::Warning);
        msgBox.setWindowTitle("Opgepast !");
        //msgBox.setStyleSheet("min-width: 150px;");
        QSpacerItem *hs = new QSpacerItem(400, 0, QSizePolicy::Minimum, QSizePolicy::Expanding);
        QGridLayout *gl = (QGridLayout*)msgBox.layout();
        gl->addItem(hs, gl->rowCount(), 0, 1, gl->columnCount());
        int ret = msgBox.exec();
        if (ret == QMessageBox::Yes)
        {
            BlockKeuze(true);
            art = new Artikelen();
            art->setCode(code);
            FillFields();
            OpenEditFields(true);
            SetEditMode();
        }
        else
        {
            ClearFields();
        }
    }
    else
    {
        BlockKeuze(false);
        art = new Artikelen(id);
        FillFields();
        OpenEditFields(false);
        SetKijkMode();
    }
}




void ArtikelnummerBeheer::on_actionSave_triggered()
{
    ReadFields();
    art->save();
    ui->dtpLaatstePrijsUpdate->setDate(art->getLastPriceUpdate());
    OpenEditFields(false);
    SetKijkMode();
    BlockKeuze(false);
}

bool ArtikelnummerBeheer::AdjustSamenstelling(QString _code)
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

void ArtikelnummerBeheer::on_tbArtikelnummer_editingFinished()
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
        on_actionFind_triggered();
    }
}

void ArtikelnummerBeheer::MeldGetalError()
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

void ArtikelnummerBeheer::on_tbVerkoopprijs_editingFinished()
{
    double bedrag;
    bool ok;
    bedrag = ui->tbVerkoopprijs->text().toDouble(&ok);
    ui->tbincl->setText(QString("%1").arg(bedrag * (1+BTWTarieven::getBTWPercentage( art->getBTWAankoop())/100), 9, 'f', 2));
    if (!ok)
    {
        MeldGetalError();
        ui->tbVerkoopprijs->setText("0.0");
        ui->tbVerkoopprijs->selectAll();
        ui->tbVerkoopprijs->setFocus();
    }
}

void ArtikelnummerBeheer::on_tbPromotiePrijs_editingFinished()
{
    double bedrag;
    bool ok;
    bedrag = ui->tbPromotiePrijs->text().toDouble(&ok);
    if (!ok)
    {
        MeldGetalError();
        ui->tbPromotiePrijs->setText("0.0");
        ui->tbPromotiePrijs->selectAll();
        ui->tbPromotiePrijs->setFocus();
    }
}

void ArtikelnummerBeheer::on_tbMinimumVoorraad_editingFinished()
{
    double bedrag;
    bool ok;
    bedrag = ui->tbMinimumVoorraad->text().toDouble(&ok);
    if (!ok)
    {
        MeldGetalError();
        ui->tbMinimumVoorraad->setText("0.0");
        ui->tbMinimumVoorraad->selectAll();
        ui->tbMinimumVoorraad->setFocus();
    }
}

void ArtikelnummerBeheer::on_tbCritischeVoorraad_editingFinished()
{
    double bedrag;
    bool ok;
    bedrag = ui->tbCritischeVoorraad->text().toDouble(&ok);
    if (!ok)
    {
        MeldGetalError();
        ui->tbCritischeVoorraad->setText("0.0");
        ui->tbCritischeVoorraad->selectAll();
        ui->tbCritischeVoorraad->setFocus();
    }
}

void ArtikelnummerBeheer::on_tbMaximumVoorraad_editingFinished()
{
    double bedrag;
    bool ok;
    bedrag = ui->tbMaximumVoorraad->text().toDouble(&ok);
    if (!ok)
    {
        MeldGetalError();
        ui->tbMaximumVoorraad->setText("0.0");
        ui->tbMaximumVoorraad->selectAll();
        ui->tbMaximumVoorraad->setFocus();
    }
}

void ArtikelnummerBeheer::on_tbTemperatuur_editingFinished()
{
    double bedrag;
    bool ok;
    bedrag = ui->tbTemperatuur->text().toDouble(&ok);
    if (!ok)
    {
        MeldGetalError();
        ui->tbTemperatuur->setText("0.0");
        ui->tbTemperatuur->selectAll();
        ui->tbTemperatuur->setFocus();
    }
}

void ArtikelnummerBeheer::on_tbVochtigheid_editingFinished()
{
    double bedrag;
    bool ok;
    bedrag = ui->tbVochtigheid->text().toDouble(&ok);
    if (!ok)
    {
        MeldGetalError();
        ui->tbVochtigheid->setText("0.0");
        ui->tbVochtigheid->selectAll();
        ui->tbVochtigheid->setFocus();
    }
}

void ArtikelnummerBeheer::on_tbHoudbaarheid_editingFinished()
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

void ArtikelnummerBeheer::on_actionAanpassen_triggered()
{
    OpenEditFields(true);
    SetEditMode();
    BlockKeuze(true);
}

void ArtikelnummerBeheer::on_btnAllergenen_clicked()
{
    SelectAllergenen *sa = new SelectAllergenen(art->getArtikel_ID());
    sa->exec();
    FillAllergenen();
    delete sa;
}

void ArtikelnummerBeheer::on_btnConcurentie_clicked()
{
    AddConcurentPrijs *co = new AddConcurentPrijs(art->getArtikel_ID());
    co->exec();
    FillConcurentPrijzen();
    delete co;
}

void ArtikelnummerBeheer::on_btnIngredienten_clicked()
{
    AddIngredienten *ing = new AddIngredienten(art->getArtikel_ID());
    ing->exec();
    FillIngredienten();
    delete ing;
}

void ArtikelnummerBeheer::on_btnCalcVKP_clicked()
{
    BerekenBTW calc;
    if (calc.exec() == QDialog::Accepted)
    {
        ui->tbVerkoopprijs->setText( QString::number(calc.Result));
        ui->tbincl->setText(QString("%1").arg(calc.result() * (1+BTWTarieven::getBTWPercentage( art->getBTWAankoop())/100), 9, 'f', 2));
    }
}

void ArtikelnummerBeheer::on_btnCalcPromo_clicked()
{
    BerekenBTW calc;
    if (calc.exec() == QDialog::Accepted)
    {
        ui->tbPromotiePrijs->setText( QString::number(calc.Result));
    }
}

void ArtikelnummerBeheer::on_actionFind_changed()
{
}

void ArtikelnummerBeheer::on_tbMinWinstfactor_editingFinished()
{
    double bedrag;
    bool ok;
    bedrag = ui->tbMinWinstfactor->text().toDouble(&ok);
    if (!ok)
    {
        MeldGetalError();
        ui->tbVerkoopprijs->setText("1.8");
        ui->tbVerkoopprijs->selectAll();
        ui->tbVerkoopprijs->setFocus();
    }

}
