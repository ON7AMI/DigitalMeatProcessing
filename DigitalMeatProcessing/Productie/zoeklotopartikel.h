#ifndef ZOEKLOTOPARTIKEL_H
#define ZOEKLOTOPARTIKEL_H

#include <QDialog>
#include "lotnummerdata.h"
#include "ArtikelBeheer/artikelen.h"

namespace Ui {
class ZoekLotOpArtikel;
}

class ZoekLotOpArtikel : public QDialog
{
    Q_OBJECT

public:
    explicit ZoekLotOpArtikel(QWidget *parent = 0);
    ~ZoekLotOpArtikel();

    int getLotID();

private slots:
    void on_btnOvernemen_clicked();
    void on_btnAnnuleren_clicked();
    void on_cbxProduct_currentIndexChanged(int index);
    void on_cbxSoort_currentIndexChanged(int index);
    void on_cbxDetail_currentIndexChanged(int index);
    void on_cbxSpecificatie_currentIndexChanged(int index);
    void on_btnZoek_Art_clicked();
    void on_btnWis_Art_clicked();
    void on_tbArtikelnummer_editingFinished();
    void on_tvLotnummers_pressed(const QModelIndex &index);

private:
    Ui::ZoekLotOpArtikel *ui;
    Artikelen* art;
    QSqlQueryModel *prd_model;
    QSqlQueryModel *srt_model;
    QSqlQueryModel *det_model;
    QSqlQueryModel *spec_model;
    QSqlQueryModel *lot_model;

    int CurPrd_ID, CurSrt_ID, CurDet_ID, CurSpec_ID, CurLot_ID, CurrentArt;
    void FillProductkeuze();
    void FillSoortkeuze();
    void FillDetailKeuze();
    void FillSpecificatieKeuze();

    void FillArtikelFields();
    void ClearArtikelFields();
    bool AdjustSamenstelling(QString _code);

};

#endif // ZOEKLOTOPARTIKEL_H
