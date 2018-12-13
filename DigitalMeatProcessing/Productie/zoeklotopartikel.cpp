#include "zoeklotopartikel.h"
#include "ui_zoeklotopartikel.h"
#include "ArtikelBeheer/artikelen.h"
#include "ArtikelBeheer/producten.h"
#include "ArtikelBeheer/soorten.h"
#include "ArtikelBeheer/details.h"
#include "ArtikelBeheer/specificaties.h"

#include <QString>
#include <QtCore>
#include <QtSql>
#include <QSqlDatabase>
#include <QSettings>
#include <QApplication>
#include <QDialog>
#include <QResource>
#include <QMessageBox>
#include <QSpacerItem>
#include <QGridLayout>



ZoekLotOpArtikel::ZoekLotOpArtikel(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ZoekLotOpArtikel)
{
    ui->setupUi(this);
    ClearArtikelFields();
    CurrentArt = 0;
    CurLot_ID = 0;
    FillProductkeuze();
}

ZoekLotOpArtikel::~ZoekLotOpArtikel()
{
    delete ui;
    delete art;
    delete prd_model;
    delete srt_model;
    delete det_model;
    delete spec_model;
    delete lot_model;
}

void ZoekLotOpArtikel::FillProductkeuze()
{
    prd_model = new QSqlQueryModel();
    Producten::getProductenKeuze(prd_model);
    ui->cbxProduct->setModel(prd_model);
    ui->cbxProduct->setModelColumn(1);
}

void ZoekLotOpArtikel::FillSoortkeuze()
{
    srt_model = new QSqlQueryModel();
    Soorten::getSoortenKeuze(srt_model, CurPrd_ID);
    ui->cbxSoort->setModel((srt_model));
    ui->cbxSoort->setModelColumn(1);
}

void ZoekLotOpArtikel::FillDetailKeuze()
{
    det_model = new QSqlQueryModel();
    Details::getDetailKeuze(det_model, CurPrd_ID, CurSrt_ID);
    ui->cbxDetail->setModel(det_model);
    ui->cbxDetail->setModelColumn(1);

}

void ZoekLotOpArtikel::FillSpecificatieKeuze()
{
    spec_model = new QSqlQueryModel();
    Specificaties::getSpecificatieKeuze(spec_model, CurPrd_ID, CurSrt_ID, CurDet_ID);
    ui->cbxSpecificatie->setModel(spec_model);
    ui->cbxSpecificatie->setModelColumn(1);
}


void ZoekLotOpArtikel::on_btnOvernemen_clicked()
{

    CurLot_ID = ui->tvLotnummers->model()->index( ui->tvLotnummers->currentIndex().row() , 0).data().toInt();
    this->setResult(QDialog::Accepted);
    this->close();
}

void ZoekLotOpArtikel::on_btnAnnuleren_clicked()
{
    CurLot_ID = 0;
    this->setResult(QDialog::Rejected);
    this->close();
}

int ZoekLotOpArtikel::getLotID()
{
    return CurLot_ID;
}

void ZoekLotOpArtikel::on_cbxProduct_currentIndexChanged(int index)
{
    QString artnr = ui->tbArtikelnummer->text();
    int _prod_id = ui->cbxProduct->model()->data( ui->cbxProduct->model()->index(index, 0 )).toInt(); //ui->cbxProduct->currentIndex()
    CurPrd_ID = _prod_id;
    // Aanpassen van het artikel nummer
    Producten prod(_prod_id);
    artnr = artnr.replace(0,1,prod.getProduct_Code());
    ui->tbArtikelnummer->setText(artnr);

    // Aanpassen Soort-Keuzelijst
    FillSoortkeuze();
}

