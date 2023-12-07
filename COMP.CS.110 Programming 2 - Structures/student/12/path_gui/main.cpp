/* Polku
 *
 * Kuvaus:
 * Ohjelma toteuttaa Polku nimisen graafisen pelin. Pelissä on tavoitteena
 * saada alarivin ja yllärivin nappulat vaihdettua vastakkaisiin päätyihin
 * mahdollisimman vähillä siirroilla. Siirrettävä nappi valitaan hiiren
 * klikkauksella ja kohta mihin nappi liikutetaan valitaan tämän jälkeen
 * hiirellä.
 *
 * Peli aloitetaan 'Start' painikkeella. 'Pause' painikkeella saadaan peli
 * tauolle. 'Reset' napilla voidaan nollata peli. 'Close' painike poistuu
 * pelistä
 *
 *
 * Nimi: Jani Koistinen
 * Opiskelijanumero: H268666
 * Käyttäjätunnus: koistin3
 * E-Mail: jani.koistinen@tuni.fi
*/

#include "mainwindow.hh"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
