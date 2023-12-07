#include <iostream>

int main()
{
    int number;
    int cube;

    std::cout << "Enter a number: ";
    std::cin >> number;
    cube = number * number * number;
    if (cube < 0 or (cube/number)/number != number) {
        std::cout << "Error! The cube of " << number << " is not " << cube << "." << std::endl;
    } else {
        std::cout << "The cube of " << number << " is " << cube << "." << std::endl;
    }

}
