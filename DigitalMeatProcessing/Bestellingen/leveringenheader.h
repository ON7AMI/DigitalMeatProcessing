#ifndef LEVERINGENHEADER_H
#define LEVERINGENHEADER_H

#include <QObject>
#include <QSqlQueryModel>
#include <QDateTime>

class LeveringenHeader
{
    //    levering_header_id serial NOT NULL,
    //    leverancier_id integer,
    //    opmerking character varying,
    //    leverancier_referentie character varying,
    //    onze_referentie character varying,
    //    leverancier_factuur character varying,
    //    onze_factuur character varying,
    //    tijdstip date,
    //    create_at timestamp without time zone,
    //    modify_at timestamp without time zone,

public:
    LeveringenHeader();
    LeveringenHeader(int _id);

    void save();

    int getLeveringenHeader_ID();               void setLeveringenHeader_ID(int _id);
    int getLeverancier_ID();                    void setLeverancier_ID(int _id);
    QString getOpmerkingen();                   void setOpmerkingen(QString _opm);
    QString getLeverancierReferentie();         void setLeverancierReferentie(QString _levref);
    QString getOnzeReferentie();                void setOnzeReferentie(QString _oref);
    QString getLeverancierFactuur();            void setLeverancierFactuur(QString _levfact);
    QString getOnzeFactuur();                   void setOnzeFactuur(QString _ofact);
    QDate getTijdstip();                        void setTijdstip(QDate _tijdstip);
    QDateTime getCreatedAt();                   void setCreatedAt(QDateTime _createat);
    QDateTime getModifyAt();                    void setModifyAt(QDateTime _modifyat);


private:
        int LeveringenHeader_ID;
        int Leverancier_ID;
        QString Opmerkingen;
        QString LeverancierReferentie;
        QString OnzeReferentie;
        QString LeverancierFactuur;
        QString OnzeFactuur;
        QDate Tijdstip;
        QDateTime CreatedAt;
        QDateTime ModifyAt;

        void clear();
        void read();
        void QryRead(QSqlQuery* qry);

public:

    void static getLaatsteLeveringen(QSqlQueryModel* Leveringen_model, int Lev_ID, QDate StartDatum, QDate EindDatum);
};

#endif // LEVERINGENHEADER_H
