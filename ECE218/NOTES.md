# ECE 218 — Fall 2026 — Master Study Notes (Exam 1 material)

These notes are the reference to re-read before solving any ECE 218 paper.
Source: the instructor's handwritten lectures (8/20 → 9/24), his sample code, the
course page (topics list, supporting code), `Sample1.pdf`, `Practice1.pdf`.
Everything marked **VERIFIED** was checked by compiling/running real code
(`tools/trace.cpp` reproduces every lecture trace exactly).

Exam 1 per the instructor's 9/17 page: in class, written, closed book.
Topics (course page): General C++ syntax, compiling, execution · Memory & pointers
(dynamic/static/automatic allocation, pointers & references, stack/heap/code/global
spaces) · Sorting (bubble, selection, insertion, merge, quick — operations,
implementations, runtime & runtime analysis) · Objects & classes (information
hiding, inheritance, polymorphism; class vs struct; declaration vs definition;
coding & use) · Vectors (basic properties).

---

## 0. Instructor conventions to follow when answering (IMPORTANT)

| Topic | Instructor's version (use this first) |
|---|---|
| Selection sort | **Find the MAX** of the unsorted part and **swap it with the LAST** unsorted slot `a[N-1-i]` (sorted part grows from the right). Textbook min-to-front is also correct — mention it as an alternative. |
| Bubble sort | outer `i: 0 → N-1` (`i<N`), inner `j: 0 → N-2-i` (`j<N-1-i`), `if a[j]>a[j+1] swap`. Worst `N(N-1)/2` comps → O(N²). Best O(N) **only with early exit** (a "swapped" flag) — his code has no flag. |
| Insertion sort | sorted part \| unsorted part; take next element, **shift (move)** larger sorted elements one to the right, drop the element in the hole. |
| Merge | `i, j, k` two-pointer merge of A and B into C, then copy leftovers of A, then of B. |
| Mergesort | recursive split in halves down to 1 element, merge back up. `log2 N` levels × `N` work per level = **O(N log2 N)**. Needs a **work array** (O(N) extra memory). Use `mid = (start+end)/2`, halves `[start..mid]`, `[mid+1..end]` (reproduces his 5 4 8 \| 1 3 6 diagram). ⚠ The board formula `mid=(end-start+1)/2+start` with `[start..mid]` never shrinks a 2-element range — do not copy it literally. |
| Quicksort | `if(end>start){ p=partition(A,start,end); quicksort(A,start,p-1); quicksort(A,p+1,end); }` Best/avg O(N log2 N), worst O(N²). Partition = "find median, partition around it"; the pivot is a **guess of the median**. |
| Lomuto (partition1) | `pivot=a[end]; i=start-1; for j=start..end-1: if a[j]<=pivot {i++; swap(a[i],a[j]);} swap(a[i+1],a[end]); return i+1;` pivot ends in its final spot. |
| Hoare (partition2) | `pivot=a[start]; i=start-1; j=end+1; loop{ i++; while(a[i]<pivot) i++; j--; while(a[j]>pivot) j--; if(i>=j) return j; swap(a[i],a[j]); }` ⚠ pivot is NOT necessarily in final place; recursion must be `(start,p)` and `(p+1,end)`. |
| Median-of-3 | look at **first, middle, last**; median of the three = pivot. Lecture example `8 1 12 3 6 9` → 8, 12, 9 → **pivot 9**. |
| Memory map | top→bottom: **Stack** (R/W, grows **down**, stack frames: parameters, local variables/constants, local arrays; `fp` frame pointer, `sp` stack pointer; "stack smashing") · **Heap** (R/W, grows **up**, reached only through pointers) · **Globals** (R/W) · **Code** (R/O) · **global constants** (R/O). |
| Class files | declaration in `student.h` (with include guard), definition in `student.cpp` using `Student::` (scope), `this` pointer inside methods. Constructor with initializer list, `virtual` destructor, `std::ostream& print(std::ostream&)` returning the stream. |
| struct vs class | struct = "primitive objects", visibility public (by default); class = "full objects". |
| Copy | default copy = **shallow** (pointer members copied → both objects share the same heap block) → write a **copy constructor** `Student(const Student&)` doing a **deep copy**. |
| Vector | self-sizing array: `arr` (heap), `max_elements` (capacity), `curr_element` (count). `addAtEnd(e)`: if full → resize; then `arr[curr]=e; curr++`. Resize grows by `+1`, `+100` (constant) or `×factor` (e.g. double). Resize = new bigger array, copy, `delete [] old` (else **memory leak**; using old pointer afterwards = **use after deallocation**). |
| Templates | `template <class T>`; compiler generates the specific code per type (`bubbleT<int>`, `bubbleT<float>`); T needs the operators used (`<`, `>`, `<<`, …); template code goes **in the .h** (compiler needs the source). |
| Generic C sort | `void *` = raw address; element `j` is at `(char*)arr + j*esize`; compare returns -1/0/1 through a function pointer `int (*comp)(const void*, const void*)`; copy/swap with `malloc` + `memcpy`; `qsort(data, num, sizeof(int), comp_int)`. |

