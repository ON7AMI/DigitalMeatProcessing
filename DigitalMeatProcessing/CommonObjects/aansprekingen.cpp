#include "aansprekingen.h"

Aansprekingen::Aansprekingen()
{

}

void Aansprekingen::getAllAansprekingen( QSqlQueryModel* model)
{
    QSqlQuery myquery;
    myquery.prepare("SELECT aansprekingen_id, benaming FROM common.aansprekingen ORDER BY benaming;");
    myquery.exec();
    model->setQuery(myquery);
    model->query();
}
