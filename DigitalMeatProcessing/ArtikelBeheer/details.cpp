#include "details.h"

#include <QString>
#include <QtCore>
#include <QtSql>
#include <QSqlDatabase>
#include <QSettings>
#include <QApplication>

//==================================================================================================
//  Properties
//

void Details::setDetail_ID( int _Detail_ID)
{
    Detail_ID = _Detail_ID;
}

int Details::getDetail_ID()
{
    return Detail_ID;
}

void Details::setSoort_ID( int _Soort_ID )
{
    Soort_ID = _Soort_ID;
}

int Details::getSoort_ID()
{
    return Soort_ID;
}

void Details::setProduct_ID( int _Product_ID )
{
    Product_ID = _Product_ID;
}

int Details::getProduct_ID()
{
    return Product_ID;
}

void Details::setDetailCode( QString _DetailCode )
{
    DetailCode = _DetailCode;
}

QString Details::getDetailCode()
{
    return DetailCode;
}

void Details::setDetailOmschrijving( QString _DetailOmschrijving )
{
    DetailOmschrijving = _DetailOmschrijving;
}

QString Details::getDetailOmschrijving()
{
    return DetailOmschrijving;
}

void Details::setDetailBenaming( QString _DetailBenaming )
{
    DetailBenaming = _DetailBenaming;
}

QString Details::getDetailBenaming()
{
    return DetailBenaming;

}

//================================================================================================
//  Constructors
//

Details::Details()
{
    Detail_ID = 0;
    Soort_ID = 0;
    Product_ID = 0;
    DetailCode = "";
    DetailOmschrijving = "";
    DetailBenaming = "";
}

Details::Details(int _id)
{
    Detail_ID = _id;
    read();
}

//=================================================================================================
//  Methods
//

void Details::read()
{
    QString myQuery;
    QSqlQuery qry;
    bool status;

    myQuery = "SELECT * FROM artikelbeheer.details WHERE detail_id = :v_detail_id; ";

    qry.prepare(myQuery);
    qry.bindValue(":v_detail_id", Detail_ID);
    status = qry.exec();
    if (status )
    {
        status = qry.next();
        if (status )
        {
            Detail_ID = qry.value("detail_id").toInt();
            Soort_ID = qry.value("soort_id").toInt();
            Product_ID = qry.value("product_id").toInt();
            DetailCode = qry.value("detail_code").toString();
            DetailBenaming = qry.value("detail_benaming").toString();
            DetailOmschrijving = qry.value("detail_omschrijving").toString();
        }
        else
        {
            qDebug() << "Error bij lezen soort-record (of geen record gevonden)- " << qry.lastError().text();
        }
    }
    else
    {
        Detail_ID = 0;
        qDebug() << "Database error soort: " << qry.lastError().databaseText() << "\nQuerry error: " << qry.lastError().text();
    }
}


void Details::save()
{
    QString myQuery;
    QSqlQuery qry;

    if (Detail_ID == 0)
    {
        myQuery =
          "INSERT INTO artikelbeheer.details "
                "( product_id, soort_id, detail_code, detail_benaming, detail_omschrijving ) "
          "VALUES ( :v_product_id, :v_soort_id, :v_detail_code, :v_detail_benaming, :v_detail_omschrijving);";
        qry.prepare(myQuery);

    }
    else
    {
        myQuery = "UPDATE artikelbeheer.details "
                  "SET product_id=:v_product_id, "
                      "soort_id=:v_soort_id, "
                      "detail_code=:v_detail_code, "
                      "detail_omschrijving=:v_detail_omschrijving, "
                      "detail_benaming=:v_detail_benaming "
                  "WHERE detail_id = :v_detail_id;";

        qry.prepare(myQuery);
        qry.bindValue(":v_detail_id", Detail_ID);
    }

    qry.bindValue(":v_product_id", Product_ID);
    qry.bindValue(":v_soort_id", Soort_ID);
    qry.bindValue(":v_detail_code", DetailCode);
    qry.bindValue(":v_detail_benaming", DetailBenaming);
    qry.bindValue(":v_detail_omschrijving", DetailOmschrijving);

    if (qry.exec())
    {
        if (Detail_ID == 0)
        {
            Detail_ID = qry.lastInsertId().toInt();
        }
    }
    else

    {
        qDebug() << "Database error Details: " << qry.lastError().databaseText() << "\nQuerry error: " << qry.lastError().text();
    }
}


//====================================================================================================
//   Static Methods
//

int Details::getDetail_IDbyCode(QString _code, int product_id, int soort_id)
{
    QString myQuery;
    QSqlQuery qry;
    bool status;
    int _id = 0;

    myQuery = "SELECT detail_id FROM artikelbeheer.details WHERE detail_code = :v_detail_code AND "
                                                                "product_id = :v_product_id AND "
                                                                "soort_id = :v_soort_id; ";

    qry.prepare(myQuery);
    qry.bindValue(":v_detail_code", _code);
    qry.bindValue(":v_product_id", product_id);
    qry.bindValue(":v_soort_id", soort_id);
    status = qry.exec();
    if (status )
    {
        status = qry.next();
        if (status )
        {
            _id = qry.value("detail_id").toInt();
        }
        else
        {
            qDebug() << "Error bij lezen soort-record (of geen record gevonden)- " << qry.lastError().text();
        }
    }
    else
    {
        _id = 0;
        qDebug() << "Database error soort: " << qry.lastError().databaseText() << "\nQuerry error: " << qry.lastQuery();
    }
    return _id;
}

void Details::getAllDetails(QSqlQueryModel *model, int _product, int _soort)
{
    QString myQuery = "SELECT detail_id, detail_code, detail_benaming FROM artikelbeheer.details "
                      "WHERE ((product_id = :v_product_id)and(soort_id = :v_soort_id)) "
                      "ORDER BY detail_code";
    QSqlQuery qry;
    qry.prepare(myQuery);

    qry.bindValue(":v_product_id", _product);
    qry.bindValue(":v_soort_id", _soort);
    qry.exec();
    model->setQuery(qry);
    model->query();
}

void Details::getDetailKeuze(QSqlQueryModel *model, int _product, int _soort)
{
    QString myQuery = "SELECT detail_id, concat_ws('. ', detail_code::text, detail_benaming::text) AS naam "
                      "FROM artikelbeheer.details "
                      "WHERE ((product_id = :v_product_id)and(soort_id = :v_soort_id)) "
                      "ORDER BY detail_code;";
    QSqlQuery qry;
    qry.prepare(myQuery);
    qry.bindValue(":v_product_id", _product);
    qry.bindValue(":v_soort_id", _soort);
    qry.exec();
    model->setQuery(qry);
}
