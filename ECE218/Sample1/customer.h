#ifndef CUSTOMER_H_
#define CUSTOMER_H_

#include <iostream>
#include <string>

// Customer holds an Address object (not a pointer), so the compiler
// needs the full Address class here - a forward declaration
// (class Address;) is NOT enough
#include "address.h"

class Customer {
    private:
        std::string name;    // customer name
        std::string phone;   // customer phone number
        Address home;        // home address (Customer has-a Address)

    public:
        // constructor
        Customer(std::string name, std::string phone, Address home);

        // destructor
        virtual ~Customer();

        // print the customer: name, phone and address
        std::ostream& print(std::ostream&) const;

};

#endif
