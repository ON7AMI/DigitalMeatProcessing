#ifndef BESTELLIJN_H
#define BESTELLIJN_H


#include <QObject>
#include <QSqlQueryModel>
#include <QDateTime>


class BestelLijn
{
public:
    BestelLijn();
    BestelLijn(int _id);

    int getBestelLijn_ID();                     void setBestelLijn_ID(int _id);
    int getBestelHeader_ID();                   void setBestelHeader_ID(int _id);
    int getArtikel_ID();                        void setArtikel_ID(int _id);
    int getLeverancierReferentie_ID();          void setLeverancierReferentie_ID(int _id);
    QString getOpmerking();                     void setOpmerking(QString _opm);
    double getHoeveelheidBesteld();             void setHoeveelheidBesteld(double _hoeveel);
    double getHoeveelheidGeleverd();            void setHoeveelheidGeleverd(double _hoeveel);
    double getPrijs();                          void setPrijs(double _prijs);
    QDateTime getTijdstip();                    void setTijdstip(QDateTime _tijd);
    bool getBestellingAf();                     void setBestellingAf(bool _af);
    QDateTime getTijdBestellingAf();            void setTijdBestellingAf(QDateTime _tijd);

    void save();

private:
    int BestelLijn_ID;
    int BestelHeader_ID;
    int Artikel_ID;
    int LeverancierReferentie_ID;
    QString Opmerking;
    double HoeveelheidBesteld;
    double HoeveelheidGeleverd;
    double Prijs;
    QDateTime Tijdstip;
    bool BestellingAf;
    QDateTime TijdBestellingAf;

    void clear();
    void read();
    void QryRead(QSqlQuery* qry);
};

#endif // BESTELLIJN_H
