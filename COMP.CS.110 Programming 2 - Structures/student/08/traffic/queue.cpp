#include "queue.hh"
#include <iostream>
#include <string>

// Implement the member functions of Queue here

Queue::Queue(unsigned int cycle): cycle_(cycle)
{

}

Queue::~Queue()
{
    while ( first_ != nullptr ) {
        Vehicle* vehicle_to_be_destroyed = first_;
        first_ = first_->next;
        delete vehicle_to_be_destroyed;
    }
}

void Queue::enqueue(const string &reg)
{
    if ( is_green_ ) {
        std::cout << "GREEN: The vehicle " << reg << " need not stop to wait"
                  << std::endl;
    } else {
        if ( first_ == nullptr ) {
            Vehicle* new_vehicle = new Vehicle{reg, nullptr};
            first_ = new_vehicle;
            last_ = new_vehicle;
        } else {
            Vehicle* new_vehicle = new Vehicle{reg, nullptr};
            last_->next = new_vehicle;
            last_ = new_vehicle;

        }
    }

}

void Queue::switch_light()
{
    std::string color;
    if ( is_green_ ) {
        is_green_ = false;
        color = "RED";
    } else {
        is_green_ = true;
        color = "GREEN";
    }
    unsigned int vehicles_to_pass = cycle_;
    if ( first_ == nullptr ) {
        std::cout << color << ": No vehicles waiting in traffic lights"
                  << std::endl;
    } else {
        std::cout << "GREEN: Vehicle(s) ";
        for (unsigned int i = 1; i <= vehicles_to_pass; i++ ) {
            if ( first_ == nullptr ) { break; }
            dequeue(first_->reg_num);
        }
        std::cout << "can go on" << std::endl;
        is_green_ = false;
    }
}
void Queue::reset_cycle(unsigned int cycle)
{
    cycle_ = cycle;
}

void Queue::print() const
{
    std::string color;
    Vehicle* vehicle_to_be_printed = first_;
    if ( is_green_ ) {
        color = "GREEN";
    } else {
        color = "RED";
    }
    if ( first_ == nullptr ) {
        std::cout << color << ": No vehicles waiting in traffic lights"
                  << std::endl;
    } else {
        std::cout << color << ": " << "Vehicle(s) ";
        while ( vehicle_to_be_printed != nullptr ) {
            std::cout <<  vehicle_to_be_printed->reg_num << " ";
            vehicle_to_be_printed = vehicle_to_be_printed->next;

        }
        std::cout << "waiting in traffic lights" << std::endl;
    }


}


void Queue::dequeue(const string &reg)
{
    Vehicle* new_first = first_->next;
    Vehicle* vehicle_to_pass = first_;
    std::cout << reg << " ";
    delete vehicle_to_pass;
    first_ = new_first;
}

