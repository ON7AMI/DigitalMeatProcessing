#ifndef TALEN_H
#define TALEN_H

#include "commonobjects.h"
#include <QtCore>
#include <QtSql>
#include <QSqlDatabase>
#include <QSettings>
#include <QApplication>


class Talen
{
public:
    Talen();

    //static QSqlTableModel* getAllTalen(QSqlTableModel* );
    static void getAllTalen(QSqlTableModel* );
};

#endif // TALEN_H
