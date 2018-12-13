#ifndef COMMONOBJECTS_H
#define COMMONOBJECTS_H

#include "commonobjects_global.h"

#include <QtCore>
#include <QtSql>
#include <QSqlDatabase>
#include <QSettings>
#include <QApplication>


class COMMONOBJECTSSHARED_EXPORT CommonObjects
{

public:

public:
    CommonObjects();

    static bool OpenDatabase();
};

#endif // COMMONOBJECTS_H
