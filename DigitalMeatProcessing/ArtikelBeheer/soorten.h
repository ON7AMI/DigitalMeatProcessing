#ifndef SOORTEN_H
#define SOORTEN_H

#include <QObject>
#include <QSqlQueryModel>

class Soorten
{
public:
    Soorten();
    Soorten(int _id);

    void setSoorten_ID( int _Soorten_ID );                      int getSoorten_ID();
    void setProduct_ID( int _Product_ID );                      int getProduct_ID();
    void setSoortCode( QString _SoortCode );                    QString getSoortCode();
    void setSoortOmschrijving( QString _SoortOmschrijving );    QString getSoortOmschrijving();
    void setSoortBenaming( QString _SoortBenaming );            QString getSoortBenaming();
    void setSoortAfbeelding( QByteArray _SoortAfbeelding );     QByteArray getSoortAfbeelding();

    void save();

private:
    int Soorten_ID;             //    soort_id serial NOT NULL,
    int Product_ID;             //    product_id int,
    QString SoortCode;          //    soort_code character varying,
    QString SoortOmschrijving;  //    soort_omschrijving character varying,
    QString SoortBenaming;      //    soort_benaming character varying,
    QByteArray SoortAfbeelding; //    soort_afbeelding bytea,

    void read();

public:   // statics
    static void getAllSoorten(QSqlQueryModel *model, int _product);
    static void getSoortenKeuze(QSqlQueryModel *model, int _product);
    static int getSoort_IDbyCode(QString _code, int product_ID);
};

#endif // SOORTEN_H
