#ifndef FEHLERDIALOG_H
#define FEHLERDIALOG_H

#include <QDialog>

namespace Ui {
class FehlerDialog;
}

class FehlerDialog : public QDialog
{
    Q_OBJECT

public:
    explicit FehlerDialog(QString inhalt, QWidget *parent = nullptr);
    ~FehlerDialog();

private:
    Ui::FehlerDialog *ui;
};

#endif // FEHLERDIALOG_H
