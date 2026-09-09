# review/

Snapshot taken 2026-07-30, after a ~10 month gap since the last linalg commit
(68a068a, Sept 17 2025).

- **[landmines.md](landmines.md)** — everything wrong in the code, or right only
  by accident. Read #1 first; it's a one-line fix and it's why you stopped.
- **[how-it-works.md](how-it-works.md)** — how LU decomposition works from first
  principles, and a line-by-line trace of your own LU + forward substitution
  with real numbers.

## The 30-second version

Your LU decomposition works. Your forward substitution works. Both were already
working when you walked away. The build was broken by a missing function
declaration, which made it look like the math was broken.

Fix the declaration, then write back substitution. That's the whole remaining
gap to a working matrix inverse.
