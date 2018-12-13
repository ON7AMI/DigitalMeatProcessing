//======================================================================================================
//
//                        ==== ON7AMI = Project: Digital Meat Processing ====
//
//======================================================================================================
//
//   Doel:    Main Window - Startpagina globaal beheer
//   File:    MainWindow.h
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


#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QCoreApplication>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    void startBalans();
    void startKassa();

private slots:
    void on_action_Afsluiten_triggered();
    void on_action_Over_DMP_triggered();
    void on_actionInstellingen_triggered();
    void on_actionRelaties_triggered();
    void on_actionArtikelnummers_triggered();
    void on_actionAllergenen_triggered();
    void on_actionLotnummers_triggered();
    void on_actionStart_weegschaal_triggered();

    void on_actionStart_Kassa_triggered();

    void on_actionDagrapport_triggered();

    void on_actionPrikkes_maken_triggered();

    void on_actionNieuwe_factuur_triggered();

    void on_actionToon_klantenscherm_triggered();

    void on_actionKeuzelijst_triggered();

    void on_actionLeveringen_triggered();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
