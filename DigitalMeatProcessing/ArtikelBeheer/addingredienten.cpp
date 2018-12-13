#include "addingredienten.h"
#include "ui_addingredienten.h"

#include <QResource>
#include <QMessageBox>
#include <QSpacerItem>
#include <QGridLayout>
#include <QInputDialog>


AddIngredienten::AddIngredienten(int _artID, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddIngredienten)
{
    QResource::registerResource("../Resources/myresource.qrc");
    ui->setupUi(this);

    Artikel_ID = _artID;
    FillTabel();
    FillIngredienten();
    ui->cbxIngredienten->setCurrentIndex(0);
    ui->tbHoeveelheid->setText("0");

    ui->cbxIngredienten->setEnabled(false);
    ui->tbHoeveelheid->setEnabled(false);

    ui->btnEdit->setEnabled(true);
    ui->btnNew->setEnabled(true);
    ui->btnSave->setEnabled(false);
    ui->btnDelete->setEnabled(true);
    ui->btnToevoegen->setEnabled(false);

    this->setWindowTitle("Ingrediënten bewerken");

}

AddIngredienten::~AddIngredienten()
{
    delete ui;
    delete tv_model;
    delete ing_model;
    delete ing;
    delete ing_art;
}


void AddIngredienten::FillTabel()
{
    tv_model = new QSqlQueryModel();
    Ingredient_Artikel::getIngredientenPerArtikel(tv_model, Artikel_ID);
    tv_model->setHeaderData(2, Qt::Horizontal, tr("Omschrijving."));
    tv_model->setHeaderData(3, Qt::Horizontal, tr("Procent"));

    ui->tvIngredienten->setModel(tv_model);

    ui->tvIngredienten->hideColumn(0);
    ui->tvIngredienten->hideColumn(1);

    ui->tvIngredienten->setColumnWidth(2,380);
    ui->tvIngredienten->setColumnWidth(3,140);

    ui->tvIngredienten->setAlternatingRowColors(true);
    if (ui->tvIngredienten->model()->rowCount() > 0)
    {
        ui->tvIngredienten->selectRow(0);
    }
}

void AddIngredienten::FillIngredienten()
{
    ing_model = new QSqlQueryModel();
    Ingredienten::getAllIngredienten(ing_model);
    ui->cbxIngredienten->setModel(ing_model);
    ui->cbxIngredienten->setModelColumn(1);
}

void AddIngredienten::on_btnStop_clicked()
{
    this->close();
}

void AddIngredienten::on_btnNew_clicked()
{
    ing_art = new Ingredient_Artikel();
    ing_art->setArtikel_ID(Artikel_ID);

    ui->tbHoeveelheid->setEnabled(true);
    ui->cbxIngredienten->setEnabled(true);

    ui->btnDelete->setEnabled(false);
    ui->btnEdit->setEnabled(false);
    ui->btnNew->setEnabled(false);
    ui->btnSave->setEnabled(true);
    ui->btnToevoegen->setEnabled(true);

}

void AddIngredienten::on_btnEdit_clicked()
{
    int _ID = ui->tvIngredienten->model()->data( ui->tvIngredienten->model()->index(ui->tvIngredienten->currentIndex().row(), 0)).toInt();
    ing_art = new Ingredient_Artikel(_ID);
    ui->cbxIngredienten->setCurrentIndex((ing_art->getIngredient_ID() == 0 ? 0 :
             ui->cbxIngredienten->model()->match(
             ui->cbxIngredienten->model()->index(0, 0),
             Qt::DisplayRole,
             QVariant::fromValue(ing_art->getIngredient_ID()),
             -1,
             Qt::MatchFixedString)[0].row())
             );
    ui->tbHoeveelheid->setText(QString("%1").arg(ing_art->getHoeveelheid()));
    ui->tbHoeveelheid->setEnabled(true);
    ui->cbxIngredienten->setEnabled(true);

    ui->btnDelete->setEnabled(false);
    ui->btnEdit->setEnabled(false);
    ui->btnNew->setEnabled(false);
    ui->btnSave->setEnabled(true);
    ui->btnToevoegen->setEnabled(true);
}

void AddIngredienten::on_btnSave_clicked()
{
    ing_art->setArtikel_ID( Artikel_ID );
    ing_art->setIngredient_ID(ui->cbxIngredienten->model()->data( ui->cbxIngredienten->model()->
                              index(ui->cbxIngredienten->currentIndex(), 0 )).toInt());
    ing_art->setHoeveelheid(ui->tbHoeveelheid->text().toDouble());
    ing_art->save();
    FillTabel();
    FillIngredienten();
    ui->cbxIngredienten->setCurrentIndex(0);
    ui->tbHoeveelheid->setText("0");

    ui->cbxIngredienten->setEnabled(false);
    ui->tbHoeveelheid->setEnabled(false);

    ui->btnEdit->setEnabled(true);
    ui->btnNew->setEnabled(true);
    ui->btnSave->setEnabled(false);
    ui->btnDelete->setEnabled(true);
    ui->btnToevoegen->setEnabled(false);

}

void AddIngredienten::on_btnToevoegen_clicked()
{
    bool ok;
    QString text = QInputDialog::getText(this, tr("Nieuw ingredient"),
                                         tr("Naam nieuw ingredient:"),
                                         QLineEdit::Normal,
                                         "",
                                         &ok);
    if (ok && !text.isEmpty())
    {
        ing = new Ingredienten();
        ing->setOmschrijving(text);
        ing->save();
        FillIngredienten();
        ui->cbxIngredienten->setCurrentText(text);
    }
}

void AddIngredienten::on_btnDelete_clicked()
{
    int _ID = ui->tvIngredienten->model()->data( ui->tvIngredienten->model()->index(ui->tvIngredienten->currentIndex().row(), 0)).toInt();
    Ingredient_Artikel::deleteIngredientenPerArtikel(_ID);
    FillTabel();
}

void AddIngredienten::on_tbHoeveelheid_editingFinished()
{
    double klad;
    bool ok;
    klad = ui->tbHoeveelheid->text().toDouble(&ok);
    if ( !ok )
    {
        QMessageBox msgBox;
        msgBox.setText("<strong>Foutieve ingave Prijs!</strong>");
        msgBox.setInformativeText("U mag hier enkel een geldige hoeveelheid ingeven.\n Enkel getallen en het decimaal teken.");
        msgBox.setStandardButtons(QMessageBox::Cancel);
        msgBox.setDefaultButton(QMessageBox::Cancel);
        msgBox.setIcon(QMessageBox::Critical);
        msgBox.setWindowTitle("Opgepast !");
        QSpacerItem *hs = new QSpacerItem(400, 0, QSizePolicy::Minimum, QSizePolicy::Expanding);
        QGridLayout *gl = (QGridLayout*)msgBox.layout();
        gl->addItem(hs, gl->rowCount(), 0, 1, gl->columnCount());
        msgBox.exec();

        ui->tbHoeveelheid->setText("0");
        ui->tbHoeveelheid->setFocus();
    }
}
