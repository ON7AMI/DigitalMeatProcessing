#ifndef TICKEROW_H
#define TICKEROW_H

#include <QWidget>
#include <QString>

namespace Ui {
class TickeRow;
}

class TickeRow : public QWidget
{
    Q_OBJECT

public:
    explicit TickeRow(QWidget *parent = 0);
    ~TickeRow();
    void setOmschrijving(QString _omschr);
    void setHoeveelheid(QString _hoeveel);
    void setPrijs(QString _prijs);
    QString getOmscrijving();

private:
    Ui::TickeRow *ui;
};

#endif // TICKEROW_H
