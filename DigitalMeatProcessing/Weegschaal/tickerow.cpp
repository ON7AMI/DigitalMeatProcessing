#include "tickerow.h"
#include "ui_tickerow.h"

TickeRow::TickeRow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::TickeRow)
{
    ui->setupUi(this);
}

TickeRow::~TickeRow()
{
    delete ui;
}

QString TickeRow::getOmscrijving()
{
    QString txt;
    txt = ui->lbOmschrijving->text();
    return txt;
}

void TickeRow::setOmschrijving(QString _omschr)
{
    ui->lbOmschrijving->setText(_omschr);
}

void TickeRow::setHoeveelheid(QString _hoeveel)
{
    ui->lbHoeveel->setText(_hoeveel);
}

void TickeRow::setPrijs(QString _prijs)
{
    ui->lbPrijs->setText(_prijs);
}
