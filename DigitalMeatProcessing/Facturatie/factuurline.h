#ifndef FACTUURLINE_H
#define FACTUURLINE_H


#include <QObject>
#include <QSqlQueryModel>
#include <QDateTime>



class FactuurLine
{
public:
    FactuurLine();
    FactuurLine(int _id);

    int getFactuurLine_ID();                    void setFactuurLine_ID(int _id);
    int getFactuur_ID();                        void setFactuur_ID(int _id);
    int getArtikel_ID();                        void setArtikel_ID(int _id);
    QString getArtikelCode();                   void setArtikelCode(QString _code);
    QString getOmschrijving();                  void setOmschrijving(QString _omschr);
    double getAantal();                         void setAantal(double _aant);
    QString getEenheid();                       void setEenheid( QString _eenh );
    double getEenheidsprijs();                  void setEenheidsprijs(double _prijs);
    double getKortingPercent();                 void setKortingPercent(double _kort);
    double getBTW_Percent();                    void setBTW_Percent(double _btw);

    void save();
    void wis();


public: // static
    void static getLinesByFactuurID(int _id, QSqlQueryModel* _model);
    void static getBTWBlockByFactuurID(int _id, QSqlQueryModel* _model);
    void static getTotalsByFactuurID(int _id, QSqlQueryModel* _model);

private:
    int FactuurLine_ID;
    int Factuur_ID;
    int Artikel_ID;
    QString ArtikelCode;
    QString Omschrijving;
    double Aantal;
    QString Eenheid;
    double Eenheidsprijs;
    double KortingPercent;
    double  BTW_Percent;

    void clear();
    void read();
    void QryRead(QSqlQuery* qry);

};

#endif // FACTUURLINE_H
