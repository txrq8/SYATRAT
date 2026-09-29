#include "customer.h"

// definition of constructor
// using an initializer list to set the data
// home(home) copies the Address using the Address copy constructor
// param: name : string - customer name
// param: phone : string - customer phone number
// param: home : Address - home address (passed by value, so it is a copy)
Customer::Customer(std::string name, std::string phone, Address home)
    : name(name), phone(phone), home(home) {}

// destructor
// do not need code, name, phone and home clean up after themselves
Customer::~Customer() {}

// print the data to output stream
// the Address prints itself, Customer does not need to know
// how an address is laid out
// param: out : ostream& - reference to output stream
// return: ostream& - output stream
std::ostream& Customer::print(std::ostream &out) const {
    out << "Customer name: " << name << std::endl;
    out << "Customer phone: " << phone << std::endl;
    out << "Customer address:" << std::endl;
    home.print(out);
    return out;
}
