#include <iostream>
#include <fstream>
#include <string>

#include "light.h"
#include "room.h"

// load the room data from an input stream (the data file)
// expected format (tokens are separated by spaces / new lines):
//   Room
//   <id> <name> <location>
//   Light <number_of_lights>
//   <id> <name>          <- one line per light
//   ...
//   End
// names and locations must be single words (no spaces)
// a room holds at most MAX_LIGHTS lights: extra lights are read,
// a warning is printed and they are ignored
// param: in : istream& - reference to the input stream to read from
// param: room : Room& - reference to the room to fill with the data
// return: int - 0 on success, -1 on error (message printed to cerr)
int loadRoom(std::istream &in, Room &room) {
    std::string keyword;

    // 1. keyword "Room"
    in >> keyword;
    if (in.fail() || keyword != "Room") {
        std::cerr << "Error: expected keyword 'Room'\n";
        return -1;
    }

    // 2. room <id> <name> <location>
    int id;
    std::string name;
    std::string location;
    in >> id >> name >> location;
    if (in.fail()) {
        std::cerr << "Error: could not read room <id> <name> <location>\n";
        return -1;
    }
    room.setId(id);
    room.setName(name);
    room.setLocation(location);

    // 3. keyword "Light" and <number_of_lights>
    int count;
    in >> keyword;
    if (in.fail() || keyword != "Light") {
        std::cerr << "Error: expected keyword 'Light'\n";
        return -1;
    }
    in >> count;
    if (in.fail() || count < 0) {
        std::cerr << "Error: could not read a valid number of lights\n";
        return -1;
    }

    // 4. one light per line: <id> <name>
    for (int i=0;i<count;i++) {
        int lightId;
        std::string lightName;
        in >> lightId >> lightName;
        if (in.fail()) {
            std::cerr << "Error: could not read light " << i+1
                      << " of " << count << std::endl;
            return -1;
        }
        // create the Light object and copy it into the room
        if (room.addLight(Light(lightId, lightName)) != 0) {
            std::cerr << "Warning: a room holds at most " << MAX_LIGHTS
                      << " lights, ignoring light " << lightId << " "
                      << lightName << std::endl;
        }
    }

    // 5. keyword "End"
    // if it is not found, the number of lights usually does not
    // match the number of light lines in the file
    in >> keyword;
    if (in.fail() || keyword != "End") {
        std::cerr << "Error: expected keyword 'End' after " << count
                  << " lights (check the number of lights)\n";
        return -1;
    }

    return 0;
}

int main(int argc, char *argv[]) {

    // 1 argument
    // 1. name of the data file
    if (argc!=2) {
        std::cerr << "Usage: " << argv[0] << " <data file>\n";
        return -1;
    }

    // open the data file
    std::ifstream inFile(argv[1]);
    if (!inFile.is_open()) {
        std::cerr << "Error: could not open data file " << argv[1] << std::endl;
        return -1;
    }

    // create a Room instance and load it with the data from the file
    Room room;
    if (loadRoom(inFile, room) != 0) {
        std::cerr << "Error reading data file " << argv[1] << std::endl;
        return -1;
    }
    inFile.close();

    // 1. print the initial state of the Room
    std::cout << "+++++++++++++++++++++++++++++++++\n";
    std::cout << "1. Initial state of the Room\n";
    std::cout << "+++++++++++++++++++++++++++++++++\n";
    room.print(std::cout);

    // 2. change the state of all lights to ON and print the Room
    for (int i=0;i<room.getNumLights();i++) {
        if (room.setLightOn(i) != 0) {
            std::cerr << "Error: could not turn ON light " << i << std::endl;
        }
    }
    std::cout << "+++++++++++++++++++++++++++++++++\n";
    std::cout << "2. All lights ON\n";
    std::cout << "+++++++++++++++++++++++++++++++++\n";
    room.print(std::cout);

    // 3. change the state of all lights to OFF and print the Room
    // NOTE: the assignment text also says "and all blinds to CLOSED",
    // but the UML design of this version has no blinds (only Room and
    // Light), so only the lights are turned OFF here
    for (int i=0;i<room.getNumLights();i++) {
        if (room.setLightOff(i) != 0) {
            std::cerr << "Error: could not turn OFF light " << i << std::endl;
        }
    }
    std::cout << "+++++++++++++++++++++++++++++++++\n";
    std::cout << "3. All lights OFF (no blinds in this version)\n";
    std::cout << "+++++++++++++++++++++++++++++++++\n";
    room.print(std::cout);

    return 0;
}
