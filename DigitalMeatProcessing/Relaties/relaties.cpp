#include "relaties.h"
#include "../CommonObjects/commonobjects.h"





//------------------------------------------------------------------------------------
//  Properties
//

void Relaties::setRelatie_ID(int id) { Relatie_ID = id; }                                                       int Relaties::getRelatie_ID() { return Relatie_ID; }                    // int         Relatie_ID
void Relaties::setNaam( QString _Naam ) { Naam = _Naam; }                                                       QString Relaties::getNaam() { return Naam; }                            // QString     Naam;
void Relaties::setIsFirmaNaam( bool _IsFirmaNaam ) { IsFirmaNaam = _IsFirmaNaam; }                              bool Relaties::getIsFirmaNaam() { return IsFirmaNaam; }                 // bool        IsFirmaNaam;
void Relaties::setVoornaam( QString _Voornaam ) { Voornaam = _Voornaam; }                                       QString Relaties::getVoornaam() { return Voornaam; }                    // QString     Voornaam;
void Relaties::setAankoper( QString _Aankoper ) { Aankoper = _Aankoper; }                                       QString Relaties::getAankoper() { return Aankoper; }                    // QString     Aankoper;
void Relaties::setIsBedrijf( bool _IsBedrijf ) { IsBedrijf = _IsBedrijf; }                                      bool Relaties::getIsBedrijf() { return IsBedrijf; }                     // bool        IsBedrijf;
void Relaties::setAdres( QString _Adres ) { Adres = _Adres; }                                                   QString Relaties::getAdres() { return Adres; }                          // QString     Adres;
void Relaties::setNrBus( QString _NrBus ) { NrBus = _NrBus; }                                                   QString Relaties::getNrBus() { return NrBus; }                          // QString     NrBus;
void Relaties::setGemeente_ID(int gemeente_id) { Gemeente_ID = gemeente_id; }                                   int Relaties::getGemeente_ID() { return Gemeente_ID; }                  // int         Gemeente_ID;
void Relaties::setLandCode(QString landcode) { LandCode = landcode; }                                           QString Relaties::getLandCode() { return LandCode; }                    // QString     LandCode;
void Relaties::setTaal_ID( int _Taal_ID ) { Taal_ID = _Taal_ID; }                                               int Relaties::getTaal_ID() { return Taal_ID; }                          // int         Taal_ID;
void Relaties::setTel_1( QString _Tel_1 ) { Tel_1 = _Tel_1; }                                                   QString Relaties::getTel_1() { return Tel_1; }                          // QString     Tel_1;
void Relaties::setTel_1_Contact( bool _Tel_1_Contact ) { Tel_1_Contact = _Tel_1_Contact; }                      bool Relaties::getTel_1_Contact() { return Tel_1_Contact; }             // bool        Tel_1_Contact;
void Relaties::setTel_1_Publiciteit( bool _Tel_1_Publiciteit ) { Tel_1_Publiciteit = _Tel_1_Publiciteit; }      bool Relaties::getTel_1_Publiciteit() { return Tel_1_Publiciteit; }     // bool        Tel_1_Publiciteit;
void Relaties::setGSM_1( QString _GSM_1 ) { GSM_1 = _GSM_1; }                                                   QString Relaties::getGSM_1() { return GSM_1; }                          // QString     GSM_1;

