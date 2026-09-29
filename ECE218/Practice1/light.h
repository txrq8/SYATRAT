#ifndef LIGHT_H_
#define LIGHT_H_

#include <iostream>
#include <string>

// Light - one light in a room of the Smart Home
//
// return code convention for methods that return int:
//    0 = success
//   -1 = error
class Light {
    private:
        int id;             // light id
        std::string name;   // light name
        bool state;         // light state: true = ON, false = OFF (default false)

    public:
        // constructor (default)
        Light();

        // constructor with id and name
        Light(int, std::string);

        // destructor
        virtual ~Light();

        // turn the light ON
        int setOn();

        // turn the light OFF
        int setOff();

        // check if the light is ON
        bool isOn();

        // getters and setters
        int getId();
        void setId(int);

        std::string getName();
        void setName(std::string);

        // print the light
        std::ostream& print(std::ostream&);

};

#endif
