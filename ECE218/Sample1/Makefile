# Makefile for ECE 218 Sample Exam L3 / L4 (Customer and Address)
#   make            build the program
#   make run        build and run with sample arguments
#   make memcheck   build and run under valgrind
#   make clean      remove object files and the program
# to use clang instead of g++:  make CXX=clang++

CXX = g++
CXXFLAGS = -std=c++11 -Wall -Wextra -pedantic -g

PROG = customer
OBJS = main.o customer.o address.o

$(PROG): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(PROG) $(OBJS)

# each .o depends on its .cpp and on every header it includes
# customer.h includes address.h, so a change to address.h
# must rebuild customer.o and main.o too
main.o: main.cpp customer.h address.h
	$(CXX) $(CXXFLAGS) -c main.cpp

customer.o: customer.cpp customer.h address.h
	$(CXX) $(CXXFLAGS) -c customer.cpp

address.o: address.cpp address.h
	$(CXX) $(CXXFLAGS) -c address.cpp

run: $(PROG)
	./$(PROG) "Jane Smith" "305-555-0123"

memcheck: $(PROG)
	valgrind --leak-check=full --error-exitcode=1 ./$(PROG) "Jane Smith" "305-555-0123"

clean:
	rm -f $(OBJS) $(PROG)

.PHONY: run memcheck clean
