#include "levcodefiche.h"
#include "ui_levcodefiche.h"

LevCodeFiche::LevCodeFiche(LeverancierCodes* _lc ,QWidget *parent) :
    QDialog(parent),
    ui(new Ui::LevCodeFiche)
{
    ui->setupUi(this);
    this->setWindowTitle("Nieuwe Leverancierscode!");
    ui->tbOmschrijving->setText("");
    ui->tbRef->setText("");
    lc = _lc;
}

LevCodeFiche::~LevCodeFiche()
{
    delete ui;
}

void LevCodeFiche::on_btnAnnuleren_clicked()
{
    this->close();
}

void LevCodeFiche::on_btnOpslaan_clicked()
{
    lc->setLev_Ref(ui->tbRef->text());
    lc->setLev_Omschr(ui->tbOmschrijving->text());
    lc->save();
    this->close();
}
