#include <vector>
#include <iostream>
#include <string>
#include "inverse.hpp"

using namespace std;


int main(){
    //first lets create the A, and y to find 'x'

    // vector<vector<float>> A = {{1,1,1}, {2,2,2}, {3,3,3}};
    // vector<float> y = {1,0,1};

    // //test inverse:
    // vector<float> L = LU_decompisition(A);

    vector<vector<float>> A = {{2,3,1}, {4,7,2}, {6,18,5}};
    vector<float> y = {1,0,1};

    //test inverse:
    vector<float> L = LU_decompisition(A);

    // output results
    // cout << "result: " << endl << L << endl;
    return 0;
}