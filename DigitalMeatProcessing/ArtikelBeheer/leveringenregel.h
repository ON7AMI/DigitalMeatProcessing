#ifndef LEVERINGENREGEL_H
#define LEVERINGENREGEL_H

#include "Bestellingen/leveringenline.h"
#include "Bestellingen/leveringenheader.h"
#include "leveranciercodes.h"
#include "levcodefiche.h"
#include "ArtikelBeheer/artikelen.h"



#include <QDialog>

namespace Ui {
class LeveringenRegel;
}

class LeveringenRegel : public QDialog
{
    Q_OBJECT

public:
    explicit LeveringenRegel(int _id, LeveringenHeader* lh, QWidget *parent = 0);
    ~LeveringenRegel();

private slots:
    void on_btnAnnuleren_clicked();
    void on_btnZoek_Art_clicked();
    void on_tbLevArtikelCode_editingFinished();
    void on_tbLevArtikelNaam_editingFinished();
    void on_tbArtikelCode_editingFinished();
    void on_tbEenheidsprijs_editingFinished();
    void on_tbHoeveelheid_editingFinished();
    void on_cbxBTW_currentIndexChanged(int index);
    void on_cbxEenheid_currentIndexChanged(int index);
    void on_tbArtikelnummer_editingFinished();
    void on_btnOvernemen_clicked();
    void on_cbxProduct_currentIndexChanged(int index);
    void on_cbxSoort_currentIndexChanged(int index);
    void on_cbxDetail_currentIndexChanged(int index);
    void on_cbxSpecificatie_currentIndexChanged(int index);
    void on_btnWis_Art_clicked();
    void on_btnWissen_clicked();


    void on_btnPrijsAanpassen_clicked();

    void on_btnPrijsOpslaan_clicked();

    void on_btnPrijsOvernemn_clicked();

    void on_tbGewenstePrijs_editingFinished();

    void on_btnPrijsAnnuleren_clicked();

    void on_btnMargeOvernemen_clicked();

    void on_tbGewensteMarge_editingFinished();

private:
    Ui::LeveringenRegel *ui;

    LeveringenLine* ll;
    LeveringenHeader* lh;
    LeverancierCodes* lc;
    Artikelen* art;

    int CurrentArt;
    int CurrentLeArtID;

    QSqlQueryModel* BTW_model;
    QSqlQueryModel* Eenh_model;
    QSqlQueryModel *prd_model;
    QSqlQueryModel *srt_model;
    QSqlQueryModel *det_model;
    QSqlQueryModel *spec_model;

    void FillBTWKeuze();
    void FillEenheidKeuze();

    int CurPrd_ID, CurSrt_ID, CurDet_ID, CurSpec_ID;
    bool initialised;
    double vorigeVKP, vorigeMarge;

    void FillProductkeuze();
    void FillSoortkeuze();
    void FillDetailKeuze();
    void FillSpecificatieKeuze();

    void ClearAllFields();
    void ClearArtikelFields();
    void FillFields();

    void ReadFields();

    void Bereken();
};

#endif // LEVERINGENREGEL_H
