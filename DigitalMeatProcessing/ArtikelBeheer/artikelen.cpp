#include "artikelen.h"
#include "CommonObjects/btwtarieven.h"

#include <QString>
#include <QtCore>
#include <QtSql>
#include <QSqlDatabase>
#include <QSettings>
#include <QApplication>

//==================================================================================================
//  Properties
//
//==================================================================================================
//
// artikel_id serial NOT NULL,
// code character(6),
// barcode character varying,
// ext_plu character varying,
// rfi_code character varying,
// extra_code character varying,
// benaming character varying,
// omschrijving character varying,
// afbeelding bytea,
// eenheid_verkoop integer,
// btw_verkoop integer,
// verkoopprijs numeric(20,4),
// promoprijs numeric(20,4),
// promo_van date,
// promo_tot date,
// eenheid_aankoop integer,
// btw_aankoop integer,
// min_voorraad numeric(20,4),
// crit_voorraad numeric(20,4),
// max_voorraad numeric(20,4),
// houdbaarheid integer,
// wettelijk character varying,
// opmerking character varying,
// bewaar_temp numeric(8,2),
// bewaar_vocht numeric(8,2),
// actief_van date,
// actief_tot date,
//

void Artikelen::setArtikel_ID( int _Artikel_ID) { Artikel_ID = _Artikel_ID; }
int Artikelen::getArtikel_ID() { return Artikel_ID; }

void Artikelen::setCode( QString _Code ) { Code = _Code; }
QString Artikelen::getCode() { return Code; }

void Artikelen::setBarcode( QString _Barcode ) { Barcode = _Barcode; }
QString Artikelen::getBarcode() { return Barcode; }

void Artikelen::setExtPlu( QString _ExtPlu ) { ExtPlu = _ExtPlu; }
QString Artikelen::getExtPlu() { return ExtPlu; }

void Artikelen::setRFIcode( QString _RFIcode ) { RFIcode = _RFIcode; }
QString Artikelen::getRFIcode() { return RFIcode; }

void Artikelen::setExtraCode( QString _ExtraCode ) { ExtraCode = _ExtraCode; }
QString Artikelen::getExtraCode() { return ExtraCode; }

void Artikelen::setBenaming( QString _Benaming ) { Benaming = _Benaming; }
QString Artikelen::getBenaming() { return Benaming; }

void Artikelen::setOmschrijving( QString _Omschrijving ) { Omschrijving = _Omschrijving; }
QString Artikelen::getOmschrijving() { return Omschrijving; }

void Artikelen::setAfbeelding(QByteArray _Afbeelding) { Afbeelding = _Afbeelding; }
QByteArray Artikelen::getAfbeelding() { return Afbeelding; }

void Artikelen::setEenheidVerkoop( int _EenheidVerkoop ) { EenheidVerkoop = _EenheidVerkoop; }
int Artikelen::getEenheidVerkoop() { return EenheidVerkoop; }

void Artikelen::setBTWVerkoop( int _BTWVerkoop ) { BTWVerkoop = _BTWVerkoop; }
int Artikelen::getBTWVerkoop() { return BTWVerkoop; }

void Artikelen::setVerkoopPrijs( double _VerkoopPrijs ) { VerkoopPrijs = _VerkoopPrijs; }
double Artikelen::getVerkoopPrijs() { return VerkoopPrijs; }

void Artikelen::setPromoPrijs( double _PromoPrijs ) { PromoPrijs = _PromoPrijs; }
double Artikelen::getPromoPrijs() { return PromoPrijs; }

void Artikelen::setPromoVan( QDate _PromoVan ) { PromoVan = _PromoVan; }
QDate Artikelen::getPromoVan() { return PromoVan; }

void Artikelen::setPromoTot( QDate _PromoTot ) { PromoTot = _PromoTot; }
QDate Artikelen::getPromoTot() { return PromoTot; }

void Artikelen::setEenheidAankoop( int _EenheidAankoop ) { EenheidAankoop = _EenheidAankoop; }
int Artikelen::getEenheidAankoop() { return EenheidAankoop; }

