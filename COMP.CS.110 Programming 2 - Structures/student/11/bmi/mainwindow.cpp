#include "mainwindow.hh"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_weightLineEdit_editingFinished()
{
    weight = ui->weightLineEdit->text();
}

void MainWindow::on_heightLineEdit_editingFinished()
{
    height = ui->heightLineEdit->text();
}

void MainWindow::on_countButton_clicked()
{
    if ( height == "" or height.toDouble() == 0) {
        ui->resultLabel->setText("Cannot count.");
        ui->infoTextBrowser->setText("");
    } else {
        count_BMI(weight.toDouble(), height.toDouble());
    }
}

void MainWindow::count_BMI(const double weight, const double height)
{
    double bmi;
    bmi = weight/(height/100*height/100);
    ui->resultLabel->setText(QString::number(bmi));
    if ( bmi == 0 ) { ui->infoTextBrowser->setText(""); }
    else if ( bmi < 18.5 ) {
        ui->infoTextBrowser->setText("You are underweight.");
    }
    else if ( bmi < 25 ) {
        ui->infoTextBrowser->setText("Your weight is normal.");
    }
    else {
        ui->infoTextBrowser->setText("You are overweight.");
    }
}


void MainWindow::on_closeButton_clicked()
{
    close();
}

