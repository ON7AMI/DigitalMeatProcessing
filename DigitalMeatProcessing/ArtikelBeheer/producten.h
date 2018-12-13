#ifndef PRODUCTEN_H
#define PRODUCTEN_H

#include <QObject>
#include <QSqlQueryModel>

class Producten
{
public:
    Producten();
    Producten(int);
    void save();
    void setProduct_ID( int );                      int getProduct_ID();
    void setProduct_Code( QString );                QString getProduct_Code();
    void setProduct_Benaming( QString );            QString getProduct_Benaming();
    void setProduct_Omschrijving( QString );        QString getProduct_Omschrijving();
    void setProduct_Afbeelding( QByteArray );       QByteArray getProduct_Afbeelding();


public:     // statics
    static void getAllProducten(QSqlQueryModel *model);
    static void getProductenKeuze(QSqlQueryModel *model);
    static int getProduct_IDbyCode(QString _code);


private:
    int Product_ID;
    QString Product_Code;
    QString Product_Benaming;
    QString Product_Omschrijving;
    QByteArray Product_Afbeelding;

    void read();
};

#endif // PRODUCTEN_H
