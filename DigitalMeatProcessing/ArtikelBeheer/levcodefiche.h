#ifndef LEVCODEFICHE_H
#define LEVCODEFICHE_H

#include "leveranciercodes.h"

#include <QDialog>

namespace Ui {
class LevCodeFiche;
}

class LevCodeFiche : public QDialog
{
    Q_OBJECT

public:
    explicit LevCodeFiche(LeverancierCodes* _lc ,QWidget *parent = 0);
    ~LevCodeFiche();

private slots:
    void on_btnAnnuleren_clicked();

    void on_btnOpslaan_clicked();

private:
    Ui::LevCodeFiche *ui;
    LeverancierCodes* lc;
};

#endif // LEVCODEFICHE_H
