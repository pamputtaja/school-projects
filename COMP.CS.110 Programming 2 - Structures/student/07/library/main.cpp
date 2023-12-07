/* Projekti 7.2 Kirjasto
 *
 * Ohjelma toteuttaa eräänlaisen kirjastotietokannan, josta voidaan tehdä
 * erilaisia hakuja komennoilla. Ohjelma alkaa kysymällä syötetidoston,
 * jossa on tiedot kirjastoista ja kirjoista. Ohjelma tallettaa tämän jälkeen
 * ne tietorakenteeseen.
 *
 * Ohjelman käyttöliittymänä toimii komentokehote. Ohjelman suorituksen aikana
 * komentokehotteessa näkyy tunniste "lib >", jolloin ohjelman komentoja voi
 * syöttää.
 *
 * Komennot:
 *
 *  - quit                  - lopettaa ohjelman
 *  - libraries             - tulostaa kirjastot
 *  - material <kirjasto>   - tulostaa kirjaston kirjat
 *  - books <kirjasto> <tekijä>
 *                          - tulostaa tekijän kirjat tietystä kirjastosta
 *  - reservable <tekijä> <kirjan nimi>
 *                          - tulostaa kirjan lyhyimmän varausjonon
 *  - loanable              - tulostaa kaikki sillä hetkellä lainattivissa
 *                            olevat kirjat
 *
 * Ohjelman kirjoittaja
 * Nimi: Jani Koistinen
 * Opiskelijanumero: H268666
 * Käyttäjätunnus: koistin3 ( Git-repositorion hakemistonimi. )
 * E-Mail: jani.koistinen@tuni.fi
 */

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <set>
#include <map>
#include <vector>
#include <algorithm>


// tietorakenne johon pelkät kirjat tallennetaan
struct Book
{
    std::string author;
    std::string title;
    int reservations;
};

// vertailufunktio sorttaukseen kirjan kirjoittajalle, palauttaa totuusarvon
bool compare_author(const Book &a, const Book &b)
{
    return a.author < b.author;
}

