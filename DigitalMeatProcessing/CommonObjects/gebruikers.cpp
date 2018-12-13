#include "gebruikers.h"

Gebruikers::Gebruikers()
{

}

void Gebruikers::getAllGebruikers(QSqlQueryModel* model)
{
    QSqlQuery myquery;
    myquery.prepare("SELECT user_id, naam FROM common.users ORDER BY naam;");
    myquery.exec();
    model->setQuery(myquery);
    model->query();
}

void Gebruikers::CleanDagboek()
{
    QString qry;
    QSqlQuery myquery;

    qry = "DELETE FROM boekhouding.kasboek "
          "where bedrag_in = 0 and bedrag_uit = 0; ";

    myquery.prepare(qry);
    myquery.exec();

}
