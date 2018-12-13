#ifndef LOTNUMMERDBEVAT_H
#define LOTNUMMERDBEVAT_H


#include <QObject>
#include <QSqlQueryModel>
#include <QDate>


class LotnummerdBevat
{
public:
    LotnummerdBevat();
    LotnummerdBevat(int _id);

    void save();

    int getBevat_ID();              void setBevat_ID(int _id);
    int getLotnr_ID();              void setLotnr_ID(int _id);
    int getBetvatLotnummer();       void setBevatLotnummer(int _id);
    double getHoeveelheidIn();      void setHoeveelheidIn(double geb);

private:
    int Bevat_ID;
    int Lotnr_ID;
    int BevatLotnummer;
    double HoeveelheidIn;

    void clear();
    void read();
    void QryRead(QSqlQuery* qry);

public:   //static
    void static getBevatPerLotnummer(QSqlQueryModel* qm, int _id);
    void static deleteRow(int _id);
};

#endif // LOTNUMMERDBEVAT_H
