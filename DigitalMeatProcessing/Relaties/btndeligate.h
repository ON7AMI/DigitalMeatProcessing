#ifndef BTNDELIGATE_H
#define BTNDELIGATE_H

#include <QObject>
#include <QWidget>
#include <QtGui>
#include <QItemDelegate>
#include <QTableView>
#include <QPushButton>

class btnDeligate  : public QItemDelegate
{
public:
    btnDeligate(QObject *parent = 0);
    void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const;

private:

};

#endif // BTNDELIGATE_H