void ZoekLotOpArtikel::on_cbxSoort_currentIndexChanged(int index)
{
    QString artnr = ui->tbArtikelnummer->text();
    int _srt_id = ui->cbxSoort->model()->data( ui->cbxSoort->model()->index(index, 0 )).toInt();
    CurSrt_ID = _srt_id;
    // Aanpassen van het artikel nummer
    Soorten srt(_srt_id);
    artnr = artnr.replace(2,1,srt.getSoortCode());
    ui->tbArtikelnummer->setText(artnr);

    // Aanpassen Detail-Keuzelijst
    FillDetailKeuze();
}

void ZoekLotOpArtikel::on_cbxDetail_currentIndexChanged(int index)
{
    QString artnr = ui->tbArtikelnummer->text();
    int _det_id = ui->cbxDetail->model()->data( ui->cbxDetail->model()->index(index, 0 )).toInt();
    CurDet_ID = _det_id;
    // Aanpassen van het artikel nummer
    Details det(_det_id);
    artnr = artnr.replace(4,2,det.getDetailCode());
    ui->tbArtikelnummer->setText(artnr);

    // Aanpassen Ras-Keuzelijst
    FillSpecificatieKeuze();
}

void ZoekLotOpArtikel::on_cbxSpecificatie_currentIndexChanged(int index)
{
    QString artnr = ui->tbArtikelnummer->text();
    int _spec_id = ui->cbxSpecificatie->model()->data( ui->cbxSpecificatie->model()->index(index, 0 )).toInt();
    CurSpec_ID = _spec_id;
    // Aanpassen van het artikel nummer
    Specificaties spec(_spec_id);
    artnr = artnr.replace(7,2,spec.getSpecificatieCode());
    ui->tbArtikelnummer->setText(artnr);
}

void ZoekLotOpArtikel::on_btnZoek_Art_clicked()
{
    QString code;
    int id;
    code = ui->tbArtikelnummer->text().remove(char('.'));
    id = Artikelen::getArtikelIDByCode(code);
    if (id == 0)
    {
        // Artikel onbekend, wil je het aanmaken
        QMessageBox msgBox;
        msgBox.setText("<strong>Onbekend Artikel !</strong>");
        msgBox.setInformativeText("Artikel onbekend");
        msgBox.setStandardButtons(QMessageBox::Cancel);
        msgBox.setDefaultButton(QMessageBox::Cancel);
        msgBox.setIcon(QMessageBox::Warning);
        msgBox.setWindowTitle("Opgepast !");
        QSpacerItem *hs = new QSpacerItem(400, 0, QSizePolicy::Minimum, QSizePolicy::Expanding);
        QGridLayout *gl = (QGridLayout*)msgBox.layout();
        gl->addItem(hs, gl->rowCount(), 0, 1, gl->columnCount());
        msgBox.exec();
        ClearArtikelFields();
    }
    else
    {
        art = new Artikelen(id);
        FillArtikelFields();
        CurrentArt = id;
        lot_model =  new QSqlQueryModel();
        LotnummerData::getLotnrByArticle(id, lot_model);

        ui->tvLotnummers->setModel(lot_model);
        ui->tvLotnummers->setColumnHidden(0,true);
        ui->tvLotnummers->setColumnWidth(1,100);
    }
}

void ZoekLotOpArtikel::ClearArtikelFields()
{
    ui->tbArtikelnummer->setText("000000");
    ui->tbArtikelNaam->setText("");
    ui->cbxProduct->setCurrentIndex(0);
}

void ZoekLotOpArtikel::FillArtikelFields()
{
    ui->tbArtikelNaam->setText(art->getBenaming());
}

void ZoekLotOpArtikel::on_btnWis_Art_clicked()
{
    ClearArtikelFields();
}

