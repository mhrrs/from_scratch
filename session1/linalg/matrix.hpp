#include <iostream>
#include <vector>
#include <array>
#include <tuple>

using namespace std;

// class for Matrix
// create single vector that holds all data
// create attributes that let you know the columnsxrows info


vector<float> matrix_mult(vector<float> A, vector<float> B){
    const int A_c = 3;
    const int A_r = 3;

    const int B_c = 3;
    const int B_r = 3;

    const int res_size = A_r*B_c; // # of rows * # of cols
    vector<float> result;

    // THIS SHOULD INITIALIZE THE FIRST ROW OF THE IDENTITY MAT [this is technically wrong. i should make the first columnn for LU decomp purposes, this is the first row]
    vector<float> I;
    vector<float> Y;
    I.reserve(3);
    Y.reserve(3);
    for (int i = 0; i < 3; i++){
        if (i == 0){
            I.push_back(1);
        }
        else{
            I.push_back(0);
        }
    }

    // THIS SHOULD INITIALIZE THE FIRST ROW OF THE IDENTITY MAT [this is technically wrong. i should make the first columnn for LU decomp purposes, this is the first row]
    vector<float> y;
    y.reserve(3);
    for (int i = 0; i < 3; i++){
        y.push_back(0);
        Y.push_back(0);
    }


    vector<float> A_rows;
    for (int k=0; k<A_r; k+=1){
        for (int i=0+k; i<A.size(); i+=A_r){
            // cout << "A[i]: " << A[i] << endl;
            A_rows.push_back(A[i]);
        }
    }


    cout<< "====================" << endl;
    vector<float> B_cols;
    for (int k=0; k<B_c; k+=1){
        for (int i=0+k; i<B.size(); i+=B_c){
            // cout << "B[i]: " << B[i] << endl;
            B_cols.push_back(B[i]);
        }
    }

    // now that you have the row and col info in order, walk through and compute
    for (int i = 0; i <= A_r*B_c; i+=3){
        cout<< "i: " << i << endl;
        result.push_back((A_rows[i]*B_cols[i])+(A_rows[i+1]*B_cols[i+1])+(A_rows[i+2]*B_cols[i+2]));
    }


    // solve for y[1,1]
    // NOTE: rows is PURPOSELY 1 for testing
    int rows = 1;
    for (int i = 0; i < rows; i++){
        for (int j = 0; j < A_c; j++) {
            y[j] += I[i+j] * A[i+j];
            cout << "y[j]: " << y[j] << endl;
        }
    }

    



    return y;
}