void Artikelen::setBTWAankoop( int _BTWAankoop ) { BTWAankoop = _BTWAankoop; }
int Artikelen::getBTWAankoop() { return BTWAankoop; }

void Artikelen::setMinVoorraad( double _MinVoorraad ) { MinVoorraad = _MinVoorraad; }
double Artikelen::getMinVoorraad() { return MinVoorraad; }

void Artikelen::setCriticalVoorraad( double _CriticalVoorraad ) { CriticalVoorraad = _CriticalVoorraad; }
double Artikelen::getCriticalVoorraad() { return CriticalVoorraad; }

void Artikelen::setMaxVoorraad( double _MaxVoorraad ) { MaxVoorraad = _MaxVoorraad; }
double Artikelen::getMaxVoorraad() { return MaxVoorraad; }

void Artikelen::setHoudbaarheid( int _Houdbaarheid ) { Houdbaarheid = _Houdbaarheid; }
int Artikelen::getHoudbaarheid() { return Houdbaarheid; }

void Artikelen::setWettelijk( QString _Wettelijk ) { Wettelijk = _Wettelijk; }
QString Artikelen::getWettelijk() { return Wettelijk; }

void Artikelen::setOpmerking( QString _Opmerking ) { Opmerking = _Opmerking; }
QString Artikelen::getOpmerking() { return Opmerking; }

void Artikelen::setBewaarTemp( double _BewaarTemp ) { BewaarTemp = _BewaarTemp; }
double Artikelen::getBewaarTemp() { return BewaarTemp; }

void Artikelen::setBewaarVocht( double _BewaarVocht ) { BewaarVocht = _BewaarVocht; }
double Artikelen::getBewaarVocht() { return BewaarVocht; }

void Artikelen::setActiefVan( QDate _ActiefVan ) { ActiefVan = _ActiefVan; }
QDate Artikelen::getActiefVan() { return ActiefVan; }

void Artikelen::setActiefTot( QDate _ActiefTot ) { ActiefTot = _ActiefTot; }
QDate Artikelen::getActiefTot() { return ActiefTot; }

void Artikelen::setPrikkerGewenst(bool gewenst) { PrikkerGewenst = gewenst; }
bool Artikelen::getPrikkerGewenst() { return PrikkerGewenst; }

void Artikelen::setPrikkerAfgedrukt(bool afgedrukt) { PrikkerAfgedrukt = afgedrukt; }
bool Artikelen::getPrikkerAfgedrukt() { return PrikkerAfgedrukt; }

void Artikelen::setMinWinstfactor(double _MinWinstfactor) { MinWinstfactor = _MinWinstfactor; }
double Artikelen::getMinWinstfactor() { return MinWinstfactor; }

void Artikelen::setLaatstePrijscontrole(QDate _LaatstePrijscontrole) { LaatstePrijscontrole = _LaatstePrijscontrole; }
QDate Artikelen::getLaatstePrijscontrole() { return LaatstePrijscontrole; }


QDate Artikelen::getLastPriceUpdate()
{
    QDate laatste;
    QString myQuery;
    QSqlQuery qry;
    bool status;

    myQuery = "select max(datum_aanpassing) as laatste_datum "
              "from artikelbeheer.prijsaanpassingen "
              "where artikel_id = :v_artikel_id; ";

    qry.prepare(myQuery);
    qry.bindValue(":v_artikel_id", Artikel_ID);
    status = qry.exec();
    if (status )
    {
        status = qry.next();
        if (status )
        {
            laatste = qry.value("laatste_datum").toDate();
        }
        else
        {
            laatste = QDate::currentDate();
        }
    }
    else
    {
        Artikel_ID = 0;
        qDebug() << "Database error LaatstePrijsUpdate: " << qry.lastError().databaseText() << "\nQuerry error: " << qry.lastError().text();
    }

    return laatste;
}

