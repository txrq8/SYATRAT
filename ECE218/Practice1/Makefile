# Makefile for the Simple Smart Home (ECE 218 Practice)
#   make        -> builds the executable smarthome
#   make clean  -> removes the executable and object files

CXX = g++
CXXFLAGS = -std=c++11 -Wall -Wextra -pedantic

all: smarthome

smarthome: main.o room.o light.o
	$(CXX) $(CXXFLAGS) -o smarthome main.o room.o light.o

main.o: main.cpp room.h light.h
	$(CXX) $(CXXFLAGS) -c main.cpp

room.o: room.cpp room.h light.h
	$(CXX) $(CXXFLAGS) -c room.cpp

light.o: light.cpp light.h
	$(CXX) $(CXXFLAGS) -c light.cpp

clean:
	rm -f smarthome *.o

.PHONY: all clean
