#ifndef FINDRELATIES_H
#define FINDRELATIES_H

#include <QDialog>
#include <QObject>
#include <QtCore>
#include <QtSql>
#include <QSqlDatabase>
#include <QSettings>
#include <QApplication>

namespace Ui {
class FindRelaties;
}

class FindRelaties : public QDialog
{
    Q_OBJECT

public:
    explicit FindRelaties(QString _naam, QString _adres, QString _gemeente, QString _email, QWidget *parent = 0);
    ~FindRelaties();
    int getID();

private slots:
    void on_buttonBox_accepted();

    void on_tvZoeken_clicked(const QModelIndex &index);

private:
    Ui::FindRelaties *ui;
    QSqlQueryModel* myModel;
    int _ID;
};

#endif // FINDRELATIES_H
