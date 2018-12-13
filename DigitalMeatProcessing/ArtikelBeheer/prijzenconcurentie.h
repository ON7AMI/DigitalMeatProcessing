#ifndef PRIJZENCONCURENTIE_H
#define PRIJZENCONCURENTIE_H

#include <QSqlQueryModel>
#include <QDate>


class PrijzenConcurentie
{
public:
    PrijzenConcurentie();
    PrijzenConcurentie(int _id );

    void setPrijs_ID( int _id );                                int getPrijs_ID();
    void setArtikel_ID( int _id );                              int getArtikel_ID();
    void setRelatie_ID( int _id );                              int getRelatie_ID();
    void setDatumAankoop( QDate _datum );                       QDate getDatumAankoop();
    void setPrijs( double _prijs );                             double getPrijs();
    void setDatumInvoer( QDate _datum );                        QDate getDatumInvoer();

    void save();

public:   //statics
    static void getPrijzenPerArtikel( QSqlQueryModel* _model, int _art_id );
    static void deletePrijs(int _id);

private:
    int Prijs_ID;
    int Artikel_ID;
    int Relatie_ID;
    QDate DatumAankoop;
    double Prijs;
    QDate DatumInvoer;

    void read();
    void clear();
};

#endif // PRIJZENCONCURENTIE_H