---

## 1. Compiling & execution (course page, hello.cpp, hw.h, support.*)

* Stages: **preprocess** (`#include`, `#define`, `#ifdef`; `g++ -E`) → **compile** to
  assembly (`g++ -S`, `.s`) → **assemble** to object code (`g++ -c`, `.o`) → **link**
  object files + libraries into the executable (`g++ a.o b.o -o prog`).
* `g++ sort.cpp support.cpp -o sort` — support.cpp must be on the compile line or the
  **linker** fails (undefined reference to `getCPUTime`).
* `hw.h` → `DPRINT` macro: active only when compiled with `-DDEBUG` (preprocessor
  `#ifdef DEBUG` sets `PDEBUG 1`). VERIFIED: with `-DDEBUG` it prints
  `DEBUG-->hello2.cpp:25:main():i=0` to stderr.
* `main(int argc, char *argv[])`: `argv[0]` = program name, `argc` counts it.
  VERIFIED `./hello one two three` → index 0 `./hello`, 1 `one`, 2 `two`, 3 `three`.
* Input redirection: `./sort 10 < data.txt`; output redirection `./mkdata 10 1 100 > data.txt`.
* `mkdata.cpp` uses `srandomdev()` — exists on macOS/BSD only (instructor uses a Mac);
  on Linux it fails to compile (use `srandom(time(NULL))`). VERIFIED.

## 2. Memory & pointers (8/20 lecture, hello2.cpp)

* hello2 regions (VERIFIED addresses on Linux): `g2` global **const** (lowest, read-only
  data) < `g1` global (R/W data) < heap block from `new int[10]` < … < stack
  (`l1`, `c1`, `arr1`, `aptr` at 0x7ffe…). `&aptr[1] - &aptr[0]` = 4 bytes (`sizeof(int)`).
* `arr1` and `&arr1` print the **same address** (different types: `int*` vs `int(*)[10]`).
* `aptr` (the pointer variable) lives on the **stack**; what it points to lives on the **heap**.
* Allocation kinds: **automatic** (locals/params on the stack, freed when the function
  returns), **static** (globals, `static` locals — exist for the whole program, in the
  global space), **dynamic** (`new`/`delete`, `new[]`/`delete[]`, heap, lifetime controlled
  by the programmer, size can be decided at run time).
* Pointer = variable holding an address (`int *p = &x; *p = 5;`), can be `nullptr`,
  can be re-pointed, supports arithmetic. Reference = alias (`int &r = x;`), must be
  initialized, cannot be null, cannot be re-seated, no arithmetic, used like the variable.
* **Memory leak** = heap block no longer reachable and never freed. Instructor examples:
  resize without `delete [] temp` (9/22); **the sort programs themselves never
  `delete [] data`** — VERIFIED with valgrind: `20 bytes in 1 blocks are definitely lost`.
* `new` throws `std::bad_alloc` on failure — the `if (data==nullptr)` check in the sort
  programs can never trigger (only `new (std::nothrow)` returns nullptr).

## 3. Sorting — facts and complexities

| | best | average | worst | extra memory | stable | notes |
|---|---|---|---|---|---|---|
| Bubble | O(N) *with early-exit flag* | O(N²) | O(N²) | O(1) | yes | many swaps |
| Selection | O(N²) | O(N²) | O(N²) | O(1) | no | always N(N-1)/2 comps, ≤ N-1 swaps |
| Insertion | O(N) (sorted) | O(N²) | O(N²) (reverse) | O(1) | yes | great for nearly sorted / small N |
| Mergesort | O(N log N) | O(N log N) | O(N log N) | O(N) work array | yes if merge uses `<=` (his `A[i] < B[j]` takes B first on ties → not stable) | guaranteed |
| Quicksort | O(N log N) | O(N log N) | O(N²) | O(log N) stack avg, O(N) worst | no | worst when pivot is always min/max (sorted data + first/last pivot) |

VERIFIED traces (instructor algorithms, `tools/trace.cpp`):

