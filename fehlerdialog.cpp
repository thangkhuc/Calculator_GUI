#include "fehlerdialog.h"
#include "ui_fehlerdialog.h"

FehlerDialog::FehlerDialog(QString inhalt, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::FehlerDialog)
{
    ui->setupUi(this);
    ui->Fehlerinhalt->setText(inhalt);
}

FehlerDialog::~FehlerDialog()
{
    delete ui;
}
