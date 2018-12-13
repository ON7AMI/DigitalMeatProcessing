#include "landen.h"

Landen::Landen()
{

}


//-------------------------------------------------------------------------------------------------
//  Vul het model met alle beschikbare landen (code en korte landnaam)
//
void Landen::getAllLanden( QSqlQueryModel* model)
{
    QSqlQuery myquery;
    myquery.prepare("SELECT land_code, land FROM common.landen ORDER BY land;");
    myquery.exec();
    model->setQuery(myquery);
    model->query();
}

QString Landen::getLandByCode(QString _code)
{
    QSqlQuery myquery;
    myquery.prepare("SELECT land land FROM common.landen WHERE land_code = :v_land_code");
    myquery.bindValue(":v_land_code",_code);
    myquery.exec();
    myquery.next();
    return myquery.value("land").toString();
}
