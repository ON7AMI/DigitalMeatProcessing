#ifndef GESLACHTEN_H
#define GESLACHTEN_H

#include <QObject>
#include <QStandardItemModel>

class Geslachten
{
public:
    Geslachten();

    static void getAllGeslachten(QStandardItemModel* );
};

#endif // GESLACHTEN_H
