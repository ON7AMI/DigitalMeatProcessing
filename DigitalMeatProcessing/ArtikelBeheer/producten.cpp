#include "producten.h"

#include <QString>
#include <QtCore>
#include <QtSql>
#include <QSqlDatabase>
#include <QSettings>
#include <QApplication>


//==================================================================================================
//  Properties
//

void Producten::setProduct_ID( int _Product_ID )
{
    Product_ID = _Product_ID;
}

int Producten::getProduct_ID()
{
    return Product_ID;
}

void Producten::setProduct_Code( QString _Product_Code )
{
    Product_Code = _Product_Code;
}

QString Producten::getProduct_Code()
{
    return Product_Code;
}

void Producten::setProduct_Benaming(QString _Product_Benaming )
{
    Product_Benaming = _Product_Benaming;
}

QString Producten::getProduct_Benaming()
{
    return Product_Benaming;
}

void Producten::setProduct_Omschrijving( QString _Product_Omschrijving )
{
    Product_Omschrijving = _Product_Omschrijving;
}

QString Producten::getProduct_Omschrijving()
{
    return Product_Omschrijving;
}

void Producten::setProduct_Afbeelding( QByteArray _Product_Afbeelding )
{
    Product_Afbeelding = _Product_Afbeelding;
}

QByteArray Producten::getProduct_Afbeelding()
{
    return Product_Afbeelding;
}


//================================================================================================
//  Constructors
//


Producten::Producten()
{
    Product_ID = 0;
    Product_Code = "";
    Product_Benaming = "";
    Product_Omschrijving = "";
    //Product_Afbeelding;
}

Producten::Producten(int _id)
{
    Product_ID = _id;
    read();
}

//=================================================================================================
//  Methods
//

void Producten::read()
{
    QString myQuery;
    QSqlQuery qry;
    bool status;

    myQuery = "SELECT * FROM artikelbeheer.producten WHERE product_id = :v_product_id; ";

    qry.prepare(myQuery);
    qry.bindValue(":v_product_id", Product_ID);
    status = qry.exec();
    if (status )
    {
        status = qry.next();
        if (status )
        {
            Product_ID = qry.value("product_id").toInt();
            Product_Code = qry.value("product_code").toString();
            Product_Benaming = qry.value("product_benaming").toString();
            Product_Omschrijving = qry.value("product_omschrijving").toString();
            Product_Afbeelding = QByteArray::fromBase64(qry.value("product_afbeelding").toByteArray());
        }
        else
        {
            qDebug() << "Error bij lezen record (of geen record gevonden)- " << qry.lastError().text();
        }
    }
    else
    {
        Product_ID = 0;
        qDebug() << "Database error: " << qry.lastError().databaseText() << "\nQuerry error: " << qry.lastError().text();
    }

}

void Producten::save()
{

    QString myQuery;
    QSqlQuery qry;

    if (Product_ID == 0)
    {
        myQuery = "INSERT INTO artikelbeheer.producten "
                         "( product_code, product_benaming, product_omschrijving, product_afbeelding ) "
                  "VALUES ( :v_product_code, :v_product_benaming, :v_product_omschrijving, :v_product_afbeelding );";
        qry.prepare(myQuery);

    }
    else
    {
        myQuery = "UPDATE artikelbeheer.producten "
                  "SET product_code = :v_product_code, "
                      "product_benaming = :v_product_benaming, "
                      "product_omschrijving = :v_product_omschrijving, "
                      "product_afbeelding = :v_product_afbeelding "
                  "WHERE product_id = :v_product_id; ";
        qry.prepare(myQuery);
        qry.bindValue(":v_product_id", Product_ID);
    }

    //QString foto_64 = Product_Afbeelding.toBase64();

    qry.bindValue(":v_product_code", Product_Code);
    qry.bindValue(":v_product_benaming", Product_Benaming);
    qry.bindValue(":v_product_omschrijving", Product_Omschrijving);
    qry.bindValue(":v_product_afbeelding", Product_Afbeelding.toBase64());

    if (qry.exec())
    {
        if (Product_ID == 0)
        {
            Product_ID = qry.lastInsertId().toInt();
        }
    }
    else
    {
        qDebug() << "Database error: " << qry.lastError().databaseText() << "\nQuerry error: " << qry.lastError().text();
    }

}


//====================================================================================================
//   Static Methods
//

int Producten::getProduct_IDbyCode(QString _code)
{
    QString myQuery;
    QSqlQuery qry;
    bool status;
    int ID = 0;

    myQuery = "SELECT product_id FROM artikelbeheer.producten WHERE product_code = :v_product_code; ";

    qry.prepare(myQuery);
    qry.bindValue(":v_product_code", _code);
    status = qry.exec();
    if (status )
    {
        status = qry.next();
        if (status )
        {
            ID = qry.value("product_id").toInt();
        }
        else
        {
            qDebug() << "Error bij lezen record (of geen record gevonden)- " << qry.lastError().text();
        }
    }
    else
    {
        ID = 0;
        qDebug() << "Database error: " << qry.lastError().databaseText() << "\nQuerry error: " << qry.lastError().text();
    }
    return ID;
}

void Producten::getAllProducten(QSqlQueryModel *model)
{
    model->setQuery("SELECT product_id, product_code, product_benaming FROM artikelbeheer.producten ORDER BY product_code");
}

void Producten::getProductenKeuze(QSqlQueryModel *model)
{
    QString myQuery = "SELECT product_id, concat_ws('. ', product_code::text, product_benaming::text) AS naam FROM artikelbeheer.producten ORDER BY product_code;";
    QSqlQuery qry;
    qry.prepare(myQuery);
    qry.exec();
    model->setQuery(qry);
}
