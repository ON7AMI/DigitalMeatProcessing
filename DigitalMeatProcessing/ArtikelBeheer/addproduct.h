#ifndef ADDPRODUCT_H
#define ADDPRODUCT_H

#include "producten.h"
#include <QDialog>
#include <QSqlQueryModel>

namespace Ui {
class AddProduct;
}

class AddProduct : public QDialog
{
    Q_OBJECT

public:
    explicit AddProduct(QWidget *parent = 0);
    ~AddProduct();

private slots:
    void on_btnLaadPicture_clicked();
    void on_btnStop_clicked();
    void on_btnNieuw_clicked();
    void on_btnOpslaan_clicked();
    void on_btnBewerk_clicked();

private:
    Ui::AddProduct *ui;
    Producten *prd;

    QSqlQueryModel *Product_Model;


};

#endif // ADDPRODUCT_H

#ifndef IMAGEDELEGATE_H
#define IMAGEDELEGATE_H

#include <QPainter>
#include <QObject>
#include <QItemDelegate>
#include <QTableView>


class ImageDelegate : public QItemDelegate
{
public:
    ImageDelegate(QObject * parent = 0);

    void paint(QPainter * painter, const QStyleOptionViewItem & option, const QModelIndex & index) const;

};

#endif // IMAGEDELEGATE_H
