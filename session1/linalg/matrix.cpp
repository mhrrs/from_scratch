#include <iostream>
#include <vector>
#include <array>
#include <tuple>
#include <cmath>
#include "utils.hpp"
#include "matrix.hpp"

using namespace std;

// class for Matrix
// create single vector that holds all data
// create attributes that let you know the columnsxrows info


vector<float> matrix_mult(vector<float> A, vector<float> B){
    // # of cols in A
    int A_col = sqrt(A.size());

    // THIS SHOULD INITIALIZE THE FIRST ROW OF THE IDENTITY MAT [this is technically wrong. i should make the first columnn for LU decomp purposes, this is the first row]
    // vector<float> I;
    // I.reserve(9);
    // for (int i = 0; i < A_col; i++){
    //     for (int j = 0; j < A_col; j++){
    //         if (i == j){
    //             I.push_back(1);
    //         }
    //         else{
    //             I.push_back(0);
    //         }
    //     }
    // }

    // THIS SHOULD INITIALIZE THE FIRST ROW OF THE IDENTITY MAT [this is technically wrong. i should make the first columnn for LU decomp purposes, this is the first row]
    vector<float> y;
    vector<float> Y;
    y.reserve(9);
    Y.reserve(9);
    for (int i = 0; i < int(A.size()); i++){
        y.push_back(0);
        Y.push_back(0);
    }


    int k = 0;
    int count = 0;
    cout << "A_col:" << A_col << endl;
    cout << "A size:" << int(A.size()) << endl;
    cout << "Y size:" << Y.size() << endl;
    for (int i = 0; i<int(A.size()*A_col); i+=A_col){ // for the len of A vector | step == # of cols in A
        for (int j = 0; j<int(A_col); j++){ // for the len of y vector | step == 1
            cout << "k = " << A[i+j] << "*" << Y[j+i] << endl;
            k += int(A[i+j])*int(Y[j]);
        }
        // Y[count] = I[i] - k;
        // cout << "Y[count] = " << I[i] << " - " << k << endl;
        count +=1;
        k = 0;

    }
    

    return Y;
}


vector<float> forward_substitute(vector<float> L){
// # of cols in A
    int L_col = sqrt(L.size());

    // THIS SHOULD INITIALIZE THE FIRST ROW OF THE IDENTITY MAT [this is technically wrong. i should make the first columnn for LU decomp purposes, this is the first row]
    vector<float> y;
    vector<float> Y;
    y.reserve(9);
    Y.reserve(9);
    for (int i = 0; i < L_col; i++){
        y.push_back(0);
        Y.push_back(0);
    }


    int k = 0;
    int count = 0;

    for (int i = 0; i < (L_col*L_col); i+=L_col){ // for the len of A vector | step == # of cols in A

        for (int j = 0; j < int(L_col); j++){ // for the len of y vector | step == 1
            k += int(L[i+j]*Y[j]);
        }
        // Y[count] = I[i] - k;
        // cout << "Y[count] = " << I[i] << " - " << k << endl;
        count +=1;
        k = 0;

    }
    

    return Y;
}