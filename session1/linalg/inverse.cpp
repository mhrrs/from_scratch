#include <iostream>
#include <vector>
#include <array>
#include <tuple>
#include "utils.hpp"

using namespace std;



// DOCUMENTATION:
// THIS IS how a matrix is indexed column-wise:
//     0 1 2
//     3 4 5
//     6 7 8
//



// inverse calculation
// vector<vector <float>> inverse_mat(vector<vector <float>> Mat){
//     // so first we want to perform A*A^-1 = I
//     // where A*x_i = e_i where e_i is the i-th column of the Identity matrix I
//     // however now we have L and U to help us perform this equation
//     display_vec(Mat[0]);
// }



std::tuple<std::vector<float>, std::vector<float>> LU_decompisition(vector<vector <float>> A){
    // convert A to 2D format
    // init L
    vector<float> L;
    vector<float> U;
    vector<float> M;
    vector<float> K;
    vector<float> U_hat;

    // get col and row size
    const int cols = A.size();
    const int rows = A[0].size();

    // check to see if the matrix is square, else return error
    if (cols != rows){
        cout << "Error. Not a square matrix." << " ===> cols: " << cols <<"| rows: "<< rows << endl;
        // return;
    }

    // reserve mem space
    L.reserve(rows*cols);
    U.reserve(rows*cols);
    K.reserve(rows*cols);
    M.reserve(rows*cols);
    U_hat.reserve(rows*cols);

    for (int i = 0; i < rows*cols; i++){
        K.push_back(0);
        M.push_back(0);
        U_hat.push_back(0);
    }

    // convert L into Identity of A and copy A as U
    for (int col = 0; col < cols; col++){
        for (int row = 0; row < rows; row++){
            if (row == col){
                L.push_back(1);
            } else{
                L.push_back(0);
            }
            U.push_back(A[col][row]);
        }
    }

    for (int idx = 0; idx < int(U.size()); idx++){
        //most things happen inside this loop
        float mult = 0;
        if ((idx / cols) == (idx % cols)) {
            int pivot_row = idx / cols;
        
            // init M and K
            std::fill(M.begin(), M.end(), 0.0f);
            std::fill(K.begin(), K.end(), 0.0f);

            // OBTAIN MULTIPLIERS
            for (int i = 0; i < int(U.size()); i++){
                int i_row = i / cols;
                int i_col = i % cols;
                // Only update multipliers for rows below the pivot in the same column as the pivot.
                if (i_row > pivot_row && i_col == (idx % cols)) {
                    mult = float(U[i]) / float(U[idx]);
                    M[i] = mult;
                }
                M[i] = mult;
                // Optionally, for indices that don't match, you might leave M[i] unchanged or set it to 0.
            }

            //////////////////////////// USE MULTIPLIERS TO CALCULATE K
            int pivot_start = idx - (idx % cols);
            for (int i = pivot_row+1; i < rows; i++) {
                for (int j = 0; j < cols; j++) {
                    // Use the pivot row element from the correct column.
                    K[i*cols+j] = float(U[pivot_start + j]) * float(M[i*cols + (idx % cols)]);
                }
            }

            //////////////////////////////////////////// NOW UPDATE U
            for (int i = 0; i< int(U.size()); i++){
                U[i] -= K[i];
            }

            ///////////////////////////////////////////// NOW UPDATE L:
            for (int i = 0; i < int(U.size()); i++){
                int i_row = i / cols;
                int i_col = i % cols;
                // Update L only for rows below the pivot and in the pivot column.
                if (i_row > pivot_row && i_col == (idx % cols)){
                    L[i] = M[i];
                }
            }
        }
    }

    return std::make_tuple(L, U);
}


// Simply trying to optimize on the code created above
std::tuple<std::vector<float>, std::vector<float>> LU_decompisition_opt(vector<vector <float>> A){
    vector<float> L;
    vector<float> U;

    // reservations
    L.reserve(A.size()*A.size());
    U.reserve(A.size()*A.size());
    int cols = static_cast<int>(A.size());

    // turning L into A
    for (int i = 0; i < int(A.size()); i++){
        for (int j = 0; j < int(A.size()); j++){
                U.push_back(A[i][j]);
                if (i == j){
                    L.push_back(1.0);
                } else{
                    L.push_back(0.0);
                }
        }
    }

    // decomposing L into lower-triangular-mat and U into upper-triangular-mat
    // assess diagonal
    // find elimination value
    // gather pivot value
    // gather the elimination multiplier
    // use row based elim
    // reset and repeat

    // go along diagonal => first loop
    // find all non-zero values below that diagonal and calculate multiplier
    //    middle loop iterates over each value in that column 
    //   (which is accessible by taking diagonal value and adding col size)
    // the subtract that mult's row by the current diagonal row (do this by iterating over col size)

    //idea:
    // turn diagonal into 1s
    // iterate through vector, if 1 is found add to TOTAL, then select the
    // number of proceeding terms using the TOTAL value

    // NOTES ON VARS:
    // i moves along diagonal
    // i/(cols+1) => determines what row you are on
    // L[r] is the value being removed
    // r is diagonal idx + col size >> r lets us know the value under the diagonal it does NOT start us correctly in the third loop
    // we need another agnostic value that determine current row in update mode


    // j+r = for item under this diagonal, calculate the next 3
    //  

    // lol so we're actually calculating U in place?
    for (int i = 0; i <= (cols*cols)-1; i+=cols+1){
        float pivot = U[i];

        // go through each row in this column and reduce value.
        for (int r = i+cols; r <= (cols*cols)-1; r+=cols){
            // ^ maybe iterate by row number so that you then have the same index to call a specific row    
            float mult = U[r]/pivot;
            std::cout << "pivot: "<< pivot << " | L[r]: " << U[r] << std::endl;
            // std::cout << "r: "<< r << std::endl;

            // obtain row values by identifying what row you're on
            int cur_row_start = (r / cols); // < probably bad practice?
            int piv_row_start = (i / cols);

            // AH okay so the issue is that its subtracting from one row up
            // go through each column and reduct the value
            for (int j = 0; j < cols; j++){
                U[j+(cols*cur_row_start)] = U[j+(cols*cur_row_start)] - (mult * U[j+(cols*piv_row_start)]);
                if(((j+(cols*cur_row_start)) % cols) == 0){
                    L[j+r] = mult;
                }
                std::cout << "cur_row_start: " << cur_row_start << std::endl;
                std::cout << "mod var: " << j+r-(cols*cur_row_start) << std::endl;
                // std::cout << "i: " << i << " | j+r: " << j+r << " | cols: " << cols << std::endl;
            }

        }

        // DEBUG
        std::cout << "mid run: "<< i << " of " << (cols*cols)-1 << std::endl;
        display_vec(U);
    }

    std::cout << "L MAT:"<< std::endl;
    display_vec(L);

    return std::make_tuple(L, U);
}