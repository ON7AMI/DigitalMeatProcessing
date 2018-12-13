#ifndef PRINTPAGEBACKGROUND_H
#define PRINTPAGEBACKGROUND_H

#include <QObject>
#include <QPrinter>
#include <QPainter>

class PrintPageBackground
{
public:
    PrintPageBackground();

public: // statics
    void static Print(QPrinter* pr, QPainter* painter);
    void static PrintFactuur(QPrinter* pr, QPainter* painter);
};

#endif // PRINTPAGEBACKGROUND_H
