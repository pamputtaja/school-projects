/* Polku
 *
 * Nimi: Jani Koistinen
 * Opiskelijanumero: H268666
 * Käyttäjätunnus: koistin3
 * E-Mail: jani.koistinen@tuni.fi
*/

#ifndef MAINWINDOW_HH
#define MAINWINDOW_HH

#include "gameboard.hh"
#include <QDebug>
#include <QMainWindow>
#include <QInputDialog>
#include <QTimer>
#include <QTime>
#include <QStatusBar>
#include <QPushButton>
#include <vector>
#include <map>
#include <iostream>
#include <fstream>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();

    // funktio jossa luodaan pelilaudan napit, koko ja nappien paikat.
    // Napit talletaan buttons_ vektoriin
    void init_gui_board();

    // funktio pelilaudan nappien värien päivittämiseksi
    void update_view();

    std::vector<std::string> split(std::string s, char delimiter,
                                   bool ignore_empty);

private slots:
    // funktio pelissä kuluneen ajan päivittämiseen. Samassa funktiossa
    // päivitetään myös siirtojen näkymä
    void update_time();

    void on_startButton_clicked();

    void on_resetButton_clicked();

    void on_closeButton_clicked();

    void on_pauseButton_clicked();

    // alustetaan napit ja pelinapit, jotta niitä voidaan painaa pelin aikana
    void init_buttons();

    // funktio jossa määritetään mitä tapahtuu kun pelinappia painetaan
    // ensimmäisen kerran
    void handle_button_click();

    // funktiossa yritetään suorittaa siirtää pelinappula haluttuun kohtaan sen
    // jälkeen kun siirrettävä pelinappula on valittu
    void handle_destination_click();

    void on_changePlayerButton_clicked();

    // nimen päivitysfunktio, aukaisee dialogin nimen päivitykseen ja päivittää
    // nimen mikäli dialogissa painetaan ok nappia, cancel kumoaa päivityksen
    void ask_name();

    // lukee pisteet tiedostosta tulostaulua varten
    void read_scores();

    void update_scores();

private:
    Ui::MainWindow *ui;

    // const attributes for appearence
    const int LEFT_MARGIN = 150;
    const int TOP_MARGIN = 40;
    const int BUTTON_MARGIN = 50;
    const int BUTTON_SIZE = 40;
    const int ROWS = 5;
    const int COLUMNS = 4;



    QTime time;
    QTimer* timer;
    QStatusBar* statusbar;

    GameBoard *board_;
    QPushButton *button;

    std::vector< std::vector< QPushButton*> > buttons_;


    // timer attributes
    int mm = 0;
    int ss = 0;
    int hh = 0;

    // move attributes
    int start_x;
    int start_y;
    int dest_x;
    int dest_y;

    QString player_name;
    bool name_ok;
    std::string score_file = "scores.sco";
    std::map < std::string, int > scores;



};
#endif // MAINWINDOW_HH
