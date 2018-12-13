#ifndef PERSONEEL_H
#define PERSONEEL_H

#include <QObject>
#include <QString>
#include <QSqlQueryModel>

class Personeel
{
public:
    Personeel();
    Personeel(int _id);

    int getPersoneel_ID();              void setPersoneel_ID(int _id);
    QString getVoornaam();              void setVoornaam(QString _vn);
    QString getNaam();                  void setNaam(QString _n);
    bool getVerkoper();                 void setVerkoper(bool _set);
    bool getActief();                   void setActief(bool _set);

public: //static
    static void getAllActiveSalesmen(QSqlQueryModel* _model);
    static void setSalesmenOnBalance(int _id, int balans);
    static int getSalesmenOnBalance(int balans);

private:
    int Personeel_ID;
    QString Voornaam;
    QString Naam;
    bool Verkoper;
    bool Actief;

    void clear();
    void read();

};

#endif // PERSONEEL_H
