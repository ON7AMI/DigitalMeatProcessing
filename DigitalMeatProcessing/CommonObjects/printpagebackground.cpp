#include "printpagebackground.h"

#include <QImage>
#include <QPen>

PrintPageBackground::PrintPageBackground()
{

}

void PrintPageBackground::Print(QPrinter* pr, QPainter* painter)
{

    QFont f_bloktit("FreeSans", 50, QFont::Bold);
    QFont f_blok("FreeSans", 25);
    QFont f_blokvet("FreeSans", 40, QFont::Bold);

    QImage pixmap1(":/icons/icons/Logo.png");
    // painter->drawImage(QRect(10 * x_scale, 7, 40 * x_scale, 47 * y_scale),pixmap1);
    painter->drawImage(QRect(20 , 20, 550 , 550 ),pixmap1);

    QPen penText("#663500");
    painter->setPen(penText);

    painter->setFont(f_bloktit);
    painter->drawText(1200, 200, "Hans Mertens");
    painter->setFont(f_blokvet);
    painter->drawText(1200, 280, "Slager-Spekslager");

    painter->setFont(f_blok);


    painter->drawText(120, 2860, "Kauwstraat 28 - 9550 Sint Lievens Esse");
    painter->drawText(870, 2860, "info@deneeuwigenbeenhouwer.be");
    painter->drawText(1570, 2860, "Bank:BE67 7310 4051 8487");
    painter->drawText(120, 2900, "tel: 054 25 44 66");
    painter->drawText(870, 2900, "www.deneeuwigenbeenhouwer.be");
    painter->drawText(1570, 2900, "BTW: BE 0645.608.640");



    QPen pen("#663500");
    pen.setWidth(3);

    painter->setPen(pen);
    painter->drawLine(50, 500, 2020, 500);
    painter->drawLine(50, 2810, 2020, 2810);




}
void PrintPageBackground::PrintFactuur(QPrinter* pr, QPainter* painter)
{

    QFont f_bloktit("FreeSans", 40, QFont::Bold);
    QFont f_blok("FreeSans", 25);
    QFont f_blokvet("FreeSans", 30, QFont::Bold);

    QImage pixmap1(":/icons/icons/Logo.png");
    // painter->drawImage(QRect(10 * x_scale, 7, 40 * x_scale, 47 * y_scale),pixmap1);
    painter->drawImage(QRect(20 , 20, 550 , 550 ),pixmap1);

    QPen penText("#663500");
    painter->setPen(penText);

    painter->setFont(f_bloktit);
    painter->drawText(115, 520, "Hans Mertens");
    painter->setFont(f_blokvet);
    painter->drawText(117, 580, "Slager-Spekslager");

    painter->setFont(f_blok);


    painter->drawText(120, 2860, "Kauwstraat 28 - 9550 Sint Lievens Esse");
    painter->drawText(870, 2860, "info@deneeuwigenbeenhouwer.be");
    painter->drawText(1570, 2860, "Bank:BE67 7310 4051 8487");
    painter->drawText(120, 2900, "tel: 054 25 44 66");
    painter->drawText(870, 2900, "www.deneeuwigenbeenhouwer.be");
    painter->drawText(1570, 2900, "BTW: BE 0645.608.640");



    QPen pen("#663500");
    pen.setWidth(2);

    painter->setPen(pen);
    painter->drawLine(50, 690, 2020, 690);
    painter->drawLine(50, 2810, 2020, 2810);




}
