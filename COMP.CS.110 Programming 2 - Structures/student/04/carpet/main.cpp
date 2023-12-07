/* Mysteerimatto
 *
 * Kuvaus:
 *
 * Ohjelma tekee maton, josta voidaan etsiä 2x2 värimalleja. Maton koon on
 * oltava vähintään myös 2x2.
 *
 * Ohjelma kysyy ensin maton kokoa, jonka jälkeen käyttäjällä on mahdollisuus
 * täyttää matto satunnaisilla tai itse syöttämillään väreillä. Satunnainen
 * täyttö kysyy siemenlukua (1-20), jota käytetään satunnaislukugeneraattorissa.
 * Itse värit täyttämällä käyttäjän on syötettävä yhtä monta väriä kuin matossa on
 * ruutuja.
 *
 * Kun matto on saatu täytettyä, käyttäjältä kysytään neljän värin 2x2 mallia,
 * jota matosta etsitään. Ohjelma tulostaa maton kohdat, joista malli löytyi,'
 * kuinka monta kyseisiä malleja löytyi. Ohjelma myös tarkistaa sisältikö
 * etsittävä malli sallittuja värejä.
 *
 * Ohjelma päättyy kun käyttäjä antaa syötteen 'q' 'Q'
 *
 * Ohjelman kirjoittaja
 * Nimi: Jani Koistinen
 * Opiskelijanumero: H268666
 * Käyttäjätunnus: koistin3 ( Git-repositorion hakemistonimi. )
 * E-Mail: jani.koistinen@tuni.fi
 *
 * Huomioita ohjelmasta ja sen toteutuksesta (jos sellaisia on):
 *
 * */

#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <cctype>
#include <random>

enum Color {RED, GREEN, BLUE, YELLOW, WHITE};

struct ColorInfo {
    Color name;
    char color_char;
};

const std::vector< ColorInfo > colors {
    { RED, 'R'},
    { GREEN, 'G'},
    { BLUE, 'B'},
    { YELLOW, 'Y'},
    { WHITE, 'W'}

};

// tallennetaan maton koko int vectoriin
void get_size(std::vector< int > &carpet)
{
    int input = 0;
    for(int i = 0; i < 2; ++i) {
        std::cin >> input;
        carpet.push_back(input);
    }
}

// kysytään satunnais- tai itsetäyttöä niin kauan kunnes jompikumpi merkki
// annetaan, saa parametrina viittauksen muuttujaan johon valinta talletetaan
void ask_start(char &input) {
    while (true) {
        std::cout << "Select start (R for random, I for input): ";
        std::cin >> input;
        input = toupper(input);
        if(input == 'R' or input == 'I') {
            break;
        }
    }
}

// kysytään satunnaislukugeneraattorin siemenlukua niin kauan kunnes sallittu
// luku annetaan, saa parametrina viitteen siemenlukuun.
void ask_seed(int &seed) {
    while (true) {
        std::cout << "Enter seed value: ";
        std::cin >> seed;
        if(seed < 1 or seed > 20) {
            std::cout << "Error: Wrong seed value." << std::endl;
            continue;
        }
        break;
    }
}

// tarkistetaan, jotta syötetyt värit ovat sallittuja värejä, saa parametrina
// värien merkkijonon.
bool check_colors(std::string input) {
    int input_length = input.length();
    int colors_length = colors.size();
    bool is_color_found = false;

    for(int i = 0; i < input_length; i++) {
        for(int j = 0; j < colors_length; j++) {
            if(input[i] == colors[j].color_char) {
                is_color_found = true;
                break;
            }
            is_color_found = false;
        }
        if (is_color_found == false) {
            std::cout << " Error: Unknown color." << std::endl;
            return false;
        }
    }
    return true;
}

