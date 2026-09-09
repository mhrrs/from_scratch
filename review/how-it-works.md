# How the code actually works

Written 2026-07-30, because the pattern in `log.md` is clearly "leave for six
months, come back having forgotten everything." This is the refresher, so
next time you don't have to re-derive it.

Two parts: **LU decomposition** (the theory + your implementation) and
**forward substitution** (your implementation, which is subtler than it looks).

---

# PART 1: LU decomposition

## Why it exists at all

You want to solve `A x = b`. Gaussian elimination does it in about `n³/3`
operations. Fine — once.

But you rarely want it once. To get `A⁻¹` you need to solve `A x = e` for all
`n` columns of the identity. Naively that's `n × n³/3 = n⁴/3`. Miserable.

The observation that saves you: **when you solve `A x = b` twice with different
`b`, you redo the exact same elimination arithmetic both times.** The row
operations depend only on `A`. `b` just goes along for the ride.

So: do the elimination *once*, save what you did, and replay it cheaply for each
new `b`. "What you did" is the L matrix. That's the entire idea.

Cost after factoring: each solve is two triangular solves at `n²` each. The
inverse becomes `n³/3 + 2n³` instead of `n⁴/3`. For n=100 that's roughly a
50x difference.

## What triangular actually buys you

A lower-triangular system is trivial to solve because the first equation has
exactly one unknown:

```
 1·y₀                = 1      ->  y₀ = 1,      no work
 2·y₀ +  1·y₁        = 0      ->  y₁ = 0 - 2·y₀,  now that y₀ is known
 3·y₀ +  9·y₁ + 1·y₂ = 0      ->  y₂ = 0 - 3·y₀ - 9·y₁
```

Solve top to bottom, each row substituting in everything already found. That's
"forward substitution." Upper-triangular is the same thing bottom-to-top —
"back substitution."

So the whole game is: turn the hard general matrix `A` into two easy triangular
ones.

## Where L comes from (the part that feels like magic)

Elimination turns `A` into upper-triangular `U` by repeatedly subtracting
multiples of one row from the rows below it.

Here's the key: **every row operation is itself a matrix multiplication.**
"Subtract m times row p from row i" is left-multiplication by an elementary
matrix E — an identity matrix with a single `-m` in position (i,p).

So all of elimination is:

```
Eₖ ··· E₂ E₁ A = U
```

Move them to the other side:

```
A = E₁⁻¹ E₂⁻¹ ··· Eₖ⁻¹ U  =  L U
```

And now two pieces of luck stack up:

1. **Inverting an elementary matrix is free.** If E subtracts m times row p from
   row i, then E⁻¹ adds it back. Same matrix with the sign flipped: `+m`.
2. **Multiplying them all together is free.** Because of the order they come in,
   the product is just an identity matrix with every multiplier sitting in its
   own slot. Nothing interferes with anything else.

So L is *literally just the multipliers you already computed*, written into
position, with a positive sign. You never compute L. You record it.

> **The sign question you will ask again in six months:** "I *subtracted* m
> during elimination — why is L storing `+m`?" Because L is built from the
> *inverses*, which undo the subtraction. And there's an intuition that makes it
> obvious: **row i of L is the recipe for rebuilding row i of A out of the rows
> of U.** Check it on your own matrix — L row 2 is `[3, 9, 1]`, so:
>
> `3·[2,3,1] + 9·[0,1,0] + 1·[0,0,2] = [6, 9+9, 3+2] = [6,18,5]` = row 2 of A ✓
>
> L says "how much of each U row do I need." Of course it's positive.

## Then the two-step solve

Given `A = LU`, solving `A x = b` becomes `L U x = b`. Insert a placeholder
`y = U x`:

1. Solve `L y = b` by **forward** substitution (top-down). Cheap, L is triangular.
2. Solve `U x = y` by **back** substitution (bottom-up). Cheap, U is triangular.

For the **inverse** specifically: run this with `b` = each column of the
identity in turn. The `x` you get back is the corresponding column of `A⁻¹`.
That's the `A x_i = e_i` note you left yourself in `experiments.hpp`. You were
right.

