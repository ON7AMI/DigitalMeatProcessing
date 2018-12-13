//======================================================================================================
//
//                        ==== ON7AMI = Project: Digital Meat Processing ====
//
//======================================================================================================
//
//   Doel:    Relatie fiche voor bijhouden en opzoeken relaties
//   File:    Relatiefiche.cpp
//   Created: 26/07/2015
//   By:      Jean Paul Mertens  (jpm)
//   email:   jpm@on7ami.be
//
//-------------------------------------------------------------------------------------------------------
//
//  Version |  Date      |  By    |  Description / Changes
// ---------+------------+--------+-----------------------------------------------------------------------
//  1.0.0   | 26/07/2015 |  JPM   |  Original
//          |            |        |
//
//--------------------------------------------------------------------------------------------------------
//
//  Interface:
//  ----------
//
// -Menu's:
//
//
// -Statusbar's:
//
//
// -Tabpages:
//      nbRelatiefiche
//          tabContactgegevens  tabDiverse  tabContactpersonen  tabContacten    tabDocumenten
//
// -Fields:void Gebruikers::getAllGebruikers(QSqlQueryModel* model)
//    -Hoofding
//                                      relatie_id                  serial,
//      tbNaam                          naam                        character varying,
//      cbIsFirmanaam                   is_firma_naam               bool,
//      tbVoornaam                      voornaam                    character varying,
//      tbAankoper                      aankoper                    character varying,
//      cbIsBedrijf                     is_bedrijf                  bool,
//      tbAdres                         adres                       character varying,
//      tbBusNummer                     nr_bus                      character varying,
//      cbxPostcode                     gemeente_id                 int,
//      cbxGemeente
//      cbxLand                         land_code                   character varying,,
//      cbxTalen                        taal_id                     int,
//      tbTelefoon                      tel_1                       character varying,
//      cbTelefoonVoorContact           tel_1_contact               bool,
//      cbTelefoonVoorPubliciteit       tel_1_publiciteit           bool,
//      tbGSM                           gsm_1                       character varying,
//      cbGSMVoorContact                gsm_1_contact               bool,
//      cbGSMVoorPubliciteit            gsm_1_publiciteit           bool,
//      cbxAanspreking                  aanspreking_id              int,
//      tbBTWNummer                     btw_nummer                  character varying,
//      cbxFirma                        firma_id                    int,
//      cbxSite                         site_id                     int,
//      cbxAfdeling                     afdeling_id                 int,
//      cbxGebruiker                    gebruiker_id                int,
//      cbxGeslacht                     geslacht_code               char,
//      tbHerkomst                      herkomst                    character varying,
//      tbBeroep                        beroep                      character varying,
//      cbIsProspect                    is_prospect                 bool,
//      cbIsKlant                       is_klant                    bool,
//      cbIsLeverancier                 is_leverancier              bool,
//      cbIsBenaderbaar                 is_benaderbaar              bool,
//      cbNeemtDeel                     is_deelnemer                bool,
//      cbIsVerhuisd                    is_verhuisd                 bool,
//      cbIsInactief                    is_inactief                 bool,
//      cbLopendeKlacht                 is_lopende_klacht           bool,
//      cbIsOverleden                   is_overleden                bool,
//
//    -Contactgegevens
//      tbTel2                          tel_2                       character varying,
//      cbTel2VoorContact               tel_2_contact               bool,
//      cbTel2VoorPubliciteit           tel_2_publiciteit           bool,
//      tbFax                           fax                         character varying,
//      cbFaxVoorContact                fax_contact                 bool,
//      cbFaxVoorPubliciteit            fax_publiciteit             bool,
//      tbEmail1                        email_1                     character varying,
//      cbEmail1VoorContact             email_1_contact             bool,
//      cbEmail1VoorPubliciteit         email_1_publiciteit         bool,
//      tbEmail2                        email_2                     character varying,
//      cbEmail2VoorContact             email_2_contact             bool,
//      cbEmail2VoorPubliciteit         email_2_publiciteit         bool,
//      cbAdresVoorContact              adres_contact               bool,
//      cbAdresVoorPubliciteit          adres_publiciteit           bool,
//      tbWebsite                       website                     character varying,
//      tbFacebook                      facebook                    character varying,
//      tbLinckedIn                     linked_in                   character varying,
//      tbRefBijRelatie                 ref_bij_relatie             character varying,
//      tbNaceCode                      nace_code                   character varying,
//      tbMailingcode                   mailing_code                character varying,
//      dtpGeboorteDatum                geboortedatum               date,
//      tbGeboorteplaats                geboorteplaats              character varying,
//      sbxAantalKinderen               aantal_kinderen             int,
//      tbHobbys                        hobby                       character varying,
//      cbxBTWRegime                    btw_regime_id               int,
//      tbBTWAutorisatie                btw_autorisatiecode         character varying,
//      cbxBKHCategorie                 bkh_categorie_id            int,
//      cbxKortingsCategorie            kortings_categorie_id       int,
//      tbKredietLimiet                 kredietlimiet               money,
//      cbxBetalingsTermijn             betalingstermijn_id         int,
//      tbBankrekening1                 bankrekening_1              character varying,
//      tbIban1                         iban_1                      character varying,
//      tbBankrekening2                 bankrekening_2              character varying,
//      tbIban2                         iban_2                      character varying,
//      tbPopUpTekst                    pop_up_tekst                character varying,
//      tbOpmerkingen                   opmerking                   character varying,
//      tbID_1                          id_1                        int,
//      tbID_2                          id_2                        int,
//      tbID_3                          id_3                        int,
//      tbID_4                          id_4                        int,
//      tbID_5                          id_5                        int,
//
//    -Diverse
//      tbIDCartNummer                  idcard_nummer               character varying,
//      tbRijksregisterNummer           reziv_nummer                character varying,
//      tbUitgereiktTe                  idcard_uitgereikt_te        character varying,
//      dtpGeldigVan                    id_geldig_van               date,
//      dtpGeldigTot                    id_geldig_tot               date,
//      cbFlag1                         flag_1                      bool,
//      cbFlag2                         flag_2                      bool,
//      cbFlag3                         flag_3                      bool,
//      cbFlag4                         flag_4                      bool,
//      cbFlag5                         flag_5                      bool,N.Voornaam
//      cbFlag6                         flag_6                      bool,
//      cbFlag7                         flag_7                      bool,
//      cbFlag8                         flag_8                      bool,
//      cbFlag9                         flag_9                      bool,
//      cbFlag10                        flag_10                     bool,
//      tbVrijTekst1                    vrij_tekst_1                character varying,
//      tbVrijTekst2                    vrij_tekst_2                character varying,
//      tbVrijTekst3                    vrij_tekst_3                character varying,
//      tbVrijTekst4                    vrij_tekst_4                character varying,
//      tbVrijTekst5                    vrij_tekst_5                character varying,
//      tbVrijNum1                      vrij_num_1                  numeric(4),
//      tbVrijNum2                      vrij_num_2                  numeric(4),
//      tbVrijNum3                      vrij_num_3                  numeric(4),
//      tbVrijNum4                      vrij_num_4                  numeric(4),
//      tbVrijNum5                      vrij_num_5                  numeric(4),
//
//
//    -Contactpersonen
//    -Contacten
//    -Documenten
//
//
// -Externe classes used:
//      CRM.Relaties   -   Alle gegevens betreffende de relaties
//
// -DataBases / Tables used:
//
//
//    //ui->cbxGemeente->setModelColumn(0);
//int val = 507;

//========================================================================================================




#include "relatiefiche.h"
#include "ui_relatiefiche.h"
#include "findrelaties.h"


#include "../CommonObjects/commonobjects.h"
#include "../CommonObjects/postcodes.h"
#include "../CommonObjects/talen.h"
#include "../CommonObjects/landen.h"
#include "../CommonObjects/geslachten.h"
#include "../CommonObjects/aansprekingen.h"
#include "../CommonObjects/firma.h"
#include "../CommonObjects/sites.h"
#include "../CommonObjects/afdelingen.h"
#include "../CommonObjects/gebruikers.h"
#include "../CommonObjects/btwregimes.h"
#include "../CommonObjects/bkhcategorie.h"
#include "../CommonObjects/kortingscategorie.h"
#include "../CommonObjects/betalingstermijn.h"

#include <QSqlTableModel>
#include <QMessageBox>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QJsonDocument>


