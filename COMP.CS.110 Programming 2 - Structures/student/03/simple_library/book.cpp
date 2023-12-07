#include "book.hh"
#include <iostream>


Book::Book(std::string author, std::string title):
    author_(author), title_(title) {

}

void Book::print()
{
    std::cout << author_ << " : " << title_ << std::endl;
    if (is_avail) {
        std::cout << "- available" << std::endl;
    } else {
        std::cout << "- loaned: ";
        loan_date.print();
        std::cout << "- to be returned: ";
        due_date.print();
    }
}

void Book::loan(Date &today) {
    if (is_avail) {
        loan_date = today;
        due_date = today;
        due_date.advance(28);
        is_avail = false;
    } else {
        std::cout << "Already loaned: cannot be loaned" << std::endl;
    }
}

void Book::renew() {
    if (is_avail) {
        std::cout << "Not loaned: cannot be renewed" << std::endl;
    } else {
        due_date.advance(28);
    }
}

void Book::give_back() {
    is_avail = true;
}

