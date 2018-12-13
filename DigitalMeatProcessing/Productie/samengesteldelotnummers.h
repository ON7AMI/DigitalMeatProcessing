#ifndef SAMENGESTELDELOTNUMMERS_H
#define SAMENGESTELDELOTNUMMERS_H

#include <QDialog>

#include "lotnummerdata.h"
#include "lotnummerdbevat.h"
#include "ArtikelBeheer/artikelen.h"


namespace Ui {
class SamengesteldeLotnummers;
}

class SamengesteldeLotnummers : public QDialog
{
    Q_OBJECT

public:
    explicit SamengesteldeLotnummers(int _bevat_id, int _lotID, QWidget *parent = 0);
    ~SamengesteldeLotnummers();

private slots:
    void on_btnOk_clicked();
    void on_btnCancel_clicked();
    void on_tbLotnummer_editingFinished();

    void on_tbBenodigdeHoeveelheid_editingFinished();

private:
    Ui::SamengesteldeLotnummers *ui;
    LotnummerdBevat* bev;
    LotnummerData* lot;
    Artikelen* art;

    void FillFields();
    void MeldGetalError();

};

#endif // SAMENGESTELDELOTNUMMERS_H
