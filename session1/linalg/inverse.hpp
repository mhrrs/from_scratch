#include <iostream>
#include <vector>
#include <array>

using namespace std;

// FOR TESTING:
//operator overload to display 'x' vector
template <typename T>
ostream& operator<<(ostream& os, const vector<T>& V){
    for(const auto& v:V){
        os << v << endl;
    }
    return os;
}

void display_vec(vector<float> V){
    cout << "Result: " << endl << V << endl << "=============================" << endl;
}

///////////////////////////////



// inverse calculation
vector<vector <float>> inverse_mat(vector<vector <float>> Mat){

    //decompose A into L*U



    // convert it into Mat*x_i = e_i where e_i is the i-th row of I and x_i is the i-th row of the inverse
    // we are thus solving for 'x'
    
    // take the first row of Mat and 


    // decompose Mat into L*U 

    // find the y for L*y  = x 

    // perform back substitution from U*x = y in order to get the matrix that is the inverse of A
}


// vector<vector<vector<float>>> LU_decompisition(vector<vector <float>> A){
vector<float> LU_decompisition(vector<vector <float>> A){
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

    cout << "M" << endl;
    display_vec(M);

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

    display_vec(U);
    display_vec(L);


    //
    // PERFORM ELIMINATION:
    //

    // determine what col needs elimination (starting with the first column)
    // find the associated pivot value 
    // find the multipliers by dividing the values under the pivot value by the pivot value
    // update L with those multipliers
    // modify the L and U matrices accordingly

    // take the values in pivot 1,1 and find each value in this column
    // row 2, col 1: multiplier 'm': where U[1,1] = p and U[2,1] = x ---> m[2,1] = x/p
    // --> now update L so that L[2,1] = x/p
    // repeat for each value in each column underneath a pivot value

    // then update U
    // where U[r,c] := U[r,c] - m[r,1] * U[1,i]

    double pivot = 0;
    int elim_col;
    vector<float> pivots;
    pivots.reserve(rows*cols);
    vector<float> pivots_pos;
    pivots_pos.reserve(rows*cols);


    // THIS IS HOW YOU FIND PIVOTs
    for (int i = 0; i < U.size(); i++){
        if (i%(rows+1) == 0){
            cout << "idx: " << i << "| value: " << U[i] << endl;
        }
    }

    for (int idx = 0; idx < U.size(); idx++){
        cout << idx << "and" << rows+1 << " ====== "<< idx%(rows+1) << endl;

        //most things happen inside this loop
        float mult = 0;
        // if (idx%(rows+1) == 0){
        if ((idx / cols) == (idx % cols)) {
            int pivot_row = idx / cols;
            cout << "piv row: " << pivot_row << endl;

            // OBTAIN MULTIPLIERS
            // this gives me the multipliers for each index... i need to take these and use these in this loop
            // for (int i = 0; i < U.size(); i++){

            //     // where pivot_row * col_size ends, zeros will stop
            //     if (i >= pivot_row+cols and i%(cols) ==0){

            //         // correctly placing the multipliers in sequence
            //         mult = float(U[i])/float(U[idx]);
            //     }
            //     // add the multiplier to its appropriate spot
            //     M[i] = mult;
            // }
            std::fill(M.begin(), M.end(), 0.0f);
            std::fill(K.begin(), K.end(), 0.0f);


            for (int i = 0; i < U.size(); i++){
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
            cout<< "M:" << endl;
            display_vec(M);
            


            //////////////////////////// USE MULTIPLIERS TO CALCULATE K
            // for (int i = 0; i < U.size(); i+=cols){
            //     for (int j = 0; j < cols; j++){
            //         K[i+j] = float(U[j])*float(M[i]);
            //     }
            // }
            int pivot_start = idx - (idx % cols);
            for (int i = pivot_row+1; i < rows; i++) {
                for (int j = 0; j < cols; j++) {
                    // Use the pivot row element from the correct column.
                    printf("%f * %f\n", float(U[pivot_start + j]), float(M[i*cols + (idx % cols)]));
                    K[i*cols+j] = float(U[pivot_start + j]) * float(M[i*cols + (idx % cols)]);
                }
            }
            cout<< "K:" << endl;
            display_vec(K);

            //////////////////////////////////////////// NOW UPDATE U
            for (int i = 0; i< U.size(); i++){
                U[i] -= K[i];
            }
            cout<< "U:" << endl;
            display_vec(U);

            ///////////////////////////////////////////// NOW UPDATE L:
            // for (int i = 1; i < U.size(); i++){
            //     if (i%(idx+rows) == 0){
            //         L[i] = M[i];
            //     }
            // }

            for (int i = 0; i < U.size(); i++){
                int i_row = i / cols;
                int i_col = i % cols;
                // Update L only for rows below the pivot and in the pivot column.
                if (i_row > pivot_row && i_col == (idx % cols)){
                    L[i] = M[i];
                }
            }
            
            // cout<< "L:" << endl;
            // display_vec(L);
            // break;
        }
    }


    cout<< "L:" << endl;
    display_vec(L);

    cout<< "U:" << endl;
    display_vec(U);


    // Find current pivot value. Then add the cols variable to it until its larger than A.size()
    // any value that appears until A.size() that isn't zero results in that being the active column
    // cout << "=====================" << endl;
    // display_vec(pivots_pos);

    // for i in all pivot values. take i and divide by the values under it in that row for matrix U (row,col can get you this quickly)
    // take the resulting values of those U multipliers and fill them in the indices for those multipliers but in L
    // now subtract the appropriate multiple from row 2 so that it achieves identity on the left side of the diagonal
    // 
    // vector <float> pivots;
    // for (int idx = 0; idx < L.size(); idx++){
    //     pivots.push_back(U[idx])
    // }

    return pivots;
}