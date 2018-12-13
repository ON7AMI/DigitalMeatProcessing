#include "addbtwtarief.h"
#include "ui_addbtwtarief.h"

#include <QFileDialog>
#include <QModelIndex>
#include <QPushButton>
#include <QTableView>


AddBTWTarief::AddBTWTarief(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddBTWTarief)
{
    ui->setupUi(this);

    BTW_Model = new QSqlQueryModel();
    BTWTarieven::getAllBTWTarieven(BTW_Model);


    BTW_Model->setHeaderData(1, Qt::Horizontal, tr("Tarief"));
    BTW_Model->setHeaderData(2, Qt::Horizontal, tr("Percentage"));
    BTW_Model->setHeaderData(3, Qt::Horizontal, tr("Geldig Vanaf"));
    BTW_Model->setHeaderData(4, Qt::Horizontal, tr("Geldig Tot"));
    //Product_Model->
    ui->tvBTWTarief->setModel(BTW_Model);
    ui->tvBTWTarief->setColumnWidth(0,80);
    ui->tvBTWTarief->setColumnWidth(1,200);
    ui->tvBTWTarief->setColumnWidth(2,100);
    ui->tvBTWTarief->setColumnWidth(3,120);
    ui->tvBTWTarief->setColumnWidth(4,120);

    ui->tvBTWTarief->hideColumn(0);

    ui->tvBTWTarief->setAlternatingRowColors(true);

    ui->tbTarief->setText("");
    ui->tbPercentage->setText("");
    ui->dtpVanaf->setDate(QDate::currentDate());
    ui->dtpTot->setDate(QDate::currentDate());
    BTW = new BTWTarieven();

    ui->btnBewerk->setEnabled(true);
    ui->btnNieuw->setEnabled(true);
    ui->btnOpslaan->setEnabled(false);

    ui->tbTarief->setReadOnly(true);
    ui->tbPercentage->setReadOnly(true);
    ui->dtpVanaf->setReadOnly(true);
    ui->dtpTot->setReadOnly(true);
}

AddBTWTarief::~AddBTWTarief()
{
    delete ui;
    delete BTW;
    delete BTW_Model;
}

void AddBTWTarief::on_btnStop_clicked()
{
    this->close();
}

void AddBTWTarief::on_btnNieuw_clicked()
{
    BTW = new BTWTarieven();
    BTW->setBTWTarief_ID(0);
    ui->tbTarief->setText(BTW->getTarief());
    ui->tbPercentage->setText(QString("%1").arg(BTW->getPercentage()));
    ui->dtpVanaf->setDate(BTW->getGeldigVanaf());
    ui->dtpTot->setDate(BTW->getGeldigTot());

    ui->btnBewerk->setEnabled(false);
    ui->btnNieuw->setEnabled(false);
    ui->btnOpslaan->setEnabled(true);

    ui->tbTarief->setReadOnly(false);
    ui->tbPercentage->setReadOnly(false);
    ui->dtpVanaf->setReadOnly(false);
    ui->dtpTot->setReadOnly(false);
}

void AddBTWTarief::on_btnBewerk_clicked()
{
    int _ID = ui->tvBTWTarief->model()->data( ui->tvBTWTarief->model()->index(ui->tvBTWTarief->currentIndex().row(), 0 )).toInt();
    BTW = new BTWTarieven(_ID);

    ui->tbTarief->setText(BTW->getTarief());
    ui->tbPercentage->setText(QString("%1").arg(BTW->getPercentage()));
    ui->dtpVanaf->setDate(BTW->getGeldigVanaf());
    ui->dtpTot->setDate(BTW->getGeldigTot());

    ui->btnBewerk->setEnabled(false);
    ui->btnNieuw->setEnabled(false);
    ui->btnOpslaan->setEnabled(true);

    ui->tbTarief->setReadOnly(false);
    ui->tbPercentage->setReadOnly(false);
    ui->dtpVanaf->setReadOnly(false);
    ui->dtpTot->setReadOnly(false);
}

void AddBTWTarief::on_btnOpslaan_clicked()
{
    BTW->setTarief(ui->tbTarief->text());
    BTW->setPercentage(ui->tbPercentage->text().toDouble());
    BTW->setGeldigVanaf(ui->dtpVanaf->date());
    BTW->setGeldigTot(ui->dtpTot->date());
    BTW->save();

    ui->btnBewerk->setEnabled(true);
    ui->btnNieuw->setEnabled(true);
    ui->btnOpslaan->setEnabled(false);

    ui->tbTarief->setReadOnly(true);
    ui->tbPercentage->setReadOnly(true);
    ui->dtpVanaf->setReadOnly(true);
    ui->dtpTot->setReadOnly(true);

    BTWTarieven::getAllBTWTarieven(BTW_Model);
    ui->tvBTWTarief->setModel(BTW_Model);
}
