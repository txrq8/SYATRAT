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
| Mergesort | recursive split in halves down to 1 element, merge back up. `log2 N` levels × `N` work per level = **O(N log2 N)**. Needs a **work array** (O(N) extra memory). Use `mid = (start+end)/2`, halves `[start..mid]`, `[mid+1..end]` (reproduces his 5 4 8 \| 1 3 6 diagram). ⚠ Board (read at 300 dpi): `mid_point = (end-start+1)/2 + start; C = merge_sort(A,start,mid_point); D = merge_sort(A,mid_point+1,end); E = merge(C,len(C),D,len(D)); return E` — it has **no base case** and on a 2-element range `mid_point = end`, so it recurses forever. On an exam write: `if (start >= end) return;` and `mid = (start+end)/2` (= his formula minus 1). |
| Quicksort | `if(end>start){ p=partition(A,start,end); quicksort(A,start,p-1); quicksort(A,p+1,end); }` Best/avg O(N log2 N), worst O(N²). Partition = "find median, partition around it"; the pivot is a **guess of the median**. |
| Lomuto (partition1) | `pivot=a[end]; i=start-1; for j=start..end-1: if a[j]<=pivot {i++; swap(a[i],a[j]);} swap(a[i+1],a[end]); return i+1;` pivot ends in its final spot. |
| Hoare (partition2) | `pivot=a[start]; i=start-1; j=end+1; loop{ i++; while(a[i]<pivot) i++; j--; while(a[j]>pivot) j--; if(i>=j) return j; swap(a[i],a[j]); }` ⚠ pivot is NOT necessarily in final place; recursion must be `(start,p)` and `(p+1,end)`. |
| Median-of-3 | look at **first, middle, last**; median of the three = pivot. Lecture example `8 1 12 3 6 9` → 8, 12, 9 → **pivot 9**. |
| Memory map | top→bottom: **Stack** (R/W, grows **down**, stack frames: parameters, local variables/constants, local arrays; `fp` frame pointer, `sp` stack pointer; "stack smashing") · **Heap** (R/W, grows **up**, reached only through pointers) · **Globals** (R/W) · **Code** (R/O) · **global constants** (R/O). |
| Class files | declaration in `student.h` (with include guard), definition in `student.cpp` using `Student::` (scope), `this` pointer inside methods. Constructor with initializer list, `virtual` destructor, `std::ostream& print(std::ostream&)` returning the stream. |
| struct vs class | struct = "primitive objects", visibility public (by default); class = "full objects". |
| Copy | default (member-wise) copy: plain members and member ARRAYS are copied by value, POINTER members copy only the address → both objects share one heap block = **shallow** copy. Fix = **deep copy**: copy constructor `Student(const Student&)` (board: `Student(Student &)`) runs for `Student s2 = s1;`, `Student s2(s1);`, pass/return by value; **`s2 = s1;` on an already-existing s2 runs `operator=`**, not the copy constructor (VERIFIED) — a class owning heap memory needs destructor + copy constructor + `operator=` (rule of three). `Student *s4 = s3;` copies only the pointer (no constructor, same object). |
| Vector | self-sizing array: `arr` (heap), `max_elements` (capacity), `curr_element` (count). `addAtEnd(e)`: if full → resize; then `arr[curr]=e; curr++`. Resize (9/24 board): new max = max `+1`, or max `+100`, or max `+ factor·max_elements` (factor 1 → doubling). Constant increments → O(N²) total copying; proportional growth → amortized O(1) per add. Resize = new bigger array, copy, `delete [] old` (else **memory leak**; using old pointer afterwards = **use after deallocation**). |
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
  (`l1`, `c1`, `arr1`, `aptr` at 0x7ffe…). The printed addresses of `aptr[0]` and `aptr[1]`
  differ by 4 bytes (`sizeof(int)`), but the C++ expression `&aptr[1] - &aptr[0]` is **1**
  (pointer subtraction counts elements); `(char*)&aptr[1] - (char*)&aptr[0]` is 4. VERIFIED.
  Likewise `arr1 + 1` moves 4 bytes, `&arr1 + 1` moves 40 bytes (a whole `int[10]`).
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
* `sortt.cpp` template calls the non-template `swap(int&,int&)`: VERIFIED it fails for
  built-in non-int types (`T=double` → `cannot bind non-const lvalue reference of type 'int&'
  to a value of type 'double'`); it happens to work for `std::string` only because
  argument-dependent lookup finds `std::swap`. Correct design (9/15): template `swapT(T&,T&)`.

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

* `LECTURE_TRANSCRIPT.md` — every lecture page transcribed verbatim at 300 dpi (checked independently), with ambiguous-handwriting decisions and verified board slips.
* `OUTLINE_TOPICS.md` — verified notes on course-outline topics beyond the Exam 1 list: searching (linear/binary), recursion, linked lists, advanced I/O, bounds-tested & 2D arrays.
* `PRACTICE_BANK.md` / `ECE218_Practice_Bank.pdf` — 45 extra exam-style questions (sorting, memory/pointers, OOP/vector) with verified answers.
* `SOLUTIONS.md` / `ECE218_Solutions.pdf` (84 pages) — every Sample1 answer (G1–G20, L1–L4)
  and the full Practice1 solution; each answer = exam-ready English + worked steps + Arabic
  step-by-step explanation + the lecture page it comes from. All drafted, then adversarially
  re-checked; every code sample compiled (g++ & clang++ -Wall -Wextra), run, valgrind-clean.
