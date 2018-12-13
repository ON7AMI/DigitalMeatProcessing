#include "selectallergenen.h"
#include "ui_selectallergenen.h"

#include "allergenen.h"
#include "artikelen.h"

#include <QStandardItemModel>
#include <QSqlQueryModel>
#include <QSqlRecord>
#include <QSqlField>


SelectAllergenen::SelectAllergenen(int _id, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SelectAllergenen)
{
    ui->setupUi(this);
    Artikel_ID = _id;
    FillTable();
    ui->btnBewerk->setEnabled(true);
    ui->btnOpslaan->setEnabled(false);
    ui->tvAllergenen->setEnabled(false);
}

SelectAllergenen::~SelectAllergenen()
{
    delete ui;
    delete tableModel;
}

void SelectAllergenen::on_btnStop_clicked()
{
    this->close();
}

void SelectAllergenen::FillTable()
{
    tableModel = new QStandardItemModel();

    QSqlQueryModel *al_model = new QSqlQueryModel();
    Allergenen::getAllergeenKeuze(al_model);

    Artikelen art = Artikelen(Artikel_ID);
    QList<int>* all = art.getAllergenen();
    bool aanwezig = false;

    //QSqlQueryModel *model = tableView->model();
    QSqlRecord record;
    QSqlField field;


    for (int rij = 0; rij<al_model->rowCount(); rij++)
    {
        record = al_model->record(rij);
        field = record.field(0);
        int al_id = field.value().toInt();
        tableModel->setItem(rij, 0, new QStandardItem(QString::number(al_id)));

        // create check box item
        QStandardItem* item0 = new QStandardItem(true);
        item0->setCheckable(true);

        aanwezig = all->contains(al_id);

        if (aanwezig)
            item0->setCheckState(Qt::Checked);
        else
            item0->setCheckState(Qt::Unchecked);

        bool test = item0->checkState();
        field = record.field(1);
        item0->setText(field.value().toString());

        tableModel->setItem(rij, 1, item0);
    }
    tableModel->setHeaderData(0, Qt::Horizontal, tr("ID"));
    tableModel->setHeaderData(1, Qt::Horizontal, tr("Aanwezig"));


    //result = tableModel->data(1,2).toString();
    ui->tvAllergenen->setModel(tableModel);

    ui->tvAllergenen->setColumnWidth(0,50);
    ui->tvAllergenen->setColumnWidth(1,300);

    ui->tvAllergenen->hideColumn(0);
    ui->tvAllergenen->verticalHeader()->setDefaultSectionSize(20);
    ui->tvAllergenen->setAlternatingRowColors(true);

    delete al_model;
    delete all;
}

void SelectAllergenen::on_btnOpslaan_clicked()
{
    int id = 0;
    bool Aanwezig = false;

    QList<int>* all = new QList<int>();

    for (int rij = 0; rij<ui->tvAllergenen->model()->rowCount(); rij++)
    {

        Aanwezig = ui->tvAllergenen->model()->data(ui->tvAllergenen->model()->index(rij, 1), Qt::CheckStateRole).toBool();
        if (Aanwezig)
        {
            id = ui->tvAllergenen->model()->data(ui->tvAllergenen->model()->index(rij, 0)).toInt();
            all->append(id);
        }
    }

    Artikelen art = Artikelen(Artikel_ID);
    art.setAllergenen(all);
    this->close();
}

void SelectAllergenen::on_btnBewerk_clicked()
{
    ui->btnBewerk->setEnabled(false);
    ui->btnOpslaan->setEnabled(true);
    ui->tvAllergenen->setEnabled(true);
}
