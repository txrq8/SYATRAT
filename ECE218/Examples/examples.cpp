// examples.cpp - small, tested examples for ECE 218 Exam 1 topics
// build: g++ -std=c++11 -Wall -Wextra examples.cpp vector.cpp -o examples
#include <iostream>
#include <string>

#include "vector.h"

// ---------- 1. memory spaces (lecture 8/20, hello2.cpp) ----------
int g_count = 0;            // global       -> global space (R/W)
const int G_MAX = 100;      // global const -> read-only space

void memorySpaces() {
    static int calls = 0;   // static local -> global/static space, keeps value between calls
    int local = 5;          // automatic    -> stack (freed when the function returns)
    int *heap = new int(7); // dynamic      -> the int is on the heap, 'heap' itself is on the stack
    calls++;
    if (g_count < G_MAX)
        g_count += local + *heap;
    std::cout << "calls=" << calls << " local=" << local << " *heap=" << *heap
              << " g_count=" << g_count << std::endl;
    delete heap;            // free the heap memory (forgetting this = memory leak)
    heap = nullptr;         // avoid a dangling pointer
}

// ---------- 2. pointers vs references ----------
void incByPointer(int *p) { if (p != nullptr) (*p)++; }  // can be null, must dereference
void incByReference(int &r) { r++; }                      // alias, never null

// ---------- 3. shallow vs deep copy (lecture 9/22) ----------
class Student {
    private:
        int s_id;
        int *data;          // pointer member -> needs deep copy
    public:
        Student(int id = -1) : s_id(id), data(new int[3]()) {}
        // copy constructor - deep copy
        Student(const Student &other) : s_id(other.s_id), data(new int[3]) {
            for (int i = 0; i < 3; i++) data[i] = other.data[i];
        }
        // assignment - deep copy
        Student& operator=(const Student &other) {
            if (this != &other) {
                s_id = other.s_id;
                for (int i = 0; i < 3; i++) data[i] = other.data[i];
            }
            return *this;
        }
        virtual ~Student() { delete [] data; }
        void setData(int i, int v) { data[i] = v; }
        int getData(int i) const { return data[i]; }
};

// ---------- 4. template bubble sort (lecture 9/15, sortt.cpp) ----------
template <class T>
void swapT(T &a, T &b) { T temp = a; a = b; b = temp; }

template <class T>
int compT(const T &a, const T &b) { return (a < b) ? -1 : (a > b) ? 1 : 0; } // no overflow

template <class T>
void bubbleT(T *arr, const int num, int (*comp)(const T&, const T&)) {
    for (int i = 0; i < num; i++)
        for (int j = 0; j < num - 1 - i; j++)
            if (comp(arr[j], arr[j + 1]) > 0)
                swapT(arr[j], arr[j + 1]);
}

// ---------- 5. inheritance + polymorphism (lecture 9/17) ----------
class Person {
    protected:
        std::string first, last;
    public:
        Person(std::string f, std::string l) : first(f), last(l) {}
        virtual ~Person() {}
        virtual void print() const { std::cout << "Person: " << first << " " << last << std::endl; }
};

class StudentP : public Person {        // Student is-a Person
    private:
        int student_id;
    public:
        StudentP(std::string f, std::string l, int id) : Person(f, l), student_id(id) {}
        void print() const override {
            std::cout << "Student: " << first << " " << last << " id=" << student_id << std::endl;
        }
};

int main() {
    std::cout << "--- 1. memory spaces" << std::endl;
    memorySpaces();
    memorySpaces();

    std::cout << "--- 2. pointer vs reference" << std::endl;
    int x = 10;
    incByPointer(&x);
    incByReference(x);
    std::cout << "x=" << x << std::endl;          // 12

    std::cout << "--- 3. deep copy" << std::endl;
    Student s1(10);
    s1.setData(0, 99);
    Student s2 = s1;                              // copy constructor
    s2.setData(0, 1);
    std::cout << "s1.data[0]=" << s1.getData(0) << " s2.data[0]=" << s2.getData(0) << std::endl; // 99 1

    std::cout << "--- 4. templates" << std::endl;
    int arri[] = {5, 4, 8, 1, 3};
    double arrd[] = {2.5, -1.0, 3.25};
    std::string arrs[] = {"pear", "apple", "fig"};
    bubbleT<int>(arri, 5, compT<int>);
    bubbleT<double>(arrd, 3, compT<double>);
    bubbleT<std::string>(arrs, 3, compT<std::string>);
    for (int v : arri) std::cout << v << " ";
    for (double v : arrd) std::cout << v << " ";
    for (const std::string &v : arrs) std::cout << v << " ";
    std::cout << std::endl;

    std::cout << "--- 5. polymorphism" << std::endl;
    StudentP *s = new StudentP("John", "Doe", 123);
    Person *p = s;                                // base pointer to derived object
    p->print();                                   // Student version (virtual)
    delete p;                                     // virtual destructor -> correct cleanup

    std::cout << "--- 6. vector" << std::endl;
    IntVector v(2);
    for (int i = 1; i <= 5; i++) v.addAtEnd(i * 10);
    v.print(std::cout);                           // [10 20 30 40 50] size=5 capacity=8
    v.addAt(0, 5);
    v.removeAt(3);
    v.set(1, 11);
    int val = 0;
    v.get(1, val);
    std::cout << "get(1)=" << val << " get(99) returns " << v.get(99, val) << std::endl;
    IntVector w = v;                              // deep copy
    w.addAtEnd(999);
    v.compress();
    v.print(std::cout);
    w.print(std::cout);
    return 0;
}
