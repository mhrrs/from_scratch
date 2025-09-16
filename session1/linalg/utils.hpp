// utils.hpp
#ifndef UTILS_HPP_INCLUDED
#define UTILS_HPP_INCLUDED

#include <iostream>
#include <vector>
#include <array>
#include <tuple>

using namespace std;

//operator overload to display 'x' vector
template <typename T>
ostream& operator<<(ostream& os, const vector<T>& V){
    for(const auto& v:V){
        os << v << endl;
    }
    return os;
}

void display_vec(vector<float> V);

#endif