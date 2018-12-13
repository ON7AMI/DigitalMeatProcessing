#include "talen.h"

Talen::Talen()
{

}

//QSqlTableModel* Talen::getAllTalen(QSqlTableModel* model)
//{
//    CommonObjects::OpenDatabase();
//    model = new QSqlTableModel();
//    model->setTable("common.talen");
//    model->select();
//    return model;
//}

void Talen::getAllTalen(QSqlTableModel* model)
{
    //CommonObjects::OpenDatabase();
    model->setTable("common.talen");
    model->select();
}
