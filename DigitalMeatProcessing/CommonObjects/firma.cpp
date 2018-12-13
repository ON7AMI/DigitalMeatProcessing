#include "firma.h"

Firma::Firma()
{

}

void Firma::getAllFirmas(QSqlQueryModel* model)
{
    QSqlQuery myquery;
    myquery.prepare("SELECT firma_id, benaming FROM common.firmas ORDER BY benaming;");
    myquery.exec();
    model->setQuery(myquery);
    model->query();
}
