#include "dlgsettings.h"
#include "ui_dlgsettings.h"
#include "Relaties/relatiefiche.h"
#include "Relaties/relatiesettings.h"

#include <limits>

#include <QApplication>
#include <QSettings>
#include <QLocale>
#include <QtSerialPort/QSerialPort>
#include <QtSerialPort/QSerialPortInfo>
#include <QPrinterInfo>
#include <QFileDialog>


dlgSettings::dlgSettings(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::dlgSettings)
{
    //QLocale::setDefault(QLocale(QLocale::English, QLocale::UnitedStates));
    //QLocale::setDefault(QLocale::Belgium );
    ui->setupUi(this);

    m_sSettingsFile = QApplication::applicationDirPath() + "/appSettings.ini";
    QSettings settings(m_sSettingsFile, QSettings::NativeFormat);

    ui->tbHostname->setText(settings.value("HostName", "N/A").toString());
    ui->tbDatabaseName->setText(settings.value("DatabaseName", "N/A").toString());
    ui->tbUserName->setText(settings.value("UserName", "N/A").toString());
    ui->tbPassword->setText(settings.value("Password","N/A").toString());

    ui->tbFlag_1->setText(settings.value("Relatie/Flag_1", "").toString());
    ui->tbFlag_2->setText(settings.value("Relatie/Flag_2", "").toString());
    ui->tbFlag_3->setText(settings.value("Relatie/Flag_3", "").toString());
    ui->tbFlag_4->setText(settings.value("Relatie/Flag_4", "").toString());
    ui->tbFlag_5->setText(settings.value("Relatie/Flag_5", "").toString());
    ui->tbFlag_6->setText(settings.value("Relatie/Flag_6", "").toString());
    ui->tbFlag_7->setText(settings.value("Relatie/Flag_7", "").toString());
    ui->tbFlag_8->setText(settings.value("Relatie/Flag_8", "").toString());
    ui->tbFlag_9->setText(settings.value("Relatie/Flag_9", "").toString());
    ui->tbFlag_10->setText(settings.value("Relatie/Flag_10", "").toString());

    ui->tbVrijTekst1->setText(settings.value("Relatie/VrijTekst_1", "").toString());
    ui->tbVrijTekst2->setText(settings.value("Relatie/VrijTekst_2", "").toString());
    ui->tbVrijTekst3->setText(settings.value("Relatie/VrijTekst_3", "").toString());
    ui->tbVrijTekst4->setText(settings.value("Relatie/VrijTekst_4", "").toString());
    ui->tbVrijTekst5->setText(settings.value("Relatie/VrijTekst_5", "").toString());

    ui->tbVrijNum1->setText(settings.value("Relatie/VrijNum_1", "").toString());
    ui->tbVrijNum2->setText(settings.value("Relatie/VrijNum_2", "").toString());
    ui->tbVrijNum3->setText(settings.value("Relatie/VrijNum_3", "").toString());
    ui->tbVrijNum4->setText(settings.value("Relatie/VrijNum_4", "").toString());
    ui->tbVrijNum5->setText(settings.value("Relatie/VrijNum_5", "").toString());

    ui->tbID_1->setText(settings.value("Relatie/ID_1", "").toString());
    ui->tbID_2->setText(settings.value("Relatie/ID_2", "").toString());
    ui->tbID_3->setText(settings.value("Relatie/ID_3", "").toString());
    ui->tbID_4->setText(settings.value("Relatie/ID_4", "").toString());
    ui->tbID_5->setText(settings.value("Relatie/ID_5", "").toString());

    FillSerialPorts();
    ui->cbxLotnrPr1->setCurrentText(settings.value("Printers/LotnrPr1", "").toString());
    ui->cbxWeegschaal->setCurrentText(settings.value("Weegschaal/Winkel", "").toString());

    FillPrinters();
    ui->cbxLabelPrinterWinkel->setCurrentText(settings.value("Printers/LabelPrinterWinkel1", "").toString());
    ui->cbxTicketPrinter->setCurrentText(settings.value("Printers/TicketPrinter1", "").toString());

    ui->tbKassaAfbeeldingen->setText(settings.value("Diverse/KassaAfbeeldingenMap").toString());
    ui->sbNummerKassa->setValue(settings.value("Diverse/NummerKassa").toInt());
}

void dlgSettings::FillSerialPorts()
{
    ui->cbxLotnrPr1->clear();
    ui->cbxWeegschaal->clear();
    QList<QSerialPortInfo> spiList = QSerialPortInfo::availablePorts();
    foreach (const QSerialPortInfo &spi, spiList)
    {
        QString snaam = spi.portName();
        ui->cbxLotnrPr1->addItem(snaam);
        ui->cbxWeegschaal->addItem(snaam);
    }
}

