#include <iostream>
#include <vector>
#include <array>
#include <tuple>
#include <cmath>
#include "utils.hpp"
#include "matrix.hpp"

using namespace std;


vector<float> matrix_mult(vector<float> L, vector<float> B){
    // under dev
    vector<float> y_hat = forward_substitute(L);
    return y_hat;
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