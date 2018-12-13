#ifndef ARTIKELEN_H
#define ARTIKELEN_H

#include <QObject>
#include <QSqlQueryModel>
#include <QDate>
#include <QList>

//==================================================================================================
//  Properties
//
//==================================================================================================
//
// artikel_id serial NOT NULL,
// code character(6),
// barcode character varying,
// ext_plu character varying,
// rfi_code character varying,
// extra_code character varying,
// benaming character varying,
// omschrijving character varying,
// afbeelding bytea,
// eenheid_verkoop integer,
// btw_verkoop integer,
// verkoopprijs numeric(20,4),
// promoprijs numeric(20,4),
// promo_van date,
// promo_tot date,
// eenheid_aankoop integer,
// btw_aankoop integer,
// min_voorraad numeric(20,4),
// crit_voorraad numeric(20,4),
// max_voorraad numeric(20,4),
// houdbaarheid integer,
// wettelijk character varying,
// opmerking character varying,
// bewaar_temp numeric(8,2),
// bewaar_vocht numeric(8,2),
// actief_van date,
// actief_tot date,
// min_winstfactor numeric(20,4)
// laatste_prijscontrole date
//
class Artikelen
{
public:
    Artikelen();
    Artikelen(int _id);
    Artikelen(QString _code);
    Artikelen(QString _zoek, QString _code);

    void setArtikel_ID( int _Artikel_ID);                   int getArtikel_ID();
    void setCode( QString _Code );                          QString getCode();
    void setBarcode( QString _Barcode );                    QString getBarcode();
    void setExtPlu( QString _ExtPlu );                      QString getExtPlu();
    void setRFIcode( QString _RFIcode );                    QString getRFIcode();
    void setExtraCode( QString _ExtraCode );                QString getExtraCode();
    void setBenaming( QString _Benaming );                  QString getBenaming();
    void setOmschrijving( QString _Omschrijving );          QString getOmschrijving();
    void setAfbeelding(QByteArray _Afbeelding);             QByteArray getAfbeelding();
    void setEenheidVerkoop( int _EenheidVerkoop );          int getEenheidVerkoop();
    void setBTWVerkoop( int _BTWVerkoop );                  int getBTWVerkoop();
    void setVerkoopPrijs( double _VerkoopPrijs );           double getVerkoopPrijs();
    void setPromoPrijs( double _PromoPrijs );               double getPromoPrijs();
    void setPromoVan( QDate _PromoVan );                    QDate getPromoVan();
    void setPromoTot( QDate _PromoTot );                    QDate getPromoTot();
    void setEenheidAankoop( int _EenheidAankoop );          int getEenheidAankoop();
    void setBTWAankoop( int _BTWAankoop );                  int getBTWAankoop();
    void setMinVoorraad( double _MinVoorraad );             double getMinVoorraad();
    void setCriticalVoorraad( double _CriticalVoorraad );   double getCriticalVoorraad();
    void setMaxVoorraad( double MaxVoorraad );              double getMaxVoorraad();
    void setHoudbaarheid( int _Houdbaarheid );              int getHoudbaarheid();
    void setWettelijk( QString _Wettelijk );                QString getWettelijk();
    void setOpmerking( QString _Opmerking );                QString getOpmerking();
    void setBewaarTemp( double _BewaarTemp );               double getBewaarTemp();
    void setBewaarVocht( double _BewaarVocht );             double getBewaarVocht();
    void setActiefVan( QDate _ActiefVan );                  QDate getActiefVan();
    void setActiefTot( QDate _ActiefTot );                  QDate getActiefTot();
    void setAllergenen( QList<int>* _allergenen );          QList<int>* getAllergenen();
    void setPrikkerGewenst(bool gewenst);                   bool getPrikkerGewenst();
    void setPrikkerAfgedrukt(bool afgedrukt);               bool getPrikkerAfgedrukt();
    void setMinWinstfactor(double _MinWinstfactor);         double getMinWinstfactor();
    void setLaatstePrijscontrole(QDate _LaatstePrijscontrole); QDate getLaatstePrijscontrole();

    double getVP_Min();
    double getVP_Mean();
    double getVP_Max();

    void getAllergenenlijst(QSqlQueryModel *model);

    QDate getLastPriceUpdate();

    void save();
    void clear();

private:
    int Artikel_ID;
    QString Code;
    QString Barcode;
    QString ExtPlu;
    QString RFIcode;
    QString ExtraCode;
    QString Benaming;
    QString Omschrijving;
    QByteArray Afbeelding;
    int EenheidVerkoop;
    int BTWVerkoop;
    double VerkoopPrijs;
    double VorigePrijs;
    double PromoPrijs;
    QDate PromoVan;
    QDate PromoTot;
    int EenheidAankoop;
    int BTWAankoop;
    double MinVoorraad;
    double CriticalVoorraad;
    double MaxVoorraad;
    int Houdbaarheid;
    QString Wettelijk;
    QString Opmerking;
    double BewaarTemp;
    double BewaarVocht;
    QDate ActiefVan;
    QDate ActiefTot;
    QList<int>* Allergenen;
    double VP_Min;
    double VP_Mean;
    double VP_Max;
    bool PrikkerGewenst;
    bool PrikkerAfgedrukt;
    double MinWinstfactor;
    QDate LaatstePrijscontrole;

    void read();
    void readBarcode(QString _code);
    void setPrijsAanpassing(double _vorige, double _huidige);

public:  // static
    static int getArtikelIDByCode( QString _code);
    static void ExportPrikkers();
    static void ResetPrikkers();

};

#endif // ARTIKELEN_H
