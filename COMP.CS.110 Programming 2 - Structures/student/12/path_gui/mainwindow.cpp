/* Polku
 *
 * Nimi: Jani Koistinen
 * Opiskelijanumero: H268666
 * Käyttäjätunnus: koistin3
 * E-Mail: jani.koistinen@tuni.fi
*/
#include "mainwindow.hh"
#include "ui_mainwindow.h"

#include "gameboard.hh"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{

    ui->setupUi(this);

    timer = new QTimer(this);
    statusbar = new QStatusBar(this);
    board_ = new GameBoard;

    connect(timer, SIGNAL(timeout()), this, SLOT(update_time()));
    statusBar()->showMessage("Paina 'Start' aloittaaksesi pelin");

    init_gui_board();
    update_view();
    ui->label->setVisible(false);
    ui->pauseButton->setEnabled(false);
    ui->resetButton->setEnabled(false);

    read_scores();
    ask_name();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::init_gui_board()
{
    std::vector< QPushButton* > temp;
    for(int j = 0; j < 5; j++) {
        for(int i = 0; i < 4; i++) {
            button = new QPushButton(this);
            button->setGeometry(LEFT_MARGIN + i*BUTTON_MARGIN,
                                TOP_MARGIN + j*BUTTON_MARGIN,
                                BUTTON_SIZE, BUTTON_SIZE);
            button->setEnabled(false);
            temp.push_back(button);

            connect(button, &QPushButton::clicked,
                    this, &MainWindow::handle_button_click);

        }
        buttons_.push_back(temp);
        temp.clear();
    }
}

void MainWindow::update_view()
{
    for(int j = 0; j < ROWS; j++) {
        for(int i = 0; i < COLUMNS; i++) {
            switch(board_->which_slot({i, j}))
            {
            case GREEN:
                buttons_.at(j).at(i)->setStyleSheet("background-color: green");
                break;
            case RED:
                buttons_.at(j).at(i)->setStyleSheet("background-color: red");
                break;
            case EMPTY:
                buttons_.at(j).at(i)->setStyleSheet("");
                break;
            case UNUSED:
                buttons_.at(j).at(i)->setEnabled(false);
                buttons_.at(j).at(i)->setVisible(false);
                break;
            }
        }
    }
}

void MainWindow::update_time()
{
    ss++;
    if( ss == 60 ) {
        mm++;
        ss = 0;
        if(mm == 60) {
            hh++;
            mm = 0;
        }
    }
    time = QTime(hh,mm,ss,0);
    QString timestr = time.toString("hh:mm:ss");
    statusBar()->showMessage(timestr + "  Siirrot: " +
                             QString::number(board_->get_moves()) +
                             "  Pisteet: " +
                             QString::number(board_->get_points()));
}

void MainWindow::on_startButton_clicked()
{
    if( board_->is_game_over() ) {
        board_->clear_board();
        update_view();
        ss = 0;
        mm = 0;
        hh = 0;
    }
    this->setStyleSheet("");
    timer->start(1000);    
    init_buttons();

}

void MainWindow::on_resetButton_clicked()
{
    timer->stop();
    ss = 0;
    mm = 0;
    hh = 0;
    board_->clear_board();
    update_view();
    for( int j = 0; j < ROWS; j++ ) {
        for( int i = 0; i < COLUMNS; i++ ) {
            buttons_.at(j).at(i)->setEnabled(false);
        }
    }
    ui->pauseButton->setEnabled(false);
    ui->resetButton->setEnabled(false);
    ui->startButton->setEnabled(true);
    ui->changePlayerButton->setEnabled(true);
    statusBar()->showMessage("Paina 'Start' aloittaaksesi pelin");
}

void MainWindow::on_closeButton_clicked()
{
    for( int j = 0; j < ROWS; j++ ) {
        for( int i = 0; i < COLUMNS; i++ ) {
            delete buttons_.at(j).at(i);
        }
    }
    delete timer;
    delete statusbar;
    delete board_;
    close();
}

void MainWindow::on_pauseButton_clicked()
{
    timer->stop();
    for( int j = 0; j < ROWS; j++ ) {
        for( int i = 0; i < COLUMNS; i++ ) {
            buttons_.at(j).at(i)->setEnabled(false);
        }
    }
    statusBar()->showMessage(time.toString("hh:mm:ss") +
                             "  PAUSE! Jatka painamalla 'Start' tai "
                             "aloita alusta painamalla 'Reset'");
    ui->pauseButton->setEnabled(false);
    ui->startButton->setEnabled(true);
}

