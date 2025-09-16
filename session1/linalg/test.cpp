#include <vector>
#include <iostream>
#include <string>
#include "inverse.hpp"
#include "matrix.hpp"
#include "utils.hpp"

using namespace std;


int main(){
    //first lets create the A, and y to find 'x'
    vector<vector<float>> A = {{2,3,1}, {4,7,2}, {6,18,5}};
    vector<float> y = {1,0,1};

    //test LU Decomp:
    auto result = LU_decompisition(A);
    std::vector<float> L = std::get<0>(result);
    std::vector<float> U = std::get<1>(result);

    cout << "==== LU DECOMP MAIN: ====" << endl;
    cout << "L:" << endl;
    display_vec(L);

    cout << "U:" << endl;
    display_vec(U);

    // verify that A = L * U
    auto res = matrix_mult(L, U);
    display_vec(res);

    

    //now lets test finding the inverse:
    


    return 0;
}