#ifndef LOTNUMMERS_H
#define LOTNUMMERS_H

#include "lotnummerdata.h"
#include "CommonObjects/postcodes.h"
#include "ArtikelBeheer/artikelen.h"
#include "Relaties/relaties.h"
#include <QMainWindow>

namespace Ui {
class Lotnummers;
}

class Lotnummers : public QMainWindow
{
    Q_OBJECT

public:
    explicit Lotnummers(QWidget *parent = 0);
    ~Lotnummers();

private slots:
    void on_actionNieuw_triggered();

    void on_actionPrint_Label_triggered();
    void on_btnZoek_Lev_clicked();
    void on_cbxProduct_currentIndexChanged(int index);
    void on_cbxSoort_currentIndexChanged(int index);
    void on_cbxDetail_currentIndexChanged(int index);
    void on_cbxSpecificatie_currentIndexChanged(int index);
    void on_btnZoek_Art_clicked();
    void on_tbArtikelnummer_editingFinished();
    void on_actionLotnummer_opslaan_triggered();
    void on_tbLotnummer_editingFinished();
    void on_actionAfsluiten_triggered();
    void on_tbHoudbaarheid_editingFinished();
    void on_tbIn_editingFinished();
    void on_tbUit_editingFinished();
    void on_tbAfval_editingFinished();
    void on_btnWis_Lev_clicked();
    void on_btnWis_Art_clicked();
    void on_btnAfval_clicked();
    void on_actionBewerken_triggered();
    void on_btnNew_clicked();
    void on_btnDelete_clicked();
    void on_btnEdit_clicked();
    void on_actionOp_artikelnr_triggered();
    void on_cbxLocatie_currentIndexChanged(int index);

private:
    Ui::Lotnummers *ui;
    LotnummerData* lot;
    QString CurrentLotnummer;
    int CurrentLev;
    int CurrentArt;

    bool initialised;


    QString m_sSettingsFile;

    Relaties* rel;
    Artikelen* art;
    QSqlQueryModel *prd_model;
    QSqlQueryModel *srt_model;
    QSqlQueryModel *det_model;
    QSqlQueryModel *spec_model;
    QSqlQueryModel *loc_model;
    QSqlQueryModel *bevat_model;

    int CurPrd_ID, CurSrt_ID, CurDet_ID, CurSpec_ID;
    void FillStockLocatieKeuze();
    void FillProductkeuze();
    void FillSoortkeuze();
    void FillDetailKeuze();
    void FillSpecificatieKeuze();

    void FillArtikelFields();
    void ClearArtikelFields();
    void LockArtikelFields(bool _lock);
    void ClearLevFields();
    void ClearLevZoekFields();
    void LockLevFields(bool _lock);
    void LockLevZoekFields(bool _lock);
    void LockAllFields(bool _lock);

    bool AdjustSamenstelling(QString _code);

    void ReadFields();
    void FillFields();
    void FillBevatTable();

    void MeldGetalError();

};

#endif // LOTNUMMERS_H