void Relaties::setGSM_1_Contact( bool _GSM_1_Contact ) { GSM_1_Contact = _GSM_1_Contact; }                      bool Relaties::getGSM_1_Contact() { return GSM_1_Contact; }             // bool        GSM_1_Contact;
void Relaties::setGSM_1_Publiciteit( bool _GSM_1_Publiciteit ) { GSM_1_Publiciteit = _GSM_1_Publiciteit; }      bool Relaties::getGSM_1_Publiciteit() { return GSM_1_Publiciteit; }     // bool        GSM_1_Publiciteit;
void Relaties::setAanspreking_ID( int _Aanspreking_ID ) { Aanspreking_ID = _Aanspreking_ID; }                   int Relaties::getAanspreking_ID() { return Aanspreking_ID; }            // int         Aanspreking_ID;
void Relaties::setBTWNummer( QString _BTWNummer ) { BTWNummer = _BTWNummer; }                                   QString Relaties::getBTWNummer() { return BTWNummer; }                  // QString     BTWNummer;
void Relaties::setFirma_ID( int _Firma_ID ) { Firma_ID = _Firma_ID; }                                           int Relaties::getFirma_ID() { return Firma_ID; }                        // int         Firma_ID;
void Relaties::setSite_ID( int _Site_ID ) { Site_ID = _Site_ID; }                                               int Relaties::getSite_ID() { return Site_ID; }                          // int         Site_ID;
void Relaties::setAfdeling_ID( int _Afdeling_ID ) { Afdeling_ID = _Afdeling_ID; }                               int Relaties::getAfdeling_ID() { return Afdeling_ID; }                  // int         Afdeling_ID;
void Relaties::setGebruiker_ID( int _Gebruiker_ID ) { Gebruiker_ID = _Gebruiker_ID; }                           int Relaties::getGebruiker_ID() { return Gebruiker_ID; }                // int         Gebruiker_ID;
void Relaties::setGeslachtCode( QString _GeslachtCode ) { GeslachtCode = _GeslachtCode; }                       QString Relaties::getGeslachtCode() { return GeslachtCode; }            // QString     GeslachtCode;
void Relaties::setHerkomst( QString _Herkomst ) { Herkomst = _Herkomst; }                                       QString Relaties::getHerkomst() { return Herkomst; }                    // QString     Herkomst;
void Relaties::setBeroep( QString _Beroep ) { Beroep = _Beroep; }                                               QString Relaties::getBeroep() { return Beroep; }                        // QString     Beroep;
void Relaties::setIsProspect( bool _IsProspect ) { IsProspect = _IsProspect; }                                  bool Relaties::getIsProspect() { return IsProspect; }                   // bool        IsProspect;
void Relaties::setIsKlant( bool _IsKlant ) { IsKlant = _IsKlant; }                                              bool Relaties::getIsKlant() { return IsKlant; }                         // bool        IsKlant;
void Relaties::setIsLeverancier( bool _IsLeverancier ) { IsLeverancier = _IsLeverancier; }                      bool Relaties::getIsLeverancier() { return IsLeverancier; }             // bool        IsLeverancier;
void Relaties::setIsBenaderbaar( bool _IsBenaderbaar ) { IsBenaderbaar = _IsBenaderbaar; }                      bool Relaties::getIsBenaderbaar() { return IsBenaderbaar; }             // bool        IsBenaderbaar;
void Relaties::setIsDeelnemer( bool _IsDeelnemer ) { IsDeelnemer = _IsDeelnemer; }                              bool Relaties::getIsDeelnemer() { return IsDeelnemer; }                 // bool        IsDeelnemer;
void Relaties::setIsVerhuisd( bool _IsVerhuisd ) { IsVerhuisd = _IsVerhuisd; }                                  bool Relaties::getIsVerhuisd() { return IsVerhuisd; }                   // bool        IsVerhuisd;
void Relaties::setIsInactief( bool _IsInactief ) { IsInactief = _IsInactief; }                                  bool Relaties::getIsInactief() { return IsInactief; }                   // bool        IsInactief;
void Relaties::setIsLopendeKlacht( bool _IsLopendeKlacht ) { IsLopendeKlacht = _IsLopendeKlacht; }              bool Relaties::getIsLopendeKlacht() { return IsLopendeKlacht; }         // bool        IsLopendeKlacht;
void Relaties::setIsOverleden( bool _IsOverleden ) { IsOverleden = _IsOverleden; }                              bool Relaties::getIsOverleden() { return IsOverleden; }                 // bool        IsOverleden;
void Relaties::setTel_2( QString _Tel_2 ) { Tel_2 = _Tel_2; }                                                   QString Relaties::getTel_2() { return Tel_2; }                          // QString     Tel_2;
void Relaties::setTel_2_Contact( bool _Tel_2_Contact ) { Tel_2_Contact = _Tel_2_Contact; }                      bool Relaties::getTel_2_Contact() { return Tel_2_Contact; }             // bool        Tel_2_Contact;
void Relaties::setTel_2_Publiciteit( bool _Tel_2_Publiciteit ) { Tel_2_Publiciteit = _Tel_2_Publiciteit; }      bool Relaties::getTel_2_Publiciteit() { return Tel_2_Publiciteit; }     // bool        Tel_2_Publiciteit;
void Relaties::setFax( QString _Fax ) { Fax = _Fax; }                                                           QString Relaties::getFax() { return Fax; }                              // QString     Fax;
void Relaties::setFax_Contact( bool _Fax_Contact ) { Fax_Contact = _Fax_Contact; }                              bool Relaties::getFax_Contact() { return Fax_Contact; }                 // bool        Fax_Contact;
void Relaties::setFax_Publiciteit( bool _Fax_Publiciteit ) { Fax_Publiciteit = _Fax_Publiciteit; }              bool Relaties::getFax_Publiciteit() { return Fax_Publiciteit; }         // bool        Fax_Publiciteit;
void Relaties::setEMail_1( QString _EMail_1 ) { EMail_1 = _EMail_1; }                                           QString Relaties::getEMail_1() { return EMail_1; }                      // QString     EMail_1;
void Relaties::setEMail_1_Contact( bool _EMail_1_Contact ) { EMail_1_Contact = _EMail_1_Contact; }              bool Relaties::getEMail_1_Contact() { return EMail_1_Contact; }         // bool        EMail_1_Contact;
void Relaties::setEMail_1_Publiciteit( bool _EMail_1_Publiciteit ) { EMail_1_Publiciteit = _EMail_1_Publiciteit; } bool Relaties::getEMail_1_Publiciteit() { return EMail_1_Publiciteit; } // bool     EMail_1_Publiciteit;
void Relaties::setEMail_2( QString _EMail_2 ) { EMail_2 = _EMail_2; }                                           QString Relaties::getEMail_2() { return EMail_2; }                      // QString     EMail_2;
void Relaties::setEMail_2_Contact( bool _EMail_2_Contact ) { EMail_2_Contact = _EMail_2_Contact; }              bool Relaties::getEMail_2_Contact() { return EMail_2_Contact; }         // bool        EMail_2_Contact;
void Relaties::setEMail_2_Publiciteit( bool _EMail_2_Publiciteit ) { EMail_2_Publiciteit = _EMail_2_Publiciteit; } bool Relaties::getEMail_2_Publiciteit() { return EMail_2_Publiciteit; } // bool     EMail_2_Publiciteit;
void Relaties::setAdres_Contact( bool _Adres_Contact ) { Adres_Contact = _Adres_Contact; }                      bool Relaties::getAdres_Contact() { return Adres_Contact; }             // bool        Adres_Contact;
void Relaties::setAdres_Publiciteit( bool _Adres_Publiciteit ) { Adres_Publiciteit = _Adres_Publiciteit; }      bool Relaties::getAdres_Publiciteit() { return Adres_Publiciteit; }     // bool        Adres_Publiciteit;
void Relaties::setWebsite( QString _Website ) { Website = _Website; }                                           QString Relaties::getWebsite() { return Website; }                      // QString     Website;
void Relaties::setFacebook( QString _Facebook ) { Facebook = _Facebook; }                                       QString Relaties::getFacebook() { return Facebook; }                    // QString     Facebook;
void Relaties::setLinked_in( QString _Linked_in ) { Linked_in = _Linked_in; }                                   QString Relaties::getLinked_in() { return Linked_in; }                  // QString     Linked_in;
void Relaties::setRefBijRelatie( QString _RefBijRelatie ) { RefBijRelatie = _RefBijRelatie; }                   QString Relaties::getRefBijRelatie() { return RefBijRelatie; }          // QString     RefBijRelatie;
void Relaties::setNACECode( QString _NACECode ) { NACECode = _NACECode; }                                       QString Relaties::getNACECode() { return NACECode; }                    // QString     NACECode;
void Relaties::setMailingCode( QString _MailingCode ) { MailingCode = _MailingCode; }                           QString Relaties::getMailingCode() { return MailingCode; }              // QString     MailingCode;
void Relaties::setGeboortedatum( QDate _Geboortedatum ) { Geboortedatum = _Geboortedatum; }                     QDate Relaties::getGeboortedatum() { return Geboortedatum; }            // QDate       Geboortedatum;
void Relaties::setGeboorteplaats( QString _Geboorteplaats ) { Geboorteplaats = _Geboorteplaats; }               QString Relaties::getGeboorteplaats() { return Geboorteplaats; }        // QString     Geboorteplaats;
void Relaties::setAantalKinderen( int _AantalKinderen ) { AantalKinderen = _AantalKinderen; }                   int Relaties::getAantalKinderen() { return AantalKinderen; }            // int         AantalKinderen;
void Relaties::setHobby( QString _Hobby ) { Hobby = _Hobby; }                                                   QString Relaties::getHobby() { return Hobby; }                          // QString     Hobby;
void Relaties::setBTWRegime_ID( int _BTWRegime_ID ) { BTWRegime_ID = _BTWRegime_ID; }                           int Relaties::getBTWRegime_ID() { return BTWRegime_ID; }                // int         BTWRegime_ID;
void Relaties::setBTWAutorisatiecode( QString _BTWAutorisatiecode ) { BTWAutorisatiecode = _BTWAutorisatiecode; } QString Relaties::getBTWAutorisatiecode() { return BTWAutorisatiecode; } // QString  BTWAutorisatiecode;
void Relaties::setBKHCategorie_ID( int _BKHCategorie_ID ) { BKHCategorie_ID = _BKHCategorie_ID; }               int Relaties::getBKHCategorie_ID() { return BKHCategorie_ID; }          // int         BKHCategorie_ID;
void Relaties::setKortingsCategorie_ID( int _KortingsCategorie_ID ) { KortingsCategorie_ID = _KortingsCategorie_ID; } int Relaties::getKortingsCategorie_ID() { return KortingsCategorie_ID; } // int  KortingsCategorie_ID;
void Relaties::setKredietlimiet( double _Kredietlimiet ) { Kredietlimiet = _Kredietlimiet; }                    double Relaties::getKredietlimiet() { return Kredietlimiet; }           // double      Kredietlimiet;
void Relaties::setBetalingstermijnID( int _BetalingstermijnID ) { BetalingstermijnID = _BetalingstermijnID; }   int Relaties::getBetalingstermijnID() { return BetalingstermijnID; }    // int         BetalingstermijnID;
void Relaties::setBankrekening_1( QString _Bankrekening_1 ) { Bankrekening_1 = _Bankrekening_1; }               QString Relaties::getBankrekening_1() { return Bankrekening_1; }        // QString     Bankrekening_1;
void Relaties::setIban_1( QString _Iban_1 ) { Iban_1 = _Iban_1; }                                               QString Relaties::getIban_1() { return Iban_1; }                        // QString     Iban_1;
void Relaties::setBankrekening_2( QString _Bankrekening_2 ) { Bankrekening_2 = _Bankrekening_2; }               QString Relaties::getBankrekening_2() { return Bankrekening_2; }        // QString     Bankrekening_2;
void Relaties::setIban_2( QString _Iban_2 ) { Iban_2 = _Iban_2; }                                               QString Relaties::getIban_2() { return Iban_2; }                        // QString     Iban_2;
void Relaties::setPopUpTekst( QString _PopUpTekst ) { PopUpTekst = _PopUpTekst; }                               QString Relaties::getPopUpTekst() { return PopUpTekst; }                // QString     PopUpTekst;
void Relaties::setOpmerking( QString _Opmerking ) { Opmerking = _Opmerking; }                                   QString Relaties::getOpmerking() { return Opmerking; }                  // QString     Opmerking;
void Relaties::setID_1( int _ID_1 ) { ID_1 = _ID_1; }                                                           int Relaties::getID_1() { return ID_1; }                                // int         ID_1;
void Relaties::setID_2( int _ID_2 ) { ID_2 = _ID_2; }                                                           int Relaties::getID_2() { return ID_2; }                                // int         ID_2;
void Relaties::setID_3( int _ID_3 ) { ID_3 = _ID_3; }                                                           int Relaties::getID_3() { return ID_3; }                                // int         ID_3;
void Relaties::setID_4( int _ID_4 ) { ID_4 = _ID_4; }                                                           int Relaties::getID_4() { return ID_4; }                                // int         ID_4;
void Relaties::setID_5( int _ID_5 ) { ID_5 = _ID_5; }                                                           int Relaties::getID_5() { return ID_5; }                                // int         ID_5;
void Relaties::setIDCardNummer ( QString _IDCardNummer  ) { IDCardNummer  = _IDCardNummer ; }                   QString Relaties::getIDCardNummer () { return IDCardNummer ; }          // QString     IDCardNummer;
void Relaties::setRezivNummer( QString _RezivNummer ) { RezivNummer = _RezivNummer; }                           QString Relaties::getRezivNummer() { return RezivNummer; }              // QString     RezivNummer;
void Relaties::setIDCardUitgereiktTe( QString _IDCardUitgereiktTe ) { IDCardUitgereiktTe = _IDCardUitgereiktTe; } QString Relaties::getIDCardUitgereiktTe() { return IDCardUitgereiktTe; } // QString  IDCardUitgereiktTe;
void Relaties::setIDGeldigVan( QDate _IDGeldigVan ) { IDGeldigVan = _IDGeldigVan; }                             QDate Relaties::getIDGeldigVan() { return IDGeldigVan; }                // QDate       IDGeldigVan;
void Relaties::setIDGeldigTot( QDate _IDGeldigTot ) { IDGeldigTot = _IDGeldigTot; }                             QDate Relaties::getIDGeldigTot() { return IDGeldigTot; }                // QDate       IDGeldigTot;
void Relaties::setFlag_1( bool _Flag_1 ) { Flag_1 = _Flag_1; }                                                  bool Relaties::getFlag_1() { return Flag_1; }                           // bool        Flag_1;
void Relaties::setFlag_2( bool _Flag_2 ) { Flag_2 = _Flag_2; }                                                  bool Relaties::getFlag_2() { return Flag_2; }                           // bool        Flag_2;
void Relaties::setFlag_3( bool _Flag_3 ) { Flag_3 = _Flag_3; }                                                  bool Relaties::getFlag_3() { return Flag_3; }                           // bool        Flag_3;
void Relaties::setFlag_4( bool _Flag_4 ) { Flag_4 = _Flag_4; }                                                  bool Relaties::getFlag_4() { return Flag_4; }                           // bool        Flag_4;
void Relaties::setFlag_5( bool _Flag_5 ) { Flag_5 = _Flag_5; }                                                  bool Relaties::getFlag_5() { return Flag_5; }                           // bool        Flag_5;
void Relaties::setFlag_6( bool _Flag_6 ) { Flag_6 = _Flag_6; }                                                  bool Relaties::getFlag_6() { return Flag_6; }                           // bool        Flag_6;
void Relaties::setFlag_7( bool _Flag_7 ) { Flag_7 = _Flag_7; }                                                  bool Relaties::getFlag_7() { return Flag_7; }                           // bool        Flag_7;
void Relaties::setFlag_8( bool _Flag_8 ) { Flag_8 = _Flag_8; }                                                  bool Relaties::getFlag_8() { return Flag_8; }                           // bool        Flag_8;
void Relaties::setFlag_9( bool _Flag_9 ) { Flag_9 = _Flag_9; }                                                  bool Relaties::getFlag_9() { return Flag_9; }                           // bool        Flag_9;
void Relaties::setFlag_10( bool _Flag_10 ) { Flag_10 = _Flag_10; }                                              bool Relaties::getFlag_10() { return Flag_10; }                         // bool        Flag_10;
void Relaties::setVrijTekst_1( QString _VrijTekst_1 ) { VrijTekst_1 = _VrijTekst_1; }                           QString Relaties::getVrijTekst_1() { return VrijTekst_1; }              // QString     VrijTekst_1;
void Relaties::setVrijTekst_2( QString _VrijTekst_2 ) { VrijTekst_2 = _VrijTekst_2; }                           QString Relaties::getVrijTekst_2() { return VrijTekst_2; }              // QString     VrijTekst_2;
void Relaties::setVrijTekst_3( QString _VrijTekst_3 ) { VrijTekst_3 = _VrijTekst_3; }                           QString Relaties::getVrijTekst_3() { return VrijTekst_3; }              // QString     VrijTekst_3;
void Relaties::setVrijTekst_4( QString _VrijTekst_4 ) { VrijTekst_4 = _VrijTekst_4; }                           QString Relaties::getVrijTekst_4() { return VrijTekst_4; }              // QString     VrijTekst_4;
void Relaties::setVrijTekst_5( QString _VrijTekst_5 ) { VrijTekst_5 = _VrijTekst_5; }                           QString Relaties::getVrijTekst_5() { return VrijTekst_5; }              // QString     VrijTekst_5;
void Relaties::setVrijNum_1( double _VrijNum_1 ) { VrijNum_1 = _VrijNum_1; }                                    double Relaties::getVrijNum_1() { return VrijNum_1; }                   // double      VrijNum_1;
void Relaties::setVrijNum_2( double _VrijNum_2 ) { VrijNum_2 = _VrijNum_2; }                                    double Relaties::getVrijNum_2() { return VrijNum_2; }                   // double      VrijNum_2;
void Relaties::setVrijNum_3( double _VrijNum_3 ) { VrijNum_3 = _VrijNum_3; }                                    double Relaties::getVrijNum_3() { return VrijNum_3; }                   // double      VrijNum_3;
void Relaties::setVrijNum_4( double _VrijNum_4 ) { VrijNum_4 = _VrijNum_4; }                                    double Relaties::getVrijNum_4() { return VrijNum_4; }                   // double      VrijNum_4;
void Relaties::setVrijNum_5( double _VrijNum_5 ) { VrijNum_5 = _VrijNum_5; }                                    double Relaties::getVrijNum_5() { return VrijNum_5; }                   // double      VrijNum_5;
void Relaties::setLastModifyBy( QString _LastModifyBy ) { LastModifyBy = _LastModifyBy; }                       QString Relaties::getLastModifyBy() { return LastModifyBy; }            // QString     LastModifyBy;
void Relaties::setLastModyfyOn( QDateTime _LastModyfyOn ) { LastModyfyOn = _LastModyfyOn; }                     QDateTime Relaties::getLastModyfyOn() { return LastModyfyOn; }          // QDateTime   LastModyfyOn;
void Relaties::setCreatedBy( QString _CreatedBy ) { CreatedBy = _CreatedBy; }                                   QString Relaties::getCreatedBy() { return CreatedBy; }                  // QString     CreatedBy;
void Relaties::setCreatedOn( QDateTime _CreatedOn ) { CreatedOn = _CreatedOn; }                                 QDateTime Relaties::getCreatedOn() { return CreatedOn; }                // QDateTime   CreatedOn;


