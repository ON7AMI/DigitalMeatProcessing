#include "bkhcategorie.h"

BKHCategorie::BKHCategorie()
{

}


//-------------------------------------------------------------------------------------------------
//  Vul het model met alle beschikbare BKHCategorie (code en omschrijving)
//
void BKHCategorie::getAllBKHCategorie( QSqlQueryModel* model)
{
    QSqlQuery myquery;
    myquery.prepare("SELECT categorie_id, benaming FROM common.boekhouding_categorie ;");
    myquery.exec();
    model->setQuery(myquery);
    model->query();
}
