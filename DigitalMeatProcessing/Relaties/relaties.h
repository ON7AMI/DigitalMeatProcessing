//======================================================================================================
//
//                        ==== ON7AMI = Project: Digital Meat Processing ====
//
//======================================================================================================
//
//   Doel:    Object Relaties
//   File:    Relaties.h
//   Created: 21/07/2015
//   By:      Jean Paul Mertens  (jpm)
//   email:   jpm@on7ami.be
//
//-------------------------------------------------------------------------------------------------------
//
//  Version |  Date      |  By    |  Description / Changes
// ---------+------------+--------+-----------------------------------------------------------------------
//  1.0.0   | 21/07/2015 |  JPM   |  Original
//          |            |        |
//
//--------------------------------------------------------------------------------------------------------
//
//
// -DataBases / Tables used:
//
//
// -Fields:
//
//        relatie_id serial NOT NULL,
//        naam character varying,
//        is_firma_naam boolean,
//        voornaam character varying,
//        aankoper character varying,
//        is_bedrijf boolean,
//        adres character varying,
//        nr_bus character varying,
//        gemeente_id integer,
//        land_id integer,
//        taal_id integer,
//        tel_1 character varying,
//        tel_1_contact boolean,
//        tel_1_publiciteit boolean,
//        gsm_1 character varying,
//        gsm_1_contact boolean,
//        gsm_1_publiciteit boolean,
//        aanspreking_id integer,
//        btw_nummer character varying,
//        firma_id integer,
//        site_id integer,
//        afdeling_id integer,
//        gebruiker_id integer,
//        geslacht_code character(1),
//        herkomst character varying,
//        beroep character varying,
//        is_prospect boolean,
//        is_klant boolean,
//        is_leverancier boolean,
//        is_benaderbaar boolean,
//        is_deelnemer boolean,
//        is_verhuisd boolean,
//        is_inactief boolean,
//        is_lopende_klacht boolean,
//        is_overleden boolean,
//        tel_2 character varying,
//        tel_2_contact boolean,
//        tel_2_publiciteit boolean,
//        fax character varying,
//        fax_contact boolean,
//        fax_publiciteit boolean,
//        email_1 character varying,
//        email_1_contact boolean,
//        email_1_publiciteit boolean,
//        email_2 character varying,
//        email_2_contact boolean,
//        email_2_publiciteit boolean,
//        adres_contact boolean,
//        adres_publiciteit boolean,
//        website character varying,
//        facebook character varying,
//        linked_in character varying,
//        ref_bij_relatie character varying,
//        nace_code character varying,
//        mailing_code character varying,
//        geboortedatum date,
//        geboorteplaats character varying,
//        aantal_kinderen integer,
//        hobby character varying,
//        btw_regime_id integer,
//        btw_autorisatiecode character varying,
//        bkh_categorie_id integer,
//        kortings_categorie_id integer,
//        kredietlimiet money,
//        betalingstermijn_id integer,
//        bankrekening_1 character varying,
//        iban_1 character varying,
//        bankrekening_2 character varying,
//        iban_2 characte    ui->cbxAanspreking->setCurrentIndex(( rel->getAanspreking_ID() == 0 ? 0 :
//        pop_up_tekst character varying,
//        opmerking character varying,
//        id_1 integer,
//        id_2 integer,
//        id_3 integer,
//        id_4 integer,
//        id_5 integer,
//        idcard_nummer character varying,
//        reziv_nummer character varying,
//        idcard_uitgereikt_te character varying,
//        id_geldig_van date,
//        id_geldig_tot date,
//        flag_1 boolean,
//        flag_2 boolean,
//        flag_3 boolean,
//        flag_4 boolean,
//        flag_5 boolean,
//        flag_6 boolean,
//        flag_7 boolean,
//        flag_8 boolean,
//        flag_9 boolean,
//        flag_10 boolean,
//        vrij_tekst_1 character varying,
//        vrij_tekst_2 character varying,
//        vrij_tekst_3 character varying,
//        vrij_tekst_4 character varying,
//        vrij_tekst_5 character varying,
//        vrij_num_1 numeric(4,0),
//        vrij_num_2 numeric(4,0),
//        vrij_num_3 numeric(4,0),
//        vrij_num_4 numeric(4,0),
//        vrij_num_5 numeric(4,0),
//
//
//========================================================================================================



#ifndef RELATIES_H
#define RELATIES_H