//------------------------------------------------------------------------------------
//   Constructors
//

Relaties::Relaties()
{
    clear();
}

Relaties::Relaties(int id)
{
    Relatie_ID = id;
    read();
}

//---------------------------------------------------------------------------------------
//   Methodes
//



void Relaties::clear()
{
    Relatie_ID = 1;
    read();
}

void Relaties::read()
{
    CommonObjects::OpenDatabase();
    QSqlQuery qry;
    bool status = false;
    status = qry.prepare("SELECT * FROM relaties.relaties WHERE relatie_id = :v_ID;");
    if ( status )
    {
        qry.bindValue(":v_ID", Relatie_ID);                             //    relatie_id serial NOT NULL,
        status = qry.exec();
        if (status )
        {
            status = qry.next();
            if (status )
            {
                Naam = qry.value("naam").toString();                            //    naam character varying,
                IsFirmaNaam = qry.value("is_firma_naam").toBool();              //    is_firma_naam boolean,
                Voornaam = qry.value("voornaam").toString();                    //    voornaam character varying,
                Aankoper = qry.value("aankoper").toString();                    //    aankoper character varying,
                IsBedrijf = qry.value("is_bedrijf").toBool();                   //    is_bedrijf boolean,
                Adres = qry.value("adres").toString();                          //    adres character varying,
                NrBus = qry.value("nr_bus").toString();                         //    nr_bus character varying,
                Gemeente_ID = qry.value("gemeente_id").toInt();                 //    gemeente_id integer,
                LandCode = qry.value("land_code").toString();                   //    land_code character varying,
                Taal_ID = qry.value("taal_id").toInt();                         //    taal_id integer,
                Tel_1 = qry.value("tel_1").toString();                          //    tel_1 character varying,
                Tel_1_Contact = qry.value("tel_1_contact").toBool();            //    tel_1_contact boolean,
                Tel_1_Publiciteit = qry.value("tel_1_publiciteit").toBool();    //    tel_1_publiciteit boolean,
                GSM_1 = qry.value("gsm_1").toString();                          //    gsm_1 character varying,
                GSM_1_Contact = qry.value("gsm_1_contact").toBool();            //    gsm_1_contact boolean,
                GSM_1_Publiciteit = qry.value("gsm_1_publiciteit").toBool();    //    gsm_1_publiciteit boolean,
                Aanspreking_ID = qry.value("aanspreking_id").toInt();           //    aanspreking_id integer,
                BTWNummer = qry.value("btw_nummer").toString();                 //    btw_nummer character varying,
                Firma_ID = qry.value("firma_id").toInt();                       //    firma_id integer,
                Site_ID = qry.value("site_id").toInt();                         //    site_id integer,
                Afdeling_ID = qry.value("afdeling_id").toInt();                 //    afdeling_id integer,
                Gebruiker_ID = qry.value("gebruiker_id").toInt();               //    gebruiker_id integer,
                GeslachtCode = qry.value("geslacht_code").toString();           //    geslacht_code character(1),
                Herkomst = qry.value("herkomst").toString();                    //    herkomst character varying,
                Beroep = qry.value("beroep").toString();                        //    beroep character varying,
                IsProspect = qry.value("is_prospect").toBool();                 //    is_prospect boolean,
                IsKlant = qry.value("is_klant").toBool();                       //    is_klant boolean,
                IsLeverancier = qry.value("is_leverancier").toBool();           //    is_leverancier boolean,
                IsBenaderbaar = qry.value("is_benaderbaar").toBool();           //    is_benaderbaar boolean,
                IsDeelnemer = qry.value("is_deelnemer").toBool();               //    is_deelnemer boolean,
                IsVerhuisd = qry.value("is_verhuisd").toBool();                 //    is_verhuisd boolean,
                IsInactief = qry.value("is_inactief").toBool();                 //    is_inactief boolean,
                IsLopendeKlacht = qry.value("is_lopende_klacht").toBool();      //    is_lopende_klacht boolean,
                IsOverleden = qry.value("is_overleden").toBool();               //    is_overleden boolean,
                Tel_2 = qry.value("tel_2").toString();                          //    tel_2 character varying,
                Tel_2_Contact = qry.value("tel_2_contact").toBool();            //    tel_2_contact boolean,
                Tel_2_Publiciteit = qry.value("tel_2_publiciteit").toBool();    //    tel_2_publiciteit boolean,
                Fax = qry.value("fax").toString();                              //    fax character varying,
                Fax_Contact = qry.value("fax_contact").toBool();                //    fax_contact boolean,
                Fax_Publiciteit = qry.value("fax_publiciteit").toBool();        //    fax_publiciteit boolean,
                EMail_1 = qry.value("email_1").toString();                      //    email_1 character varying,
                EMail_1_Contact = qry.value("email_1_contact").toBool();        //    email_1_contact boolean,
                EMail_1_Publiciteit = qry.value("email_1_publiciteit").toBool();//    email_1_publiciteit boolean,
                EMail_2 = qry.value("email_2").toString();                      //    email_2 character varying,
                EMail_2_Contact = qry.value("email_2_contact").toBool();        //    email_2_contact boolean,
                EMail_2_Publiciteit = qry.value("email_2_publiciteit").toBool();//    email_2_publiciteit boolean,
                Adres_Contact = qry.value("adres_contact").toBool();            //    adres_contact boolean,
                Adres_Publiciteit = qry.value("adres_publiciteit").toBool();    //    adres_publiciteit boolean,
                Website = qry.value("website").toString();                      //    website character varying,
                Facebook = qry.value("facebook").toString();                    //    facebook character varying,
                Linked_in = qry.value("linked_in").toString();                  //    linked_in character varying,
                RefBijRelatie = qry.value("ref_bij_relatie").toString();        //    ref_bij_relatie character varying,
                NACECode = qry.value("nace_code").toString();                   //    nace_code character varying,
                MailingCode = qry.value("mailing_code").toString();             //    mailing_code character varying,
                Geboortedatum = qry.value("geboortedatum").toDate();            //    geboortedatum date,
                Geboorteplaats = qry.value("geboorteplaats").toString();        //    geboorteplaats character varying,
                AantalKinderen = qry.value("aantal_kinderen").toInt();          //    aantal_kinderen integer,
                Hobby = qry.value("hobby").toString();                          //    hobby character varying,
                BTWRegime_ID = qry.value("btw_regime_id").toInt();              //    btw_regime_id integer,
                BTWAutorisatiecode = qry.value("btw_autorisatiecode").toString();//   btw_autorisatiecode character varying,
                BKHCategorie_ID = qry.value("bkh_categorie_id").toInt();        //    bkh_categorie_id integer,
                KortingsCategorie_ID = qry.value("kortings_categorie_id").toInt();//  kortings_categorie_id integer,
                Kredietlimiet = qry.value("kredietlimiet").toDouble();          //    kredietlimiet money,
                BetalingstermijnID = qry.value("betalingstermijn_id").toInt();  //    betalingstermijn_id integer,
                Bankrekening_1 = qry.value("bankrekening_1").toString();        //    bankrekening_1 character varying,
                Iban_1 = qry.value("iban_1").toString();                        //    iban_1 character varying,
                Bankrekening_2 = qry.value("bankrekening_2").toString();        //    bankrekening_2 character varying,
                Iban_2 = qry.value("iban_2").toString();                        //    iban_2 character varying,
                PopUpTekst = qry.value("pop_up_tekst").toString();              //    pop_up_tekst character varying,
                Opmerking = qry.value("opmerking").toString();                  //    opmerking character varying,
                ID_1 = qry.value("id_1").toInt();                               //    id_1 integer,
                ID_2 = qry.value("id_2").toInt();                               //    id_2 integer,
                ID_3 = qry.value("id_3").toInt();                               //    id_3 integer,
                ID_4 = qry.value("id_4").toInt();                               //    id_4 integer,
                ID_5 = qry.value("id_5").toInt();                               //    id_5 integer,
                IDCardNummer = qry.value("idcard_nummer").toString();           //    idcard_nummer character varying,
                RezivNummer = qry.value("reziv_nummer").toString();             //    reziv_nummer character varying,
                IDCardUitgereiktTe = qry.value("idcard_uitgereikt_te").toString();//  idcard_uitgereikt_te character varying,
                IDGeldigVan = qry.value("id_geldig_van").toDate();              //    id_geldig_van date,
                IDGeldigTot = qry.value("id_geldig_tot").toDate();              //    id_geldig_tot date,
                Flag_1 = qry.value("flag_1").toBool();                          //    flag_1 boolean,
                Flag_2 = qry.value("flag_2").toBool();                          //    flag_2 boolean,
                Flag_3 = qry.value("flag_3").toBool();                          //    flag_3 boolean,
                Flag_4 = qry.value("flag_4").toBool();                          //    flag_4 boolean,
                Flag_5 = qry.value("flag_5").toBool();                          //    flag_5 boolean,
                Flag_6 = qry.value("flag_6").toBool();                          //    flag_6 boolean,
                Flag_7 = qry.value("flag_7").toBool();                          //    flag_7 boolean,
                Flag_8 = qry.value("flag_8").toBool();                          //    flag_8 boolean,
                Flag_9 = qry.value("flag_9").toBool();                          //    flag_9 boolean,
                Flag_10 = qry.value("flag_10").toBool();                        //    flag_10 boolean,
                VrijTekst_1 = qry.value("vrij_tekst_1").toString();             //    vrij_tekst_1 character varying,
                VrijTekst_2 = qry.value("vrij_tekst_2").toString();             //    vrij_tekst_2 character varying,
                VrijTekst_3 = qry.value("vrij_tekst_3").toString();             //    vrij_tekst_3 character varying,
                VrijTekst_4 = qry.value("vrij_tekst_4").toString();             //    vrij_tekst_4 character varying,
                VrijTekst_5 = qry.value("vrij_tekst_5").toString();             //    vrij_tekst_5 character varying,
                VrijNum_1 = qry.value("vrij_num_1").toDouble();                 //    vrij_num_1 numeric(4,0),
                VrijNum_2 = qry.value("vrij_num_2").toDouble();                 //    vrij_num_2 numeric(4,0),
                VrijNum_3 = qry.value("vrij_num_3").toDouble();                 //    vrij_num_3 numeric(4,0),
                VrijNum_4 = qry.value("vrij_num_4").toDouble();                 //    vrij_num_4 numeric(4,0),
                VrijNum_5 = qry.value("vrij_num_5").toDouble();                 //    vrij_num_5 numeric(4,0),
                LastModifyBy = qry.value("last_modify_by").toString();          //    last_modify_by character varying,
                LastModyfyOn = qry.value("last_modify_on").toDateTime();        //    last_modify_on timestamp with time zone,
                CreatedBy = qry.value("created_by").toString();                 //    created_by character varying,
                CreatedOn = qry.value("created_on").toDateTime();               //    created_on timestamp with time zone,
            }
            else
            {
                Relatie_ID = 0;
                qDebug() << "Error bij lezen record (of geen record gevonden)- " << qry.lastError().text();
            }
        }
        else
        {
            Relatie_ID = 0;
            qDebug() << "Error bij uitvoeren Query - " << qry.lastError().text();
        }
    }
    else
    {
        Relatie_ID = 0;
        qDebug() << "Error bij voorbereiding Query - " << qry.lastError().text();
    }

}

