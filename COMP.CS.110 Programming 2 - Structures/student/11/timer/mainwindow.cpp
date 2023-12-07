#include "mainwindow.hh"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    timer = new QTimer(this);
    ui->setupUi(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(updateTime()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_closeButton_clicked()
{
    close();
}


void MainWindow::on_startButton_clicked()
{
    timer->start(1000);
}


void MainWindow::on_stopButton_clicked()
{
    timer->stop();
}


void MainWindow::on_resetButton_clicked()
{
    min = 0;
    sec = 0;
    printToLCD(min, sec);
}

void MainWindow::updateTime()
{
    sec = sec + 1;
    if( sec == 60 ) {
        min = min + 1;
        sec = 0;
    }
    printToLCD(min, sec);
}

void MainWindow::printToLCD(int min, int sec)
{
    ui->lcdNumberMin->display(min);
    ui->lcdNumberSec->display(sec);
}



