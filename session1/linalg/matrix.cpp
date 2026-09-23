#include <iostream>
#include <vector>
#include <array>
#include <tuple>
#include <cmath>
#include "utils.hpp"
#include "matrix.hpp"

using namespace std;


vector<float> matrix_mult(vmatrix A, vmatrix B){
    // under dev
    // vector<float> y_hat = forward_substitute(L);
    // return y_hat;

    // ensure A col size matches B row size
    // this is probably redundant, get rid of it
    int a_col = A.cols; int a_row = A.rows;
    int b_col = B.cols; int b_row = B.rows;

    // create vmatrix C 
    std::vector<float> c_vec;
    for (int i =0; i <= A.rows*B.cols;i++){
        c_vec.push_back(0.0);
    }
    vmatrix C = {c_vec, A.rows, B.cols};
    


    // iterate through each item in vec, keep track of col and row item
    // row == cur_row = 
    // col == cur_col

    // do this to find row and col
    
    // really just two loops
    // one that iterates over rows
    // second over columns
    // then just find at which index those two intersect (which should be easy, because
    // its the only index value that the two vecs should share)
    for (int i = 0; i < C.rows; i+=C.rows){
        for (int j = 0; j < C.cols; j+=C.cols){
            
        }
    }
}


// this setup is for finding the inverse
vector<float> forward_substitute(vector<float> L){
    // static cast of sqrt of matrix size
    int n = static_cast<int>(std::sqrt(L.size())); // we do the static_cast to avoid compiler errors

    // lambda function: only valid for size 'n'
    auto index = [n] (int i, int j) {return i*n+j;};

    std::vector<float> Y(n*n, 0.0f);

    for (int k = 0; k < n; k++){
        for (int i = 0; i < n; i++){
            float sum = 0;
            for (int j = 0; j< i; j++){
                sum += L[index(i, j)] * Y[index(j, k)];
                // cout << "A: "<< A[index(i, j)] * Y[index(j, k)] << " :Y" << endl;
            }
            float r = (i == k) ? 1.0f : 0.0f;
            // Y[index(i, k)] = (r-sum)/A[index(i, i)];
            Y[index(i, k)] = (r-sum);
        }
    }
    
    return Y;
}