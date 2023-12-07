#include <iostream>

unsigned long int calc_factorial(unsigned long int number);

int main()
{
    int total;
    int balls;
    unsigned long int odds;

    unsigned long int total_factorial;
    unsigned long int balls_factorial;
    unsigned long int total_balls_factorial;

    std::cout << "Enter the total number of lottery balls: ";
    std::cin >> total;
    std::cout << "Enter the number of drawn balls: ";
    std::cin >> balls;

    if (total <= 0 || balls <= 0) {
        std::cout << "The number of balls must be a positive number."
                  << std::endl;
        return 0;
    }
    if (total < balls) {
        std::cout << "The maximum number of drawn balls is the total "
                     "amount of balls." << std::endl;
        return 0;
    }
    if (balls == total) {
        std::cout << "The probability of guessing all " << balls
                  << " balls correctly is 1/1" << std::endl;
        return 0;
    }
    total_factorial = calc_factorial(total);
    balls_factorial = calc_factorial(balls);
    total_balls_factorial = calc_factorial(total-balls);
    odds = total_factorial / (total_balls_factorial * balls_factorial);
    std::cout << "The probability of guessing all " << balls
              << " balls correctly is 1/" << odds << std::endl;
    return 0;
}

unsigned long int calc_factorial(unsigned long int number) {
    unsigned long int i = 1;
    unsigned long int temp = number;
    while (i < number) {
        temp = temp * (number-i);
        i++;
    }
    return temp;
}

