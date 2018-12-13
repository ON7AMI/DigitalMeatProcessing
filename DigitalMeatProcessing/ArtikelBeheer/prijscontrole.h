#ifndef PRIJSCONTROLE_H
#define PRIJSCONTROLE_H

#include <QDialog>

namespace Ui {
class PrijsControle;
}

class PrijsControle : public QDialog
{
    Q_OBJECT

public:
    explicit PrijsControle(QWidget *parent = 0);
    ~PrijsControle();

private:
    Ui::PrijsControle *ui;
};

#endif // PRIJSCONTROLE_H
