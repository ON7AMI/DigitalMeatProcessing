#include "postcodes.h"
#include "commonobjects.h"

Postcodes::Postcodes()
{

}

QString Postcodes::getPocode(int _id)
{
    QString _code = "";
    QSqlQuery myquery;

    myquery.prepare("SELECT postcode FROM common.postcodes WHERE (postcode_id = :v_postcode_id);");
    myquery.bindValue(":v_postcode_id", _id);
    bool status = myquery.exec();
    if (status)
    {
        status = myquery.next();
        if (status)
        {
            _code = myquery.value("postcode").toString();
        }
        else
        {
            _code = "ONBEKEND";
            qDebug() << "Error bij lezen getGemeente-record (of geen record gevonden)- " << myquery.lastError().text();
        }
    }
    else
    {
        _code = "ONBEKEND";
        qDebug() << "Database error soort (getGemeente): " << myquery.lastError().databaseText() << "\nQuerry error: " << myquery.lastError().text();
    }
    return _code;

    return "9840";
}

QString Postcodes::getGemeente(int _id)
{
    QString _gemeente = "";
    QSqlQuery myquery;

    myquery.prepare("SELECT gemeente FROM common.postcodes WHERE (postcode_id = :v_postcode_id);");
    myquery.bindValue(":v_postcode_id", _id);
    bool status = myquery.exec();
    if (status)
    {
        status = myquery.next();
        if (status)
        {
            _gemeente = myquery.value("gemeente").toString();
        }
        else
        {
            _gemeente = "ONBEKEND";
            qDebug() << "Error bij lezen getGemeente-record (of geen record gevonden)- " << myquery.lastError().text();
        }
    }
    else
    {
        _gemeente = "ONBEKEND";
        qDebug() << "Database error soort (getGemeente): " << myquery.lastError().databaseText() << "\nQuerry error: " << myquery.lastError().text();
    }
    return _gemeente;
}


void Postcodes::getGemeentesPerLandEnPostcode(QSqlQueryModel* model, QString _LandCode, QString _Postcode)
{
    QSqlQuery myquery; //= new QSqlQuery();

    myquery.prepare("SELECT postcode_id, gemeente FROM common.postcodes WHERE land_code = :v_land AND postcode = :v_postcode ORDER BY gemeente;");
    myquery.bindValue(":v_land",_LandCode);
    myquery.bindValue(":v_postcode", _Postcode);

    myquery.exec();
    model->clear();
    model->setQuery(myquery);
    model->query();

}

void Postcodes::getPostcodesPerLand(QSqlQueryModel* model, QString _LandCode)
{
    QSqlQuery myquery; //= new QSqlQuery();

    myquery.prepare("SELECT postcode_id, postcode FROM common.postcodes WHERE land_code = :v_land ORDER BY postcode;");
    myquery.bindValue(":v_land",_LandCode);

    myquery.exec();
    model->clear();
    model->setQuery(myquery);
    model->query();
}

void Postcodes::getGemeentesPerLand(QSqlQueryModel* model, QString _LandCode)
{
    QSqlQuery myquery; //= new QSqlQuery();

    myquery.prepare("SELECT postcode_id, gemeente FROM common.postcodes WHERE ((land_code = :v_land) or (:v_land = 'xx')) ORDER BY gemeente;");
    myquery.bindValue(":v_land",_LandCode);

    myquery.exec();
    model->clear();
    model->setQuery(myquery);
    model->query();

}
