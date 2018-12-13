#include "addeenheid.h"
#include "ui_addeenheid.h"

#include <QBuffer>
#include <QFileDialog>
#include <QModelIndex>
#include <QPushButton>
#include <QTableView>

AddEenheid::AddEenheid(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddEenheid)
{
    ui->setupUi(this);
    ce_Model = new QSqlQueryModel();
    ComEenheden::getAllComEenheden(ce_Model);
    ce_Model->setHeaderData(1, Qt::Horizontal, tr("Code"));
    ce_Model->setHeaderData(2, Qt::Horizontal, tr("Benaming"));
    //Product_Model->
    ui->tvEenheid->setModel(ce_Model);
    ui->tvEenheid->setColumnWidth(0,80);
    ui->tvEenheid->setColumnWidth(1,50);
    ui->tvEenheid->setColumnWidth(2,300);
    ui->tvEenheid->hideColumn(0);

    ui->tvEenheid->setAlternatingRowColors(true);

    ui->tbCode->setText("");
    ui->tbOmschrijving->setText("");
    ce = new ComEenheden();

    ui->btnBewerk->setEnabled(true);
    ui->btnNieuw->setEnabled(true);
    ui->btnOpslaan->setEnabled(false);

    ui->tbCode->setReadOnly(true);
    ui->tbOmschrijving->setReadOnly(true);

}

AddEenheid::~AddEenheid()
{
    delete ui;
    delete ce;
    delete ce_Model;
}

void AddEenheid::on_btnStop_clicked()
{
    this->close();
}

void AddEenheid::on_btnNieuw_clicked()
{
    ce = new ComEenheden();
    ce->setEenheids_ID(0);
    ui->tbCode->setText(ce->getEenheidsCode());
    ui->tbOmschrijving->setText(ce->getEenheidsOmschrijving());

    ui->btnBewerk->setEnabled(false);
    ui->btnNieuw->setEnabled(false);
    ui->btnOpslaan->setEnabled(true);

    ui->tbCode->setReadOnly(false);
    ui->tbOmschrijving->setReadOnly(false);
}

void AddEenheid::on_btnOpslaan_clicked()
{
    ce->setEenheidsCode(ui->tbCode->text());
    ce->setEenheidsOmschrijving(ui->tbOmschrijving->text());
    ce->save();

    ui->btnBewerk->setEnabled(true);
    ui->btnNieuw->setEnabled(true);
    ui->btnOpslaan->setEnabled(false);

    ui->tbCode->setReadOnly(true);
    ui->tbOmschrijving->setReadOnly(true);

    ComEenheden::getAllComEenheden(ce_Model);
    ui->tvEenheid->setModel(ce_Model);
}

void AddEenheid::on_btnBewerk_clicked()
{
    int _ID = ui->tvEenheid->model()->data( ui->tvEenheid->model()->index(ui->tvEenheid->currentIndex().row(), 0 )).toInt();
    ce = new ComEenheden(_ID);

    ui->tbCode->setText(ce->getEenheidsCode());
    ui->tbOmschrijving->setText(ce->getEenheidsOmschrijving());

    ui->btnBewerk->setEnabled(false);
    ui->btnNieuw->setEnabled(false);
    ui->btnOpslaan->setEnabled(true);

    ui->tbCode->setReadOnly(false);
    ui->tbOmschrijving->setReadOnly(false);

}
