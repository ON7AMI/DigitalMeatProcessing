#ifndef LEVERANCIERCODES_H
#define LEVERANCIERCODES_H

#include <QObject>
#include <QSqlQueryModel>
#include <QDateTime>

class LeverancierCodes
{
    // leverancier_referentie_id serial NOT NULL,
    // leverancier_id integer,
    // artikel_id integer,
    // tijdstip timestamp without time zone,
    // leverancier_referentie character varying,
    // referentie_omschrijving character varying,


public:
    int getLevRef_ID();             void setLevRef_ID(int _id);
    int getLev_ID();                void setLev_ID(int _id);
    int getArt_ID();                void setArt_ID(int _id);
    QDateTime getCreatedAt();       void setCreatedAt(QDateTime _time);
    QString getLev_Ref();           void setLev_Ref(QString _ref);
    QString getLev_Omschr();        void setLev_Omschr(QString _omschr);

    LeverancierCodes();
    LeverancierCodes(int _id);
    LeverancierCodes(int _artid, int _levid);

    void save();

private:
    int LevRef_ID;
    int Lev_ID;
    int Art_ID;
    QDateTime CreatedAt;
    QString Lev_Ref;
    QString Lev_Omschr;

    void clear();
    void read();
    void readArtID();
    void QryRead(QSqlQuery* qry);

};

#endif // LEVERANCIERCODES_H
