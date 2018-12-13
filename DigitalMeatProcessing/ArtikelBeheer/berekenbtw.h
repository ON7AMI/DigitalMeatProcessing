#ifndef BEREKENBTW_H
#define BEREKENBTW_H

#include <QDialog>

namespace Ui {
class BerekenBTW;
}

class BerekenBTW : public QDialog
{
    Q_OBJECT

public:
    explicit BerekenBTW(QWidget *parent = 0);
    ~BerekenBTW();
    double Result;

private slots:
    void on_tbIncl_editingFinished();

    void on_rbtn6_toggled(bool checked);

private:
    Ui::BerekenBTW *ui;
    void calc();
};

#endif // BEREKENBTW_H
