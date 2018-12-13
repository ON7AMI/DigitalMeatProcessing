#ifndef DLGSETTINGS_H
#define DLGSETTINGS_H

#include <QDialog>
#include <QtCore>

namespace Ui {
class dlgSettings;
}

class dlgSettings : public QDialog
{
    Q_OBJECT

public:
    explicit dlgSettings(QWidget *parent = 0);
    ~dlgSettings();

private slots:
    void on_dlgSettings_accepted();
    void on_btnDefaultRelaties_clicked();


    void on_btnKassaAfbeeldingen_clicked();

private:
    QString m_sSettingsFile;
    Ui::dlgSettings *ui;

    void FillSerialPorts();
    void FillPrinters();
};

#endif // DLGSETTINGS_H