void MainWindow::init_buttons()
{
    ui->pauseButton->setEnabled(true);
    ui->resetButton->setEnabled(true);
    ui->startButton->setEnabled(false);
    ui->changePlayerButton->setEnabled(false);
    for( int j = 0; j < ROWS; j++ ) {
        for( int i = 0; i < COLUMNS; i++ ) {
            buttons_.at(j).at(i)->setEnabled(true);
        }
    }
}

void MainWindow::handle_button_click()
{
    QString temp;
    for( int j = 0; j < ROWS; j++) {
        for( int i = 0; i < COLUMNS; i++ ) {
            if( buttons_.at(j).at(i) == sender()) {
                if( board_->which_slot({i, j}) == EMPTY ) {
                    return;
                }
                start_x = i;
                start_y = j;
                temp = buttons_.at(j).at(i)->styleSheet();
                temp.append("; border: 4px solid black");
                buttons_.at(j).at(i)->setStyleSheet(temp);
            }
        }
    }
    for( int j = 0; j < ROWS; j++ ) {
        for( int i = 0; i < COLUMNS; i++ ) {
            disconnect(buttons_.at(j).at(i), &QPushButton::clicked,
                       this, &MainWindow::handle_button_click);
            connect(buttons_.at(j).at(i), &QPushButton::clicked,
                    this, &MainWindow::handle_destination_click);
        }
    }
}

void MainWindow::handle_destination_click()
{
    for( int j = 0; j < ROWS; j++ ) {
        for( int i = 0; i < COLUMNS; i++ ) {
            if( buttons_.at(j).at(i) == sender() ) {
                dest_x = i;
                dest_y = j;
                qDebug() << "Start X:" << start_x << "Start Y:" << start_y;
                qDebug() << "Dest X:" << dest_x << "Dest Y:" << dest_y;
                if((start_x != dest_x or start_y != dest_y) and
                    board_->move({start_x, start_y}, {dest_x, dest_y})) {
                    board_->report_move();
                    board_->deduct_points();
                }
                if( board_->is_game_over() ) {
                    ui->pauseButton->setEnabled(false);
                    ui->resetButton->setEnabled(false);
                    ui->startButton->setEnabled(true);
                    ui->changePlayerButton->setEnabled(true);
                    for( int j = 0; j < ROWS; j++ ) {
                        for( int i = 0; i < COLUMNS; i++ ) {
                            buttons_.at(j).at(i)->setEnabled(false);
                        }
                    }
                    timer->stop();
                    statusBar()->showMessage("GAME OVER!");
                    if( board_->get_moves() == 31 ) {
                        this->setStyleSheet("background-color: gold");
                    }
                }

            }
            disconnect(buttons_.at(j).at(i), &QPushButton::clicked,
                       this, &MainWindow::handle_destination_click);
            connect(buttons_.at(j).at(i), &QPushButton::clicked,
                    this, &MainWindow::handle_button_click);
        }
    }
    update_view();
}


void MainWindow::on_changePlayerButton_clicked()
{
    ask_name();
}

void MainWindow::ask_name()
{
    QString input_name = QInputDialog::getText(this, tr("QInputDialog::getText()"),
                                               tr("Player name:"),
                                               QLineEdit::Normal,
                                               "player", &name_ok);
    if( name_ok and not input_name.isEmpty()) {
        player_name = input_name;
        ui->label->setText("Player name: " + player_name);
        ui->label->setVisible(true);
    } else {
        player_name.clear();
        ui->label->setVisible(false);
    }
}

void MainWindow::read_scores()
{
    std::string line;
    std::vector< std::string > line_splitted;
    std::ifstream file_read(score_file);
    if( not file_read ) {
        std::ofstream file_out("scores.sco");
        file_out.close();
        return;
    }
    while( getline(file_read, line) ) {
        line_splitted = split(line, ';', false);
        scores.insert_or_assign(line_splitted.at(0), stoi(line_splitted.at(1)));
    }
    QString scoreboard = "";
    std::map< std::string, int >::iterator iter;
    for( iter = scores.begin(); iter != scores.end(); iter++) {
        scoreboard.append(QString::number(iter->second) + " " + QString::fromStdString(iter->first) + "\n");
    }
    ui->scoreLabel->setText(scoreboard);
}

void MainWindow::update_scores()
{

}

std::vector<std::string> MainWindow::split(std::string s, char delimiter,
                               bool ignore_empty)
{
    std::vector<std::string> result;
    std::string tmp = s;

    while(tmp.find(delimiter) != std::string::npos)
    {
        std::string new_part = tmp.substr(0, tmp.find(delimiter));
        tmp = tmp.substr(tmp.find(delimiter)+1, tmp.size());
        if(not (ignore_empty and new_part.empty()))
        {
            result.push_back(new_part);
        }
    }
    if(not (ignore_empty and tmp.empty()))
    {
        result.push_back(tmp);
    }
    return result;
}

