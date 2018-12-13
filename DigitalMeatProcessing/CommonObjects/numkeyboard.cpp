#include "numkeyboard.h"
#include "ui_numkeyboard.h"

#include <QDebug>
#include <QApplication>
#include <QSettings>
#include <QLocale>
#include <QDialog>
#include <QDateTime>
#include <QKeyEvent>

NumKeyboard::NumKeyboard(QObject* _CurObj, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::NumKeyboard)
{
    ui->setupUi(this);
    this->move(0,300);
    CurObj = _CurObj;
}

NumKeyboard::~NumKeyboard()
{
    delete ui;
}

void NumKeyboard::on_btn_Enter_clicked()
{
    QKeyEvent* ev = new QKeyEvent(QEvent::KeyPress, Qt::Key_Tab, Qt::NoModifier);
    qApp->postEvent(CurObj, (QEvent*)ev);
    this->close();
}

void NumKeyboard::on_btn_Home_clicked()
{
    QKeyEvent* ev = new QKeyEvent(QEvent::KeyPress, Qt::Key_Home, Qt::NoModifier);
    qApp->postEvent(CurObj, (QEvent*)ev);
}

void NumKeyboard::on_btn_End_clicked()
{
    QKeyEvent* ev = new QKeyEvent(QEvent::KeyPress, Qt::Key_End, Qt::NoModifier);
    qApp->postEvent(CurObj, (QEvent*)ev);
}

void NumKeyboard::on_btn_Clear_clicked()
{
    QKeyEvent* ev = new QKeyEvent(QEvent::KeyPress, Qt::Key_End, Qt::NoModifier);
    qApp->postEvent(CurObj, (QEvent*)ev);
    ev = new QKeyEvent(QEvent::KeyPress, Qt::Key_Home, Qt::ShiftModifier );
    qApp->postEvent(CurObj, (QEvent*)ev);
    ev = new QKeyEvent(QEvent::KeyPress, Qt::Key_Delete, Qt::NoModifier);
    qApp->postEvent(CurObj, (QEvent*)ev);

}

void NumKeyboard::on_btn_BS_clicked()
{
    QKeyEvent* ev = new QKeyEvent(QEvent::KeyPress, Qt::Key_Backspace, Qt::NoModifier);
    qApp->postEvent(CurObj, (QEvent*)ev);
}

void NumKeyboard::on_btn_0_clicked()
{
    QKeyEvent* ev = new QKeyEvent(QEvent::KeyPress, Qt::Key_0, Qt::NoModifier,"0",false,1);
    qApp->postEvent(CurObj, (QEvent*)ev);
}

void NumKeyboard::on_btn_1_clicked()
{
    QKeyEvent* ev = new QKeyEvent(QEvent::KeyPress, Qt::Key_1, Qt::NoModifier,"1",false,1);
    qApp->postEvent(CurObj, (QEvent*)ev);
}

void NumKeyboard::on_btn_2_clicked()
{
    QKeyEvent* ev = new QKeyEvent(QEvent::KeyPress, Qt::Key_2, Qt::NoModifier,"2",false,1);
    qApp->postEvent(CurObj, (QEvent*)ev);
}

void NumKeyboard::on_btn_3_clicked()
{
    QKeyEvent* ev = new QKeyEvent(QEvent::KeyPress, Qt::Key_3, Qt::NoModifier,"3");
    qApp->postEvent(CurObj, (QEvent*)ev);
}

void NumKeyboard::on_btn_4_clicked()
{
    QKeyEvent* ev = new QKeyEvent(QEvent::KeyPress, Qt::Key_4, Qt::NoModifier,"4");
    qApp->postEvent(CurObj, (QEvent*)ev);
}

void NumKeyboard::on_btn_5_clicked()
{
    QKeyEvent* ev = new QKeyEvent(QEvent::KeyPress, Qt::Key_5, Qt::NoModifier,"5");
    qApp->postEvent(CurObj, (QEvent*)ev);
}

void NumKeyboard::on_btn_6_clicked()
{
    QKeyEvent* ev = new QKeyEvent(QEvent::KeyPress, Qt::Key_6, Qt::NoModifier,"6");
    qApp->postEvent(CurObj, (QEvent*)ev);
}

void NumKeyboard::on_btn_7_clicked()
{
    QKeyEvent* ev = new QKeyEvent(QEvent::KeyPress, Qt::Key_7, Qt::NoModifier,"7");
    qApp->postEvent(CurObj, (QEvent*)ev);
}

void NumKeyboard::on_btn_9_clicked()
{
    QKeyEvent* ev = new QKeyEvent(QEvent::KeyPress, Qt::Key_8, Qt::NoModifier,"8");
    qApp->postEvent(CurObj, (QEvent*)ev);
}

void NumKeyboard::on_btn_10_clicked()
{
    QKeyEvent* ev = new QKeyEvent(QEvent::KeyPress, Qt::Key_9, Qt::NoModifier,"9");
    qApp->postEvent(CurObj, (QEvent*)ev);
}

void NumKeyboard::on_btn_C_clicked()
{
    QKeyEvent* ev = new QKeyEvent(QEvent::KeyPress, Qt::Key_T, Qt::NoModifier,"T");
    qApp->postEvent(CurObj, (QEvent*)ev);
}

void NumKeyboard::on_btn_B_clicked()
{
    QKeyEvent* ev = new QKeyEvent(QEvent::KeyPress, Qt::Key_Period, Qt::NoModifier,".");
    qApp->postEvent(CurObj, (QEvent*)ev);
}

void NumKeyboard::on_btn_min_clicked()
{
    QKeyEvent* ev = new QKeyEvent(QEvent::KeyPress, Qt::Key_Minus, Qt::NoModifier,"-");
    qApp->postEvent(CurObj, (QEvent*)ev);
}
