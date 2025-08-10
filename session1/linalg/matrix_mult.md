# DESCRIPTION: How does matrix multiplication function work?

INPUT:
2 vector<float> objects
2 rowxcol descriptions of those objects

IDEA:

A = [1,2,3,1,2,3,1,2,3]
B = [1,2,3,1,2,3,1,2,3]

A = [
    1, 1, 1,
    2, 2, 2,
    3, 3, 3
]

B = [
    1, 1, 1,
    2, 0, 4,
    3, 5, 3
]

R = A*B = 3x3 matrix

first matrix will increase col number and second matrix will increase row number

R[1,1] = (A[1,1] * B [1,1]) + (A[1,2] * B [2,1]) + (A[1,3] * B [3,1])
R[1,1] = (1* 1) + (1* 2) + (1* 3)

Now iterate to the next row value R[2,1]
R[2,1] = (A[1,1] * B [1,2]) + (A[1,2] * B [2,2]) + (A[1,3] * B [3,2])
R[2,1] = (1* 1) + (1* 0) + (1* 5)


SO... you know what you need from each matrix. you need rows from A and cols from B.
Aggregate these.

row_val = []
for i in range(A):
    row_val append(A[i])
    i += rows

col_val = []
for i in range(B):
    col_val append(A[i])
    i += cols




current_row = 0;
current_col = 0;
for k in range(cols*rows):
    for i in range(cols):
        R[k, i] += A[current_row, i] * B[i, current_col];








==== LU DECOMP MAIN: ====
L:
Result:
1
0
0
2
1
0
3
9
1

=============================
U:
Result:
2
3
1
0
1
0
0
0
2

U = [
    2,0,0,
    3,1,0
    1,0,2
]

=============================
::: k::: 0
A[i]: 1
A[i]: 2
A[i]: 3
::: k::: 1
A[i]: 0
A[i]: 1
A[i]: 9
::: k::: 2
A[i]: 0
A[i]: 0
A[i]: 1
====================
::: k::: 0
B[i]: 2
B[i]: 0
B[i]: 0
::: k::: 1
B[i]: 3
B[i]: 1
B[i]: 0
::: k::: 2
B[i]: 1
B[i]: 0
B[i]: 2