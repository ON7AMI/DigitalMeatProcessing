#include "betalingstermijn.h"

BetalingsTermijn::BetalingsTermijn()
{

}


//-------------------------------------------------------------------------------------------------
//  Vul het model met alle beschikbare landen (code en korte landnaam)
//
void BetalingsTermijn::getAllBetalingsTermijn( QSqlQueryModel* model)
{
    QSqlQuery myquery;
    myquery.prepare("SELECT betalingstermijn_id, benaming  FROM common.betalingstermijnen;");
    myquery.exec();
    model->setQuery(myquery);
    model->query();
}
