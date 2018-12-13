#ifndef COMEENHEDEN_H
#define COMEENHEDEN_H

#include <QObject>
#include <QSqlQueryModel>


class ComEenheden
{
public:
    ComEenheden();
    ComEenheden(int _id);
    void save();
    void setEenheids_ID(int _id);                                   int getEenheids_ID();
    void setEenheidsCode(QString _EenheidsCode);                    QString getEenheidsCode();
    void setEenheidsOmschrijving(QString _EenheidsOmschrijving);    QString getEenheidsOmschrijving();

public:    // statics
    static void getAllComEenheden(QSqlQueryModel *model);
    static void getComEenhedenKeuze(QSqlQueryModel *model);
    static QString getComEenheidsCode(int _id);
    static int getComEenheidsID(QString _code);


private:
    int Eenheids_ID;                //    eenheids_id serial NOT NULL,
    QString EenheidsCode;           //    eenheids_code character varying,
    QString EenheidsOmschrijving;   //    eenheids_omschrijving character varying,

    void read();

};

#endif // COMEENHEDEN_H
