#include "dlgabout.h"
#include "ui_dlgabout.h"

#include <QApplication>

dlgAbout::dlgAbout(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::dlgAbout)
{
    ui->setupUi(this);

    QString ver = QApplication::applicationVersion();
    ui->lbVersion->setText("Version nr.: " + ver);
}

dlgAbout::~dlgAbout()
{
    delete ui;
}
