#ifndef BESTELHEADER_H
#define BESTELHEADER_H

#include <QObject>
#include <QSqlQueryModel>
#include <QDateTime>

class BestelHeader
{
public:
    BestelHeader();
    BestelHeader(int _id);

    int getBestelHeader_ID();               void setBestelHeader_ID(int _id);
    int getLeverancier_ID();                void setLeverancier_ID(int _id);
    QString getOpmerking();                 void setOpmerking(QString _opm);
    QString getBestelReferentie();          void setBestelReferentie(QString _ref);
    QDateTime getTijdstip();                void setTijdstip(QDateTime _tijd);
    bool getBestellingAf();                 void setBestellingAf(bool _af);

    void save();

private:
    int BestelHeader_ID;
    int Leverancier_ID;
    QString Opmerking;
    QString BestelReferentie;
    QDateTime Tijdstip;
    bool BestellingAf;

    void clear();
    void read();
    void QryRead(QSqlQuery* qry);


};

#endif // BESTELHEADER_H
