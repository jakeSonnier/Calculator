#include "mainwindow.h"
#include "ui_mainwindow.h"

double calcVal = 0.0;
bool divTrigger = false;
bool multTrigger = false;
bool subTrigger = false;
bool addTrigger = false;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->Display->setText(QString::number(calcVal));
    QPushButton *numButtons[10];
    for (int i = 0; i < 10; i++)
    {
        QString buttonName = "Button" + QString::number(i);
        numButtons[i] = MainWindow::findChild<QPushButton *>(buttonName);
        connect(numButtons[i], SIGNAL(released()), this, SLOT(NumPressed()));
    }

    connect(ui->Add, SIGNAL(released()), this, SLOT(MathButtonPressed()));
    connect(ui->Subtract, SIGNAL(released()), this, SLOT(MathButtonPressed()));
    connect(ui->Multiply, SIGNAL(released()), this, SLOT(MathButtonPressed()));
    connect(ui->Divide, SIGNAL(released()), this, SLOT(MathButtonPressed()));
    connect(ui->Equals, SIGNAL(released()), this, SLOT(EqualButton()));
    connect(ui->ChangeSign, SIGNAL(released()), this, SLOT(ChangeSign()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::NumPressed()
{
    QPushButton *button = (QPushButton *)sender();
    QString buttonVal = button->text();
    QString displayVal = ui->Display->text();
    if (displayVal.toDouble() == 0 || displayVal.toDouble() == 0.0)
    {
        ui->Display->setText(buttonVal);
    }
    else
    {
        QString newVal = displayVal + buttonVal;
        double dblNewVal = newVal.toDouble();
        ui->Display->setText(QString::number(dblNewVal, 'g', 16));
    }
}


void MainWindow::MathButtonPressed()
{
    divTrigger = false;
    multTrigger = false;
    subTrigger = false;
    addTrigger = false;
    QString displayVal = ui->Display->text();
    calcVal = displayVal.toDouble();
    QPushButton *button = (QPushButton *)sender();
    QString buttonVal = button->text();

    //Parsing math buttons
         if (QString::compare(buttonVal, "/", Qt::CaseInsensitive) == 0)
    {
        divTrigger = true;
    }
    else if (QString::compare(buttonVal, "*", Qt::CaseInsensitive) == 0)
    {
        multTrigger = true;
    }
    else if (QString::compare(buttonVal, "-", Qt::CaseInsensitive) == 0)
    {
        subTrigger = true;
    }
    else if (QString::compare(buttonVal, "+", Qt::CaseInsensitive) == 0)
    {
        addTrigger = true;
    }

    ui->Display->setText("");
}

void MainWindow::EqualButton()
{
    double solution = 0.0;
    QString displayVal = ui->Display->text();
    double dblDisplayVal = displayVal.toDouble();
    if (addTrigger || subTrigger || multTrigger || divTrigger)
    {
             if (addTrigger)
        {
            solution = calcVal + dblDisplayVal;
        }
        else if (subTrigger)
        {
            solution = calcVal - dblDisplayVal;
        }
        else if (multTrigger)
        {
            solution = calcVal * dblDisplayVal;
        }
        else if (divTrigger)
        {
            solution = calcVal / dblDisplayVal;
        }
    }

    ui->Display->setText(QString::number(solution));
}

void MainWindow::ChangeSign()
{
    QString displayVal = ui->Display->text();
    QRegExp reg("[-]?[0-9.]*");
    if (reg.exactMatch(displayVal))
    {
        double dblDisplayVal = displayVal.toDouble();
        double dblDisplayValSign = -1 * dblDisplayVal;
        ui->Display->setText(QString::number(dblDisplayVal));
    }
}
