* `Practice1/` — Smart Home (Room + Light) — full code, data file `room.txt`, Makefile, README.
* `Sample1/` — Customer + Address classes (Sample L3, L4) + test driver.
* `Examples/` — tested IntVector (self-sizing array, deep copy), memory spaces, pointer vs
  reference, deep copy, template bubble sort, polymorphism.
* `tools/trace.cpp` — pass-by-pass traces of the instructor's algorithms for any array:
  `g++ -std=c++11 -o trace tools/trace.cpp && ./trace all 10 2 12 5 3`
  (algorithms: bubble selmax selmin insertion merge lomuto hoare quick quickh med3 all).
* `tools/md2pdf.py` — Markdown → styled PDF (Arabic RTL blocks, `[[token]]` = English on its
  own line, highlighted code): `python3 tools/md2pdf.py in.md out.pdf`.
  Needs: `pip install markdown-it-py pygments`, Noto fonts (`apt-get install fonts-noto-core`),
  poppler-utils, Playwright Chromium (preinstalled at /opt/pw-browsers).

Pitfalls found while checking (keep in mind when writing answers):
* A reference *can* dangle (object died) — say "cannot be null / must be initialized", not
  "always valid". `r++` on a reference increments the referred variable.
* Code in answers must be inside a function (`int main(){...}`) to compile.
* Vector growth `×2` needs starting capacity ≥ 1 (2×0 = 0).
* Private members of a base ARE inherited (exist in the object) but are not accessible in
  the derived class; the compiler says "is private within this context".
* Median-of-3 on reverse data: first split is a perfect half, later splits balanced (not all
  perfect); sorted data: perfect halves every level.
* Selection sort: count a swap only when `max_loc != N-1-i` (lecture P4 = 0 swaps).
* Hoare partition: pivot not necessarily in final place; recurse `(start,p)`, `(p+1,end)`.

## 7. Playbook for solving a new ECE 218 paper

1. Read this file (sections 0–5) first; follow the instructor conventions in section 0.
2. Transcribe every question exactly (numbers, arrays, UML) — re-read the photo twice;
   ask the student about any unreadable digit instead of guessing.
3. Sorting traces → run `tools/trace` on the exact array and copy the verified passes;
   show instructor version first (selection = find max → end), textbook version as note.
4. Code questions → write in instructor style (header guard, initializer list, virtual
   destructor, `std::ostream& print(std::ostream&)`, `// param:` comments), compile with
   `g++ -std=c++11 -Wall -Wextra -pedantic`, run, valgrind; paste the real output.
5. Theory → short exam-ready English answer + small example; tie to the lecture page.
6. Second pass: adversarially re-check every claim/number (or a verify workflow), fix.
7. Write `PaperN/SOLUTIONS.md` (English answer + Arabic `<div class="ar" markdown="1">`
   block with `[[...]]` for English tokens), build PDF with `tools/md2pdf.py`, look at
   rendered pages (`pdftoppm -r 60 -png`), then send.

---

## 8. Deep details (completeness review against every lecture page and code file — all VERIFIED by running code)

### 8.1 Memory map picture (8/20) — details not captured

**Memory map details (8/20 drawing)**
- Stack (top, R/W) grows DOWN. main's stack frame (between `fp` frame pointer at top and `sp` stack pointer at bottom) holds: parameters (argc, argv) → variables/constants (`l1`, `c1`) → local array `arr1` → pointer `ptr`.
- Inside an array, indexes grow UP (toward higher addresses): `arr1` = address of `arr1[0]` (lowest), `arr1[1]` is 4 bytes higher (verified `...9e0`, `...9e4`).
- **Stack smashing** = writing past the end of a local array (e.g. `arr1[10]`, or a negative index) overwrites neighbouring frame data (other locals, saved fp/return address). Verified: loop writing 20 ints into `int arr1[10]` prints `*** stack smashing detected ***: terminated` then Aborted (exit 134), detected when the function returns.
- `ptr` (the variable) sits in the stack frame; the block it points to is in the HEAP (R/W, grows UP), reachable only through pointers.
- Below: globals (R/W), code (R/O), global constants (R/O).
- A LOCAL `const int c1` is on the stack (verified `&c1 = 0x7ffe...`), not in the global-const area. Writing to a GLOBAL const through a cast crashes (verified: Segmentation fault, exit 139); `g2 = 5;` does not compile: `assignment of read-only variable 'g2'`.
- Real Linux addresses (verified): code (`&main` 0x55..51c9) < global const 0x55..6008 < globals/static 0x55..8010 < heap 0x55..f2b0 < … < stack 0x7ffd... On the exam draw the instructor's order (stack top, heap, globals, code, g. const).

### 8.2 Pointers & arrays: hello2.cpp coding pattern and pointer arithmetic

