#ifndef KLANTENSCHERM_H
#define KLANTENSCHERM_H

#include "ticket.h"
#include "ticketline.h"
#include "weegschaal.h"

#include <QDialog>
#include <QTimer>
#include <QDir>
#include <QPropertyAnimation>
#include <QGraphicsOpacityEffect>
#include <QGraphicsEffect>

namespace Ui {
class KlantenScherm;
}

class KlantenScherm : public QDialog
{
    Q_OBJECT

public:
    explicit KlantenScherm(Weegschaal* _ws, QWidget *parent = 0);
    ~KlantenScherm();

private:
    Ui::KlantenScherm *ui;
    Weegschaal* ws;
    int VorigePersWissel;
    int PixTeller;
    int PixSwitch;

    QTimer* DisplayTimer;
    QTimer* PixTimer;

    QDir* PixDir;
    QStringList filelist;

    QGraphicsOpacityEffect *effect1, *effect2;
    QPropertyAnimation* animation1, *animation2;

    void FillTicket();




private slots:
    void SchrijfDisplay();
    void ShowPictures();

};

#endif // KLANTENSCHERM_H