RelatieFiche::RelatieFiche(OpenAs _openAs, int _id, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::RelatieFiche)
{
    ui->setupUi(this);

    QList<QLineEdit *> EditList = this->findChildren<QLineEdit *>();
    for (int i = 0 ; i < EditList.count() ; i++)
    {
        connect(EditList[i] , SIGNAL(textChanged(const QString)), SLOT(on_formEdited(const QString)));
    }

    //void on_cb_toggled(bool checked);
    QList<QCheckBox *> CheckList = this->findChildren<QCheckBox *>();
    for (int i = 0 ; i < CheckList.count() ; i++)
    {
        connect(CheckList[i] , SIGNAL(stateChanged(int)), SLOT(on_cb_stateChanged(int )));
    }

    //void on_cbx_currentIndexChanged(const QString &arg1);
    QList<QComboBox *> ComboList = this->findChildren<QComboBox *>();
    for (int i = 0 ; i < ComboList.count() ; i++)
    {
        connect(ComboList[i] , SIGNAL(currentIndexChanged(const QString)), SLOT(on_cbx_currentIndexChanged(const QString)));
    }

    //void on_dtp_userDateChanged(const QDate &date);
    QList<QDateEdit *> DateList = this->findChildren<QDateEdit *>();
    for (int i = 0 ; i < DateList.count() ; i++)
    {
        connect(DateList[i] , SIGNAL(dateChanged(const QDate)), SLOT(on_dtp_DateChanged(const QDate)));
    }

    //void on_tbe_textChanged();
    QList<QTextEdit *> TextList = this->findChildren<QTextEdit *>();
    for (int i = 0 ; i < TextList.count() ; i++)
    {
        connect(TextList[i] , SIGNAL(textChanged()), SLOT(on_tbe_textChanged()));
    }


    //this->findChildren();
    //li.first().
    HideVrijeVelden();
    SetFieldValidators();


    qDebug() <<"test: " <<_id;

    _find = false;

    switch (_openAs) {
    case RelatieFiche::OpenAsEdit:
        {
            rel = new Relaties(_id);
            FillComboBoxes();
            SetFieldValues();

            SetFieldsReadOnly(false);
            ui->actionEditRelatie->setEnabled(false);
            ui->actionSaveRelatie->setEnabled(true);

            qDebug() <<"OpenAsEdit.";
        }
        break;

    case RelatieFiche::OpenAsFind:
        {
            qDebug() <<"OpenAsFind.";

            PrepareFind();
        }
        break;

    case RelatieFiche::OpenAsNew:
        {
            NewRecord();
            qDebug() <<"OpenAsNew.";
        }
        break;

    case RelatieFiche::OpenAsView:
        {
            qDebug() <<"OpenAsView.";
        }
        break;

    case RelatieFiche::OpenAsSettings:
        {
            rel = new Relaties();
            FillComboBoxes();
            SetFieldValues();

            SetFieldsReadOnly(false);
            qDebug() <<"OpenAsSettings.";
            ui->btnID_Cart->setVisible(false);
            ui->btnNaceCode->setVisible(false);

            ui->actionFindRelatie->setEnabled(false);
            ui->actionNewRelatie->setEnabled(false);
            ui->actionEditRelatie->setEnabled(true);
            ui->actionSaveRelatie->setEnabled(true);
            ui->actionStop->setEnabled(true);
        }
        break;

    default:
        break;
    }

    //QLineEdit* postcodeEdit;
    //postcodeEdit = ui->cbxPostcode->lineEdit();
    connect(ui->cbxPostcode->lineEdit() , SIGNAL(editingFinished()), SLOT(on_cbxPostcode_LineEditTextChanged()));
    connect(&networkManager, SIGNAL(finished(QNetworkReply*)), this, SLOT(onResult(QNetworkReply*)));

    dirty = false;
}


RelatieFiche::~RelatieFiche()
{
    delete ui;
    delete rel;
    delete Talen_model;
    delete Postcodes_model;
    delete Gemeenten_model;
    delete Landen_model;
    delete Geslachten_model;
    delete Aansprekingen_model;
    delete Firmas_model;
    delete Sites_model;
    delete Afdelingen_model;
    delete Gebruiker_model;
    delete BTWRegime_model;
    delete BKHCategorie_model;
    delete KortingsCategorie_model;
    delete BetalingsTermijn_model;
}

void RelatieFiche::PrepareFind()
{
    rel = new Relaties();
    FillComboBoxes();
    SetFieldValues();

    SetFieldsReadOnly( true );
    ui->lbID->setVisible(true);
    ui->tbID->setVisible(true);
    ui->tbID->setText("");
    ui->tbNaam->setStyleSheet("background-color: Lightcyan;");
    ui->tbNaam->setEnabled(true);
    ui->tbNaam->setText("");
    ui->tbAdres->setStyleSheet("background-color: Lightcyan;");
    ui->tbAdres->setEnabled(true);
    ui->cbxGemeente->setStyleSheet("background-color: Lightcyan;");
    ui->cbxGemeente->setEnabled(true);
    ui->tbEmail1->setStyleSheet("background-color: Lightcyan;");
    ui->tbEmail1->setEnabled(true);
    ui->cbxGemeente->clearEditText();

    ui->actionEditRelatie->setEnabled(false);
    ui->actionSaveRelatie->setEnabled(false);
    _find = true;
}


void RelatieFiche::SetFieldValidators()
{

    // ------------- integer
    ui->tbID->setValidator(new QIntValidator);
    ui->tbID_1->setValidator(new QIntValidator);
    ui->tbID_2->setValidator(new QIntValidator);
    ui->tbID_3->setValidator(new QIntValidator);
    ui->tbID_4->setValidator(new QIntValidator);
    ui->tbID_5->setValidator(new QIntValidator);

    // ------------- double
    ui->tbKredietLimiet->setValidator(new QDoubleValidator);
    ui->tbVrijNum1->setValidator(new QDoubleValidator);
    ui->tbVrijNum2->setValidator(new QDoubleValidator);
    ui->tbVrijNum3->setValidator(new QDoubleValidator);
    ui->tbVrijNum4->setValidator(new QDoubleValidator);
    ui->tbVrijNum5->setValidator(new QDoubleValidator);

    // -------------- Teklefoon nummers
    QRegExp rt("^([0-9\\(\\)\\/\\+ \\-]*)$");
    QValidator *validatorTel = new QRegExpValidator(rt, this);

    ui->tbTelefoon->setValidator(validatorTel);
    ui->tbTel2->setValidator(validatorTel);
    ui->tbFax->setValidator(validatorTel);
    ui->tbGSM->setValidator(validatorTel);

    //--------------- email adressen
    QRegExp rx("[a-z0-9!#$%&'*+/=?^_`{|}~-]+(?:\\.[a-z0-9!#$%&'*+/=?^_`{|}~-]+)*@(?:[a-z0-9](?:[a-z0-9-]*[a-z0-9])?\\.)+[a-z0-9](?:[a-z0-9-]*[a-z0-9])?");
    QValidator *validatorEMail = new QRegExpValidator(rx, this);

    ui->tbEmail1->setValidator(validatorEMail);
    ui->tbEmail2->setValidator(validatorEMail);


}

