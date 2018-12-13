#include "addconcurentprijs.h"
#include "ui_addconcurentprijs.h"
#include "artikelen.h"
#include "prijzenconcurentie.h"
#include "Relaties/findrelaties.h"
#include "CommonObjects/postcodes.h"

#include <QResource>
#include <QMessageBox>
#include <QSpacerItem>
#include <QGridLayout>

AddConcurentPrijs::AddConcurentPrijs(int _id, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddConcurentPrijs)
{
    QResource::registerResource("../Resources/myresource.qrc");
    ui->setupUi(this);

    Artikelen_ID = _id;
    ui->lbArtNr->setText("");
    ui->dtpDatumAankoop->setDate(QDate::currentDate());
    FillTabel();

    ui->tbNummer->setText("");
    ui->tbNaam->setText("");
    ui->tbStraat->setText("");
    ui->tbGemeente->setText("");
    ui->tbEMail->setText("");
    ui->tbPrijs->setText("");

    ui->tbNummer->setEnabled(false);
    ui->tbNaam->setEnabled(false);
    ui->tbStraat->setEnabled(false);
    ui->tbGemeente->setEnabled(false);
    ui->tbEMail->setEnabled(false);
    ui->dtpDatumAankoop->setEnabled(false);
    ui->tbPrijs->setEnabled(false);

    ui->btnDelete->setEnabled(true);
    ui->btnEdit->setEnabled(true);
    ui->btnNew->setEnabled(true);
    ui->btnSave->setEnabled(false);
    ui->btnZoek->setEnabled(false);
    ui->btnWis->setEnabled(true);
}

void AddConcurentPrijs::FillTabel()
{
    tv_model = new QSqlQueryModel();
    PrijzenConcurentie::getPrijzenPerArtikel(tv_model, Artikelen_ID);
    tv_model->setHeaderData(2, Qt::Horizontal, tr("Dat.Aank."));
    tv_model->setHeaderData(3, Qt::Horizontal, tr("Naam Concurent"));
    tv_model->setHeaderData(4, Qt::Horizontal, tr("Prijs per eenheid"));

    ui->tvPrijzen->setModel(tv_model);

    ui->tvPrijzen->hideColumn(0);
    ui->tvPrijzen->hideColumn(1);

    ui->tvPrijzen->setColumnWidth(2,80);
    ui->tvPrijzen->setColumnWidth(3,300);
    ui->tvPrijzen->setColumnWidth(4,140);

    ui->tvPrijzen->setAlternatingRowColors(true);
    if (ui->tvPrijzen->model()->rowCount() > 0)
    {
        ui->tvPrijzen->selectRow(0);
    }


}

AddConcurentPrijs::~AddConcurentPrijs()
{
    delete ui;
    delete tv_model;
    delete rel;
    delete pc;
}

void AddConcurentPrijs::on_btnStop_clicked()
{
    this->close();
}

void AddConcurentPrijs::on_btnNew_clicked()
{
    pc = new PrijzenConcurentie();
    pc->setArtikel_ID(Artikelen_ID);

    ui->tbNummer->setEnabled(true);
    ui->tbNaam->setEnabled(true);
    ui->tbStraat->setEnabled(true);
    ui->tbGemeente->setEnabled(true);
    ui->tbEMail->setEnabled(true);
    ui->dtpDatumAankoop->setEnabled(false);
    ui->tbPrijs->setEnabled(false);


    ui->btnDelete->setEnabled(false);
    ui->btnEdit->setEnabled(false);
    ui->btnNew->setEnabled(false);
    ui->btnSave->setEnabled(false);
    ui->btnZoek->setEnabled(true);
    ui->btnWis->setEnabled(true);
}

