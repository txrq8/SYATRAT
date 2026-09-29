# ECE 218 Sample Exam: L3 (Customer) and L4 (Address)

## Files

| File | What it is |
|------|------------|
| `address.h` / `address.cpp` | L4: the `Address` class (US mailing address) |
| `customer.h` / `customer.cpp` | L3: the `Customer` class, written exactly as the UML, plus a virtual destructor |
| `main.cpp` | Driver: builds Addresses and Customers, prints them, shows that copying works |
| `Makefile` | Build, run, valgrind, clean |

## Build and run

```
make                  # g++ -std=c++11 -Wall -Wextra -pedantic -g
make CXX=clang++      # same build with clang
make run              # ./customer "Jane Smith" "305-555-0123"
make memcheck         # valgrind --leak-check=full
make clean
```

Running with the wrong number of arguments prints a usage line to `std::cerr` and returns -1:

```
$ ./customer
Usage: ./customer <name> <phone>
```

Both g++ 13 and clang++ 18 build it with zero warnings. Valgrind reports
`All heap blocks were freed -- no leaks are possible` and `ERROR SUMMARY: 0 errors`.

## L3: Customer

```cpp
class Customer {
    private:
        std::string name;    // customer name
        std::string phone;   // customer phone number
        Address home;        // home address (Customer has-a Address)

    public:
        Customer(std::string name, std::string phone, Address home);
        virtual ~Customer();
        std::ostream& print(std::ostream&) const;
};

Customer::Customer(std::string name, std::string phone, Address home)
    : name(name), phone(phone), home(home) {}

std::ostream& Customer::print(std::ostream &out) const {
    out << "Customer name: " << name << std::endl;
    out << "Customer phone: " << phone << std::endl;
    out << "Customer address:" << std::endl;
    home.print(out);      // the Address prints itself
    return out;
}
```

### What additional code is needed to make it work?

1. **The `Address` class has to exist, and `customer.h` must `#include "address.h"`.**
   `home` is an `Address` object, not a pointer, so the compiler needs the full class to know how big a `Customer` is.
   A forward declaration (`class Address;`) is not enough:
   `error: field 'home' has incomplete type 'Address'`.
2. **`Address` needs a `print(std::ostream&)` (or `operator<<`).** `Customer::print` has to output the address, but the address fields are private to `Address`, so `Address` must print itself.
3. **`Address` needs a working copy constructor.** The constructor takes `Address home` *by value*, which is one copy, and `home(home)` in the initializer list copies it again into the member. `Customer c2(c1)` and `c3 = c1` also copy `home`, so `Address` needs a working `operator=` as well.
   The compiler-generated versions would be correct here, because every member is a `std::string` (no pointers, so no deep copy is needed). The design writes them out anyway to show exactly what `Customer` relies on (rule of three).
4. **A default constructor `Address()`**, if `Customer` ever sets `home` in the constructor body (`this->home = home;`) instead of the initializer list, or if a default `Customer` or an array of `Customer` is added. Otherwise:
   `error: no matching function for call to 'Address::Address()'`.
5. **Include guards** (`#ifndef ADDRESS_H_ / #define ADDRESS_H_ / #endif`). `main.cpp` includes both `address.h` and `customer.h`, and `customer.h` includes `address.h` again. Without the guards you get
   `error: redefinition of 'class Address'`.
6. **`#include <iostream>` and `<string>`**, and `std::` on `string` and `ostream` in the headers (no `using namespace std;` in a header).
7. **A driver (`main`) and a Makefile** to test it. The Makefile must list `address.h` as a dependency of `customer.o` and `main.o`.
8. Optional: getters and setters for `Customer`. The UML has none, so once it is built a Customer can only be printed.

Passing `Address` (and the strings) by `const &` would save a copy. The UML says by value, so the code follows the UML.

## L4: Address design

```
+-------------------------------------------------------------------+
|                             Address                               |
+-------------------------------------------------------------------+
| - street : string   // line 1: "123 Main Street"                  |
| - unit   : string   // line 2: "Apt 4B", "" if none (optional)    |
| - city   : string   // "Miami"                                    |
| - state  : string   // 2 letter USPS code: "FL"                   |
| - zip    : string   // "33146" or ZIP+4 "33146-0620"              |
+-------------------------------------------------------------------+
| + Address()                                                       |
| + Address(street, city, state, zip : string)                      |
| + Address(street, unit, city, state, zip : string)                |
| + Address(other : const Address&)          // copy constructor    |
| + operator=(other : const Address&) : Address&                    |
| + ~Address()                               // virtual             |
| + getStreet() : string  ... getZip() : string                     |
| + setStreet(s : string) ... setZip(z : string)                    |
| + isValid() : bool                                                |
| + print(out : ostream&) : ostream&                                |
| - validState() : bool                                             |
| - validZip() : bool                                               |
+-------------------------------------------------------------------+
  operator<<(out : ostream&, a : const Address&) : ostream&   (free function)
```

Why each piece is there:

- **`zip` is a string, not an int.** Zip codes can start with 0 (`02134` in Boston), and ZIP+4 contains a dash.
- **Separate `street`/`unit` lines** follow the USPS label layout. `unit` is optional, so there is a 4-argument constructor without it.
- **Default constructor**: lets an `Address` exist with no data (arrays, members assigned later). The defaults (`"--"` state) are deliberately invalid.
- **Copy constructor / `operator=`**: needed by `Customer` (pass by value, `home(home)`, `c3 = c1`).
- **Virtual destructor**: follows the course style. It is empty because strings free themselves.
- **Getters/setters**: other classes can read or change parts of an address (for example, sort customers by zip) without breaking information hiding.
- **`isValid()`**: checks that street and city are not empty, the state is 2 uppercase letters, and the zip is `NNNNN` or `NNNNN-NNNN`. It checks the format only; checking that a state really exists would need a table of the ~60 USPS codes. The helpers are private because they are only used inside the class.
- **`print(std::ostream&)` returning the stream**: this is the method `Customer::print` needs. It works with `std::cout`, `std::cerr` or a file.
- **`operator<<`**: convenience, so `std::cout << a;` works. It just calls `print`.

## Sample output

```
$ ./customer "Jane Smith" "305-555-0123"
+++++++++++++++++++++++++++++++++
default Address:
none
none, -- 00000
valid: no
+++++++++++++++++++++++++++++++++
Address a:
123 Main Street
Apt 4B
Miami, FL 33146
valid: yes
+++++++++++++++++++++++++++++++++
Customer c1:
Customer name: Jane Smith
Customer phone: 305-555-0123
Customer address:
123 Main Street
Apt 4B
Miami, FL 33146
...
```

(`make run` shows the rest: `a` is changed and `c1` stays the same, then the copies `c2(c1)` and `c3 = c1`, then a bad address.)

## Note

With extra warning flags (`-Wdeprecated` for clang, `-Wdeprecated-copy-dtor` for g++), which are not the course flags, the compilers point out that `Customer` declares a destructor but relies on the compiler-generated copy (rule of three). The generated copy is correct for `Customer`. To silence it, add a copy constructor and `operator=` to `Customer` written the same way as the ones in `Address`.
