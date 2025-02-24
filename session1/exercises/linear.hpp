#include <stdlib.h>
#include <iostream>
#include <vector>
#include <bits/stdc++.h>
using namespace std;

vector<float> matrix_mult(vector<vector<float>> A, vector<float> x){
    vector<float> result;

    //non-optimized way:
    const int rows = A.size(); // in a 10x3 mat, this should get 10
    const int cols = A[0].size();

    // ensure the A and x are size compatible

    // make result the product of zeros for a vec of this size:

    // 1x3 * 3x2  = 1x2 where RowsxCols 

    // multiple each row by the x vector
    for (int col = 0; col < cols; col++){
        float sum = 0.0;
        for (int row = 0; row < rows; row++){
            float prod = A[col][row] * x[row];
            sum += prod;
        }
        result.push_back(sum);
    }


    return result;
}