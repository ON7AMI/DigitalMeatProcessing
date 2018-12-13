#include "btwregimes.h"

BTWRegimes::BTWRegimes()
{

}


//-------------------------------------------------------------------------------------------------
//  Vul het model met alle beschikbare landen (code en korte landnaam)
//
void BTWRegimes::getAllBTWRegimes( QSqlQueryModel* model)
{
    QSqlQuery myquery;
    myquery.prepare("SELECT btwregime_id, benaming FROM common.btw_regimes WHERE (geldig_vanaf <= current_date AND geldig_tot >= current_date);");
    myquery.exec();
    model->setQuery(myquery);
    model->query();
}
