#include "leveringenfiche.h"
#include "ui_leveringenfiche.h"
#include "Bestellingen/leveringenheader.h"
#include "Bestellingen/leveringenline.h"
#include "CommonObjects/postcodes.h"
#include "CommonObjects/landen.h"
#include "Relaties/findrelaties.h"
#include "ArtikelBeheer/leveringenregel.h"


#include <QMessageBox>
#include <QSpacerItem>
#include <QGridLayout>

LeveringenFiche::LeveringenFiche(int _id, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::LeveringenFiche)
{
    ui->setupUi(this);
    if (_id == 0 )
    {
        // Nieuwe fiche
        lh = new LeveringenHeader();
        rel = new Relaties();
        ClearFiche();
    }
    else
    {
        // Bestaande fiche openen
        lh = new LeveringenHeader(_id);
        rel = new Relaties(lh->getLeverancier_ID());
        FillFiche();
    }

}

LeveringenFiche::~LeveringenFiche()
{
    delete ui;
    delete lh;
}

void LeveringenFiche::ClearRelZoekFields()
{
    ui->tbNummer->setText("");
    ui->tbNaam->setText("");
    ui->tbStraat->setText("");
    ui->tbGemeente->setText("");
    ui->tbEMail->setText("");
    ui->tbPostcode->setText("");
    ui->tbBTW_Nummer->setText("");
}

void LeveringenFiche::ClearFiche()
{
    ClearRelZoekFields();
    ui->tbLevRef->setText("");
    ui->tbLevFact->setText("");
    ui->tbORef->setText("");
    ui->tbOFact->setText("");
    ui->tbOpm->setText("");
    ui->dtpDatum->setDate(QDate::currentDate());
}

void LeveringenFiche::FillFiche()
{
    ui->tbNummer->setText( QString("%1").arg(rel->getRelatie_ID()));
    ui->tbNaam->setText(rel->getNaam() + " " + rel->getVoornaam());
    ui->tbStraat->setText(rel->getAdres());
    ui->tbGemeente->setText(Postcodes::getGemeente(rel->getGemeente_ID()));
    ui->tbPostcode->setText(Postcodes::getPocode(rel->getGemeente_ID()));
    ui->tbEMail->setText(rel->getEMail_1());
    ui->tbBTW_Nummer->setText(rel->getBTWNummer());
    ui->tbLevRef->setText(lh->getLeverancierReferentie());
    ui->tbLevFact->setText(lh->getLeverancierFactuur());
    ui->tbORef->setText(lh->getOnzeReferentie());
    ui->tbOFact->setText(lh->getOnzeFactuur());
    ui->tbOpm->setText(lh->getOpmerkingen());
    ui->dtpDatum->setDate(lh->getTijdstip());

    FillRegels();
}

void LeveringenFiche::on_btnWis_Lev_clicked()
{
    ClearRelZoekFields();
}

void LeveringenFiche::on_btnZoek_Lev_clicked()
{
    bool ok;
    int rel_id;
    CurrentRel = lh->getLeverancier_ID();

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
    lh->setLeverancier_ID(CurrentRel);
}

void LeveringenFiche::SafeHeader()
{
    lh->setLeverancierFactuur(ui->tbLevFact->text());
    lh->setLeverancierReferentie(ui->tbLevRef->text());
    lh->setOnzeFactuur(ui->tbOFact->text());
    lh->setOnzeReferentie(ui->tbORef->text());
    lh->setOpmerkingen(ui->tbOpm->text());
    lh->setTijdstip(ui->dtpDatum->date());
    lh->save();
}

void LeveringenFiche::on_btnOpslaan_clicked()
{
    SafeHeader();
}

void LeveringenFiche::FillRegels()
{
    QSqlQueryModel *reg_model = new QSqlQueryModel();
    LeveringenLine::getLeveringLijnen(reg_model, lh->getLeveringenHeader_ID());
    ui->tvRegels->setModel(reg_model);
    ui->tvRegels->verticalHeader()->setDefaultSectionSize(20);
    ui->tvRegels->setAlternatingRowColors(true);


}

void LeveringenFiche::on_tvRegels_doubleClicked(const QModelIndex &index)
{
    if ( lh->getLeveringenHeader_ID() == 0)
        lh->save();

    int Line_ID;
    Line_ID = ui->tvRegels->model()->data( ui->tvRegels->model()->index(ui->tvRegels->currentIndex().row(), 0 )).toInt();

    LeveringenRegel* lr = new LeveringenRegel(Line_ID, lh);
    lr->exec();
    FillRegels();

}

void LeveringenFiche::on_btnEditLine_clicked()
{
    if ( lh->getLeveringenHeader_ID() == 0)
        lh->save();

    int Line_ID;
    Line_ID = ui->tvRegels->model()->data( ui->tvRegels->model()->index(ui->tvRegels->currentIndex().row(), 0 )).toInt();

    LeveringenRegel* lr = new LeveringenRegel(Line_ID, lh);
    lr->exec();
    FillRegels();

}

void LeveringenFiche::on_btnRegelToevoegen_clicked()
{
    if ( lh->getLeveringenHeader_ID() == 0)
        lh->save();

    LeveringenRegel* lr = new LeveringenRegel(0, lh);
    lr->exec();
    FillRegels();
}
