#ifndef DETAILS_H
#define DETAILS_H

#include <QObject>
#include <QSqlQueryModel>

class Details
{
public:
    Details();
    Details(int _id);

    void setDetail_ID( int _Detail_ID);                         int getDetail_ID();
    void setSoort_ID( int _Soort_ID );                        int getSoort_ID();
    void setProduct_ID( int _Product_ID );                      int getProduct_ID();
    void setDetailCode( QString _DetailCode );                  QString getDetailCode();
    void setDetailOmschrijving( QString _DetailOmschrijving );  QString getDetailOmschrijving();
    void setDetailBenaming( QString _DetailBenaming );          QString getDetailBenaming();

    void save();

private:
    int Detail_ID;                  //    detail_id serial NOT NULL,
    int Product_ID;                 //    product_id integer,
    int Soort_ID;                   //    soort_id integer,
    QString DetailCode;             //    detail_code character varying,
    QString DetailOmschrijving;     //    detail_omschrijving character varying,
    QString DetailBenaming;         //    detail_benaming character varying,

    void read();

public: // static
    static void getAllDetails(QSqlQueryModel *model, int _product, int _soort);
    static void getDetailKeuze(QSqlQueryModel *model, int _product, int _soort);
    static int getDetail_IDbyCode(QString _code, int product_id, int soort_id);


};

#endif // DETAILS_H
