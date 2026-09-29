# ECE 218 Practice 1: Simple Smart Home

The first version of the Smart Home. It has **one Room with Lights**.

## Files

| File | Contents |
|------|----------|
| `light.h`, `light.cpp` | `Light` class: `id`, `name`, `state` (default `false` = OFF) |
| `room.h`, `room.cpp` | `Room` class: `id`, `name`, `location`, `lights[5]`, `numLights` |
| `main.cpp` | Reads the data file, builds the Room and prints the three required outputs |
| `room.txt` | Sample data file (1 room, 4 lights) |
| `Makefile` | `make` builds `smarthome`, and `make clean` removes the build files |

## Build

```sh
make
# or, without make:
g++ -std=c++11 -Wall -Wextra -pedantic -o smarthome main.cpp room.cpp light.cpp
```

The code compiles with zero warnings under both `g++` and `clang++` using these flags.

## Run

```sh
./smarthome room.txt
```

The program takes exactly one argument, the data file. With no argument or more than one, it prints `Usage: ./smarthome <data file>` to `std::cerr` and returns `-1` (the shell shows exit code 255).

The program prints:

1. the initial state of the Room after loading the data (all lights OFF)
2. the Room after every light is turned ON
3. the Room after every light is turned OFF

Output with the provided `room.txt`:

```
+++++++++++++++++++++++++++++++++
1. Initial state of the Room
+++++++++++++++++++++++++++++++++
Room ID: 1
Room name: LivingRoom
Room location: FirstFloor
Number of lights: 4
  lights[0] Light ID: 101  name: Ceiling  state: OFF
  lights[1] Light ID: 102  name: FloorLamp  state: OFF
  lights[2] Light ID: 103  name: TableLamp  state: OFF
  lights[3] Light ID: 104  name: WallSconce  state: OFF
+++++++++++++++++++++++++++++++++
2. All lights ON
+++++++++++++++++++++++++++++++++
Room ID: 1
Room name: LivingRoom
Room location: FirstFloor
Number of lights: 4
  lights[0] Light ID: 101  name: Ceiling  state: ON
  lights[1] Light ID: 102  name: FloorLamp  state: ON
  lights[2] Light ID: 103  name: TableLamp  state: ON
  lights[3] Light ID: 104  name: WallSconce  state: ON
+++++++++++++++++++++++++++++++++
3. All lights OFF (no blinds in this version)
+++++++++++++++++++++++++++++++++
Room ID: 1
Room name: LivingRoom
Room location: FirstFloor
Number of lights: 4
  lights[0] Light ID: 101  name: Ceiling  state: OFF
  lights[1] Light ID: 102  name: FloorLamp  state: OFF
  lights[2] Light ID: 103  name: TableLamp  state: OFF
  lights[3] Light ID: 104  name: WallSconce  state: OFF
```

`lights[i]` is the array index, the value passed to `setLightOn(i)` and `setLightOff(i)`. The light IDs (101 to 104) come from the data file and are separate from the index.

## Data file format

```
Room
<id> <name> <location>
Light <number_of_lights>
<id> <name>
...
End
```

The file is read one token at a time with `>>`, so names and locations must be single words (for example `LivingRoom` or `FirstFloor`).

## Design decisions

- **Attributes and methods follow the UML.** All attributes are `private` and all methods are `public`.
  - `Light`: `setOn()`, `setOff()`, `isOn()`, `getId()/setId()` and `getName()/setName()`. The `state` attribute changes only through `setOn()` and `setOff()`, and is read through `isOn()`.
  - `Room`: `setLightOn(index)`, `setLightOff(index)`, and getters and setters for every attribute: `getId/setId`, `getName/setName`, `getLocation/setLocation` and `getNumLights/setNumLights`. For the array there are `getLight(index)` and `setLight(index, light)`, plus an `addLight(light)` helper.
- **Default state is OFF.** Both `Light` constructors set `state(false)` in the initializer list (UML: `state: bool = false`).
- **Return code convention.** Every method that returns `int` returns `0` on success and `-1` on error:
  - `Light::setOn()` and `Light::setOff()` always return `0`, because a single light cannot fail.
  - `Room::setLightOn(i)`, `Room::setLightOff(i)` and `Room::setLight(i, l)` return `-1` if `i` is not in `0 .. numLights-1`. `numLights` is never more than 5, so a valid index is always in `0 .. 4`.
  - `Room::setNumLights(n)` returns `-1` if `n` is not in `0 .. 5`. The value is not changed.
  - `Room::addLight(l)` returns `-1` when the room is already full.
  - `Room::getLight(i)` returns a copy of the light, or a default `Light` (id `-1`, name `none`) if `i` is invalid.
- **Index validation.** Only `lights[0] .. lights[numLights-1]` are in use. Every method that takes an index checks it before touching the array, so a bad index can never read or write outside the array.
- **At most 5 lights.** The array is `Light lights[MAX_LIGHTS]` with `const int MAX_LIGHTS = 5` in `room.h`. Creating a `Room` default-constructs all 5 `Light` objects. If the data file lists more than 5 lights (for example `Light 7`), every line is still read so the parser stays in step with the file. The first 5 lights are kept, and a warning is printed to `std::cerr` for each extra light.
- **Error handling while reading the file.** The program prints a message to `std::cerr` and returns `-1` if:
  - the file cannot be opened
  - a keyword (`Room`, `Light`, `End`) is missing or wrong
  - a number cannot be read
  - the light count is negative
  - the file ends early (truncated file)
  - `End` is not where it should be, which usually means the light count does not match the number of light lines
- **No dynamic memory.** The lights are a fixed array inside `Room`, so there is no `new` or `delete`. Valgrind reports 0 errors and no leaks.
- **The "blinds" discrepancy.** Output step 3 of the assignment says "change state of all light to OFF **and all blinds to CLOSED**". The UML for this version has only `Room` and `Light`, and there are no blinds. That sentence appears to come from a later version of the assignment. No `Blind` class was invented. Step 3 turns all lights OFF and prints the Room, and a comment in `main.cpp` explains this.
