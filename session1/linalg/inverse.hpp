// inverse.hpp
#ifndef INVERSE_HPP_INCLUDED
#define INVERSE_HPP_INCLUDED

#include <iostream>
#include <vector>
#include <array>
#include <tuple>
using namespace std;

// vector<vector <float>> inverse_mat(vector<vector <float>> Mat);

std::tuple<std::vector<float>, std::vector<float>> LU_decompisition(vector<vector <float>> A);


#endif