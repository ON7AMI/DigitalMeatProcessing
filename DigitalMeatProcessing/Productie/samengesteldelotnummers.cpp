#include "samengesteldelotnummers.h"
#include "ui_samengesteldelotnummers.h"

#include <QResource>
#include <QMessageBox>
#include <QSpacerItem>
#include <QGridLayout>


SamengesteldeLotnummers::SamengesteldeLotnummers(int _bevat_id, int _lotID, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SamengesteldeLotnummers)
{
    ui->setupUi(this);
    ui->tbLotnummer->setEnabled(true);
    ui->tbArtikelnummer->setEnabled(false);
    ui->tbArtikelNaam->setEnabled(false);
    ui->tbHuidigVoorraad->setEnabled(false);
    ui->tbBenodigdeHoeveelheid->setEnabled(false);
    ui->tbNieuweVoorraad->setEnabled(false);
    ui->dtpInStock->setEnabled(false);
    ui->dtpTGV->setEnabled(false);

    ui->tbLotnummer->setText("");
    ui->tbArtikelnummer->setText("000000");
    ui->tbArtikelNaam->setText("");
    ui->tbHuidigVoorraad->setText("0");
    ui->tbBenodigdeHoeveelheid->setText("0");
    ui->tbNieuweVoorraad->setText("0");
    ui->dtpInStock->setDate(QDate::currentDate());
    ui->dtpTGV->setDate(QDate::currentDate());
    ui->btnOk->setEnabled(false);

    if(_bevat_id == 0)
    {
        ui->tbLotnummer->setFocus();
        art = new Artikelen();
        lot = new LotnummerData();
        bev = new LotnummerdBevat();
        bev->setLotnr_ID(_lotID);
    }
    else
    {
        bev = new LotnummerdBevat(_bevat_id);
        lot = new LotnummerData(bev->getBetvatLotnummer());
        art = new Artikelen(lot->getArtikel_ID());
        ui->tbLotnummer->setEnabled(false);
        ui->tbLotnummer->setText(lot->getLotnummer());
        ui->tbBenodigdeHoeveelheid->setText(QString("%1").arg(bev->getHoeveelheidIn()));;
        ui->tbBenodigdeHoeveelheid->setEnabled(true);
        ui->tbBenodigdeHoeveelheid->setFocus();
        ui->tbBenodigdeHoeveelheid->selectAll();
        ui->btnOk->setEnabled(true);
        double nu;
        nu = lot->getHoeveelheidUit() - bev->getHoeveelheidIn();
        lot->setHoeveelheidUit(nu);
        FillFields();
    }
}

SamengesteldeLotnummers::~SamengesteldeLotnummers()
{
    delete ui;
    delete lot;
    delete art;
    delete bev;
}

void SamengesteldeLotnummers::on_btnOk_clicked()
{
    double geb;
    geb = ui->tbBenodigdeHoeveelheid->text().toDouble();
    lot->setHoeveelheidUit(lot->getHoeveelheidUit() + geb);
    lot->save();

    bev->setBevatLotnummer(lot->getLotnummer_id());
    bev->setHoeveelheidIn(ui->tbBenodigdeHoeveelheid->text().toDouble());
    bev->save();

    this->setResult(QDialog::Accepted);
    this->close();
}

void SamengesteldeLotnummers::on_btnCancel_clicked()
{
    this->setResult(QDialog::Rejected);
    this->close();
}

