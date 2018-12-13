#ifndef FACTUURFICHE_H
#define FACTUURFICHE_H

#include <QDialog>

#include "Relaties/relaties.h"
#include "factuurheader.h"
#include "factuurline.h"

namespace Ui {
class FactuurFiche;
}

class FactuurFiche : public QDialog
{
    Q_OBJECT

public:
    explicit FactuurFiche(int _id, QWidget *parent = 0);
    ~FactuurFiche();

private slots:
    void on_btnZoek_Lev_clicked();
    void on_btnWis_Lev_clicked();
    void on_btnRegelToevoegen_clicked();
    void on_btnOpslaan_clicked();
    void on_btnPrinten_clicked();
    void on_btnEditLine_clicked();
    void on_tvRegels_doubleClicked(const QModelIndex &index);
    void on_btnAddTicket_clicked();

private:
    Ui::FactuurFiche *ui;

    int CurrentRel;

    Relaties* rel;
    FactuurHeader* fh;


    void ClearRelZoekFields();
    void FillRegels();

};

#endif // FACTUURFICHE_H
