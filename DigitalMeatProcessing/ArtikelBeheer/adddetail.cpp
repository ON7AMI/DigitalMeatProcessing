#include "adddetail.h"
#include "ui_adddetail.h"
#include "producten.h"
#include "soorten.h"
#include "details.h"

#include <QBuffer>
#include <QFileDialog>
#include <QModelIndex>
#include <QPushButton>
#include <QTableView>

//======================================================================================================================
//   Beheren aan aanmaken van detail groepen
//

AddDetail::AddDetail(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::adddetail)
{
    ui->setupUi(this);

    prd_model = new QSqlQueryModel();
    Producten::getProductenKeuze(prd_model);
    ui->cbxProduct->setModel(prd_model);
    ui->cbxProduct->setModelColumn(1);

    Soort_Model = new QSqlQueryModel();
    Soorten::getSoortenKeuze(Soort_Model, Product_ID);
    ui->cbxSoort->setModel(Soort_Model);
    ui->cbxSoort->setModelColumn(1);

    Detail_Model = new QSqlQueryModel();
    Details::getAllDetails(Detail_Model, Product_ID, Soort_ID);
    Detail_Model->setHeaderData(1, Qt::Horizontal, tr("Code"));
    Detail_Model->setHeaderData(2, Qt::Horizontal, tr("Benaming"));

    ui->tvDetail->setModel(Detail_Model);
    ui->tvDetail->setColumnHidden(0,true);
    ui->tvDetail->setColumnHidden(3,true);
    ui->tvDetail->setColumnWidth(1,50);
    ui->tvDetail->setColumnWidth(2,300);

    ui->tvDetail->setAlternatingRowColors(true);

    ui->cbxProduct->setCurrentIndex(-1);
    ui->cbxSoort->setCurrentIndex(-1);
    ui->cbxCode->setCurrentIndex(-1);
    ui->tbBenaming->setText("");
    ui->tbOmschrijving->setText("");
    det = new Details();

    ui->btnBewerk->setEnabled(true);
    ui->btnNieuw->setEnabled(true);
    ui->btnOpslaan->setEnabled(false);

    ui->cbxCode->setEnabled(false);
    ui->cbxProduct->setEnabled(false);
    ui->cbxSoort->setEnabled(false);
    ui->tbBenaming->setReadOnly(true);
    ui->tbOmschrijving->setReadOnly(true);

}

void AddDetail::setIDs(int _product_id, int _soort_id)
{
    Product_ID = _product_id;
    det->setProduct_ID(Product_ID);
    ui->cbxProduct->setCurrentIndex((_product_id == 0 ? 0 :
                ui->cbxProduct->model()->match(
                ui->cbxProduct->model()->index(0, 0),
                Qt::DisplayRole,
                QVariant::fromValue(_product_id),
                -1,
                Qt::MatchFixedString)[0].row()));

    Soort_ID = _soort_id;
    det->setSoort_ID(Soort_ID);
    Soorten::getSoortenKeuze(Soort_Model, Product_ID);
    ui->cbxSoort->setModel(Soort_Model);
    ui->cbxSoort->setModelColumn(1);
    ui->cbxSoort->setCurrentIndex((_soort_id == 0 ? 0 :
                ui->cbxSoort->model()->match(
                ui->cbxSoort->model()->index(0, 0),
                Qt::DisplayRole,
                QVariant::fromValue(_soort_id),
                -1,
                Qt::MatchFixedString)[0].row()));

    Details::getAllDetails(Detail_Model, _product_id, _soort_id);
}

AddDetail::~AddDetail()
{
    delete ui;
    delete prd_model;
    delete Soort_Model;
    delete Detail_Model;
    delete det;
}

void AddDetail::on_btnStop_clicked()
{
    this->close();
}

void AddDetail::on_btnNieuw_clicked()
{
    det = new Details();
    det->setProduct_ID(Product_ID);
    det->setSoort_ID(Soort_ID);
    det->setDetail_ID(0);

    ui->cbxCode->setCurrentIndex(-1);
    ui->cbxProduct->setCurrentIndex((Product_ID == 0 ? 0 :
                                    ui->cbxProduct->model()->match(
                                    ui->cbxProduct->model()->index(0, 0),
                                    Qt::DisplayRole,
                                    QVariant::fromValue(Product_ID),
                                    -1,
                                    Qt::MatchFixedString)[0].row()));
    ui->cbxSoort->setCurrentIndex((Soort_ID == 0 ? 0 :
                                    ui->cbxSoort->model()->match(
                                    ui->cbxSoort->model()->index(0, 0),
                                    Qt::DisplayRole,
                                    QVariant::fromValue(Soort_ID),
                                    -1,
                                    Qt::MatchFixedString)[0].row()));

    ui->tbBenaming->setText(det->getDetailBenaming());
    ui->tbOmschrijving->setText(det->getDetailOmschrijving());

    ui->btnBewerk->setEnabled(false);
    ui->btnNieuw->setEnabled(false);
    ui->btnOpslaan->setEnabled(true);

    ui->cbxCode->setEnabled(true);
    ui->tbBenaming->setReadOnly(false);
    ui->tbOmschrijving->setReadOnly(false);
}

void AddDetail::on_btnOpslaan_clicked()
{
    det->setDetailCode(ui->cbxCode->currentText());
    det->setProduct_ID(Product_ID);
    det->setSoort_ID(Soort_ID);
    det->setDetailBenaming(ui->tbBenaming->text());
    det->setDetailOmschrijving(ui->tbOmschrijving->text());
    det->save();

    ui->btnBewerk->setEnabled(true);
    ui->btnNieuw->setEnabled(true);
    ui->btnOpslaan->setEnabled(false);

    ui->cbxCode->setEnabled(false);
    ui->tbBenaming->setReadOnly(true);
    ui->tbOmschrijving->setReadOnly(true);

    Details::getAllDetails(Detail_Model, Product_ID, Soort_ID);
    ui->tvDetail->setModel(Detail_Model);

}

void AddDetail::on_btnBewerk_clicked()
{
    int _ID = ui->tvDetail->model()->data( ui->tvDetail->model()->index(ui->tvDetail->currentIndex().row(), 0 )).toInt();

    det = new Details(_ID);

    ui->cbxCode->setCurrentText(det->getDetailCode());
    ui->tbBenaming->setText(det->getDetailBenaming());
    ui->tbOmschrijving->setText(det->getDetailOmschrijving());

    ui->btnBewerk->setEnabled(false);
    ui->btnNieuw->setEnabled(false);
    ui->btnOpslaan->setEnabled(true);

    ui->cbxCode->setEnabled(true);
    ui->tbBenaming->setReadOnly(false);
    ui->tbOmschrijving->setReadOnly(false);

}
