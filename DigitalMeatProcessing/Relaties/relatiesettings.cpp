#include "relatiesettings.h"
#include "ui_relatiesettings.h"

RelatieSettings::RelatieSettings(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::RelatieSettings)
{
    ui->setupUi(this);
}

RelatieSettings::~RelatieSettings()
{
    delete ui;
}
