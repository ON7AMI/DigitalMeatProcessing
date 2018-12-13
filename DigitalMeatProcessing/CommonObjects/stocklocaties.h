#ifndef STOCKLOCATIES_H
#define STOCKLOCATIES_H

#include <QObject>
#include <QSqlQueryModel>
#include <QtSql>
#include <QSqlDatabase>
#include <QDate>



class StockLocaties
{
public:
    StockLocaties();

public:     // statics
    static void getAllStockLocaties( QSqlQueryModel* );

};

#endif // STOCKLOCATIES_H
