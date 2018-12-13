#ifndef KASBOEK_H
#define KASBOEK_H

#include <QObject>
#include <QSqlQueryModel>
#include <QDate>


class Kasboek
{
public:
    Kasboek();
    Kasboek(int _id);

    void save();

    int getKasboek_ID();                        void setKasboek_ID(int _id);
    double getBedragIn();                       void setBedragIn(double _bedrag);
    double getBedragUit();                      void setBedragUit(double _bedrag);
    int getBetaalmiddel_ID();                   void setBetaalmiddel_ID(int _id);
    QString getSoort();                         void setSoort(QString _soort);        // O = Ontvangst - U = uitgave
    int getTicket_ID();                         void setTicket_ID(int _id);
    QString getOmschrijving();                  void setOmschrijving(QString _omschr);
    QDateTime getTijdstip();                    void setTijdstip(QDateTime _tijd);

public: // statics
    void static getKassaBetaalmiddelen(QDateTime _tijd, QSqlQueryModel* _model);
    void static getKassaTotalen(QDateTime _tijd, QSqlQueryModel* _model);
    void static getUitgaveRedenen(QSqlQueryModel* _model);
    void static getBetaalmiddelen(QSqlQueryModel* _model);
    QString static getUitgaveTeken(QString Omschrijving);
    void static GetUitgaveTotalen(QDateTime _tijd, QSqlQueryModel* _model);

private:
    int Kasboek_ID;
    double BedragIn;
    double BedragUit;
    int Betaalmiddel_ID;
    QString Soort;
    int Ticket_ID;
    QString Omschrijving;
    QDateTime Tijdstip;

    void clear();
    void read();
    void read_qry(QSqlQuery qry);

};

#endif // KASBOEK_H
