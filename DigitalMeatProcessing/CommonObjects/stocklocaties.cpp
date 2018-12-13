#include "stocklocaties.h"

StockLocaties::StockLocaties()
{

}

void StockLocaties::getAllStockLocaties(QSqlQueryModel *model)
{
    QSqlQuery myquery;
    myquery.prepare("SELECT locatie_id, omschrijving FROM common.locatie ORDER BY omschrijving;");
    myquery.exec();
    model->setQuery(myquery);
    model->query();
}
