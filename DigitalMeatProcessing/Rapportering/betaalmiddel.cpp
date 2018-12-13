#include "betaalmiddel.h"
#include "ui_betaalmiddel.h"



#include <QDateTime>
#include <QSqlRecord>

Betaalmiddel::Betaalmiddel(QDateTime datum , QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Betaalmiddel)
{
    ui->setupUi(this);
    Datum = datum;
    this->setWindowTitle(QString("Correctie betaalmiddelen van %1").arg(datum.date().toString("dd/MM/yyyy")));
    Betaalmiddel_Model = new QSqlQueryModel();
    Kasboek::getBetaalmiddelen(Betaalmiddel_Model);
    ui->cbxBetaalwijze->setModel(Betaalmiddel_Model);
    ui->cbxBetaalwijze->setModelColumn(1);
    ui->cbxBetaalwijze->setCurrentIndex(-1);
    kb = new Kasboek();
    Fill();
}

void Betaalmiddel::Fill()
{
    Kasboek_Model = new QSqlQueryModel();
    Kasboek::getKassaBetaalmiddelen(Datum, Kasboek_Model);
    ui->tvLijst->setModel(Kasboek_Model);
    ui->tvLijst->setColumnWidth(0,80);
    ui->tvLijst->setColumnWidth(1,100);
    ui->tvLijst->setColumnWidth(2,100);
    ui->tvLijst->setColumnWidth(3,140);
    ui->tvLijst->setColumnWidth(4,180);
    ui->tvLijst->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tvLijst->setAlternatingRowColors(true);
    ui->tbID->setText("");
    ui->tbTijdstip->setText("");
    ui->tbBedrag->setText("");

}


Betaalmiddel::~Betaalmiddel()
{
    delete ui;
    delete kb;
    delete Kasboek_Model;
    delete Betaalmiddel_Model;
}

void Betaalmiddel::on_btnSluiten_clicked()
{
    this->close();
}

void Betaalmiddel::on_tvLijst_doubleClicked(const QModelIndex &index)
{
    int _ID = Kasboek_Model->record(index.row()).value(0).toInt();
    //int _ID = ui->tvLijst->model()->data( ui->tvLijst->model()->index(ui->tvLijst->currentIndex().row(), 0 )).toInt();
    kb = new Kasboek(_ID);
    ui->tbID->setText(QString::number(kb->getKasboek_ID()));
    ui->tbTijdstip->setText(kb->getTijdstip().time().toString());
    ui->tbBedrag->setText(QString::number(kb->getBedragIn()));
    ui->cbxBetaalwijze->setCurrentIndex((kb->getBetaalmiddel_ID() == 0 ? 0 :
                ui->cbxBetaalwijze->model()->match(
                ui->cbxBetaalwijze->model()->index(0, 0),
                Qt::DisplayRole,
                QVariant::fromValue(kb->getBetaalmiddel_ID()),
                -1,
                Qt::MatchFixedString)[0].row()));

}

void Betaalmiddel::on_btnOpslaan_clicked()
{
    int _ID = Betaalmiddel_Model->record(ui->cbxBetaalwijze->currentIndex()).value(0).toInt();
    if (kb->getKasboek_ID() != 0)
    {
        kb->setBetaalmiddel_ID(_ID);
        kb->save();
        Fill();
    }
}