void Artikelen::setAllergenen(QList<int> *_allergenen)
{
    QString myQuery;
    QSqlQuery qry;
    bool status;

    myQuery = "delete "
              "from artikelbeheer.allergenenperartikel "
              "where artikel_id = :v_artikel_id; ";

    qry.prepare(myQuery);
    qry.bindValue(":v_artikel_id", Artikel_ID);
    status = qry.exec();
    if ( !status )
    {
        qDebug() << "Database error SelectedAllergenen: " << qry.lastError().databaseText() << "\nQuerry error: " << qry.lastError().text();
    }

    myQuery = "INSERT INTO artikelbeheer.allergenenperartikel( artikel_id, allergeen_id) "
              "VALUES (:v_artikel_id, :v_allergeen_id); ";

    qry.prepare(myQuery);

    for (int i = 0; i<_allergenen->count() ; i++)
    {
        qry.bindValue(":v_artikel_id", Artikel_ID);
        qry.bindValue(":v_allergeen_id", _allergenen->at(i));
        if ( !qry.exec())
        {
            qDebug() << "Database error SelectedAllergenen: " << qry.lastError().databaseText() << "\nQuerry error: " << qry.lastError().text();
        }
    }
}

QList<int>* Artikelen::getAllergenen()
{
    QList<int>* lijst = new QList<int>();
    //QDate laatste;
    QString myQuery;
    QSqlQuery qry;
    bool status;

    myQuery = "select allergeen_id "
              "from artikelbeheer.allergenenperartikel "
              "where artikel_id = :v_artikel_id; ";

    qry.prepare(myQuery);
    qry.bindValue(":v_artikel_id", Artikel_ID);
    status = qry.exec();
    if (status )
    {
        while( qry.next())
        {
            lijst->append( qry.value("allergeen_id").toInt() );
        }
    }
    else
    {
        Artikel_ID = 0;
        qDebug() << "Database error SelectedAllergenen: " << qry.lastError().databaseText() << "\nQuerry error: " << qry.lastError().text();
    }

    return lijst;
}

void Artikelen::getAllergenenlijst(QSqlQueryModel *model)
{
    QString myQuery = "SELECT allergenen.allergeen_benaming "
                      "FROM artikelbeheer.allergenenperartikel, artikelbeheer.allergenen "
                      "WHERE allergenenperartikel.allergeen_id = allergenen.allergeen_id AND "
                            "allergenenperartikel.artikel_id = :v_artikel_id; ";

    QSqlQuery qry;
    qry.prepare(myQuery);
    qry.bindValue(":v_artikel_id", Artikel_ID);
    qry.exec();
    model->setQuery(qry);

}

double Artikelen::getVP_Max() { return VP_Max; }
double Artikelen::getVP_Mean() { return VP_Mean; }
double Artikelen::getVP_Min() { return VP_Min; }


//================================================================================================
//  Constructors
//



Artikelen::Artikelen()
{
    clear();
}

Artikelen::Artikelen(int _id)
{
    Artikel_ID = _id;
    read();
}

Artikelen::Artikelen(QString _code)
{
    clear();
    Artikel_ID = getArtikelIDByCode(_code);
    read();
}

Artikelen::Artikelen(QString _zoek, QString _code)
{
    if (_zoek == "Barcode")
    {
        readBarcode(_code);
    }
}

//=================================================================================================
//  Methods
//

void Artikelen::clear()
{
    Artikel_ID = 0;
    Code = "000000";
    Barcode = "";
    ExtPlu = "";
    RFIcode = "";
    ExtraCode = "";
    Benaming = "";
    Omschrijving = "";
    Afbeelding = NULL;
    EenheidVerkoop = 0;
    BTWVerkoop = BTWTarieven::getDefaultBTW();
    VerkoopPrijs = 0;
    VorigePrijs = VerkoopPrijs;
    PromoPrijs = 0;
    PromoVan = QDate::currentDate().addDays(-1);
    PromoTot = QDate::currentDate().addDays(-1);
    EenheidAankoop = 0;
    BTWAankoop = BTWTarieven::getDefaultBTW();
    MinVoorraad = 0;
    CriticalVoorraad = 0;
    MaxVoorraad = 0;
    Houdbaarheid = 0;
    Wettelijk = "";
    Opmerking = "";
    BewaarTemp = 0;
    BewaarVocht = 0;
    ActiefVan = QDate::currentDate();
    ActiefTot = QDate::currentDate().addYears(99);
    VP_Max = 0;
    VP_Min = 0;
    VP_Mean = 0;
    PrikkerGewenst = false;
    PrikkerAfgedrukt = false;
    MinWinstfactor = 1.8;
    LaatstePrijscontrole = QDate::currentDate();
}

