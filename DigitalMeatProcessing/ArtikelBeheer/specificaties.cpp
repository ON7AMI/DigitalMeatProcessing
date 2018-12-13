#include "specificaties.h"

#include <QString>
#include <QtCore>
#include <QtSql>
#include <QSqlDatabase>
#include <QSettings>
#include <QApplication>

//==================================================================================================
//  Properties
//

void Specificaties::setSpecificatie_ID(int _Specificatie_ID)
{
    Specificatie_ID = _Specificatie_ID;
}

int Specificaties::getSpecificatie_ID()
{
    return Specificatie_ID;
}

void Specificaties::setDetail_ID(int _Detail_ID)
{
    Detail_ID = _Detail_ID;
}

int Specificaties::getDetail_ID()
{
    return Detail_ID;
}

void Specificaties::setProduct_ID( int _Product_ID )
{
    Product_ID = _Product_ID;
}

int Specificaties::getProduct_ID()
{
    return Product_ID;
}

void Specificaties::setSoort_ID(int _Soort_ID)
{
    Soort_ID = _Soort_ID;
}

int Specificaties::getSoort_ID()
{
    return Soort_ID;
}

void Specificaties::setSpecificatieCode(QString _SpecificatieCode)
{
    SpecificatieCode = _SpecificatieCode;
}

QString Specificaties::getSpecificatieCode()
{
    return SpecificatieCode;
}

void Specificaties::setSpecificatieBenaming(QString _SpecificatieBenaming)
{
    SpecificatieBenaming = _SpecificatieBenaming;
}

QString Specificaties::getSpecificatieBenaming()
{
    return SpecificatieBenaming;
}


//================================================================================================
//  Constructors
//


Specificaties::Specificaties()
{
    Specificatie_ID = 0;
    Detail_ID = 0;
    Product_ID = 0;
    Soort_ID = 0;
    SpecificatieCode = "";
    SpecificatieBenaming = "";
}

Specificaties::Specificaties(int _id)
{
    Specificatie_ID = _id;
    read();
}

//=================================================================================================
//  Methods
//

void Specificaties::read()
{
    QString myQuery;
    QSqlQuery qry;
    bool status;

    myQuery = "SELECT * FROM artikelbeheer.specificaties "
              "WHERE specificatie_id = :v_specificatie_id; ";

    qry.prepare(myQuery);
    qry.bindValue(":v_specificatie_id", Specificatie_ID);
    status = qry.exec();
    if (status )
    {
        status = qry.next();
        if (status )
        {
            Specificatie_ID = qry.value("specificatie_id").toInt();
            Detail_ID = qry.value("detail_id").toInt();
            Soort_ID = qry.value("soort_id").toInt();
            Product_ID = qry.value("product_id").toInt();
            SpecificatieCode = qry.value("specificatie_code").toString();
            SpecificatieBenaming = qry.value("specificatie_benaming").toString();
        }
        else
        {
            qDebug() << "Error bij lezen soort-record (of geen record gevonden)- " << qry.lastError().text();
        }
    }
    else
    {
        Specificatie_ID = 0;
        qDebug() << "Database error specificaties: " << qry.lastError().databaseText() << "\nQuerry error: " << qry.lastError().text();
    }
}


void Specificaties::save()
{
    QString myQuery;
    QSqlQuery qry;

    if (Specificatie_ID == 0)
    {
        myQuery =
          "INSERT INTO artikelbeheer.specificaties "
                "( product_id, soort_id, detail_id, specificatie_code, specificatie_benaming ) "
          "VALUES ( :v_product_id, :v_soort_id, :v_detail_id, :v_specificatie_code, :v_specificatie_benaming);";
        qry.prepare(myQuery);

    }
    else
    {
        myQuery = "UPDATE artikelbeheer.specificaties "
                  "SET product_id=:v_product_id, "
                      "soort_id=:v_soort_id, "
                      "detail_id=:v_detail_id, "
                      "specificatie_code=:v_specificatie_code, "
                      "specificatie_benaming=:v_specificatie_benaming "
                  "WHERE specificatie_id = :v_specificatie_id;";

        qry.prepare(myQuery);
        qry.bindValue(":v_specificatie_id", Specificatie_ID);
    }

    qry.bindValue(":v_product_id", Product_ID);
    qry.bindValue(":v_soort_id", Soort_ID);
    qry.bindValue(":v_detail_id", Detail_ID);
    qry.bindValue(":v_specificatie_code", SpecificatieCode);
    qry.bindValue(":v_specificatie_benaming", SpecificatieBenaming);

    if (qry.exec())
    {
        if (Specificatie_ID == 0)
        {
            Specificatie_ID = qry.lastInsertId().toInt();
        }
    }
    else

    {
        qDebug() << "Database error Specificatiess: " << qry.lastError().databaseText() << "\nQuerry error: " << qry.lastError().text();
    }
}


//====================================================================================================
//   Static Methods
//

void Specificaties::getAllSpecificaties(QSqlQueryModel *model, int _product, int _soort, int _detail)
{
    QString myQuery = "SELECT specificatie_id, specificatie_code, specificatie_benaming FROM artikelbeheer.specificaties "
                      "WHERE ((product_id = :v_product_id)and(soort_id = :v_soort_id)and(detail_id = :v_detail_id)) "
                      "ORDER BY specificatie_code";
    QSqlQuery qry;
    qry.prepare(myQuery);

    qry.bindValue(":v_product_id", _product);
    qry.bindValue(":v_soort_id", _soort);
    qry.bindValue(":v_detail_id", _detail);
    qry.exec();
    model->setQuery(qry);
    model->query();
}

void Specificaties::getSpecificatieKeuze(QSqlQueryModel *model, int _product, int _soort, int _detail)
{
    QString myQuery = "SELECT specificatie_id, concat_ws('. ', specificatie_code::text, specificatie_benaming::text) AS naam "
                      "FROM artikelbeheer.specificaties "
                      "WHERE ((product_id = :v_product_id)and(soort_id = :v_soort_id)and(detail_id = :v_detail_id)) "
                      "ORDER BY specificatie_code;";
    QSqlQuery qry;
    qry.prepare(myQuery);
    qry.bindValue(":v_product_id", _product);
    qry.bindValue(":v_soort_id", _soort);
    qry.bindValue(":v_detail_id", _detail);
    qry.exec();
    model->setQuery(qry);
}