// alustetaan satunnainen matto, saa parametreina viittaukset siemenlukuun,
// maton kokoon, mattovektoriin ja totuusarvoon, jolla ilmaistaan, että matto
// alustettiin oikein
void init_carpet_random(int &seed, std::vector< int > &carpet_size,
                        std::vector< std::vector< char > > &carpet,
                        bool &is_carpet_init) {
    std::default_random_engine gen(seed);
    std::uniform_int_distribution<int> distr(0, colors.size()-1);
    std::vector< char > temp;

    for(int j = 0; j < carpet_size[1]; j++) {
        for(int i = 0; i < carpet_size[0]; i++) {
            temp.push_back(colors[distr(gen)].color_char);
        }
        carpet.push_back(temp);
        temp = {};
    }
    is_carpet_init = true;
}

// alustetaan matto omalla syötteellä, saa parametreina viittaukset maton kokoon
// mattovektoriin, totuusarvoon maton alustuksen onnistumisesta sekä värit
// joita mattoon koitetaan syöttää.
void init_carpet_input(std::vector< int > &carpet_size,
                       std::vector< std::vector< char > > &carpet,
                       bool &is_carpet_init, std::string input) {
    std::vector< char > temp;
    int input_length = input.length();

    if(input_length != carpet_size[0]*carpet_size[1]) {
        std::cout << " Error: Wrong amount of colors." << std::endl;
        return;
    }

    if(not check_colors(input)) {
        return;
    }

    for(int j = 0; j < carpet_size[1]; j++) {
        for(int i = 0; i < carpet_size[0]; i++) {
            temp.push_back(input.at(0));
            input.erase(0,1);
        }
        carpet.push_back(temp);
        temp ={};
    }
    is_carpet_init = true;
}
// etsitään halutut värimalli valmiista matosta, saa parametrina viittaukset
// mattoon, maton kokoon ja etsittävään värimalliin
void find_colors(std::vector< std::vector< char > > &carpet,
                 std::vector< int > &carpet_size,
                 std::string &colors_to_find) {
    int matches_found = 0;
    std::vector< char > temp;
    std::vector< char > temp_match;

    for(int j = 0; j < carpet_size[1]-1; j++) {
        temp = carpet[j];
        for(int i = 0; i < carpet_size[0]-1; i++) {
            if(temp[i] == colors_to_find.at(0)) {
                if(temp[i+1] == colors_to_find.at(1)) {
                    temp_match = carpet[j+1];
                    if(temp_match[i] == colors_to_find.at(2)) {
                        if(temp_match[i+1] == colors_to_find.at(3)) {
                            matches_found++;
                            std::printf(" - Found at (%d, %d)\n", i+1, j+1);
                        }
                    }
                }
            }
        }
    }
    std::cout << " = Matches found: " << matches_found << std::endl;
}

int main()
{
    std::vector< std::vector< char > > carpet;
    std::vector< int > carpet_size;   
    char start = 'X';
    std::string colors_to_find;
    std::string input;
    int seed = 0;
    bool is_carpet_init = false;

    std::cout << "Enter carpet's width and height: ";
    get_size(carpet_size);

    for(auto part : carpet_size) {
        if(part < 2) {
            std::cout << " Error: Carpet cannot be smaller than pattern."
                      << std::endl;
            return EXIT_FAILURE;
        }
    }

    while(not is_carpet_init) {
        ask_start(start);
        if(start == 'R') {
            ask_seed(seed);
            init_carpet_random(seed, carpet_size, carpet, is_carpet_init);
        }
        else if(start == 'I') {
            std::cout << "Input: ";
            std::cin >> input;
            init_carpet_input(carpet_size, carpet, is_carpet_init, input);
        }
    }

    for( int i = 0; i < carpet_size[1]; i++) {
        for( auto part : carpet[i]) {
            std::cout << " " << part;
        }
        std::cout << std::endl;
    }

    while(true) {
        std::cout << "Enter 4 colors, or q to quit: ";
        std::cin >> colors_to_find;
        int colors_to_find_length = colors_to_find.length();

        for(int i = 0; i < colors_to_find_length; i++) {
            colors_to_find[i] = toupper(colors_to_find[i]);
        }
        if(colors_to_find == "Q") {
            break;
        }
        else if(colors_to_find_length != 4) {
            std::cout << " Error: Wrong amount of colors." << std::endl;
            continue;
        }
        if(check_colors(colors_to_find)) {
            find_colors(carpet, carpet_size, colors_to_find);
        }
    }
}