void Artikelen::read()
{
    QString myQuery;
    QSqlQuery qry;
    bool status;

    myQuery = "SELECT * FROM artikelbeheer.artikelen WHERE artikel_id = :v_artikel_id; ";

    qry.prepare(myQuery);
    qry.bindValue(":v_artikel_id", Artikel_ID);
    status = qry.exec();
    if (status )
    {
        status = qry.next();
        if (status )
        {
            Artikel_ID = qry.value("artikel_id").toInt();
            Code = qry.value("code").toString();
            Barcode = qry.value("barcode").toString();
            ExtPlu = qry.value("ext_plu").toString();
            RFIcode = qry.value("rfi_code").toString();
            ExtraCode = qry.value("extra_code").toString();
            Benaming = qry.value("benaming").toString();
            Omschrijving = qry.value("omschrijving").toString();
            Afbeelding = QByteArray::fromBase64(qry.value("afbeelding").toByteArray());
            EenheidVerkoop = qry.value("eenheid_verkoop").toInt();
            BTWVerkoop = qry.value("btw_verkoop").toInt();
            VerkoopPrijs = qry.value("verkoopprijs").toDouble();
            VorigePrijs = VerkoopPrijs;
            PromoPrijs = qry.value("promoprijs").toDouble();
            PromoVan = qry.value("promo_van").toDate();
            PromoTot = qry.value("promo_tot").toDate();
            EenheidAankoop = qry.value("eenheid_aankoop").toInt();
            BTWAankoop = qry.value("btw_aankoop").toInt();
            MinVoorraad = qry.value("min_voorraad").toDouble();
            CriticalVoorraad = qry.value("crit_voorraad").toDouble();
            MaxVoorraad = qry.value("max_voorraad").toDouble();
            Houdbaarheid = qry.value("houdbaarheid").toInt();
            Wettelijk = qry.value("wettelijk").toString();
            Opmerking = qry.value("opmerking").toString();
            BewaarTemp = qry.value("bewaar_temp").toDouble();
            BewaarVocht = qry.value("bewaar_vocht").toDouble();
            ActiefVan = qry.value("actief_van").toDate();
            ActiefTot = qry.value("actief_tot").toDate();
            PrikkerGewenst = qry.value("label").toBool();
            PrikkerAfgedrukt = qry.value("label_printed").toBool();
            MinWinstfactor = qry.value("min_winstfactor").toDouble();
            LaatstePrijscontrole = qry.value("laatste_prijscontrole").toDate();
        }
        else
        {
            qDebug() << "Error bij lezen Artikel record (of geen record gevonden)- " << qry.lastError().text();
        }
    }
    else
    {
        Artikel_ID = 0;
        qDebug() << "Database error Artikelen: " << qry.lastError().databaseText() << "\nQuerry error: " << qry.lastError().text();
    }

    myQuery = "SELECT min(huidige_prijs) as mini, avg(huidige_prijs) as mean, max(huidige_prijs) as maxi "
              "FROM artikelbeheer.prijsaanpassingen "
              "WHERE artikel_ID = :v_artikel_id; ";


    qry.prepare(myQuery);
    qry.bindValue(":v_artikel_id", Artikel_ID);
    status = qry.exec();
    if (status )
    {
        status = qry.next();
        if (status )
        {
            VP_Min = qry.value("mini").toDouble();
            VP_Mean = qry.value("mean").toDouble();
            VP_Max = qry.value("maxi").toDouble();
        }
        else
        {
            qDebug() << "Error bij lezen Artikel_stat record (of geen record gevonden)- " << qry.lastError().text();
        }
    }
    else
    {
        qDebug() << "Database error Artikelen(stat): " << qry.lastError().databaseText() << "\nQuerry error: " << qry.lastError().text();
    }

}

