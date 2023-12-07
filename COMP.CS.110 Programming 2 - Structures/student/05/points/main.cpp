#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <map>

int main()
{
    std::string input_filename = "";
    std::string name;
    std::string::size_type splitter = 0;
    std::map< std::string, int > players_points;

    std::cout << "Input file: ";
    getline(std::cin, input_filename);

    std::ifstream file_in(input_filename);
    if ( not file_in) {
        std::cout << "Error! The file " << input_filename << " cannot be opened." << std::endl;
        return EXIT_FAILURE;
    } else {
        std::string line;
        std::string line_2;
        int points;
        while ( getline(file_in, line )) {
            line_2 = line;
            splitter = line.find(":");
            name = line.replace(splitter, line.length()-splitter, "");
            points = std::stoi(line_2.substr(splitter+1, line_2.length()-splitter));
            if ( players_points.find(name) != players_points.end() ) {
                players_points.at(name) = players_points.at(name) + points;
            } else {
                players_points.insert( std::pair< std::string, int >(name, points) );
            }
        }
        file_in.close();
        std::cout << "Final scores:" << std::endl;
        for (auto data : players_points) {
            std::cout << data.first << ": " << data.second << std::endl;
        }
    }
    return 0;
}
