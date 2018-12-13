#include "addsoort.h"
#include "ui_addsoort.h"
#include "producten.h"
#include "soorten.h"

#include <QBuffer>
#include <QFileDialog>
#include <QModelIndex>
#include <QPushButton>
#include <QTableView>

//=========================================================================
//  Beheren en aanmaken van Soorten
//  Per Product kunnen 36 soorten zijn
//  0    Geen verdere specificatie
//  1->9 Meest voorkomende
//  A->Z Minder voorkomende
//
AddSoort::AddSoort(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddSoort)
{
    ui->setupUi(this);

    // Vul keuzelijst Producten
    prd_model = new QSqlQueryModel();
    Producten::getProductenKeuze(prd_model);
    ui->cbxProduct->setModel(prd_model);
    ui->cbxProduct->setModelColumn(1);

    Soort_Model = new QSqlQueryModel();
    Soorten::getAllSoorten(Soort_Model, Product_ID);
    Soort_Model->setHeaderData(0, Qt::Horizontal, tr("Afbeelding"));
    Soort_Model->setHeaderData(1, Qt::Horizontal, tr("Code"));
    Soort_Model->setHeaderData(2, Qt::Horizontal, tr("Benaming"));
    //Product_Model->
    ui->tvSoorten->setModel(Soort_Model);
    ui->tvSoorten->setColumnWidth(0,80);
    ui->tvSoorten->setColumnWidth(1,50);
    ui->tvSoorten->setColumnWidth(2,300);

    ui->tvSoorten->setAlternatingRowColors(true);
    ui->tvSoorten->setItemDelegate(new SoortImageDelegate(this));

    ui->cbxProduct->setCurrentIndex(-1);
    ui->cbxCode->setCurrentIndex((-1));
    ui->tbBenaming->setText("");
    ui->tbOmschrijving->setText("");

    srt = new Soorten();

    ui->btnBewerk->setEnabled(true);
    ui->btnLaadPicture->setEnabled(false);
    ui->btnNieuw->setEnabled(true);
    ui->btnOpslaan->setEnabled(false);

    ui->cbxProduct->setEnabled(false);
    ui->cbxCode->setEnabled(false);
    ui->tbBenaming->setReadOnly(true);
    ui->tbOmschrijving->setReadOnly(true);

}

void AddSoort::setProductID(int _product_id)
{
    Product_ID = _product_id;
    srt->setProduct_ID(Product_ID);

    // Selecteer huidig product
    ui->cbxProduct->setCurrentIndex((_product_id == 0 ? 0 :
                ui->cbxProduct->model()->match(
                ui->cbxProduct->model()->index(0, 0),
                Qt::DisplayRole,
                QVariant::fromValue(_product_id),
                -1,
                Qt::MatchFixedString)[0].row()));

    Soorten::getAllSoorten(Soort_Model, Product_ID);
}

AddSoort::~AddSoort()
{
    delete ui;
    delete prd_model;
    delete Soort_Model;
    delete srt;
}

void AddSoort::on_btnStop_clicked()
{
    this->close();
}


void AddSoort::on_btnLaadPicture_clicked()
{
    QString bestand;
    bestand = QFileDialog::getOpenFileName(this, tr("Open Afbeeldingen"), "~", tr("Afbeeldingen (*.png *.jpg *.bmp);;Alle bestanden (*.*)"));
    if (!bestand.isEmpty())
    {
        QPixmap image(bestand);
        QByteArray bytes;
        QBuffer buffer(&bytes);
        buffer.open(QIODevice::WriteOnly);
        image.save(&buffer, "PNG");

        ui->lbFoto->setPixmap(image);
    }
}

