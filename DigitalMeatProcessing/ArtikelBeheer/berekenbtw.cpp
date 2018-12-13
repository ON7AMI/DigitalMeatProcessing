#include "berekenbtw.h"
#include "ui_berekenbtw.h"

BerekenBTW::BerekenBTW(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::BerekenBTW)
{
    ui->setupUi(this);
    Result = 0;
    ui->tbExcl->setText("0");
    ui->tbIncl->setText("0");
}

BerekenBTW::~BerekenBTW()
{
    delete ui;
}

void BerekenBTW::calc()
{
    double BTW, excl, incl;
    if(ui->rbtn6->isChecked())
        BTW = 1.06;
    else
        BTW = 1.21;

    incl = ui->tbIncl->text().toDouble();
    excl = incl / BTW;
    ui->tbExcl->setText(QString::number(excl));
    Result = excl;
}


void BerekenBTW::on_tbIncl_editingFinished()
{
    calc();
}

void BerekenBTW::on_rbtn6_toggled(bool checked)
{
    calc();
}
