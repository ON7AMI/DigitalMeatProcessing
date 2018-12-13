#ifndef SELECTALLERGENEN_H
#define SELECTALLERGENEN_H

#include <QDialog>
#include <QStandardItemModel>

namespace Ui {
class SelectAllergenen;
}

class SelectAllergenen : public QDialog
{
    Q_OBJECT

public:
    explicit SelectAllergenen(int _id,  QWidget *parent = 0);

    ~SelectAllergenen();

private slots:
    void on_btnStop_clicked();

    void on_btnOpslaan_clicked();

    void on_btnBewerk_clicked();

private:
    Ui::SelectAllergenen *ui;
    QStandardItemModel* tableModel;
    int Artikel_ID;

    void FillTable();
};

#endif // SELECTALLERGENEN_H
