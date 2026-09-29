#include "room.h"

// definition of default constructor
// using an initializer list to set the defaults
// the array lights[MAX_LIGHTS] does not appear in the list:
// C++ calls Light() for every element, so each light starts id -1, "none", OFF
Room::Room() : id(-1), name("none"), location("none"), numLights(0) {}

// definition of constructor with id, name and location
// using an initializer list to set the data
// the room starts with no lights in use
// param: id : int - room id to set
// param: name : string - room name to set
// param: location : string - room location to set
Room::Room(int id, std::string name, std::string location)
    : id(id), name(name), location(location), numLights(0) {}

// destructor
// do not need code (lights is an array, not memory from new)
Room::~Room() {}

// turn ON the light at index
// param: index : int - index of the light (0 .. numLights-1)
// return: int - 0 on success, -1 if index is invalid
int Room::setLightOn(int index) {
    if (index < 0 || index >= numLights) {
        return -1;
    }
    return lights[index].setOn();
}

// turn OFF the light at index
// param: index : int - index of the light (0 .. numLights-1)
// return: int - 0 on success, -1 if index is invalid
int Room::setLightOff(int index) {
    if (index < 0 || index >= numLights) {
        return -1;
    }
    return lights[index].setOff();
}

// get the room id
// param: none
// return: int - room id
int Room::getId() {
    return id;
}

// set the room id
// param: id : int - room id to set
// return: none
void Room::setId(int id) {
    this->id = id;
}

// get the room name
// param: none
// return: string - room name
std::string Room::getName() {
    return name;
}

// set the room name
// param: name : string - room name to set
// return: none
void Room::setName(std::string name) {
    this->name = name;
}

// get the room location
// param: none
// return: string - room location
std::string Room::getLocation() {
    return location;
}

// set the room location
// param: location : string - room location to set
// return: none
void Room::setLocation(std::string location) {
    this->location = location;
}

// get the number of lights in use
// param: none
// return: int - number of lights in use
int Room::getNumLights() {
    return numLights;
}

// set the number of lights in use
// param: numLights : int - number of lights (0 .. MAX_LIGHTS)
// return: int - 0 on success, -1 if numLights is out of range (not changed)
int Room::setNumLights(int numLights) {
    if (numLights < 0 || numLights > MAX_LIGHTS) {
        return -1;
    }
    this->numLights = numLights;
    return 0;
}

// get a copy of the light at index
// param: index : int - index of the light (0 .. numLights-1)
// return: Light - copy of the light, or a default Light (id -1) if index is invalid
Light Room::getLight(int index) {
    if (index < 0 || index >= numLights) {
        return Light();
    }
    return lights[index];
}

// replace the light at index
// param: index : int - index of the light (0 .. numLights-1)
// param: light : const Light& - light to copy into the room
// return: int - 0 on success, -1 if index is invalid
int Room::setLight(int index, const Light &light) {
    if (index < 0 || index >= numLights) {
        return -1;
    }
    lights[index] = light;
    return 0;
}

// add a light at the end of the array
// param: light : const Light& - light to copy into the room
// return: int - 0 on success, -1 if the room is full (MAX_LIGHTS lights)
int Room::addLight(const Light &light) {
    if (numLights >= MAX_LIGHTS) {
        return -1;
    }
    lights[numLights] = light;
    numLights++;
    return 0;
}

// print the data to output stream
// param: out : ostream& - reference to output stream
// return: ostream& - output stream
std::ostream& Room::print(std::ostream &out) {
    out << "Room ID: " << id << std::endl;
    out << "Room name: " << name << std::endl;
    out << "Room location: " << location << std::endl;
    out << "Number of lights: " << numLights << std::endl;
    for (int i=0;i<numLights;i++) {
        out << "  lights[" << i << "] ";
        lights[i].print(out);
    }
    return out;
}
