#ifndef TICKET_H
#define TICKET_H

#include <QObject>
#include <QDateTime>
#include <QSqlQuery>
#include <QSqlQueryModel>

class Ticket
{
public:
    Ticket();
    Ticket(int _id);
    Ticket(QString _volgnr);

    void save();

    int getTicket_ID();                     void setTicket_ID(int _id);
    QDateTime getTijdstip();                void setTijdstip(QDateTime _tijd);
    QString getVolgnummer();                void setVolgnummer(QString _nr);
    int getVerkoper_ID();                   void setVerkoper_ID(int _id);
    QString getVerkoper_Naam();             void setVerkoper_Naam(QString _naam);
    double getTotaal_Ex_BTW();              void setTotaal_Ex_BTW(double _bedrag);
    double getTotaal_BTW();                 void setTotaal_BTW(double _bedrag);
    double getTotaal_Incl_BTW();            void setTotaal_Incl_BTW(double _bedrag);
    bool getNaar_Kas();                     void setNaar_Kas(bool _set);
    bool getBetaald();                      void setBetaald(bool _set);
    bool getNaar_Factuur();                 void setNaar_Factuur(bool _set);
    int getFactuurKlant_ID();               void setFactuurKlant_ID(int _id);
    int getFactuur_ID();                    void setFactuur_ID(int _id);
    int getBetaalwijze();                   void setBetaalwijze(int _id);
    double getBetaalwijze_Bedrag();         void setBetaalwijze_Bedrag(double _bedrag);
    int getBetaalwijze2();                  void setBetaalwijze2(int _id);
    double getBetaalwijze2_Bedrag();        void setBetaalwijze2_Bedrag(double _bedrag);
    int getBestelling();                    void setBestelling(int _id);
    double getBetaalwijze3_Bedrag();        void setBetaalwijze3_Bedrag(double _bedrag);

public:  // statics
    int static CheckOpenTicket(int _persID);
    int static CheckLastOpenTicket(int _persID);
    void static deleteTicket(int _id);
    void static TeBetalenTickets(QSqlQueryModel* _model);
    void static LogTicketControle(int _id);
    void static TicketToFactuur(int _FactuurID, int _TicketID, int _KlantID);
    void static getOmzetPerBTW(QDateTime _dag, QSqlQueryModel* _model);
    double static getOmzetTotaa(QDateTime _dag);
    double static getTicketTotaal(QDateTime _dag);
    int static getAantalTickets(QDateTime _dag);
    int static getBestellingByNumber(int _nr);
    void static getTeFactureren(QSqlQueryModel* _model);

private:
    int Ticket_ID;
    QDateTime Tijdstip;
    QString Volgnummer;
    int Verkoper_ID;
    QString Verkoper_Naam;
    double Totaal_Ex_BTW;
    double Totaal_BTW;
    double Totaal_Incl_BTW;
    bool Naar_Kas;
    bool Betaald;
    bool Naar_Factuur;
    int FactuurKlant_ID;
    int Factuur_ID;
    int Betaalwijze;
    double Betaalwijze_Bedrag;
    int Betaalwijze2;
    double Betaalwijze2_Bedrag;
    int Bestelling;
    double Betaalwijze3_Bedrag;

    void clear();
    void read();
    void read(QString _volgnr);
    void read_qry(QSqlQuery qry);
};

#endif // TICKET_H
