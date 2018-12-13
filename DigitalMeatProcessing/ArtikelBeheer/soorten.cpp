#include "soorten.h"


#include <QString>
#include <QtCore>
#include <QtSql>
#include <QSqlDatabase>
#include <QSettings>
#include <QApplication>


//==================================================================================================
//  Properties
//

void Soorten::setSoorten_ID( int _Soorten_ID )
{
    Soorten_ID = _Soorten_ID;
}

int Soorten::getSoorten_ID()
{
    return Soorten_ID;
}

void Soorten::setProduct_ID( int _Product_ID )
{
    Product_ID = _Product_ID;
}

int Soorten::getProduct_ID()
{
    return Product_ID;
}

void Soorten::setSoortCode( QString _SoortCode )
{
    SoortCode = _SoortCode;
}

QString Soorten::getSoortCode()
{
    return SoortCode;
}

void Soorten::setSoortOmschrijving( QString _SoortOmschrijving )
{
    SoortOmschrijving = _SoortOmschrijving;
}

QString Soorten::getSoortOmschrijving()
{
    return SoortOmschrijving;
}

void Soorten::setSoortBenaming( QString _SoortBenaming )
{
    SoortBenaming = _SoortBenaming;
}

QString Soorten::getSoortBenaming()
{
    return SoortBenaming;

}

void Soorten::setSoortAfbeelding( QByteArray _SoortAfbeelding )
{
    SoortAfbeelding = _SoortAfbeelding;
}

QByteArray Soorten::getSoortAfbeelding()
{
    return SoortAfbeelding;
}



//================================================================================================
//  Constructors
//


Soorten::Soorten()
{
    Soorten_ID = 0;             //    soort_id serial NOT NULL,
    Product_ID = 0;             //    product_id int,
    SoortCode = "";             //    soort_code character varying,
    SoortOmschrijving = "";     //    soort_omschrijving character varying,
    SoortBenaming = "";         //    soort_benaming character varying,product
    // SoortAfbeelding;         //    soort_afbeelding bytea,
}

Soorten::Soorten(int _id)
{
    Soorten_ID = _id;
    read();
}


//=================================================================================================
//  Methods
//

void Soorten::read()
{
    QString myQuery;
    QSqlQuery qry;
    bool status;

    myQuery = "SELECT * FROM artikelbeheer.soorten WHERE soort_id = :v_soort_id; ";

    qry.prepare(myQuery);
    qry.bindValue(":v_soort_id", Soorten_ID);
    status = qry.exec();
    if (status )
    {
        status = qry.next();
        if (status )
        {
            Soorten_ID = qry.value("soort_id").toInt();
            Product_ID = qry.value("product_id").toInt();
            SoortCode = qry.value("soort_code").toString();
            SoortBenaming = qry.value("soort_benaming").toString();
            SoortOmschrijving = qry.value("soort_omschrijving").toString();
            SoortAfbeelding = QByteArray::fromBase64(qry.value("soort_afbeelding").toByteArray());
        }
        else
        {
            qDebug() << "Error bij lezen soort-record (of geen record gevonden)- " << qry.lastError().text();
        }
    }
    else
    {
        Product_ID = 0;
        qDebug() << "Database error soort: " << qry.lastError().databaseText() << "\nQuerry error: " << qry.lastError().text();
    }
}


void Soorten::save()
{
    QString myQuery;
    QSqlQuery qry;

    if (Soorten_ID == 0)
    {
        myQuery =
                  "INSERT INTO artikelbeheer.soorten "
                         "( product_id, soort_code, soort_benaming, soort_omschrijving, soort_afbeelding ) "
                  "VALUES ( :v_product_id, :v_soort_code, :v_soort_benaming, :v_soort_omschrijving, :v_soort_afbeelding );";
        qry.prepare(myQuery);

    }
    else
    {
        myQuery = "UPDATE artikelbeheer.soorten "
                  "SET product_id=:v_product_id, "
                      "soort_code=:v_soort_code, "
                      "soort_omschrijving=:v_soort_omschrijving, "
                      "soort_benaming=:v_soort_benaming, "
                      "soort_afbeelding=:v_soort_afbeelding "
                  "WHERE soort_id = :v_soort_id;";

        qry.prepare(myQuery);
        qry.bindValue(":v_soort_id", Soorten_ID);
    }

    qry.bindValue(":v_product_id", Product_ID);
    qry.bindValue(":v_soort_code", SoortCode);
    qry.bindValue(":v_soort_benaming", SoortBenaming);
    qry.bindValue(":v_soort_omschrijving", SoortOmschrijving);
    qry.bindValue(":v_soort_afbeelding", SoortAfbeelding.toBase64());

    if (qry.exec())
    {
        if (Soorten_ID == 0)
        {
            Soorten_ID = qry.lastInsertId().toInt();
        }
    }
    else

    {
        qDebug() << "Database error Soorten: " << qry.lastError().databaseText() << "\nQuerry error: " << qry.lastError().text();
    }
}


//====================================================================================================
//   Static Methods
//

int Soorten::getSoort_IDbyCode(QString _code, int product_ID)
{
    QString myQuery;
    QSqlQuery qry;
    bool status;
    int soort_id;

    myQuery = "SELECT soort_id FROM artikelbeheer.soorten WHERE (soort_code = :v_soort_code) AND (product_id = :v_product_id); ";

    qry.prepare(myQuery);
    qry.bindValue(":v_soort_code", _code);
    qry.bindValue(":v_product_id", product_ID);
    status = qry.exec();
    if (status )
    {
        status = qry.next();
        if (status )
        {
            soort_id = qry.value("soort_id").toInt();
        }
        else
        {
            qDebug() << "Error bij lezen soort-record (of geen record gevonden)- " << qry.lastError().text();
        }
    }
    else
    {
        soort_id = 0;
        qDebug() << "Database error soort: " << qry.lastError().databaseText() << "\nQuerry error: " << qry.lastError().text();
    }
    return soort_id;
}

void Soorten::getAllSoorten(QSqlQueryModel *model, int _product)
{
    QString myQuery = "SELECT soort_id, soort_code, soort_benaming FROM artikelbeheer.soorten WHERE product_id = :v_product_id ORDER BY soort_code";
    QSqlQuery qry;
    qry.prepare(myQuery);

    qry.bindValue(":v_product_id", _product);
    qry.exec();
    model->setQuery(qry);
    model->query();
}

void Soorten::getSoortenKeuze(QSqlQueryModel *model, int _product)
{
    QString myQuery = "SELECT soort_id, concat_ws('. ', soort_code::text, soort_benaming::text) AS naam FROM artikelbeheer.soorten WHERE product_id = :v_product_id ORDER BY soort_code;";
    QSqlQuery qry;
    qry.prepare(myQuery);
    qry.bindValue(":v_product_id", _product);
    qry.exec();
    model->setQuery(qry);
}
