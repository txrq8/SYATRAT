#ifndef ADDRESS_H_
#define ADDRESS_H_

#include <iostream>
#include <string>

// US style mailing address
// example:
//     123 Main Street        <- street (line 1)
//     Apt 4B                 <- unit   (line 2, optional)
//     Miami, FL 33146        <- city, state zip
class Address {
    private:
        std::string street;   // line 1: house number and street name
        std::string unit;     // line 2: apt / suite / room, "" if none
        std::string city;     // city name
        std::string state;    // 2 letter USPS state code, e.g. FL
        std::string zip;      // 5 digit zip (33146) or zip+4 (33146-0620)

        // check the state format
        bool validState() const;

        // check the zip format
        bool validZip() const;

    public:
        // default constructor
        // needed so an Address can be created with no data
        // (e.g. an array of Address, or a class member not in an initializer list)
        Address();

        // constructor - address with no unit (line 2)
        Address(std::string street, std::string city,
                std::string state, std::string zip);

        // constructor - address with a unit (line 2)
        Address(std::string street, std::string unit, std::string city,
                std::string state, std::string zip);

        // destructor
        virtual ~Address();

        // get the data
        std::string getStreet() const;
        std::string getUnit() const;
        std::string getCity() const;
        std::string getState() const;
        std::string getZip() const;

        // set the data
        void setStreet(std::string);
        void setUnit(std::string);
        void setCity(std::string);
        void setState(std::string);
        void setZip(std::string);

        // check that the address is complete and well formed
        bool isValid() const;

        // print the address
        std::ostream& print(std::ostream&) const;

};

// output operator, so we can write: std::cout << address;
std::ostream& operator<<(std::ostream&, const Address&);

#endif
