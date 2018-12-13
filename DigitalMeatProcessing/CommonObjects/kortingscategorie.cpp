#include "kortingscategorie.h"

KortingsCategorie::KortingsCategorie()
{

}


//-------------------------------------------------------------------------------------------------
//  Vul het model met alle beschikbare landen (code en korte landnaam)
//
void KortingsCategorie::getAllKortingsCategorie( QSqlQueryModel* model)
{
    QSqlQuery myquery;
    myquery.prepare("SELECT korting_id, benaming  FROM common.korting_categorie;");
    myquery.exec();
    model->setQuery(myquery);
    model->query();
}
