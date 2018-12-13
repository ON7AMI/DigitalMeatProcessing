#ifndef MY_LBFOTO_H
#define MY_LBFOTO_H

#include <QObject>
#include <QWidget>
#include <QLabel>

class my_lbFoto : public QLabel
{
    Q_OBJECT

public:
    my_lbFoto(QWidget *parent = 0);

    void dragEnterEvent(QDragEnterEvent *event);
    void dropEvent(QDropEvent *event);

};

#endif // MY_LBFOTO_H