//---------------------------------------------------------------------------------------------------------------------------
//  De vrije keuzevelden die niet gebruikt worden moeten verborgen worden.
//  Als in de settings geen labelnaam ingevuld is, dan worden ze verborgen
//  Als er wel een label naam ingevuld is wordt die in de plaats van de oorspronkelijke label
//  gezet zodat het veld zijn uiteindelijke betekenis krijgt.
//
//
void RelatieFiche::HideVrijeVelden()
{
    QString m_sSettingsFile = QApplication::applicationDirPath() + "/appSettings.ini";
    QSettings settings(m_sSettingsFile, QSettings::NativeFormat);
    QString titel;

    titel = settings.value("Relatie/Flag_1", "").toString();
    if (! titel.trimmed().isEmpty())
    {
        ui->cbFlag1->setText(titel);
        ui->cbFlag1->setVisible(true);
    }
    else
    {
        ui->cbFlag1->setVisible(false);
    }

    titel = settings.value("Relatie/Flag_2", "").toString();
    if (! titel.trimmed().isEmpty())
    {
        ui->cbFlag2->setText(titel);
        ui->cbFlag2->setVisible(true);
    }
    else
    {
        ui->cbFlag2->setVisible(false);
    }

    titel = settings.value("Relatie/Flag_3", "").toString();
    if (! titel.trimmed().isEmpty())
    {
        ui->cbFlag3->setText(titel);
        ui->cbFlag3->setVisible(true);
    }
    else
    {
        ui->cbFlag3->setVisible(false);
    }

    titel = settings.value("Relatie/Flag_4", "").toString();
    if (! titel.trimmed().isEmpty())
    {
        ui->cbFlag4->setText(titel);
        ui->cbFlag4->setVisible(true);
    }
    else
    {
        ui->cbFlag4->setVisible(false);
    }

    titel = settings.value("Relatie/Flag_5", "").toString();
    if (! titel.trimmed().isEmpty())
    {
        ui->cbFlag5->setText(titel);
        ui->cbFlag5->setVisible(true);
    }
    else
    {
        ui->cbFlag5->setVisible(false);
    }

    titel = settings.value("Relatie/Flag_6", "").toString();
    if (! titel.trimmed().isEmpty())
    {
        ui->cbFlag6->setText(titel);
        ui->cbFlag6->setVisible(true);
    }
    else
    {
        ui->cbFlag6->setVisible(false);
    }

    titel = settings.value("Relatie/Flag_7", "").toString();
    if (! titel.trimmed().isEmpty())
    {
        ui->cbFlag7->setText(titel);
        ui->cbFlag7->setVisible(true);
    }
    else
    {
        ui->cbFlag7->setVisible(false);
    }

    titel = settings.value("Relatie/Flag_8", "").toString();
    if (! titel.trimmed().isEmpty())
    {
        ui->cbFlag8->setText(titel);
        ui->cbFlag8->setVisible(true);
    }
    else
    {
        ui->cbFlag8->setVisible(false);
    }

    titel = settings.value("Relatie/Flag_9", "").toString();
    if (! titel.trimmed().isEmpty())
    {
        ui->cbFlag9->setText(titel);
        ui->cbFlag9->setVisible(true);
    }
    else
    {
        ui->cbFlag9->setVisible(false);
    }

    titel = settings.value("Relatie/Flag_10", "").toString();
    if (! titel.trimmed().isEmpty())
    {
        ui->cbFlag10->setText(titel);
        ui->cbFlag1->setVisible(true);
    }
    else
    {
        ui->cbFlag10->setVisible(false);
    }

    //------------------------------------------------------------------------------------------------

    titel = settings.value("Relatie/VrijTekst_1", "").toString();
    if (! titel.trimmed().isEmpty())
    {
        ui->lbVrijTekst1->setText(titel);
        ui->lbVrijTekst1->setVisible(true);
        ui->tbVrijTekst1->setVisible(true);
    }
    else
    {
        ui->lbVrijTekst1->setVisible(false);
        ui->tbVrijTekst1->setVisible(false);
    }

    titel = settings.value("Relatie/VrijTekst_2", "").toString();
    if (! titel.trimmed().isEmpty())
    {
        ui->lbVrijTekst2->setText(titel);
        ui->lbVrijTekst2->setVisible(true);
        ui->tbVrijTekst2->setVisible(true);
    }
    else
    {
        ui->lbVrijTekst2->setVisible(false);
        ui->tbVrijTekst2->setVisible(false);
    }

    titel = settings.value("Relatie/VrijTekst_3", "").toString();
    if (! titel.trimmed().isEmpty())
    {
        ui->lbVrijTekst3->setText(titel);
        ui->lbVrijTekst3->setVisible(true);
        ui->tbVrijTekst3->setVisible(true);
    }
    else
    {
        ui->lbVrijTekst3->setVisible(false);
        ui->tbVrijTekst3->setVisible(false);
    }

    titel = settings.value("Relatie/VrijTekst_4", "").toString();
    if (! titel.trimmed().isEmpty())
    {
        ui->lbVrijTekst4->setText(titel);
        ui->lbVrijTekst4->setVisible(true);
        ui->tbVrijTekst4->setVisible(true);
    }
    else
    {
        ui->lbVrijTekst4->setVisible(false);
        ui->tbVrijTekst4->setVisible(false);
    }

    titel = settings.value("Relatie/VrijTekst_5", "").toString();
    if (! titel.trimmed().isEmpty())
    {
        ui->lbVrijTekst5->setText(titel);
        ui->lbVrijTekst5->setVisible(true);
        ui->tbVrijTekst5->setVisible(true);
    }
    else
    {
        ui->lbVrijTekst5->setVisible(false);
        ui->tbVrijTekst5->setVisible(false);
    }

//------------------------------------------------------------------------------------------------------

    titel = settings.value("Relatie/VrijNum_1", "").toString();
    if (! titel.trimmed().isEmpty())
    {
        ui->lbVrijNum1->setText(titel);
        ui->lbVrijNum1->setVisible(true);
        ui->tbVrijNum1->setVisible(true);
    }
    else
    {
        ui->lbVrijNum1->setVisible(false);
        ui->tbVrijNum1->setVisible(false);
    }

    titel = settings.value("Relatie/VrijNum_2", "").toString();
    if (! titel.trimmed().isEmpty())
    {
        ui->lbVrijNum2->setText(titel);
        ui->lbVrijNum2->setVisible(true);
        ui->tbVrijNum2->setVisible(true);
    }
    else
    {
        ui->lbVrijNum2->setVisible(false);
        ui->tbVrijNum2->setVisible(false);
    }

    titel = settings.value("Relatie/VrijNum_3", "").toString();
    if (! titel.trimmed().isEmpty())
    {
        ui->lbVrijNum3->setText(titel);
        ui->lbVrijNum3->setVisible(true);
        ui->tbVrijNum3->setVisible(true);
    }
    else
    {
        ui->lbVrijNum3->setVisible(false);
        ui->tbVrijNum3->setVisible(false);
    }

    titel = settings.value("Relatie/VrijNum_4", "").toString();
    if (! titel.trimmed().isEmpty())
    {
        ui->tbVrijNum4->setText(titel);
        ui->tbVrijNum4->setVisible(true);
        ui->lbVrijNum4->setVisible(true);
    }
    else
    {
        ui->lbVrijNum4->setVisible(false);
        ui->tbVrijNum4->setVisible(false);
    }

    titel = settings.value("Relatie/VrijNum_5", "").toString();
    if (! titel.trimmed().isEmpty())
    {
        ui->lbVrijNum5->setText(titel);
        ui->lbVrijNum5->setVisible(true);
        ui->tbVrijNum5->setVisible(true);
    }
    else
    {
        ui->lbVrijNum5->setVisible(false);
        ui->tbVrijNum5->setVisible(false);
    }

    //-------------------------------------------------------------------------------------------

    titel = settings.value("Relatie/ID_1", "").toString();
    if (! titel.trimmed().isEmpty())
    {
        ui->lbID_1->setText(titel);
        ui->lbID_1->setVisible(true);
        ui->tbID_1->setVisible(true);
    }
    else
    {
        ui->lbID_1->setVisible(false);
        ui->tbID_1->setVisible(false);
    }

    titel = settings.value("Relatie/ID_2", "").toString();
    if (! titel.trimmed().isEmpty())
    {
        ui->lbID_2->setText(titel);
        ui->lbID_2->setVisible(true);
        ui->tbID_2->setVisible(true);
    }
    else
    {
        ui->lbID_2->setVisible(false);
        ui->tbID_2->setVisible(false);
    }

    titel = settings.value("Relatie/ID_3", "").toString();
    if (! titel.trimmed().isEmpty())
    {
        ui->lbID_3->setText(titel);
        ui->lbID_3->setVisible(true);
        ui->tbID_3->setVisible(true);
    }
    else
    {
        ui->lbID_3->setVisible(false);
        ui->tbID_3->setVisible(false);
    }

    titel = settings.value("Relatie/ID_4", "").toString();
    if (! titel.trimmed().isEmpty())
    {
        ui->lbID_4->setText(titel);
        ui->lbID_4->setVisible(true);
        ui->tbID_4->setVisible(true);
    }
    else
    {
        ui->lbID_4->setVisible(false);
        ui->tbID_4->setVisible(false);
    }

    titel = settings.value("Relatie/ID_5", "").toString();
    if (! titel.trimmed().isEmpty())
    {
        ui->lbID_5->setText(titel);
        ui->lbID_5->setVisible(true);
        ui->tbID_5->setVisible(true);
    }
    else
    {
        ui->lbID_5->setVisible(false);
        ui->tbID_5->setVisible(false);
    }

}