void SamengesteldeLotnummers::on_tbLotnummer_editingFinished()
{
    if((!ui->tbLotnummer->text().trimmed().isEmpty()) )
    {
        lot = new LotnummerData(ui->tbLotnummer->text().trimmed());
        if (lot->getLotnummer_id() == 0)
        {
            ui->tbLotnummer->setText("");
            QMessageBox msgBox;
            msgBox.setText("<strong>Onbekend Lotnummer !</strong>");
            msgBox.setInformativeText("Het ingegeven lotnummer is onbekend,\ngelieve enkel bestaande lotnummers op te geven.");
            msgBox.setStandardButtons(QMessageBox::Cancel);
            msgBox.setDefaultButton(QMessageBox::Cancel);
            msgBox.setIcon(QMessageBox::Critical);
            msgBox.setWindowTitle("Opgepast !");
            //msgBox.setStyleSheet("min-width: 150px;");
            QSpacerItem *hs = new QSpacerItem(400, 0, QSizePolicy::Minimum, QSizePolicy::Expanding);
            QGridLayout *gl = (QGridLayout*)msgBox.layout();
            gl->addItem(hs, gl->rowCount(), 0, 1, gl->columnCount());
            msgBox.exec();

            ui->tbLotnummer->setFocus();
        }
        else
        {
            if (lot->getLotnummer_id() == bev->getLotnr_ID())
            {
                ui->tbLotnummer->setText("");
                QMessageBox msgBox;
                msgBox.setText("<strong>Een lotnummer kan geen deel zijn van zichzelf !</strong>");
                msgBox.setInformativeText("Het ingegeven lotnummer is hetzelfde als het basis lotnummer,\ngelieve enkel lotnummers op te geven die verschillend zijn van het basis lotnummer.");
                msgBox.setStandardButtons(QMessageBox::Cancel);
                msgBox.setDefaultButton(QMessageBox::Cancel);
                msgBox.setIcon(QMessageBox::Critical);
                msgBox.setWindowTitle("Opgepast !");
                //msgBox.setStyleSheet("min-width: 150px;");
                QSpacerItem *hs = new QSpacerItem(400, 0, QSizePolicy::Minimum, QSizePolicy::Expanding);
                QGridLayout *gl = (QGridLayout*)msgBox.layout();
                gl->addItem(hs, gl->rowCount(), 0, 1, gl->columnCount());
                msgBox.exec();

                ui->tbLotnummer->setFocus();
            }
            else
            {
                FillFields();
                ui->tbLotnummer->setEnabled(false);
                ui->tbBenodigdeHoeveelheid->setEnabled(true);
                ui->tbBenodigdeHoeveelheid->setFocus();
                ui->tbBenodigdeHoeveelheid->selectAll();
                ui->btnOk->setEnabled(true);
            }
        }
    }
}

void SamengesteldeLotnummers::FillFields()
{
    double hv = lot->getHoeveelheidIn() - lot->getHoeveelheidUit();
    double nod = ui->tbBenodigdeHoeveelheid->text().toDouble();
    double nv = hv - nod;
    art = new Artikelen(lot->getArtikel_ID());
    ui->tbArtikelnummer->setText(art->getCode());
    ui->tbArtikelNaam->setText(art->getBenaming());
    ui->dtpInStock->setDate(lot->getDatumInstock());
    ui->dtpTGV->setDate(lot->getDatumEigTgv());
    if (lot->getDatumEigTgv() <= QDate::currentDate())
    {
        ui->lbTGV->setStyleSheet("color: rgb(255, 0, 0); font-weight: bold;");
    }
    else
    {
        ui->lbTGV->setStyleSheet("color: rgb(0, 0, 0); font-weight: normal;");
    }
    ui->tbHuidigVoorraad->setText(QString("%1").arg(hv));
    ui->tbNieuweVoorraad->setText(QString("%1").arg(nv));
}

void SamengesteldeLotnummers::MeldGetalError()
{
    QMessageBox msgBox;
    msgBox.setText("<strong>Foutieve ingave !</strong>");
    msgBox.setInformativeText("U mag hier enkel een geldig getal ingeven.\n Getallen en het correcte decimaal teken.");
    msgBox.setStandardButtons(QMessageBox::Cancel);
    msgBox.setDefaultButton(QMessageBox::Cancel);
    msgBox.setIcon(QMessageBox::Critical);
    msgBox.setWindowTitle("Opgepast !");
    //msgBox.setStyleSheet("min-width: 150px;");
    QSpacerItem *hs = new QSpacerItem(400, 0, QSizePolicy::Minimum, QSizePolicy::Expanding);
    QGridLayout *gl = (QGridLayout*)msgBox.layout();
    gl->addItem(hs, gl->rowCount(), 0, 1, gl->columnCount());
    msgBox.exec();
}

void SamengesteldeLotnummers::on_tbBenodigdeHoeveelheid_editingFinished()
{
    double geb;
    bool ok;
    geb = ui->tbBenodigdeHoeveelheid->text().toDouble(&ok);
    if (!ok)
    {
        MeldGetalError();
        ui->tbBenodigdeHoeveelheid->setText("0.0");
        ui->tbBenodigdeHoeveelheid->selectAll();
        ui->tbBenodigdeHoeveelheid->setFocus();
    }
    else
    {
        double hv = lot->getHoeveelheidIn() - lot->getHoeveelheidUit();
        double nv = hv - geb;
        ui->tbNieuweVoorraad->setText(QString("%1").arg(nv));
    }
}
