#ifndef VECTOR_H_
#define VECTOR_H_

#include <iostream>

// IntVector - self-sizing array (lectures 9/22 and 9/24)
//
// arr          : pointer to the data array on the heap
// max_elements : capacity (size of the heap array)
// curr_element : number of elements in use (next free location)
//
// return code convention: 0 = success, -1 = error (bad index / empty)
class IntVector {
    private:
        int *arr;           // data array (heap)
        int max_elements;   // capacity
        int curr_element;   // number of elements used

        // grow the array: allocate bigger, copy, delete old
        void resize(int);

    public:
        // constructor - initial capacity
        IntVector(int initial = 10);

        // copy constructor - deep copy
        IntVector(const IntVector&);

        // assignment - deep copy
        IntVector& operator=(const IntVector&);

        // destructor - release heap memory
        virtual ~IntVector();

        // add at the end (lecture: addAtEnd)
        void addAtEnd(const int&);

        // add at the start / at a location (shift right)
        int addAt(int, const int&);

        // remove at a location (shift left)
        int removeAt(int);

        // get / change value at a location
        int get(int, int&) const;
        int set(int, const int&);

        // shrink capacity to the number of elements (compress)
        void compress();

        int size() const { return curr_element; }
        int capacity() const { return max_elements; }

        // print the vector
        std::ostream& print(std::ostream&) const;
};

#endif