---

## Your implementation, traced

`inverse.cpp`, function `LU_decompisition`. Per pivot `p` it does four things:

1. **multipliers** — `m_i = U[i][p] / U[p][p]` for every row `i` below `p`
2. **build K** — `K[i][j] = m_i · U[p][j]`
3. **subtract** — `U -= K`
4. **record** — `L[i][p] = m_i`

Step 2 is worth naming: K is the **outer product** of the multiplier column with
the pivot row. And "subtract an outer product from the trailing submatrix" is
exactly the standard right-looking LU update you'd find in a textbook or in
LAPACK. You reinvented it. The 03/25 log entry where you rewrote everything
"for simplicity" is the entry where you accidentally landed on the canonical
algorithm.

### The trace, on your own test matrix

```
A = [ 2   3   1 ]
    [ 4   7   2 ]
    [ 6  18   5 ]
```

**Pivot p=0**, pivot value `U[0][0] = 2`, pivot row `[2,3,1]`.

```
m₁ = 4/2 = 2
m₂ = 6/2 = 3

K row1 = 2·[2,3,1] = [4, 6, 2]
K row2 = 3·[2,3,1] = [6, 9, 3]

row1: [4, 7,2] - [4,6,2] = [0, 1, 0]
row2: [6,18,5] - [6,9,3] = [0, 9, 2]
```

```
U = [ 2  3  1 ]        L = [ 1  .  . ]
    [ 0  1  0 ]            [ 2  1  . ]
    [ 0  9  2 ]            [ 3  .  1 ]
```

First column below the diagonal is zeroed, and the multipliers that did it are
parked in L.

**Pivot p=1**, pivot value `U[1][1] = 1`, pivot row `[0,1,0]`.

```
m₂ = 9/1 = 9
K row2 = 9·[0,1,0] = [0, 9, 0]
row2: [0,9,2] - [0,9,0] = [0, 0, 2]
```

```
U = [ 2  3  1 ]        L = [ 1  0  0 ]
    [ 0  1  0 ]            [ 2  1  0 ]
    [ 0  0  2 ]            [ 3  9  1 ]
```

**Pivot p=2** — nothing below it. Done.

Verify `L·U = A`:
- row 0: `1·[2,3,1]` = `[2,3,1]` ✓
- row 1: `2·[2,3,1] + 1·[0,1,0]` = `[4,7,2]` ✓
- row 2: `3·[2,3,1] + 9·[0,1,0] + 1·[0,0,2]` = `[6,18,5]` ✓

**This is correct.** It has been correct since at least Sept 2025.

### Implementation notes on your version

- The outer loop `for idx in 0..n²` with `if (idx/cols == idx%cols)` scans all
  `n²` flat indices to find the `n` diagonal ones. It works, it's just doing
  `n²` iterations of nothing. A loop over `p in 0..n` with `idx = p*n+p` is the
  same thing directly.
- Your own note in `LU_decomposition.md` — "remove the K values, just index the
  multipliers into the operation" — is correct and worth doing. K is a full `n²`
  buffer that only ever holds nonzeros in the trailing submatrix. You can fold
  steps 2 and 3 into one loop and drop the allocation entirely.
- `U_hat` is declared, reserved, zero-filled, and never used.
- See `landmines.md` #2 before touching any of this.

---

# PART 2: Forward substitution

`matrix.cpp`, function `forward_substitute`. This one is denser than it looks —
it solves all `n` systems at once and synthesizes the right-hand sides on the
fly.

```cpp
int n = static_cast<int>(std::sqrt(L.size()));
auto index = [n] (int i, int j) { return i*n+j; };
std::vector<float> Y(n*n, 0.0f);

for (int k = 0; k < n; k++){          // which column of I we're solving against
    for (int i = 0; i < n; i++){      // which row / which unknown
        float sum = 0;
        for (int j = 0; j < i; j++){  // every unknown already solved above row i
            sum += L[index(i, j)] * Y[index(j, k)];
        }
        float r = (i == k) ? 1.0f : 0.0f;
        Y[index(i, k)] = (r - sum);
    }
}
```

