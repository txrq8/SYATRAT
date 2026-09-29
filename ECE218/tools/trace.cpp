// trace.cpp
// Prints step-by-step traces of the sorting algorithms exactly as the
// ECE 218 instructor wrote them in lecture (8/27, 9/1, 9/3), so hand traces
// on an exam can be checked against real output.
//
// build: g++ -std=c++11 -Wall -Wextra -o trace trace.cpp
// run:   ./trace <algorithm> <values...>
//   algorithm: bubble | selmax | selmin | insertion | merge | lomuto | hoare
//              | quick | quickh | med3 | all
// example: ./trace selmax 10 2 12 5 3

#include <iostream>
#include <string>
#include <vector>
#include <cstdlib>

static long g_comp = 0; // comparisons of data values
static long g_swap = 0; // swaps (selection/bubble/quick) or moves (insertion)

void show(const std::vector<int> &a, int from = 0, int to = -1) {
    if (to < 0) to = (int)a.size() - 1;
    for (int k = 0; k < (int)a.size(); k++) {
        if (k == from && from > 0) std::cout << "| ";
        std::cout << a[k] << " ";
        if (k == to && to < (int)a.size() - 1) std::cout << "| ";
    }
}

void swapv(int &a, int &b) { int t = a; a = b; b = t; g_swap++; }

// bubble sort - instructor version (8/27, sort.cpp): no early exit
void bubble(std::vector<int> a) {
    int n = a.size();
    for (int i = 0; i < n; i++) {
        bool swapped = false;
        for (int j = 0; j < n - 1 - i; j++) {
            g_comp++;
            if (a[j] > a[j + 1]) { swapv(a[j], a[j + 1]); swapped = true; }
        }
        std::cout << "  pass " << i + 1 << ": "; show(a);
        std::cout << (swapped ? "" : "  (no swaps -> early exit possible)") << "\n";
    }
}

// selection sort - instructor version (8/27): find MAX, swap to a[N-1-i]
void selmax(std::vector<int> a) {
    int n = a.size();
    for (int i = 0; i < n - 1; i++) {
        int max_loc = 0;
        for (int j = 1; j < n - i; j++) {
            g_comp++;
            if (a[j] > a[max_loc]) max_loc = j;
        }
        int before = a[n - 1 - i];
        if (max_loc != n - 1 - i) swapv(a[max_loc], a[n - 1 - i]);
        std::cout << "  pass " << i + 1 << ": max=" << a[n - 1 - i] << " (index " << max_loc
                  << ") -> position " << n - 1 - i
                  << (max_loc != n - 1 - i ? " swap with " + std::to_string(before) : " already there, no swap")
                  << "  => "; show(a); std::cout << "\n";
    }
    std::cout << "  pass " << n << ": one element left -> sorted\n";
}

// selection sort - textbook version: find MIN, swap to a[i]
void selmin(std::vector<int> a) {
    int n = a.size();
    for (int i = 0; i < n - 1; i++) {
        int min_loc = i;
        for (int j = i + 1; j < n; j++) {
            g_comp++;
            if (a[j] < a[min_loc]) min_loc = j;
        }
        int before = a[i];
        if (min_loc != i) swapv(a[min_loc], a[i]);
        std::cout << "  pass " << i + 1 << ": min=" << a[i] << " (index " << min_loc << ") -> position " << i
                  << (min_loc != i ? " swap with " + std::to_string(before) : " already there, no swap")
                  << "  => "; show(a); std::cout << "\n";
    }
}

// insertion sort (8/27): take next element, shift larger ones right, drop in hole
void insertion(std::vector<int> a) {
    int n = a.size();
    for (int i = 1; i < n; i++) {
        int key = a[i];
        int j = i - 1;
        int shifts = 0;
        while (j >= 0) {
            g_comp++;
            if (a[j] > key) { a[j + 1] = a[j]; j--; shifts++; g_swap++; }
            else break;
        }
        a[j + 1] = key;
        std::cout << "  step " << i << ": insert " << key << " (" << shifts << " shifts)  => ";
        show(a, 0, i); std::cout << "\n";
    }
}

// merge (9/1): i, j, k two-pointer merge
std::vector<int> merge(const std::vector<int> &A, const std::vector<int> &B) {
    std::vector<int> C;
    size_t i = 0, j = 0;
    while (i < A.size() && j < B.size()) {
        g_comp++;
        if (A[i] < B[j]) C.push_back(A[i++]);
        else C.push_back(B[j++]);
    }
    while (i < A.size()) C.push_back(A[i++]);
    while (j < B.size()) C.push_back(B[j++]);
    return C;
}

std::vector<int> msort(const std::vector<int> &a, int start, int end, int depth) {
    std::string ind(depth * 2, ' ');
    std::vector<int> part(a.begin() + start, a.begin() + end + 1);
    if (start >= end) return part;
    int mid = (start + end) / 2;
    std::cout << "  " << ind << "split "; show(part);
    std::cout << " -> [" << start << ".." << mid << "] [" << mid + 1 << ".." << end << "]\n";
    std::vector<int> C = msort(a, start, mid, depth + 1);
    std::vector<int> D = msort(a, mid + 1, end, depth + 1);
    std::vector<int> E = merge(C, D);
    std::cout << "  " << ind << "merge "; show(C); std::cout << "+ "; show(D);
    std::cout << "=> "; show(E); std::cout << "\n";
    return E;
}

