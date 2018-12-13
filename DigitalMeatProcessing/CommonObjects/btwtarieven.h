#ifndef BTWTARIEVEN_H
#define BTWTARIEVEN_H

#include <QObject>
#include <QSqlQueryModel>
#include <QDate>

class BTWTarieven
{
public:
    BTWTarieven();
    BTWTarieven(int _id);
    void save();
    void setBTWTarief_ID( int _id);             int getBTWTarief_ID();
    void setTarief(QString _tarief);            QString getTarief();
    void setPercentage(double _percentage);     double getPercentage();
    void setGeldigVanaf(QDate _geldigVanaf);    QDate getGeldigVanaf();
    void setGeldigTot(QDate _geldigTot);        QDate getGeldigTot();

    int static getBTWTariefByPercent(double _percentage);

public:   //statics
    static void getAllBTWTarieven(QSqlQueryModel *model);
    static void getBTWTarievenKeuze(QSqlQueryModel *model);
    static int getDefaultBTW();
    static double getBTWPercentage(int _id);


private:
    int BTWTarief_ID;
    QString Tarief;
    double Percentage;
    QDate GeldigVanaf;
    QDate GeldigTot;

    void read();
};

#endif // BTWTARIEVEN_H
