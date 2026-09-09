# LANDMINES

Reviewed 2026-07-30. Things in the linalg code that are wrong, or that are
right only by accident. Nothing here is fixed — this is the list, not the patch.
Deliberately no fix-code written out, since the point of this repo is that you
write it.

Ordered by "how badly will this waste my evening."

---

## 1. The build is broken. One line. [BLOCKING]

```
matrix.cpp:14:27: error: use of undeclared identifier 'forward_substitute'
```

`forward_substitute` is *defined* at `matrix.cpp:20` but *called* at
`matrix.cpp:14`. C++ reads top-to-bottom; at line 14 the name doesn't exist yet.
`matrix.hpp` only declares `matrix_mult`, so nothing fixes it from outside.

Fix: declare it in `matrix.hpp` (or reorder the two functions in the .cpp).

**This is almost certainly why you walked away in Sept 2025.** The code
underneath it was already working. Read that again.

Compile line that reproduces it:
`g++ -std=c++17 test.cpp inverse.cpp matrix.cpp utils.cpp -o test`

---

## 2. `M[i] = mult;` — inverse.cpp:85 [SILENT, WILL BITE LATER]

Sitting just outside the `if` block above it, at the bottom of the multiplier
loop. Every iteration it writes the *most recently computed* multiplier into
whatever slot it's currently on. So the multiplier for row 1 gets smeared across
every index until row 2 computes a new one.

For the test matrix, M ends up as:

```
[0,0,0,  2,2,2,  3,3,3]     <- what it actually is
[0,0,0,  2,0,0,  3,0,0]     <- what it should be
```

**Your answers are still correct.** That is luck, not design. The only two
places that read M (the K loop at line 94, the L update at line 109) both index
`M[i*cols + (idx % cols)]` — the pivot column — and the pivot-column entries are
the ones that happen to be right. Every other cell of M is garbage that nothing
currently looks at.

The moment you touch the indexing, or optimize K away as your notes plan to,
this starts producing wrong numbers with no warning. Delete the line.

---

## 3. No pivoting. Division by zero is silent. [KNOWN HOLE]

`inverse.cpp:82` does `U[i] / U[idx]` with no check that `U[idx]` is nonzero.
If a diagonal entry is zero — or just very small — you get `inf`/`nan`
propagating through the whole factorization, and nothing prints an error.

`{{0,1},{1,0}}` is enough to break it. That matrix is perfectly invertible; it
just needs its rows swapped first.

Real LU is **PA = LU**: you track a permutation P of row swaps, and at each
pivot you swap in the largest-magnitude candidate from the column below
(partial pivoting). That also buys you numerical stability, not just
zero-avoidance — dividing by a tiny pivot blows up rounding error.

This is a deliberate not-yet, not a bug. But know that it's missing so you
don't spend an evening confused by a `nan`.

---

## 4. `matrix_mult` ignores its second argument [TEST LIES TO YOU]

`matrix.cpp:12-16`. Signature takes `(L, B)`. Body never touches `B` — it just
returns `forward_substitute(L)`. It's tagged `// under dev` and it is.

The consequence is in `test.cpp:29`, where the comment says
`// verify that A = L * U` and the call is `matrix_mult(L, U)`. It does not
verify that. It prints L-inverse under the label `Res`.

So once you fix landmine #1, the program builds and prints correct-looking
numbers that have nothing to do with what the comment claims. That is a
genuinely nasty trap — you'd have gone looking for a bug in LU that isn't there.

Fix the comment and the test at the same time you write the real multiply.

---

## 5. Missing divide in forward substitution [CORRECT BY ACCIDENT]

`matrix.cpp:38`:

```cpp
Y[index(i, k)] = (r-sum);          // line 38, live
// Y[index(i, k)] = (r-sum)/A[index(i, i)];   // line 37, commented out
```

Textbook forward substitution divides by the diagonal `L[i][i]`. Yours doesn't.

It works anyway **because Doolittle LU gives L a unit diagonal** — every
`L[i][i]` is exactly 1, and dividing by 1 changes nothing. Your `L` builder at
`inverse.cpp:57-58` pushes a literal `1` on the diagonal and never touches it
again, so this holds for anything coming out of your own factorization.

Two reasons to care:
- Feed this function any lower-triangular matrix that *isn't* unit-diagonal and
  it returns wrong answers silently.
