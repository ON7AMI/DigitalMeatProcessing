//======================================================================================================
//
//                        ==== ON7AMI = Project: Digital Meat Processing ====
//
//======================================================================================================
//
//   Doel:    Relatie fiche voor bijhouden en opzoeken relaties
//   File:    Relatiefiche.h
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
//
//
//========================================================================================================


#ifndef RELATIEFICHE_H
#define RELATIEFICHE_H

#include "relaties.h"

#include <QMainWindow>
#include <QSqlTableModel>
#include <QStandardItemModel>
#include <QNetworkReply>
#include <QNetworkAccessManager>

namespace Ui {
class RelatieFiche;
}

class RelatieFiche : public QMainWindow
{
    Q_OBJECT

public:

    enum OpenAs
    {
        OpenAsFind,
        OpenAsNew,
        OpenAsView,
        OpenAsEdit,
        OpenAsSettings,
    };


    explicit RelatieFiche(OpenAs, int _id = 0, QWidget *parent = 0);
    void SetMode(RelatieFiche::OpenAs);
    ~RelatieFiche();


private slots:
    void on_actionStop_triggered();
    void on_btnNaceCode_clicked();
    void on_btnID_Cart_clicked();
    void closeEvent(QCloseEvent* event);
    void on_actionNewRelatie_triggered();
    void on_actionEditRelatie_triggered();
    void on_actionSaveRelatie_triggered();
    void on_actionFindRelatie_triggered();
    void on_cbxGeslacht_activated(int index);
    void on_cbxPostcode_activated(int index);
    void on_cbxPostcode_LineEditTextChanged();
    void on_cbxPostcode_currentIndexChanged(int index);
    void on_formEdited(const QString &arg1);
    void on_cbx_currentIndexChanged(const QString &arg1);
    void on_cb_stateChanged(int arg1);
    void on_dtp_DateChanged(const QDate &date);
    void on_tbe_textChanged();
    void on_sbxAantalKinderen_valueChanged(const QString &arg1);
    void on_cb_toggled(bool checked);

    void on_cbxGemeente_currentIndexChanged(int index);

    void on_btnPostcodeFilter_clicked();

    void on_btnBTW_clicked();
    void onResult(QNetworkReply* reply);

private:    // Variabelen

    Ui::RelatieFiche *ui;

    Relaties* rel;

    RelatieFiche::OpenAs OpenMode;

    bool dirty;             // Flag die aangeeft of ergens een veld is aangepast.
    bool _find;             // Flag die aangeeft of fiche in zoekstand staat

    QSqlTableModel* Talen_model;
    QSqlQueryModel* Postcodes_model;
    QSqlQueryModel* Gemeenten_model;
    QSqlQueryModel* Landen_model;
    QStandardItemModel* Geslachten_model;
    QSqlQueryModel* Aansprekingen_model;
    QSqlQueryModel* Firmas_model;
    QSqlQueryModel* Sites_model;
    QSqlQueryModel* Afdelingen_model;
    QSqlQueryModel* Gebruiker_model;
    QSqlQueryModel* BTWRegime_model;
    QSqlQueryModel* BKHCategorie_model;
    QSqlQueryModel* KortingsCategorie_model;
    QSqlQueryModel* BetalingsTermijn_model;



private:    // Methodes

    void FillComboBoxes();
    void SetFieldsReadOnly(bool RO);
    void SetFieldValues();
    void HideVrijeVelden();
    void NewRecord();
    void SaveRecord();
    void EditRecord();
    void FindRecord();
    void SetFieldValidators();
    bool ReadFields();
    void PrepareFind();

    QNetworkAccessManager networkManager;



};

#endif // RELATIEFICHE_H
