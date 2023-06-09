#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QDebug>
#include <cmath>

double firstNum;
bool userIsTypingSecondNumber = false;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect(ui->pushButton_0, SIGNAL(released()), this, SLOT(digit_pressed()));
    connect(ui->pushButton_1, SIGNAL(released()), this, SLOT(digit_pressed()));
    connect(ui->pushButton_2, SIGNAL(released()), this, SLOT(digit_pressed()));
    connect(ui->pushButton_3, SIGNAL(released()), this, SLOT(digit_pressed()));
    connect(ui->pushButton_4, SIGNAL(released()), this, SLOT(digit_pressed()));
    connect(ui->pushButton_5, SIGNAL(released()), this, SLOT(digit_pressed()));
    connect(ui->pushButton_6, SIGNAL(released()), this, SLOT(digit_pressed()));
    connect(ui->pushButton_7, SIGNAL(released()), this, SLOT(digit_pressed()));
    connect(ui->pushButton_8, SIGNAL(released()), this, SLOT(digit_pressed()));
    connect(ui->pushButton_9, SIGNAL(released()), this, SLOT(digit_pressed()));
    connect(ui->pushButton_pi, SIGNAL(released()), this, SLOT(digit_pressed()));

    connect(ui->pushButton_plus_minus, SIGNAL(released()), this, SLOT(unary_operation_pressed()));;
    connect(ui->pushButton_persent, SIGNAL(released()), this, SLOT(unary_operation_pressed()));
    connect(ui->pushButton_2nd, SIGNAL(clicked()), this, SLOT(unary_operation_pressed()));

    connect(ui->pushButton_plus, SIGNAL(clicked()), this, SLOT(math_operation()));
    connect(ui->pushButton_minus, SIGNAL(clicked()), this, SLOT(math_operation()));
    connect(ui->pushButton_multyple, SIGNAL(clicked()), this, SLOT(math_operation()));
    connect(ui->pushButton_divide, SIGNAL(clicked()), this, SLOT(math_operation()));

    ui->pushButton_plus->setCheckable(true);
    ui->pushButton_minus->setCheckable(true);
    ui->pushButton_multyple->setCheckable(true);
    ui->pushButton_divide->setCheckable(true);

    connect(ui->pushButton_ln, SIGNAL(clicked()), this, SLOT(trigonometry_operation_pressed()));
    connect(ui->pushButton_sin, SIGNAL(clicked()), this, SLOT(trigonometry_operation_pressed()));
    connect(ui->pushButton_asin, SIGNAL(clicked()), this, SLOT(trigonometry_operation_pressed()));
    connect(ui->pushButton_cot, SIGNAL(clicked()), this, SLOT(trigonometry_operation_pressed()));
    connect(ui->pushButton_cos, SIGNAL(clicked()), this, SLOT(trigonometry_operation_pressed()));
    connect(ui->pushButton_acos, SIGNAL(clicked()), this, SLOT(trigonometry_operation_pressed()));
    connect(ui->pushButton_sh, SIGNAL(clicked()), this, SLOT(trigonometry_operation_pressed()));
    connect(ui->pushButton_tan, SIGNAL(clicked()), this, SLOT(trigonometry_operation_pressed()));
    connect(ui->pushButton_atan, SIGNAL(clicked()), this, SLOT(trigonometry_operation_pressed()));
    connect(ui->pushButton_ch, SIGNAL(clicked()), this, SLOT(trigonometry_operation_pressed()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::digit_pressed()
{
    QPushButton * button = (QPushButton*)sender();

    double labelNumber;
    QString newLabel;

    if((ui->pushButton_plus->isChecked() || ui->pushButton_minus->isChecked() ||
            ui->pushButton_multyple->isChecked() || ui->pushButton_divide->isChecked()) && (!userIsTypingSecondNumber))
    {
        labelNumber = button->text().toDouble();
        userIsTypingSecondNumber = true;
        newLabel = QString::number(labelNumber, 'g', 15);
    }
    else
    {
        if(ui->label->text().contains('.') && button->text() == "0")
        {
            newLabel = ui->label->text() + button->text();
        }
        else{
             labelNumber = (ui->label->text() + button->text()).toDouble();
             newLabel = QString::number(labelNumber, 'g', 15);
        }
    }

    ui->label->setText(newLabel);
}

void MainWindow::on_pushButton_dot_released()
{
    if(!ui->label->text().contains('.'))
        ui->label->setText(ui->label->text() + '.');

}

void MainWindow::unary_operation_pressed()
{
    QPushButton * button = (QPushButton*)sender();
    double labelNumber;
    QString newLabel;

    if(button->text()=="+/-")
    {
        labelNumber = ui->label->text().toDouble();
        labelNumber = labelNumber* -1;
        newLabel = QString::number(labelNumber, 'g', 15);
        ui->label->setText(newLabel);
    }

    if(button->text() == "%")
    {
        labelNumber = ui->label->text().toDouble();
        labelNumber = labelNumber * 0.01;
        newLabel = QString::number(labelNumber, 'g', 15);
        ui->label->setText(newLabel);
    }
    if(button->text() == "2nd")
    {
        labelNumber = ui->label->text().toDouble();
        labelNumber = pow(2, labelNumber);
        newLabel = QString::number(labelNumber, 'g', 15);
        ui->label->setText(newLabel);
    }
}

void MainWindow::math_operation()
{
    QPushButton *button = (QPushButton*)sender();

    firstNum = ui->label->text().toDouble();
    ui->label->setText("");

    button->setChecked(true);
}

void MainWindow::on_pushButton_clear_clicked()
{
    ui->pushButton_plus->setChecked(false);
    ui->pushButton_minus->setChecked(false);
    ui->pushButton_multyple->setChecked(false);
    ui->pushButton_divide->setChecked(false);

    ui->label->setText("");
}

void MainWindow::on_pushButton_equals_clicked()
{
    double labelNumber, secondNum;
    QString newLabel;

    secondNum = ui->label->text().toDouble();

    if(ui->pushButton_plus->isChecked())
    {
        labelNumber = firstNum + secondNum;
        newLabel = QString::number(labelNumber, 'g', 15);
        ui->label->setText(newLabel);
        ui->pushButton_plus->setChecked(false);
    }
    else if(ui->pushButton_minus->isChecked())
    {
        labelNumber = firstNum - secondNum;
        newLabel = QString::number(labelNumber, 'g', 15);
        ui->label->setText(newLabel);
        ui->pushButton_minus->setChecked(false);
    }
    else if(ui->pushButton_multyple->isChecked())
    {
        labelNumber = firstNum * secondNum;
        newLabel = QString::number(labelNumber, 'g', 15);
        ui->label->setText(newLabel);
        ui->pushButton_multyple->setChecked(false);
    }
    else if(ui->pushButton_divide->isChecked())
    {
        if(secondNum == 0){
            ui->label->setText("0");
        }else{
        labelNumber = firstNum / secondNum;
        newLabel = QString::number(labelNumber, 'g', 15);
        ui->label->setText(newLabel);
        ui->pushButton_divide->setChecked(false);
        }
    }
}

void MainWindow::trigonometry_operation_pressed()
{
    QPushButton * button = (QPushButton*)sender();
    double labelNumber;
    QString newLabel;

    if(button->text()=="sin")
    {
        labelNumber = ui->label->text().toDouble();
        labelNumber = sin(labelNumber);
        newLabel = QString::number(labelNumber, 'g', 15);
        ui->label->setText(newLabel);
    }
    if(button->text() == "asin")
    {
        labelNumber = ui->label->text().toDouble();
        labelNumber = asin(labelNumber);
        newLabel = QString::number(labelNumber, 'g', 15);
        ui->label->setText(newLabel);
    }
    if(button->text() == "cot")
    {
        labelNumber = ui->label->text().toDouble();
        labelNumber = 1 / tan(labelNumber);
        newLabel = QString::number(labelNumber, 'g', 15);
        ui->label->setText(newLabel);
    }
    if(button->text() == "cos")
    {
        labelNumber = ui->label->text().toDouble();
        labelNumber = cos(labelNumber);
        newLabel = QString::number(labelNumber, 'g', 15);
        ui->label->setText(newLabel);
    }
    if(button->text() == "acos")
    {
        labelNumber = ui->label->text().toDouble();
        labelNumber = acos(labelNumber);
        newLabel = QString::number(labelNumber, 'g', 15);
        ui->label->setText(newLabel);
    }
    if(button->text() == "tan")
    {
        labelNumber = ui->label->text().toDouble();
        labelNumber = tan(labelNumber);
        newLabel = QString::number(labelNumber, 'g', 15);
        ui->label->setText(newLabel);
    }
    if(button->text() == "atan")
    {
        labelNumber = ui->label->text().toDouble();
        labelNumber = atan(labelNumber);
        newLabel = QString::number(labelNumber, 'g', 15);
        ui->label->setText(newLabel);
    }
    if(button->text() == "sh")
    {
        labelNumber = ui->label->text().toDouble();
        labelNumber = sinh(labelNumber);
        newLabel = QString::number(labelNumber, 'g', 15);
        ui->label->setText(newLabel);
    }
    if(button->text() == "ch")
    {
        labelNumber = ui->label->text().toDouble();
        labelNumber = cosh(labelNumber);
        newLabel = QString::number(labelNumber, 'g', 15);
        ui->label->setText(newLabel);
    }
    if(button->text() == "ln")
    {
        labelNumber = ui->label->text().toDouble();
        labelNumber = log(labelNumber);
        newLabel = QString::number(labelNumber, 'g', 15);
        ui->label->setText(newLabel);
    }
}
