/* Yliopisto
 *
 * Kuvaus:
 * Ohjelma toteuttaa yliopiston yksinkertaisen opintorekisterin. Opintorekiste-
 * riin voi lisätä kursseja ja henkilöitä. Ohjelmaa käytetään komentoikkunassa
 * ja ohjelman suoritus näkyy kun "Uni>" on auki komentoikkunassa. Tällöin
 * käyttäjältä odotetaan komentoa.
 *
 * Komennot:
 *  QUIT, ohjelman suoritus päättyy
 *  HELP, tulostaa käytössä olevat komennot ja niiden lyhenteet
 *  NEW_ACCOUNT <koko nimi>, lisää järjestelmään henkilön
 *  PRINT_ACCOUNT <henkilönumero>, tulostaa henkilönumeron tiedot
 *  PRINT_ACCOUNTS, tulostaa kaikkien henkilöiden tiedot
 *  NEW_COURSE <koodi> <nimi>, lisää uuden kurssin yliopiston järjestelmään
 *  ADD_STAFF <koodi> <henkilönumero>, lisää koodin kurssille henkilökuntaa
 *  PRINT_COURSE <koodi>, tulostaa kurssin tiedot
 *  PRINT_COURSES, tulostaa yliopiston kaikki kurssit
 *  READ_FROM <tiedosto>, komennolla voidaan lukea useampi komento kerralla
 *                        annetusta tiedostosta
 *  SIGN_UP <koodi> <henkilönumero>, ilmoittaa opiskelijan kurssille
 *  COMPLETE <koodi> <henkilönumero>, lisätää kurssi suoritetuksi
 *  PRINT_STUDY_STATE <henkilönumero>, tulostaa opiskelutilanteen
 *  PRINT_COMPLETED <henkilönumero>, tulostaa henkilön suoritetut kurssit
 *  PRINT_SIGNUPS <koodi>, tulostaa kurssille ilmoittautuneet henkilöt
 *  GRADUATE <henkilönumero>, merkkaa henkilö valmistuneeksi
 *
 * Nimi: Jani Koistinen
 * Opiskelijanumero: H268666
 * Käyttäjätunnus: koistin3
 * E-Mail: jani.koistinen@tuni.fi
*/

//#include "utils.hh"
#include "cli.hh"
#include "university.hh"
//#include <iostream>
//#include <string>
//#include <vector>
//#include <fstream>

const std::string PROMPT = "Uni> ";


int main()
{
    University* university = new University("tuni.fi");
    Cli cli(university, PROMPT);
    while ( cli.exec() ){}

    delete university;
    return EXIT_SUCCESS;
}

