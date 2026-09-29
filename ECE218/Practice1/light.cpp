#include "light.h"

// definition of default constructor
// using an initializer list to set the defaults
// state = false means every new light starts OFF (UML: state: bool = false)
Light::Light() : id(-1), name("none"), state(false) {}

// definition of constructor with id and name
// using an initializer list to set the data
// the light still starts OFF
// param: id : int - light id to set
// param: name : string - light name to set
Light::Light(int id, std::string name) : id(id), name(name), state(false) {}

// destructor
// do not need code
Light::~Light() {}

// turn the light ON
// param: none
// return: int - 0 on success (turning a light ON cannot fail)
int Light::setOn() {
    state = true;
    return 0;
}

// turn the light OFF
// param: none
// return: int - 0 on success (turning a light OFF cannot fail)
int Light::setOff() {
    state = false;
    return 0;
}

// check if the light is ON
// param: none
// return: bool - true if the light is ON, false if it is OFF
bool Light::isOn() {
    return state;
}

// get the light id
// param: none
// return: int - light id
int Light::getId() {
    return id;
}

// set the light id
// param: id : int - light id to set
// return: none
void Light::setId(int id) {
    this->id = id;
}

// get the light name
// param: none
// return: string - light name
std::string Light::getName() {
    return name;
}

// set the light name
// param: name : string - light name to set
// return: none
void Light::setName(std::string name) {
    this->name = name;
}

// print the data to output stream
// param: out : ostream& - reference to output stream
// return: ostream& - output stream
std::ostream& Light::print(std::ostream &out) {
    out << "Light ID: " << id;
    out << "  name: " << name;
    if (state) {
        out << "  state: ON" << std::endl;
    } else {
        out << "  state: OFF" << std::endl;
    }
    return out;
}
