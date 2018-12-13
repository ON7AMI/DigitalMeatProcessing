//======================================================================================================
//
//                        ==== ON7AMI = Project: Digital Meat Processing ====
//
//======================================================================================================
//
//   Doel:    Main Window - Startpagina globaal beheer
//   File:    MainWindow.cpp
//   Created: 20/07/2015
//   By:      Jean Paul Mertens  (jpm)
//   email:   jpm@on7ami.be
//
//-------------------------------------------------------------------------------------------------------
//
//  Version |  Date      |  By    |  Description / Changes
// ---------+------------+--------+-----------------------------------------------------------------------
//  1.0.0   | 26/07/2015 |  JPM   |  Original
//          |            |        |
//
//--------------------------------------------------------------------------------------------------------
//
//  Interface:
//  ----------
//
// -Menu's:
//
//
//
//
// -Statusbar's:
//
//
// -Tabpages:
//
//
// -Fields:
//
//
//
// -Data used:
//
//
//
//========================================================================================================



#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "dlgabout.h"
#include "dlgsettings.h"
#include "Relaties/relatiefiche.h"
#include "ArtikelBeheer/artikelnummerbeheer.h"
#include "ArtikelBeheer/addallergenen.h"
#include "ArtikelBeheer/leveringenlijst.h"
#include "Productie/lotnummers.h"
#include "Weegschaal/bedienscherm.h"
#include "Weegschaal/kassa.h"
#include "Weegschaal/klantenscherm.h"
#include "Rapportering/dagrapport.h"
#include "Facturatie/factuurfiche.h"
#include "Facturatie/factuurkeuzelijst.h"


#include <QCoreApplication>
#include <QString>
#include <QStringList>
#include <QMessageBox>
#include <QSpacerItem>
#include <QGridLayout>
#include <QInputDialog>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{


    ui->setupUi(this);
    this->setWindowTitle("Digital Meat Processing");
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_action_Afsluiten_triggered()
{
    this->close();
}

void MainWindow::on_action_Over_DMP_triggered()
{
    dlgAbout* dlg = new dlgAbout();
    dlg->exec();
    delete dlg;
}

void MainWindow::on_actionInstellingen_triggered()
{
    dlgSettings* dlg = new dlgSettings();
    dlg->exec();
    delete dlg;
}

void MainWindow::on_actionRelaties_triggered()
{
    RelatieFiche* win = new RelatieFiche(RelatieFiche::OpenAsFind);
    win->show();

}

void MainWindow::on_actionArtikelnummers_triggered()
{
    ArtikelnummerBeheer *art = new ArtikelnummerBeheer();
    art->show();
}

void MainWindow::on_actionAllergenen_triggered()
{
    AddAllergenen *al_win = new AddAllergenen();
    al_win->show();
}

void MainWindow::on_actionLotnummers_triggered()
{
    Lotnummers *LotNr = new Lotnummers();
    LotNr->show();
}

void MainWindow::startBalans()
{
    on_actionStart_weegschaal_triggered();
}

void MainWindow::on_actionStart_weegschaal_triggered()
{
    BedienScherm *ws = new BedienScherm();
    ws->show();
}

void MainWindow::startKassa()
{
    on_actionStart_Kassa_triggered();
}

void MainWindow::on_actionStart_Kassa_triggered()
{
    Kassa* ka = new Kassa();
    ka->show();
}

void MainWindow::on_actionDagrapport_triggered()
{
   Dagrapport* dr = new Dagrapport();
   dr->exec();
   //delete dr;
}

void MainWindow::on_actionPrikkes_maken_triggered()
{
    Artikelen::ExportPrikkers();
    QProcess::execute("glabels-3 /usr/DMP/Prikkers.glabels");
    QMessageBox msgBox;
    msgBox.setText("<strong>Afdrukken Prikkers !</strong>");
    msgBox.setInformativeText("Is het afdrukken goed verlopen, \nmogen de vlaggetjes worden gewist");
    msgBox.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
    msgBox.setDefaultButton(QMessageBox::Yes);
    msgBox.setIcon(QMessageBox::Question);
    msgBox.setWindowTitle("Afdrukken.");
    //msgBox.setStyleSheet("min-width: 150px;");
    QSpacerItem *hs = new QSpacerItem(400, 0, QSizePolicy::Minimum, QSizePolicy::Expanding);
    QGridLayout *gl = (QGridLayout*)msgBox.layout();
    gl->addItem(hs, gl->rowCount(), 0, 1, gl->columnCount());
    int ret = msgBox.exec();
    if (ret == QMessageBox::Yes)
    {
        Artikelen::ResetPrikkers();
    }
}

void MainWindow::on_actionNieuwe_factuur_triggered()
{
    int _id = 0;
    //_id = QInputDialog::getInt(this, tr("Herafdruk factuur"),tr("Geef het factuur ID op:"));
    FactuurFiche* ff = new FactuurFiche(_id);
    ff->exec();
    //delete ff;
}

void MainWindow::on_actionToon_klantenscherm_triggered()
{
    Weegschaal* _ws;
    KlantenScherm* ks = new KlantenScherm(_ws);
    ks->exec();
}

void MainWindow::on_actionKeuzelijst_triggered()
{
    FactuurKeuzeLijst* fl = new FactuurKeuzeLijst();
    fl->show();
}

void MainWindow::on_actionLeveringen_triggered()
{
    LeveringenLijst* ll = new LeveringenLijst();
    ll->exec();
    ll->deleteLater();
}
