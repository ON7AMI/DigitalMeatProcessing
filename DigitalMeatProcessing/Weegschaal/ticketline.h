#ifndef TICKETLINE_H
#define TICKETLINE_H


#include <QObject>
#include <QDateTime>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QDateTime>

class TicketLine
{
public:
    TicketLine();
    TicketLine(int _id);

    void save();

    int getTicketLineID();                  void setTicketLineID(int _id);
    int getTicketID();                      void setTicketID(int _id);
    QDateTime getTijdstip();                void setTijdstip(QDateTime _tijd);
    int getArtID();                         void setArtID(int _id);
    QString getArtCode();                   void setArtCode(QString _code);
    QString getArtOmschrijving();           void setArtOmschrijving(QString _omschr);
    int getLotnrID();                       void setLotnrID(int _id);
    QString getLotnrCode();                 void setLotnrCode(QString _code);
    double getHoeveelheid();                void setHoeveelheid(double _aantal);
    QString getEenheid();                   void setEenheid(QString _eenh);
    double getEenheidsprijs();              void setEenheidsprijs(double _bedrag);
    double getBTWperc();                    void setBTWperc(double _bedrag);
    double getPrijsExBTW();                 void setPrijsExBTW(double _bedrag);
    double getPrijsBTW();                   void setPrijsBTW(double _bedrag);
    double getPrijsInclBTW();               void setPrijsInclBTW(double _bedrag);


public:    // statics

    void static getLinesByTicketID(int _id, QSqlQueryModel* _model);
    void static getBTWByTicketID(int _id, QSqlQueryModel* _model);
    void static getOmzetPerRubiek(QDateTime _dag, QSqlQueryModel* _model);
    void static getTeFacturerenPerRubiek(QDateTime _dag, QSqlQueryModel* _model);
    bool static isTeFacturerenPerRubiek(QDateTime _dag);
    void static deleteTicketLine(int _id);
    void static getTicketTotalen(int _id, double &ex, double &btw, double &incl);
    void static setTicketGefactureerd(QDateTime _dag, int _klant, int _factuur);
    void static setTimePerTicketID(int _id, QDateTime _tijdstip);

private:
    int TicketLineID;
    int TicketID;
    QDateTime Tijdstip;
    int ArtID;
    QString ArtCode;
    QString ArtOmschrijving;
    int LotnrID;
    QString LotnrCode;
    double Hoeveelheid;
    QString Eenheid;
    double Eenheidsprijs;
    double BTWperc;
    double PrijsExBTW;
    double PrijsBTW;
    double PrijsInclBTW;

    void clear();
    void read();
    void read_qry(QSqlQuery qry);
};

#endif // TICKETLINE_H
