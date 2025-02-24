#include <stdlib.h>
#include <iostream>
#include "linear.hpp"

using namespace std;


template <typename ele_type>
ostream& operator<<(ostream& os, vector<ele_type>& V){
    for(auto i: V){
        os << i << ' ';
    }
    return os;
}


int main(){
    vector<vector<float>> A = {{1,1,1}, {2,2,2}, {3,3,3}};
    vector<float> x = {1,0,1};

    vector<float> res = matrix_mult(A, x);

    // output results
    cout << "result: " << res << endl;
    return 0;
}