//--------------------------------------------------------------------------------------------
//  Het opvullen vn de verschillende keuzelijsten
//
void RelatieFiche::FillComboBoxes()
{
     //-------------------------------------------------
    // Combobox's:
    // -Fields:
    //    -Hoofding
    //      cbxPostcode
    Postcodes_model = new QSqlQueryModel();
    Postcodes::getPostcodesPerLand(Postcodes_model, rel->getLandCode() );
    ui->cbxPostcode->setModel(Postcodes_model);
    ui->cbxPostcode->setModelColumn(1);

    //      cbxGemeente
    Gemeenten_model = new QSqlQueryModel();
    Postcodes::getGemeentesPerLand(Gemeenten_model, rel->getLandCode() );
    ui->cbxGemeente->setModel(Gemeenten_model);
    ui->cbxGemeente->setModelColumn(1);

    //      cbxLand
    Landen_model = new QSqlQueryModel();
    Landen::getAllLanden(Landen_model);
    ui->cbxLand->setModel(Landen_model);
    ui->cbxLand->setModelColumn(1);

    //      cbxTalen
    Talen_model = new QSqlTableModel();
    Talen::getAllTalen(Talen_model);
    ui->cbxTalen->setModel(Talen_model);
    ui->cbxTalen->setModelColumn(1);

    //      cbxAanspreking
    Aansprekingen_model = new QSqlQueryModel();
    Aansprekingen::getAllAansprekingen( Aansprekingen_model );
    ui->cbxAanspreking->setModel(Aansprekingen_model);
    ui->cbxAanspreking->setModelColumn(1);

    //      cbxFirma
    Firmas_model = new QSqlQueryModel();
    Firma::getAllFirmas( Firmas_model );
    ui->cbxFirma->setModel(Firmas_model);
    ui->cbxFirma->setModelColumn(1);

    //      cbxSite
    Sites_model = new QSqlQueryModel();
    Sites::getAllSites(Sites_model);
    ui->cbxSite->setModel(Sites_model);
    ui->cbxSite->setModelColumn(1);

    //      cbxAfdeling
    Afdelingen_model = new QSqlQueryModel();
    Afdelingen::getAllAfdelingen(Afdelingen_model);
    ui->cbxAfdeling->setModel(Afdelingen_model);
    ui->cbxAfdeling->setModelColumn(1);

    //      cbxGebruiker
    Gebruiker_model = new QSqlQueryModel;
    Gebruikers::getAllGebruikers(Gebruiker_model);
    ui->cbxGebruiker->setModel(Gebruiker_model);
    ui->cbxGebruiker->setModelColumn(1);

    //      cbxGeslacht
    Geslachten_model = new QStandardItemModel();
    Geslachten::getAllGeslachten(Geslachten_model);
    ui->cbxGeslacht->setModel(Geslachten_model);
    ui->cbxGeslacht->setModelColumn(1);

    //
    //    -Contactgegevens
    //      cbxBTWRegime
    BTWRegime_model = new QSqlQueryModel();
    BTWRegimes::getAllBTWRegimes(BTWRegime_model);
    ui->cbxBTWRegime->setModel(BTWRegime_model);
    ui->cbxBTWRegime->setModelColumn(1);

    //      cbxBKHCategorie
    BKHCategorie_model = new QSqlQueryModel();
    BKHCategorie::getAllBKHCategorie(BKHCategorie_model);
    ui->cbxBKHCategorie->setModel(BKHCategorie_model);
    ui->cbxBKHCategorie->setModelColumn(1);

    //      cbxKortingsCategorie
    KortingsCategorie_model = new QSqlQueryModel();
    KortingsCategorie::getAllKortingsCategorie(KortingsCategorie_model);
    ui->cbxKortingsCategorie->setModel(KortingsCategorie_model);
    ui->cbxKortingsCategorie->setModelColumn(1);

    //      cbxBetalingsTermijn
    BetalingsTermijn_model = new QSqlQueryModel();
    BetalingsTermijn::getAllBetalingsTermijn(BetalingsTermijn_model);
    ui->cbxBetalingsTermijn->setModel(BetalingsTermijn_model);
    ui->cbxBetalingsTermijn->setModelColumn(1);

    //
    //    -Diverse
    //
}

//---------------------------------------------------------------------------
//  Het Read/Only of Read/Write zetten van de invoervelden
//
void RelatieFiche::SetFieldsReadOnly(bool RO)
{

    // -Fields:
    //    -Hoofding
    ui->lbID->setVisible(false);
    ui->tbID->setVisible(false);
    ui->tbNaam->setStyleSheet("");
    ui->tbAdres->setStyleSheet("");
    ui->cbxGemeente->setStyleSheet("");
    ui->tbEmail1->setStyleSheet("");

    ui->tbNaam->setEnabled( !RO );
    ui->cbIsFirmanaam->setEnabled( !RO );
    ui->tbVoornaam->setEnabled( !RO );
    ui->tbAankoper->setEnabled( !RO );
    ui->cbIsBedrijf->setEnabled( !RO );
    ui->tbAdres->setEnabled( !RO );
    ui->tbBusNummer->setEnabled( !RO );
    ui->cbxPostcode->setEnabled( !RO );
    ui->cbxGemeente->setEnabled( !RO );
    ui->cbxLand->setEnabled( !RO );
    ui->cbxTalen->setEnabled( !RO );
    ui->tbTelefoon->setEnabled( !RO );
    ui->cbTelefoonVoorContact->setEnabled( !RO );
    ui->cbTelefoonVoorPubliciteit->setEnabled( !RO );
    ui->tbGSM->setEnabled( !RO );
    ui->cbGSMVoorContact->setEnabled( !RO );
    ui->cbGSMVoorPubliciteit->setEnabled( !RO );
    ui->cbxAanspreking->setEnabled( !RO );
    ui->tbBTWNummer->setEnabled( !RO );
    ui->cbxFirma->setEnabled( !RO );
    ui->cbxSite->setEnabled( !RO );
    ui->cbxAfdeling->setEnabled( !RO );
    ui->cbxGebruiker->setEnabled( !RO );
    ui->cbxGeslacht->setEnabled( !RO );
    ui->tbHerkomst->setEnabled( !RO );
    ui->tbBeroep->setEnabled( !RO );
    ui->cbIsProspect->setEnabled( !RO );
    ui->cbIsKlant->setEnabled( !RO );
    ui->cbIsLeverancier->setEnabled( !RO );
    ui->cbIsBenaderbaar->setEnabled( !RO );
    ui->cbNeemtDeel->setEnabled( !RO );
    ui->cbIsVerhuisd->setEnabled( !RO );
    ui->cbIsInactief->setEnabled( !RO );
    ui->cbLopendeKlacht->setEnabled( !RO );
    ui->cbIsOverleden->setEnabled( !RO );

    //    -Contactgegevens
    ui->tbTel2->setEnabled( !RO );
    ui->cbTel2VoorContact->setEnabled( !RO );
    ui->cbTel2VoorPubliciteit->setEnabled( !RO );
    ui->tbFax->setEnabled( !RO );
    ui->cbFaxVoorContact->setEnabled( !RO );
    ui->cbFaxVoorPubliciteit->setEnabled( !RO );
    ui->tbEmail1->setEnabled( !RO );
    ui->cbEmail1VoorContact->setEnabled( !RO );
    ui->cbEmail1VoorPubliciteit->setEnabled( !RO );
    ui->tbEmail2->setEnabled( !RO );
    ui->cbEmail2VoorContact->setEnabled( !RO );
    ui->cbEmail2VoorPubliciteit->setEnabled( !RO );
    ui->cbAdresVoorContact->setEnabled( !RO );
    ui->cbAdresVoorPubliciteit->setEnabled( !RO );
    ui->tbWebsite->setEnabled( !RO );
    ui->tbFacebook->setEnabled( !RO );
    ui->tbLinckedIn->setEnabled( !RO );
    ui->tbRefBijRelatie->setEnabled( !RO );
    ui->tbNaceCode->setEnabled( !RO );
    ui->tbMailingcode->setEnabled( !RO );
    ui->dtpGeboorteDatum->setEnabled( !RO );
    ui->tbGeboorteplaats->setEnabled( !RO );
    ui->sbxAantalKinderen->setEnabled( !RO );
    ui->tbHobbys->setEnabled( !RO );
    ui->cbxBTWRegime->setEnabled( !RO );
    ui->tbBTWAutorisatie->setEnabled( !RO );
    ui->cbxBKHCategorie->setEnabled( !RO );
    ui->cbxKortingsCategorie->setEnabled( !RO );
    ui->tbKredietLimiet->setEnabled( !RO );
    ui->cbxBetalingsTermijn->setEnabled( !RO );
    ui->tbBankrekening1->setEnabled( !RO );
    ui->tbIban1->setEnabled( !RO );
    ui->tbBankrekening2->setEnabled( !RO );
    ui->tbIban2->setEnabled( !RO );
    ui->tbPopUpTekst->setEnabled( !RO );
    ui->tbOpmerkingen->setEnabled( !RO );
    ui->tbID_1->setEnabled( !RO );
    ui->tbID_2->setEnabled( !RO );
    ui->tbID_3->setEnabled( !RO );
    ui->tbID_4->setEnabled( !RO );
    ui->tbID_5->setEnabled( !RO );

    //    -Diverse
    ui->tbIDCartNummer->setEnabled( !RO );
    ui->tbRijksregisterNummer->setEnabled( !RO );
    ui->tbUitgereiktTe->setEnabled( !RO );
    ui->dtpGeldigVan->setEnabled( !RO );
    ui->dtpGeldigTot->setEnabled( !RO );
    ui->cbFlag1->setEnabled( !RO );
    ui->cbFlag2->setEnabled( !RO );
    ui->cbFlag3->setEnabled( !RO );
    ui->cbFlag4->setEnabled( !RO );
    ui->cbFlag5->setEnabled( !RO );
    ui->cbFlag6->setEnabled( !RO );
    SetFieldValues();

    ui->cbFlag7->setEnabled( !RO );
    ui->cbFlag8->setEnabled( !RO );
    ui->cbFlag9->setEnabled( !RO );
    ui->cbFlag10->setEnabled( !RO );
    ui->tbVrijTekst1->setEnabled( !RO );
    ui->tbVrijTekst2->setEnabled( !RO );
    ui->tbVrijTekst3->setEnabled( !RO );
    ui->tbVrijTekst4->setEnabled( !RO );
    ui->tbVrijTekst5->setEnabled( !RO );
    ui->tbVrijNum1->setEnabled( !RO );
    ui->tbVrijNum2->setEnabled( !RO );
    ui->tbVrijNum3->setEnabled( !RO );
    ui->tbVrijNum4->setEnabled( !RO );
    SetFieldValues();

    ui->tbVrijNum5->setEnabled( !RO );

    // Buttons
    ui->btnID_Cart->setEnabled( !RO );
    ui->btnNaceCode->setEnabled( !RO );
    ui->btnPostcodeFilter->setEnabled( !RO );
    ui->btnBTW->setEnabled( !RO );
}

