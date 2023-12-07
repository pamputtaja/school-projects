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


void MainWindow::on_closePushButton_clicked()
{
    close();
}



void MainWindow::on_fileLineEdit_editingFinished()
{
    file = ui->fileLineEdit->text().toStdString();
}


void MainWindow::on_keyLineEdit_editingFinished()
{
    key = ui->keyLineEdit->text().toStdString();
}


void MainWindow::on_findPushButton_clicked()
{
    std::string line;
    std::ifstream file_read(file);
    bool word_found = false;
    if( not file_read ) {
        ui->textBrowser->setText( "File not found" );
        return;
    } else if( file_read and key == "" ) {
        ui->textBrowser->setText( "File found" );
        return;
    } else {
        while( getline(file_read, line) ) {
            if( not ui->matchCheckBox->isChecked() ) {
                key = to_upper_case(key);
                line = to_upper_case(line);
            }
            if( line.find(key) != std::string::npos ) {
                word_found = true;
            }
        }
        if( word_found ) {
            ui->textBrowser->setText("Word found");
        } else {
            ui->textBrowser->setText("Word not found");
        }
    }
}

std::string MainWindow::to_upper_case(std::string line)
{
    std::string temp = "";
    for ( unsigned int i = 0; i < line.length(); i++ )
    {
        char c = toupper(line.at(i));
        temp.insert(i,1,c);
    }
    return temp;
}

