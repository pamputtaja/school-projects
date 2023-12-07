#include "account.hh"
#include "utils.hh"
#include "course.hh"
#include <iostream>

Account::Account(const std::string& full_name, int account_number,
                 int duplicates, const std::string& university_suffix):
    full_name_(full_name),
    last_name_(""),
    first_name_(""),
    account_number_(account_number)
{
    std::vector<std::string> name = Utils::split(full_name_, ' ');
    last_name_ = name.back();
    first_name_ = name.front();

    // Constructing e-mail address
    email_ = Utils::to_lower(first_name_);
    email_ += ".";
    if ( duplicates > 0 )
    {
        email_ += std::to_string(duplicates);
        email_ += ".";
    }
    email_ += Utils::to_lower(last_name_);
    email_ += "@";
    email_ += university_suffix;
}

Account::~Account()
{
}

void Account::print() const
{
    std::cout << account_number_ << ": "
              << first_name_ << " "
              << last_name_  << ", "
              << email_ << std::endl;
}

std::string Account::get_email() const
{
    return email_;
}

std::string Account::get_full_name() const
{
    return full_name_;
}

int Account::get_account_number() const
{
    return account_number_;
}

void Account::add_course(Course* new_course)
{
    for(unsigned int i = 0; i < completed_courses.size(); i++) {
        if( completed_courses.at(i) == new_course ) {
            std::cout << STUDENT_COMPLETED << std::endl;
            return;
        }
    }
    for(unsigned int i = 0; i < ongoing_courses.size(); i++) {
        if( ongoing_courses.at(i) == new_course ) {
            std::cout << STUDENT_EXISTS << std::endl;
            return;
        }
    }

    ongoing_courses.push_back(new_course);
    std::cout << SIGNED_UP << std::endl;
}

void Account::make_completed(Course* course)
{
    for( unsigned int i = 0; i < ongoing_courses.size(); i++ ) {
        if( ongoing_courses.at(i) == course ) {
            completed_courses.push_back(ongoing_courses.at(i));
            ongoing_courses.erase(ongoing_courses.begin()+i);
            std::cout << COMPLETED << std::endl;
            return;
        }
    }
    std::cout << NO_SIGNUPS << std::endl;
}

void Account::print_completed() const
{
    int credits = 0;
    for( unsigned int i = 0; i < completed_courses.size(); i++ ) {
        completed_courses.at(i)->print_info(true);
        credits = credits + completed_courses.at(i)->get_credits();
    }
    std::cout << "Total credits: " << credits << std::endl;
}

void Account::print_study_state() const
{
    int credits = 0;

    std::cout << "Current:" << std::endl;
    for( unsigned int i = 0; i < ongoing_courses.size(); i++ ) {
        ongoing_courses.at(i)->print_info(true);
    }

    std::cout << "Completed:" << std::endl;
    for( unsigned int i = 0; i < completed_courses.size(); i++ ) {
        completed_courses.at(i)->print_info(true);
        credits = credits + completed_courses.at(i)->get_credits();
    }
    std::cout << "Total credits: " << credits << std::endl;
}

void Account::graduate()
{
    if( graduated == true ) {
        std::cout << GRADUATED << std::endl;
        return;
    }
    for( unsigned int i = 0; i < ongoing_courses.size(); i++ ) {
        completed_courses.push_back(ongoing_courses.at(i));
    }
    ongoing_courses.clear();
    graduated = true;
    std::cout << GRADUATED << std::endl;
}

bool Account::check_graduated() const
{
    if( graduated ) {
        return true;
    }
    return false;
}
