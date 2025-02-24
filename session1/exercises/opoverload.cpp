// Author: Michael Harris
// Exercise: overload an operator to allow you to add characters to create strings

#include <iostream>
#include <vector>
#include <string>
#include <typeinfo>

using namespace std;

ostream& operator<<(ostream& os, vector<char> V){
    string str;
    for (auto v : V){
        str += v;
    }
    cout << str << endl;
}


int main(){
    vector<char> ch = {'h', 'e', 'l', 'l', 'o'};
    cout << ch << endl;
}