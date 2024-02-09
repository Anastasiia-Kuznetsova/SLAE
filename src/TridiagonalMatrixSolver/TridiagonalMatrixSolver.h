#pragma once
#include <iostream>
#include <vector>
#include <gtest/gtest.h>

#ifndef TRIDIAGONAL_MATRIX_SOLVER_H
#define TRIDIAGONAL_MATRIX_SOLVER_H


class TridiagonalMatrix {
private:
    std::vector<double> a;
    std::vector<double> b;
    std::vector<double> c;
    std::size_t matrix_size;  
public:
    TridiagonalMatrix(const std::vector<double> &a,
                      const std::vector<double> &b,
                      const std::vector<double> &c) : a(a), b(b), c(c), matrix_size(b.size()) {}
    
    
    size_t size() const;
    double operator()(char i, unsigned int j) const;
    friend std::ostream& operator<<(std::ostream& os, const TridiagonalMatrix& matrix);
};

std::vector<double> solve_tridiagonal_matrix(const TridiagonalMatrix& matrix, const std::vector<double>& d);

#endif /* TRIDIAGONAL_MATRIX_SOLVER_H */