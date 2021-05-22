#include "calculator.h"
#include "ui_calculator.h"
#include <cmath>

Calculator :: Calculator(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui :: Calculator)
{
    ui->setupUi(this);
    connect(ui->addiere, &QPushButton::clicked, this, &Calculator :: berechnen);
    connect(ui->reset, &QPushButton::clicked, this, &Calculator :: reset);
    ui->summand1->setText(QString :: number(0.0));
    ui->ergebnis->setText(QString :: number(0.0));
}

Calculator :: ~Calculator()
{
    delete ui;
}

void Calculator :: berechnen()
{
    ui->summand1->setCursorPosition(0);

    //ui->ergebnis->setText(QString :: number(ui->summand1->maxLength()));

    QChar zeichen;
    get(zeichen);
    ui->ergebnis->setText(QString :: number(ausdruck(zeichen)));
}

void Calculator :: get(QChar& zeichen)
{
    int curentCursor = ui->summand1->cursorPosition();

    if (!endOfLineCheck()) {
        ui->summand1->setSelection(curentCursor, 1);
        zeichen =  ui->summand1->selectedText().back();
    }
    else
        zeichen = 'c';
}

bool Calculator :: endOfLineCheck()
{
    QString ausdruck = ui->summand1->text();
    int size = ausdruck.size();
    return ui->summand1->cursorPosition() == size ? 1 : 0;
}

void Calculator :: reset()
{
    ui->summand1->setText("");
    ui->ergebnis->setText("");
    ui->summand1->setCursorPosition(0);
}

double Calculator :: ausdruck(QChar& zeichen)
{
    double result;
    while (zeichen == ' ')
        get(zeichen);

    if (zeichen == "-") {
        get(zeichen);
        result = -summand(zeichen);
    } else {
        if (zeichen == "+")
            get(zeichen);
        result = summand(zeichen);
    }

    while(zeichen == ' ')
        get(zeichen);

    while (zeichen == "+" || zeichen == "-") {
        if (zeichen == "+") {
            get(zeichen);
            result += summand(zeichen);
        }
        else {
            get(zeichen);
            result -= summand(zeichen);
        }
    }
    return result;
}

double Calculator :: summand(QChar& zeichen)
{
    double result = faktor(zeichen);

    while (zeichen == ' ')
        get(zeichen);

    while(zeichen == "*" || zeichen == "/") {
        if (zeichen == "*") {
            get(zeichen);
            result *= faktor(zeichen);
        }
        else {
            get(zeichen);
            long nenner = faktor(zeichen);
            if (nenner == 0) {
                FehlerDialog* fehler = new FehlerDialog("Division durch 0");
                fehler->show();
            }
            else
                result /= nenner;
        }
    }
    return result;
}

double Calculator :: faktor(QChar& zeichen)
{
    double result;

    while (zeichen == ' ')
        get(zeichen);

    if (zeichen == "("){
        get(zeichen);
        result = ausdruck(zeichen);
        if (zeichen != ')') {
            FehlerDialog* fehler = new FehlerDialog("Schliessende Klammar fehlt");
            fehler->show();
        }
        else
            get(zeichen);
    }
    else
        result = zahl(zeichen);

    return result;
}

double Calculator :: zahl(QChar& zeichen)
{
    double result = 0;
    bool nachkomma = false;

    while (zeichen == ' ')
        get(zeichen);

    int i = 1;
    while (zeichen.isDigit()) {
        if (nachkomma == false) {
            result = result * 10 + (double) zeichen.digitValue();
            get(zeichen);
        }
        else {
            result += (double) zeichen.digitValue() / (pow(10, i));
            i++;
            get(zeichen);
        }
        if (zeichen == '.') {
            get(zeichen);
            nachkomma = true;
        }
    }
    return result;
}
