#include "prijscontrole.h"
#include "ui_prijscontrole.h"

PrijsControle::PrijsControle(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::PrijsControle)
{
    ui->setupUi(this);
}

PrijsControle::~PrijsControle()
{
    delete ui;
}
