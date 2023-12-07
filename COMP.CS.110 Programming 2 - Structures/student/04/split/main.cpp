#include <iostream>
#include <string>
#include <vector>


// TODO: Implement split function here
// Do not change main function
std::vector< std::string > split(std::string line, char separator, bool ignore_empty = false)
{
    std::string temp = "";
    std::vector< std::string > line_splitted;

    // ei toimi
    //std::string::size_type length;
    //length = line.length();

    int length = line.length();

    for(int i = 0; i <= length; i++ ) {
        if(not ignore_empty) {
            if(i == length) {
                line_splitted.push_back(temp);
                temp = "";
                continue;
            } else if(line[i] == separator) {
                if(line[i+1] == separator) {
                    line_splitted.push_back(temp);
                    temp = "";
                    continue;
                }
                line_splitted.push_back(temp);
                temp = "";
                continue;
            }
            temp = temp + line[i];
        }
        if(ignore_empty) {
            if(i == length) {
                line_splitted.push_back(temp);
                temp = "";
                continue;
            } else if(i == length and line[i] == separator) {
                line_splitted.push_back(temp);
            } else if(i == 0 and line[i] == separator) {
                continue;
            } else if(i != 0 and line[i] == separator) {
                if(line[i-1] == separator) {
                    continue;
                }
                line_splitted.push_back(temp);
                temp = "";
                continue;
            }
            temp = temp + line[i];
        }
    }
    if(ignore_empty) {
        line_splitted.pop_back();
    }
    return line_splitted;
}


int main()
{
    std::string line = "";
    std::cout << "Enter a string: ";
    getline(std::cin, line);
    std::cout << "Enter the separator character: ";
    char separator = getchar();

    std::vector< std::string > parts  = split(line, separator);
    std::cout << "Splitted string including empty parts: " << std::endl;
    for( auto part : parts ) {
        std::cout << part << std::endl;
    }

    std::vector< std::string > parts_no_empty  = split(line, separator, true);
    std::cout << "Splitted string ignoring empty parts: " << std::endl;
    for( auto part : parts_no_empty ) {
        std::cout << part << std::endl;
    }
}
