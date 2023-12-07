#include "mainwindow.hh"
#include "ui_mainwindow.h"
#include "gradecalculator.hh"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->spinBoxN->setMinimum(0);
    ui->spinBoxN->setMaximum(800);

    ui->spinBoxG->setMinimum(0);
    ui->spinBoxG->setMaximum(120);

    ui->spinBoxP->setMinimum(0);
    ui->spinBoxP->setMaximum(250);

    ui->spinBoxE->setMinimum(0);
    ui->spinBoxE->setMaximum(5);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_spinBoxN_valueChanged(int arg1)
{
    N_ = arg1;
}

void MainWindow::on_spinBoxG_valueChanged(int arg1)
{
    G_ = arg1;
}


void MainWindow::on_spinBoxP_valueChanged(int arg1)
{
    P_ = arg1;
}


void MainWindow::on_spinBoxE_valueChanged(int arg1)
{
    E_ = arg1;
}


void MainWindow::on_calculatePushButton_clicked()
{
    QString text_to_print = "W-Score: ";
    QString w_score = QString::number(score_from_weekly_exercises(N_, G_));
    QString p_score = QString::number(score_from_projects(P_));
    QString total_grade = QString::number(calculate_total_grade(N_, G_, P_, E_));
    text_to_print.append(w_score);
    text_to_print.append("\nP-Score: ");
    text_to_print.append(p_score);
    text_to_print.append("\nTotal grade: ");
    text_to_print.append(total_grade);
    ui->textBrowser->setText(text_to_print);
}

