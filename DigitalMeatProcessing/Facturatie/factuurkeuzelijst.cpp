#include "factuurkeuzelijst.h"
#include "factuurfiche.h"
#include "ui_factuurkeuzelijst.h"

#include <QSqlRecord>

FactuurKeuzeLijst::FactuurKeuzeLijst(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::FactuurKeuzeLijst)
{
    ui->setupUi(this);
    Facturen_model = new QSqlQueryModel();
    ui->rbtnLaatste->setChecked(true);
    ui->sbNummer->setValue(1);
    ui->tbNaam->setText("");
    FillTable();
}

FactuurKeuzeLijst::~FactuurKeuzeLijst()
{
    delete ui;
    delete Facturen_model;
}

void FactuurKeuzeLijst::FillTable()
{
    if(ui->rbtnLaatste->isChecked())
    {
        FactuurHeader::getLaatsteFacturen(Facturen_model);
        ui->tvFactuurLijst->setModel(Facturen_model);
    }
    else if (ui->rbtnNummer->isChecked())
    {
        FactuurHeader::getLaatsteFacturen(Facturen_model, ui->sbNummer->value());
        ui->tvFactuurLijst->setModel(Facturen_model);
    }


    ui->tvFactuurLijst->verticalHeader()->setDefaultSectionSize(20);
    ui->tvFactuurLijst->setAlternatingRowColors(true);
    ui->tvFactuurLijst->setColumnWidth(4,500);
}

void FactuurKeuzeLijst::on_tvFactuurLijst_doubleClicked(const QModelIndex &index)
{
    int Factuur_ID = 0;
    int row = index.row();
    QSqlRecord rec = Facturen_model->record(row);
    Factuur_ID = rec.value(0).toInt();
    FactuurFiche* fa = new FactuurFiche(Factuur_ID);
    fa->exec();
    delete fa;
}

void FactuurKeuzeLijst::on_pushButton_clicked()
{
    FillTable();
}
