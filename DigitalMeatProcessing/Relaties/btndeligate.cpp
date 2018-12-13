#include "btndeligate.h"

#include <QModelIndex>
#include <QPushButton>
#include <QTableView>

btnDeligate::btnDeligate(QObject *parent)
    : QItemDelegate(parent)
{

}

void btnDeligate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
 {
     if (index.column() == 0)
     {
             QPushButton* btn = new QPushButton();
             btn->setGeometry(option.rect);
             btn->setText(index.data().toString());
             QPixmap map = QPixmap::grabWidget(btn);
             painter->drawPixmap(option.rect.x(),option.rect.y(),map);
     }
     else
     {
         QItemDelegate::paint(painter, option, index);
     }
 }