**Pointer pattern (hello2.cpp):** `int *aptr = nullptr; aptr = new int[10]; aptr[0] = 5; ... delete [] aptr; aptr = nullptr;` (reset to nullptr so the dangling address can't be reused).
- `arr1[i]` ≡ `*(arr1 + i)`; `arr1 + 1` moves `sizeof(int)` = 4 bytes, `&arr1 + 1` moves 40 bytes (verified `4 40`); `&a[1] - &a[0]` = 1 element.
- 64-bit machine (verified): `sizeof(int)=4`, `sizeof(char)=1`, `sizeof(int*)=sizeof(double*)=sizeof(void*)=8` (lecture 9/10: an address is an int/long of 32 or 64 bits).
- `sizeof(arr)/sizeof(arr[0])` = number of elements of a real array (`int arr[10]` → 40/4 = 10); does NOT work on a pointer.

### 8.3 Parameter passing & storage duration — 'what does this print' basics

**By value / pointer / reference** (verified, x=1,y=2):
```cpp
void swapV(int a,int b){int t=a;a=b;b=t;}      // copies  -> prints 1 2
void swapP(int *a,int *b){int t=*a;*a=*b;*b=t;} // swapP(&x,&y) -> 2 1
void swapR(int &a,int &b){int t=a;a=b;b=t;}    // swapR(x,y)  -> back to 1 2
```
**static local** keeps its value between calls (global space); automatic local is re-created each call: `int counter(){static int c=0; int l=0; c++; l++; return c*10+l;}` called 3 times → `11`, `21`, `31` (verified).
**Dangling pointer:** `int* f(){int x=5; return &x;}` → g++ warns `address of local variable 'x' returned [-Wreturn-local-addr]`; x dies when the frame is popped.
`int a=5; int &r=a; int *p=&a; r++; (*p)++; p++;` → a = r = 7 (p++ only moves the pointer).

### 8.4 Memory errors from 9/22 — exact tool messages

**Resize code (9/22), correct syntax:** `int *arr2 = new int[100]; int *temp = arr2; arr2 = new int[200]; for(i<100) arr2[i]=temp[i]; delete [] temp;`
- Board writes `delete temp[]` → compile error `expected primary-expression before ']' token` (verified). Correct: `delete [] temp;`.
- Forget `delete [] temp` → **memory leak**: valgrind `400 bytes in 1 blocks are definitely lost` (verified).
- Read `temp[5]` after `delete [] temp` → **use after deallocation**: valgrind `Invalid read of size 4` (verified).
- `delete` on a `new[]` block → g++ warning `-Wmismatched-new-delete`; deleting the same block twice → valgrind `Invalid free() / delete / delete[] / realloc()`; natively `free(): double free detected in tcache 2` + Aborted (verified).
- `new` never returns nullptr: it throws `std::bad_alloc` (verified for 10^12 ints); only `new (std::nothrow) int[n]` returns nullptr.

### 8.5 C string vs std::string (9/22)

**C string:** `char str[] = "hello";` = h e l l o **'\0'** → `sizeof(str)` = **6**, `strlen(str)` = 5 (verified). Fixed size; `c1 == c2` on two char arrays compares ADDRESSES (0 even if same text; g++ warns `-Warray-compare`) → use `strcmp(c1,c2)==0`.
**std::string** = C++ class: the object holds a pointer `_str` to a buffer 'size to fit' that it grows/frees itself; `string s2 = s1;` is a DEEP copy (verified: after `s2[0]='j'`, s1 = `hello`, s2 = `jello`, different buffers). `==` compares text. `sizeof(std::string)` = 32 on g++ (verified); short strings (≤15 chars) are stored inside the object (small-string optimization, verified), long ones on the heap. Conceptually (his drawing): pointer → heap buffer.

### 8.6 Which special member runs (constructor / copy / assignment / destructor)

Verified output of a class that prints in each special member:
```
Student s1;            -> default ctor
Student s2 = s1;       -> copy ctor
Student s3(s1);        -> copy ctor
s2 = s1;               -> operator=
byValue(s1);           -> copy ctor, then dtor (parameter dies)
byRef(s1);             -> nothing
Student *p = new Student; -> default ctor
Student *q = p;        -> nothing (pointer copy)
delete q;              -> dtor
end of main            -> dtor dtor dtor (s3, s2, s1 - reverse order)
```
- Class with `int *data` + destructor `delete [] data` but NO copy ctor: `Student s2 = s1;` → both delete the same block → `free(): double free detected in tcache 2`, Aborted (verified).
- Copy ctor must take a reference: `Student(Student s)` → `error: invalid constructor; you probably meant 'Student (const Student&)'` (verified).
- **Rule of three:** if a class needs a destructor (owns heap memory) it needs a deep-copy copy constructor and operator= (check `this != &other`, delete old, allocate, copy, `return *this`).

### 8.7 Self-sizing array / Vector (9/22, 9/24) — operations, pseudo-code, measured costs

**Self-sizing array = vector** (9/22): resize (inc/dec), compress; add/remove at start, mid, end; change values; get value at location. `int arr1[100]` ✗ (size fixed at compile time, stack); use `int *arr2 = new int[100]` so it can be replaced by a bigger block.
**addAtEnd(elem &e)** (9/24): check if full (`curr_element == max_elements`) → true: resize; then add to next location `arr2[curr] = e; curr++`.
Measured element copies for N adds starting at capacity 1 (verified):
| policy | N=1000 | N=2000 |
|---|---|---|
| +1 | 999 resizes, 499,500 copies (=N(N-1)/2) | 1,999,000 (×4) |
| +100 | 10 resizes, 4,510 copies | 19,020 (≈×4) |
| ×2 | 10 resizes, 1,023 copies | 2,047 (×2) |
So constant growth → O(N²) total (O(N) per add); proportional growth → < 2N copies total, amortized O(1). g++ `std::vector` capacities while pushing: 1 2 4 8 16 32 64 128 (verified doubling); `v.at(100)` on size 100 throws `std::out_of_range` (verified).

### 8.8 Bubble sort analysis as derived on the 8/27 page

**Bubble derivation (8/27):** pass i does j = 0 … N-2-i → **N-1-i comparisons** (5 4 8 1 3: 4, 3, 2, 1). Worst case each comparison also swaps: (comp+swap)(N-1 + N-2 + … + 0) = (comp+swap)·Σ_{n=0}^{N-1} n = (comp+swap)·N(N-1)/2 = (N²/2)(comp+swap) − (N/2)(comp+swap) → as N→∞ keep the dominant term, drop constants → **O(N²)**. (Identity used: Σ_{0}^{N} n = N(N+1)/2.)
Best case O(N) only with early exit: verified on `1 2 3 4 5`: with a swapped-flag 4 comparisons (N-1), the instructor's code (no flag) still does 10. Reverse `5 4 3 2 1`: 10 comps, 10 swaps.
Useful numbers (verified): N=5 → 10, N=6 → 15, N=8 → 28, N=10 → 45, N=100 → 4,950, N=1000 → 499,500 comparisons; N log2 N for 1000 ≈ 9,966; for 10^6: N² = 10^12 vs N log2 N ≈ 2·10^7.

### 8.9 Selection sort — instructor pseudo-code, code, analysis, stability

```cpp
// selection sort (8/27): find max, swap to end of unsorted part
void selectionSort(int *arr, const int n) {
  for (int i = 0; i < n; i++) {          // N passes (last has 1 element)
    int max_loc = 0;
    for (int j = 1; j < n - i; j++)      // 1 -> N-1-i
      if (arr[j] > arr[max_loc]) max_loc = j;
    swap(arr[max_loc], arr[n - 1 - i]);  // may swap with itself (lecture P4)
  }
}
```
Verified: `5 4 8 1 3` → `1 3 4 5 8`; `10 2 12 5 3` → `2 3 5 10 12`. Board cost: inner compare loop ⇒ N² ; swap line ⇒ N → comparisons always N(N-1)/2, swaps ≤ N-1 (far fewer swaps than bubble: 3 vs 7 on 5 4 8 1 3). **Not stable** (verified): `2a 2b 1c` → `1c 2b 2a`.

### 8.10 Insertion sort — lecture example, both versions, code

**Lecture example (8/27):** sorted `1 6 9` | unsorted `3 8 1`: insert 3 → `1 3 6 9` (2 moves), insert 8 → `1 3 6 8 9` (1 move), insert 1 → `1 1 3 6 8 9` (4 moves) (verified; whole array from start: 12 comps, 7 moves). Board shows it two ways: (a) adjacent swaps 's' leftward; (b) 'move' version: hold next element, move larger ones right, drop it in the hole — same result, 1 assignment per move instead of 3 per swap.
```cpp
void insertionSort(int *arr, const int n) {
  for (int i = 1; i < n; i++) {
    int next = arr[i]; int j = i - 1;
    while (j >= 0 && arr[j] > next) { arr[j + 1] = arr[j]; j--; }
    arr[j + 1] = next;
  }
}
```
Verified: sorted `1 2 3 4 5` → 4 comps, 0 moves (O(N)); reverse `5 4 3 2 1` → 10 comps, 10 moves (O(N²)). Stable (verified `2a 2b 1c` → `1c 2a 2b`) because it stops at an equal key (`>` not `>=`).

### 8.11 Merge & mergesort — lecture example, code, midpoint formula

**Merge example (9/1):** A = `1 9 12 14`, B = `3 6 10` → C = `1 3 6 9 10 12 14`: 5 comparisons (1<3→1, 3, 6, 9<10→9, 10), then 'j is done' → copy leftovers 12 14 of A (verified).
```cpp
void merge(const int *A,const int lenA,const int *B,const int lenB,int *C){
  int i=0,j=0,k=0;
  while(i<lenA && j<lenB){ if(A[i]<B[j]){C[k]=A[i];k++;i++;} else {C[k]=B[j];k++;j++;} }
  while(i<lenA){C[k]=A[i];k++;i++;}
  while(j<lenB){C[k]=B[j];k++;j++;}
}
void mergeSort(int *A,int *work,const int start,const int end){
  if(start>=end) return;
  int mid=(start+end)/2;
  mergeSort(A,work,start,mid); mergeSort(A,work,mid+1,end);
  merge(A+start,mid-start+1,A+mid+1,end-mid,work+start);
  for(int k=start;k<=end;k++) A[k]=work[k];   // A <-> Work
}
```
Verified `5 4 8 1 3 6` → `1 3 4 5 6 8`, valgrind clean. Board midpoint `mid=(end-start+1)/2+start` works if halves are `[start..mid-1]`,`[mid..end]` (verified: 5 4 8 | 1 3 6, then 5 | 4 8); with `[start..mid]`,`[mid+1..end]` it recurses forever on 2 elements (verified).
**Bottom-up** (loops, run size 1,2,4…): `5 4 8 1 3 6` → `4 5 1 8 3 6` → `1 4 5 8 3 6` → `1 3 4 5 6 8` (verified).

### 8.12 Quicksort — concept vs mergesort, board-versus-code Hoare caveat, failure cases, measured timings

**Idea (9/1 'split?'):** mergesort splits by POSITION (easy) and does the work in the MERGE; quicksort splits by VALUE around a pivot (partition does the work) so `1 3 6 | 8 9 12` needs no merge — sort part 1, sort part 2, done. 9/3 diagram: `8 1 12 3 6 9`, pivot 6 (true median guess) → `1 3 | 6 | 8 12 9` → `1 | 3`, `8 | 9 | 12`.
**sortp.cpp comments:** partition1 (Lomuto): pivot = last, i is the slow index, j the fast index, final `swap(a[i+1],a[end])` puts pivot in place. partition2 (Hoare): pivot = first, i moves right from the left, j moves left from the right.
**Caveat:** the board's hand trace of Hoare on `8 1 12 3 6 9` ends `6 1 3 8 12 9` (pivot 8 drawn in the middle); running partition2's CODE gives `6 1 3 12 8 9`, returns j=2 (verified). Same split sets {6,1,3} | {8,12,9} — for a 'trace the code' question give the code result.
**Bug:** Hoare + `quicks(a,start,p-1); quicks(a,p+1,end)` → wrong output `1 6 3 9 8 12` on the lecture array (verified). Use `(start,p)`,`(p+1,end)`.
**Lomuto worst cases (verified N=8):** sorted, reverse AND all-equal input all give 28 = N(N-1)/2 comparisons, recursion depth 8 = N.
**Measured (instructor sort/sortp, g++ -O0):** random 10,000: bubble 0.19 s, quicksort 0.001 s; SORTED 10,000: quicksort 0.148 s — slower than bubble's 0.074 s on the same sorted data.

### 8.13 Runtime measurement (sort.cpp + getCPUTime) — scaling experiment

`double start = getCPUTime(); sort(...); double end = getCPUTime();` measures CPU time (user + system) of the process, not wall-clock. Verified runs of the instructor's programs on random data (1..1,000,000):
| N | bubble (sort.cpp) | quicksort (sortp.cpp) |
|---|---|---|
| 10,000 | 0.19 s | 0.0011 s |
| 20,000 | 0.97 s | 0.0023 s |
| 40,000 | 4.66 s | 0.0048 s |
Doubling N: O(N²) → ≈×4 (measured ×5, cache effects); O(N log N) → slightly more than ×2 (measured ×2.1). Exam rule of thumb: if bubble takes T for N, expect ≈4T for 2N, ≈100T for 10N.

### 8.14 support.h / support.cpp / mkdata.cpp details

- Portability via conditional compilation: `#if defined(__unix__) || (defined(__APPLE__) && defined(__MACH__))` → `<sys/time.h>`, `<sys/resource.h>`; `#elif defined(_WIN32)` → `<time.h>`. The preprocessor picks the code for the OS.
- `getCPUTime()`: `getrusage(RUSAGE_SELF,&ru)`; t = `ru_utime` (user) + `ru_stime` (system), each `tv_sec + tv_usec/1000000.0` seconds. Windows: `clock()/(double)CLOCKS_PER_SEC`.
- `randomInRange(start,end)` = `start + random()%(end-start+1)` → INCLUSIVE [start,end] (verified 1..3 gives 1,2,3 ≈ 1/3 each); Windows uses `rand()`.
- `srandomdev()` (macOS/BSD) seeds `random()` from the OS random device. Linux: `error: 'srandomdev' was not declared in this scope` → use `srandom(time(NULL))`. With NO seed, every run prints the same sequence (verified `84 87 78 16 94` twice).
- `std::stoi(argv[1], &sz)`: converts text → int; `sz` receives how many characters were used (`"12abc"` → 12, sz=2); non-numeric → throws `std::invalid_argument` (`./sort abc` → `terminate called ... what(): stoi`, Aborted). `std::string::size_type` = alias of size_t.
- Wrong argument count → usage on `std::cerr`, `return -1` → shell exit status 255 (verified). Pipeline: `./mkdata 10 1 100 | ./sort 10` works like `> data.txt` then `< data.txt`.

### 8.15 hw.h DPRINT macro internals

`hw.h`: include guard `#ifndef HW_H_ / #define HW_H_ / #endif`; `#ifdef DEBUG → #define PDEBUG 1 #else 0`.
`DPRINT(fmt, ...)` = `do { if (PDEBUG) { char str[100]; snprintf(str,100,fmt,##__VA_ARGS__); std::cerr << "DEBUG-->" << __FILE__ << ":" << __LINE__ << ":" << __func__ << "():" << str; } } while (0)`
- `__FILE__`, `__LINE__`, `__func__` = current file, line, function; `##__VA_ARGS__` removes the comma when there are no extra arguments.
- `do{...}while(0)` makes the macro ONE statement, so `if (x) DPRINT(...); else ...` works; a plain `{...}` macro gives `error: 'else' without a previous 'if'` (verified).
- Without `-DDEBUG` the preprocessor output is `if (0) {...}` (verified with `g++ -E`) → nothing printed, code optimized away. Output goes to stderr (not captured by `> file`; use `2>`).

### 8.16 Compiling multi-file programs — commands and error messages

- `g++ hello.cpp` (no `-o`) → executable `a.out`. Stages verified: `g++ -S` → `.s` 'assembler source', `g++ -c` → `.o` 'ELF relocatable', link → 'ELF executable'.
- Classes: `g++ main.cpp student.cpp -o student`. Compile `main.cpp` alone → LINKER errors `undefined reference to 'Student::Student()'`, `... 'Student::print(std::ostream&)'` (verified). Compiles fine, fails at link = definition missing.
- `#include "student.h"` searches the current directory first; `#include <student.h>` → `fatal error: student.h: No such file or directory` unless `-I.` (verified). System headers use `< >`.
- Include guard: including student.h twice is fine WITH the guard; without it → `error: redefinition of 'class Student'` (verified).

### 8.17 Generic C sort with void* (9/10) — design, rules, limits

**Board design (9/10):** `bubble(A /*location*/, num /*# elements*/, size_of_element, f compare, f allocate, f assign)`. The loops `for(i..num) for(j..num-1-i)` use plain ints → type-independent; ONLY the comparison and the swap depend on the type:
- `if (A[j] > A[j+1])` → `compare(a,b)`: -1 a<b, 0 a==b, 1 a>b.
- `temp=A[j]; A[j]=A[j+1]; A[j+1]=temp;` → `assign(a,b)` ⇒ a = b = copy size-of-data bytes from b to a = `memcpy(a, b, size)` (DESTINATION first).
- allocate = `void *malloc(# of bytes)` for temp (pair with `free`). sortb.cpp hard-codes malloc/memcpy with `esize`, so only `comp` is passed: `bubbleSort(void *arr, int num, int esize, int (*comp)(const void*, const void*))`.
**void* rules (verified g++):** `*p` → `error: 'void*' is not a pointer-to-object type`; `int *ip = p;` → `error: invalid conversion from 'void*' to 'int*'` (C++ needs `(int*)p`); `p + 4` is only a GNU extension (`warning: pointer of type 'void *' used in arithmetic`) → element j = `(char*)arr + j*esize` (d[2] at byte 8).
**Other compare functions (verified):** descending = swap the -1/1 answers (`10 2 12 5 3` → `12 10 5 3 2`); double via `(double*)`; struct by field `((const Rec*)a)->id` with `sizeof(Rec)` (12 bytes). `qsort((void*)data, num, sizeof(int), comp_int)` has the same compare contract.
**Limit:** memcpy copies raw bytes — fine for int/double/plain structs, WRONG for C++ objects: sorting `std::string {"pear","apple","fig"}` this way printed `[pear] [apple] [fig]` (still unsorted, verified). Templates call the real copy/assignment instead.

### 8.18 Templates (9/15) — board variants and the errors they cause

- `template <class T>` = temporary data type T; the compiler generates specific code per use: `bubbleT<int>(arri,n)`, `bubbleT<float>(arrf,n)` (or let it deduce: `bubbleT(arrf,3,comp_flt)` → T=float).
- Board variants: `void bubbleT(T *arr, const int num, int (*comp)(const T *a, const T *b))` → call `comp(&arr[j], &arr[j+1])`, e.g. `int comp_int(const int *a, const int *b)`; sortt.cpp uses references `int (*comp)(const T&, const T&)`. Swap: `template<class T> void swapT(T &a, T &b){T temp=a; a=b; b=temp;}` (verified int, float, struct).
- 'Needs support functions / operator functions `<, >, >>, <<, + - * /`': with `if (arr[j] > arr[j+1])` and T=Point without `operator>` → `error: no match for 'operator>' (operand types are 'Point' and 'Point')`; add `bool operator>(const Point &a, const Point &b)`. You CANNOT write `operator>(const int&, const int&)` (board note) → `error: ... must have an argument of class or enumerated type` (verified) — built-ins already have it.
- Template body in a .cpp, only declared in .h → `undefined reference to 'void bubbleT<int>(int*, int)'` (verified) ⇒ put template code in the .h.
- Mixed types: `bubbleT(intArray, 5, comp_flt)` → `deduced conflicting types for parameter 'const T' ('int' and 'float')` (verified).

### 8.19 Classes 9/15–9/17: struct example, Person/ssn, class→instance, this, Student::, instructor's Student code details

- `struct name { string first, last; }; name n; n.first = "John";` (struct members public by default). Same members in a `class` → `error: 'std::string NameC::first' is private within this context` (verified).
- Object → attributes + methods (methods include constructor/destructor). Person: `firstname, lastname, ssn (private)`, method `write_name` — ssn private = information hiding.
- class → instance like `int` (data type) → `int x` (instance): `Student s;`. In `s.print()`, `this` == `&s` (a `Student*`).
- `Student::print` = scope (namespace) of the class. Omit `Student::` in student.cpp → free function: `error: 's_id' was not declared in this scope`, and `this` → `error: invalid use of 'this' in non-member function` (verified).
- student.cpp: `Student::Student() : s_id(-1), name("none") {}` (initializer list); destructor 'can be eliminated, system adds default'; `set(int id, std::string name){ s_id=id; this->name=name; }` — the parameter hides the member, so `name = name;` compiles but leaves `none` (verified; clang warns self-assign).
- `std::ostream& print(std::ostream &out)` returns `out` → chaining `s1.print(cout) << "-- end --";` (verified). Stream by value → `use of deleted function 'std::basic_ostream...(const std::basic_ostream&)'` (verified).
- Course-page UML → code: `- s_id : int` → `private: int s_id;`, `- name : string` → `std::string name;`, `+ Student` → `Student();`, `+ ~Student()` → `virtual ~Student();`, `+ set(id:int, name:string):void` → `void set(int, std::string);`.
- Practice UML: `state: bool = false` = default value (set in constructor); `lights[5]: Light` array member needs `Light::Light()` — without a default constructor → `error: no matching function for call to 'Light::Light()'` (verified).

### 8.20 Inheritance & polymorphism (9/17) — UML example and verified behaviour

**UML (9/17):** Person ◁— Student, Faculty, Admin, Guest (hollow-triangle arrows = inheritance, is-a); Student ◁— UG, G; Faculty ◁— R, A; Student —mentor→ Faculty = ASSOCIATION (plain line, not inheritance); 'Dean' written below (where does it fit?). Generalization ↑ toward Person, specialization ↓.
**Verified run** (`Student *s = new Student; Person *p = s;`): `s->print()` → Student version; `p->print()` (virtual) → Student version; `p->show()` (NOT virtual) → Person version; `delete p` with virtual dtor → `~Student` then `~Person`; without virtual dtor → only `~Person` + warning `deleting object of polymorphic class type 'Person' which has non-virtual destructor might cause undefined behavior`.
- Overloading `compare(int,int)` / `compare(float,float)` = same name, different parameters, chosen at COMPILE time; overriding `print()` in Student + `virtual` = polymorphism, chosen at RUN time.
- Access (verified): protected member from outside → `is protected within this context`; base private member used in derived → `is private within this context`; `class DC : B {}` inherits PRIVATELY by default → `'int B::x' is inaccessible within this context` (struct inherits publicly).
- `class Dean : public Faculty, public Admin` (both derive Person) → `d.lastname` is `error: request for member 'lastname' is ambiguous` (two Person parts) (verified).

### 8.21 Exam logistics

**Exam #1: Thursday, Oct 1st 2026 (9/17 page) — in class, written, closed book.** Material through the 9/24 Vector lecture.

---

## 9. Likely exam question types (beyond Sample1)

- Short-answer definitions (2-4 lines) that go beyond Sample1: stack smashing; stack frame / fp / sp; where a local const, a static local, a global const and a `new` block live; `this` pointer; `Student::` scope; overloading vs overriding; shallow vs deep copy; copy constructor vs operator=; rule of three; why template code goes in the .h; what `void *` is and why element j is `(char*)arr + j*esize`; C string '\0' vs std::string; what `-DDEBUG` does to DPRINT.
- Memory-map drawing: give a hello2-style program and ask to draw stack (frame with parameters, locals, local array, pointer var), heap block, globals, code and global const. Label R/W vs R/O and the growth directions. Classify each variable as automatic, static or dynamic, and show where stack smashing would overwrite.
- Sorting traces on a NEW array (not 10 2 12 5 3). Example verified with tools/trace for `7 3 9 2 5 1`: bubble 15 comps/11 swaps (P1 `3 7 2 5 1 9`); selection-max 15 comps/5 swaps (P1 `7 3 1 2 5 9`); insertion 13 comps/11 moves; mergesort 9 comps; one Lomuto partition (pivot 1) → `1 3 9 2 5 7`, p=0; one Hoare partition (pivot 7) → `1 3 5 2 | 9 7`, j=3; median-of-3 (7, 9, 1) → 7.
- Merge step trace: merge two given sorted arrays showing i, j, k and when leftovers are copied (lecture: `1 9 12 14` + `3 6 10` → 5 comparisons, then copy 12 14). Also drawing the recursive split/merge tree with log2 N levels × N work per level.
- Write the code, closed book and in the instructor's style: bubble / selection (max→end) / insertion (move version) / merge / partition1 (Lomuto) / partition2 (Hoare) / quicks, or the vector's addAtEnd + resize. The // param comments and the delete [] of the old block are expected.
- Runtime analysis and estimation: derive N(N-1)/2 for bubble or selection; explain O(N log2 N) for mergesort and best-case quicksort; 'if bubble sort takes T for N, how long for 2N?' (≈4T; measured 0.19 s → 0.97 s); why quicksort with a last-element pivot is O(N²) on sorted, reverse or all-equal data (28 comps for N=8, and slower than bubble on sorted input); cost of resize policies (+1 → 499,500 copies for 1000 adds vs ×2 → 1,023).
- What-does-this-print (verified answers): swap by value / pointer / reference (`1 2`, `2 1`, `1 2`); static local counter (11 21 31); the constructor / copy / operator= / destructor sequence; a virtual vs non-virtual call through `Person *p = s`; shallow copy sharing `int *data` (s1 sees s2's change, the member array does not); `sizeof(str)=6` vs `strlen=5`; `&a[1]-&a[0]` = 1; Student output before and after set().
- Find-the-bug / fix-the-code: `delete temp[]`; missing `delete []` (leak); use after delete; returning `&local`; `name = name` instead of `this->name = name`; missing `Student::`; bubble inner loop `j < n-i` (out-of-bounds read/write); Hoare partition used with `p-1`/`p+1` recursion (gives `1 6 3 9 8 12`); `comp_int` returning `a-b` (overflow); copy constructor taking the object by value; a class with a pointer member and destructor but no copy constructor (double free); the board mergesort mid formula recursing forever; a local array overflow (stack smashing); a template called with a type that has no `operator>`.
- Write-a-class from a UML box other than Customer/Address: e.g. the course-page Student UML (s_id, name, set, print) split into .h (guard) and .cpp (Student::, initializer list, virtual destructor, `std::ostream& print(std::ostream&)`); the 9/22 Student with `int *data` that needs copy ctor, operator= and destructor; an IntVector; Person→Student with a virtual print; Room/Light-style classes with an array of objects (default constructor required) and default attribute values.
- UML/design reading and drawing: draw a class diagram for a described system (the university personnel hierarchy); mark + - # visibility and `name : type`; tell inheritance (hollow triangle, is-a) from association (plain line such as 'mentor'); say which attributes to hide; decide class vs struct.
- Compile/execution mechanics: give the g++ command for a multi-file build (`g++ main.cpp student.cpp -o student`, `g++ sort.cpp support.cpp -o sort`); say whether an error comes from the compiler or the linker ('undefined reference'); state the argc/argv values for `./hello one two three`; `<` and `>` redirection and the mkdata | sort pipeline; the effect of `-DDEBUG`; why `srandomdev` fails on Linux and what `#if defined(__unix__)` is for.
- Generic programming comparison: design the six-parameter C bubble (compare, allocate, assign); write a compare function for descending order, for double, or for a struct field (used with qsort or sortb); explain why memcpy-based swapping is wrong for std::string objects (the sort stays unsorted) and why C++ templates fix that but need operator/support functions and the code in the header.

---

## 10. Board vs. correct — the instructor's handwritten slips (all VERIFIED by compiling/running)

Full verbatim page-by-page text: `LECTURE_TRANSCRIPT.md`. Use the board's *ideas* and the
*correct code* below; never copy the board syntax literally.

| Page | Board (as written) | Correct / what really happens |
|---|---|---|
| 8/20 memory | code drawn above `g. const` | on g++/Linux `.text` (code) is actually *below* `.rodata`; both R/O — draw his order on the exam |
| 8/27 bubble | red count column `N-1, N-2, N-2, …` | third term is `N-3`; total `N(N-1)/2` |
| 8/27 bubble | "Best case O(N) sorted (early exit)" | needs a `swapped` flag; his loops/sort.cpp have none → sorted input still 10 comps for N=5 |
| 8/27 selection | labels swapped: `outer: j`, `inner: i : 1 → N-1-i` | `for(i=0;i<N;i++){ max_loc=0; for(j=1;j<N-i;j++) if(a[j]>a[max_loc]) max_loc=j; swap(a[max_loc],a[N-1-i]); }` |
| 8/27 selection | `max_loc = 0` drawn inside the inner (dashed) scope | must be set ONCE per pass before the inner loop (literal version turns `5 4 8 1 3` into `1 4 8 3 5`) |
| 8/27 selection | swap column 1,1,1,0 | counts real exchanges; unconditional code makes N swap calls (self-swaps) |
| 8/27 insertion | example `1 6 9 3 8 1`, row 3 unfinished | whole array: 12 comps, 7 swaps (swap version); use `>` (not `>=`) to stay stable; stop at index 0 |
| 9/1 merge | else branch `C[t] = B[j]` | `C[k] = B[j]` |
| 9/1 merge | `if A[i] < B[j]` | works; `<=` makes the merge stable |
| 9/1 mergesort | `mid_point=(end-start+1)/2+start`, halves `[start..mid_point]`,`[mid_point+1..end]`, **no base case** | infinite recursion on 2 elements; write `if(start>=end) return; mid=(start+end)/2;` (reproduces his 5 4 8 \| 1 3 6 tree) |
| 9/1 mergesort | `len(A)` etc. | pseudocode — pass lengths as parameters in C++ |
| 9/3 Lomuto | code missing last two lines | add `swap(A[i+1],A[end]); return i+1;` — trace result `8 1 3 6 9 12`, p=4 |
| 9/3 Lomuto | mixes `A[end]` and `a[j]` | C++ is case-sensitive — one name |
| 9/3 Hoare | `i++, while(A[i]<pivot) i++` | `i++; while(A[i]<pivot) i++;` (comma form doesn't compile) |
| 9/3 Hoare | hand trace ends `6 1 3 8 12 9` | the written code gives `6 1 3 12 8 9`, returns j=2; pivot not necessarily at j; recurse `(start,p)`,`(p+1,end)` |
| 9/3 quicksort tree | first pivot 6 | illustration of the ideal (true median); none of his pivot rules picks 6 (end→9, start→8, median-of-3→9) |
| 9/10 generic C | `if (A[j] > A[j+1])` on `void*` | can't compile — that's why `compare(a,b)` exists; element j = `(char*)arr + j*esize` |
| 9/10 generic C | `int compare(void *a, void *b)` | qsort needs `int comp(const void*, const void*)` |
| 9/10 generic C | malloc temp, memcpy swap | `memcpy(dest, src, n)`; `free(temp)` at end; raw-byte copy breaks `std::string` (crash) → templates |
| 9/10 generic C | "compare returns -1/0/1" | only test `> 0` / `< 0` (sortt returns `a-b`) |
| 9/15 templates | `if ( i=0 ; i<num ; i++ )` | `for (int i=0; i<num; i++)` |
| 9/15 templates | parameter `arr`, body uses `a[j]` | use one name |
| 9/15 templates | `swapT(...)` never defined | `template <class T> void swapT(T &a, T &b){ T t=a; a=b; b=t; }` |
| 9/15 templates | `operator>(const int&, const int&)` | impossible for built-ins (must involve a class type); overload `>` only for your own class |
| 9/15 templates | `int arri[n]` with variable n | VLA, not standard C++ (`-Wvla`); use `new int[n]` |
| 9/15 templates | "put code in .h" | body only in a .cpp → `undefined reference to 'void bubbleT<int>(int*, int)'` |
| 9/15, 9/17 struct | `n.first = 'John"` | `n.first = "John";` (`'John'` compiles but stores one char!) + `std::string` / `#include <string>` |
| 9/17 UML p1 | triangle drawn `Person ▷—— Student` | UML: hollow triangle tip at the PARENT `Person ◁—— Student` (page 2 draws it right) |
| 9/17 polymorphism | `p->print()` "Student version" | only if `print` is `virtual` in Person; `Person *p = s` needs `class Student : public Person` |
| 9/17 overloading | `compare(int,int)`, `compare(float,float)` | `compare(1.5, 2.5)` is **ambiguous** (double literals) — use `1.5f` |
| 9/17 | `Student::compare(s)` vs `Person::compare()` | different parameters → hides, doesn't override (`s.compare()` fails) |
| 9/17 | "`Student::` = namespace (scope)" | strictly *class scope* with the scope-resolution operator `::` |
| 9/22 class | `public` without `:`; `}` without `;` | `public:` and `};` |
| 9/22 copy | `s2 = s1` → "Copy Constructor" | s2 already exists → **`operator=`**; copy ctor runs for `Student s2 = s1;` |
| 9/22 copy | `Student(Student &)` | prefer `Student(const Student &)` (can copy const objects) |
| 9/22 copy | default copy | pointer member shared (shallow), member array `arr[100]` copied fully |
| 9/22 resize | `delete temp[]` | `delete [] temp;` then `temp = nullptr;` |
| 9/24 vector | "true: resize / false: add" | if full → resize; then ALWAYS `arr2[curr]=e; curr++;` |
| 9/24 vector | `addAtEnd(elem &e)` | `const elem &e` (else `addAtEnd(5)` won't compile) |
| 9/24 vector | `+ (factor)(max_elements)` | never grows from 0 → start capacity ≥ 1; costs for 100,000 adds: +1 → 4,999,950,000 copies, +100 → 49,951,000, doubling → 131,071 |
