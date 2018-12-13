#ifndef DAGRAPPORT_H
#define DAGRAPPORT_H

#include <QDialog>
#include <QSqlQueryModel>
#include <QDateTime>

namespace Ui {
class Dagrapport;
}

class Dagrapport : public QDialog
{
    Q_OBJECT

public:
    explicit Dagrapport(QWidget *parent = 0);
    ~Dagrapport();

private slots:
    void on_btnStop_clicked();

    void on_btnRefresch_clicked();

    void on_dtpDatum_editingFinished();

    void on_btnPrint_clicked();

    void on_btnFacturatie_clicked();

    void on_pushButton_clicked();

private:
    Ui::Dagrapport *ui;
    QDateTime datum;

    QSqlQueryModel* OmzetPerRubiek_Model;
    QSqlQueryModel* OmzetPerBTW_Model;
    QSqlQueryModel* Kasboek_Model;
    QSqlQueryModel* Uitgaven_Model;

    void FillScreen();
};

#endif // DAGRAPPORT_H
