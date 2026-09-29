#ifndef ROOM_H_
#define ROOM_H_

#include <iostream>
#include <string>

#include "light.h"

// maximum number of lights in a room (UML: lights[5])
const int MAX_LIGHTS = 5;

// Room - a room of the Smart Home (this version has only 1 Room with Lights)
//
// only lights[0] .. lights[numLights-1] are in use
//
// return code convention for methods that return int:
//    0 = success
//   -1 = error (for example an invalid light index)
class Room {
    private:
        int id;                     // room id
        std::string name;           // room name
        std::string location;       // room location
        Light lights[MAX_LIGHTS];   // lights in the room (each one default constructed)
        int numLights;              // number of lights in use

    public:
        // constructor (default)
        Room();

        // constructor with id, name and location
        Room(int, std::string, std::string);

        // destructor
        virtual ~Room();

        // turn ON the light at index
        int setLightOn(int);

        // turn OFF the light at index
        int setLightOff(int);

        // getters and setters
        int getId();
        void setId(int);

        std::string getName();
        void setName(std::string);

        std::string getLocation();
        void setLocation(std::string);

        int getNumLights();
        int setNumLights(int);

        Light getLight(int);
        int setLight(int, const Light&);

        // helper: add a light at the end of the array
        int addLight(const Light&);

        // print the room and all its lights
        std::ostream& print(std::ostream&);

};

#endif