#include <QString>
#include <QtCore>
#include <QtSql>
#include <QSqlDatabase>
#include <QSettings>
#include <QApplication>


class Relaties
{

public:
    Relaties();
    Relaties(int id);
    void save();
    static void FindList(QSqlQueryModel *model, QString _naam, QString _adres, QString _gemeente, QString _email);

private:
    void read();
    void clear();

public:
    void setRelatie_ID(int);                        int getRelatie_ID();              // int         Relatie_ID;
    void setNaam( QString );                        QString getNaam();                // QString     Naam;
    void setIsFirmaNaam( bool );                    bool getIsFirmaNaam();            // bool        IsFirmaNaam;
    void setVoornaam( QString );                    QString getVoornaam();            // QString     Voornaam;
    void setAankoper( QString );                    QString getAankoper();            // QString     Aankoper;
    void setIsBedrijf( bool );                      bool getIsBedrijf();              // bool        IsBedrijf;
    void setAdres( QString );                       QString getAdres();               // QString     Adres;
    void setNrBus( QString );                       QString getNrBus();               // QString     NrBus;
    void setGemeente_ID(int);                       int getGemeente_ID();
    void setLandCode(QString);                      QString getLandCode();
    void setTaal_ID( int );                         int getTaal_ID();                 // int         Taal_ID;
    void setTel_1( QString );                       QString getTel_1();               // QString     Tel_1;
    void setTel_1_Contact( bool );                  bool getTel_1_Contact();          // bool        Tel_1_Contact;
    void setTel_1_Publiciteit( bool );              bool getTel_1_Publiciteit();      // bool        Tel_1_Publiciteit;
    void setGSM_1( QString );                       QString getGSM_1();               // QString     GSM_1;

