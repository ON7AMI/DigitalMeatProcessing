#ifndef FACTUURHEADER_H
#define FACTUURHEADER_H


#include <QObject>
#include <QSqlQueryModel>
#include <QDateTime>

class FactuurHeader
{
public:
    FactuurHeader();
    FactuurHeader(int _id);

    int getFactuur_ID();                    void setFactuur_ID( int _id );
    QDate getTijdstip();                    void setTijdstip( QDate _tijd );
    int getVolgnummer();                    void setVolgnummer( int _volgnr );
    int getKlant_ID();                      void setKlant_ID( int _id );
    QString getKlantNaam();                 void setKlantNaam( QString _naam );
    QString getKlantAdres();                void setKlantAdres( QString _adres );
    QString getKlantPostcode();             void setKlantPostcode( QString _code );
    QString getKlantGemeente();             void setKlantGemeente( QString _gem );
    QString getKlantLand();                 void setKlantLand( QString _land );
    double getKortingBedrag();              void setKortingBedrag( double _bedr );
    bool getPrinted();                      void setPrinted( bool _printed );

    void save();



private:
    int Factuur_ID;
    QDate Tijdstip;
    int Volgnummer;
    int Klant_ID;
    QString KlantNaam;
    QString KlantAdres;
    QString KlantPostcode;
    QString KlantGemeente;
    QString KlantLand;
    double KortingBedrag;
    bool Printed;

    void clear();
    void read();
    void QryRead(QSqlQuery* qry);


public:  //static
    int static getLastFactuurNummer();
    void static getLaatsteFacturen(QSqlQueryModel* _model);
    void static getLaatsteFacturen(QSqlQueryModel* _model, int _num);


};

#endif // FACTUURHEADER_H
