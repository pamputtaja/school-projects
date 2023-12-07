#include <iostream>
#include <fstream>
#include <string>

int main()
{
    std::string input_filename = "";
    std::string output_filename= "";

    std::cout << "Input file: ";
    getline(std::cin, input_filename);

    std::cout << "Output file: ";
    getline(std::cin, output_filename);

    std::ifstream file_in(input_filename);
    if ( not file_in) {
        std::cout << "Error! The file " << input_filename << " cannot be opened." << std::endl;
        return EXIT_FAILURE;
    } else {
        std::ofstream file_out(output_filename);
        int line_number = 1;
        std::string line;
        while ( getline(file_in, line) ) {
            file_out << line_number << " " << line << std::endl;
            line_number++;
        }
        file_in.close();
        file_out.close();
    }
    return 0;
}