void Artikelen::readBarcode(QString _code)
{
    QString myQuery;
    QSqlQuery qry;
    bool status;

    myQuery = "SELECT * FROM artikelbeheer.artikelen WHERE barcode = :v_barcode; ";

    qry.prepare(myQuery);
    qry.bindValue(":v_barcode", _code);
    status = qry.exec();
    if (status )
    {
        status = qry.next();
        if (status )
        {
            Artikel_ID = qry.value("artikel_id").toInt();
            Code = qry.value("code").toString();
            Barcode = qry.value("barcode").toString();
            ExtPlu = qry.value("ext_plu").toString();
            RFIcode = qry.value("rfi_code").toString();
            ExtraCode = qry.value("extra_code").toString();
            Benaming = qry.value("benaming").toString();
            Omschrijving = qry.value("omschrijving").toString();
            Afbeelding = QByteArray::fromBase64(qry.value("afbeelding").toByteArray());
            EenheidVerkoop = qry.value("eenheid_verkoop").toInt();
            BTWVerkoop = qry.value("btw_verkoop").toInt();
            VerkoopPrijs = qry.value("verkoopprijs").toDouble();
            VorigePrijs = VerkoopPrijs;
            PromoPrijs = qry.value("promoprijs").toDouble();
            PromoVan = qry.value("promo_van").toDate();
            PromoTot = qry.value("promo_tot").toDate();
            EenheidAankoop = qry.value("eenheid_aankoop").toInt();
            BTWAankoop = qry.value("btw_aankoop").toInt();
            MinVoorraad = qry.value("min_voorraad").toDouble();
            CriticalVoorraad = qry.value("crit_voorraad").toDouble();
            MaxVoorraad = qry.value("max_voorraad").toDouble();
            Houdbaarheid = qry.value("houdbaarheid").toInt();
            Wettelijk = qry.value("wettelijk").toString();
            Opmerking = qry.value("opmerking").toString();
            BewaarTemp = qry.value("bewaar_temp").toDouble();
            BewaarVocht = qry.value("bewaar_vocht").toDouble();
            ActiefVan = qry.value("actief_van").toDate();
            ActiefTot = qry.value("actief_tot").toDate();
            PrikkerGewenst = qry.value("label").toBool();
            PrikkerAfgedrukt = qry.value("label_printed").toBool();
            MinWinstfactor = qry.value("min_winstfactor").toDouble();
            LaatstePrijscontrole = qry.value("laatste_prijscontrole").toDate();
        }
        else
        {
            Artikel_ID = 0;
            qDebug() << "Error bij lezen Artikel record (of geen record gevonden)- " << qry.lastError().text();
        }
    }
    else
    {
        Artikel_ID = 0;
        qDebug() << "Database error Artikelen: " << qry.lastError().databaseText() << "\nQuerry error: " << qry.lastError().text();
    }

    myQuery = "SELECT min(huidige_prijs) as mini, avg(huidige_prijs) as mean, max(huidige_prijs) as maxi "
              "FROM artikelbeheer.prijsaanpassingen "
              "WHERE artikel_ID = :v_artikel_id; ";


    qry.prepare(myQuery);
    qry.bindValue(":v_artikel_id", Artikel_ID);
    status = qry.exec();
    if (status )
    {
        status = qry.next();
        if (status )
        {
            VP_Min = qry.value("mini").toDouble();
            VP_Mean = qry.value("mean").toDouble();
            VP_Max = qry.value("maxi").toDouble();
        }
        else
        {
            qDebug() << "Error bij lezen Artikel_stat record (of geen record gevonden)- " << qry.lastError().text();
        }
    }
    else
    {
        qDebug() << "Database error Artikelen(stat): " << qry.lastError().databaseText() << "\nQuerry error: " << qry.lastError().text();
    }


}

