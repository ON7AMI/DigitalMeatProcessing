#include "addspecificatie.h"
#include "ui_addspecificatie.h"
#include "producten.h"
#include "soorten.h"
#include "details.h"
#include "specificaties.h"

#include <QBuffer>
#include <QFileDialog>
#include <QModelIndex>
#include <QPushButton>
#include <QTableView>

AddSpecificatie::AddSpecificatie(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddSpecificatie)
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
    Details::getDetailKeuze(Detail_Model, Product_ID, Soort_ID);
    ui->cbxDetail->setModel(Detail_Model);
    ui->cbxDetail->setModelColumn(1);

    Spec_Model = new QSqlQueryModel();
    Specificaties::getAllSpecificaties(Spec_Model, Product_ID, Soort_ID, Detail_ID);
    Spec_Model->setHeaderData(1, Qt::Horizontal, tr("Code"));
    Spec_Model->setHeaderData(2, Qt::Horizontal, tr("Benaming"));

    ui->tvSpecificatie->setModel(Spec_Model);
    ui->tvSpecificatie->setColumnHidden(0,true);
    ui->tvSpecificatie->setColumnHidden(3,true);
    ui->tvSpecificatie->setColumnWidth(1,50);
    ui->tvSpecificatie->setColumnWidth(2,300);

    ui->tvSpecificatie->setAlternatingRowColors(true);

    ui->cbxProduct->setCurrentIndex(-1);
    ui->cbxSoort->setCurrentIndex(-1);
    ui->cbxDetail->setCurrentIndex(-1);
    ui->cbxCode->setCurrentIndex(-1);
    ui->tbBenaming->setText("");
    spec = new Specificaties();

    ui->btnBewerk->setEnabled(true);
    ui->btnNieuw->setEnabled(true);
    ui->btnOpslaan->setEnabled(false);

    ui->cbxCode->setEnabled(false);
    ui->cbxProduct->setEnabled(false);
    ui->cbxSoort->setEnabled(false);
    ui->cbxDetail->setEnabled(false);
    ui->tbBenaming->setReadOnly(true);

}
void AddSpecificatie::setIDs(int _product_id, int _soort_id, int _detail_id)
{
    Product_ID = _product_id;
    spec->setProduct_ID(Product_ID);
    ui->cbxProduct->setCurrentIndex((_product_id == 0 ? 0 :
                ui->cbxProduct->model()->match(
                ui->cbxProduct->model()->index(0, 0),
                Qt::DisplayRole,
                QVariant::fromValue(_product_id),
                -1,
                Qt::MatchFixedString)[0].row()));

    Soort_ID = _soort_id;
    spec->setSoort_ID(Soort_ID);
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

    Detail_ID = _detail_id;
    spec->setDetail_ID(Detail_ID);
    Details::getDetailKeuze(Detail_Model, Product_ID, Soort_ID);
    ui->cbxDetail->setModel(Detail_Model);
    ui->cbxDetail->setModelColumn(1);
    ui->cbxDetail->setCurrentIndex((_detail_id == 0 ? 0 :
                ui->cbxDetail->model()->match(
                ui->cbxDetail->model()->index(0, 0),
                Qt::DisplayRole,
                QVariant::fromValue(_detail_id),
                -1,
                Qt::MatchFixedString)[0].row()));

    Specificaties::getAllSpecificaties(Spec_Model, _product_id, _soort_id, _detail_id );

}

AddSpecificatie::~AddSpecificatie()
{
    delete ui;
    delete prd_model;
    delete Soort_Model;
    delete Detail_Model;
    delete Spec_Model;
    delete spec;
}


void AddSpecificatie::on_btnStop_clicked()
{
    this->close();
}


void AddSpecificatie::on_btnNieuw_clicked()
{
    spec = new Specificaties();
    spec->setProduct_ID(Product_ID);
    spec->setSoort_ID(Soort_ID);
    spec->setDetail_ID(Detail_ID);
    spec->setSpecificatie_ID(0);

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

    ui->cbxDetail->setCurrentIndex((Detail_ID == 0 ? 0 :
                                    ui->cbxDetail->model()->match(
                                    ui->cbxDetail->model()->index(0, 0),
                                    Qt::DisplayRole,
                                    QVariant::fromValue(Detail_ID),
                                    -1,
                                    Qt::MatchFixedString)[0].row()));

    ui->tbBenaming->setText(spec->getSpecificatieBenaming());

    ui->btnBewerk->setEnabled(false);
    ui->btnNieuw->setEnabled(false);
    ui->btnOpslaan->setEnabled(true);

    ui->cbxCode->setEnabled(true);
    ui->tbBenaming->setReadOnly(false);

}

void AddSpecificatie::on_btnOpslaan_clicked()
{
    spec->setSpecificatieCode(ui->cbxCode->currentText());
    spec->setProduct_ID(Product_ID);
    spec->setSoort_ID(Soort_ID);
    spec->setDetail_ID(Detail_ID);
    spec->setSpecificatieBenaming(ui->tbBenaming->text());
    spec->save();

    ui->btnBewerk->setEnabled(true);
    ui->btnNieuw->setEnabled(true);
    ui->btnOpslaan->setEnabled(false);

    ui->cbxCode->setEnabled(false);
    ui->tbBenaming->setReadOnly(true);

    Specificaties::getAllSpecificaties(Spec_Model, Product_ID, Soort_ID, Detail_ID);
    ui->tvSpecificatie->setModel(Spec_Model);

}

void AddSpecificatie::on_btnBewerk_clicked()
{
    int _ID = ui->tvSpecificatie->model()->data( ui->tvSpecificatie->model()->index(ui->tvSpecificatie->currentIndex().row(), 0 )).toInt();

    spec = new Specificaties(_ID);

    ui->cbxCode->setCurrentText(spec->getSpecificatieCode());
    ui->tbBenaming->setText(spec->getSpecificatieBenaming());

    ui->btnBewerk->setEnabled(false);
    ui->btnNieuw->setEnabled(false);
    ui->btnOpslaan->setEnabled(true);

    ui->cbxCode->setEnabled(true);
    ui->tbBenaming->setReadOnly(false);
}
