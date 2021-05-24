#ifndef CALCULATOR_H
#define CALCULATOR_H

#include <QMainWindow>
#include <QMessageBox>

QT_BEGIN_NAMESPACE
namespace Ui { class Calculator; }
QT_END_NAMESPACE

class Calculator : public QMainWindow
{
    Q_OBJECT

public:
    Calculator(QWidget *parent = nullptr);
    ~Calculator();

    double ausdruck(QChar& zeichen);
    double summand(QChar& zeichen);
    double faktor(QChar& zeichen);
    double zahl(QChar& zeichen);

    void get(QChar& zeichen);
    bool endOfLineCheck();

private slots:
    void berechnen();
    void reset();
    void deleteCharakter();

    void null();
    void eins();
    void zwei();
    void drei();
    void vier();
    void fuenf();
    void sechs();
    void sieben();
    void acht();
    void neun();
    void klammarAuf();
    void klammarZu();
    void komma();

    void multiplikation();
    void subtraktion();
    void addtion();
    void division();

private:
    Ui :: Calculator*ui;
};
#endif // MAINWINDOW_H