void Relaties::save()
{
    QString updateQuery, insertQuery;

    insertQuery =
            "INSERT INTO relaties.relaties( "
            "naam, is_firma_naam, voornaam, aankoper, is_bedrijf, "
            "adres, nr_bus, gemeente_id, land_code, taal_id, tel_1, tel_1_contact, "
            "tel_1_publiciteit, gsm_1, gsm_1_contact, gsm_1_publiciteit, aanspreking_id, "
            "btw_nummer, firma_id, site_id, afdeling_id, gebruiker_id, geslacht_code, "
            "herkomst, beroep, is_prospect, is_klant, is_leverancier, is_benaderbaar, "
            "is_deelnemer, is_verhuisd, is_inactief, is_lopende_klacht, is_overleden, "
            "tel_2, tel_2_contact, tel_2_publiciteit, fax, fax_contact, fax_publiciteit, "
            "email_1, email_1_contact, email_1_publiciteit, email_2, email_2_contact, "
            "email_2_publiciteit, adres_contact, adres_publiciteit, website, "
            "facebook, linked_in, ref_bij_relatie, nace_code, mailing_code, "
            "geboortedatum, geboorteplaats, aantal_kinderen, hobby, btw_regime_id, "
            "btw_autorisatiecode, bkh_categorie_id, kortings_categorie_id, "
            "kredietlimiet, betalingstermijn_id, bankrekening_1, iban_1, bankrekening_2, "
            "iban_2, pop_up_tekst, opmerking, id_1, id_2, id_3, id_4, id_5, "
            "idcard_nummer, reziv_nummer, idcard_uitgereikt_te, id_geldig_van, "
            "id_geldig_tot, flag_1, flag_2, flag_3, flag_4, flag_5, flag_6, "
            "flag_7, flag_8, flag_9, flag_10, vrij_tekst_1, vrij_tekst_2, "
            "vrij_tekst_3, vrij_tekst_4, vrij_tekst_5, vrij_num_1, vrij_num_2, "
            "vrij_num_3, vrij_num_4, vrij_num_5, last_modify_by, last_modify_on, "
            "created_by, created_on"
            ") "
    "VALUES ( "
            ":v_naam, :v_is_firma_naam, :v_voornaam, :v_aankoper, :v_is_bedrijf, "
            ":v_adres, :v_nr_bus, :v_gemeente_id, :v_land_code, :v_taal_id, :v_tel_1, :v_tel_1_contact, "
            ":v_tel_1_publiciteit, :v_gsm_1, :v_gsm_1_contact, :v_gsm_1_publiciteit, :v_aanspreking_id, "
            ":v_btw_nummer, :v_firma_id, :v_site_id, :v_afdeling_id, :v_gebruiker_id, :v_geslacht_code, "
            ":v_herkomst, :v_beroep, :v_is_prospect, :v_is_klant, :v_is_leverancier, :v_is_benaderbaar, "
            ":v_is_deelnemer, :v_is_verhuisd, :v_is_inactief, :v_is_lopende_klacht, :v_is_overleden, "
            ":v_tel_2, :v_tel_2_contact, :v_tel_2_publiciteit, :v_fax, :v_fax_contact, :v_fax_publiciteit, "
            ":v_email_1, :v_email_1_contact, :v_email_1_publiciteit, :v_email_2, :v_email_2_contact, "
            ":v_email_2_publiciteit, :v_adres_contact, :v_adres_publiciteit, :v_website, "
            ":v_facebook, :v_linked_in, :v_ref_bij_relatie, :v_nace_code, :v_mailing_code, "
            ":v_geboortedatum, :v_geboorteplaats, :v_aantal_kinderen, :v_hobby, :v_btw_regime_id, "
            ":v_btw_autorisatiecode, :v_bkh_categorie_id, :v_kortings_categorie_id, "
            ":v_kredietlimiet, :v_betalingstermijn_id, :v_bankrekening_1, :v_iban_1, :v_bankrekening_2, "
            ":v_iban_2, :v_pop_up_tekst, :v_opmerking, :v_id_1, :v_id_2, :v_id_3, :v_id_4, :v_id_5, "
            ":v_idcard_nummer, :v_reziv_nummer, :v_idcard_uitgereikt_te, :v_id_geldig_van, "
            ":v_id_geldig_tot, :v_flag_1, :v_flag_2, :v_flag_3, :v_flag_4, :v_flag_5, :v_flag_6, "
            ":v_flag_7, :v_flag_8, :v_flag_9, :v_flag_10, :v_vrij_tekst_1, :v_vrij_tekst_2, "
            ":v_vrij_tekst_3, :v_vrij_tekst_4, :v_vrij_tekst_5, :v_vrij_num_1, :v_vrij_num_2, "
            ":v_vrij_num_3, :v_vrij_num_4, :v_vrij_num_5, :v_last_modify_by, :v_last_modify_on, "
            ":v_created_by, :v_created_on"
            ");";

    updateQuery =
        "UPDATE relaties.relaties "
            "SET "
            "naam = :v_naam, "
            "is_firma_naam = :v_is_firma_naam, "
            "voornaam = :v_voornaam, "
            "aankoper = :v_aankoper, "
            "is_bedrijf = :v_is_bedrijf, "
            "adres = :v_adres, "
            "nr_bus = :v_nr_bus, "
            "gemeente_id = :v_gemeente_id, "
            "land_code = :v_land_code, "
            "taal_id = :v_taal_id, "
            "tel_1 = :v_tel_1, "
            "tel_1_contact = :v_tel_1_contact, "
            "tel_1_publiciteit = :v_tel_1_publiciteit, "
            "gsm_1 = :v_gsm_1, "
            "gsm_1_contact = :v_gsm_1_contact, "
            "gsm_1_publiciteit = :v_gsm_1_publiciteit, "
            "aanspreking_id = :v_aanspreking_id, "
            "btw_nummer = :v_btw_nummer, "
            "firma_id = :v_firma_id, "
            "site_id = :v_site_id, "
            "afdeling_id = :v_afdeling_id, "
            "gebruiker_id = :v_gebruiker_id, "
            "geslacht_code = :v_geslacht_code, "
            "herkomst = :v_herkomst, "
            "beroep = :v_beroep, "
            "is_prospect = :v_is_prospect, "
            "is_klant = :v_is_klant, "
            "is_leverancier = :v_is_leverancier, "
            "is_benaderbaar = :v_is_benaderbaar, "
            "is_deelnemer = :v_is_deelnemer, "
            "is_verhuisd = :v_is_verhuisd, "
            "is_inactief = :v_is_inactief, "
            "is_lopende_klacht = :v_is_lopende_klacht, "
            "is_overleden = :v_is_overleden, "
            "tel_2 = :v_tel_2, "
            "tel_2_contact = :v_tel_2_contact, "
            "tel_2_publiciteit = :v_tel_2_publiciteit, "
            "fax = :v_fax, "
            "fax_contact = :v_fax_contact, "
            "fax_publiciteit = :v_fax_publiciteit, "
            "email_1 = :v_email_1, "
            "email_1_contact = :v_email_1_contact, "
            "email_1_publiciteit = :v_email_1_publiciteit, "
            "email_2 = :v_email_2, "
            "email_2_contact = :v_email_2_contact, "
            "email_2_publiciteit = :v_email_2_publiciteit, "
            "adres_contact = :v_adres_contact, "
            "adres_publiciteit = :v_adres_publiciteit, "
            "website = :v_website, "
            "facebook = :v_facebook, "
            "linked_in = :v_linked_in, "
            "ref_bij_relatie = :v_ref_bij_relatie, "
            "nace_code = :v_nace_code, "
            "mailing_code = :v_mailing_code, "
            "geboortedatum = :v_geboortedatum, "
            "geboorteplaats = :v_geboorteplaats, "
            "aantal_kinderen = :v_aantal_kinderen, "
            "hobby = :v_hobby, "
            "btw_regime_id = :v_btw_regime_id, "
            "btw_autorisatiecode = :v_btw_autorisatiecode, "
            "bkh_categorie_id = :v_bkh_categorie_id, "
            "kortings_categorie_id = :v_kortings_categorie_id, "
            "kredietlimiet = :v_kredietlimiet, "
            "betalingstermijn_id = :v_betalingstermijn_id, "
            "bankrekening_1 = :v_bankrekening_1, "
            "iban_1 = :v_iban_1, "
            "bankrekening_2 = :v_bankrekening_2, "
            "iban_2 = :v_iban_2, "
            "pop_up_tekst = :v_pop_up_tekst, "
            "opmerking = :v_opmerking, "
            "id_1 = :v_id_1, "
            "id_2 = :v_id_2, "
            "id_3 = :v_id_3, "
            "id_4 = :v_id_4, "
            "id_5 = :v_id_5, "
            "idcard_nummer = :v_idcard_nummer, "
            "reziv_nummer = :v_reziv_nummer, "
            "idcard_uitgereikt_te = :v_idcard_uitgereikt_te, "
            "id_geldig_van = :v_id_geldig_van, "
            "id_geldig_tot = :v_id_geldig_tot, "
            "flag_1 = :v_flag_1, "
            "flag_2 = :v_flag_2, "
            "flag_3 = :v_flag_3, "
            "flag_4 = :v_flag_4, "
            "flag_5 = :v_flag_5, "
            "flag_6 = :v_flag_6, "
            "flag_7 = :v_flag_7, "
            "flag_8 = :v_flag_8, "
            "flag_9 = :v_flag_9, "
            "flag_10 = :v_flag_10, "
            "vrij_tekst_1 = :v_vrij_tekst_1, "
            "vrij_tekst_2 = :v_vrij_tekst_2, "
            "vrij_tekst_3 = :v_vrij_tekst_3, "
            "vrij_tekst_4 = :v_vrij_tekst_4, "
            "vrij_tekst_5 = :v_vrij_tekst_5, "
            "vrij_num_1 = :v_vrij_num_1, "
            "vrij_num_2 = :v_vrij_num_2, "
            "vrij_num_3 = :v_vrij_num_3, "
            "vrij_num_4 = :v_vrij_num_4, "
            "vrij_num_5 = :v_vrij_num_5, "
            "last_modify_by = :v_last_modify_by, "
            "last_modify_on = :v_last_modify_on "
          "WHERE (relatie_id = :v_relatie_id);";

    QSqlQuery qry;
    QString user = QString(qgetenv("USER"));

    if (Relatie_ID == 0)
    {

        qry.prepare(insertQuery);
        qry.bindValue(":v_created_by", user);
        qry.bindValue(":v_created_on", QDateTime::currentDateTime());
    }
    else
    {
        qry.prepare(updateQuery);
        qry.bindValue(":v_relatie_id", Relatie_ID);
    }


    qry.bindValue(":v_naam", Naam);
    qry.bindValue(":v_is_firma_naam", IsFirmaNaam);
    qry.bindValue(":v_voornaam", Voornaam);
    qry.bindValue(":v_aankoper", Aankoper);
    qry.bindValue(":v_is_bedrijf", IsBedrijf);
    qry.bindValue(":v_adres", Adres);
    qry.bindValue(":v_nr_bus", NrBus);
    qry.bindValue(":v_gemeente_id", Gemeente_ID);
    qry.bindValue(":v_land_code", LandCode);
    qry.bindValue(":v_taal_id", Taal_ID);
    qry.bindValue(":v_tel_1", Tel_1);
    qry.bindValue(":v_tel_1_contact", Tel_1_Contact);
    qry.bindValue(":v_tel_1_publiciteit", Tel_1_Publiciteit);
    qry.bindValue(":v_gsm_1", GSM_1);
    qry.bindValue(":v_gsm_1_contact", GSM_1_Contact);
    qry.bindValue(":v_gsm_1_publiciteit", GSM_1_Publiciteit);
    qry.bindValue(":v_aanspreking_id", Aanspreking_ID);
    qry.bindValue(":v_btw_nummer", BTWNummer);
    qry.bindValue(":v_firma_id", Firma_ID);
    qry.bindValue(":v_site_id", Site_ID);
    qry.bindValue(":v_afdeling_id", Afdeling_ID);
    qry.bindValue(":v_gebruiker_id", Gebruiker_ID);
    qry.bindValue(":v_geslacht_code", GeslachtCode);
    qry.bindValue(":v_herkomst", Herkomst);
    qry.bindValue(":v_beroep", Beroep);
    qry.bindValue(":v_is_prospect", IsProspect);
    qry.bindValue(":v_is_klant", IsKlant);
    qry.bindValue(":v_is_leverancier", IsLeverancier);
    qry.bindValue(":v_is_benaderbaar", IsBenaderbaar);
    qry.bindValue(":v_is_deelnemer", IsDeelnemer);
    qry.bindValue(":v_is_verhuisd", IsVerhuisd);
    qry.bindValue(":v_is_inactief", IsInactief);
    qry.bindValue(":v_is_lopende_klacht", IsLopendeKlacht);
    qry.bindValue(":v_is_overleden", IsOverleden);
    qry.bindValue(":v_tel_2", Tel_2);
    qry.bindValue(":v_tel_2_contact", Tel_2_Contact);
    qry.bindValue(":v_tel_2_publiciteit", Tel_2_Publiciteit);
    qry.bindValue(":v_fax", Fax);
    qry.bindValue(":v_fax_contact", Fax_Contact);
    qry.bindValue(":v_fax_publiciteit", Fax_Publiciteit);
    qry.bindValue(":v_email_1", EMail_1);
    qry.bindValue(":v_email_1_contact", EMail_1_Contact);
    qry.bindValue(":v_email_1_publiciteit", EMail_1_Publiciteit);
    qry.bindValue(":v_email_2", EMail_2);
    qry.bindValue(":v_email_2_contact", EMail_2_Contact);
    qry.bindValue(":v_email_2_publiciteit", EMail_2_Publiciteit);
    qry.bindValue(":v_adres_contact", Adres_Contact);
    qry.bindValue(":v_adres_publiciteit", Adres_Publiciteit);
    qry.bindValue(":v_website", Website);
    qry.bindValue(":v_facebook", Facebook);
    qry.bindValue(":v_linked_in", Linked_in);
    qry.bindValue(":v_ref_bij_relatie", RefBijRelatie);
    qry.bindValue(":v_nace_code",NACECode);
    qry.bindValue(":v_mailing_code", MailingCode);
    qry.bindValue(":v_geboortedatum", Geboortedatum);
    qry.bindValue(":v_geboorteplaats", Geboorteplaats);
    qry.bindValue(":v_aantal_kinderen", AantalKinderen);
    qry.bindValue(":v_hobby", Hobby);
    qry.bindValue(":v_btw_regime_id", BTWRegime_ID);
    qry.bindValue(":v_btw_autorisatiecode", BTWAutorisatiecode);
    qry.bindValue(":v_bkh_categorie_id", BKHCategorie_ID);
    qry.bindValue(":v_kortings_categorie_id", KortingsCategorie_ID);
    qry.bindValue(":v_kredietlimiet", Kredietlimiet);
    qry.bindValue(":v_betalingstermijn_id", BetalingstermijnID);
    qry.bindValue(":v_bankrekening_1", Bankrekening_1);
    qry.bindValue(":v_iban_1", Iban_1);
    qry.bindValue(":v_bankrekening_2", Bankrekening_2);
    qry.bindValue(":v_iban_2", Iban_2);
    qry.bindValue(":v_pop_up_tekst", PopUpTekst);
    qry.bindValue(":v_opmerking", Opmerking);
    qry.bindValue(":v_id_1", ID_1);
    qry.bindValue(":v_id_2", ID_2);
    qry.bindValue(":v_id_3", ID_3);
    qry.bindValue(":v_id_4", ID_4);
    qry.bindValue(":v_id_5", ID_5);
    qry.bindValue(":v_idcard_nummer", IDCardNummer);
    qry.bindValue(":v_reziv_nummer", RezivNummer);
    qry.bindValue(":v_idcard_uitgereikt_te", IDCardUitgereiktTe);
    qry.bindValue(":v_id_geldig_van", IDGeldigVan);
    qry.bindValue(":v_id_geldig_tot", IDGeldigTot);
    qry.bindValue(":v_flag_1", Flag_1);
    qry.bindValue(":v_flag_2", Flag_2);
    qry.bindValue(":v_flag_3", Flag_3);
    qry.bindValue(":v_flag_4", Flag_4);
    qry.bindValue(":v_flag_5", Flag_5);
    qry.bindValue(":v_flag_6", Flag_6);
    qry.bindValue(":v_flag_7", Flag_7);
    qry.bindValue(":v_flag_8", Flag_8);
    qry.bindValue(":v_flag_9", Flag_9);
    qry.bindValue(":v_flag_10", Flag_10);
    qry.bindValue(":v_vrij_tekst_1", VrijTekst_1);
    qry.bindValue(":v_vrij_tekst_2", VrijTekst_2);
    qry.bindValue(":v_vrij_tekst_3", VrijTekst_3);
    qry.bindValue(":v_vrij_tekst_4", VrijTekst_4);
    qry.bindValue(":v_vrij_tekst_5", VrijTekst_5);
    qry.bindValue(":v_vrij_num_1", VrijNum_1);
    qry.bindValue(":v_vrij_num_2", VrijNum_2);
    qry.bindValue(":v_vrij_num_3", VrijNum_3);
    qry.bindValue(":v_vrij_num_4", VrijNum_4);
    qry.bindValue(":v_vrij_num_5", VrijNum_5);
    qry.bindValue(":v_last_modify_by", user);
    qry.bindValue(":v_last_modify_on", QDateTime::currentDateTime());

    if (qry.exec())
    {
        if (Relatie_ID == 0)
        {
            Relatie_ID = qry.lastInsertId().toInt();
        }
    }
    else
    {
        qDebug() << "Database error: " << qry.lastError().databaseText() << "\nQuerry error: " << qry.lastError().text();
    }


}

void Relaties::FindList(QSqlQueryModel *model, QString _naam, QString _adres, QString _gemeente, QString _email)
{
    QString myQuery = "select * from relaties.find_relaties(:v_naam, :v_gemeente);";
    QSqlQuery myquery;
    myquery.prepare(myQuery);
    myquery.bindValue(":v_naam", QString("\%%1\%").arg(_naam));
    myquery.bindValue(":v_gemeente", QString("\%%1\%").arg(_gemeente));
    myquery.exec();
    model->setQuery(myquery);
    model->query();

}
