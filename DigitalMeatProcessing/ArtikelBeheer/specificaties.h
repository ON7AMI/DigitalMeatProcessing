#ifndef SPECIFICATIES_H
#define SPECIFICATIES_H

#include <QObject>
#include <QSqlQueryModel>


class Specificaties
{
public:
    Specificaties();
    Specificaties(int _id);

    void setSpecificatie_ID(int _Specificatie_ID);                  int getSpecificatie_ID();
    void setDetail_ID(int _Detail_ID);                              int getDetail_ID();
    void setProduct_ID( int _Product_ID );                          int getProduct_ID();
    void setSoort_ID(int _Soort_ID);                                int getSoort_ID();
    void setSpecificatieCode(QString _SpecificatieCode);            QString getSpecificatieCode();
    void setSpecificatieBenaming(QString _SpecificatieBenaming);    QString getSpecificatieBenaming();

    void save();

private:
    int Specificatie_ID;            //    specificatie_id serial NOT NULL,
    int Detail_ID;                  //    detail_id integer,
    int Product_ID;                 //    product_id integer,
    int Soort_ID;                   //    soort_id integer,
    QString SpecificatieCode;       //    detail_code character varying,
    QString SpecificatieBenaming;   //    specificatie_benaming character varying,

    void read();

public: //static
    static void getAllSpecificaties(QSqlQueryModel *model, int _product, int soort, int _detail);
    static void getSpecificatieKeuze(QSqlQueryModel *model, int _product, int soort, int _detail);
};

#endif // SPECIFICATIES_H
