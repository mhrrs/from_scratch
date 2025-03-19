# LOG:

*03/18/2025:*
so right now i get the following output from printing the following code:
code:
// THIS IS HOW YOU FIND PIVOTs
    for (int idx = 0; idx < U.size(); idx++){
        if (idx%(rows+1) == 0){
            //we've found our pivot value, now lets calculate the multiples and then modify the L
            for(int j = idx+cols; j<U.size(); j+=cols){
                // printf("u[%d,%d]\n", idx, j);
                double multiplier = U[j]/U[idx];
                printf("L[%d, %d] = %f\n", idx, j, multiplier);
                // printf("U[j] = %f and U[idx] = %f\n", U[j], U[idx]);
                L[j] = multiplier;
            }
        }
    }

output:
u[0,3]
L[0, 3] = 2.000000
U[j] = 4.000000 and U[idx] = 2.000000
u[0,6]
L[0, 6] = 3.000000
U[j] = 6.000000 and U[idx] = 2.000000
u[4,7]
L[4, 7] = 2.571429
U[j] = 18.000000 and U[idx] = 7.000000
L:
Result:
1
0
0
2
1
1
0
3
2.57143
1

Now you will notice that the 18/7 results in a weird float value. And considering I have already precalculated this LU Decomp problem on paper, I know it is wrong.
> The reason it is wrong is because we allow ourselves to go back through updating L without updating the U in between the first and second pivot value.