void Artikelen::save()
{
    QString myQuery;
    QSqlQuery qry;

    if (Artikel_ID == 0)
    {
        myQuery ="INSERT INTO artikelbeheer.artikelen( "
                        "code, barcode, ext_plu, rfi_code, extra_code, benaming, "
                        "omschrijving, afbeelding, eenheid_verkoop, btw_verkoop, verkoopprijs, "
                        "promoprijs, promo_van, promo_tot, eenheid_aankoop, btw_aankoop, "
                        "min_voorraad, crit_voorraad, max_voorraad, houdbaarheid, wettelijk, "
                        "opmerking, bewaar_temp, bewaar_vocht, actief_van, actief_tot, label, label_printed, "
                        "min_winstfactor, laatste_prijscontrole) "
                 "VALUES (:v_code, :v_barcode, :v_ext_plu, :v_rfi_code, :v_extra_code, :v_benaming, "
                        ":v_omschrijving, :v_afbeelding, :v_eenheid_verkoop, :v_btw_verkoop, :v_verkoopprijs, "
                        ":v_promoprijs, :v_promo_van, :v_promo_tot, :v_eenheid_aankoop, :v_btw_aankoop, "
                        ":v_min_voorraad, :v_crit_voorraad, :v_max_voorraad, :v_houdbaarheid, :v_wettelijk, "
                        ":v_opmerking, :v_bewaar_temp, :v_bewaar_vocht, :v_actief_van, :v_actief_tot, :v_label, :v_label_printed, "
                        ":v_min_winstfactor, :v_laatste_prijscontrole );";

        qry.prepare(myQuery);

    }
    else
    {
        myQuery = "UPDATE artikelbeheer.artikelen "
                  "SET code = :v_code, barcode = :v_barcode, ext_plu = :v_ext_plu, "
                      "rfi_code = :v_rfi_code, extra_code = :v_extra_code, benaming = :v_benaming, "
                      "omschrijving = :v_omschrijving, afbeelding = :v_afbeelding, "
                      "eenheid_verkoop = :v_eenheid_verkoop, btw_verkoop = :v_btw_verkoop, "
                      "verkoopprijs = :v_verkoopprijs, promoprijs = :v_promoprijs, promo_van = :v_promo_van, "
                      "promo_tot = :v_promo_tot, eenheid_aankoop = :v_eenheid_aankoop, "
                      "btw_aankoop = :v_btw_aankoop, min_voorraad = :v_min_voorraad, "
                      "crit_voorraad = :v_crit_voorraad, max_voorraad = :v_max_voorraad, "
                      "houdbaarheid = :v_houdbaarheid, wettelijk = :v_wettelijk, opmerking = :v_opmerking, "
                      "bewaar_temp = :v_bewaar_temp, bewaar_vocht = :v_bewaar_vocht, "
                      "actief_van = :v_actief_van, actief_tot = :v_actief_tot, "
                      "label = :v_label, label_printed = :v_label_printed, "
                      "min_winstfactor = :v_min_winstfactor, "
                      "laatste_prijscontrole = :v_laatste_prijscontrole "
                  "WHERE (artikel_id = :v_artikel_id); ";

        qry.prepare(myQuery);
        qry.bindValue(":v_artikel_id", Artikel_ID);
    }

    qry.bindValue(":v_code", Code);
    qry.bindValue(":v_barcode", Barcode);
    qry.bindValue(":v_ext_plu", ExtPlu);
    qry.bindValue(":v_rfi_code", RFIcode);
    qry.bindValue(":v_extra_code", ExtraCode);
    qry.bindValue(":v_benaming", Benaming);
    qry.bindValue(":v_omschrijving", Omschrijving);
    qry.bindValue(":v_afbeelding", Afbeelding);
    qry.bindValue(":v_eenheid_verkoop", EenheidVerkoop);
    qry.bindValue(":v_btw_verkoop", BTWVerkoop);
    qry.bindValue(":v_verkoopprijs", VerkoopPrijs);
    qry.bindValue(":v_promoprijs", PromoPrijs);
    qry.bindValue(":v_promo_van", PromoVan);
    qry.bindValue(":v_promo_tot", PromoTot);
    qry.bindValue(":v_eenheid_aankoop", EenheidAankoop);
    qry.bindValue(":v_btw_aankoop", BTWAankoop);
    qry.bindValue(":v_min_voorraad", MinVoorraad);
    qry.bindValue(":v_crit_voorraad", CriticalVoorraad);
    qry.bindValue(":v_max_voorraad", MaxVoorraad);
    qry.bindValue(":v_houdbaarheid", Houdbaarheid);
    qry.bindValue(":v_wettelijk", Wettelijk);
    qry.bindValue(":v_opmerking", Opmerking);
    qry.bindValue(":v_bewaar_temp", BewaarTemp);
    qry.bindValue(":v_bewaar_vocht", BewaarVocht);
    qry.bindValue(":v_actief_van", ActiefVan);
    qry.bindValue(":v_actief_tot", ActiefTot);
    qry.bindValue(":v_label", PrikkerGewenst);
    qry.bindValue(":v_label_printed", PrikkerAfgedrukt);
    qry.bindValue(":v_min_winstfactor", MinWinstfactor);
    qry.bindValue(":v_laatste_prijscontrole", LaatstePrijscontrole);

    if (qry.exec())
    {
        if (Artikel_ID == 0)
        {
            Artikel_ID = qry.lastInsertId().toInt();
            setPrijsAanpassing(VorigePrijs, VerkoopPrijs);
        }
        if (qAbs(VorigePrijs - VerkoopPrijs) >= 0.01)
        {
            setPrijsAanpassing(VorigePrijs, VerkoopPrijs);
        }
    }
    else
    {
        qDebug() << "Database error Artikelen: " << qry.lastError().databaseText() << "\nQuerry error: " << qry.lastError().text();
    }
}