    void setGSM_1_Contact( bool );                  bool getGSM_1_Contact();          // bool        GSM_1_Contact;
    void setGSM_1_Publiciteit( bool );              bool getGSM_1_Publiciteit();      // bool        GSM_1_Publiciteit;
    void setAanspreking_ID( int );                  int getAanspreking_ID();          // int         Aanspreking_ID;
    void setBTWNummer( QString );                   QString getBTWNummer();           // QString     BTWNummer;
    void setFirma_ID( int );                        int getFirma_ID();                // int         Firma_ID;
    void setSite_ID( int );                         int getSite_ID();                 // int         Site_ID;
    void setAfdeling_ID( int );                     int getAfdeling_ID();             // int         Afdeling_ID;
    void setGebruiker_ID( int );                    int getGebruiker_ID();            // int         Gebruiker_ID;
    void setGeslachtCode( QString );                QString getGeslachtCode();        // QString     GeslachtCode;
    void setHerkomst( QString );                    QString getHerkomst();            // QString     Herkomst;
    void setBeroep( QString );                      QString getBeroep();              // QString     Beroep;
    void setIsProspect( bool );                     bool getIsProspect();             // bool        IsProspect;
    void setIsKlant( bool );                        bool getIsKlant();                // bool        IsKlant;
    void setIsLeverancier( bool );                  bool getIsLeverancier();          // bool        IsLeverancier;
    void setIsBenaderbaar( bool );                  bool getIsBenaderbaar();          // bool        IsBenaderbaar;
    void setIsDeelnemer( bool );                    bool getIsDeelnemer();            // bool        IsDeelnemer;
    void setIsVerhuisd( bool );                     bool getIsVerhuisd();             // bool        IsVerhuisd;
    void setIsInactief( bool );                     bool getIsInactief();             // bool        IsInactief;
    void setIsLopendeKlacht( bool );                bool getIsLopendeKlacht();        // bool        IsLopendeKlacht;
    void setIsOverleden( bool );                    bool getIsOverleden();            // bool        IsOverleden;
    void setTel_2( QString );                       QString getTel_2();               // QString     Tel_2;
    void setTel_2_Contact( bool );                  bool getTel_2_Contact();          // bool        Tel_2_Contact;
    void setTel_2_Publiciteit( bool );              bool getTel_2_Publiciteit();      // bool        Tel_2_Publiciteit;
    void setFax( QString );                         QString getFax();                 // QString     Fax;
    void setFax_Contact( bool );                    bool getFax_Contact();            // bool        Fax_Contact;
    void setFax_Publiciteit( bool );                bool getFax_Publiciteit();        // bool        Fax_Publiciteit;
    void setEMail_1( QString );                     QString getEMail_1();             // QString     EMail_1;
    void setEMail_1_Contact( bool );                bool getEMail_1_Contact();        // bool        EMail_1_Contact;
    void setEMail_1_Publiciteit( bool );            bool getEMail_1_Publiciteit();    // bool     EMail_1_Publiciteit;
    void setEMail_2( QString );                     QString getEMail_2();             // QString     EMail_2;
    void setEMail_2_Contact( bool );                bool getEMail_2_Contact();        // bool        EMail_2_Contact;
    void setEMail_2_Publiciteit( bool );            bool getEMail_2_Publiciteit();    // bool     EMail_2_Publiciteit;
    void setAdres_Contact( bool );                  bool getAdres_Contact();          // bool        Adres_Contact;
    void setAdres_Publiciteit( bool );              bool getAdres_Publiciteit();      // bool        Adres_Publiciteit;
    void setWebsite( QString );                     QString getWebsite();             // QString     Website;
    void setFacebook( QString );                    QString getFacebook();            // QString     Facebook;
    void setLinked_in( QString );                   QString getLinked_in();           // QString     Linked_in;
    void setRefBijRelatie( QString );               QString getRefBijRelatie();       // QString     RefBijRelatie;
    void setNACECode( QString );                    QString getNACECode();            // QString     NACECode;
    void setMailingCode( QString );                 QString getMailingCode();         // QString     MailingCode;
    void setGeboortedatum( QDate );                 QDate getGeboortedatum();         // QDate       Geboortedatum;
    void setGeboorteplaats( QString );              QString getGeboorteplaats();      // QString     Geboorteplaats;
    void setAantalKinderen( int );                  int getAantalKinderen();          // int         AantalKinderen;
    void setHobby( QString );                       QString getHobby();               // QString     Hobby;
    void setBTWRegime_ID( int );                    int getBTWRegime_ID();            // int         BTWRegime_ID;
    void setBTWAutorisatiecode( QString );          QString getBTWAutorisatiecode();  // QString  BTWAutorisatiecode;
    void setBKHCategorie_ID( int );                 int getBKHCategorie_ID();         // int         BKHCategorie_ID;
    void setKortingsCategorie_ID( int );            int getKortingsCategorie_ID();    // int  KortingsCategorie_ID;
    void setKredietlimiet( double );                double getKredietlimiet();        // double      Kredietlimiet;
    void setBetalingstermijnID( int );              int getBetalingstermijnID();      // int         BetalingstermijnID;
    void setBankrekening_1( QString );              QString getBankrekening_1();      // QString     Bankrekening_1;
    void setIban_1( QString );                      QString getIban_1();              // QString     Iban_1;
    void setBankrekening_2( QString );              QString getBankrekening_2();      // QString     Bankrekening_2;
    void setIban_2( QString );                      QString getIban_2();              // QString     Iban_2;
    void setPopUpTekst( QString );                  QString getPopUpTekst();          // QString     PopUpTekst;
    void setOpmerking( QString );                   QString getOpmerking();           // QString     Opmerking;
    void setID_1( int );                            int getID_1();                    // int         ID_1;
    void setID_2( int );                            int getID_2();                    // int         ID_2;
    void setID_3( int );                            int getID_3();                    // int         ID_3;
    void setID_4( int );                            int getID_4();                    // int         ID_4;
    void setID_5( int );                            int getID_5();                    // int         ID_5;
    void setIDCardNummer( QString );                QString getIDCardNummer();        // QString     IDCardNummer;
    void setRezivNummer( QString );                 QString getRezivNummer();         // QString     RezivNummer;
    void setIDCardUitgereiktTe( QString );          QString getIDCardUitgereiktTe();  // QString  IDCardUitgereiktTe;
    void setIDGeldigVan( QDate );                   QDate getIDGeldigVan();           // QDate       IDGeldigVan;
    void setIDGeldigTot( QDate );                   QDate getIDGeldigTot();           // QDate       IDGeldigTot;
    void setFlag_1( bool );                         bool getFlag_1();                 // bool        Flag_1;
    void setFlag_2( bool );                         bool getFlag_2();                 // bool        Flag_2;
    void setFlag_3( bool );                         bool getFlag_3();                 // bool        Flag_3;
    void setFlag_4( bool );                         bool getFlag_4();                 // bool        Flag_4;
    void setFlag_5( bool );                         bool getFlag_5();                 // bool        Flag_5;
    void setFlag_6( bool );                         bool getFlag_6();                 // bool        Flag_6;
    void setFlag_7( bool );                         bool getFlag_7();                 // bool        Flag_7;
    void setFlag_8( bool );                         bool getFlag_8();                 // bool        Flag_8;
    void setFlag_9( bool );                         bool getFlag_9();                 // bool        Flag_9;
    void setFlag_10( bool );                        bool getFlag_10();                // bool        Flag_10;
    void setVrijTekst_1( QString );                 QString getVrijTekst_1();         // QString     VrijTekst_1;
    void setVrijTekst_2( QString );                 QString getVrijTekst_2();         // QString     VrijTekst_2;
    void setVrijTekst_3( QString );                 QString getVrijTekst_3();         // QString     VrijTekst_3;
    void setVrijTekst_4( QString );                 QString getVrijTekst_4();         // QString     VrijTekst_4;
    void setVrijTekst_5( QString );                 QString getVrijTekst_5();         // QString     VrijTekst_5;
    void setVrijNum_1( double );                    double getVrijNum_1();            // double      VrijNum_1;
    void setVrijNum_2( double );                    double getVrijNum_2();            // double      VrijNum_2;
    void setVrijNum_3( double );                    double getVrijNum_3();            // double      VrijNum_3;
    void setVrijNum_4( double );                    double getVrijNum_4();            // double      VrijNum_4;
    void setVrijNum_5( double );                    double getVrijNum_5();            // double      VrijNum_5;
    void setLastModifyBy( QString );                QString getLastModifyBy();        // QString     LastModifyBy;
    void setLastModyfyOn( QDateTime );              QDateTime getLastModyfyOn();      // QDateTime   LastModyfyOn;
    void setCreatedBy( QString );                   QString getCreatedBy();           // QString     CreatedBy;
    void setCreatedOn( QDateTime );                  QDateTime getCreatedOn();         // QDateTime   CreatedOn;


private:
    int         Relatie_ID;                 // relatie_id serial NOT NULL,
    QString     Naam;                       // naam character varying,
    bool        IsFirmaNaam;                // is_firma_naam boolean,
    QString     Voornaam;                   // voornaam character varying,
    QString     Aankoper;                   // aankoper character varying,
    bool        IsBedrijf;                  // is_bedrijf boolean,
    QString     Adres;                      // adres character varying,
    QString     NrBus;                      // nr_bus character varying,
    int         Gemeente_ID;                // gemeente_id integer,
    QString     LandCode;                   // land_code character varying,
    int         Taal_ID;                    // taal_id integer,
    QString     Tel_1;                      // tel_1 character varying,
    bool        Tel_1_Contact;              // tel_1_contact boolean,
    bool        Tel_1_Publiciteit;          // tel_1_publiciteit boolean,
    QString     GSM_1;                      // gsm_1 character varying,
    bool        GSM_1_Contact;              // gsm_1_contact boolean,
    bool        GSM_1_Publiciteit;          // gsm_1_publiciteit boolean,
    int         Aanspreking_ID;             // aanspreking_id integer,
    QString     BTWNummer;                  // btw_nummer character varying,
    int         Firma_ID;                   // firma_id integer,
    int         Site_ID;                    // site_id integer,
    int         Afdeling_ID;                // afdeling_id integer,
    int         Gebruiker_ID;               // gebruiker_id integer,
    QString     GeslachtCode;               // geslacht_code character(1),
    QString     Herkomst;                   // herkomst character varying,
    QString     Beroep;                     // beroep character varying,
    bool        IsProspect;                 // is_prospect boolean,
    bool        IsKlant;                    // is_klant boolean,
    bool        IsLeverancier;              // is_leverancier boolean,
    bool        IsBenaderbaar;              // is_benaderbaar boolean,
    bool        IsDeelnemer;                // is_deelnemer boolean,
    bool        IsVerhuisd;                 // is_verhuisd boolean,
    bool        IsInactief;                 // is_inactief boolean,
    bool        IsLopendeKlacht;            // is_lopende_klacht boolean,
    bool        IsOverleden;                // is_overleden boolean,
    QString     Tel_2;                      // tel_2 character varying,
    bool        Tel_2_Contact;              // tel_2_contact boolean,
    bool        Tel_2_Publiciteit;          // tel_2_publiciteit boolean,
    QString     Fax;                        // fax character varying,
    bool        Fax_Contact;                // fax_contact boolean,
    bool        Fax_Publiciteit;            // fax_publiciteit boolean,
    QString     EMail_1;                    // email_1 character varying,
    bool        EMail_1_Contact;            // email_1_contact boolean,
    bool        EMail_1_Publiciteit;        // email_1_publiciteit boolean,
    QString     EMail_2;                    // email_2 character varying,
    bool        EMail_2_Contact;            // email_2_contact boolean,
    bool        EMail_2_Publiciteit;        // email_2_publiciteit boolean,
    bool        Adres_Contact;              // adres_contact boolean,
    bool        Adres_Publiciteit;          // adres_publiciteit boolean,
    QString     Website;                    // website character varying,
    QString     Facebook;                   // facebook character varying,
    QString     Linked_in;                  // linked_in character varying,
    QString     RefBijRelatie;              // ref_bij_relatie character varying,
    QString     NACECode;                   // nace_code character varying,
    QString     MailingCode;                // mailing_code character varying,
    QDate       Geboortedatum;              // geboortedatum date,
    QString     Geboorteplaats;             // geboorteplaats character varying,
    int         AantalKinderen;             // aantal_kinderen integer,
    QString     Hobby;                      // hobby character varying,
    int         BTWRegime_ID;               // btw_regime_id integer,
    QString     BTWAutorisatiecode;         // btw_autorisatiecode character varying,
    int         BKHCategorie_ID;            // bkh_categorie_id integer,
    int         KortingsCategorie_ID;       // kortings_categorie_id integer,
    double      Kredietlimiet;              // kredietlimiet money,
    int         BetalingstermijnID;         // betalingstermijn_id integer,
    QString     Bankrekening_1;             //bankrekening_1 character varying,
    QString     Iban_1;                     // iban_1 character varying,
    QString     Bankrekening_2;             // bankrekening_2 character varying,
    QString     Iban_2;                     // iban_2 character varying,
    QString     PopUpTekst;                 // pop_up_tekst character varying,
    QString     Opmerking;                  // opmerking character varying,
    int         ID_1;                       // id_1 integer,
    int         ID_2;                       // id_2 integer,
    int         ID_3;                       // id_3 integer,
    int         ID_4;                       // id_4 integer,
    int         ID_5;                       // id_5 integer,
    QString     IDCardNummer;               // idcard_nummer character varying,
    QString     RezivNummer;                // reziv_nummer character varying,
    QString     IDCardUitgereiktTe;         // idcard_uitgereikt_te character varying,
    QDate       IDGeldigVan;                // id_geldig_van date,
    QDate       IDGeldigTot;                // id_geldig_tot date,
    bool        Flag_1;                     // flag_1 boolean,
    bool        Flag_2;                     // flag_2 boolean,
    bool        Flag_3;                     // flag_3 boolean,
    bool        Flag_4;                     // flag_4 boolean,
    bool        Flag_5;                     // flag_5 boolean,
    bool        Flag_6;                     // flag_6 boolean,
    bool        Flag_7;                     // flag_7 boolean,
    bool        Flag_8;                     // flag_8 boolean,
    bool        Flag_9;                     // flag_9 boolean,
    bool        Flag_10;                    // flag_10 boolean,
    QString     VrijTekst_1;                // vrij_tekst_1 character varying,
    QString     VrijTekst_2;                // vrij_tekst_2 character varying,
    QString     VrijTekst_3;                // vrij_tekst_3 character varying,
    QString     VrijTekst_4;                // vrij_tekst_4 character varying,
    QString     VrijTekst_5;                // vrij_tekst_5 character varying,
    double      VrijNum_1;                  // vrij_num_1 numeric(4,0),
    double      VrijNum_2;                  // vrij_num_2 numeric(4,0),
    double      VrijNum_3;                  // vrij_num_3 numeric(4,0),
    double      VrijNum_4;                  // vrij_num_4 numeric(4,0),
    double      VrijNum_5;                  // vrij_num_5 numeric(4,0),
    QString     LastModifyBy;               // last_modify_by character varying,
    QDateTime   LastModyfyOn;               // last_modify_on timestamp with time zone,
    QString     CreatedBy;                  // created_by character varying,
    QDateTime   CreatedOn;                  // created_on timestamp with time zone,

    // UUID Type



};

#endif // RELATIES_H
