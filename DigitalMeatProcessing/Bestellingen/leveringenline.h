#ifndef LEVERINGENLINE_H
#define LEVERINGENLINE_H

#include <QObject>
#include <QSqlQueryModel>
#include <QDateTime>


class LeveringenLine
{
    // levering_line_id serial NOT NULL,
    // levering_header_id integer,
    // lev_art_id integer,
    // art_id integer,
    // artikel_code character varying,
    // omschrijving character varying,
    // aantal numeric(20,4),
    // eenheid integer,
    // eenheidsprijs numeric(20,4),
    // btw_code integer,
    // opmerking character varying,
    // create_at timestamp without time zone,
    // modify_at timestamp without time zone,

public:
    LeveringenLine();
    LeveringenLine(int _id);

    int getLeveringLine_ID();                       void setLeveringLine_ID(int _id);
    int getLeveringHeader_ID();                     void setLeveringHeader_ID(int _id);
    int getLevArt_ID();                             void setLevArt_ID(int _id);
    int getArt_ID();                                void setArt_ID(int _id);
    QString getArtikelCode();                       void setArtikelCode(QString _code);
    QString getArtikelOmschrijving();               void setArtikelOmschrijving(QString _oms);
    double getAantal();                             void setAantal(double _aantal);
    int getEenheid();                               void setEenheid(int _eenheid);
    double getEenheidsprijs();                      void setEenheidsprijs(double _prijs);
    int getBtwCode();                               void setBtwCode(int _code);
    QString getOpmerking();                         void setOpmerking(QString _opm);
    QDateTime getCreateAt();                        void setCreateAt(QDateTime _time);
    QDateTime getModifyAt();                        void setModifyAt(QDateTime _time);

    void save();
    void wis();

private:
    int LeveringLine_ID;
    int LeveringHeader_ID;
    int LevArt_ID;
    int Art_ID;
    QString ArtikelCode;
    QString ArtikelOmschrijving;
    double Aantal;
    int Eenheid;
    double Eenheidsprijs;
    int BtwCode;
    QString Opmerking;
    QDateTime CreateAt;
    QDateTime ModifyAt;

    void clear();
    void read();

    void QryRead(QSqlQuery* qry);

public:

    void static getLeveringLijnen(QSqlQueryModel* LeveringLijnen_model, int Lev_ID );
    void static getLeverStatistiek(QSqlQueryModel* LeverStat, int _id);

};

#endif // LEVERINGENLINE_H
