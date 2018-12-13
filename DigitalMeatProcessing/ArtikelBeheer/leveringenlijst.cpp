#include "leveringenlijst.h"
#include "ui_leveringenlijst.h"

#include "Bestellingen/leveringenheader.h"
#include "ArtikelBeheer/leveringenfiche.h"
#include "Relaties/relaties.h"
#include "Relaties/findrelaties.h"

LeveringenLijst::LeveringenLijst(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::LeveringenLijst)
{
    ui->setupUi(this);
    ui->cbFilterLeverancier->setChecked(false);
    Lev_ID = 0;
    SelLev_ID = 0;
    StartDatum = QDate::currentDate().addYears(-1);
    EindDatum =QDate::currentDate().addDays(1);
    ui->dtpVanDatum->setDate(StartDatum);
    ui->dtpTotDatum->setDate(EindDatum);
    ui->tbLeverancier->setText("");

    Leveringenen_model = new QSqlQueryModel();
    FillTable();
}

LeveringenLijst::~LeveringenLijst()
{
    delete ui;
    delete Leveringenen_model;
}

void LeveringenLijst::on_btnExit_clicked()
{
    this->close();
}

void LeveringenLijst::RefreshTable()
{
    FillTable();
}

void LeveringenLijst::FillTable()
{
    if (ui->cbFilterLeverancier->isChecked())
        Lev_ID = SelLev_ID;
    else
        Lev_ID = 0;

    LeveringenHeader::getLaatsteLeveringen(Leveringenen_model, Lev_ID, StartDatum, EindDatum);
    ui->tvLeveringenLijst->setModel(Leveringenen_model);
    ui->tvLeveringenLijst->verticalHeader()->setDefaultSectionSize(20);
    ui->tvLeveringenLijst->setAlternatingRowColors(true);
    ui->tvLeveringenLijst->setColumnWidth(0,40);
    ui->tvLeveringenLijst->setColumnWidth(1,75);
    ui->tvLeveringenLijst->setColumnWidth(2,200);
    ui->tvLeveringenLijst->setColumnWidth(5,500);
}

void LeveringenLijst::on_btnRefresh_clicked()
{
    RefreshTable();
}

void LeveringenLijst::on_dtpTotDatum_editingFinished()
{
    EindDatum = ui->dtpTotDatum->date();
}

void LeveringenLijst::on_dtpVanDatum_editingFinished()
{
    StartDatum = ui->dtpVanDatum->date();
}

void LeveringenLijst::on_btnZoek_clicked()
{
    int rel_id;
    FindRelaties *fr = new FindRelaties( ui->tbLeverancier->text(),"","","");

    fr->exec();
    rel_id = fr->getID();
    Relaties* rel = new Relaties(rel_id);
    if (rel->getRelatie_ID() != 0)
    {
        ui->tbLeverancier->setText(rel->getNaam() + " " + rel->getVoornaam());
        SelLev_ID =  rel->getRelatie_ID();
    }
}

void LeveringenLijst::on_btnAdd_clicked()
{
    LeveringenFiche* lf = new LeveringenFiche(0);
    lf->exec();
    RefreshTable();
}

void LeveringenLijst::on_tvLeveringenLijst_doubleClicked(const QModelIndex &index)
{
    int Line_ID = 0;
    Line_ID = ui->tvLeveringenLijst->model()->data( ui->tvLeveringenLijst->model()->index(ui->tvLeveringenLijst->currentIndex().row(), 0 )).toInt();
    LeveringenFiche* lf = new LeveringenFiche(Line_ID);
    lf->exec();
    RefreshTable();
}
