#ifndef ARTIKELNUMMERBEHEER_H
#define ARTIKELNUMMERBEHEER_H

#include <QMainWindow>
#include "addproduct.h"
#include "addsoort.h"
#include "adddetail.h"
#include "artikelen.h"


namespace Ui {
class ArtikelnummerBeheer;
}

class ArtikelnummerBeheer : public QMainWindow
{
    Q_OBJECT

public:
    explicit ArtikelnummerBeheer(QWidget *parent = 0);
    ~ArtikelnummerBeheer();

private slots:
    void on_actionAfsluiten_triggered();
    void on_btnMaintProduct_clicked();
    void on_btnMaintSoort_clicked();
    void on_cbxProduct_currentIndexChanged(int index);
    void on_cbxSoort_currentIndexChanged(int index);
    void on_btnMaintDetail_clicked();
    void on_cbxDetail_currentIndexChanged(int index);
    void on_btnMaintSpecificatie_clicked();
    void on_cbxSpecificatie_currentIndexChanged(int index);
    void on_btnMaintEenheid_clicked();
    void on_btnMaintBTWtarief_clicked();
    void on_actionFind_triggered();
    void on_actionSave_triggered();
    void on_tbArtikelnummer_editingFinished();
    void on_tbVerkoopprijs_editingFinished();
    void on_tbPromotiePrijs_editingFinished();
    void on_tbMinimumVoorraad_editingFinished();
    void on_tbCritischeVoorraad_editingFinished();
    void on_tbMaximumVoorraad_editingFinished();
    void on_tbTemperatuur_editingFinished();
    void on_tbVochtigheid_editingFinished();
    void on_tbHoudbaarheid_editingFinished();
    void on_actionAanpassen_triggered();
    void on_btnAllergenen_clicked();
    void on_btnConcurentie_clicked();
    void on_btnIngredienten_clicked();

    void on_btnCalcVKP_clicked();

    void on_btnCalcPromo_clicked();

    void on_actionFind_changed();

    void on_tbMinWinstfactor_editingFinished();

private:
    Ui::ArtikelnummerBeheer *ui;
    Artikelen *art;
    int CurPrd_ID;
    int CurSrt_ID;
    int CurDet_ID;
    int CurSpec_ID;
    QSqlQueryModel *prd_model;
    QSqlQueryModel *srt_model;
    QSqlQueryModel *det_model;
    QSqlQueryModel *spec_model;
    QSqlQueryModel *Eenha_model;
    QSqlQueryModel *Eenhv_model;
    QSqlQueryModel *BTWa_model;
    QSqlQueryModel *BTWv_model;

private: // methods
    void FillSoortkeuze();
    void FillDetailKeuze();
    void FillSpecificatieKeuze();
    void FillEenheidAankoopKeuze();
    void FillEenheidVerkoopKeuze();
    void FillBTWAankoopKeuze();
    void FillBTWVerkoopKeuze();
    void FillAllergenen();
    void FillConcurentPrijzen();
    void FillIngredienten();
    bool AdjustSamenstelling(QString _code);

    void BlockKeuze(bool block);
    void OpenEditFields(bool open);
    void SetEditMode();
    void SetKijkMode();
    void ClearFields();
    void FillFields();
    void ReadFields();
    void MeldGetalError();
};

#endif // ARTIKELNUMMERBEHEER_H