- The commented line refers to `A[...]`, a parameter name that no longer exists
  (it's `L` now). Leftover from an earlier signature.

Decide which function this is: "solve unit-lower-triangular" (then rename it and
document the assumption) or "solve any lower-triangular" (then restore the
divide). Right now it's neither, and the commented-out line makes it look
unfinished when it isn't.

---

## 6. `cols` and `rows` are swapped [INVISIBLE UNTIL IT ISN'T]

`inverse.cpp:32-33`:

```cpp
const int cols = A.size();       // this is the ROW count
const int rows = A[0].size();    // this is the COLUMN count
```

`A.size()` is how many inner vectors there are = how many rows. You have them
backwards. Every use downstream is self-consistent, and the square-matrix guard
means `rows == cols` in every case that gets far enough to matter, so nothing
breaks today. It's purely a readability bomb for future-you trying to reason
about the indexing.

---

## 7. Non-square matrices print an error and then run anyway

`inverse.cpp:36-39`. The `return` is commented out. So a non-square input prints
"Error. Not a square matrix." and then walks straight into the loops, which
assume square, and reads out of bounds.

Note you also can't just uncomment it — the function returns a tuple, so a bare
`return;` won't compile. You need to decide the failure contract: return an
empty tuple, throw, or take an out-param success flag. Worth thinking about,
it's a real API design question you'll hit everywhere.

---

## 8. Docs contradict the code on memory layout

`session1/linalg/LinearAlgebraDocumentation.md` says everything is stored
**column-major**. The code is **row-major**.

`inverse.cpp:55-63` builds U with `U[col*cols + row] = A[col][row]`, and since
A's first index is the row, that's `U[i*n + j] == A[i][j]`. Row-major. Your
`index` lambda in `matrix.cpp:25` is `i*n+j`, also row-major. The code is
consistent with itself; the doc is just wrong.

Fix the doc, not the code. Row-major is the right default and matches C/C++
convention.

---

## 9. Repo hygiene

- **Three Windows `.exe` binaries are committed to git.** `file` reports them as
  `PE32 executable ... for MS Windows`. You're on macOS now. They're dead
  artifacts from the old machine:
  `session1/linalg/test.exe`, `session1/exercises/ex1.exe`,
  `session1/exercises/linear.exe`
- **There is no `.gitignore` at all.** That's why the above happened.
- **`session1/linalg/experiments.hpp`** — 149 lines, an older abandoned LU
  attempt, `#include`d by nothing. It redefines `display_vec` and
  `LU_decompisition`, so if you ever do include it you'll get redefinition
  errors. It's the version of the algorithm you gave up on, sitting right next
  to the version that works. Delete or move to an `attic/` folder.
- **`session1/main.hpp`** — dead scaffolding, included by nothing, and would not
  compile if it were: `for(v:Vec)` is missing a type, the `operator<<` has no
  `return`, and `linear_regression` has an empty body but a non-void return type.
- **`LU_decomposition.md` and `inverseNotes.md`** are near-identical copies of
  the same notes. `inverseNotes.md` has the forward-substitute image, that's the
  only difference. Merge them.
- **No build system for linalg.** You're hand-typing a four-file g++ invocation
  every session. `image_editor/` has a Makefile (empty, but it exists) — linalg
  doesn't even have that. This is real friction on a project you only touch late
  at night.

---

## 10. `image_editor` — the `demo.txt` thing

Uncommitted working-tree deletion of `image_editor/demo.txt`, but `main.c:10`
still does `fopen("demo.txt", "r+")`. That call now returns `NULL`, there's no
null check, and no `fclose`. Also relative path, so it only ever worked when run
from inside `image_editor/`.

Not urgent — that subproject is ~13 lines old — but it'll be the first thing
that confuses you when you go back.

---

## Not landmines, just true

- **LU decomposition works.** Hand-traced against `{{2,3,1},{4,7,2},{6,18,5}}`,
  produces `L = [1,0,0, 2,1,0, 3,9,1]`, `U = [2,3,1, 0,1,0, 0,0,2]`, and
  `L*U == A` exactly. Matches the output you'd already pasted into
  `matrix_mult.md` back in the day.
- **Forward substitution works.** Produces `[1,0,0, -2,1,0, 15,-9,1]`, which is
  genuinely L-inverse.
- The only *mathematics* missing between here and a working `inverse_mat` is
  **back substitution** (solve `U x = y`, iterate rows bottom-up, and this time
  you DO need the divide by `U[i][i]` because U's diagonal is not 1s).
