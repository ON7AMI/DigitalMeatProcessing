#ifndef LEVERINGENFICHE_H
#define LEVERINGENFICHE_H

#include <QDialog>

#include "Bestellingen/leveringenheader.h"
#include "Relaties/relaties.h"

namespace Ui {
class LeveringenFiche;
}

class LeveringenFiche : public QDialog
{
    Q_OBJECT

public:
    explicit LeveringenFiche(int _id, QWidget *parent = 0);
    ~LeveringenFiche();

private slots:
    void on_btnWis_Lev_clicked();

    void on_btnZoek_Lev_clicked();

    void on_btnOpslaan_clicked();

    void on_tvRegels_doubleClicked(const QModelIndex &index);

    void on_btnEditLine_clicked();

    void on_btnRegelToevoegen_clicked();

private:
    Ui::LeveringenFiche *ui;

    LeveringenHeader* lh;
    Relaties* rel;
    int CurrentRel;

    void FillFiche();
    void FillRegels();
    void ClearRelZoekFields();
    void ClearFiche();
    void SafeHeader();

};

#endif // LEVERINGENFICHE_H
