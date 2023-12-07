#ifndef BOOK_HH
#define BOOK_HH

#include <date.hh>
#include <string>

class Book {
public:
    Book(std::string author, std::string title);
    void print();
    void loan(Date& today);
    void renew();
    void give_back();

private:
    std::string author_;
    std::string title_;
    bool is_avail = true;
    Date loan_date;
    Date due_date;

};

#endif // BOOK_HH
