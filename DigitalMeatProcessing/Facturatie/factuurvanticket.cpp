#include "factuurvanticket.h"
#include "ui_factuurvanticket.h"

#include "../Weegschaal/ticket.h"
#include "../Weegschaal/ticketline.h"
#include "../Weegschaal/tickerow.h"

#include <QSqlRecord>
#include <QMessageBox>
#include <QSpacerItem>
#include <QGridLayout>

FactuurVanTicket::FactuurVanTicket(int _FactuurID, int _KlantID, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::FactuurVanTicket)
{
    ui->setupUi(this);

    FactuurID = _FactuurID;
    TicketID = 0;
    KlantID = _KlantID;

    TeFacturerenModel = new QSqlQueryModel();
    Ticket::getTeFactureren(TeFacturerenModel);
    TeFacturerenModel->setHeaderData(1,Qt::Horizontal, tr("Tijdstip"));
    TeFacturerenModel->setHeaderData(2,Qt::Horizontal, tr("Ticketnummer"));
    TeFacturerenModel->setHeaderData(3,Qt::Horizontal, tr("Verkoper"));
    TeFacturerenModel->setHeaderData(4,Qt::Horizontal, tr("Bedrag"));
    ui->tvTeFactureren->setModel(TeFacturerenModel);
    ui->tvTeFactureren->setColumnWidth(0,80);
    ui->tvTeFactureren->setColumnWidth(1,150);
    ui->tvTeFactureren->setColumnWidth(2,200);
    ui->tvTeFactureren->setColumnWidth(3,100);
    //ui->tvTeFactureren->hideColumn(0);

    ui->tvTeFactureren->setAlternatingRowColors(true);
}

FactuurVanTicket::~FactuurVanTicket()
{
    delete ui;
    delete TeFacturerenModel;
}

void FactuurVanTicket::on_tvTeFactureren_clicked(const QModelIndex &index)
{
    ui->tvTeFactureren->selectRow(index.row());
    int _ID = ui->tvTeFactureren->model()->data( ui->tvTeFactureren->model()->index(ui->tvTeFactureren->currentIndex().row(), 0 )).toInt();
    TicketID = _ID;
    FillTicket(_ID);
}

void FactuurVanTicket::FillTicket(int _id)
{
    Ticket* ws = new Ticket(_id);
    ui->lbTicketNr->setText( QString("Ticket nummer: %1").arg(ws->getVolgnummer()));
    ui->lstwTicket->clear();

    QVariant nr;
    TickeRow* tr;
    QListWidgetItem *item;

    QSqlQueryModel* mod = new QSqlQueryModel();
    TicketLine::getLinesByTicketID(ws->getTicket_ID(), mod);

    double totaal = 0;


    for(int i = 0; i < mod->rowCount() ; i++)
    {
        tr = new TickeRow();
        tr->setOmschrijving(mod->record(i).value("art_omschrijving").toString());
        tr->setHoeveelheid(QString("%1 %2").arg(mod->record(i).value("hoeveelheid").toDouble(), 0, 'f', 3).
                           arg(mod->record(i).value("eenheid").toString()));
        tr->setPrijs(QString("%1 €").arg(mod->record(i).value("prijs_incl_btw").toDouble(), 0,'f',2));
        totaal += mod->record(i).value("prijs_incl_btw").toDouble();
        item = new QListWidgetItem();
        item->setSizeHint(QSize(0,65));
        //item->setStatusTip("test1");
        nr = mod->record(i).value("ticket_line_id").toInt();
        item->setData(Qt::UserRole, nr);
        ui->lstwTicket->insertItem(0,item);
        ui->lstwTicket->setItemWidget(item,tr);
    }
    ui->lbToaal->setText(QString("%1 €").arg(totaal, 0,'f',2));
    //ui->grboxBestelling->setTitle(QString("Bestelling nr.: %1").arg(ws->Bestelling));
    //ui->tbBestelling->setText(QString("%1").arg(ws->Bestelling));

}

void FactuurVanTicket::on_btnAnuleren_clicked()
{
    this->close();
}

void FactuurVanTicket::on_btnOvernemen_clicked()
{
    if (TicketID == 0)
    {
        QMessageBox *msgBox = new QMessageBox(this);
        msgBox->setText("Ticketkeuze - Fout");
        msgBox->setWindowModality(Qt::WindowModal);
        msgBox->setInformativeText("U Moet een ticket aanduiden");
        msgBox->setStandardButtons(QMessageBox::Ok);
        QSpacerItem *hs = new QSpacerItem(400, 0, QSizePolicy::Minimum, QSizePolicy::Expanding);
        QGridLayout *gl = (QGridLayout*)msgBox->layout();
        gl->addItem(hs, gl->rowCount(), 0, 1, gl->columnCount());
        msgBox->exec();
    }
    else
    {
        Ticket::TicketToFactuur(FactuurID, TicketID, KlantID);
        this->close();
    }
}
