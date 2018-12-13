#include "sites.h"

Sites::Sites()
{

}

//-------------------------------------------------------------------------------------------------
//  Vul het model met alle beschikbare Sites (code en benaming)
//
void Sites::getAllSites( QSqlQueryModel* model)
{
    QSqlQuery myquery;
    myquery.prepare("SELECT site_id, benaming FROM common.sites ORDER BY benaming;");
    myquery.exec();
    model->setQuery(myquery);
    model->query();
}
