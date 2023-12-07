#include "account.hh"
#include <iostream>

Account::Account(const std::string& owner, bool has_credit):
    owner_(owner), has_credit_(has_credit)
{
    generate_iban();
}

// Setting initial value for the static attribute running_number_
int Account::running_number_ = 0;

void Account::generate_iban()
{
    ++running_number_;
    std::string suffix = "";
    if(running_number_ < 10)
    {
        suffix.append("0");
    }
    else if(running_number_ > 99)
    {
        std::cout << "Too many accounts" << std::endl;
    }
    suffix.append(std::to_string(running_number_));

    iban_ = "FI00 1234 ";
    iban_.append(suffix);
}

void Account::set_credit_limit(int limit) {
    if (Account::has_credit_ != true) {
        std::cout << "Cannot set credit limit: "
                     "the account has no credit card" << std::endl;
    } else {
        credit_limit = limit;
    }

}

void Account::print() const {
    std::cout << owner_ << " : "
              << iban_ << " : "
              << balance << " euros" << std::endl;
}

void Account::save_money(int amount) {
    balance = amount;
}

bool Account::take_money(int amount) {
    if (balance - amount < 0) {
        if (has_credit_) {
            if (balance - amount < credit_limit*-1) {
                std::cout << "Cannot take money: credit limit underflow"
                          << std::endl;
                return false;
            } else {
                balance -= amount;
                std::cout << amount << " euros taken: new balance of " << iban_
                          << " is " << balance << std::endl;
                return true;
            }
        }
        std::cout << "Cannot take money: balance underflow"
                  << std::endl;
        return false;
    }
    balance -= amount;
    std::cout << amount << " euros taken: new balance of " << iban_
    << " is " << balance << std::endl;
    return true;
}

bool Account::transfer_to(Account& destination, int amount) {
    if (balance - amount < 0) {
        if (has_credit_) {
            if (balance - amount < credit_limit*-1) {
                std::cout << "Cannot take money: credit limit underflow"
                          << std::endl;
                std::cout << "Transfer from " << iban_ << " failed"
                          << std::endl;
                return false;
            } else {
                balance -= amount;
                destination.balance += amount;
                std::cout << amount << " euros taken: new balance of "
                          << destination.iban_ << " is " << balance
                          << std::endl;
                return true;
            }
        }
        std::cout << "Cannot take money: balance underflow"
                  << std::endl;
        std::cout << "Transfer from " << iban_ << " failed" << std::endl;
        return false;
    }
    balance -= amount;
    destination.balance += amount;
    std::cout << amount << " euros taken: new balance of " << destination.iban_
              << " is " << balance << std::endl;
    return true;
}
