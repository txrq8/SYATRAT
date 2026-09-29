# ECE 218 — Verbatim Lecture Transcripts (8/20 – 9/24)

Every handwritten page rendered at 300 dpi, read tile by tile, transcribed verbatim, then independently re-checked against the images. Instructor slips are kept and marked [sic]; every claimed error was verified by compiling/running code.

---

## Page 20260820-1  (written date: 8-2ϕ-2ϕ26 (slashed zeros) = 8-20-2026)

## Template header / footer
- Top-right box: **Date: 8-2ϕ-2ϕ26** (the instructor writes zeros with a slash through them, so this is 8-20-2026).
- Bottom-right box: **Initials:** (left blank).
- The whole drawing is in the left third of the page. The rest of the page is blank grid.

## Title (top, above the memory column)
**MEMORY**

## Top of the memory column
- Upper right: '**Top**' with a squiggly arrow [from the word Top down to the top-right corner of the memory column].
- A short horizontal line runs out to the right from that top-right corner, labelled **fp** (frame pointer).

## Stack region (black)
- Left of the column: **STACK** with a down arrow (vertical line with an open triangular head) to its right [the stack grows down].
- The stack frame is drawn as a top edge and two side walls, with NO bottom edge. The left wall stops just above the 10/15 cells; the right wall goes a little lower. Inside it, from top to bottom:
  - `parameters`
  - `Variables/`
  - `Constants`
  - A smaller inner box (the local array). Its two bottom cells hold **10** (upper cell) and **15** (lower cell). There is a small up arrow inside the box, at the left above the cells [the array's addresses and indices go up]. To the right of the cells are small index marks **1** (beside 10) and **0** (beside 15).
  - At the left: '**arr1** ——o' [arrow from the label arr1 ending in a small open circle at the bottom-left corner of the array box, where element 0 is].
- A short line labelled **sp** ('— sp') leaves the right wall level with the bottom of the array (the bottom of the 15 cell). A small tick continues the right wall there.
- Labels to the right of the frame, top to bottom: **main** / **stack frame**, then **l1**, **c1**, then **local array**. Far right, level with 'stack frame': **R/W**.

## Red annotations (stack smashing)
- [red] **stack smashing**, written to the left of the frame at the level of the top of the array.
- [red] A left arrow points at the top-right corner of the array box. A red dotted vertical line rises from the top of the array box into the word 'Constants' [writing past the top of arr1 runs into the variables and constants above it].
- [red] A left arrow points at the right end of the small green box just below the array. A red dotted vertical line runs down through that box and below it [writing below arr1 runs into the pointer variable].

## Green annotations (pointer to the heap)
- [green] A small flat rectangle directly under arr1, drawn just below the sp level (below where the frame walls stop). This is the pointer variable.
- [green] A line starts inside this box and goes left, then runs down the left side (labelled [green] **ptr**) and turns right into the heap, ending in an arrowhead at the bottom-left of a block in the heap [arrow from ptr on the stack to the heap block].

## Heap region (green)
- Between the stack and the heap, the column walls continue as broken tick marks.
- The heap is bounded by green dashed horizontal lines at its top and bottom and by green vertical walls (with a few black tick marks on the right wall).
- Right of it: [green] **HEAP**   [green] **R/W**.
- Inside: a green block (the allocated array). Its two bottom cells are marked off by lines, with small index marks ':' (1) and 'o' (0) to their right.
- [green] An up arrow to the right of the block [the heap grows up].
- [green] A left arrow outside the lower right wall points at the heap's bottom boundary.
- Below the heap, the column walls continue as broken tick marks (unused space).

## Lower static region (black)
There is a top edge above globals, then the rows below. The side walls go a little below the last row and there is no bottom edge.
| row (top to bottom) | right-side label |
|---|---|
| `globals` | **R/W**, with a dashed marker '- - -' at the line under globals |
| `code` | **R/O** |
| `g. const` | dashed marker '- - -' at the line under g. const |
[So R/O covers the code row and the g. const row, between the two dashed markers.]

## Very bottom
More broken tick-mark walls, then an empty box at the bottom of the column. It has two side walls and a bottom edge but no top edge, and no label.

### Ambiguous handwriting — reading chosen

| As written | Possible readings | Chosen | Why |
|---|---|---|---|
| Date field 8-2ϕ-2ϕ26 | 8-24-2026 / 8-20-2026 | 8-20-2026 | The instructor writes every zero with a slash, and the year shows the same stroke (2ϕ26 = 2026). The file name is ECE218F20260820. |
| 'loed array' beside the lower part of the frame | local array / load array | local array | It labels the array box inside main's stack frame, and hello2.cpp declares a local int arr1[10];. |
| 'L1' / '21' under 'stack frame' | l1 / L1 / 21 | l1 | hello2.cpp declares int l1 = 12; and const int c1 = 14; as main's locals, and the next label is c1. |
| 'err1' label with an arrow to the array | arr1 / err1 | arr1 | In hello2.cpp, arr1[0] = 15; arr1[1] = 10; matches the 15 (bottom) and 10 (above it) drawn in the cells. |
| Small marks '1' and 'o' to the right of the 10 and 15 cells (also ':' and 'o' next to the heap block) | indices 1 and 0 / stray dots / colon | index 1 (next to 10) and index 0 (next to 15) | arr1[1]=10 and arr1[0]=15 in hello2.cpp. The heap block copies the same layout. |
| Green 'ptr' | ptr / aptr | ptr (as written) | The code names it aptr (int *aptr = new int[10];), but the page clearly says ptr. |
| 'Veriebles/ Constounts' | Variables/Constants | Variables/ Constants | The instructor's handwriting. Local variables and constants (l1, c1) live in the frame. |
| 'steek smeshing' in red | stack smashing | stack smashing | The red arrows mark writes going past both ends of the array. This matches the gcc message '*** stack smashing detected ***'. |
| 'R/0' beside code | R/O (read-only) / R/0 | R/O | The code segment is read-only and the rows above are R/W. |
| 'g. const' | global const / g. const / g1 const | g. const (global constants) | hello2.cpp has const int g2 = 23; at global scope, and when run &g2 is at a lower address than &g1, which matches its place below globals. |
| Squiggle from 'Top' | arrow to the top of memory / scribble | arrow pointing to the top of the memory column | It ends at the column's top-right corner, where the fp line starts. |
| Green pointer box position relative to sp | inside main's frame / just below the frame | described as drawn: directly under arr1, just below the sp line level | The sp line is level with the bottom of the 15 cell and the green box is drawn beneath it. In the real program, aptr is in main's frame just below arr1 (&aptr = arr1 - 8). |

### Board slips / gotchas (verified)

- The order of locals inside a frame is chosen by the compiler; the drawing only shows the idea. I ran the instructor's hello2.cpp (g++ 13.3): relative to arr1, l1 is at arr1-0x14, c1 at arr1-0x10 and aptr at arr1-0x8 (e.g. ...4e5c, ...4e60, ...4e68, ...4e70; the exact addresses change on every run because of ASLR). So the scalar locals sit at LOWER addresses than the array, although the drawing puts 'Variables/Constants' above it. The pointer sitting directly under arr1 does match the drawing.
- Stack smashing check (re-verified): a function with int arr1[10]; that writes arr1[0..15], compiled with -fstack-protector-strong, prints the line after the writes and then '*** stack smashing detected ***: terminated' and aborts (exit 134). The error is caught when the function returns, not at the bad write.
- The label 'ptr' is 'aptr' in the matching code (hello2.cpp). The heap block can only be reached through that pointer, which lives on the stack. The code frees it with delete [] aptr; aptr = nullptr;.
- Verified with hello2.cpp: &g2 (global const, ...6008) < &g1 (global, ...8010) < heap block (...d2b0) < stack (0x7ffd...). The stack is at the highest addresses and grows down, and the heap grows up. This matches the drawing.
- Verified: code is actually BELOW the global constants on g++/Linux. main (.text) ...b1a9 < &g2 (.rodata) ...c008 < &g1 (.data) ...e010, and readelf shows .text 0x1120, .rodata 0x2000, .data 0x4000. The drawing puts code above g. const. Both are read-only (R/O), which the drawing gets right; only their relative order differs, and that depends on the toolchain.
- The empty box at the bottom of the column has no label. Do not guess a meaning for it on an exam; the labelled sections are STACK, HEAP, globals, code and g. const.

---

## Page 20260827-1  (written date: 8-27-2ϕ26 = 8-27-2026)

## Template header / footer
- Top-right box: **Date: 8-27-2ϕ26** (8-27-2026).
- Bottom-right: **Initials:** (blank).

## Title row
**BUBBLE SORT**          **n=5**

Top right, under the date box: **↓ Inner loop : j** [the symbol is a short down arrow with a crossbar and an open triangular head; it heads the column of per-pass counts below].

## Pass trace (numbers black unless marked [green]; green = in final sorted place)
The label **i** sits above the pass labels (the pass number is the outer loop i). Each arc is a curved arrow joining the two compared neighbours; 's' under it means they were swapped.

**Pass 1**, with 5 snapshots left to right:
1. `5 4 8 1 3`: arc under **5–4**, marked **s** (swap)
2. `4 5 8 1 3`: arc under **5–8**, no s (compare only)
3. `4 5 8 1 3`: arc under **8–1**, marked **s**
4. `4 5 1 8 3`: arc under **8–3**, marked **s**
5. `4 5 1 3` [green]`8`

Right column: **=> 4**

**Pass 2**:
1. `4 5 1 3` [green]`8`: arc under **4–5**, no s
2. `4 5 1 3` [green]`8`: arc under **5–1**, marked **s**
3. `4 1 5 3` [green]`8`: arc under **5–3**, marked **s**
4. `4 1 3` [green]`5 8`

Right column: **=> 3**

**Pass 3**:
1. `4 1 3` [green]`5 8`: arc under **4–1**, marked **s**
2. `1 4 3` [green]`5 8`: arc under **4–3**, marked **s**
3. `1 3` [green]`4 5 8`

Right column: **=> 2** (the 2 is written Z-shaped)

**Pass4**:
1. `1 3` [green]`4 5 8`: arc under **1–3**, no s
2. `1` [green]`3 4 5 8`

Right column: **=> 1**

Final row: [green]`1 3 4 5 8`   **=> sorted**

## Loop structure (black, with red generalisation)
```
outer loop :   for i : 0 —> 4              [red] 0 —> N-1          [red] i<N
inner loop :     for j : 0 —> 3 (i=0)      [red] 0 —> N-2-i        [red] j < N-1-i

                   if a[j] > a[j+1]            ]
                          swap a[j], a[j+1]    ]   <- one bracket around both lines
```
(The dot of the i in 'for i' is drawn as a small open circle.)

## Red block, right side (inner-loop range for each i)
```
i=0 : j :  0 —> N-2   : N-1
i=1 : j :  0 —> N-3   : N-2
  ⋮                     N-2      <- [sic] written 'N-Ƶ' (Z-shaped 2 with a crossbar); should be N-3
                          ⋮
                          1
                          0
```

## Black formula, right side
Σ_{0}^{N} n = (N+1)N / 2   (Σ with lower limit 0 and upper limit N)

## Worst-case analysis (red)
**Worst case :** (comp + swap) (N-1 + N-2 + N-3 + . . . + 0)
- A red curly brace under (N-1 + … + 0), and below it:
  Σ_{0}^{N-1} n = N(N-1) / 2 = N²/2 - N/2   (the '=' signs are written small, like '₂')

Next line:
N²/2 (comp + swap) - N/2 (comp + swap)
- Black check marks ✓ above 'comp' and 'swap' in the first term, with tiny red double marks (=) under them.

Below the first term (under 'comp'), directly above O(N²): a red **=**

**N —> ∞  :  O(N²)**

Bottom right (red):
**Best case : O(N)**
**sorted (early exit)**

### Ambiguous handwriting — reading chosen

| As written | Possible readings | Chosen | Why |
|---|---|---|---|
| Symbol before 'Inner loop : j' (top right) | ↓ down arrow / # 'number of' | ↓ (down arrow) | A vertical stroke with a crossbar ending in an open triangle, like the STACK arrow on the 8/20 page. Either way, the column below lists how many inner-loop iterations each pass does (4, 3, 2, 1). |
| Third entry of the red count column, 'N-Ƶ' | N-2 / N-3 / N-Z | N-2 [sic] | The last character is a Z-shaped 2 with a crossbar, not a 3; the instructor also writes the Pass 3 count '=> 2' as a Z. The sequence N-1, N-2, …, 1, 0 means this entry should be N-3 (for i=2), so it is recorded as a slip. |
| 'a{j+1]' / 'aΣj+1]' in the pseudocode | a[j+1] / a{j+1} | a[j+1] | Hasty square brackets. It is array indexing, and the instructor's sort.cpp uses arr[j+1]. |
| Small '₂'-like marks between terms: 'Σn ₂ N(N-1)/2 ₂ N²/2 - N/2' | = / 2 | = | They sit where equality signs belong in a chain of equal expressions, and 'N(N-1)/2 · 2' would make no sense. |
| Tiny red marks under 'comp' and 'swap' in N²/2 (comp + swap) | small '=' underline / 'const' mark / stray ink | small double-underline marks, described but not interpreted | They are only two short dashes. Together with the black check marks they seem to say that comp and swap each cost a constant amount. |
| 'Sor ted (cerly exit)' | sorted (early exit) | sorted (early exit) | Handwriting. The best case is an already-sorted input with early termination. |
| 'for i° :' | for i : / for i0 | for i : | The dot of the i is drawn as a small circle. It parallels 'for j :' on the next line. |
| Snapshot 2 of Pass 1, '4 s 8 1 3' | 4 5 8 1 3 | 4 5 8 1 3 | It follows swapping 5 and 4 in '5 4 8 1 3'; the 5 is just written quickly. |
| 'Pass4' / 'Passy' | Pass 4 | Pass4 | The fourth pass row comes after Pass 1, 2 and 3. |

### Board slips / gotchas (verified)

- The outer loop runs 'for i : 0 —> 4', i.e. 0 —> N-1 (i<N), which is N passes, but only N-1 passes are drawn (Pass 1–4 for n=5). The last iteration (i=N-1) has j < N-1-i = 0, so its inner loop does nothing. It is harmless but wasteful, and it matches the instructor's sort.cpp (for(int i=0;i<n;i++)). Re-verified with trace.cpp: 5 4 8 1 3 gives 1 3 4 5 8 after pass 3, with 10 comparisons and 7 swaps. The 7 's' marks on the page agree (3+2+2+0), and every snapshot row follows from the one before.
- 'Best case : O(N) sorted (early exit)' needs a 'swapped' flag that stops the outer loop after a pass with no swaps. Neither the pseudocode on this page nor sort.cpp/sortb.cpp has one. Re-verified: on the sorted input 1 2 3 4 5 the literal loops still make 10 comparisons (N(N-1)/2, so O(N²)); with a swapped flag they make 4 (N-1).
- The red count column reads N-1, N-2, N-2, …, 1, 0. The third entry should be N-3 (i=2 means j: 0 —> N-4, which is N-3 comparisons).
- The worst case assumes every comparison also swaps (reverse-sorted input). Re-verified: 5 4 3 2 1 gives 10 comparisons and 10 swaps = N(N-1)/2 each.
- The page shows two different sum identities: Σ_{0}^{N-1} n = N(N-1)/2, which is the one bubble sort uses, and Σ_{0}^{N} n = (N+1)N/2 (right side). Do not mix up the upper limits.
- 'for j : 0 —> 3' and '0 —> N-2-i' are inclusive ranges; in C++ they become j < N-1-i. Writing j <= N-1-i would read a[j+1] = a[N-i], which is one past the unsorted part and, when i=0, out of bounds.
- 'swap a[j], a[j+1]' is pseudocode. In C++, use std::swap(a[j], a[j+1]) or the instructor's own swap(int&, int&) from sort.cpp.

---

## Page 20260827-2  (written date: 8-27-2ϕ26 = 8-27-2026)

## Template header / footer
- Top-right box: **Date: 8-27-2ϕ26** (8-27-2026).
- Bottom-right: **Initials:** (blank).

## Title
**SELECTION SORT**

## Column headers
- Far left: **i** (above the pass labels P1…P5).
- Right side: **j** above the first count column. The headers are **4 comp** (red dashed line above it) and **1 swap** (red dashed line above it); these are also the Pass 1 values.

## Trace (black numbers unless marked [green]; black arrows = 'find max' pointers; the longer arrow with a hook is max_loc, the short hooked arrow is j, and a line joins them)

**P1** ('**find max**' written under the label)
- A red down-arrow mark above the **4** (index 1), with a red dashed line running right to a short black overline above the **3** (index 4) [j runs from 1 to the last unsorted slot N-1-i; the black overline marks the slot that receives the max].
1. `5 4 8 1 3`: max_loc arrow under **5**, j under **4**. Below: **max_loc = 0**
2. `5 4 8 1 3`: max_loc under **5**, j under **8**
3. `5 4 8 1 3`: max_loc under **8**, j under **1**
4. `5 4 8 1 3`: max_loc under **8**, j under **3**
5. `5 4 3 1` [green]`8`: [green] bracket '{ swap }' from the **3** (index 2) to the **8** (index 4)

Counts: **4 comp**, **1 swap**

**P2** (black overline above the **1** at index 3)
1. `5 4 3 1` [green]`8`: max_loc under 5, j under 4
2. `5 4 3 1` [green]`8`: max_loc under 5, j under 3
3. `5 4 3 1` [green]`8`: max_loc under 5, j under 1
4. `1 4 3` [green]`5 8`: [green] '⌊ swap ⌋' bracket joining the **1** (index 0) and the **5** (index 3)

Counts: **3**, **1**

**P3** (black overline above the **3** at index 2)
1. `1 4 3` [green]`5 8`: max_loc under 1, j under 4
2. `1 4 3` [green]`5 8`: max_loc under 4, j under 3
3. `1 3` [green]`4 5 8`: [green] an up arrow under the **3** joined by a line to an up-pointing hook under the **4**, labelled [green] **swap**

Counts: **2**, **1**

**P4** (black overline above the **3** at index 1)
1. `1 3` [green]`4 5 8`: max_loc under 1, j under 3
2. `1` [green]`3 4 5 8`: [green] a small U-shaped loop with two arrowheads, both pointing up at the **3** (swap with itself), labelled [green] **swap**

Counts: **1**, **0**, with a black **=** under the comp-column '1' [end or total of the column]

**P5** (black overline above the **1** at index 0)
1. `1` [green]`3 4 5 8`: a single arrow under the **1** (no j)

No counts written for P5.

## Pseudocode (all red)
```
outer:   j : 0 ——> N-1                      < N
inner        i : 1 ——> N-1-i                < N-i
             ¦   max_loc = 0              ]
             ¦   if  a[j] > a[max_loc]    ]  => N²
             ¦          max_loc = j       ]
             ¦                                           => O(N²)
             swap  a[max_loc], a[ N-1-i ] ]  => N
```
- A red dashed vertical line (¦) hangs from under the 'i' of the INNER-loop header and runs down to just above `swap`. It marks the inner loop's body: `max_loc = 0`, `if …` and `max_loc = j` are to its right, at the same indentation (max_loc = j indented further under the if).
- `swap` starts in the same column as the inner-loop header and the dashed line, below where the dashed line ends. So it is after the inner loop, in the outer loop's body.
- One red bracket ] groups the three lines max_loc = 0 / if … / max_loc = j, and points to **=> N²**.
- A second red bracket ] around the swap line points to **=> N**.
- To the right, between the two levels: **=> O(N²)**.

