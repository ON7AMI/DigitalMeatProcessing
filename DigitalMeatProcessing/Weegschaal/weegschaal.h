#ifndef WEEGSCHAAL_H
#define WEEGSCHAAL_H

#include <QObject>
#include <QByteArray>


struct Weegschaal
{
    QString status;
    QString weegmethode;
    QString gewicht;
    double Aantal;
    double Gewicht;
    double Tarra;
    QString eenheid;
    int Artikel_ID;
    int Product_ID;
    int Soort_ID;
    int Detail_ID;
    QString ArtikelCode;
    double PrijsPerEenheidExclBTW;
    double PrijsPerEenheid;
    double BTWPercentage;
    QString ProductBenaming;
    QString VerkoopsEenheid;
    bool Promo;
    int LotnrID;
    QString Lotnr;
    int PersID;
    QString PersNaam;
    int TicketID;
    QString TicketNummer;
    int PersWissel;
    int NummerWeegschaal;
    int HuidigeGebruiker;
    int Bestelling;
};
#endif // WEEGSCHAAL_H
