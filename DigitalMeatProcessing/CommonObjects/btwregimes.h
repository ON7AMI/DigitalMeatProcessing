#ifndef BTWREGIMES_H
#define BTWREGIMES_H

#include <QObject>
#include <QtCore>
#include <QtSql>
#include <QSqlDatabase>
#include <QSettings>
#include <QApplication>


class BTWRegimes
{
public:
    BTWRegimes();


public:     // statics
    static void getAllBTWRegimes( QSqlQueryModel* );
};

#endif // BTWREGIMES_H
