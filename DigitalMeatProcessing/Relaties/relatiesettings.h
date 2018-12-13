#ifndef RELATIESETTINGS_H
#define RELATIESETTINGS_H

#include <QWidget>



namespace Ui {
class RelatieSettings;
}

class RelatieSettings : public QWidget
{
    Q_OBJECT

public:
    explicit RelatieSettings(QWidget *parent = 0);
    ~RelatieSettings();

private:
    Ui::RelatieSettings *ui;
};

#endif // RELATIESETTINGS_H
