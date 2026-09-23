// inverse.hpp
#ifndef MATRIX_HPP_INCLUDED
#define MATRIX_HPP_INCLUDED

#include <iostream>
#include <vector>
#include <array>
#include <tuple>
#include <cmath>


std::vector<float> matrix_mult(std::vector<float> A, std::vector<float> B);

std::vector<float> forward_substitute(std::vector<float> L);

struct vmatrix {
    std::vector<float> vec;
    int rows;
    int cols;
};

#endif