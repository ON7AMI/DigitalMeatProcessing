#ifndef ALLERGENEN_H
#define ALLERGENEN_H

#include <QObject>
#include <QSqlQueryModel>


class Allergenen
{
public:
    Allergenen();
    Allergenen(int _id);

    void save();

    void setAllergeen_ID( int );                      int getAllergeen_ID();
    void setAllergeen_Benaming( QString );            QString getAllergeen_Benaming();
    void setAllergeen_Omschrijving( QString );        QString getAllergeen_Omschrijving();
    void setAllergeen_Afbeelding( QByteArray );       QByteArray getAllergeen_Afbeelding();

public:     // statics
    static void getAllAllergeen(QSqlQueryModel *model);
    static void getAllergeenKeuze(QSqlQueryModel *model);


private:
    int Allergeen_ID;
    QString Allergeen_Benaming;
    QString Allergeen_Omschrijving;
    QByteArray Allergeen_Afbeelding;

    void read();


};

#endif // ALLERGENEN_H
