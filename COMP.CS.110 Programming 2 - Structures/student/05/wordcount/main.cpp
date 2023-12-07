#include <iostream>
#include <map>
#include <fstream>
#include <string>
#include <algorithm>
#include <set>
#include <vector>
#include <utility>

std::map<std::string, std::vector<int>> splitter(std::map<std::string, std::vector<int>> &words, std::string const &line, int const &row)
{
    char sep = ' ';

    std::string temp = line;
    std::string word = "";
    int row_number = row;
    std::vector<int> rows;

    while (temp.find(sep) != std::string::npos) {
        word = temp.substr(0, temp.find(sep));
        temp = temp.substr(temp.find(sep)+1, std::string::npos);
        if ( words.find(word) != words.end() ) {
            words.at(word).push_back(row_number);
        } else {
            std::vector<int> rows;
            rows.push_back(row_number);
            words.insert(make_pair(word, rows));
            rows.clear();
        }
    }
    if ( words.find(temp) != words.end() ) {
        words.at(temp).push_back(row_number);
    } else {
        std::vector<int> rows_2;
        rows_2.push_back(row_number);
        words.insert(make_pair(temp, rows_2));
        rows_2.clear();
    }
    return words;
}




int main()
{
    std::string input_filename = "";
    std::map<std::string, std::vector<int>> words;




    std::cout << "Input file: ";
    getline(std::cin, input_filename);

    std::ifstream file_in(input_filename);
    if ( not file_in) {
        std::cout << "Error! The file " << input_filename << " cannot be opened." << std::endl;
        return EXIT_FAILURE;
    } else {
        std::string line;
        std::string word;
        int row = 1;
        while ( getline(file_in, line )) {
            splitter(words, line, row);
            row = row + 1;
        }
    }
    for ( auto data : words) {
        int i = 0;
        int size = data.second.size();
        std::cout << data.first << " " << data.second.size() << ": ";
        while (i < size) {
            if (i+1 == size) {
                std::cout << data.second.at(i);
            } else {
                std::cout << data.second.at(i) << ", ";
            }
            i++;
        }
        std::cout << std::endl;
    }
    return 0;
}

