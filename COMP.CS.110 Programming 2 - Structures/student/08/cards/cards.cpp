#include "cards.hh"

// TODO: Implement the methods here

Cards::Cards():
    top_(nullptr)
{

}

Card_data *Cards::get_topmost()
{
    return top_;
}

void Cards::add(int id)
{
    Card_data *new_card = new Card_data;
    new_card->data = id;
    new_card->next = top_;
    top_ = new_card;
}

void Cards::print_from_top_to_bottom(std::ostream &s)
{
    Card_data *current_card = top_;
    int i = 1;
    while ( current_card != nullptr ) {
        s << i << ": " << current_card->data << std::endl;
        current_card = current_card->next;
        i++;
    }
}

bool Cards::remove(int &id)
{
    if ( top_ == nullptr ) {
        return false;
    }
    Card_data *temp = top_;
    top_ = top_->next;
    id = temp->data;
    delete temp;
    return true;
}

bool Cards::bottom_to_top()
{
    if ( top_ == nullptr ) { return false; }
    Card_data *last = top_;
    Card_data *second_last = top_;
    while ( last->next != nullptr ) {
        second_last = last;
        last = last->next;
    }
    second_last->next = nullptr;
    last->next = top_;
    top_ = last;
    return true;
}

bool Cards::top_to_bottom()
{
    if ( top_ == nullptr ) { return false; }
    Card_data *temp = top_;
    Card_data *last = top_;
    top_ = top_->next;
    while (last->next != nullptr ) {
        last = last->next;
    }
    last->next = temp;
    temp->next = nullptr;
    return true;
}

void Cards::print_from_bottom_to_top(std::ostream &s)
{
    s << std::endl;
}

Cards::~Cards()
{
    Card_data *temp = top_;
    while ( top_ != nullptr ) {
        top_ = top_->next;
        delete temp;
        temp = top_;
    }
}

int Cards::recursive_print(Card_data *top, std::ostream &s)
{
    if ( top == nullptr ) {
        s << std::endl;
    }
    return 0;
}