### Ambiguous handwriting — reading chosen

| As written | Possible readings | Chosen | Why |
|---|---|---|---|
| Loop variables 'outer: j : 0 → N-1' / 'inner i : 1 → N-1-i' | as written (outer j, inner i) / swapped (outer i, inner j) | Transcribed as written: outer j, inner i [sic] | The letters are clearly j (outer) and i (inner). But the body uses a[j] as the scan index and N-1-i as the pass-dependent end, and the trace headers put i on the passes and j above the comp column. So the intended code is outer i, inner j. |
| Red mark above the '4' in P1 row 1 | ↓ down arrow / 'b' / 'ϕ' | red down-arrow mark showing where j starts (index 1) | It is a vertical stroke with a small loop at its lower right, followed by a red dashed line to the black overline above index 4. Together they spell out the inner range j: 1 → N-1-i. |
| 'max-loc' / 'mox-loc' / 'mex-loc' | max_loc / max-loc | max_loc | It is an identifier, and the separator is a low dash. A hyphen would parse as subtraction in C++. |
| 'a{max_loc]' and 'a[mox-loc]' | a[max_loc] | a[max_loc] | Hand-drawn square brackets. |
| P4 label written like 'Pφ' | P4 / Pφ | P4 | It comes between P3 and P5. |
| '=' under the '1' in the comp column (P4 row) | equals / total line / stray mark | '=' (probably a total or end-of-column mark) | No total is written after it. Summing the column gives 4+3+2+1 = 10 = N(N-1)/2. |
| Green arrows under the 3 in P4 row 2 | self-swap of a[1] with a[1] / a mark on the 3 | self-swap (max_loc = N-1-i = 1) | The P4 find-max leaves max_loc = 1, which is also the target slot N-1-i = 1. The swap column still records 0. |
| Overline marks (short black bars above one element per pass) | marks the last unsorted slot N-1-i / underline of something above | marks the target slot N-1-i | They sit above index 4, 3, 2, 1, 0 for P1…P5, which is exactly where the max is swapped to. |
| Scope of the red dashed line | inner-loop body / outer-loop body | inner-loop body | It starts under the 'i' of the inner header (not under the outer 'j'), and the three body lines sit to its right. swap is aligned with the inner header, i.e. after the inner loop. |

### Board slips / gotchas (verified)

- The loop labels are swapped: 'outer: j : 0 → N-1' and 'inner i : 1 → N-1-i'. Copied literally, the inner bound N-1-i refers to its own loop variable. Use for (int i = 0; i < N; i++) { int max_loc = 0; for (int j = 1; j < N - i; j++) { if (a[j] > a[max_loc]) max_loc = j; } swap(a[max_loc], a[N-1-i]); }. Re-verified: this gives 1 3 4 5 8, and every snapshot on the page matches it (P1 gives 5 4 3 1 8, P2 gives 1 4 3 5 8, P3 gives 1 3 4 5 8).
- 'max_loc = 0' is drawn inside the inner (dashed) scope, at the same indentation as the 'if'. If it really goes inside the inner loop, max_loc resets on every j and the sort breaks. Re-verified in C++: that literal version turns 5 4 8 1 3 into 1 4 8 3 5, while setting max_loc = 0 once per outer pass, before the inner loop, gives 1 3 4 5 8.
- The outer range 0 → N-1 (<N) makes N passes, but only N-1 are needed. The last pass (P5 on the page) has an empty inner loop (j: 1 → 0) and swaps a[0] with itself.
- The pseudocode swaps without checking, so the code makes one swap per pass: N swap calls, which matches '=> N'. That is 5 for N=5: 3 real swaps plus self-swaps in P4 and P5 (verified). The page's swap column (1, 1, 1, 0) counts only real exchanges, even though P4 draws a green 'swap' under the 3. Say which count you mean on an exam.
- Comparisons are 4+3+2+1 = 10 = N(N-1)/2 for N=5 whatever the input order (verified on 5 4 8 1 3 and on the sorted 1 3 4 5 8). '=> N²' is the order of growth, not the exact count, and selection sort has no better best case: O(N²) always.
- This version finds the MAX and moves it to the END (index N-1-i). The more common textbook version finds the min and moves it to the front. Follow the instructor's max version.

---

## Page 20260827-3  (written date: 8-27-2ϕ26 = 8-27-2026)

## Template header / footer
- Top-right box: **Date: 8-27-2ϕ26** (8-27-2026).
- Bottom-right: **Initials:** (blank).

## Title
**INSERTION SORT**

## Concept sketch (top)
- [green] **Sorted** above [green] `1 6 9`, with a [green] bracket under 1 6 9.
- Black **unsorted set** above `3 8 1` (black). A small black bracket sits under the **3**.
- A down arrow from the 3 to the text:
  **Insert into sorted set**
  **in correct location**

## Trace (black = element being inserted; [green] = sorted part; each arc is a one-headed hook that starts under the element being inserted, with its arrowhead at the left neighbour it is compared with; 's' = swap)

**Row 1** (inserting 3):
1. [green]`1 6 9` `3`: arc under **9–3**, marked **s**
2. [green]`1 6` `3` [green]`9`: arc under **6–3**, marked **s**
3. [green]`1` `3` [green]`6 9`: arc under **1–3**, no s (stop)
4. [green]`1 3 6 9`

**Row 2** (inserting 8):
1. [green]`1 3 6 9` `8`: arc under **9–8**, marked **s**
2. [green]`1 3 6` `8` [green]`9`: arc under **6–8**, no s (stop)
3. [green]`1 3 6 8 9`

**Row 3** (inserting 1):
1. [green]`1 3 6 8 9` `1`: arc under **9–1**, marked **s**
(nothing further drawn)

## Divider
A long, slightly slanted black horizontal line across the page.

## Diagram A: scanning left (bottom left)
- [purple] **i** with a [purple] down arrow pointing at the **9**. To its left, two [purple] left arrows, above the gap between 6 and 9 and the gap between 1 and 6 [i moves left].
- Row: [green]`1 6 9` `3`
- Under the row, three [purple] hooked arrows, each starting in the gap to an element's right and curving up into that element: from beside the 3 up to the 9, from between 9 and 6 up to the 6, and from between 6 and 1 up to the 1 [each step compares with the next element to the left].
- A black up arrow under the 3 labelled **next_element**.
- [purple] Short dashed vertical lines, each with a small circle on top, under the **1** and under the **6**.

## Diagram B: move/shift version (bottom middle)
- [purple] **i** with a [purple] down arrow pointing at the **1** (index 0).
- Row: [green]`1 6 9` `3`
- Above: **move** with a curved arrow from the 6 into the 9's slot, and **move** with a curved arrow from the 9 into the 3's slot [the larger elements shift right one place].
- A black down arrow from the 3 to a copy **3** written below [the 3 is saved in a temporary].
- A black L-shaped arrow from the saved **3**, left and then up into the 6's slot (index 1) [the 3 is placed at i+1].

### Ambiguous handwriting — reading chosen

| As written | Possible readings | Chosen | Why |
|---|---|---|---|
| 'unsorted sot' | unsorted set / unsorted sort | unsorted set | It pairs with 'Sorted' and with 'Insert into sorted set' just below. |
| 'next_element' | next_element / next-element / next element | next_element | There is an underscore-like low dash between the words, as in the identifier style of max_loc on the previous page. |
| Purple dashed lines with small circles under the 1 and the 6 (Diagram A) | candidate insertion positions / j positions as the scan moves left / markers that the elements shift | described as drawn (dashed vertical lines with small circles), not interpreted | They carry no label, and they sit under the two positions the purple hooks reach. |
| Purple i position in Diagram B (above the 1) | i where the scan stopped / i = start | i points at index 0, where the scan stopped because 1 < 3 | The L-shaped arrow drops the 3 at index 1, i.e. i+1. |
| Arc in Row 1 snapshot 3 (under 1–3) with no 's' | a compare with no swap / an unlabelled swap | compare only (stop) | The result, 1 3 6 9, keeps 1 before 3. Every other arc that swaps is marked 's'. |

### Board slips / gotchas (verified)