void AddConcurentPrijs::on_btnZoek_clicked()
{
    bool ok;
    int rel_id;

    rel_id = ui->tbNummer->text().toInt(&ok);
    if (ok)
    {
        rel = new Relaties(rel_id);
        if (rel->getRelatie_ID() == 0)
        {
            QMessageBox *msgBox = new QMessageBox(this);
            msgBox->setText("Relatie - Fout");
            msgBox->setWindowModality(Qt::WindowModal);
            msgBox->setInformativeText("Relatie met dit nummer bestaat niet");
            msgBox->setStandardButtons(QMessageBox::Ok);
            QSpacerItem *hs = new QSpacerItem(400, 0, QSizePolicy::Minimum, QSizePolicy::Expanding);
            QGridLayout *gl = (QGridLayout*)msgBox->layout();
            gl->addItem(hs, gl->rowCount(), 0, 1, gl->columnCount());

            msgBox->exec();
        }
        else
        {
            ui->tbNaam->setText(rel->getNaam() + " " + rel->getVoornaam());
            ui->tbStraat->setText(rel->getAdres());
            ui->tbGemeente->setText(Postcodes::getGemeente(rel->getGemeente_ID()));
            ui->tbEMail->setText(rel->getEMail_1());

            pc->setRelatie_ID(rel->getRelatie_ID());

            ui->tbNummer->setEnabled(false);
            ui->tbNaam->setEnabled(false);
            ui->tbStraat->setEnabled(false);
            ui->tbGemeente->setEnabled(false);
            ui->tbEMail->setEnabled(false);
            ui->dtpDatumAankoop->setEnabled(true);
            ui->tbPrijs->setEnabled(true);


            ui->btnDelete->setEnabled(false);
            ui->btnEdit->setEnabled(false);
            ui->btnNew->setEnabled(false);
            ui->btnSave->setEnabled(true);
            ui->btnZoek->setEnabled(false);
            ui->btnWis->setEnabled(false);

        }
    }
    else
    {
        FindRelaties *fr = new FindRelaties(
                    ui->tbNaam->text(),
                    ui->tbStraat->text(),
                    ui->tbGemeente->text(),
                    ui->tbEMail->text());
        fr->exec();
        rel_id = fr->getID();
        rel = new Relaties(rel_id);
        if (rel->getRelatie_ID() != 0)
        {
            ui->tbNummer->setText( QString("%1").arg(rel->getRelatie_ID()));
            ui->tbNaam->setText(rel->getNaam() + " " + rel->getVoornaam());
            ui->tbStraat->setText(rel->getAdres());
            ui->tbGemeente->setText(Postcodes::getGemeente(rel->getGemeente_ID()));
            ui->tbEMail->setText(rel->getEMail_1());

            pc->setRelatie_ID(rel->getRelatie_ID());

            ui->tbNummer->setEnabled(false);
            ui->tbNaam->setEnabled(false);
            ui->tbStraat->setEnabled(false);
            ui->tbGemeente->setEnabled(false);
            ui->tbEMail->setEnabled(false);
            ui->dtpDatumAankoop->setEnabled(true);
            ui->tbPrijs->setEnabled(true);


            ui->btnDelete->setEnabled(false);
            ui->btnEdit->setEnabled(false);
            ui->btnNew->setEnabled(false);
            ui->btnSave->setEnabled(true);
            ui->btnZoek->setEnabled(false);
            ui->btnWis->setEnabled(false);

        }
    }
}

void AddConcurentPrijs::on_btnSave_clicked()
{
    double prijs = 0;
    bool ok = false;
    prijs = ui->tbPrijs->text().toDouble(&ok);
    if (ok)
    {
        // inlezen
        //pc->setRelatie_ID();
        pc->setArtikel_ID(Artikelen_ID);
        pc->setDatumAankoop(ui->dtpDatumAankoop->date());
        pc->setPrijs(prijs);
        pc->setDatumInvoer(QDate::currentDate());
        pc->save();
    }
    else
    {
        QMessageBox msgBox;
        msgBox.setText("<strong>Foutieve ingave Prijs!</strong>");
        msgBox.setInformativeText("U mag hier enkel een geldige prijs ingeven.\n Enkel getallen en het decimaal teken.");
        msgBox.setStandardButtons(QMessageBox::Cancel);
        msgBox.setDefaultButton(QMessageBox::Cancel);
        msgBox.setIcon(QMessageBox::Critical);
        msgBox.setWindowTitle("Opgepast !");
        QSpacerItem *hs = new QSpacerItem(400, 0, QSizePolicy::Minimum, QSizePolicy::Expanding);
        QGridLayout *gl = (QGridLayout*)msgBox.layout();
        gl->addItem(hs, gl->rowCount(), 0, 1, gl->columnCount());
        msgBox.exec();
        ui->tbPrijs->setFocus();
        ui->tbPrijs->selectAll();
    }
    PrijzenConcurentie::getPrijzenPerArtikel(tv_model, Artikelen_ID);
    ui->tvPrijzen->setModel(tv_model);
    if (ui->tvPrijzen->model()->rowCount() > 0)
    {
        ui->tvPrijzen->selectRow(0);
    }

    ui->tbNummer->setText("");
    ui->tbNaam->setText("");
    ui->tbStraat->setText("");
    ui->tbGemeente->setText("");
    ui->tbEMail->setText("");
    ui->tbPrijs->setText("");

    ui->tbNummer->setEnabled(false);
    ui->tbNaam->setEnabled(false);
    ui->tbStraat->setEnabled(false);
    ui->tbGemeente->setEnabled(false);
    ui->tbEMail->setEnabled(false);
    ui->dtpDatumAankoop->setEnabled(false);
    ui->tbPrijs->setEnabled(false);

    ui->btnDelete->setEnabled(true);
    ui->btnEdit->setEnabled(true);
    ui->btnNew->setEnabled(true);
    ui->btnSave->setEnabled(false);
    ui->btnZoek->setEnabled(false);
    ui->btnWis->setEnabled(true);

}