// pilkkoo rivin ja palauttaa rivin vektorina, saa parametrina pilkkomattoman
// rivin ja merkin jos erotellaan, samaa metodia käytetään myös komennon
// pilkkomiseen sen jälkeen kun tiedot on luettu tiedostosta
std::vector<std::string> split(const std::string& s, const char delimiter,
                               bool ignore_empty = false){
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

// tarkistaa rivin oikeellisuuden, saa parametrina vektorin valmiiksi
// pilkotusta rivistä
bool check_line(std::vector< std::string > line_splitted)
{
    if(line_splitted.size() != 4) {
        return 0;
    }
    for( auto elem : line_splitted) {
        if(elem == "" or elem[0] == ' ') {
            return 0;
        }
    }
    return 1;
}

// tallettaa kirjat tietorakenteeseen, saa parametreina pilkotun vektorin
// tiedoston rivistä ja tietorakenteen johon kirjat tallennetaan
void store_to_catalog(std::vector< std::string > line_splitted,
                      std::map< std::string, std::vector< Book > > &catalog)
{
    std::vector< Book > temp;
    Book new_book;
    new_book.author = line_splitted[1];
    new_book.title = line_splitted[2];
    int length;

    if(line_splitted[3] == "on-the-shelf"){
        new_book.reservations = 0;
    } else {
        new_book.reservations = stoi(line_splitted[3]);
    }
    if(catalog.find(line_splitted[0]) != catalog.end()) {
        temp = catalog[line_splitted[0]];
        length = temp.size();
        for(int i = 0; i < length; i++) {
            if(temp[i].author == new_book.author and
               temp[i].title == new_book.title) {
                temp[i].reservations = new_book.reservations;
                return;
            }
        }
        temp.push_back(new_book);
        catalog.insert_or_assign(line_splitted[0], temp);

    } else {
        temp.push_back(new_book);
        catalog.insert_or_assign(line_splitted[0], temp);
    }


}

// tulostaa tietorakenteeseen tallennetut kirjastot, saa parametrina
// tietorakenteen, joka sisältää kirjastot ja kirjat
void print_libraries(std::map< std::string, std::vector< Book > > &catalog)
{
    std::map< std::string, std::vector< Book > >::iterator iter;

    for(iter = catalog.begin(); iter != catalog.end(); iter++) {
        std::cout << iter->first << std::endl;
    }
}

// tulostaa valitun kirjaston materiaalin, saa parametrina tietorakententeen,
// johon kirjastot ja kirjat tallennettu
void print_material(std::map< std::string, std::vector< Book > > &catalog,
                    std::string library)
{
    std::vector< Book > temp;

    std::map< std::string, std::vector< Book > >::iterator
        iter = catalog.find(library);

    if(iter != catalog.end()) {
        temp = iter->second;
        sort(temp.begin(), temp.end(), compare_author);
        int length = temp.size();
        for(int i = 0; i < length; i++) {
            std::cout << temp[i].author << ": " << temp[i].title << std::endl;
        }
    } else {
        std::cout << "Error: unknown library" << std::endl;
        return;
    }
}

// tulostaa kirjailijan kirjat tietystä kirjastosta, saa parametreina
// tietorakenteen, joka sisältää kirjaston ja kirjat ja etsittävän
// kirjaston ja kirjan
void print_books(std::map< std::string, std::vector< Book > > &catalog,
                 std::string library, std::string author) {
    std::vector< Book > temp;
    bool found = false;

    std::map< std::string, std::vector< Book > >::iterator
        iter = catalog.find(library);

    if(iter != catalog.end()) {
        temp = iter->second;
        sort(temp.begin(), temp.end(), compare_author);
        int length = temp.size();
        for(int i = 0; i < length; i++) {
            if(temp[i].author == author) {
                found = true;
                if(temp[i].reservations == 0) {
                    std::cout << temp[i].title << " --- " <<
                        "on the shelf" << std::endl;
                } else {
                    std::cout << temp[i].title << " --- " <<
                        temp[i].reservations << " reservations" << std::endl;
                }
            }
        }
        if(not found) {
            std::cout << "Error: unknown author" << std::endl;
        }

    } else {
        std::cout << "Error: unknown library" << std::endl;
    }
}

// Tulostaa haetun kirjan varaukset ja mistä sen voi varata lyhyimmällä
// varausajalla. Mikäli kahdessa kirjastossa sama varausjono, tulostetaan
// molemmat kirjastot. Saa parametrina tietorakenteen jossa kirjastot ja kirjat
// sekä koko komennon.
void print_reservable(std::map< std::string, std::vector< Book > > &catalog,
                      std::vector< std::string > command) {
    std::vector< Book > temp;
    std::set< std::string > libraries;
    std::string author = command[1];
    std::string title;
    int reservations = 100;
    int length = command.size();
    bool found = false;

    std::map< std::string, std::vector< Book > >::iterator iter;

    std::set< std::string >::iterator iter_set;

    // parsitaan kirjan nimi yhteen merkkijonomuuttujaan
    title.append(command[2]);
    for(int i = 3; i < length; i++) {
        title.append(" " + command[i]);
    }

    length = title.size();
    if(title.at(0) == '"' and title.at(length-1) == '"') {
        title.erase(length-1);
        title.erase(0, 1);
    }


    for(iter = catalog.begin(); iter != catalog.end(); iter++) {
        temp = iter->second;
        length = temp.size();
        for(int i = 0; i < length; i++) {
            if(temp[i].author == author and temp[i].title == title) {
                found = true;
                if(temp[i].reservations < reservations) {
                    reservations = temp[i].reservations;
                    libraries.clear();
                    libraries.insert(iter->first);
                } else if (temp[i].reservations == reservations) {
                    libraries.insert(iter->first);
                }
            }
        }
    }

    if(not found) {
        std::cout << "Book is not a library book" << std::endl;
        return;
    }

    if(reservations > 99) {
        std::cout << "Book is not reservable from any library" << std::endl;
    } else if(reservations == 0) {
        std::cout << "on the shelf" << std::endl;
        for(iter_set = libraries.begin(); iter_set != libraries.end();
            iter_set++) {
            std::cout << "--- " << *iter_set << std::endl;
        }
    } else {
        std::cout << reservations << " reservations" << std::endl;
        for(iter_set = libraries.begin(); iter_set != libraries.end();
             iter_set++) {
            std::cout << "--- " << *iter_set << std::endl;
        }
    }
}

// Käy läpi kirjastojen kirjat ja katsoo, onko kirja hyllyssä ja koostaa näistä
// setin, joka lopuksi tulostetaan. Saa parametrina mapin, joka sisältää
// kirjastot ja kirjat.
void print_loanable(std::map< std::string, std::vector< Book > > &catalog)
{
    std::vector< Book > temp;
    std::set< std::string > temp_set;
    std::string author_title;
    int length;

    std::map< std::string, std::vector< Book > >::iterator iter;
    std::set< std::string >::iterator iter_set;

    for(iter = catalog.begin(); iter != catalog.end(); iter++) {
        temp = iter->second;
        length = temp.size();
        for(int i = 0; i < length; i++) {
            if(temp[i].reservations == 0) {
                author_title.append(temp[i].author + ": " + temp[i].title);
                temp_set.insert(author_title);
            }
            author_title = "";
        }
    }
    for(iter_set = temp_set.begin(); iter_set != temp_set.end(); iter_set++) {
        std::cout << *iter_set << std::endl;
    }
}

int main()
{
    // map tietorakenne johon kirjastot ja kirjat tallennetaan,
    // kirjaston nimi on key ja valueksi tulee structin sisältävä
    // vektori kirjoista
    std::map< std::string, std::vector< Book > > catalog;

    std::vector< std::string > line_splitted;
    std::vector< std::string > command;
    std::string input;

    std::string file_line;
    std::string file_name;
    std::cout << "Input file: ";
    std::getline(std::cin, file_name);

    std::ifstream file_in(file_name);
    if (not file_in) {
        std::cout << "Error: input file cannot be opened" << std::endl;
        return EXIT_FAILURE;
    } else {
        while(getline(file_in, file_line)) {
            line_splitted = split(file_line, ';');
            if (check_line(line_splitted) == false) {
                std::cout << "Error: empty field" << std::endl;
                    return EXIT_FAILURE;
            }
            store_to_catalog(line_splitted, catalog);
        }
        file_in.close();
    }

    // ohjelman varsinainen toimintasilmukka
    while(true) {
        std::cout << "lib> ";
        getline(std::cin, input);
        command = split(input, ' ');

        if(command[0] == "quit") {
            return EXIT_SUCCESS;

        } else if(command[0] == "libraries") {
            print_libraries(catalog);

        } else if(command[0] == "material") {
            if(command.size() != 2) {
                std::cout << "Error: wrong number of parameters" << std::endl;
            } else {
                print_material(catalog, command[1]);
            }

        } else if(command[0] == "books") {
            if(command.size() != 3) {
                std::cout << "Error: wrong number of parameters" << std::endl;
            } else {
                print_books(catalog, command[1], command[2]);
            }

        } else if(command[0] == "reservable") {
            print_reservable(catalog, command);

        } else if(command[0] == "loanable") {
            print_loanable(catalog);

        } else {
            std::cout << "Error: unknown command" << std::endl;
        }
    }
}
