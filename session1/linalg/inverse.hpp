#include <iostream>
#include <vector>
#include <array>

using namespace std;

// FOR TESTING:
//operator overload to display 'x' vector
template <typename any_elem>
ostream& operator<<(ostream& os, vector<any_elem> Vec){
    for(auto v: Vec){
        cout << v << endl;
    }
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
    vector <float> L;
    vector <float> U;

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

    // convert L into Identity of A
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

    // go through each pivot value
    // find the multipliers
    // modify the L and U matrices accordingly
    double pivot;
    vector<float> pivots;
    for (int col = 0; col < cols; col++){
        for (int row = 0; row < rows; row++){
            if (row == col){
                pivots.push_back(A[col][row]);
            } else{
                L.at(row+col) = 9;
            }
        }
    }

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