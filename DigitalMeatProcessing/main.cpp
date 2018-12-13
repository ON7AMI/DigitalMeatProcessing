//======================================================================================================
//
//                        ==== ON7AMI = Project: Digital Meat Processing ====
//
//======================================================================================================
//
//   Doel:    Main - Programma globaal beheer
//   File:    main.h
//   Created: 26/07/2015
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
//
//========================================================================================================



#include "mainwindow.h"
#include "CommonObjects/commonobjects.h"
#include "Weegschaal/bedienscherm.h"
#include <QApplication>


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    CommonObjects::OpenDatabase();
    //==========================================================================
    //  Version:
    //  22/06/2018 1.5.0.0 - Invoering van de leveringen en prijsberekening
    //             1.5.0.2 - Operationeel
    //  01/07/2018 1.5.1.0 - Aanpassingen aan de Artikelfiche voor Prijsbewaking
    //
    //
    a.setApplicationVersion("1.5.1.0   -   01-07-2018");

//    QCoreApplication* app = new QCoreApplication(argc, argv);
    QStringList arglst = a.arguments();

    MainWindow w;
    w.show();

    if ((arglst.count()>=2) && (arglst[1] == "-b"))
    {
        w.startBalans();
    }
    else if ((arglst.count()>=2) && (arglst[1] == "-k"))
    {
        w.startKassa();
    }



    return a.exec();
}