//---------------------------------------------------------------------------------------------------------
//  Invullen van de velden
//
void RelatieFiche::SetFieldValues()
{
    // -Fields:
    //    -Hoofding

    ui->tbNaam->setText(rel->getNaam());
    ui->tbVoornaam->setText(rel->getVoornaam());

    ui->cbIsFirmanaam->setChecked(rel->getIsFirmaNaam());
    ui->tbAankoper->setText(rel->getAankoper());
    ui->cbIsBedrijf->setChecked(rel->getIsBedrijf());
    ui->tbAdres->setText(rel->getAdres());
    ui->tbBusNummer->setText(rel->getNrBus());

    ui->cbxPostcode->setCurrentIndex((rel->getGemeente_ID() == 0 ? 0 :
                ui->cbxPostcode->model()->match(
                    ui->cbxPostcode->model()->index(0, 0), Qt::DisplayRole, QVariant::fromValue(rel->getGemeente_ID()),-1 ,Qt::MatchFixedString).first().row()));

    ui->cbxGemeente->setCurrentIndex((rel->getGemeente_ID() == 0 ? 0 :
                ui->cbxGemeente->model()->match(
                ui->cbxGemeente->model()->index(0, 0),
                Qt::DisplayRole,
                QVariant::fromValue(rel->getGemeente_ID()),
                -1 ,
                Qt::MatchFixedString).first().row()));

    ui->cbxLand->setCurrentIndex((rel->getLandCode() == "" ? 0 :
                ui->cbxLand->model()->match(
                    ui->cbxLand->model()->index(0, 0), Qt::DisplayRole, QVariant::fromValue(rel->getLandCode()),-1 ,Qt::MatchFixedString).first().row()));


    ui->cbxTalen->setCurrentIndex(( rel->getTaal_ID() == 0 ? 0 :
                                          ui->cbxTalen->model()->match(
                                              ui->cbxTalen->model()->index(0, 0), Qt::DisplayRole, QVariant::fromValue(rel->getTaal_ID()),-1 ,Qt::MatchFixedString).first().row()));

    ui->tbTelefoon->setText(rel->getTel_1());
    ui->cbTelefoonVoorContact->setChecked(rel->getTel_1_Contact());
    ui->cbTelefoonVoorPubliciteit->setChecked(rel->getTel_1_Publiciteit());

    ui->tbGSM->setText(rel->getGSM_1());
    ui->cbGSMVoorContact->setChecked(rel->getGSM_1_Contact());
    ui->cbGSMVoorPubliciteit->setChecked(rel->getGSM_1_Publiciteit());

    ui->cbxAanspreking->setCurrentIndex(( rel->getAanspreking_ID() == 0 ? 0 :
                                          ui->cbxAanspreking->model()->match(
                                              ui->cbxAanspreking->model()->index(0, 0), Qt::DisplayRole, QVariant::fromValue(rel->getAanspreking_ID()),-1 ,Qt::MatchFixedString).first().row()));

    ui->tbBTWNummer->setText(rel->getBTWNummer());

    ui->cbxFirma->setCurrentIndex(( rel->getFirma_ID() == 0 ? 0 :
                                          ui->cbxFirma->model()->match(
                                              ui->cbxFirma->model()->index(0, 0), Qt::DisplayRole, QVariant::fromValue(rel->getFirma_ID()),-1 ,Qt::MatchFixedString).first().row()));

    ui->cbxSite->setCurrentIndex(( rel->getSite_ID() == 0 ? 0 :
                                          ui->cbxSite->model()->match(
                                              ui->cbxSite->model()->index(0, 0), Qt::DisplayRole, QVariant::fromValue(rel->getSite_ID()),-1 ,Qt::MatchFixedString).first().row()));

    ui->cbxAfdeling->setCurrentIndex(( rel->getAfdeling_ID() == 0 ? 0 :
                                          ui->cbxAfdeling->model()->match(
                                              ui->cbxAfdeling->model()->index(0, 0), Qt::DisplayRole, QVariant::fromValue(rel->getAfdeling_ID()),-1 ,Qt::MatchFixedString).first().row()));

    ui->cbxGebruiker->setCurrentIndex(( rel->getGebruiker_ID() == 0 ? 0 :
                                          ui->cbxGebruiker->model()->match(
                                              ui->cbxGebruiker->model()->index(0, 0), Qt::DisplayRole, QVariant::fromValue(rel->getGebruiker_ID()),-1 ,Qt::MatchFixedString).first().row()));

    ui->cbxGeslacht->setCurrentIndex(( rel->getGeslachtCode() == "" ? 0 :
                                          ui->cbxGeslacht->model()->match(
                                              ui->cbxGeslacht->model()->index(0, 0), Qt::DisplayRole, QVariant::fromValue(rel->getGeslachtCode()),-1 ,Qt::MatchFixedString).first().row()));


    ui->tbHerkomst->setText(rel->getHerkomst());
    ui->tbBeroep->setText(rel->getBeroep());

    ui->cbIsProspect->setChecked(rel->getIsProspect());
    ui->cbIsKlant->setChecked(rel->getIsKlant());
    ui->cbIsLeverancier->setChecked(rel->getIsLeverancier());
    ui->cbIsBenaderbaar->setChecked(rel->getIsBenaderbaar());
    ui->cbNeemtDeel->setChecked( rel->getIsDeelnemer() );
    ui->cbIsVerhuisd->setChecked( rel->getIsVerhuisd() );
    ui->cbIsInactief->setChecked( rel->getIsInactief() );
    ui->cbLopendeKlacht->setChecked( rel->getIsLopendeKlacht() );
    ui->cbIsOverleden->setChecked( rel->getIsOverleden() );

    //    -Contactgegevens
    ui->tbTel2->setText(rel->getTel_2());
    ui->cbTel2VoorContact->setChecked(rel->getTel_2_Contact());
    ui->cbTel2VoorPubliciteit->setChecked(rel->getTel_2_Publiciteit());

    ui->tbFax->setText(rel->getFax());
    ui->cbFaxVoorContact->setChecked(rel->getFax_Contact());
    ui->cbFaxVoorPubliciteit->setChecked(rel->getFax_Publiciteit());

    ui->tbEmail1->setText(rel->getEMail_1());
    ui->cbEmail1VoorContact->setChecked(rel->getEMail_1_Contact());
    ui->cbEmail1VoorPubliciteit->setChecked(rel->getEMail_1_Publiciteit());
    ui->tbEmail2->setText(rel->getEMail_2());
    ui->cbEmail2VoorContact->setChecked(rel->getEMail_2_Contact());
    ui->cbEmail2VoorPubliciteit->setChecked(rel->getEMail_2_Publiciteit());

    ui->cbAdresVoorContact->setChecked(rel->getAdres_Contact());
    ui->cbAdresVoorPubliciteit->setChecked(rel->getAdres_Publiciteit());

    ui->tbWebsite->setText(rel->getWebsite());
    ui->tbFacebook->setText(rel->getFacebook());
    ui->tbLinckedIn->setText(rel->getLinked_in());

    ui->tbRefBijRelatie->setText(rel->getRefBijRelatie());
    ui->tbNaceCode->setText(rel->getNACECode());
    ui->tbMailingcode->setText(rel->getMailingCode());
    ui->dtpGeboorteDatum->setDate(rel->getGeboortedatum());
    ui->tbGeboorteplaats->setText(rel->getGeboorteplaats());
    ui->sbxAantalKinderen->setValue(rel->getAantalKinderen());
    ui->tbHobbys->setText(rel->getHobby());

    ui->cbxBTWRegime->setCurrentIndex(( rel->getBTWRegime_ID() == 0 ? 0 :
                                          ui->cbxBTWRegime->model()->match(
                                              ui->cbxBTWRegime->model()->index(0, 0), Qt::DisplayRole, QVariant::fromValue(rel->getBTWRegime_ID()),-1 ,Qt::MatchFixedString).first().row()));

    ui->tbBTWAutorisatie->setText(rel->getBTWAutorisatiecode());

    ui->cbxBKHCategorie->setCurrentIndex(( rel->getBKHCategorie_ID() == 0 ? 0 :
                                          ui->cbxBKHCategorie->model()->match(
                                              ui->cbxBKHCategorie->model()->index(0, 0), Qt::DisplayRole, QVariant::fromValue(rel->getBKHCategorie_ID()),-1 ,Qt::MatchFixedString).first().row()));

    ui->cbxKortingsCategorie->setCurrentIndex(( rel->getKortingsCategorie_ID() == 0 ? 0 :
                                          ui->cbxKortingsCategorie->model()->match(
                                              ui->cbxKortingsCategorie->model()->index(0, 0), Qt::DisplayRole, QVariant::fromValue(rel->getKortingsCategorie_ID()),-1 ,Qt::MatchFixedString).first().row()));

    ui->tbKredietLimiet->setText(QString("%1").arg(rel->getKredietlimiet(), 0, 'f', 2));

    ui->cbxBetalingsTermijn->setCurrentIndex(( rel->getBetalingstermijnID() == 0 ? 0 :
                                          ui->cbxBetalingsTermijn->model()->match(
                                              ui->cbxBetalingsTermijn->model()->index(0, 0), Qt::DisplayRole, QVariant::fromValue(rel->getBetalingstermijnID()),-1 ,Qt::MatchFixedString).first().row()));


    ui->tbBankrekening1->setText(rel->getBankrekening_1());
    ui->tbIban1->setText(rel->getIban_1());
    ui->tbBankrekening2->setText(rel->getBankrekening_2());
    ui->tbIban2->setText(rel->getIban_2());

    ui->tbPopUpTekst->setText(rel->getPopUpTekst());
    ui->tbOpmerkingen->setText(rel->getOpmerking());
    ui->tbID_1->setText(QString::number(rel->getID_1()));
    ui->tbID_2->setText(QString::number(rel->getID_2()));
    ui->tbID_3->setText(QString::number(rel->getID_3()));
    ui->tbID_4->setText(QString::number(rel->getID_4()));
    ui->tbID_5->setText(QString::number(rel->getID_5()));

    //    -Diverse
    ui->tbIDCartNummer->setText(rel->getIDCardNummer());
    ui->tbRijksregisterNummer->setText(rel->getRezivNummer());
    ui->tbUitgereiktTe->setText(rel->getIDCardUitgereiktTe());
    ui->dtpGeldigVan->setDate(rel->getIDGeldigVan());
    ui->dtpGeldigTot->setDate(rel->getIDGeldigTot());

    ui->cbFlag1->setChecked(rel->getFlag_1());
    ui->cbFlag2->setChecked(rel->getFlag_2());
    ui->cbFlag3->setChecked(rel->getFlag_3());
    ui->cbFlag4->setChecked(rel->getFlag_4());
    ui->cbFlag5->setChecked(rel->getFlag_5());
    ui->cbFlag6->setChecked(rel->getFlag_6());
    ui->cbFlag7->setChecked(rel->getFlag_7());
    ui->cbFlag8->setChecked(rel->getFlag_8());
    ui->cbFlag9->setChecked(rel->getFlag_9());
    ui->cbFlag10->setChecked(rel->getFlag_10());

    ui->tbVrijTekst1->setText(rel->getVrijTekst_1());
    ui->tbVrijTekst2->setText(rel->getVrijTekst_2());
    ui->tbVrijTekst3->setText(rel->getVrijTekst_3());
    ui->tbVrijTekst4->setText(rel->getVrijTekst_4());
    ui->tbVrijTekst5->setText(rel->getVrijTekst_5());

    ui->tbVrijNum1->setText(QString("%1").arg(rel->getVrijNum_1()));
    ui->tbVrijNum2->setText(QString("%1").arg(rel->getVrijNum_2()));
    ui->tbVrijNum3->setText(QString("%1").arg(rel->getVrijNum_3()));
    ui->tbVrijNum4->setText(QString("%1").arg(rel->getVrijNum_4()));
    ui->tbVrijNum5->setText(QString("%1").arg(rel->getVrijNum_5()));

}