void ZoekLotOpArtikel::on_tbArtikelnummer_editingFinished()
{
    if (!AdjustSamenstelling(ui->tbArtikelnummer->text().remove(char('.'))))
    {
        QMessageBox msgBox;
        msgBox.setText("<strong>Onbekend Artikel !</strong>");
        msgBox.setInformativeText("De onderliggende categorieën van dit artikel bestaan niet.\nU moet die eerst aanmaken.");
        msgBox.setStandardButtons(QMessageBox::Cancel);
        msgBox.setDefaultButton(QMessageBox::Cancel);
        msgBox.setIcon(QMessageBox::Critical);
        msgBox.setWindowTitle("Opgepast !");
        //msgBox.setStyleSheet("min-width: 150px;");
        QSpacerItem *hs = new QSpacerItem(400, 0, QSizePolicy::Minimum, QSizePolicy::Expanding);
        QGridLayout *gl = (QGridLayout*)msgBox.layout();
        gl->addItem(hs, gl->rowCount(), 0, 1, gl->columnCount());
        msgBox.exec();
        ui->tbArtikelnummer->setText("000000");
        AdjustSamenstelling("000000");
    }
    if (ui->tbArtikelnummer->text() != "0.0.00.00")
    {
        on_btnZoek_Art_clicked();
    }
}

bool ZoekLotOpArtikel::AdjustSamenstelling(QString _code)
{
    bool gelukt = true;
    int index;
    QString Zoek;

    Zoek = _code.mid(0,1); Zoek.append(".");
    index = ui->cbxProduct->findText(Zoek, Qt::MatchStartsWith);
    if (index != -1)
    {
        ui->cbxProduct->setCurrentIndex(index);
        Zoek = _code.mid(1,1); Zoek.append(".");
        index = ui->cbxSoort->findText(Zoek, Qt::MatchStartsWith);
        if (index != -1)
        {
            ui->cbxSoort->setCurrentIndex(index);
            Zoek = _code.mid(2,2); Zoek.append(".");
            index = ui->cbxDetail->findText(Zoek, Qt::MatchStartsWith);
            if (index != -1)
            {
                ui->cbxDetail->setCurrentIndex(index);
                Zoek = _code.mid(4,2); Zoek.append(".");
                index = ui->cbxSpecificatie->findText(Zoek, Qt::MatchStartsWith);
                if (index != -1)
                {
                    ui->cbxSpecificatie->setCurrentIndex(index);
                }
                else
                {
                    gelukt = false;
                }
            }
            else
            {
                gelukt = false;
            }
        }
        else
        {
            gelukt = false;
        }
    }
    else
    {
        gelukt = false;
    }
    return gelukt;
}




void ZoekLotOpArtikel::on_tvLotnummers_pressed(const QModelIndex &index)
{
    qDebug() << "Pressed";
    if ( QApplication::mouseButtons() == Qt::RightButton)
    {
        qDebug() << "Right";
        QMessageBox msgBox;
        msgBox.setText("<strong>Opwerking lotnumme !</strong>");
        msgBox.setInformativeText("U gaat de rest van de voorraad als afval verwerken\nen het lot als niet actief markeren.\nIS HET DAT WAT U WENST TE DOEN ?");
        msgBox.setStandardButtons(QMessageBox::Cancel | QMessageBox::Ok);
        msgBox.setDefaultButton(QMessageBox::Cancel);
        msgBox.setIcon(QMessageBox::Question);
        msgBox.setWindowTitle("Opgepast !");
        //msgBox.setStyleSheet("min-width: 150px;");
        QSpacerItem *hs = new QSpacerItem(400, 0, QSizePolicy::Minimum, QSizePolicy::Expanding);
        QGridLayout *gl = (QGridLayout*)msgBox.layout();
        gl->addItem(hs, gl->rowCount(), 0, 1, gl->columnCount());
        if (msgBox.exec() == QMessageBox::Ok)
        {
            int Lotnr_id = 0;
            int row = index.row();
            QSqlRecord rec = lot_model->record(row);
            Lotnr_id = rec.value(0).toInt();
            LotnummerData* ld = new LotnummerData(Lotnr_id);
            ld->setHoeveelheidAfval(ld->getHoeveelheidIn() - ld->getHoeveelheidUit());
            ld->setActief(false);
            ld->setDatumUitstock(QDate::currentDate());
            ld->setLocatie_ID(16);
            ld->save();
        }
    }
    else
    {
        qDebug() << "Left";
    }
}
