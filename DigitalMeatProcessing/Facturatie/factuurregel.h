#ifndef FACTUURREGEL_H
#define FACTUURREGEL_H

#include "factuurline.h"
#include "ArtikelBeheer/artikelen.h"

#include <QDialog>
#include <QObject>
#include <QSqlQueryModel>

namespace Ui {
class FactuurRegel;
}

class FactuurRegel : public QDialog
{
    Q_OBJECT

public:
    explicit FactuurRegel(int _factuurID, int _id, QWidget *parent = 0);
    ~FactuurRegel();

private slots:
    void on_btnZoek_Art_clicked();

    void on_tbEenheidsprijs_editingFinished();

    void on_tbHoeveelheid_editingFinished();

    void on_tbKorting_editingFinished();

    void on_tbArtikelCode_editingFinished();

    void on_tbArtikelNaam_editingFinished();

    void on_cbxBTW_currentIndexChanged(int index);

    void on_cbxEenheid_currentIndexChanged(int index);

    void on_tbArtikelnummer_editingFinished();

    void on_btnAnnuleren_clicked();

    void on_btnOvernemen_clicked();

    void on_cbxProduct_currentIndexChanged(int index);

    void on_cbxSoort_currentIndexChanged(int index);

    void on_cbxDetail_currentIndexChanged(int index);

    void on_cbxSpecificatie_currentIndexChanged(int index);

    void on_btnWis_Art_clicked();

    void on_btnWissen_clicked();

private:
    Ui::FactuurRegel *ui;
    int CurrentFactuurID;
    int CurrentArt;
    Artikelen* art;
    FactuurLine* fl;
    QSqlQueryModel* BTW_model;
    QSqlQueryModel* Eenh_model;
    QSqlQueryModel *prd_model;
    QSqlQueryModel *srt_model;
    QSqlQueryModel *det_model;
    QSqlQueryModel *spec_model;

    void ClearArtikelFields();

    int CurPrd_ID, CurSrt_ID, CurDet_ID, CurSpec_ID;

    void FillProductkeuze();
    void FillSoortkeuze();
    void FillDetailKeuze();
    void FillSpecificatieKeuze();

    void FillArtikelFields();
    void FillBTWKeuze();
    void FillEenheidKeuze();
    void FillRecord();

    void ReadFields();

    void Bereken();
};

#endif // FACTUURREGEL_H