void RelatieFiche::on_actionStop_triggered()
{
    if (dirty && !_find)
    {
        // TODO - Functie implementeren
        QMessageBox msgBox;
        msgBox.setWindowTitle("Opgelet");
        msgBox.setText("Er zijn aanpassingen gebeurt aan dit formulier,\nWil je die eerst opslaan?");
        msgBox.setStandardButtons( QMessageBox::No | QMessageBox::Yes);
        msgBox.setIcon(QMessageBox::Question);
        if (msgBox.exec() == QMessageBox::No)
        {
            this->close();
        }
    }
    else
    {
        this->close();
    }

    //delete this;
}

void RelatieFiche::closeEvent(QCloseEvent* )
{
    //event->setAccepted(true);
    delete this;
}

void RelatieFiche::on_btnNaceCode_clicked()
{
    // TODO - Functie implementeren
    QMessageBox msgBox;
    msgBox.setWindowTitle("Opgelet");
    msgBox.setText("Deze functie is nog niet geimplementeerd");
    msgBox.setStandardButtons(QMessageBox::Yes);
    msgBox.setIcon(QMessageBox::Information);
    msgBox.exec();
}

void RelatieFiche::on_btnID_Cart_clicked()
{
    // TODO - Functie implementeren
    QMessageBox msgBox;
    msgBox.setWindowTitle("Opgelet");
    msgBox.setText("Deze functie is nog niet geimplementeerd");
    msgBox.setStandardButtons(QMessageBox::Yes);
    msgBox.setIcon(QMessageBox::Information);
    msgBox.exec();
}

void RelatieFiche::on_actionNewRelatie_triggered()
{
    NewRecord();
}

void RelatieFiche::NewRecord()
{
    rel = new Relaties();
    SetFieldsReadOnly( false );
    FillComboBoxes();
    SetFieldValues();
    this->setWindowTitle("Relatiefiche - <Nieuwe Relatie>");
    _find = false;
    dirty = false;
    rel->setRelatie_ID(0);
    ui->actionFindRelatie->setEnabled(true);
    ui->actionNewRelatie->setEnabled(true);
    ui->actionEditRelatie->setEnabled(false);
    ui->actionSaveRelatie->setEnabled(true);
    ui->actionStop->setEnabled(true);

}

void RelatieFiche::on_actionEditRelatie_triggered()
{
    EditRecord();
}

void RelatieFiche::EditRecord()
{
    SetFieldsReadOnly( false );
    ui->actionEditRelatie->setEnabled(false);
    ui->actionSaveRelatie->setEnabled(true);

}

void RelatieFiche::on_actionSaveRelatie_triggered()
{
    SaveRecord();
    dirty = false;
}

