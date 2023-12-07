#include "course.hh"
#include "account.hh"
#include <iostream>

Course::Course(const std::string& code, const std::string& name, int credits):
    course_code_(code), name_(name), credits_(credits)
{
}

Course::~Course()
{
}

void Course::print_info(bool print_new_line)
{
    std::cout << course_code_ << " : " << name_;
    if ( print_new_line )
    {
        std::cout << std::endl;
    }
}

void Course::print_long_info()
{
    std::cout << "* Course name: " << name_ << std::endl
              << "* Code: " << course_code_ << std::endl;
    print_staff();
}

void Course::print_staff()
{
    std::cout << "* Staff: " << std::endl;
    for (auto member : course_staff_ )
    {
        member->print();
    }
}

void Course::add_staff(Account *new_staff_member)
{
    // Checking if account is already a staff member
    for ( unsigned int i = 0; i < course_staff_.size(); ++i )
    {
        if ( course_staff_.at(i) == new_staff_member )
        {
            std::cout << STAFF_EXISTS << std::endl;
            return;
        }
    }

    course_staff_.push_back(new_staff_member);
    std::cout << STAFF_ADDED << std::endl;
}

const std::string Course::get_code() const
{
    return course_code_;
}

int Course::get_credits() const
{
    return credits_;
}

void Course::add_student(Account *new_student)
{
    for( unsigned int i = 0; i < attendance_.size(); i++) {
        if( attendance_.at(i) == new_student) {
            return;
        }
    }
    attendance_.push_back(new_student);
}

void Course::get_sign_ups() const
{
    for( unsigned int i = 0; i < attendance_.size(); i++ ) {
        std::cout << attendance_.at(i)->get_account_number() << ": "
                  << attendance_.at(i)->get_full_name() << ", "
                  << attendance_.at(i)->get_email() << std::endl;
    }
}






