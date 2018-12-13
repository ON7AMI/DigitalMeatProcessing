#include "geslachten.h"



Geslachten::Geslachten()
{

}

void Geslachten::getAllGeslachten(QStandardItemModel* model)
{
    model->setColumnCount(2);
    model->setRowCount(3);
    model->setHorizontalHeaderItem(0, new QStandardItem("geslacht_code"));
    model->setHorizontalHeaderItem(1, new QStandardItem("benaming"));

    model->setItem(0, 0, new QStandardItem("M")); model->setItem(0, 1, new QStandardItem("Man"));
    model->setItem(1, 0, new QStandardItem("V")); model->setItem(1, 1, new QStandardItem("Vrouw"));
    model->setItem(2, 0, new QStandardItem("O")); model->setItem(2, 1, new QStandardItem("Onbekend"));

}