* Bubble `5 4 8 1 3` → P1 `4 5 1 3 8`, P2 `4 1 3 5 8`, P3 `1 3 4 5 8`, P4 `1 3 4 5 8` — 10 comps, 7 swaps.
* Selection(max) `5 4 8 1 3` → P1 `5 4 3 1 8`, P2 `1 4 3 5 8`, P3 `1 3 4 5 8`, P4 no swap — 10 comps, 3 swaps.
* Lomuto on `8 1 12 3 6 9` (pivot 9) → `8 1 3 6 9 12`, p=4 (matches his page).
* Hoare on `8 1 12 3 6 9` (pivot 8) → `6 1 3 | 12 8 9`, returns j=2.
* Median-of-3 `8 1 12 3 6 9` → 8, 12, 9 → 9.
* Mergesort `5 4 8 1 3 6` → `5 4 8 | 1 3 6` → `4 5 | 8`, `1 3 | 6` → `4 5 8`, `1 3 6` → `1 3 4 5 6 8`.

VERIFIED on the Sample1 array `10 2 12 5 3`:

* Selection (max→end, instructor): `10 2 3 5 12` → `5 2 3 10 12` → `3 2 5 10 12` → `2 3 5 10 12`; 10 comps, 4 swaps.
* Selection (min→front, textbook): `2 10 12 5 3` → `2 3 12 5 10` → `2 3 5 12 10` → `2 3 5 10 12`; 10 comps, 4 swaps.
* Insertion: insert 2 (1 shift) `2 10|12 5 3` → 12 (0) → 5 (2) `2 5 10 12|3` → 3 (3) `2 3 5 10 12`; 9 comps, 6 shifts.
* Bubble: `2 10 5 3 12` → `2 5 3 10 12` → `2 3 5 10 12`; 10 comps, 6 swaps.
* Mergesort: `10 2 12 | 5 3` → `10 2 | 12`, `5 | 3` → `2 10`, `3 5` → `2 10 12` → `2 3 5 10 12`; 7 comps.
* Median-of-3: 10, 12, 3 → pivot 10.
* Mergesort on reverse data `8 7 6 5 4 3 2 1`: still O(N log N), only 12 comps (= N/2·log2 N, the minimum) — every merge copies the whole right half first.
* Quicksort (Lomuto) on sorted `1 2 3 4 5 6`: 15 comps = N(N-1)/2 → worst case O(N²).

Instructor code facts:
* `sortp.cpp` `quicks` uses `partition1` (Lomuto) with `p-1`/`p+1` — correct. Swapping in
  `partition2` (Hoare) with the same recursion would be wrong (must be `start..p`).
* `sortt.cpp` `comp_int` returns `a-b` → **integer overflow** for extreme values; VERIFIED
  wrong order for `2147483647, -2147483648, 5` → printed `5, 2147483647, -2147483648`.
  Safe version: `return (a<b) ? -1 : (a>b) ? 1 : 0;`.
* `sortt.cpp` template calls `swap(int&,int&)` → only works for `T=int` (needs a
  template `swapT(T&,T&)` for other types).

## 4. Objects & classes (9/15, 9/17, 9/22)

* Object = real-world entity → **attributes** + **methods**, with visibility
  `public / protected / private` = **information hiding**; constructor/destructor;
  **inheritance** (Student *is-a* Person; generalization ↑ / specialization ↓; UML hollow
  triangle arrow); **polymorphism** (`Person *p = s; p->print()` runs the Student version —
  requires `virtual`); overloading `compare(int,int)` / `compare(float,float)`.
* UML: `-` private, `+` public, `#` protected; `name : type`; `method(param : type) : return`.
  Association (Student —mentor— Faculty) ≠ inheritance.
* class vs struct in C++: the only language difference is the **default** access
  (struct public, class private) and default inheritance access (public vs private).
* `Student s;` → instance on the stack; `Student *s1 = new Student;` → on the heap, use `->`,
  must `delete s1;`.
* Instructor Student example (VERIFIED output): `Student ID: -1 / Student name: none`, then
  after `set(123,"John Doe")` → `Student ID: 123 / Student name: John Doe`.

## 5. Vector (9/22, 9/24)

Properties: contiguous, O(1) access by index, size vs capacity, grows automatically
(allocate bigger heap array, copy, delete old), add/remove at end cheap (amortized O(1)
with multiplicative growth), at start/middle O(N) (shifting), change/get value at index,
can shrink/compress. Growth `+1` or `+100` ⇒ O(N) per add amortized (O(N²) total);
growth `×2` ⇒ amortized O(1). `std::vector<T>`: `push_back`, `size()`, `capacity()`,
`operator[]` (no bounds check), `at()` (bounds check, throws `std::out_of_range`).

---

## 6. Solved papers in this folder

* `Practice1/` — Smart Home (Room + Light) — full code, data file, Makefile, README.
* `Sample1/` — Customer + Address classes (Sample Q3, Q4).
* `SOLUTIONS.md` — all Sample1 answers (G1–G20, L1–L4) and Practice1 walkthrough.
* `tools/trace.cpp` — prints pass-by-pass traces for any array:
  `g++ -std=c++11 -o trace tools/trace.cpp && ./trace all 10 2 12 5 3`.
