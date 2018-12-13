#ifndef ADDALLERGENEN_H
#define ADDALLERGENEN_H

#include "allergenen.h"
#include <QDialog>
#include <QSqlQueryModel>

namespace Ui {
class AddAllergenen;
}

class AddAllergenen : public QDialog
{
    Q_OBJECT

public:
    explicit AddAllergenen(QWidget *parent = 0);
    ~AddAllergenen();

private slots:
    void on_btnLaadPicture_clicked();
    void on_btnStop_clicked();
    void on_btnNieuw_clicked();
    void on_btnOpslaan_clicked();
    void on_btnBewerk_clicked();

private:
    Ui::AddAllergenen *ui;
    Allergenen *al;

    QSqlQueryModel *Allergeen_Model;
};

#endif // ADDALLERGENEN_H
#ifndef IMAGEDELEGATE_H
#define IMAGEDELEGATE_H

#include <QPainter>
#include <QObject>
#include <QItemDelegate>
#include <QTableView>


class Al_ImageDelegate : public QItemDelegate
{
public:
    Al_ImageDelegate(QObject * parent = 0);

    void paint(QPainter * painter, const QStyleOptionViewItem & option, const QModelIndex & index) const;

};

#endif // IMAGEDELEGATE_H