void AddConcurentPrijs::on_btnEdit_clicked()
{
    int _ID = ui->tvPrijzen->model()->data( ui->tvPrijzen->model()->index(ui->tvPrijzen->currentIndex().row(), 0 )).toInt();
    pc = new PrijzenConcurentie(_ID);
    rel = new Relaties(pc->getRelatie_ID());
    ui->tbNummer->setText( QString("%1").arg(rel->getRelatie_ID()));
    ui->tbNaam->setText(rel->getNaam() + " " + rel->getVoornaam());
    ui->tbStraat->setText(rel->getAdres());
    ui->tbGemeente->setText(Postcodes::getGemeente(rel->getGemeente_ID()));
    ui->tbEMail->setText(rel->getEMail_1());
    ui->dtpDatumAankoop->setDate(pc->getDatumAankoop());
    ui->tbPrijs->setText(QString("%1").arg(pc->getPrijs()));

    ui->tbNummer->setEnabled(true);
    ui->tbNaam->setEnabled(true);
    ui->tbStraat->setEnabled(true);
    ui->tbGemeente->setEnabled(true);
    ui->tbEMail->setEnabled(true);
    ui->dtpDatumAankoop->setEnabled(true);
    ui->tbPrijs->setEnabled(true);


    ui->btnDelete->setEnabled(false);
    ui->btnEdit->setEnabled(false);
    ui->btnNew->setEnabled(false);
    ui->btnSave->setEnabled(true);
    ui->btnZoek->setEnabled(true);
    ui->btnWis->setEnabled(true);

}

void AddConcurentPrijs::on_btnWis_clicked()
{
    ui->tbNummer->setText("");
    ui->tbNaam->setText("");
    ui->tbStraat->setText("");
    ui->tbGemeente->setText("");
    ui->tbEMail->setText("");
}

void AddConcurentPrijs::on_btnDelete_clicked()
{
    QMessageBox msgBox;
    msgBox.setText("<strong>Gegevens Wissen!</strong>");
    msgBox.setInformativeText("Wilt u zeker deze gegevens wissen?");
    msgBox.setStandardButtons(QMessageBox::No | QMessageBox::Yes);
    msgBox.setDefaultButton(QMessageBox::No);
    msgBox.setIcon(QMessageBox::Critical);
    msgBox.setWindowTitle("Opgepast !");
    QSpacerItem *hs = new QSpacerItem(400, 0, QSizePolicy::Minimum, QSizePolicy::Expanding);
    QGridLayout *gl = (QGridLayout*)msgBox.layout();
    gl->addItem(hs, gl->rowCount(), 0, 1, gl->columnCount());
    if (msgBox.exec() == QMessageBox::Yes)
    {
        if (ui->tvPrijzen->model()->rowCount() > 0)
        {
            int _ID = ui->tvPrijzen->model()->data( ui->tvPrijzen->model()->index(ui->tvPrijzen->currentIndex().row(), 0 )).toInt();
            PrijzenConcurentie::deletePrijs(_ID);
        }
        PrijzenConcurentie::getPrijzenPerArtikel(tv_model, Artikelen_ID);
        ui->tvPrijzen->setModel(tv_model);
        if (ui->tvPrijzen->model()->rowCount() > 0)
        {
            ui->tvPrijzen->selectRow(0);
        }
    }
}
