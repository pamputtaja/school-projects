#include <iostream>


int main()
{
    int numbers;
    std::cout << "How many numbers would you like to have? ";
    std::cin >> numbers;

    for (int i = 1; i <= numbers; i++) {
        if (i % 3 == 0 && i % 7 == 0) {
            std::cout << "zip boing" << std::endl;
        }
        if (i % 3 == 0 && i % 7 != 0) {
            std::cout << "zip" << std::endl;
        }
        if (i % 7 == 0 && i % 3 != 0) {
            std::cout << "boing" << std::endl;
        }
        if (i % 3 != 0 && i % 7 != 0) {
            std::cout << i << std::endl;
        }
    }

    return 0;
}
