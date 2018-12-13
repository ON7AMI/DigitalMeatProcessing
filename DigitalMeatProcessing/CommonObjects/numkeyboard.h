#ifndef NUMKEYBOARD_H
#define NUMKEYBOARD_H

#include <QDialog>
#include <QObject>

namespace Ui {
class NumKeyboard;
}

class NumKeyboard : public QDialog
{
    Q_OBJECT

public:
    explicit NumKeyboard(QObject* CurObj, QWidget *parent = 0);
    ~NumKeyboard();


private slots:
    void on_btn_1_clicked();
    void on_btn_2_clicked();
    void on_btn_0_clicked();
    void on_btn_Enter_clicked();
    void on_btn_Home_clicked();
    void on_btn_End_clicked();
    void on_btn_Clear_clicked();
    void on_btn_BS_clicked();
    void on_btn_3_clicked();
    void on_btn_4_clicked();
    void on_btn_5_clicked();
    void on_btn_6_clicked();
    void on_btn_7_clicked();
    void on_btn_9_clicked();
    void on_btn_10_clicked();
    void on_btn_C_clicked();

    void on_btn_B_clicked();

    void on_btn_min_clicked();

private:
    Ui::NumKeyboard *ui;
    QObject* CurObj;
};

#endif // NUMKEYBOARD_H
