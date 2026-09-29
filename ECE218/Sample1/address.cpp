#include "address.h"

// definition of default constructor
// using an initializer list to set the defaults
// "--" is not a valid state, so a default Address is not valid
// until the real data is set
Address::Address() : street("none"), unit(""), city("none"),
                     state("--"), zip("00000") {}

// definition of constructor - address with no unit
// param: street : string - house number and street name
// param: city : string - city name
// param: state : string - 2 letter state code
// param: zip : string - zip or zip+4
Address::Address(std::string street, std::string city,
                 std::string state, std::string zip)
    : street(street), unit(""), city(city), state(state), zip(zip) {}

// definition of constructor - address with a unit
// param: street : string - house number and street name
// param: unit : string - apt / suite / room
// param: city : string - city name
// param: state : string - 2 letter state code
// param: zip : string - zip or zip+4
Address::Address(std::string street, std::string unit, std::string city,
                 std::string state, std::string zip)
    : street(street), unit(unit), city(city), state(state), zip(zip) {}

// copy constructor
// makes a new Address with the same data as other
// all members are std::string, so copying each one is a full copy
// (no pointers, so no deep copy code is needed)
// param: other : const Address& - address to copy
Address::Address(const Address &other)
    : street(other.street), unit(other.unit), city(other.city),
      state(other.state), zip(other.zip) {}

// assignment operator
// copies the data of other into this Address
// param: other : const Address& - address to copy
// return: Address& - this Address, so a = b = c works
Address& Address::operator=(const Address &other) {
    if (this != &other) {      // a = a: nothing to do
        street = other.street;
        unit = other.unit;
        city = other.city;
        state = other.state;
        zip = other.zip;
    }
    return *this;
}

// destructor
// do not need code, all members are std::string
// and clean up after themselves
Address::~Address() {}

// get the street
// param: none
// return: string - street (line 1)
std::string Address::getStreet() const {
    return street;
}

// get the unit
// param: none
// return: string - unit (line 2), "" if none
std::string Address::getUnit() const {
    return unit;
}

// get the city
// param: none
// return: string - city
std::string Address::getCity() const {
    return city;
}

// get the state
// param: none
// return: string - 2 letter state code
std::string Address::getState() const {
    return state;
}

// get the zip
// param: none
// return: string - zip or zip+4
std::string Address::getZip() const {
    return zip;
}

// set the street
// param: street : string - house number and street name
// return: none
void Address::setStreet(std::string street) {
    this->street = street;
}

// set the unit
// param: unit : string - apt / suite / room, "" for none
// return: none
void Address::setUnit(std::string unit) {
    this->unit = unit;
}

// set the city
// param: city : string - city name
// return: none
void Address::setCity(std::string city) {
    this->city = city;
}

// set the state
// param: state : string - 2 letter state code
// return: none
void Address::setState(std::string state) {
    this->state = state;
}

// set the zip
// param: zip : string - zip or zip+4
// return: none
void Address::setZip(std::string zip) {
    this->zip = zip;
}

// check the state: exactly 2 uppercase letters, e.g. FL
// only checks the format, not that the state really exists
// param: none
// return: bool - true if the format is ok
bool Address::validState() const {
    if (state.length() != 2)
        return false;
    for (std::string::size_type i=0; i<state.length(); i++) {
        if (state[i] < 'A' || state[i] > 'Z')
            return false;
    }
    return true;
}

// check the zip: NNNNN or NNNNN-NNNN
// param: none
// return: bool - true if the format is ok
bool Address::validZip() const {
    if (zip.length() != 5 && zip.length() != 10)
        return false;
    for (std::string::size_type i=0; i<zip.length(); i++) {
        if (i == 5) {
            // zip+4: the 6th character must be the dash
            if (zip[i] != '-')
                return false;
        } else if (zip[i] < '0' || zip[i] > '9') {
            return false;
        }
    }
    return true;
}

// check that the address is complete and well formed
// unit is optional so it is not checked
// param: none
// return: bool - true if the address is valid
bool Address::isValid() const {
    return !street.empty() && !city.empty() && validState() && validZip();
}

// print the address to output stream, US mailing label format
// the unit line is only printed if there is one
// param: out : ostream& - reference to output stream
// return: ostream& - output stream
std::ostream& Address::print(std::ostream &out) const {
    out << street << std::endl;
    if (!unit.empty())
        out << unit << std::endl;
    out << city << ", " << state << " " << zip << std::endl;
    return out;
}

// output operator, so we can write: std::cout << address;
// param: out : ostream& - reference to output stream
// param: a : const Address& - address to print
// return: ostream& - output stream
std::ostream& operator<<(std::ostream &out, const Address &a) {
    return a.print(out);
}