void dlgSettings ::FillPrinters()
{
    QStringList printers = QPrinterInfo::availablePrinterNames();
    ui->cbxLabelPrinterWinkel->clear();
    ui->cbxTicketPrinter->clear();
    foreach (const QString naam, printers)
    {
        ui->cbxLabelPrinterWinkel->addItem(naam);
        ui->cbxTicketPrinter->addItem(naam);
    }
}

dlgSettings::~dlgSettings()
{
    delete ui;
    //delete fiche;
    //delete NUM_validator;
}


void dlgSettings::on_dlgSettings_accepted()
{
    m_sSettingsFile = QApplication::applicationDirPath() + "/appSettings.ini";
    QSettings settings(m_sSettingsFile, QSettings::NativeFormat);

    settings.setValue("HostName", ui->tbHostname->text());
    settings.setValue("DatabaseName", ui->tbDatabaseName->text());
    settings.setValue("UserName", ui->tbUserName->text());
    settings.setValue("Password", ui->tbPassword->text());

    settings.setValue("Relatie/Flag_1", ui->tbFlag_1->text());
    settings.setValue("Relatie/Flag_2", ui->tbFlag_2->text());
    settings.setValue("Relatie/Flag_3", ui->tbFlag_3->text());
    settings.setValue("Relatie/Flag_4", ui->tbFlag_4->text());
    settings.setValue("Relatie/Flag_5", ui->tbFlag_5->text());
    settings.setValue("Relatie/Flag_6", ui->tbFlag_6->text());
    settings.setValue("Relatie/Flag_7", ui->tbFlag_7->text());
    settings.setValue("Relatie/Flag_8", ui->tbFlag_8->text());
    settings.setValue("Relatie/Flag_9", ui->tbFlag_9->text());
    settings.setValue("Relatie/Flag_10", ui->tbFlag_10->text());

    settings.setValue("Relatie/VrijTekst_1", ui->tbVrijTekst1->text());
    settings.setValue("Relatie/VrijTekst_2", ui->tbVrijTekst2->text());
    settings.setValue("Relatie/VrijTekst_3", ui->tbVrijTekst3->text());
    settings.setValue("Relatie/VrijTekst_4", ui->tbVrijTekst4->text());
    settings.setValue("Relatie/VrijTekst_5", ui->tbVrijTekst5->text());

    settings.setValue("Relatie/VrijNum_1", ui->tbVrijNum1->text());
    settings.setValue("Relatie/VrijNum_2", ui->tbVrijNum2->text());
    settings.setValue("Relatie/VrijNum_3", ui->tbVrijNum3->text());
    settings.setValue("Relatie/VrijNum_4", ui->tbVrijNum4->text());
    settings.setValue("Relatie/VrijNum_5", ui->tbVrijNum5->text());

    settings.setValue("Relatie/ID_1", ui->tbID_1->text());
    settings.setValue("Relatie/ID_2", ui->tbID_2->text());
    settings.setValue("Relatie/ID_3", ui->tbID_3->text());
    settings.setValue("Relatie/ID_4", ui->tbID_4->text());
    settings.setValue("Relatie/ID_5", ui->tbID_5->text());
    settings.setValue("Printers/LotnrPr1", ui->cbxLotnrPr1->currentText());
    settings.setValue("Weegschaal/Winkel", ui->cbxWeegschaal->currentText());
    settings.setValue("Printers/LabelPrinterWinkel1", ui->cbxLabelPrinterWinkel->currentText());
    settings.setValue("Printers/TicketPrinter1", ui->cbxTicketPrinter->currentText());

    settings.setValue("Diverse/KassaAfbeeldingenMap", ui->tbKassaAfbeeldingen->text());
    settings.setValue("Diverse/NummerKassa", QString::number(ui->sbNummerKassa->value()));
}

void dlgSettings::on_btnDefaultRelaties_clicked()
{
    RelatieFiche* fiche = new RelatieFiche(RelatieFiche::OpenAsSettings, 1);
    //fiche->setWindowFlags(Qt::WindowStaysOnTopHint);
    fiche->setWindowModality(Qt::ApplicationModal);
    fiche->show();
}


void dlgSettings::on_btnKassaAfbeeldingen_clicked()
{
    QString MapName = QFileDialog::getExistingDirectory();
    ui->tbKassaAfbeeldingen->setText(MapName);
}