void AddSoort::on_btnNieuw_clicked()
{
    srt = new Soorten();
    srt->setProduct_ID(Product_ID);
    srt->setSoorten_ID(0);

    ui->cbxCode->setCurrentIndex(-1);
    ui->cbxProduct->setCurrentIndex((Product_ID == 0 ? 0 :
                                    ui->cbxProduct->model()->match(
                                    ui->cbxProduct->model()->index(0, 0),
                                    Qt::DisplayRole,
                                    QVariant::fromValue(Product_ID),
                                    -1,
                                    Qt::MatchFixedString)[0].row()));

    ui->tbBenaming->setText(srt->getSoortBenaming());
    ui->tbOmschrijving->setText(srt->getSoortOmschrijving());

    ui->btnBewerk->setEnabled(false);
    ui->btnLaadPicture->setEnabled(true);
    ui->btnNieuw->setEnabled(false);
    ui->btnOpslaan->setEnabled(true);

    ui->cbxCode->setEnabled(true);
    ui->tbBenaming->setReadOnly(false);
    ui->tbOmschrijving->setReadOnly(false);

    QPixmap image;
    ui->lbFoto->setPixmap(image);

}


void AddSoort::on_btnOpslaan_clicked()
{
    QByteArray bytes;
    QBuffer buffer(&bytes);
    buffer.open(QIODevice::WriteOnly);
    ui->lbFoto->pixmap()->save(&buffer, "PNG");

    srt->setProduct_ID(Product_ID);
    srt->setSoortCode(ui->cbxCode->currentText());
    srt->setSoortBenaming(ui->tbBenaming->text());
    srt->setSoortOmschrijving(ui->tbOmschrijving->text());
    srt->setSoortAfbeelding(bytes);
    srt->save();

    ui->btnBewerk->setEnabled(true);
    ui->btnLaadPicture->setEnabled(false);
    ui->btnNieuw->setEnabled(true);
    ui->btnOpslaan->setEnabled(false);

    ui->cbxCode->setEnabled(false);
    ui->tbBenaming->setReadOnly(true);
    ui->tbOmschrijving->setReadOnly(true);

//    QPixmap image;
//    ui->lbFoto->setPixmap(image);

    Soorten::getAllSoorten(Soort_Model, Product_ID);
    ui->tvSoorten->setModel(Soort_Model);

}


void AddSoort::on_btnBewerk_clicked()
{
    QPixmap image;

    int _ID = ui->tvSoorten->model()->data( ui->tvSoorten->model()->index(ui->tvSoorten->currentIndex().row(), 0 )).toInt();

    srt = new Soorten(_ID);

    ui->cbxCode->setCurrentText(srt->getSoortCode());
    ui->tbBenaming->setText(srt->getSoortBenaming());
    ui->tbOmschrijving->setText(srt->getSoortOmschrijving());
    image.loadFromData(srt->getSoortAfbeelding(), "PNG");
    ui->lbFoto->setPixmap(image);

    ui->btnBewerk->setEnabled(false);
    ui->btnLaadPicture->setEnabled(true);
    ui->btnNieuw->setEnabled(false);
    ui->btnOpslaan->setEnabled(true);

    ui->cbxCode->setEnabled(true);
    ui->tbBenaming->setReadOnly(false);
    ui->tbOmschrijving->setReadOnly(false);

}

void AddSoort::on_cbxProduct_currentIndexChanged(int index)
{

    if (index != 0)
    {
      Soorten::getAllSoorten(Soort_Model, index);
    }
}


//==================================================================================================================
//   Delegate voor het tekenen van de afbeelding in de eerste colom.
//

SoortImageDelegate::SoortImageDelegate(QObject * parent)
        : QItemDelegate(parent)
{

}

void SoortImageDelegate::paint(QPainter * painter, const QStyleOptionViewItem & option, const QModelIndex & index) const
{
    if (index.column() == 0)
    {
        int data = index.data().toInt(); //index.data(Qt::DisplayRole).toInt();
        Soorten *pr = new Soorten(data);

        QPixmap pm, pn;
        pm.loadFromData(pr->getSoortAfbeelding(), "PNG");
        pm = pm.scaledToHeight(40);

        QRect newrect;
        int nx, ox, rw, pw, hw;
        ox = option.rect.x();
        rw = option.rect.width();
        pw = pm.width();
        hw = (rw - pw)/2;
        nx = ox + hw;
        newrect.setX(option.rect.x() + ((option.rect.width() - pm.width())/2));
        newrect.setY(option.rect.y());
        newrect.setWidth(pm.width());
        newrect.setHeight(option.rect.height());
        painter->drawPixmap(newrect, pm);
        //painter->drawPixmap(option.rect, pm);
    }
    else
    {
        QItemDelegate::paint(painter, option, index);
    }
}

