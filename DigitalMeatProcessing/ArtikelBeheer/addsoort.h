#ifndef ADDSOORT_H
#define ADDSOORT_H

#include "soorten.h"
#include <QDialog>
#include <QSqlQueryModel>

namespace Ui {
class AddSoort;
}

class AddSoort : public QDialog
{
    Q_OBJECT

public:
    explicit AddSoort(QWidget *parent = 0);
    ~AddSoort();

    void setProductID(int _product_id);

private slots:
    void on_btnStop_clicked();
    void on_cbxProduct_currentIndexChanged(int index);
    void on_btnLaadPicture_clicked();
    void on_btnNieuw_clicked();
    void on_btnBewerk_clicked();
    void on_btnOpslaan_clicked();

private:
    Ui::AddSoort *ui;
    int Product_ID;
    Soorten *srt;

    QSqlQueryModel *prd_model;
    QSqlQueryModel *Soort_Model;
};

#endif // ADDSOORT_H

#ifndef SOORTIMAGEDELEGATE_H
#define SOORTIMAGEDELEGATE_H

#include <QPainter>
#include <QObject>
#include <QItemDelegate>
#include <QTableView>


class SoortImageDelegate : public QItemDelegate
{
public:
    SoortImageDelegate(QObject * parent = 0);

    void paint(QPainter * painter, const QStyleOptionViewItem & option, const QModelIndex & index) const;

};

#endif // SOORTIMAGEDELEGATE_H