- Row 3 is unfinished: only the first swap (9↔1) of inserting the last 1 is drawn. Inserting that 1 takes 5 comparisons and 4 swaps IN TOTAL, so 3 more swaps after the one drawn, giving 1 1 3 6 8 9. Re-verified with trace.cpp: inserting 3 takes 3 comparisons and 2 swaps, inserting 8 takes 2 and 1, inserting 1 takes 5 and 4. The whole array 1 6 9 3 8 1 takes 12 comparisons and 7 swaps.
- The example array (1 6 9 3 8 1) has two 1s. Using a strict '>' test (shift only while a[j-1] > key) stops at the equal 1, which keeps insertion sort stable. Re-verified with tagged values: '>' gives 1A 1B 3 6 8 9 (7 swaps); '>=' gives 1B 1A 3 6 8 9 (8 swaps), so it loses stability.
- The page shows two versions. The upper trace swaps adjacent elements ('s'); Diagram B holds the element in a temporary, moves the larger elements right one place ('move'), and drops the element into the hole. They give the same result, but a swap costs 3 assignments and a move costs 1.
- In Diagram B the inner scan must stop at index 0 (check j > 0, or i >= 0 when counting down). Otherwise reading a[i] when i is -1 is out of bounds whenever the key is smaller than everything on its left, as the final 1 is here.
- No pseudocode or complexity is written on this page. Do not expect the O(N²) worst case / O(N) best case (already sorted) figures here; they are not on the page.

---

## Page 20260901-1  (written date: 9/1/2026 (header box reads "Date: 9/1/2026"; the year is a scribbled "2026"))

# 20260901-1: Merge algorithm and mergesort

[Page layout: printed "Date:" box at top right and printed "Initials:" box at bottom right, left empty. A hand-drawn vertical line from top to bottom, a little right of centre, splits the page. The LEFT half has the merge trace and the merge pseudocode. The RIGHT half has the mergesort recursion tree, the complexity and the merge_sort pseudocode.]

## Header (top right)
Date:  9/1/2026

---

## Region L1 (top left): merge trace of two sorted arrays

[green] **A**  (label above the first array)
[green dashed arrow: starts with a small vertical tick above the left edge of 12 (over the gap between 9 and 12) and points right past 14. It marks the leftover 12, 14 that are copied at the end]
[green] `1    9    12    14`
[green pointer row under A: ↑ under 1, then a hooked arrow → ↑ under 9, then a hooked arrow → ↑ under 12]
[black step numbers: `1.` left of the ↑ under 1. `2.`, `3.`, `4.` stacked one under another beneath the 1→9 arrow, next to the ↑ under 9. `5.` beneath the 9→12 arrow, next to the ↑ under 12]
[green] **i**  (under the first pointer, below 1)

[red] **B**  (label above the second array; drawn so it looks like "8")
[red] `3    6    10`
[red pointer row: ↑ under 3, then a hooked arrow → ↑ under 6, then a hooked arrow → ↑ under 10, then a red horizontal line — running off to the right past 10 (j goes past the end)]
[black step numbers: `1.` and `2.` stacked left of the ↑ under 3. `3.` under the 3→6 arrow. `4.` and `5.` stacked under the 6→10 arrow]
[red] **j**  (under the first pointer, below 3)

[black, to the right]  `6.  j is done`

[black title, small caps, right of the trace]  **MERGE  ALGORITHM**

[black] **C**  (label above the merged array)
`1    3    6    9    10    12    14`   ← each value is coloured by its source: 1 [green], 3 [red], 6 [red], 9 [green], 10 [red], 12 [green], 14 [green]
[black pointer row: ↑ under 1 → ↑ under 3 → ↑ under 6 → ↑ under 9 → ↑ under 10 → ↑ under 12, with hooked arrows between them. There is NO pointer under 14]
[black step numbers: `1.` left of the first ↑, then `2.` `3.` `4.` `5.` `6.` under the successive arrows]
**K**  (under the first pointer; written like a capital K)

---

## Region L2 (left, middle to bottom): merge pseudocode [black]

```
i=0, j=0, k=0

while ( i< len(A) && (j< len(B)) )
          if    A[i] < B[j]
                        C[k] = A[i]
                        k++, i++
          else
                        C[t] = B[j]          <- [sic] letter looks like t (or l); meant k
                        k++, j++

while ( i< len(A) )
          C[k]= A[i]
          k++, i++

while ( j< len(B) )
          C[k] = B[j]
          k++, j++
```
[Notes on the ink: in `if A[i] < B[j]` the i inside A[ ] is an ink blob (written over). There are no braces and no semicolons; nesting is shown only by indentation. Square brackets are sometimes drawn like `{`, `£` or `3`. The `(` before the second j looks like a `c`.]

---

## Region R1 (right half, top): mergesort recursion tree [black]

[`s` with ↓ arrow above the first element (5). `e` with ↓ arrow above the last element (6); the `e` is written just inside the bottom edge of the Date box]

