#include "addallergenen.h"
#include "ui_addallergenen.h"
#include "allergenen.h"

#include <QBuffer>
#include <QFileDialog>
#include <QModelIndex>
#include <QPushButton>
#include <QTableView>

//======================================================================================================================
//   Beheren aan aanmaken van Allergenen
//


AddAllergenen::AddAllergenen(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddAllergenen)
{
    ui->setupUi(this);

    this->setWindowTitle("Beheer van Allergenen.");

    Allergeen_Model = new QSqlQueryModel();
    Allergenen::getAllAllergeen(Allergeen_Model);
    Allergeen_Model->setHeaderData(0, Qt::Horizontal, tr("Afbeelding"));
    Allergeen_Model->setHeaderData(1, Qt::Horizontal, tr("Benaming"));
    Allergeen_Model->setHeaderData(2, Qt::Horizontal, tr("Beschrijving"));
    //Allergeen_Model->
    ui->tvAllergenen->setModel(Allergeen_Model);
    ui->tvAllergenen->setColumnWidth(0,80);
    ui->tvAllergenen->setColumnWidth(1,100);
    ui->tvAllergenen->setColumnWidth(2,300);

    ui->tvAllergenen->setAlternatingRowColors(true);
    ui->tvAllergenen->setItemDelegate(new Al_ImageDelegate(this));

    ui->tbBenaming->setText("");
    ui->tbOmschrijving->setPlainText("");
    al = new Allergenen();

    ui->btnBewerk->setEnabled(true);
    ui->btnLaadPicture->setEnabled(false);
    ui->btnNieuw->setEnabled(true);
    ui->btnOpslaan->setEnabled(false);

    ui->tbBenaming->setReadOnly(true);
    ui->tbOmschrijving->setReadOnly(true);

}

AddAllergenen::~AddAllergenen()
{
    delete ui;
    delete al;
    delete Allergeen_Model;
}

void AddAllergenen::on_btnLaadPicture_clicked()
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

void AddAllergenen::on_btnStop_clicked()
{
     this->close();
}
void AddAllergenen::on_btnNieuw_clicked()
{
    al = new Allergenen();
    al->setAllergeen_ID(0);
    ui->tbBenaming->setText(al->getAllergeen_Benaming());
    ui->tbOmschrijving->setPlainText(al->getAllergeen_Omschrijving());

    ui->btnBewerk->setEnabled(false);
    ui->btnLaadPicture->setEnabled(true);
    ui->btnNieuw->setEnabled(false);
    ui->btnOpslaan->setEnabled(true);

    ui->tbBenaming->setReadOnly(false);
    ui->tbOmschrijving->setReadOnly(false);

    QPixmap image;
    ui->lbFoto->setPixmap(image);

}

void AddAllergenen::on_btnOpslaan_clicked()
{
    QByteArray bytes;
    QBuffer buffer(&bytes);
    buffer.open(QIODevice::WriteOnly);
    ui->lbFoto->pixmap()->save(&buffer, "PNG");

    al->setAllergeen_Benaming(ui->tbBenaming->text());
    al->setAllergeen_Omschrijving(ui->tbOmschrijving->toPlainText());
    al->setAllergeen_Afbeelding(bytes);
    al->save();

    ui->btnBewerk->setEnabled(true);
    ui->btnLaadPicture->setEnabled(false);
    ui->btnNieuw->setEnabled(true);
    ui->btnOpslaan->setEnabled(false);

    ui->tbBenaming->setReadOnly(true);
    ui->tbOmschrijving->setReadOnly(true);

    Allergenen::getAllAllergeen(Allergeen_Model);
    ui->tvAllergenen->setModel(Allergeen_Model);

}

void AddAllergenen::on_btnBewerk_clicked()
{
    QPixmap image;

    int _ID = ui->tvAllergenen->model()->data( ui->tvAllergenen->model()->index(ui->tvAllergenen->currentIndex().row(), 0 )).toInt();

    al = new Allergenen(_ID);
    ui->tbBenaming->setText(al->getAllergeen_Benaming());
    ui->tbOmschrijving->setPlainText(al->getAllergeen_Omschrijving());
    image.loadFromData(al->getAllergeen_Afbeelding(), "PNG");
    ui->lbFoto->setPixmap(image);

    ui->btnBewerk->setEnabled(false);
    ui->btnLaadPicture->setEnabled(true);
    ui->btnNieuw->setEnabled(false);
    ui->btnOpslaan->setEnabled(true);

    ui->tbBenaming->setReadOnly(false);
    ui->tbOmschrijving->setReadOnly(false);

}

//==================================================================================================================
//   Delegate voor het tekenen van de afbeelding in de eerste colom.
//

Al_ImageDelegate::Al_ImageDelegate(QObject * parent)
        : QItemDelegate(parent)
{

}

void Al_ImageDelegate::paint(QPainter * painter, const QStyleOptionViewItem & option, const QModelIndex & index) const
{
    if (index.column() == 0)
    {
        int data = index.data().toInt(); //index.data(Qt::DisplayRole).toInt();
        Allergenen *pr = new Allergenen(data);

        QPixmap pm, pn;
        pm.loadFromData(pr->getAllergeen_Afbeelding(), "PNG");
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
