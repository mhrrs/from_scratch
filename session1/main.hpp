#include <vector>
#include <iostream>
#include <string>

using namespace std;

//operator overload to display 'x' vector
template <typename any_elem>
ostream& operator<<(ostream& os, vector<any_elem> Vec){
    for(v:Vec){
        cout << v << endl;
    }
}


// create transpose function

// create inversion function


//linear regression:
vector<float> linear_regression(vector<vector<float>> A, vector<float> y){
    //
}