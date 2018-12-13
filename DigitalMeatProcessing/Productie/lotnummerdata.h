#ifndef LOTNUMMERDATA_H
#define LOTNUMMERDATA_H

#include <QObject>
#include <QSqlQueryModel>
#include <QDate>


class LotnummerData
{
public:
    LotnummerData();
    LotnummerData(int _id);
    LotnummerData(QString _lotnr);

    int getLotnummer_id();          void setLotnummer_id(int _id);
    QString getLotnummer();         void setLotnummer(QString _lotnr);
    QString getOpmerkingen();       void setOpmerkingen(QString _opm);
    QDate getDatumInstock();        void setDatumInstock(QDate _in);
    QDate getDatumEigTgv();         void setDatumEigTgv(QDate _tgv);
    QDate getDatumUitstock();       void setDatumUitstock(QDate _uit);
    bool getActief();               void setActief(bool _actief);
    int getArtikel_ID();            void setArtikel_ID(int _id);
    double getHoeveelheidIn();      void setHoeveelheidIn(double _in);
    double getHoeveelheidUit();     void setHoeveelheidUit(double _uit);
    double getHoeveelheidAfval();   void setHoeveelheidAfval(double _afval);
    int getHoudbaarheid();          void setHoudbaarheid(int _houd);
    QString getVerpakking();        void setVerpakking(QString _verp);
    int getReceptProductie();       void setReceptProductie(int _recept);
    int getLev_ID();                void setLev_ID(int _lev);
    QString getLevLotnr();          void setLevLotnr(QString _lotnr);
    QString getLevSlachthuis();     void setLevSlachthuis(QString _slachthuis);
    QString getLevSanitel();        void setLevSanitel(QString _sanitel);
    QDate getLevProdDatum();        void setLevProdDatum(QDate _dat);
    QDate getLevTgv();              void setLevTgv(QDate _tgv);
    QString getLevDocument();       void setLevDocument(QString _doc);
    QString getLevRegel();          void setLevRegel(QString _reg);
    int getLocatie_ID ();           void setLocatie_ID(int _id);
    QDateTime getLocatieVeranderdOp(); void setLocatieVeranderdOp(QDateTime _nu);

    void save();

public:   // Statics
    int static getLotInWinkel(int _art);
    void static getLotnrByArticle(int _art, QSqlQueryModel* _mod);

private:

    int Lotnummer_id;
    QString Lotnummer;
    QString Opmerkingen;
    QDate DatumInstock;
    QDate DatumEigTgv;
    QDate DatumUitstock;
    bool Actief;
    int Artikel_ID;
    double HoeveelheidIn;
    double HoeveelheidUit;
    double HoeveelheidAfval;
    int Houdbaarheid;
    QString Verpakking;
    int ReceptProductie;
    int Lev_ID;
    QString LevLotnr;
    QString LevSlachthuis;
    QString LevSanitel;
    QDate LevProdDatum;
    QDate LevTgv;
    QString LevDocument;
    QString LevRegel;
    int Locatie_ID;
    QDateTime LocatieVeranderdOp;

    void clear();
    void read();
    void read(QString _lotnr);
    void QryRead(QSqlQuery* qry);
};

#endif // LOTNUMMERDATA_H