void Artikelen::setPrijsAanpassing(double _vorige, double _huidige)
{
    QString myQuery;
    QSqlQuery qry;

    myQuery = "INSERT INTO artikelbeheer.prijsaanpassingen( "
                    "artikel_id, vorige_prijs, huidige_prijs, datum_aanpassing) "
              "VALUES (:v_artikel_id, :v_vorige_prijs, :v_huidige_prijs, :v_datum_aanpassing);";


    qry.prepare(myQuery);

    qry.bindValue(":v_artikel_id", Artikel_ID );
    qry.bindValue(":v_vorige_prijs", _vorige );
    qry.bindValue(":v_huidige_prijs", _huidige );
    qry.bindValue(":v_datum_aanpassing", QDate::currentDate() );

    if (!qry.exec())
    {
        qDebug() << "Database error Artikel_Prijsaanpassing: " << qry.lastError().databaseText() << "\nQuerry error: " << qry.lastError().text();
    }

}



int Artikelen::getArtikelIDByCode( QString _code )
{
    QString myQuery;
    QSqlQuery qry;
    bool status;
    int _id = 0;

    myQuery = "SELECT artikel_id FROM artikelbeheer.artikelen WHERE code = :v_code; ";

    qry.prepare(myQuery);
    qry.bindValue(":v_code", _code);
    status = qry.exec();
    if (status )
    {
        status = qry.next();
        if (status )
        {
            _id = qry.value("artikel_id").toInt();
        }
        else
        {
            qDebug() << "Error bij lezen ArtikelByCode record (of geen record gevonden)- " << qry.lastError().text();
        }
    }
    else
    {
        _id = 0;
        qDebug() << "Database error ArtikelByCode: " << qry.lastError().databaseText() << "\nQuerry error: " << qry.lastError().text();
    }
    return _id;
}

void Artikelen::ExportPrikkers()
{
    QString myQuery;
    QSqlQuery qry;

    myQuery = "SELECT artikelbeheer.maak_prikkers();";


    qry.prepare(myQuery);
    if (!qry.exec())
    {
        qDebug() << "Database error ExportPrikkers: " << qry.lastError().databaseText() << "\nQuerry error: " << qry.lastError().text();
    }
}

void Artikelen::ResetPrikkers()
{
    QString myQuery;
    QSqlQuery qry;

    myQuery =
            "UPDATE artikelbeheer.artikelen "
            "SET label_printed= true "
            "WHERE label = true AND label_printed = FALSE; ";


    qry.prepare(myQuery);
    if (!qry.exec())
    {
        qDebug() << "Database error ResetPrikkers: " << qry.lastError().databaseText() << "\nQuerry error: " << qry.lastError().text();
    }
}
