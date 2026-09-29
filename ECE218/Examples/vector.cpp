#include "vector.h"

// constructor
// param: initial : int - initial capacity (at least 1)
IntVector::IntVector(int initial) : arr(nullptr), max_elements(initial < 1 ? 1 : initial), curr_element(0) {
    arr = new int[max_elements];
}

// copy constructor - DEEP copy: new heap array, copy the values
// (the default copy would copy only the pointer -> shallow copy)
IntVector::IntVector(const IntVector &other)
    : arr(nullptr), max_elements(other.max_elements), curr_element(other.curr_element) {
    arr = new int[max_elements];
    for (int i = 0; i < curr_element; i++)
        arr[i] = other.arr[i];
}

// assignment - DEEP copy
IntVector& IntVector::operator=(const IntVector &other) {
    if (this != &other) {               // protect against v = v
        int *temp = new int[other.max_elements];
        for (int i = 0; i < other.curr_element; i++)
            temp[i] = other.arr[i];
        delete [] arr;                  // free the old array (else memory leak)
        arr = temp;
        max_elements = other.max_elements;
        curr_element = other.curr_element;
    }
    return *this;
}

// destructor
IntVector::~IntVector() {
    delete [] arr;
    arr = nullptr;
}

// resize - allocate a bigger array, copy data, delete the old one
// param: newMax : int - new capacity
void IntVector::resize(int newMax) {
    int *temp = arr;                    // keep the old array
    arr = new int[newMax];              // new bigger array
    for (int i = 0; i < curr_element; i++)
        arr[i] = temp[i];               // copy data
    delete [] temp;                     // missing this line = memory leak
    max_elements = newMax;
}

// add at the end
// check if full: true -> resize; then add at next location
void IntVector::addAtEnd(const int &e) {
    if (curr_element == max_elements)
        resize(max_elements * 2);       // growth factor 2 -> amortized O(1)
    arr[curr_element] = e;
    curr_element++;
}

// add at a location 0..curr_element (shift the rest right) - O(N)
int IntVector::addAt(int loc, const int &e) {
    if (loc < 0 || loc > curr_element) return -1;
    if (curr_element == max_elements)
        resize(max_elements * 2);
    for (int i = curr_element; i > loc; i--)
        arr[i] = arr[i - 1];
    arr[loc] = e;
    curr_element++;
    return 0;
}

// remove at a location (shift the rest left) - O(N)
int IntVector::removeAt(int loc) {
    if (loc < 0 || loc >= curr_element) return -1;
    for (int i = loc; i < curr_element - 1; i++)
        arr[i] = arr[i + 1];
    curr_element--;
    return 0;
}

// get value at a location - O(1)
int IntVector::get(int loc, int &value) const {
    if (loc < 0 || loc >= curr_element) return -1;
    value = arr[loc];
    return 0;
}

// change value at a location - O(1)
int IntVector::set(int loc, const int &value) {
    if (loc < 0 || loc >= curr_element) return -1;
    arr[loc] = value;
    return 0;
}

// compress - make capacity equal to the number of elements
void IntVector::compress() {
    if (curr_element > 0 && curr_element < max_elements)
        resize(curr_element);
}

// print
std::ostream& IntVector::print(std::ostream &out) const {
    out << "[";
    for (int i = 0; i < curr_element; i++)
        out << (i ? " " : "") << arr[i];
    out << "] size=" << curr_element << " capacity=" << max_elements << std::endl;
    return out;
}