bool RelatieFiche::ReadFields()
{
    bool OK = true;
    // -Fields:
    //    -Hoofding
    rel->setNaam(ui->tbNaam->text());
    rel->setVoornaam(ui->tbVoornaam->text());
    rel->setIsFirmaNaam(ui->cbIsFirmanaam->isChecked());
    rel->setAankoper(ui->tbAankoper->text());
    rel->setIsBedrijf(ui->cbIsBedrijf->isChecked());
    rel->setAdres(ui->tbAdres->text());
    rel->setNrBus(ui->tbBusNummer->text());
    //    ui->cbxPostcode->setEnabled( !RO );
    rel->setGemeente_ID(ui->cbxGemeente->model()->data( ui->cbxGemeente->model()->index(ui->cbxGemeente->currentIndex(), 0 )).toInt());
    rel->setLandCode(ui->cbxLand->model()->data( ui->cbxLand->model()->index(ui->cbxLand->currentIndex(), 0 )).toString());
    rel->setTaal_ID(ui->cbxTalen->model()->data( ui->cbxTalen->model()->index(ui->cbxTalen->currentIndex(), 0 )).toInt());
    rel->setTel_1(ui->tbTelefoon->text());
    rel->setTel_1_Contact(ui->cbTelefoonVoorContact->isChecked());
    rel->setTel_1_Publiciteit(ui->cbTelefoonVoorPubliciteit->isChecked());
    rel->setGSM_1(ui->tbGSM->text());
    rel->setGSM_1_Contact(ui->cbGSMVoorContact->isChecked());
    rel->setGSM_1_Publiciteit(ui->cbGSMVoorPubliciteit->isChecked());
    rel->setAanspreking_ID(ui->cbxAanspreking->model()->data( ui->cbxAanspreking->model()->index(ui->cbxAanspreking->currentIndex(), 0 )).toInt());
    rel->setBTWNummer(ui->tbBTWNummer->text());
    rel->setFirma_ID(ui->cbxFirma->model()->data( ui->cbxFirma->model()->index(ui->cbxFirma->currentIndex(), 0 )).toInt());
    rel->setSite_ID(ui->cbxSite->model()->data( ui->cbxSite->model()->index(ui->cbxSite->currentIndex(), 0 )).toInt());
    rel->setAfdeling_ID(ui->cbxAfdeling->model()->data( ui->cbxAfdeling->model()->index(ui->cbxAfdeling->currentIndex(), 0 )).toInt());
    rel->setGebruiker_ID(ui->cbxGebruiker->model()->data( ui->cbxGebruiker->model()->index(ui->cbxGebruiker->currentIndex(), 0 )).toInt());
    rel->setGeslachtCode(ui->cbxGeslacht->model()->data( ui->cbxGeslacht->model()->index(ui->cbxGeslacht->currentIndex(), 0 )).toString());
    rel->setHerkomst(ui->tbHerkomst->text());
    rel->setBeroep(ui->tbBeroep->text());
    rel->setIsProspect(ui->cbIsProspect->isChecked());
    rel->setIsKlant(ui->cbIsKlant->isChecked());
    rel->setIsLeverancier(ui->cbIsLeverancier->isChecked());
    rel->setIsBenaderbaar(ui->cbIsBenaderbaar->isChecked());
    rel->setIsDeelnemer(ui->cbNeemtDeel->isChecked());
    rel->setIsVerhuisd(ui->cbIsVerhuisd->isChecked());
    rel->setIsInactief(ui->cbIsInactief->isChecked());
    rel->setIsLopendeKlacht(ui->cbLopendeKlacht->isChecked());
    rel->setIsOverleden(ui->cbIsOverleden->isChecked());

    //    -Contactgegevens
    rel->setTel_2(ui->tbTel2->text());
    rel->setTel_2_Contact(ui->cbTel2VoorContact->isChecked());
    rel->setTel_2_Publiciteit(ui->cbTel2VoorPubliciteit->isChecked());
    rel->setFax(ui->tbFax->text());
    rel->setFax_Contact(ui->cbFaxVoorContact->isChecked());
    rel->setFax_Publiciteit(ui->cbFaxVoorPubliciteit->isChecked());
    rel->setEMail_1(ui->tbEmail1->text());
    rel->setEMail_1_Contact(ui->cbEmail1VoorContact->isChecked());
    rel->setEMail_1_Publiciteit(ui->cbEmail1VoorPubliciteit->isChecked());
    rel->setEMail_2(ui->tbEmail2->text());
    rel->setEMail_2_Contact(ui->cbEmail2VoorContact->isChecked());
    rel->setEMail_2_Publiciteit(ui->cbEmail2VoorPubliciteit->isChecked());
    rel->setAdres_Contact(ui->cbAdresVoorContact->isChecked());
    rel->setAdres_Publiciteit(ui->cbAdresVoorPubliciteit->isChecked());
    rel->setWebsite(ui->tbWebsite->text());
    rel->setFacebook(ui->tbFacebook->text());
    rel->setLinked_in(ui->tbLinckedIn->text());
    rel->setRefBijRelatie(ui->tbRefBijRelatie->text());
    rel->setNACECode(ui->tbNaceCode->text());
    rel->setMailingCode(ui->tbMailingcode->text());
    rel->setGeboortedatum(ui->dtpGeboorteDatum->date());
    rel->setGeboorteplaats(ui->tbGeboorteplaats->text());
    rel->setAantalKinderen(ui->sbxAantalKinderen->value());
    rel->setHobby(ui->tbHobbys->text());
    rel->setBTWRegime_ID(ui->cbxBTWRegime->model()->data( ui->cbxBTWRegime->model()->index(ui->cbxBTWRegime->currentIndex(), 0 )).toInt());
    rel->setBTWAutorisatiecode(ui->tbBTWAutorisatie->text());
    rel->setBKHCategorie_ID(ui->cbxBKHCategorie->model()->data( ui->cbxBKHCategorie->model()->index(ui->cbxBKHCategorie->currentIndex(), 0 )).toInt());
    rel->setKortingsCategorie_ID(ui->cbxKortingsCategorie->model()->data( ui->cbxKortingsCategorie->model()->index(ui->cbxKortingsCategorie->currentIndex(), 0 )).toInt());
    rel->setKredietlimiet(ui->tbKredietLimiet->text().toDouble());
    rel->setBetalingstermijnID(ui->cbxBetalingsTermijn->model()->data( ui->cbxBetalingsTermijn->model()->index(ui->cbxBetalingsTermijn->currentIndex(), 0 )).toInt());
    rel->setBankrekening_1(ui->tbBankrekening1->text());
    rel->setIban_1(ui->tbIban1->text());
    rel->setBankrekening_2(ui->tbBankrekening2->text());
    rel->setIban_2(ui->tbIban2->text());
    rel->setPopUpTekst(ui->tbPopUpTekst->toPlainText());
    rel->setOpmerking(ui->tbOpmerkingen->toPlainText());
    rel->setID_1(ui->tbID_1->text().toInt());
    rel->setID_2(ui->tbID_2->text().toInt());
    rel->setID_3(ui->tbID_3->text().toInt());
    rel->setID_4(ui->tbID_4->text().toInt());
    rel->setID_5(ui->tbID_5->text().toInt());

    //    -Diverse
    rel->setIDCardNummer(ui->tbIDCartNummer->text());
    rel->setRezivNummer(ui->tbRijksregisterNummer->text());
    rel->setIDCardUitgereiktTe(ui->tbUitgereiktTe->text());
    rel->setIDGeldigVan(ui->dtpGeldigVan->date());
    rel->setIDGeldigTot(ui->dtpGeldigTot->date());
    rel->setFlag_1(ui->cbFlag1->isChecked());
    rel->setFlag_2(ui->cbFlag2->isChecked());
    rel->setFlag_3(ui->cbFlag3->isChecked());
    rel->setFlag_4(ui->cbFlag4->isChecked());
    rel->setFlag_5(ui->cbFlag5->isChecked());
    rel->setFlag_6(ui->cbFlag6->isChecked());
    rel->setFlag_7(ui->cbFlag7->isChecked());
    rel->setFlag_8(ui->cbFlag8->isChecked());
    rel->setFlag_9(ui->cbFlag9->isChecked());
    rel->setFlag_10(ui->cbFlag10->isChecked());
    rel->setVrijTekst_1(ui->tbVrijTekst1->text());
    rel->setVrijTekst_2(ui->tbVrijTekst2->text());
    rel->setVrijTekst_3(ui->tbVrijTekst3->text());
    rel->setVrijTekst_4(ui->tbVrijTekst4->text());
    rel->setVrijTekst_5(ui->tbVrijTekst5->text());
    rel->setVrijNum_1(ui->tbVrijNum1->text().toDouble());
    rel->setVrijNum_2(ui->tbVrijNum2->text().toDouble());
    rel->setVrijNum_3(ui->tbVrijNum3->text().toDouble());
    rel->setVrijNum_4(ui->tbVrijNum4->text().toDouble());
    rel->setVrijNum_5(ui->tbVrijNum5->text().toDouble());



    return OK;
}

void RelatieFiche::SaveRecord()
{
    if (ReadFields())
    {
        rel->save();
        SetFieldsReadOnly( true );
        ui->actionEditRelatie->setEnabled(true);
        ui->actionSaveRelatie->setEnabled(false);

    }
}

void RelatieFiche::on_actionFindRelatie_triggered()
{
    FindRecord();
}

void RelatieFiche::FindRecord()
{
    if (_find)
    {
        QString _naam, _adres, _gemeente, _email;
        int _ID;
        _ID = ui->tbID->text().toInt();
        _naam = ui->tbNaam->text();
        _adres = ui->tbAdres->text();
        _gemeente = ui->cbxGemeente->lineEdit()->text();
        _email = ui->tbEmail1->text();

        if (_ID > 0)
        {
            rel = new Relaties(_ID);
            if (rel->getRelatie_ID() > 0)
            {
                SetFieldsReadOnly(true);
                FillComboBoxes();
                SetFieldValues();
                ui->actionEditRelatie->setEnabled(true);
                ui->actionSaveRelatie->setEnabled(false);

                dirty = false;
                _find = false;
            }
        }
        else
        {
            FindRelaties *fr = new FindRelaties(_naam, _adres, _gemeente, _email);
            fr->exec();
            rel = new Relaties(fr->getID());
            if (rel->getRelatie_ID() > 0)
            {
                SetFieldsReadOnly(true);
                FillComboBoxes();
                SetFieldValues();

                ui->actionEditRelatie->setEnabled(true);
                ui->actionSaveRelatie->setEnabled(false);

                dirty = false;
                _find = false;
            }
        }
    }
    else
    {
        PrepareFind();
    }
}