## The three loops

**`k` — which right-hand side.** You're solving `L y = eₖ` for each of the `n`
identity columns. Column `k` of the answer Y is the solution for `eₖ`. Solve all
`n` and Y is the full `L⁻¹`.

**`i` — which unknown, top-down.** Row `i` of `L y = eₖ` reads
`L[i][0]·y₀ + L[i][1]·y₁ + ... + L[i][i]·yᵢ = eₖ[i]`. Everything left of the
diagonal is already known (that's the point of going top-down), and everything
right of it is zero (that's the point of L being lower-triangular). One unknown:
`yᵢ`.

**`j` — the already-known terms.** `j < i` is doing real work: it stops exactly
at the diagonal. Terms past it would be multiplied by structural zeros, so
skipping them isn't an optimization, it's the algorithm.

## The `r` trick

```cpp
float r = (i == k) ? 1.0f : 0.0f;
```

This is the part worth appreciating. You never build the identity matrix. `r` is
element `i` of the `k`-th identity column, computed on demand — which is `1`
exactly when `i == k`. One ternary replaces an `n²` allocation and every read
from it.

## The trace

With `L = [1,0,0, 2,1,0, 3,9,1]`:

**k=0** — solving `L y = [1,0,0]`:
```
i=0:  no j terms, sum=0,  r=1  ->  Y[0][0] =  1
i=1:  sum = 2·1 = 2,      r=0  ->  Y[1][0] = -2
i=2:  sum = 3·1 + 9·(-2) = -15, r=0 ->  Y[2][0] = 15
```

**k=1** — solving `L y = [0,1,0]`:
```
i=0:  sum=0,              r=0  ->  Y[0][1] =  0
i=1:  sum = 2·0 = 0,      r=1  ->  Y[1][1] =  1
i=2:  sum = 3·0 + 9·1 = 9, r=0 ->  Y[2][1] = -9
```

**k=2** — solving `L y = [0,0,1]`: gives `[0, 0, 1]`.

```
Y = [  1   0   0 ]
    [ -2   1   0 ]
    [ 15  -9   1 ]
```

Sanity check `L·Y = I`:
- row 1: `2·1 + 1·(-2) = 0` ✓
- row 2 col 0: `3·1 + 9·(-2) + 1·15 = 3 - 18 + 15 = 0` ✓
- row 2 col 1: `9·1 + 1·(-9) = 0` ✓

**Correct.** That's genuinely `L⁻¹`.

## The optimization you already found and didn't apply

From `matrix_mult.md`:

> "there is no reason to multiply the first 12 values when calculating e[1,1]
> because all of the values for y[1,n] will be zero * L[1,n]"

You were right and here's the formal reason: **the inverse of a unit
lower-triangular matrix is also unit lower-triangular.** Look at Y above — zeros
above the diagonal, ones on it. Guaranteed, not a coincidence of this example.

So for column `k`, every `Y[i][k]` with `i < k` is zero, and your loop is
currently computing all of them the long way. Starting `i` at `k` instead of `0`
skips them and roughly halves the work. You can also write `Y[k][k] = 1`
directly rather than deriving it.

Only valid because the diagonal is unit — see `landmines.md` #5, which is the
same assumption.

---

# What's left

Between here and a working `inverse_mat`, the only piece of *mathematics*
missing is **back substitution**: solve `U x = y` for `x`.

It's the mirror of what you already wrote:
- iterate `i` from `n-1` down to `0` instead of up
- the inner sum runs over `j > i` (the already-solved unknowns are now *below*)
- **you must divide by `U[i][i]`** — U's diagonal is `[2, 1, 2]`, not ones. This
  is the divide that's commented out in forward substitution and doesn't matter
  there. Here it matters.

Feed it the `Y` from forward substitution and the `X` you get back is `A⁻¹`.

You are one function away.
