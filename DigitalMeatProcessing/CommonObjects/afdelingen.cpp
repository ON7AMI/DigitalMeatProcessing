#include "afdelingen.h"

Afdelingen::Afdelingen()
{

}


void Afdelingen::getAllAfdelingen(QSqlQueryModel* model)
{
    QSqlQuery myquery;
    myquery.prepare("SELECT afdeling_id, benaming FROM common.afdelingen ORDER BY benaming;");
    myquery.exec();
    model->setQuery(myquery);
    model->query();
}