// Lomuto partition (9/3, sortp.cpp partition1): pivot = a[end]
int lomuto(std::vector<int> &a, int start, int end) {
    int pivot = a[end];
    int i = start - 1;
    for (int j = start; j < end; j++) {
        g_comp++;
        if (a[j] <= pivot) { i++; if (i != j) swapv(a[i], a[j]); }
    }
    if (i + 1 != end) swapv(a[i + 1], a[end]);
    return i + 1;
}

// Hoare partition (9/3, sortp.cpp partition2): pivot = a[start], returns j
int hoare(std::vector<int> &a, int start, int end) {
    int pivot = a[start];
    int i = start - 1;
    int j = end + 1;
    while (true) {
        i++; g_comp++;
        while (a[i] < pivot) { i++; g_comp++; }
        j--; g_comp++;
        while (a[j] > pivot) { j--; g_comp++; }
        if (i >= j) return j;
        swapv(a[i], a[j]);
    }
}

void quick(std::vector<int> &a, int start, int end, int depth) {
    if (start < end) {
        std::string ind(depth * 2, ' ');
        std::cout << "  " << ind << "partition [" << start << ".." << end << "] pivot=" << a[end];
        int p = lomuto(a, start, end);
        std::cout << " -> p=" << p << "  => "; show(a, start, end); std::cout << "\n";
        quick(a, start, p - 1, depth + 1);
        quick(a, p + 1, end, depth + 1);
    }
}

// NOTE: with Hoare the recursion must be (start, p) and (p+1, end)
void quickh(std::vector<int> &a, int start, int end, int depth) {
    if (start < end) {
        std::string ind(depth * 2, ' ');
        std::cout << "  " << ind << "partition [" << start << ".." << end << "] pivot=" << a[start];
        int p = hoare(a, start, end);
        std::cout << " -> p=" << p << "  => "; show(a, start, end); std::cout << "\n";
        quickh(a, start, p, depth + 1);
        quickh(a, p + 1, end, depth + 1);
    }
}

void med3(const std::vector<int> &a) {
    int s = 0, e = a.size() - 1, m = (s + e) / 2;
    int x = a[s], y = a[m], z = a[e];
    int med = std::max(std::min(x, y), std::min(std::max(x, y), z));
    std::cout << "  first a[" << s << "]=" << x << ", middle a[" << m << "]=" << y
              << ", last a[" << e << "]=" << z << "  -> median (pivot) = " << med << "\n";
}

void report() {
    std::cout << "  comparisons=" << g_comp << "  swaps/moves=" << g_swap << "\n\n";
    g_comp = g_swap = 0;
}

int main(int argc, char *argv[]) {
    if (argc < 3) {
        std::cerr << "Usage: " << argv[0]
                  << " <bubble|selmax|selmin|insertion|merge|lomuto|hoare|quick|quickh|med3|all> <values...>\n";
        return -1;
    }
    std::string alg = argv[1];
    std::vector<int> a;
    for (int k = 2; k < argc; k++) a.push_back(std::atoi(argv[k]));
    std::cout << "input: "; show(a); std::cout << "\n\n";
    bool all = (alg == "all");
    if (all || alg == "bubble")    { std::cout << "BUBBLE (instructor)\n"; bubble(a); report(); }
    if (all || alg == "selmax")    { std::cout << "SELECTION - find max, swap to end (instructor)\n"; selmax(a); report(); }
    if (all || alg == "selmin")    { std::cout << "SELECTION - find min, swap to front (textbook)\n"; selmin(a); report(); }
    if (all || alg == "insertion") { std::cout << "INSERTION\n"; insertion(a); report(); }
    if (all || alg == "merge")     { std::cout << "MERGESORT (top-down)\n"; std::vector<int> r = msort(a, 0, a.size() - 1, 0);
                                     std::cout << "  result: "; show(r); std::cout << "\n"; report(); }
    if (all || alg == "lomuto")    { std::vector<int> b = a; std::cout << "ONE LOMUTO PARTITION (pivot = last)\n";
                                     int p = lomuto(b, 0, b.size() - 1); std::cout << "  p=" << p << " => "; show(b); std::cout << "\n"; report(); }
    if (all || alg == "hoare")     { std::vector<int> b = a; std::cout << "ONE HOARE PARTITION (pivot = first)\n";
                                     int p = hoare(b, 0, b.size() - 1); std::cout << "  returned j=" << p << " => "; show(b, 0, p); std::cout << "\n"; report(); }
    if (all || alg == "quick")     { std::vector<int> b = a; std::cout << "QUICKSORT (Lomuto, instructor quicks)\n"; quick(b, 0, b.size() - 1, 0);
                                     std::cout << "  result: "; show(b); std::cout << "\n"; report(); }
    if (all || alg == "quickh")    { std::vector<int> b = a; std::cout << "QUICKSORT (Hoare)\n"; quickh(b, 0, b.size() - 1, 0);
                                     std::cout << "  result: "; show(b); std::cout << "\n"; report(); }
    if (all || alg == "med3")      { std::cout << "MEDIAN-OF-3\n"; med3(a); std::cout << "\n"; }
    return 0;
}
