#include "calculator.h"
#include "ui_calculator.h"
#include <cmath>

Calculator :: Calculator(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui :: Calculator)
{
    ui->setupUi(this);
    connect(ui->Gleichheit_Button, &QPushButton::clicked, this, &Calculator :: berechnen);
    connect(ui->AC_Button, &QPushButton::clicked, this, &Calculator :: reset);

    connect(ui->Null, &QPushButton::clicked, this, &Calculator :: null);
    connect(ui->EINS, &QPushButton::clicked, this, &Calculator :: eins);
    connect(ui->ZWEI, &QPushButton::clicked, this, &Calculator :: zwei);
    connect(ui->DREI, &QPushButton::clicked, this, &Calculator :: drei);
    connect(ui->VIER, &QPushButton::clicked, this, &Calculator :: vier);
    connect(ui->FUENF, &QPushButton::clicked, this, &Calculator :: fuenf);
    connect(ui->SECHS, &QPushButton::clicked, this, &Calculator :: sechs);
    connect(ui->SIEBEN, &QPushButton::clicked, this, &Calculator :: sieben);
    connect(ui->ACHT, &QPushButton::clicked, this, &Calculator :: acht);
    connect(ui->NEUN, &QPushButton::clicked, this, &Calculator :: neun);
    connect(ui->KlammarAuf_Button, &QPushButton::clicked, this, &Calculator :: klammarAuf);
    connect(ui->KlammarZu_Button, &QPushButton::clicked, this, &Calculator :: klammarZu);
    connect(ui->Kommar_Button, &QPushButton::clicked, this, &Calculator :: komma);
    connect(ui->C_Button, &QPushButton::clicked, this, &Calculator :: deleteCharakter);

    connect(ui->Multiplikation_Button, &QPushButton::clicked, this, &Calculator :: multiplikation);
    connect(ui->Substraktion_Button, &QPushButton::clicked, this, &Calculator :: subtraktion);
    connect(ui->Addition_Button, &QPushButton::clicked, this, &Calculator :: addtion);
    connect(ui->Division_Button, &QPushButton::clicked, this, &Calculator :: division);
}

Calculator :: ~Calculator()
{
    delete ui;
}

void Calculator :: berechnen()
{
    ui->Ausdruck->setCursorPosition(0);

    QChar zeichen;
    get(zeichen);

    try{
        ui->Ergebnis->setText(QString :: number(ausdruck(zeichen)));
    }
    catch (const char* message) {
        QMessageBox meldung;
        meldung.setText(message);
        meldung.exec();
        ui->Ausdruck->clear();
        ui->Ergebnis->clear();
    }
}

void Calculator :: get(QChar& zeichen)
{
    int curentCursor = ui->Ausdruck->cursorPosition();

    if (!endOfLineCheck()) {
        ui->Ausdruck->setSelection(curentCursor, 1);
        zeichen =  ui->Ausdruck->selectedText().back();
    }
    else
        zeichen = 'c';
}

bool Calculator :: endOfLineCheck()
{
    QString ausdruck = ui->Ausdruck->text();
    int size = ausdruck.size();
    return ui->Ausdruck->cursorPosition() == size ? 1 : 0;
}

void Calculator :: reset()
{
    ui->Ausdruck->setText("");
    ui->Ergebnis->setText("");
    ui->Ausdruck->setCursorPosition(0);
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
                throw "Division durch 0";
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
            throw "Es fehlt schließende Klammar";
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

void Calculator::null()
{
    QString text = ui->Ausdruck->text();
    text += "0";
    ui->Ausdruck->setText(text);
}

void Calculator::eins()
{
    QString text = ui->Ausdruck->text();
    text += "1";
    ui->Ausdruck->setText(text);
}

void Calculator::zwei()
{
    QString text = ui->Ausdruck->text();
    text += "2";
    ui->Ausdruck->setText(text);
}

void Calculator::drei()
{
    QString text = ui->Ausdruck->text();
    text += "3";
    ui->Ausdruck->setText(text);
}

void Calculator::vier()
{
    QString text = ui->Ausdruck->text();
    text += "4";
    ui->Ausdruck->setText(text);
}

void Calculator::fuenf()
{
    QString text = ui->Ausdruck->text();
    text += "5";
    ui->Ausdruck->setText(text);
}

void Calculator::sechs()
{
    QString text = ui->Ausdruck->text();
    text += "6";
    ui->Ausdruck->setText(text);
}

void Calculator::sieben()
{
    QString text = ui->Ausdruck->text();
    text += "7";
    ui->Ausdruck->setText(text);
}

void Calculator::acht()
{
    QString text = ui->Ausdruck->text();
    text += "8";
    ui->Ausdruck->setText(text);
}

void Calculator::neun()
{
    QString text = ui->Ausdruck->text();
    text += "9";
    ui->Ausdruck->setText(text);
}

void Calculator::klammarAuf()
{
    QString text = ui->Ausdruck->text();
    text += "(";
    ui->Ausdruck->setText(text);
}

void Calculator::klammarZu()
{
    QString text = ui->Ausdruck->text();
    text += ")";
    ui->Ausdruck->setText(text);
}

void Calculator::komma()
{
    QString text = ui->Ausdruck->text();
    text += ".";
    ui->Ausdruck->setText(text);
}

void Calculator::multiplikation()
{
    QString text = ui->Ausdruck->text();
    text += "*";
    ui->Ausdruck->setText(text);
}

void Calculator::subtraktion()
{
    QString text = ui->Ausdruck->text();
    text += "-";
    ui->Ausdruck->setText(text);
}

void Calculator::addtion()
{
    QString text = ui->Ausdruck->text();
    text += "+";
    ui->Ausdruck->setText(text);
}

void Calculator::division()
{
    QString text = ui->Ausdruck->text();
    text += "/";
    ui->Ausdruck->setText(text);
}

void Calculator::deleteCharakter()
{
    QString text = ui->Ausdruck->text();
    text.remove(text.length() - 1, text.length());
    ui->Ausdruck->setText(text);
}
