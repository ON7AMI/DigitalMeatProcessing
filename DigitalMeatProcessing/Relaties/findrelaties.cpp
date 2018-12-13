#include "findrelaties.h"
#include "ui_findrelaties.h"
#include "relaties.h"
#include "btndeligate.h"

FindRelaties::FindRelaties(QString _naam, QString _adres, QString _gemeente, QString _email, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::FindRelaties)
{
    ui->setupUi(this);

    myModel = new QSqlQueryModel();
    Relaties::FindList( myModel,  _naam,  _adres,  _gemeente,  _email);
    QSortFilterProxyModel* proxyModel = new QSortFilterProxyModel();        // QSqlQueryModel heeft geen eigen sorting logica

    proxyModel->setSourceModel( myModel );

    ui->tvZoeken->setModel(proxyModel);
    ui->tvZoeken->horizontalHeader()->setSortIndicatorShown(true);
    ui->tvZoeken->horizontalHeader()->setSortIndicator(1, Qt::AscendingOrder);
    ui->tvZoeken->setSortingEnabled(true);
    btnDeligate *delegate = new btnDeligate(ui->tvZoeken);
    ui->tvZoeken->setItemDelegate(delegate);
    _ID = 0;
}

FindRelaties::~FindRelaties()
{
    delete ui;
    delete myModel;
}

void FindRelaties::on_buttonBox_accepted()
{
    _ID = ui->tvZoeken->model()->data( ui->tvZoeken->model()->index(ui->tvZoeken->currentIndex().row(), 0 )).toInt();
    //_ID = 4;
}

int FindRelaties::getID()
{
    return _ID;
}

void FindRelaties::on_tvZoeken_clicked(const QModelIndex &index)
{
    if (index.column() == 0)
    {
        _ID = ui->tvZoeken->model()->data( ui->tvZoeken->model()->index(ui->tvZoeken->currentIndex().row(), 0 )).toInt();
        this->close();
    }

}
