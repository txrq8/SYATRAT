#include <iostream>
#include <string>

// both headers include address.h - the include guards
// stop the Address class from being defined twice
#include "address.h"
#include "customer.h"

int main(int argc, char *argv[]) {

    // 2 arguments
    // 1. customer name
    // 2. customer phone
    if (argc!=3) {
        std::cerr << "Usage: " << argv[0] << " <name> <phone>\n";
        return -1;
    }

    // create an Address with the default constructor
    Address blank;
    std::cout << "+++++++++++++++++++++++++++++++++\n";
    std::cout << "default Address:\n";
    blank.print(std::cout);
    std::cout << "valid: " << (blank.isValid() ? "yes" : "no") << std::endl;

    // create an Address with the full constructor (with a unit)
    Address a("123 Main Street", "Apt 4B", "Miami", "FL", "33146");
    std::cout << "+++++++++++++++++++++++++++++++++\n";
    std::cout << "Address a:\n";
    std::cout << a;    // same as a.print(std::cout)
    std::cout << "valid: " << (a.isValid() ? "yes" : "no") << std::endl;

    // create a Customer from the command line and Address a
    // a is passed by value, so c1 gets its own copy in home
    Customer c1(argv[1], argv[2], a);
    std::cout << "+++++++++++++++++++++++++++++++++\n";
    std::cout << "Customer c1:\n";
    c1.print(std::cout);

    // change Address a - c1 does not change
    // because c1.home is a copy, not the same object
    a.setStreet("500 Ocean Drive");
    a.setUnit("");
    a.setZip("33139-1234");
    std::cout << "+++++++++++++++++++++++++++++++++\n";
    std::cout << "Address a after the set calls:\n";
    a.print(std::cout);
    std::cout << "valid: " << (a.isValid() ? "yes" : "no") << std::endl;
    std::cout << "Customer c1 is unchanged:\n";
    c1.print(std::cout);

    // copy a Customer with the (compiler supplied) copy constructor
    Customer c2(c1);
    std::cout << "+++++++++++++++++++++++++++++++++\n";
    std::cout << "Customer c2 (copy of c1):\n";
    c2.print(std::cout);

    // copy a Customer with the (compiler supplied) assignment operator
    Customer c3("John Doe", "305-555-0199",
                Address("1 Palm Avenue", "Orlando", "FL", "32801"));
    std::cout << "+++++++++++++++++++++++++++++++++\n";
    std::cout << "Customer c3 before c3 = c1:\n";
    c3.print(std::cout);
    c3 = c1;
    std::cout << "Customer c3 after c3 = c1:\n";
    c3.print(std::cout);

    // an Address with a bad state and a bad zip
    Address bad("9 Elm Street", "Miami", "Florida", "3314");
    std::cout << "+++++++++++++++++++++++++++++++++\n";
    std::cout << "Address bad:\n";
    bad.print(std::cout);
    std::cout << "valid: " << (bad.isValid() ? "yes" : "no") << std::endl;
    std::cout << "+++++++++++++++++++++++++++++++++\n";

    return 0;
}
