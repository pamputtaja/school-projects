#include <iostream>

int main()
{
    double input;
    double celsius;
    double fahrenheit;


    std::cout << "Enter a temperature: ";
    std::cin >> input;

    fahrenheit = input*1.8 + 32;
    celsius = (input - 32)/1.8;

    std::cout << input << " degrees Celsius is " << fahrenheit
              << " degrees Fahrenheit" << std::endl;
    std::cout << input << " degrees Fahrenheit is " << celsius
              << " degrees Celsius" << std::endl;

    return 0;
}