Level 0:   `|5  4  8|` `||` `|1  3  6|`   [two brackets side by side; the double bar between 8 and 1 marks the split. The 6 is an overstrike and looks partly like 4]
           [`/` under the left half, `\` under the right half. Small ↓ arrows above the 1 of `1 3` and above `6` on the next level]
Level 1:   `|5  4|` `|8|`          `|1  3|` `|6|`
           [`/\` under [5 4]. A dotted vertical line straight down from [8]. `/\` under [1 3]. A dashed diagonal from [6] down to the right]
Level 2:   `N/8`  `|5|`   `|4|`      `8` (with a dotted underline)        `|1|`   `|3|`        `6` (no bracket)
           [`\ m /` joins [5] and [4], with a second `N/8` written just right of the `/` (below the right end of [4]). `\m /` joins [1] and [3]]  (m = merge)
           `N/4` [written rotated]  `|4  5|`   `|8|`          `|1  3|`   `|6|`
           [`\  m  /` joins [4 5] and [8], with a curly brace ⏟ under the pair labelled `N/2`. `\  m  /` joins [1 3] and [6], with a curly brace ⏟ labelled `N/2`]
           `N/2` `|4  5  8|`                     `|1  3  6|` `N/2`
           [`\      m      /` joins the two halves]
Final:     `|1  3  4  5  6  8|`   with a small `N` at its lower left

[A long vertical line to the left of the lower levels of the tree, labelled at its bottom:]  `log₂N`

[Far right column:]  `recursive split`  [long arrow pointing down from it]
`N`   (level with the single-element row)
`N`   (level with the [4 5] / [1 3] row)
`N`   (level with the [4 5 8] / [1 3 6] row)
`———`   (horizontal line under the last N, like a sum line)

---

## Region R2 (right half, middle)

`Array of size N   =>        log₂ N`
`                          # of divisions`   (written under log₂ N)

`=>  O( N log₂N )`   (large)

---

## Region R3 (right half, bottom): merge_sort pseudocode

```
merge_sort( A, start, end)
     mid_point =   end - start +1
                   ------------   + start
                         2

       C = merge_sort (A , start , mid-point)
       D = merge_sort ( A, mid.point+1 , end)
       E = merge ( C , len(C), D , len(D))
       return E
```
[The name is spelled three ways: `mid_point` (a stray dot above a low dash), `mid-point` and `mid.point`. All three mean the same variable. In all three merge_sort lines the joining stroke is short and sits low, near the baseline; in the header there is a small gap before it ('merge _sort').]

[Right margin, just below the O(N log₂N) line and above the level of the merge_sort header:]  `A , Work`  [curved arrow over the top from A to Work, and a curved arrow underneath from Work back to A. It means the data ping-pongs between A and a work array]

## Footer (bottom right)
Initials:  (blank)

### Ambiguous handwriting — reading chosen

| As written | Possible readings | Chosen | Why |
|---|---|---|---|
| Red label above the array 3 6 10 | B / 8 | B | Paired with the green A above the first array and the black C above the result. The pseudocode indexes B[j], and the red j pointer lives under this array. |
| Else branch: C[?] = B[j] | C[t] / C[l] / C[k] | C[t] [sic], meaning C[k] | The letter is clearly different from the k in C[k] = A[i] on the line above; it looks like t or l. Every other assignment uses k, and the next line is k++, j++, so k is intended. |
| while ( i< len(A) && (j< len(B)) ) | '(j' / 'cj' | (j | With '(' the parentheses balance: while( ... (j<len(B)) ). The stroke is the same shape as the other opening parens on the page. |
| if  A[i] < B[j] | A[i] (i written as a blob) / A[j] | A[i] | The merge compares A's current element with B's current element, and the body copies A[i]. The dark blob is an overwritten i. |
| mid_point / mid-point / mid.point | 'mid :-point', 'mid_point', 'mid-point', 'mid.point' | First line transcribed as mid_point, then mid-point and mid.point exactly as they appear | The first occurrence has a stray dot above a low underscore-like dash. The C line has a mid-height dash and the D line a dot. All clearly name one variable. |
| merge_sort( A, start, end) | merge_sort / merge-sort | merge_sort | On all three lines the joining stroke sits low, near the baseline, so it reads as an underscore (the header also has a small gap before it). A hyphen would not be a valid C++ identifier anyway. |
| Top-level right half \|1 3 6\|: last digit | 6 / 4 (overstrike) | 6 | The lower levels show 6 ([6], 6, [6], [1 3 6]) and the final array 1 3 4 5 6 8 has only one 4, which comes from the left half. |
| Leaf-level size labels 'N/8' | N/8 / N/3 | N/8 | The 8 is written with an open top so it resembles 3. The labels form the halving sequence N/8 → N/4 → N/2 → N going up the tree. |
| Label under the C pointer row | K / k | k (drawn as capital K) | The pseudocode uses lowercase k as the index into C. |
| Small step numbers under A: '2.' '3.' '4.' | 2. / 8. | 2. | The sequence 1. 2. 3. 4. 5. runs in order. This matches the merge simulation: i stays on 9 during comparisons 2–4 and is on 12 at step 5. |
| s and e arrows on the tree | s = start / 5; e = end | s (start) above the first element, e (end) above the last element | They match the merge_sort(A, start, end) parameters. The s is a small lowercase letter above a ↓ arrow, not the digit 5. |
| Year in the date box | 2026 / 2024 / 2020 | 2026 | The last two digits are scribbled. The 9/3 page's second date line, 9-3-2026, is more legible, and the upload file name is ECE218F20260901. |

### Board slips / gotchas (verified)

- merge_sort has NO base case, and its midpoint formula mid_point = (end-start+1)/2 + start returns end on a 2-element range. merge_sort(A,0,1) calls merge_sort(A,0,1) again forever; a 1-element range (s,s) also recurses on (s,s) forever. VERIFIED in C++: the call sequence is (0,5) → (0,3) → (0,2) → (0,1) → (0,1) → (0,1) ... until the depth guard trips. Fix: add `if (start >= end) return;` and use `mid = (start+end)/2`, i.e. (end-start)/2 + start, which is the board formula without the +1.
- The board formula also does not produce the board's own tree. For start=0, end=5 it gives mid_point=3, so the halves would be [5 4 8 1] | [3 6]. The tree draws 5 4 8 | 1 3 6, which is what mid=(start+end)/2=2 gives. VERIFIED (printed mid_point(0,5)=3, (0,2)=1, (0,1)=1; trace.cpp's mergesort with mid=(start+end)/2 reproduces the board tree exactly).
- Else branch writes `C[t] = B[j]` [sic]; it must be C[k]. If copied literally, t is an undeclared variable.
- The variable name is written three ways: mid_point, mid-point and mid.point. In C++, `mid-point` parses as mid minus point and `mid.point` as member access. Use one underscore name. merge_sort's joining stroke is low on all three lines, so it reads as merge_sort, though it could be mistaken for merge-sort, which is also not a valid identifier.
- `len(A)`, `len(B)`, `len(C)`, `len(D)` are Python-style pseudocode. C++ raw arrays and pointers have no len(), so the lengths must be passed in as parameters.
- `if A[i] < B[j]` uses a strict < comparison. On equal keys the element from B is copied first, so this merge (and the mergesort built on it) is NOT stable; `<=` makes it stable. VERIFIED: with equal keys the test is false and B's element is taken first.
- The worked merge takes 5 comparisons (1<3, 3, 6, 9<10, 10). After '6. j is done' the leftover 12, 14 of A are copied by the `while (i < len(A))` loop. VERIFIED: C = 1 3 6 9 10 12 14 with 5 comparisons.
- The tree labels N/8, N/4, N/2 are generic (they assume N=8 or another power of 2). With N=6 the pieces have sizes 1, 2/1 and 3, and log₂6 ≈ 2.58, so there are ceil(log₂N) = 3 merge levels. Each level still does about N work, giving O(N log₂N).
- merge_sort as written returns a new array E at every call, so it needs O(N) extra memory. The margin note 'A ⇄ Work' refers to the usual implementation, which alternates between A and a single work array.

---

## Page 20260901-2  (written date: 9-1-2026 (header box reads "Date: 9-1-2026"; year scribbled))

# 20260901-2: 'split?' (start of the quicksort idea). The page is nearly empty.

## Header (top right)
Date:  9-1-2026

## Region 1 (top left) [black unless noted]

`|8    1   12    3    6    9|`   (bracket underneath the whole array)

[↓ arrow down from the middle of the bracket]  `split?`

[green] `1    3    6`             [red] `8    9    12`
[curly brace ⏟ under the green group]      [curly brace ⏟ under the red group]
`1.` ↓   (arrow down under the green group; it points to nothing)      `2.` ↓   (arrow down under the red group; it points to nothing)

## Rest of page
[Blank grid. An ink-pixel check found zero ink in the middle and lower-left tiles; only the printed boxes are present.]

## Footer (bottom right)
Initials:  (blank)

[NOTE: The top-left region of the 9/3 page is pixel-for-pixel identical to this page (verified by image diff: 0 differing pixels). The instructor continued this same page on 9/3.]

### Ambiguous handwriting — reading chosen

| As written | Possible readings | Chosen | Why |
|---|---|---|---|
| split? | split? / spilt? | split? | The context is dividing the array into two groups; the l and i strokes are just compressed. |
| '1.' and '2.' with down arrows under the two braces | step numbers (sort part 1, then sort part 2) / arrows to a result that was never written | step numbers 1. and 2., arrows pointing to nothing | Nothing is written below the arrows on this page or on the continued 9/3 page. They read as 'sort part 1, then sort part 2': split by VALUE (small values green, large values red), so no merge is needed afterwards. |
| Colour grouping 1 3 6 (green) vs 8 9 12 (red) | sorted halves / partition by value | partition by value (values ≤ 6 green, values ≥ 8 red), each group already shown in sorted order | The source array 8 1 12 3 6 9 is split into its three smallest and three largest values. This leads into QUICKSORT on the continued 9/3 page. |

### Board slips / gotchas (verified)

- This page is not finished on 9/1. Its content is continued on the 9/3 page, whose top-left region is pixel-identical (verified). The groups '1 3 6' and '8 9 12' are drawn already sorted, but a partition step only guarantees 'all small values | all large values'. Each group still has to be sorted recursively, which is what the '1.' and '2.' arrows stand for.

---

## Page 20260903-1  (written date: 9-3-2026 (header box has two lines: "9-1-2026" and "9-3-2026"; this is the 9/1 page 2 continued))

# 20260903-1: Quicksort, partition (Lomuto and Hoare), median-of-3

## Header (top right)
Date:  9-1-2026
       9-3-2026

---

## Region 1 (top left, carried over unchanged from the 9/1 page 2)
`|8    1   12    3    6    9|`   (bracket under the array)
[↓ arrow]  `split?`
[green] `1   3   6` with a brace ⏟ under it, then `1.` ↓        [red] `8   9   12` with a brace ⏟ under it, then `2.` ↓

## Region 2 (top right)
`best :     O(N log₂N )`
`worst :    O(N² )`        ("worst" is written so it looks like "korst")

---

## Region 3 (left, middle): QUICKSORT concept tree [black unless noted]

**QUICKSORT**   (title, small caps)

```
                             8    1    12    3    6    9
  N          p ->                                  [green dashed arrow labelled "m" from the top-row 6 down-left to the green 6 below]
  |                  |1   3|         [green]6     |8    12    9|
  |                                   p          (black "p" just below-right of the green 6)
  v  N       p , p
                     [green dashed vertical line labelled "m" from the 3 in |1 3| down to the green 3]
                                     [green dashed vertical line from the green 6 down to the green 6]
                                                     [green dashed diagonal labelled "m" from the 9 in |8 12 9| down-left to the green 9]
             |1|   [green]3     [green]6  |8|   [green]9    |12|
```
[Far left: `N` level with the "p →" row and `N` level with the "p , p" row, with a long ↓ arrow down the left edge between them. So each level of partitioning costs N work. "m" on the green dashed lines = the median chosen as pivot.]

---

## Region 4 (right, middle): quicksort pseudocode [black]

```
quicksort ( A , start, end )
      if ( end > start )
            p = partition (A, start, end)                p is pivot
                ~~~~~~~~~   (wavy underline under "partition")

            quicksort( A , start, p-1 )
            quick sort ( A, p+1 , end)          <- written with a gap: "quick sort"
```

---

## Region 5 (left, middle): what partition does

`partition :   find median ,   partition around median`   [black]
               ~~~~~~~~~~~  (black wavy underline under "find median")
[red ↓ arrow from "find median" down to:]
[red]   `guess median`
[red]   `(pivot)`
[red long arrow from "guess median" pointing right to:]   [red] `median-of-3`
[red arrow from "(pivot)" down-left to:]   [red] `pivot = A[end]`
[red arrow from "(pivot)" down-right to:]  [red] `pivot = A[start]`

## Region 6 (right of "median-of-3"): median-of-3 diagram [black]

```
                 9
        /        |         \
       8    1   12    3    6    9
       -        --              -        (8, 12 and 9 are underlined: first, middle, last)
```
[Short strokes from the underlined 8 (/), 12 (|) and 9 (\) converge on the 9 written on top: the median of the three is 9.]

---

## Region 7 (bottom left): Lomuto partition, under the red "pivot = A[end]"

Overwritten values stacked above the array (the newest value is on top):
```
                               6        9        12
                        3     12       12       [red] pivot
        8       1      12      3        6        9
```
i.e. column 0 (8): unchanged. Column 1 (1): unchanged. Column 2 (12): 12 → 3. Column 3 (3): 3 → 12 → 6. Column 4 (6): 6 → 12 → 9. Column 5 (9): 9 → 12. The red word `pivot` is written just above the 9, under the black 12.

Pointer rows under the array:
- Row a: `↑` at the far left (before 8) labelled `i` (i = start-1). `↑` under 8 labelled `j`. Hooked arrow → `↑` under 1. Hooked arrows → toward 12, → toward 3, → toward 6, → toward 9 (j sweeps right, one step per column).
- Row b (i's movement): hooked arrow from the far left → toward 8, → `↑` under 1, → `i` under 12, → toward 3, → toward 6.

Lomuto code [black]:
```
pivot = A [end]
i = start - 1
for (j = start ; j < end ; j++ )
          if    a[j] <= pivot
                    i++
                    swap ( a[i], a[j] )
```
[as written: lowercase `a` in the if and in the swap, capital `A` in the first line. No closing swap of the pivot and no return statement.]

Result drawn at the bottom:
`|8    1    3    6|   9   |12|`   (bracket under 8 1 3 6; a short black dash under 9 marks the pivot; bracket under 12)

---

## Region 8 (bottom middle): Hoare partition, under the red "pivot = A[start]"

```
  i                                                     j
  ↓ -> ↓        ↓ -> ↓                          ↓     ↓  ↩↓
        8       1      12       3        6      9
        6               8                8
                        3        8       12
```
- `i` is written above the far-left position (start-1); `j` above the far-right position (end+1).
- i arrows: ↓→↓ from start-1 to 8 (index 0); ↓→↓ from 1 (index 1) to 12 (index 2).
- j arrows: a hooked ↓ at end+1, curving left; ↓ above 9 (index 5); ↓ above 6 (index 4).
- Values written below the array (read top to bottom = in time order): under 8 → `6`; under 12 → `8`, then `3`; under 3 → `8`; under 6 → `8`, then `12`; 1 and 9 unchanged.

[To the right of the trace, on the same line:]  `6   1   3        8        12   9`   (gaps separate 6 1 3 | 8 | 12 9)

Hoare code [black]:
```
pivot = A[start]
i = start -1 ,   j = end + 1
 while ( true )
          i++,   while ( A[i] < pivot )  i++
          j--,   while ( A[j] > pivot )  j--

          if ( i >= j )        return j

          swap ( A[i], A[j] )
```

## Footer (bottom right)
Initials:  (blank)

### Ambiguous handwriting — reading chosen

| As written | Possible readings | Chosen | Why |
|---|---|---|---|
| worst : | worst / korst / lorst | worst | It is paired with 'best :' and O(N²), which is quicksort's worst case. |
| 'p , p' label at the left of the second tree row | p, p / D, P | p , p | The row above is labelled 'p →' (one partition). The second level has two sub-arrays, so two partitions: p, p. |
| Green 'm' on the dashed lines of the quicksort tree | m = median / m = merge (as on the 9/1 mergesort page) | m = median (the chosen pivot) | Each dashed line goes from the element chosen as pivot (6, then 3, then 9) down to that same value. The text says 'partition: find median'. Nothing is merged in quicksort. |
| partition : find median , partition around median | 'fund medion', 'partitoi oroond medion' | find median, partition around median | The letters are sloppy handwriting of the ordinary words. The red annotation beneath says 'guess median (pivot)'. |
| Lomuto 'if a[j] <= pivot' and 'swap ( a[i], a[j] )' | lowercase a / capital A | lowercase a, kept exactly as written ([sic] against A in 'pivot = A[end]') | The letter is clearly a lowercase 'a' (the first one in swap looks like '@'), while the first line uses capital A. The instructor's sortp.cpp uses lowercase a throughout. |
| for (j = start ; j < end ; j++ ) | 'for (j' / 'for Cj' | for (j | The C-shaped stroke is the opening parenthesis; the line closes with ')'. |
| i = start - 1 (Lomuto) | 'i = start - 1' / 'i 2 start - 1' | i = start - 1 | The '=' is drawn like a small '2', as elsewhere on the page ('p = partition', 'pivot = A[start]'). |
| Hoare 'i++,' and 'j--,' | comma / semicolon | comma (as written) | There is a single tail stroke and no upper dot, so it is a comma. It is kept verbatim even though it is not valid C++ (see gotchas). |
| swap ( A[i], A[j] ) (Hoare) | A[i2 / A[i) / A[i] | A[i] | The closing bracket after i is drawn like '2' or ')'. It must be ']' to pair with 'A['. |
| Hoare trace: the order of the values stacked under 12 and under 6 | 12→8→3 and 6→8→12 (top to bottom = time order) / reverse | Top to bottom is chronological: 12→8→3, 3→8, 6→8→12, 8→6 | The final array written to the right, 6 1 3 8 12 9, equals the bottom-most value in each column (8→6, 1, 12→8→3, 3→8, 6→8→12, 9). |
| Red 'pivot' in the last column of the Lomuto trace | labels the original 9 as the pivot / labels the 12 swapped into the last slot | labels the pivot column (the 9 = A[end]); the black 12 above it is the value after the final swap | It is written in the same red as 'pivot = A[end]', right above the 9. The bottom result 8 1 3 6 \| 9 \| 12 shows 9 moved to index 4 and 12 to index 5. |
| Short dash under 9 in the bottom array '8 1 3 6 9 12' | underline marking the pivot / minus sign | underline marking the pivot | 8 1 3 6 and 12 each have a bracket; 9 sits alone between them as the pivot in its final place. |
| 'quick sort ( A, p+1 , end)' | quicksort / quick sort / 'quick srt' | quick sort [sic: gap], meaning quicksort | It is the same recursive call as the line above, which is written without a gap. |
| Date box two lines | 9-1-2026 and 9-3-2026 | both kept; this page was begun 9/1 and continued 9/3 | The top-left region is pixel-identical to the 20260901-2 page (verified by image diff). |

### Board slips / gotchas (verified)

- The Lomuto code as written is MISSING its last two lines, `swap(A[i+1], A[end]);` and `return i+1;`. Without them the pivot is never placed and partition returns nothing. VERIFIED: the as-written loop leaves 8 1 3 6 12 9, and g++ warns 'no return statement in function returning non-void'. The board's own trace and the bottom result '8 1 3 6 | 9 | 12' DO include the final swap: the full version gives 8 1 3 6 9 12 with p=4, which matches the board and partition1 in the instructor's sortp.cpp.
- The Lomuto code mixes cases: `pivot = A[end]` but `a[j]` and `swap(a[i], a[j])`. C++ is case-sensitive, so copied literally with an array named A it fails with ''a' was not declared in this scope' (VERIFIED by compiling).
- In the Hoare code, `i++, while (A[i] < pivot) i++` is not valid C++ because a comma cannot come before a while statement. VERIFIED: g++ gives 'expected primary-expression before 'while''. Write `i++; while (A[i] < pivot) i++;` and likewise for j, as partition2 in sortp.cpp does.
- The Hoare hand trace on the board does NOT match the Hoare code. The board swaps 8↔6, then 12↔8, then 8↔3 and ends with 6 1 3 8 12 9, pivot 8 in the middle. Running the written code on 8 1 12 3 6 9 gives 6 1 3 12 8 9 and returns j=2 (VERIFIED: i=0,j=4 swap → 6 1 12 3 8 9; i=2,j=3 swap → 6 1 3 12 8 9; i=3,j=2 return 2). After the first swap, j-- moves j to index 3 (value 3), not back to the 8 at index 4, so the second swap is 12↔3. For a 'trace the code' question, give the code's result.
- `quicksort(A,start,p-1); quicksort(A,p+1,end)` is correct only with Lomuto, which returns the pivot's final index. Hoare returns j, and the pivot is NOT necessarily at j, so 'p is pivot' is false for Hoare. The recursion must be `quicksort(A,start,p); quicksort(A,p+1,end)`. VERIFIED: Hoare with p-1/p+1 on 8 1 12 3 6 9 gives 1 6 3 9 8 12 (wrong); with (start,p)/(p+1,end) it gives 1 3 6 8 9 12. sortp.cpp's quicks correctly pairs p-1/p+1 with partition1 (Lomuto).
- The QUICKSORT tree uses the true median 6 as the first pivot. None of the pivot rules on this page would choose 6 for 8 1 12 3 6 9: A[end] = 9, A[start] = 8, median-of-3 of (8, 12, 9) = 9. The tree is a best-case illustration, not a trace of either partition.
- In the Lomuto trace the j arrows run all the way to the pivot column (index 5). The loop condition is j < end, so the last comparison is at index 4; the final arrow is only the loop exit.
- Median-of-3 uses first, middle and last. For indices 0..5 the middle is (0+5)/2 = 2, i.e. 12, so median(8, 12, 9) = 9, matching the board (VERIFIED with trace.cpp med3). The board does not show the usual step of swapping that median into the pivot slot (A[end] or A[start]) before partitioning.
- Complexity: best O(N log₂N), worst O(N²) as written; the average is also O(N log N). The worst case happens when the pivot is always the minimum or maximum, e.g. already-sorted input with pivot = A[end] or A[start].

---

## Page 20260910-1  (written date: 9-10-2026 (written in the Date box as "9-10-2⌀26", with a slashed zero))

**[Printed page template: a "Date:" box at top-right and an "Initials:" box at bottom-right. "Initials:" is empty. Everything is in black ink unless it is marked [green]; the only green ink is the two lines in Region 7. Every handwritten item is in the top ~53% of the page (last ink at y ≈ 1350 of 2550), and the rest is blank grid.]**

### Date box (top-right)
Date: 9-10-2026   [the 0 in 2026 is slashed, so it looks like "2⌀26"]

### Region 1: top-left label
ARRAY :  A

### Region 2: generic bubble-sort signature (top center)
[label "location" with a zigzag (lightning-style) arrow pointing down to `A`]
[label "# of elements" (written "# oj elements") with a zigzag arrow pointing down to `num`]
[a small "f" is written above each of `compare`, `allocate` and `assign`, marking them as function parameters]

```
bubble ( A , num , size_of_element , compare , allocate , assign )
```
[short underline under the middle of "allocate" and another under the middle of "assign"]

### Region 3: loop body (indented under the signature)
```
    for ( i=0 ; i < num ; i++ )          ◄———  ints
       for ( j=0 ; j < num-1-i ; j++ )   ◄———  ints
            if ( A[j] > A[j+1] ) {
                temp = A[j];
                A[j] = A[j+1];
                A[j+1] = temp ;
            }
```
- [The `>` in the if has a thick black double underline (a "=" drawn under it), so it looks like `≥`. See the ambiguities.]
- [The first separator in the outer loop (after `i=0`) is drawn as two round dots with almost no tail, so it looks like `:`. It is transcribed as `;`. See the ambiguities.]
- [A long horizontal line runs from under the `A` of `A[j+1]` to the right, under `) {`. It ends in an arrowhead pointing UP at the short underline under `compare` in `compare ( a, b )` (Region 4).]
- [A tall right brace `}` groups the three lines temp= / A[j]= / A[j+1]=.]
- [The closing `}` sits at the if's indentation, lower left of the block.]
- [The two "ints" labels are on the right, each with a left-pointing arrow to its for-line. Meaning: the loop counters are plain ints and do not depend on the element type.]

### Region 4: what the type-dependent parts become (right of the loop body)
```
{  ⇝  compare ( a , b )  ——→  -1  ⇒  a < b
                         ——→   0  ⇒  a == b
                         ——→   1  ⇒  a > b
```
- [A zigzag arrow ⇝ runs from the `{` of the if-line to `compare ( a, b )`, which has a short underline under "compare". Three arrows fan out from `compare ( a, b )` to the three result lines. The middle one is written "a = = b". The three result arrows are double-shaft "=>" (⇒).]

```
}  ⇝  assign ( a , b )  →  a = b
            allocated space , a , b   →   size of data
            copy data from b to a
```
- [A zigzag arrow ⇝ runs from the brace around the three swap lines to `assign ( a, b )`.]
- [The arrow after `assign ( a, b )` is a single-shaft → (like the → before "size of data"), not the double-shaft ⇒ used for the compare results.]
- ["# of bytes" (written "# oj bytes") is written small above "size" in "size of data", with a small tick pointing down at "size".]

### Region 5: C - SOLUTION (left, middle of page)
```
C - SOLUTION

void pointers  —▷   void *ptr
                          └──┘      [bracket under "*ptr"]
                           ↓
                          addr
                           ↓
                       int / long
                       32     64

          → num
          → size_e
```
["32" is under "int" and "64" is under "long". Meaning: an address is stored as a 32-bit int or a 64-bit long.]

### Region 6: memory diagram (center)
```
ptr [══════]
```
- ["ptr" is next to a long thin box (the pointer variable) with a small double tick inside its right end.]
- [A curved arrow goes from the right end of the ptr box to the right and down. It ends with an arrowhead at the bottom-left corner of a tall rectangle (a memory block).]
- [The tall rectangle has one horizontal line near its bottom that marks off a single slot, one element.]
- [A second curved arrow starts inside that bottom slot and curves down to a small box below. The arrowhead points into the top of the small box.]
- [The label on that arrow is `memcpy (a, b, size)`.]

```
⇒ allocate    [ small box ] } size
void * malloc( # of bytes )
```
["} size" is a right brace on the right side of the small box. "# of bytes" is written "# oj bytes".]

### Region 7: compare with void pointers (right, middle)
```
⇒ int  compare ( void *a, void *b )

        [green] int *a1 = (int *) a
        [green] printf( " %d ", *a1)
```
[The asterisk in `void *b` is drawn like a "+" ("void +b").]

### Ambiguous handwriting — reading chosen

| As written | Possible readings | Chosen | Why |
|---|---|---|---|
| `if ( A[j] > A[j+1] )` with a thick black "=" drawn under the `>` | (a) `>` with a double underline for emphasis; (b) `≥`, i.e. `>=` | `>` with an emphasis double underline | On 9/15 the instructor puts the same double bar (in green) under `>` in `if ( a[j] > a[j+1] )` and links it to his green note "> ⇒ operator >". His code (sort.cpp `arr[j]>arr[j+1]`, sortb.cpp `comp(...)>0`) uses a strict `>`. Tested: with `>=` the sort swaps equal keys and becomes unstable (2a 2b 1c becomes 1c 2b 2a after 3 swaps, while `>` gives 1c 2a 2b after 2 swaps). |
| first separator in `for ( i=0 ; i < num ; i++ )` (right after `i=0`) | `;` written without a tail, or `:` (colon) | `;` | At 300 dpi the mark is two round dots, and the lower one is only slightly longer than the upper one (about 9 px vs 6 px), so it looks like a colon. The `;` before `i++` on the same line has a clear slanted tail (about 14 px), and the inner loop's matching mark has a short tail. A for-header needs `;`, so this is read as a quick semicolon. If you copy it literally, `for ( i=0 : i < num ; i++ )` fails with `error: expected ';' before ':' token` (tested, g++ 13.3). |
| `size.oj-element` in the bubble signature | size_of_element / size.of.element / size-of-element | size_of_element | The instructor writes "of" as "oj" throughout ("# oj elements", "# oj bytes"), and the separators are small dot/dash marks. It is abbreviated to `size_e` lower on the page. |
| `i=o`, `j=o` in the for loops | letter o or digit 0 | 0 (zero) | This is the standard loop start and matches every sort file (`for(int i=0;...)`). |
| `num-1-i` | num-1-i or num-l-i | num-1-i | It matches the instructor's code `j<num-1-i` in sortb.cpp. |
| `A[j]: A[j+1];` and `A[j+1]: temp ;` | ":" or "=" | = (assignment) | The strokes are two short bars written quickly. This is the three-line swap temp=A[j]; A[j]=A[j+1]; A[j+1]=temp. |
| squiggle after `)` on the if-line | `{` (open brace) or a squiggle/tilde mark | `{` | A matching `}` appears below at the same indentation, and the zigzag arrow to compare starts next to it. |
| "a = = b" next to the 0 result of compare | `==` or `=` | a == b | Two separate "=" marks are written, and this is the equality test (compare returns 0). The assign line has a single "=" (`a = b`). |
| `void +b` / `void *a` in `int compare ( void *a, void *b )` | `*` or `+` or `&` | * (pointer) for both | The instructor's quick asterisk often looks like "+". The heading is "void pointers", and sortb.cpp/sortq.cpp use `const void *a, const void *b`. |
| `size_e` | size_e / size_c | size_e | It abbreviates size_of_element from the signature above. The parameter is `esize` in sortb.cpp. |
| `int / long` with `32  64` under it | (a) "int = 32-bit, long = 64-bit"; (b) a 32/64 bit-width list | 32 under int, 64 under long: an address fits in a 32-bit int or a 64-bit long | This is the spatial alignment on the page. On a 64-bit machine sizeof(void*)==8 (checked with a test program). |
| `printf( " %d ", *a1)` | format string " %d " (with spaces) or "%d" | " %d " as written (spaces inside the quotes) | There are visible gaps between the quote marks and %d. They may only be handwriting spacing. |
| the ptr / memory-block / memcpy diagram | (a) ptr points at the start of the block; (b) ptr points at the bottom element slot. The memcpy arrow goes from the block slot INTO the small allocated box | Described literally: the ptr arrow ends at the bottom-left corner of the tall block, and the memcpy arrow goes from the bottom slot down into the small `} size` box | The drawing does not label a or b. Read with "⇒ allocate" and "void * malloc(# of bytes)", it shows one element being copied into malloc'd temp space of `size` bytes. |
| small "f" above compare / allocate / assign | f = function; or a stray letter | f = function (these three parameters are functions) | They sit exactly above the three parameters that later become function calls (compare(a,b), assign(a,b), malloc). |
| arrow after `assign ( a, b )` | → (single shaft) or ⇒ (double shaft) | → | A pixel map shows one shaft plus a head, the same as the → before "size of data". The three compare-result arrows show two parallel bars ("=>"), so they stay ⇒. |

### Board slips / gotchas (verified)

- `if (A[j] > A[j+1])` cannot compile when A is a `void *`. g++ 13.3 gives `error: 'void*' is not a pointer-to-object type` plus `warning: pointer of type 'void *' used in arithmetic [-Wpointer-arith]` (re-tested). That is why the board replaces `>` with compare(a,b). In the instructor's sortb.cpp, element j is at `(char *)arr + (j*esize)`.
- The board's signature `int compare(void *a, void *b)` has no const. If you pass it to qsort in C++, g++ says `error: invalid conversion from 'int (*)(void*, void*)' to '__compar_fn_t' {aka 'int (*)(const void*, const void*)'} [-fpermissive]` (re-tested). Write `int comp_int(const void *a, const void *b)` as in sortb.cpp/sortq.cpp.
- memcpy argument order is (dest, src, size). `memcpy(a, b, size)` copies b INTO a: in a test, a=1, b=2 became a=2, b=2 (re-tested). This matches the note "copy data from b to a". Don't reverse it.
- The swap needs a temporary: allocate (malloc) once for temp, then three copies (temp←a, a←b, b←temp). sortb.cpp calls `free(temp)` at the end. The board shows malloc but never mentions free, and without it you get a memory leak.
- compare is described as returning exactly -1/0/1, but the instructor's code only tests `> 0`. sortt.cpp (9/15) even returns `a-b`. Never test `== 1`.
- The green lines `int *a1 = (int *) a` and `printf( " %d ", *a1)` have no semicolons, and printf needs <cstdio>/<stdio.h>. These are board shorthand. In C++, `int *a1 = a;` without the cast does not compile: `error: invalid conversion from 'void*' to 'int*' [-fpermissive]` (re-tested).
- The board's hand-written memcpy approach copies raw bytes. That works for int/float/plain structs but is wrong for C++ objects such as std::string. Tested: sortb.cpp's bubbleSort (malloc'd temp + three memcpy calls) on std::string {"cc","bb","aa"} aborts with `munmap_chunk(): invalid pointer` (exit 134). Templates (9/15) fix this.
- If the outer-loop separator after `i=0` is copied as the colon it resembles, `for ( i=0 : i < num ; i++ )` fails with `error: expected ';' before ':' token` (tested). Use `;`.

---

## Page 20260915-1  (written date: 9-15-2026 (written in the Date box as "9-15-2⌀26", with a slashed zero))

**[Printed page template: a "Date:" box at top-right and an empty "Initials:" box at bottom-right. Colors: black = main text, [green] = later annotations, [red] = the two bullet notes. The area below the last code line (y > ~2175 of 2550) is blank.]**

### Date box (top-right)
Date: 9-15-2026   [slashed zero: "2⌀26"]

### Region 1: title and definition (top-left)
```
C++ TEMPLATES

·  code template  ⇒  temp. data type - T
        ↳ compiler generate specific code
```

### Region 2: template bubble sort (left/center)
```
template <class T>
void bubbleT( T *arr , const int num )

          if ( i=0 ; i< num ; i++ )
               for( j=0 ; j< num-1-i ; j++ )

                    if ( a[j] > a[j+1] )
                         swapT( a[j], a[j+1] )
```
- [The outer loop is written with `if`, not `for` [sic].]
- [A green double underline "=" is under the black `>` of `a[j] > a[j+1]` (the upper green bar is thick, drawn with two overlapping strokes).]
- [The body uses `a[j]` although the parameter is named `arr` [sic].]
- [No braces and no semicolon after `swapT( a[j], a[j+1] )`.]

### Region 3: right-hand annotations, level with the signature
```
[green] , int (*comp)(const T *a, const T *b)      ⇒ int comp_int (const int *a
                                                                    const int *b)
```
- [The green part starts with a green comma. It is on the same line as the black bubbleT signature but NOT right after its `)`: it is about 1.2 in (≈5 grid squares) to the right of `)`, just in front of the green `int (*comp)(...)`. It is meant as an added third parameter.]
- [`⇒ int comp_int (...)` is in black and is the concrete version for T = int. There is no comma between `*a` and the second line `const int *b)`.]
- [The asterisks are drawn like "✱"/"+".]

### Region 4: right-hand annotations, level with swapT and the if
```
                                                  ⇒ swap ( int &a, int &b)

[green] >      ⇒ operator > (const int &a
                              const int &b)
```
- [`⇒ swap ( int &a, int &b)` is black and level with the swapT line.]
- [The green `>` and `⇒ operator > (const int &a / const int &b)` are below it. There is no comma between the two parameters and no return type. The `&` is drawn like "Q"/"&".]

### Region 5: red notes (middle-left)
```
[red] -  needs  support functions
              Operator functions ,  <, >,  >>, <<,  +/-/*/÷

[red] -  compiler need access to source code
              ↳ put code in .h header
```

### Region 6: usage examples (bottom-left)
```
int arri[n] ;  float arrf[n]

bubbleT<int> (arri, n   );

bubbleT<float>(arrf, n) ;
```
[There is a wide gap before `)` in the `bubbleT<int>` call. No comp argument is written in either call.]

### Ambiguous handwriting — reading chosen

| As written | Possible readings | Chosen | Why |
|---|---|---|---|
| `if ( i=0 ; i< num ; i++ )` (outer loop) | `if` (a slip) or `for` | if [sic] | At high zoom it is clearly a dotted i followed by an f, the same shape as the real `if ( a[j] > ...)` below. The intent is obviously `for`, as on 9/10 and in sortt.cpp. |
| green `const T *a, const T *b` and black `const int *a / const int *b` | `*` (pointer) or `&` (reference) | * (pointer) | The marks are the instructor's asterisk (a star-blob, or a "+"-like cross in "+b"). His `&` on the same page (`swap ( int &a, int &b)`, `operator > (const int &a`) is drawn as a clearly different looped "&"/"Q" shape. NOTE: his file sortt.cpp uses references instead: `int (*comp)(const T&, const T&)` and `int comp_int(const int &a, const int &b)`. |
| `T *arr` in `void bubbleT( T *arr , const int num )` | T *arr / T &arr / T arr | T *arr | The star-blob mark is the instructor's asterisk. sortt.cpp has `T *arr`. |
| `&a` in `swap ( int &a, int &b)` | &a / &o / &0 | &a | The parameters are a and b (sort.cpp: `void swap(int &a, int &b)`). The first a is written small and round. |
| `const int &a` / `const int &b` in the green operator note (the `&` looks like "Q") | &a or Qa / Ob | const int &a, const int &b | This is the instructor's looped ampersand. Operator parameters are passed by const reference. |
| red "compiler need accers to source code" | access / accers | access | The cursive "ss" looks like "rs". Only "access" makes sense. "need" (not "needs") is kept as written. |
| red operator list separators `+/-/*/÷` | slashes "/" or vertical bars "\|" | / | The separator strokes are slanted. Either way it is a list of the arithmetic operators + - * ÷. |
| `temp. data type` | "temp." = temporary or template | temp. (temporary/placeholder data type) as written | The word is abbreviated with a period. T is a placeholder type that the compiler replaces. |
| `arri` / `arrf` | arri / arr i / arrc; arrf / arr f | arri (int array) and arrf (float array) | The suffixes match the element types int/float and the calls bubbleT<int>(arri,...) and bubbleT<float>(arrf,...). |
| green comma before `int (*comp)(...)` | (a) a third parameter to insert into the bubbleT signature; (b) a separate declaration | a third parameter added to bubbleT | The comma is green (pixel color about RGB 0,115,85). It sits on the same line as the signature, about 1.2 in (≈5 grid squares) to the right of its `)` (signature ink ends at x≈1408, comma at x≈1771–1782 at 300 dpi), just before the green text. sortt.cpp has exactly `bubbleSort(T *arr, const int num, int (*comp)(const T&, const T&))`. |
| gap in `bubbleT<int> (arri, n   );` | just spacing, or room left for a third argument (comp_int) | transcribed as written (no third argument) | Nothing is written in the gap. Once the green comp parameter is added, the call would need `, comp_int` there. |

### Board slips / gotchas (verified)

- The outer loop is written `if ( i=0 ; i< num ; i++ )` [sic]. It must be `for (int i=0; i<num; i++)`. Compiled literally (re-tested, g++ 13.3, both -std=c++11 and the default): `error: 'i' was not declared in this scope` and `error: expected ')' before ';' token`. `j` is also undeclared (`error: 'j' was not declared in this scope`). Declare the counters with `int`.
- The parameter is named `arr`, but the body uses `a[j]` and `a[j+1]`. Even with the loops fixed, g++ gives `error: 'a' was not declared in this scope` (re-tested). Use `arr[j]` everywhere, or rename the parameter.
- `swapT` is called but never defined on the page. The error you see depends on the arguments. With the board's literal `swapT( a[j], a[j+1] )` (`a` undeclared, so the arguments are not dependent), g++ reports `error: there are no arguments to 'swapT' that depend on a template parameter, so a declaration of 'swapT' must be available [-fpermissive]`. Once you fix it to `swapT(arr[j], arr[j+1])`, the call is dependent and the error appears only when `bubbleT<int>` is instantiated: `In instantiation of 'void bubbleT(T*, int) [with T = int]': ... error: 'swapT' was not declared in this scope`. Both were re-tested. You need `template <class T> void swapT(T &a, T &b) { T temp = a; a = b; b = temp; }` before bubbleT. The board's `⇒ swap ( int &a, int &b)` is only the int version, and sortt.cpp itself calls that non-template `swap`, so it works only for int.
- `operator > (const int &a, const int &b)` cannot actually be written. g++: `error: 'bool operator>(const int&, const int&)' must have an argument of class or enumerated type` (re-tested). Built-in types already have `>`. You overload `>` only for your own class/struct, e.g. `bool operator>(const name &a, const name &b)`. Re-test: bubbleT<name> sorted {Smith, Adams, Lee} to Adams Lee Smith. For a struct without it, g++ gives `error: no match for 'operator>' (operand types are 'P' and 'P')`. The board also leaves out the return type (bool) and the comma between the parameters.
- Once the green `int (*comp)(const T *a, const T *b)` parameter is added, the bottom calls `bubbleT<int>(arri, n)` and `bubbleT<float>(arrf, n)` no longer compile: `error: no matching function for call to 'bubbleT<int>(int [n], int&)'` and `... 'bubbleT<float>(float [n], int&)'` (re-tested). Pass a compare function, e.g. `bubbleT<int>(arri, n, comp_int)`, with a matching `comp_float` for floats. With the pointer version, the test becomes `if (comp(&arr[j], &arr[j+1]) > 0)` (compiles). With sortt.cpp's reference version it is `comp(arr[j], arr[j+1]) > 0`.
- The pointer form on the board (`const T *a`) and the instructor's file sortt.cpp (`const T&`, template named `bubbleSort`) differ. Whichever form you choose, the compare function and the call must match.
- `int arri[n]; float arrf[n]` with a non-constant n is a variable-length array. It is not standard C++: with -pedantic, g++ warns `ISO C++ forbids variable length array 'arri' [-Wvla]` (re-tested). Use `new int[n]` as in loadData, or a constant size.
- "put code in .h header": if the template body is in a .cpp and only declared in the .h, the program fails to link: `undefined reference to 'void bubbleT<int>(int*, int)'` (re-tested). That is why template code goes in the header.
- The `comp_int` note has no comma between `const int *a` and `const int *b` (a line break was used instead). Add the comma when you write real code.

---

## Page 20260915-2  (written date: Date box left blank on this page; lecture date 9-15-2026 comes from the PDF file name (ECE218F20260915) and page 1)

**[Printed page template: a "Date:" box at top-right, left EMPTY on this page, and an empty "Initials:" box at bottom-right. Colors: black = main text, [green] = examples and annotations. Everything below y ≈ 930 of 2550 is blank.]**

### Date box (top-right)
Date:   [blank]

### Region 1: title (top-left)
C++ OBJECTS

### Region 2: struct vs class (upper-left)
```
struct    -   primitive objects   [green] —▷ visibility = public
class     -   full objects
```

### Region 3: struct example (upper-middle, all green)
```
[green]
struct name {
        string first, last ;
};
```

### Region 4: using the struct (upper-right, green)
```
[green]
name  n;
 n.first = 'John"
```
[The opening quote before John is a single quote ( ' ) and the closing one is a double quote ( " ) [sic]. No semicolon.]

### Region 5: what an object is (middle-left, black)
```
Object  —▷  represent  real-world  entity
  ↓
attributes  ⎫   visibility ( public, protected, private )
  ↓         ⎬
methods     ⎭
```
[A tall right brace spans from "attributes" down to "methods"; its point is at the ↓ row between them. The line "visibility ( public, protected, private )" is written level with "attributes" (the top of the brace), not at the brace's point.]

### Region 6: Person example (middle, green)
```
[green]
Person
  ↓
firstname, lastname, ssn (private)
  ↓
write_name
```
[The layout mirrors Object → attributes → methods on the left: firstname, lastname and ssn are the attributes, ssn is marked private, and write_name is the method.]

### Ambiguous handwriting — reading chosen

| As written | Possible readings | Chosen | Why |
|---|---|---|---|
| struct member written like "frosh" / "frist" in `string first, last ;` | first / frist / frosh | first | It is written fast. Two lines later it is used as `n.first`, and there it is clearly f-i-r-s-t. The instructor's final "t" often looks like a hooked "r"/"h". |
| `n.first = 'John"` | (a) the intended "John" (a string literal); (b) literally 'John" with mismatched quotes | transcribed literally as 'John" [sic]; the intended meaning is "John" | At 4× zoom the opening mark is one stroke (') and the closing mark is two strokes ("). The member is a std::string, so a string literal in double quotes is meant. |
| "visibility = public" after struct | struct members are ALWAYS public, or public by DEFAULT | as written: visibility = public (i.e. the default) | In C++, a struct's default access is public and a class's is private. A struct can still declare private members. |
| "real- world entoty" | entity / entoty | entity | This is ordinary cursive with an "i" that has no clear dot. |
| "visibulity" in the black visibility line | visibility / visibulity | visibility | The same word is written in green as "visibility" on the struct line. |
| "primiotive objects" | primitive / primotive | primitive | This is cursive with a looped i/t. |
| `ssn (private)` | only ssn is private, or all three attributes are private | only ssn is marked private | "(private)" follows directly after "ssn". Keeping the SSN hidden is the information-hiding example. |
| `write_name` | write_name / write-name | write_name | The underscore style matches `size_of_element` and `size_e` in the earlier lectures. |
| what the brace next to attributes/methods points to | (a) the visibility line applies to both attributes and methods; (b) the visibility line belongs only to attributes | (a) the brace groups attributes and methods, and the visibility line is written beside it | The visibility text is level with "attributes" (the top of the brace), not at the brace's point, but the brace clearly spans both words. In C++, access specifiers apply to both data members and member functions. |

### Board slips / gotchas (verified)

- `string first, last;` without `std::` or `using namespace std;` does not compile: `error: 'string' does not name a type` (re-tested). Also `#include <string>`.
- `n.first = 'John"` as written (mismatched quotes) gives `error: missing terminating ' character` (re-tested). Use double quotes: `n.first = "John";`.
- A related trap: `n.first = 'John';` with single quotes on both sides COMPILES, with only the warnings `multi-character character constant [-Wmultichar]` and `overflow in conversion from 'int' to 'char' changes value from '1248815214' to '110' [-Woverflow]`. It silently stores ONE character ('n'). Re-test printed `[n] size 1`. In C++, single quotes are for one char and double quotes are for strings.
- If the member really were spelled "frist" as it half-looks on the board, `n.first` would not compile. Use the same name in the declaration and every use.
- "struct → visibility = public" is the DEFAULT only. The only language differences between struct and class are the default member access (struct public, class private) and the default inheritance access. The same members in a class need `public:` before `n.first` can be accessed from main. Re-test: `class name { std::string first, last; };` then `n.first = "John";` gives `error: 'std::string name::first' is private within this context`.

---

## Page 20260917-1  (written date: 9-17-2026)

[Header box, top-right, printed template] Date: 9-17-2026 [handwritten. The "0" of the year is a slashed zero: "20" is one stroke and a separate stroke is drawn through the 0, so the year looks like "2ф26" or "2626". Nothing is overwritten. The 7 of 17 is crossed.]

### Region A: title (top-left, black)
C++ OBJECTS

### Region B: struct vs class (top-left, black, with a green annotation)
```
struct   -   primitive objects   [green:] -> visibility = public
class    -   full objects
```

### Region C: struct example (top-center/right, all green)
```
struct name {
     string first, last;
};

                         name  n;
                          n.first = 'John"
```
[`n.first = 'John"` is copied exactly: it opens with a single quote ', closes with a double quote ", and has no semicolon [sic]. In the struct, the member name "first" is written with letters that look like "frist" (see ambiguities).]

### Region D: object concept tree (middle-left, black; one green line)
```
Object  ->  represent  real-world  entity
  |
  v
attributes  ]
  |          }   visibility ( public, protected, private )
  v          }            [green:] ( Information hiding )
methods     ]
  |
  +------ [a line goes down from under "methods", then left, then down to:]
constructor
destructor
                         inheritance
                         polymorphism
```
[A curly brace joins "attributes" and "methods" and points to the visibility line. "inheritance" and "polymorphism" are written under the visibility line, to the right of the tree.]

### Region E: overloading (middle-left, black)
```
C++        compare ( int , int )
           compare ( float, float )
```

### Region F: Person / Student inheritance diagram (right half; green, with the method names in purple)
```
                              is_a               generalization
                               <-                      <-
Person |>-------------------------------------------------  Student
                                                     ->
  |                                            specialization   |
  v                                                             v
firstname, lastname, ssn (private)                          student_id
  |                                                             |
  v                                                             v
write_name
[purple] print(     )                                    [purple] print(    )
[purple] compare(     )                                  [purple] compare ( s )
```
[A green horizontal line joins Person and Student. At the Person end there is a hollow triangle drawn as "▷": its flat side faces Person and its tip touches the line, so the tip points toward Student. In standard UML the tip touches the parent (Person ◁—— Student), so this arrowhead is drawn reversed. Page 2 of 9/17 draws its triangles the standard way. The labels "is_a" and "generalization" are written above the line, near its middle and right end, each with a left arrow under it. "specialization" is written below the line near Student, with a right arrow above it. A down arrow next to "specialization" goes from Student to student_id, and a second down arrow goes from student_id to Student's print( ). Person's down arrow goes to the attribute line, then another down arrow goes to write_name.]

### Region G: polymorphism code (right side, under the diagram, black)
```
Student *s = new Student

        s->print()      // student version

Person *p
        p =  s
        p->print()      // student version
```
[Every "->" is drawn as an arrow with a triangular head. None of these lines has a semicolon. Each "// student version" comment is split over two lines ("student" / "version").]

### Region H: bottom-left, below a long black horizontal rule that runs across the left two-thirds of the page (black)
```
EXAM #1  ->  Oct 1st

   - in class, written, closed book
```

[Footer box, bottom-right, printed template] Initials: [blank]
[The rest of the page is blank grid.]

### Ambiguous handwriting — reading chosen

| As written | Possible readings | Chosen | Why |
|---|---|---|---|
| Date year "2026" | 2026 (slashed zero) / 2626 / 2e26 | 2026 | The PDF ink is vector strokes. "20" is one stroke, a separate stroke is drawn through the 0 (a slashed zero, as on 9/22 and 9/24), and then "26" follows. No digit is overwritten. The course is Fall 2026. |
| string first, last; (struct member) | first / frist / frish | first | The pen strokes are f, an r-like hump, a small undotted tick, s, then a t (an upright plus a separate cross stroke, made the same way as the t in "last"). So the letters look like "frist". The same member is used as n.first two lines lower, and his i in n.first has no dot either. |
| n.first = 'John" | 'John" (mismatched quotes) / "John" with a sloppy opening quote | 'John" copied as written, marked [sic] | The ink strokes show ONE short tick before J and TWO separate ticks after n. The intended C++ is n.first = "John"; |
| compare (Person and Student methods, and the overload lines) | compare / compose / conpare | compare | The overloading example compare(int,int) / compare(float,float) and the Student compare(s) only make sense as "compare". |
| write_name | write_name / write-name / wrote_name | write_name | There is a clear underscore-like dash between two words. It is a Person method listed with print and compare. |
| is_a | is_a / is-a | is_a (meaning the "is-a" relationship) | The low dash looks like an underscore. The meaning is the standard is-a (inheritance) relationship. |
| student_id | student_id / studen#_id (the t is crossed twice) | student_id | The 9/17 page 2 class declares int student_id; in the same lecture. |
| ssn (private) | ssn / san | ssn | Social security number, a classic private Person attribute. |
| Student *s = new Student | Student / Stodent | Student | It is only sloppy handwriting of the class name. |
| inheritance | inheritance / inheriteance / inheritence | inheritance | The a is written loosely, like "ea" or "eo". The meaning is unambiguous. |

### Board slips / gotchas (verified)

- n.first = 'John" (mismatched quotes, no ;) does not compile. Re-verified: 'error: missing terminating ' character' (chk_g4/cpp/v1_john.cpp). Even 'John' in single quotes compiles, with warnings (multi-character constant, overflow), and stores only ONE char, 'n'. Re-verified: n.first.size()==1 and prints [n] (v1b_john.cpp). Write n.first = "John";.
- struct name { string first, last; }; needs #include <string> plus std::string or using namespace std;. Re-verified: without them, "'string' does not name a type" (v7_nostring.cpp).
- 'struct = primitive objects, visibility = public' is about the DEFAULT only. In C++ a struct can have methods, constructors, inheritance and virtual functions. The only language differences are the default member access (public vs private) and the default inheritance access (public vs private).
- The inheritance triangle on this page is drawn reversed (Person ▷—— Student): its flat side faces Person and its tip points toward Student. In UML the hollow triangle's tip touches the PARENT: Person ◁—— Student, as drawn correctly on 9/17 page 2. The labels 'is_a <-' and 'generalization <-' do point the right way (toward Person).
- p->print() gives the 'student version' only if print() is declared virtual in Person. Re-verified: without virtual, p->print() prints 'Person version'; with virtual, it prints 'Student version' (v2_poly.cpp).
- Person *p = s; needs PUBLIC inheritance: class Student : public Person. With class Student : Person (private by default), the compiler rejects it. Re-verified: "'Person' is an inaccessible base of 'Student'" (v3_privinh.cpp).
- ssn (private) is inherited by Student (it exists in the object), but Student's methods cannot access it. Re-verified: "'std::string Person::ssn' is private within this context" (v4_privmem.cpp). Use protected if the subclass needs it.
- Overload trap: with compare(int,int) and compare(float,float), the call compare(1.5, 2.5) (double literals) is AMBIGUOUS. Re-verified: "call of overloaded 'compare(double, double)' is ambiguous" (v5_overload.cpp). Use 1.5f, 2.5f.
- Student::compare(s) has a different parameter list from Person::compare(), so it does NOT override it. It hides it, so s.compare() fails to compile. Re-verified: "no matching function for call to 'Student::compare()'" (v6_hide.cpp).
- Student *s = new Student is written without ';' and is never deleted (a memory leak if copied literally).

---

## Page 20260917-2  (written date: 9-17-2026)

[Header box, top-right, printed template] Date: 9-17-2026 [the 0 of the year is a slashed zero (a separate stroke through it), as on page 1. Nothing is overwritten.]

### Region A: title (top-left, black, small caps)
```
EXAMPLE
UNIVERSITY PERSONELL
```
["PERSONELL" is a misspelling of "Personnel" [sic]]

### Region B: UML class hierarchy (top-left/center, black; annotations in red)
```
                              [red, far right:]  UML
                         PERSON
                           /\    [red:] <- inheritance
                           |
     +---------------------+----------------------+---------------+
     |                     |                      |               |
                           G.
  STUDENT  --------------  FACULTY               ADMIN           GUEST
            mentor ->
   n       [red:] no
   =       [red:] association
    /\                     /\
    |                      |
 +--+-------+          +---+----+
 |          |          |        |
UG          G          R        A

                                        DEAN
```
Details:
- A hollow triangle (UML inheritance arrowhead) points up to PERSON. The red note "<- inheritance" has a small red arrow pointing at that triangle.
- The vertical line from PERSON goes down, crosses a long horizontal bar, and continues a little below it. The bar has short drop-ticks down to STUDENT (left end), ADMIN and GUEST (right end). The small "G." is written just under the vertical line, directly above FACULTY.
- A plain horizontal line joins STUDENT and FACULTY (an association). The label "mentor" with a small right arrow is above it.
- Under the STUDENT end of that line there is a small black mark that looks like "n" over "=" (possibly a multiplicity).
- Under the line, in red: "no" / "association".
- STUDENT has a hollow-triangle arrow from a bar below, which drops to "UG" and "G". FACULTY has a hollow-triangle arrow from a bar below, which drops to "R" and "A". Every triangle on this page has its tip touching the parent (standard UML).
- "DEAN" stands alone, lower and to the right, and is not connected to anything.

### Region C: C++ is class-based; class vs instance (top-right, black; red annotations)
```
C++
Class - based

class  - - - - - - - - ->  instance (object)
  |                        Student   s ;
  v                           ^      ^                [red:] s.print()
declaration                   |      |                        ^ (red dotted arrow)
definition                  class  instance                  this

int   - - - - - - ->  int  x   [hooked arrow from x ->] instance
  |
  v
data type
```
[An arrow goes up from "class" to "Student", and an arrow goes up from "instance" to "s". In red, a dotted arrow goes up from the word "this" to the "s" of s.print(). A small hooked arrow starts above x and points right to the word "instance".]

### Region D: class declaration (right-middle, black), with a big right bracket labelled "student.h"
```
class Student {
    private:
              int student_id ;

    public :
         void print(    ) ;

};
```
[The closing brace is drawn like "]" followed by ";". A tall bracket to the right spans these lines, from class Student { down to "};", and is labelled "student.h". The dot is written low, so it looks like "student_h".]

### Region E: class definition (right, lower, black; red annotations), with a big right bracket labelled "Student.cpp"
```
#include "student.h"
                     [red:] namespace (scope)
void  Student::print( )   {
         ________              [red:] this  ptr
        ________
        ________
        ________
}
```
[A red arrow goes from "namespace (scope)" to the word "Student" in Student::. A small red arrow goes from "this ptr" up to the empty parentheses "( )" of print. The four black horizontal lines stand for the function body. A tall bracket to the right, labelled "Student.cpp", starts at the #include line and ends at about the level of the second body line. The closing "}" is below the bottom of the bracket.]

### Region F: bottom of right half (black)
```
Student *s1 = new Student
```
[No semicolon. The "=" is written very small and looks like ":".]

[Footer box, bottom-right] Initials: [blank]
[The left half, below the UML diagram, is blank.]

### Ambiguous handwriting — reading chosen

| As written | Possible readings | Chosen | Why |
|---|---|---|---|
| "G." written above FACULTY | a label "G." (for example an abandoned start of "Grad"/"Guest") / a stray mark / "G" for a Graduate-faculty type | transcribed literally as "G." | It is clearly the letter G followed by a dot (two strokes), directly under the Person vertical line and above FACULTY. In ink stroke order it was written right after the letters UG, G, R, A and just before DEAN. Nothing on the page explains it. |
| small black mark under the STUDENT end of the mentor line | "n" over "=" / multiplicity "n" and "1" / "n" over "2" / stray marks | described as "n" over "=" (possibly a multiplicity note) | The PDF ink stroke order shows the "n" was written immediately after "mentor" and its arrow, so it belongs to the association and is most likely a multiplicity. The two short strokes below it were added at the very END of the lecture, just before "Student *s1 = new Student". They have exactly the same two-stroke shape (small arc over a bar) as the "=" in that line. Their meaning here is not clear. |
| red "no association" | "no association" / "n: association" / "an association" | no / association | In the ink strokes the red word is an "n" followed by a closed "o" made of two strokes. No "a" loop comes before it, so "an" is unlikely. It was written just before "association". The meaning is probably that mentor is an association and NOT inheritance, but that is an interpretation. |
| UG, G, R, A | UG = undergraduate, G = graduate; R/A = research/adjunct? (or regular/assistant) | letters copied as written | Only the letters are written. UG/G are clearly student types; the meaning of R/A is not given. |
| UNIVERSITY PERSONELL | PERSONELL / PERSONNEL | PERSONELL [sic] | The letters read P-E-R-S-O-N-E-L-L. The correct word is "Personnel". |
| student.h label | student.h / student_h | student.h | The dot is written low, like an underscore. The #include "student.h" line uses a clear dot. |
| Student *s1 = new Student | = / : | = | In the ink it is two short stacked horizontal strokes (a small arc over a bar), which is how he writes "=" (the same as arr2[curr] = e on 9/24). C++ needs = here. |
| class closing "];" | }; / ]; | }; | His closing brace is often drawn with square corners. A class definition ends with };. |
| red dotted arrow "this" -> s.print() | it points to "s" / it points to "." | it points to "s" | The dotted red line rises directly under the "s", meaning that inside print(), this = &s. |

### Board slips / gotchas (verified)

- The red note calls Student:: a "namespace (scope)". Strictly, Student:: is CLASS scope used with the scope-resolution operator ::. It is not a namespace, though both use :: to qualify names.
- Student *s1 = new Student is written without ';' and has no matching delete s1; (a memory leak if copied literally). Use -> on the pointer: s1->print();.
- The declaration void print( ); must match the definition void Student::print( ) exactly. If the definition in student.cpp leaves out Student::, you get a free function and a linker error. Re-verified: "undefined reference to `Student::print()'" (chk_g4/cpp/link/).
- The UML hollow-triangle arrow points FROM the child TO the parent (Student -> Person), with the tip touching the parent, as drawn on this page. Do not draw it the other way; 9/17 page 1 draws it reversed. mentor (Student - Faculty) is an association (a plain line), not inheritance.

---

## Page 20260922-1  (written date: 9-22-2026)

[Header box, top-right, printed template] Date: 9-22-2026 [the "0" is written with a vertical stroke through it, so it looks like "2ф2ь"]

### Region A: class Student (top-left; black, with two red members)
```
class Student {
  private:
            int  s_id;
     [red]  int  *data;      }
     [red]  int  arr[100];   }
  public
       void setSID(int);

}
```
[A black curly brace to the right groups the two red lines. There is a black dashed underline under "*data;" and another under "arr[100];". "public" has NO colon and the closing "}" has NO semicolon [sic].]

### Region B: copy statements (top-center; black, green, red)
```
Student  s1, s2;

  s1.setSID(10)                       [green double underline under the "."]
  s2 = s1
   <-/copy     =>     Copy Constructor

[green] Student  *s3 = new Student
[green]        s3->setSID(12);        [green] ->     ["->" drawn as an arrow; short green underline under it]
[red]   Student  *s4 = s3;            [red dashed underline under "*s4 = s3"]
```
[Under "s2 = s1" a black hooked arrow comes down from s1 and points left toward s2. It is labelled "copy". "s1.setSID(10)", "s2 = s1" and "Student *s3 = new Student" have no semicolons. The green arrow after "s3->setSID(12);" points right to the s3/s4 diagram (Region E).]

### Region C: shallow-copy diagram (top-right; black object boxes, red contents)
```
s1 +-------------+          s2 +-------------+          +=======+ (red heap block,
   | s_id [ 10 ] |             | s_id [ 10 ]  |          |=======|  horizontal lines)
   | [red data]--+--> (red)    | [red data]---+--> (red) |=======|
   | arr [:::::] |. . . . . . .| arr [:::::]  |          +=======+
   +-------------+             +--------------+       ^  [red:] shallow
                                                     /         copy
```
[Each black box (s1, s2) contains a small box labelled "s_id" holding "10", a red bar (the data pointer), and a red label "arr" over a red dashed box of lines (the array). A red arrow goes from s1's data bar up and right to a red heap block of horizontal lines at the top-right. A second red arrow goes from s2's data bar to the SAME block. A red dotted curve runs from a dot at s1's arr to s2's arr, meaning the array was copied. The red text "shallow copy" has a red arrow pointing up-left at the two arrows and the shared block.]

### Region D: copy constructor (right; red and black)
```
[red]  Copy Const
       Student ( Student & )  {        [small red dot under "&"]
            [red] - deep copy
       }
```

### Region E: pointer-copy diagram (right, under Region D)
```
s3 [green box]  -----(red arrow)----->  +---------------+  red box = one Student
s4 [red box]    -----(red arrow)----->  |  [===]        |  object on the heap
                                        |  [===]        |  (inner field boxes/lines)
                                        |  [=====]      |- - -.
                                        +---------------+     :  [red:] copy
                                        + - - - - - - - +  <- '
                                        :  (empty,      :
                                        :   dashed red) :
                                        + - - - - - - - +
```
[Both pointers (s3 in a green box, s4 in a red box) have red arrows to the same single object. A red DASHED curved arrow labelled "copy" goes from the right side of the object down to an EMPTY red dashed box below it. This shows a second object that is not created by Student *s4 = s3;.]

### Region F: strings (middle-left; black, with red)
```
C:    char str[] = "hello"                 str [ h | e | l | l | o | \0 ]
                                                                      ^-- \0
std::string  ->  C++ class                             string s1 = "hello"
                                                       string s2 = s1

    _str  ----------(red arrow)---------->  [          ]  (red box)
                                            \____  ____/
                                                 \/
                                             size to fit
```
[The char array is drawn as 6 cells: h, e, l, l, o, and \0 in the last cell. A bracket-arrow above labels the last cell "\0" (written like "\ø"). "_str" (black) has a long red arrow to an empty red rectangle. A black brace under the rectangle is labelled "size to fit".]

[A long black horizontal rule runs across the page here.]

### Region G: self-sizing array (bottom-left, black)
```
Self-sizing Array   -  Vector
       - resize ,   inc./dec ,   Compress        [small green underline under the "z" of resize]
       - add / remove
            |          |
            v          v
start  mid  end     start  mid  end              [tiny tick marks under the first "start" and "mid"]
       -  change values
       -  get values at loc
```
[The arrow under "add" is directly above the first "end". The arrow under "remove" is directly above the second "start".]

### Region H: C/C++ arrays and manual resize (bottom-center; green, red, purple)
```
[green] C/C++
[green]     array :      int arr1[100]      X

                          [red check mark above "int[100]"]
[red]      int  *arr2 = new int[100];
[green]    int  *temp = arr2
[purple]        arr2 = new int[200];
[purple]        copy data from temp to arr2
[green]         delete temp[]      // if missing the red head
                                       space is not de allocated  -  memory leak
```
["int *temp = arr2" and "delete temp[]" have no semicolons. "delete temp[]" is written with the brackets after the name [sic]. "red head" is written as "head" [sic; it means heap]. The comment wraps to a second line.]

[Green drawing to the right of "int arr1[100]  X": a tall green rectangle (a fixed array). The bottom three rows are drawn, with indices labelled on the right from the bottom: 0, 1, 2. The label "arr1" is at the bottom-left, pointing at row 0.]

### Region I: resize diagram (bottom-right; green, red, purple, black)
```
arr2 [green box]-(short red stub, ticked)     (purple dashed box)
        \                               +----------------+      +----------------+ purple
temp [green box]---(green arrow)----->  |  red block     |      |   - - - - -    | (black dashes)
        \                    (red ->)-> |    :           |      |                |
         \                              | ============== |-.->  | ======         |
          \                             | ============== |-.->  | ======         |
           \                            +----------------+ .    +----------------+
            \_______________(purple curve)________________/ (to purple block)
```
[The temp box has a green arrow to the red block of 100 elements. A short detached red arrow, just to the left of the red block, also points at the red block's bottom rows. At the right end of arr2's box there is a short red stub with a small vertical tick through it: the original red pointer. A purple curve starts INSIDE arr2's box, runs down across the temp box, passes under everything, and comes up to a purple dot at the bottom-left of the tall PURPLE block (200 elements). The red block has red lines in its bottom rows and a red dotted "⋮" above them. A purple DASHED rectangle is drawn just above the red block. Four short black lines ending in purple dots join the red block's rows to the purple block's bottom rows: the element-by-element copy. The purple block has purple lines at the bottom and one black dashed line in its upper part.]

### Region J: bottom (black)
```
- use after de allocation
```
[This is written with "vre ofter" handwriting.]

[Footer box, bottom-right] Initials: [blank]

### Ambiguous handwriting — reading chosen

| As written | Possible readings | Chosen | Why |
|---|---|---|---|
| if missing the red head | head / heap | "head" as written, marked [sic], meaning "heap" | At 4x zoom the last letter is clearly a "d" with a closed bowl and tall stem. In context ("red ... space is not de allocated - memory leak") the meaning is the red heap block. |
| char str[] = "hello" / string s1 = "hello" | hello / hollo / hella / helb | hello | The array drawn beside it has the cells h e l l o \0, so the first literal is "hello". The second is written quickly with the same word. |
| last cell of str and its label | \0 / \ø / N | \0 (null terminator) | The last cell and the bracket label above it both look like a backslash followed by a slashed zero. A 5-letter literal needs a 6th cell for '\0'. |
| _str | _str / -str | _str | A short low dash sits before "str". It names std::string's internal pointer to a heap buffer (the red box "size to fit"). |
| Compress | Compress / Compres / Compresl | Compress | Ordinary vector operation (shrink-to-fit). The last letter is a hasty "s". |
| s1.setSID(10) and s3->setSID(12) | setSID(10)/(1o); setSID(12)/(i2) | 10 and 12 | The diagram shows s_id = 10 in both s1 and s2 (after the copy). 12 matches the second, separate object s3. |
| s_id | s_id / s_i d / S-id | s_id | The instructor's student.h also uses int s_id;. |
| use after de allocation | use after / vre ofter | use after de allocation | The handwriting is sloppy, but the phrase is the standard use-after-free error. It follows the delete temp[] discussion. |
| purple dashed box above the red block, and the black dashed line in the purple block | space you cannot simply extend in place / the new capacity area / the 100-element boundary | described only (not interpreted) | There is no label for either mark. |
| Copy Const | Copy Const / Copy Construct | Copy Const (short for Copy Constructor) | The word ends after "Const". The same term is written in full in black: "Copy Constructor". |
| red stub with a tick at the right end of arr2's box | the old red pointer, cut (arr2 no longer points to the red block) / the start of the red arrow | described as a short red stub with a small vertical tick | There is no label. A separate red arrow, detached from it, points at the red block. |

### Board slips / gotchas (verified)

- The class as written does not compile: "public" has no colon and the closing brace has no semicolon. Re-verified: "error: expected ':' before 'void'" and "error: expected ';' after class definition" (chk_g4/cpp/v8_board.cpp). Also s1.setSID(10), s2 = s1, Student *s3 = new Student, int *temp = arr2 and delete temp[] have no ';'.
- IMPORTANT: the page links "s2 = s1" to the Copy Constructor, but s2 ALREADY EXISTS (Student s1, s2;), so s2 = s1; calls the copy ASSIGNMENT operator (operator=), not the copy constructor. Re-verified: even with a user-written Student(Student&), "[copy constructor]" is NOT printed for s2 = s1;, and s1/s2 still share the data block. It IS printed for Student s5 = s1;. The copy constructor runs for Student s5 = s1; / Student s5(s1); / pass or return by value (v9_copy.cpp).
- Default (member-wise) copy: the pointer member data is shallow-copied (re-verified: s1.data == s2.data). The array member arr[100] is copied element by element, which is a real copy (re-verified: different addresses; s2.s_id == 10). This matches the red diagram.
- The board signature Student(Student &) should be Student(const Student &). With a non-const reference you cannot copy a const object. Re-verified: "binding reference of type 'Student&' to 'const Student' discards qualifiers" (v10_constref.cpp).
- Deep copy needs the Rule of Three: destructor (delete [] data), copy constructor, AND operator=. With only a destructor and the default copy, two objects delete the same block. Re-verified with AddressSanitizer: "attempting double-free" (v17_r3.cpp).
- Student *s4 = s3; copies only the pointer. No constructor runs and s4 == s3 is the same object (re-verified). Calling delete s3; and then delete s4; is a double delete (re-verified with AddressSanitizer: "attempting double-free", v18_dd.cpp).
- char str[] = "hello" has 6 bytes, including '\0' (re-verified: sizeof(str)==6). string s2 = s1 is an independent (deep) copy: after changing s2[0], s1 stays "hello" (re-verified: prints hello Jello, v11_str.cpp).
- "delete temp[]" is invalid syntax. Re-verified: "error: expected primary-expression before ']' token" (v12_del.cpp). The correct form is delete [] temp;.
- The memory leak is re-verified with AddressSanitizer: leaving out delete [] temp gives "Direct leak of 400 byte(s)" (100 ints) (v13_leak.cpp). Reading temp[5] after delete [] temp gives "heap-use-after-free" (v14_uaf.cpp). Set temp = nullptr after deleting.
- int arr1[100] (marked X) cannot be resized: its size is fixed at compile time. Only a heap array reached through a pointer can be replaced with a bigger one.

---

## Page 20260924-1  (written date: 9-24-2026)

[Header box, top-right, printed template] Date: 9-24-2026 [the 0 of the year is a slashed zero (a separate stroke through it), as on 9/17 and 9/22]

### Region A: vector addAtEnd pseudocode (top-left; black, with red code)
```
Vector

- addAtEnd ( elem &e )
        - check if full
            true :   resize
            false    add to next location
                  [red]  arr2 [curr] = e
                  [red]      curr++
```
["&" in "elem &e" is drawn like a "G". "false" is written like "falke" and "location" like "locatin". "false" has no colon. The "=" in arr2[curr] = e is small.]

### Region B: vector memory diagram (top-center; red, with a purple resize arrow)
```
[red]  max N ---->  +------------+ - - +
                    |     .      |     :
                    |     .      |     :
                    |     .      |     :
                    +------------+ <---- curr  [red]
                    |  (empty)   |     :
                    +------------+     :
                    |////////////|     :
                    +------------+     :
                    |////////////|     :
[red] arr2 -------> +------------+     :
                    |////////////|     :
                    +------------+ - - +
                     \_ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ ->  [purple, larger array]
[red] max_elements = N
[red] curr_element
```
[The red rectangle is the array. From the top: a tall empty region with a dotted "⋮", then a horizontal line, then ONE EMPTY row, then the bottom 3 rows hatched with red tick marks (the stored elements). "max N" has an arrow pointing to the top of the array (capacity N). "curr" has an arrow pointing left at the line that forms the TOP edge of the empty row, one full row above the hatched rows. In the ink stroke order the arrow was drawn first, and this line was added afterwards, exactly at the arrow's tip. "arr2" has an arrow pointing at the line that forms the top edge of the bottom row (index 0). So both arrows mark the top edge of the slot they index: arr2 marks slot 0, and curr marks slot 3, the empty next free slot. In the hatched area, the lines above the first and second rows stick out a little on the right with thick or hooked ends. A narrow red DASHED outline runs alongside the right side of the array, from its top to its bottom. A purple dashed curved arrow goes from under the red array to a taller PURPLE rectangle on the right (the resized array). The purple array has lines at its bottom (the copied elements) and a few lines higher up.]

### Region C: resize rule (to the right of "max_elements = N"; purple, black, green)
```
[red] max_elements = N  [purple] --> resize  inc. max_elements --> inc value
                                                               [purple] +1
                                                               [black]  + (factor) (max-elements)
                                                               [green]  +100
```
["resize" is double-underlined in purple and written like "rezize". A small dot sits under "factor". The three rows are three alternative increment values: +1 (purple), + factor*max_elements (black), and +100 (green). The "=" in max_elements = N is tiny and looks like ":".]

[The rest of the page (about two-thirds) is blank grid.]
[Footer box, bottom-right] Initials: [blank]

### Ambiguous handwriting — reading chosen

| As written | Possible readings | Chosen | Why |
|---|---|---|---|
| +100 (green, last increment option) | +100 / +200 | +100 | Confirmed from the vector ink. The first digit is made of TWO strokes: a flag-and-stem stroke plus a separate base stroke. His purple "1" in "+1" on this page is built exactly the same way. Every "2" on this page (arr2 in the diagram, arr2 in arr2[curr], and the 2s in the date) is ONE continuous stroke that includes its base. So the digit is a 1 with a wide base serif, not a 2. |
| elem &e | elem &e / elem Ge / elem 6e | elem &e | His "&" in Student(Student &) on 9/22 is drawn the same G-like way. A C++ reference parameter fits "addAtEnd(elem &e)". |
| (max-elements) | max-elements / max_elements | max_elements (written with a hyphen-like dash) | The same variable is written "max_elements" with an underscore on the left of the diagram. |
| max_elements = N | = / : | = | In the ink it is two very short stacked horizontal strokes, so at normal zoom it looks like a colon. His "=" in arr2[curr] = e on this page is built the same way (two short stacked strokes). An assignment/definition of the capacity also fits "=". |
| curr / curr_element | curr is shorthand for curr_element / a separate index | curr = curr_element | Only curr_element is listed as a member. The "curr" arrow marks the empty slot just above the 3 stored elements, the same slot arr2[curr] = e writes to. |
| false (written "falke") | false / falke | false | It is the counterpart of "true :" in the "check if full" test. |
| resize (written "rezize", double-underlined) | resize / rezize | resize | The same word is written "resize" on the left of the page and on 9/22. |
| red dashed outline to the right of the red array | growing in place (not possible) / the capacity boundary | described only | There is no label. |

### Board slips / gotchas (verified)

- Read literally, the pseudocode says 'true: resize' and 'false: add to next location', as if a full array is resized but the element is not added. The correct logic is: if full, resize; then ALWAYS do arr2[curr] = e; curr++. That is how the verified simulation is written (tx_g4/cpp/t10_vec.cpp; re-checked in chk_g4/cpp/v16_sim.cpp).
- "check if full" means curr_element == max_elements. Writing arr2[curr] without that check writes past the end of the array.
- addAtEnd(elem &e) takes a non-const reference, so addAtEnd(5) will not compile. Re-verified: "cannot bind non-const lvalue reference of type 'elem&' to an rvalue" (chk_g4/cpp/v15_ref.cpp). Use const elem &e.
- The growth rule + (factor)(max_elements) never grows from 0: if max_elements starts at 0, the new max is 0 + factor*0 = 0 (re-verified in v16_sim.cpp), and arr2[0] is out of bounds. Start with a capacity of at least 1, or use max(1, ...).
- Cost re-verified by independent simulation (N = 100,000 addAtEnd calls starting from capacity 1). Growth +1 gives 4,999,950,000 element copies and growth +100 gives 49,951,000 (both O(N^2) total). +factor*max with factor 1 (doubling) gives 131,071 (O(N) total, amortized O(1) per add) (v16_sim.cpp).
- resize must also update max_elements and delete [] the old array. Otherwise you get the 9/22 memory leak.
