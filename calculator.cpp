#include "calculator.h"
#include "ui_calculator.h"
#include<QIcon>

double calcVal = 0.0;
QString ArchVal = "";
QString LastNum = "";
bool AddOperation = false;
bool SubOperation = false;
bool MultiOperation = false;
bool divOperation = false;
bool DoteStatus = false;

calculator::calculator(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::calculator)
{
    ui->setupUi(this);
    ui->lineEdit->setText(QString::number(calcVal));

    // Will hold references to all the number buttons
    QPushButton *numButtons[10];

    // Cycle through locating the buttons
    for(int i = 0; i < 10; ++i){
        QString butName = "Button" + QString::number(i);

        // Get the buttons by name and add to array
        numButtons[i] = calculator::findChild<QPushButton *>(butName);
        //qDebug()<<numButtons[i];

        // When the button is released call num_pressed()
        connect(numButtons[i], SIGNAL(released()), this, SLOT(NumClick()));
    }
    connect(ui->dot, SIGNAL(released()), this, SLOT(DoteClick()));

    connect(ui->clear, SIGNAL(clicked()), this,SLOT(ClaerDisply()));

    connect(ui->divide, SIGNAL(clicked()), this,SLOT(MathOp()));
    connect(ui->multiply, SIGNAL(clicked()), this,SLOT(MathOp()));
    connect(ui->subtract, SIGNAL(clicked()), this,SLOT(MathOp()));
    connect(ui->add, SIGNAL(clicked()), this,SLOT(MathOp()));

    connect(ui->equal, SIGNAL(clicked()), this,SLOT(EqualClick()));

    connect(ui->Signe, SIGNAL(clicked()), this,SLOT(SingneChange()));
}

calculator::~calculator()
{
    delete ui;
}

void calculator::DoteClick()
{
    QString displayVal = ui->lineEdit->text();
    if(DoteStatus==false)
    {
        ui->lineEdit->setText(displayVal+".");
        DoteStatus = true;
    }


}
void calculator::NumClick()
{
    QPushButton *button = (QPushButton *)sender();
    QString butVal = button->text();
    QString displayVal = ui->lineEdit->text();

    if((displayVal.toDouble() == 0) || (displayVal.toDouble() == 0.0))
    {
        ui->lineEdit->setText(butVal);
    }
    else {
    // Put the new number to the right of whats there
    QString newVal = displayVal + butVal;

    double dblNewVal = newVal.toDouble();
    ui->lineEdit->setText(QString::number(dblNewVal, 'g', 16));

    }
}

void calculator::MathOp()
{

    // Cancel out previous math button clicks
    AddOperation = false;
    SubOperation = false;
    MultiOperation = false;
    divOperation = false;

    // Store current value in Display
    QString displayVal = ui->lineEdit->text();
    calcVal = displayVal.toDouble();

    // Sender returns a pointer to the button pressed
    QPushButton *button = (QPushButton *)sender();

    // Get math symbol on the button
    QString butVal = button->text();

    if(QString::compare(butVal, "/", Qt::CaseInsensitive) == 0){
        divOperation = true; DoteStatus = false;
    } else if(QString::compare(butVal, "*", Qt::CaseInsensitive) == 0){
        MultiOperation = true; DoteStatus = false;
    } else if(QString::compare(butVal, "+", Qt::CaseInsensitive) == 0){
        AddOperation = true; DoteStatus = false;
    } else {
        SubOperation = true; DoteStatus = false;
    }

    // Clear display
    ArchVal = displayVal+butVal;
    ui->label->setText(ArchVal);
    ui->lineEdit->setText("");
}

void calculator::SingneChange()
{
    QString displayVal = ui->lineEdit->text();
    QRegularExpression reg("[-]?[0-9.]*");
    QRegularExpressionMatch match = reg.match(displayVal);
    if(match.hasMatch())
    {
        double dblDisplayVal = displayVal.toDouble();
        double dblDisplayValSign = -1 * dblDisplayVal;
        ui->lineEdit->setText(QString::number(dblDisplayValSign));
    }
}

void calculator::EqualClick()
{

    // Holds new calculation
    double solution = 0.0;

    // Get value in display
    QString displayVal = ui->lineEdit->text();
    double dblDisplayVal = displayVal.toDouble();

    // Make sure a math button was pressed
    if(AddOperation || SubOperation || MultiOperation || divOperation ){
        if(AddOperation){
            solution = calcVal + dblDisplayVal;
        } else if(SubOperation){
            solution = calcVal - dblDisplayVal;
        } else if(MultiOperation){
            solution = calcVal * dblDisplayVal;
        } else {
            solution = calcVal / dblDisplayVal;
        }
    }
    DoteStatus = true;

    // Put solution in display
    ArchVal = ArchVal+displayVal;
    ui->label->setText(ArchVal);
    ui->lineEdit->setText(QString::number(solution));

}

void calculator::ClaerDisply()
{
    calcVal = 0.0;
    DoteStatus = false;
    ui->label->setText("");
    ui->lineEdit->setText(QString::number(calcVal));
}