void RelatieFiche::on_cbxGeslacht_activated(int index)
{
    QString code = ui->cbxGeslacht->itemData(index).toString();
}


void RelatieFiche::on_cbxPostcode_activated(int index)
{
//    //QModelIndex myindex = model->index(index, 0, QModelIndex());
//    QString gegevens = "";
//    gegevens = ui->cbxPostcode->model()->data( ui->cbxPostcode->model()->index(index, 0 )).toString();
//    qDebug()<< "index 0: " << gegevens;
//    gegevens = ui->cbxPostcode->model()->data( ui->cbxPostcode->model()->index(index, 1 )).toString();
//    qDebug()<< "index 1: " << gegevens;
}

void RelatieFiche::on_cbxPostcode_LineEditTextChanged()
{
    QString curText = ui->cbxPostcode->currentText();
    int indx = ui->cbxPostcode->findText(curText);
    if (indx == -1)
    {
        QMessageBox msgBox;
        msgBox.setWindowTitle("Opgelet");
        msgBox.setText("Deze postkode is niet gekend voor dit land,\nWil je een nieuwe aanmaken?");
        msgBox.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
        msgBox.setIcon(QMessageBox::Question);
        if (msgBox.exec() == QMessageBox::Yes)
        {
            // TODO - Functie implementeren
            QMessageBox msgBox;
            msgBox.setWindowTitle("Opgelet");
            msgBox.setText("Deze functie is nog niet geimplementeerd");
            msgBox.setStandardButtons(QMessageBox::Yes);
            msgBox.setIcon(QMessageBox::Information);
            msgBox.exec();

        }
        else
        {
            ui->cbxPostcode->setFocus();
            ui->cbxPostcode->clearEditText();
        }
    }
    else
    {
        ui->cbxPostcode->setCurrentIndex(indx);
    }
}

void RelatieFiche::on_cbxPostcode_currentIndexChanged(int index)
{
    QString gegevens = "";
    gegevens = ui->cbxPostcode->model()->data( ui->cbxPostcode->model()->index(index, 0 )).toString();
    qDebug()<< "index 0: " << gegevens;
}


//-----------------------------------------------------------------------------------------------------------
//  Form is ergens geëditeerd
//
void RelatieFiche::on_formEdited(const QString &arg1)
{
    dirty = true;
}

void RelatieFiche::on_cbx_currentIndexChanged(const QString &arg1)
{
    dirty = true;
}

void RelatieFiche::on_cb_stateChanged(int arg1)
{
    dirty = true;
}

void RelatieFiche::on_dtp_DateChanged(const QDate &date)
{
    dirty = true;
}

void RelatieFiche::on_tbe_textChanged()
{
    dirty = true;
}

void RelatieFiche::on_sbxAantalKinderen_valueChanged(const QString &arg1)
{
    dirty = true;
}

void RelatieFiche::on_cb_toggled(bool checked)
{
    dirty = true;
}

void RelatieFiche::on_cbxGemeente_currentIndexChanged(int index)
{
    int curIndx;

    curIndx = ui->cbxGemeente->model()->data( ui->cbxGemeente->model()->index(index, 0 )).toInt();


    ui->cbxPostcode->setCurrentIndex((rel->getGemeente_ID() == 0 ? 0 :
                ui->cbxPostcode->model()->match(
                    ui->cbxPostcode->model()->index(0, 0), Qt::DisplayRole, QVariant::fromValue(curIndx),-1 ,Qt::MatchFixedString).first().row()));

}

void RelatieFiche::on_btnPostcodeFilter_clicked()
{
    int curIndx = ui->cbxPostcode->model()->data( ui->cbxPostcode->model()->index(ui->cbxPostcode->currentIndex(), 0 )).toInt();

    if (ui->btnPostcodeFilter->isChecked())
    {
        //      cbxGemeente
        Gemeenten_model = new QSqlQueryModel();
        Postcodes::getGemeentesPerLandEnPostcode(Gemeenten_model, rel->getLandCode(), ui->cbxPostcode->currentText() );
        ui->cbxGemeente->setModel(Gemeenten_model);
        ui->cbxGemeente->setModelColumn(1);
        //ui->cbxGemeente->setCurrentIndex(gemIndx);
        ui->cbxGemeente->setCurrentIndex((rel->getGemeente_ID() == 0 ? 0 :
                    ui->cbxGemeente->model()->match(
                        ui->cbxGemeente->model()->index(0, 0), Qt::DisplayRole, QVariant::fromValue(curIndx),-1 ,Qt::MatchFixedString).first().row()));

    }
    else
    {
        //      cbxGemeente
        Gemeenten_model = new QSqlQueryModel();
        Postcodes::getGemeentesPerLand(Gemeenten_model, rel->getLandCode() );
        ui->cbxGemeente->setModel(Gemeenten_model);
        ui->cbxGemeente->setModelColumn(1);
        ui->cbxPostcode->setCurrentIndex((rel->getGemeente_ID() == 0 ? 0 :
                    ui->cbxPostcode->model()->match(
                        ui->cbxPostcode->model()->index(0, 0), Qt::DisplayRole, QVariant::fromValue(curIndx),-1 ,Qt::MatchFixedString).first().row()));
        ui->cbxGemeente->setCurrentIndex((rel->getGemeente_ID() == 0 ? 0 :
                    ui->cbxGemeente->model()->match(
                        ui->cbxGemeente->model()->index(0, 0), Qt::DisplayRole, QVariant::fromValue(curIndx),-1 ,Qt::MatchFixedString).first().row()));

    }
}

void RelatieFiche::onResult(QNetworkReply* reply)
{
    // Reply
    //{"valid":true,"countryCode":"BE","vatNumber":"0430770268","name":"NV GARAGE WILLY",
    //"address":{"street":"Begoniastraat","number":"12","zip_code":"9810","city":"Nazareth",
    //"country":null,"countryCode":"BE"},"strAddress":"BEGONIASTRAAT 12\n9810 NAZARETH"}

    QString data = (QString)reply->readAll();
    QJsonDocument json = QJsonDocument::fromJson(data.toUtf8());
    QJsonObject obj = json.object();
    QJsonObject adr = obj.value("address").toObject();
    if(obj.value("valid").toBool() == true)
    {
        QMessageBox msgBox;
        msgBox.setWindowTitle("Opgelet");
        msgBox.setText("Naam:\t"+obj.value("name").toString()+"\n"+
                       "BTW:\t"+obj.value("countryCode").toString()+obj.value("vatNumber").toString()+"\n"+
                       "Adres:\t"+adr.value("street").toString()+" "+adr.value("number").toString()+"\n"+
                       "\t"+adr.value("zip_code").toString()+" "+adr.value("city").toString()+"\n\n"+
                       "Wilt u deze gegevens overnemen");
        msgBox.setStandardButtons(QMessageBox::No);
        msgBox.addButton(QMessageBox::Yes);
        msgBox.setIcon(QMessageBox::Question);
        if(msgBox.exec() == QMessageBox::Yes)
        {
            ui->tbNaam->setText(obj.value("name").toString());
            ui->tbBTWNummer->setText(obj.value("countryCode").toString()+obj.value("vatNumber").toString());
            ui->tbAdres->setText(adr.value("street").toString()+" "+adr.value("number").toString());

            int inx = ui->cbxPostcode->findText(adr.value("zip_code").toString());
            ui->cbxPostcode->setCurrentIndex(inx);

            inx = ui->cbxGemeente->findText(adr.value("city").toString().toUpper());
            if(inx >= 0)
                ui->cbxGemeente->setCurrentIndex(inx);

            if(adr.value("country").toString()=="")
            {
                if(adr.value("countryCode").toString()=="BE")
                {
                    ui->cbxLand->setCurrentText("Belgie");
                }
            }
            else
            {
                ui->cbxLand->setCurrentText(adr.value("country").toString());
            }
            qDebug() << obj.value("valid").toBool() << " Naam: " << obj.value("name").toString() << " Adres: " << adr.value("street").toString();
        }
    }
    else
    {
        QMessageBox msgBox;
        msgBox.setWindowTitle("Opgelet");
        msgBox.setText("Ongeldig BTW nummer of nummer niet gevonden");
        msgBox.setStandardButtons(QMessageBox::Ok);
        msgBox.setIcon(QMessageBox::Warning);
        msgBox.exec();
    }

    reply->deleteLater();
    networkManager.clearAccessCache();
}

void RelatieFiche::on_btnBTW_clicked()
{
    // vb. https://controleerbtwnummer.eu/api/validate/BE0430770268.json
    QString BTW = ui->tbBTWNummer->text();
    BTW.replace(" ","");
    BTW = BTW.toUpper();
    QUrl url("https://controleerbtwnummer.eu/api/validate/"+BTW+".json");
    QNetworkRequest request;
    request.setUrl(url);
    networkManager.get(request);
}
