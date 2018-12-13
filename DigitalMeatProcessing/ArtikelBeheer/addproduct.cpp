#include "addproduct.h"
#include "ui_addproduct.h"
#include "producten.h"

#include <QBuffer>
#include <QFileDialog>
#include <QModelIndex>
#include <QPushButton>
#include <QTableView>


//======================================================================================================================
//   Beheren aan aanmaken van Product groepen
//

AddProduct::AddProduct(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddProduct)
{
    ui->setupUi(this);

    Product_Model = new QSqlQueryModel();
    Producten::getAllProducten(Product_Model);
    Product_Model->setHeaderData(0, Qt::Horizontal, tr("Afbeelding"));
    Product_Model->setHeaderData(1, Qt::Horizontal, tr("Code"));
    Product_Model->setHeaderData(2, Qt::Horizontal, tr("Benaming"));
    //Product_Model->
    ui->tvProducten->setModel(Product_Model);
    ui->tvProducten->setColumnWidth(0,80);
    ui->tvProducten->setColumnWidth(1,50);
    ui->tvProducten->setColumnWidth(2,300);

    ui->tvProducten->setAlternatingRowColors(true);
    ui->tvProducten->setItemDelegate(new ImageDelegate(this));

    ui->cbxCode->setCurrentIndex(-1);
    ui->tbBenaming->setText("");
    ui->tbOmschrijving->setText("");
    prd = new Producten();

    ui->btnBewerk->setEnabled(true);
    ui->btnLaadPicture->setEnabled(false);
    ui->btnNieuw->setEnabled(true);
    ui->btnOpslaan->setEnabled(false);

    ui->cbxCode->setEnabled(false);
    ui->tbBenaming->setReadOnly(true);
    ui->tbOmschrijving->setReadOnly(true);

}

AddProduct::~AddProduct()
{
    delete ui;
    delete prd;
    delete Product_Model;
}

void AddProduct::on_btnStop_clicked()
{
    this->close();
}


void AddProduct::on_btnLaadPicture_clicked()
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

void AddProduct::on_btnNieuw_clicked()
{
    prd = new Producten();
    prd->setProduct_ID(0);
    ui->cbxCode->setCurrentIndex(-1);
    ui->tbBenaming->setText(prd->getProduct_Benaming());
    ui->tbOmschrijving->setText(prd->getProduct_Omschrijving());

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

void AddProduct::on_btnOpslaan_clicked()
{
    QByteArray bytes;
    QBuffer buffer(&bytes);
    buffer.open(QIODevice::WriteOnly);
    ui->lbFoto->pixmap()->save(&buffer, "PNG");

    prd->setProduct_Code(ui->cbxCode->currentText());
    prd->setProduct_Benaming(ui->tbBenaming->text());
    prd->setProduct_Omschrijving(ui->tbOmschrijving->text());
    prd->setProduct_Afbeelding(bytes);
    prd->save();

    ui->btnBewerk->setEnabled(true);
    ui->btnLaadPicture->setEnabled(false);
    ui->btnNieuw->setEnabled(true);
    ui->btnOpslaan->setEnabled(false);

    ui->cbxCode->setEnabled(false);
    ui->tbBenaming->setReadOnly(true);
    ui->tbOmschrijving->setReadOnly(true);

    Producten::getAllProducten(Product_Model);
    ui->tvProducten->setModel(Product_Model);
}

void AddProduct::on_btnBewerk_clicked()
{
    QPixmap image;

    int _ID = ui->tvProducten->model()->data( ui->tvProducten->model()->index(ui->tvProducten->currentIndex().row(), 0 )).toInt();

    prd = new Producten(_ID);

    ui->cbxCode->setCurrentText(prd->getProduct_Code());
    ui->tbBenaming->setText(prd->getProduct_Benaming());
    ui->tbOmschrijving->setText(prd->getProduct_Omschrijving());
    image.loadFromData(prd->getProduct_Afbeelding(), "PNG");
    ui->lbFoto->setPixmap(image);

    ui->btnBewerk->setEnabled(false);
    ui->btnLaadPicture->setEnabled(true);
    ui->btnNieuw->setEnabled(false);
    ui->btnOpslaan->setEnabled(true);

    ui->cbxCode->setEnabled(true);
    ui->tbBenaming->setReadOnly(false);
    ui->tbOmschrijving->setReadOnly(false);
}



//==================================================================================================================
//   Delegate voor het tekenen van de afbeelding in de eerste colom.
//

ImageDelegate::ImageDelegate(QObject * parent)
        : QItemDelegate(parent)
{

}

void ImageDelegate::paint(QPainter * painter, const QStyleOptionViewItem & option, const QModelIndex & index) const
{
    if (index.column() == 0)
    {
        int data = index.data().toInt(); //index.data(Qt::DisplayRole).toInt();
        Producten *pr = new Producten(data);

        QPixmap pm, pn;
        pm.loadFromData(pr->getProduct_Afbeelding(), "PNG");
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
