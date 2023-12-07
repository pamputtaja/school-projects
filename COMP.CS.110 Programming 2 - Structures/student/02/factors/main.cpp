#include <iostream>

int main()
{
    int input;
    int factor_1 = 0;
    int factor_2 = 0;
    int multi = 0;

    std::cout << "Enter a positive number: ";
    std::cin >> input;
    if (input < 1) {
        std::cout << "Only positive numbers accepted" << std::endl;
        return 0;
    }

    // test when n times n goes over input
    while (multi < input) {
        factor_1++;
        multi = factor_1 * factor_1;
        if (factor_1 * factor_1 == input) {
            break;
        }
    }

    // using n as a base to start searching smallest two factors by lowering
    // other value and raising other
    factor_2 = factor_1;
    while (multi != input) {
        factor_1--;
        if (factor_1 == 0) {
            factor_1 = 1;
        }
        multi = factor_1 * factor_2;
        if ( multi == input) {
            break;
        }
        factor_2++;
        multi = factor_1 * factor_2;
        if ( multi == input) {
            break;
        }
    }

    std::cout << input << " = " << factor_1 << " * "
              << factor_2 << std::endl;
    return 0;
}
