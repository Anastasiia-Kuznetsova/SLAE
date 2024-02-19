#pragma once
#include "../Matrix/TridiagonalMatrix.hpp"

template<typename T>
std::vector<T> solve_tridiagonal_matrix(const TridiagonalMatrix<T>& matrix, const std::vector<T>& d){
    size_t n = matrix.size();
    std::vector<T> x(n);
    std::vector<T> p(n);
    std::vector<T> q(n);

    p[1] = -matrix.c(0) / matrix.b(0);
    q[1] = d[0] /  matrix.b(0);
    for (std::size_t i = 1; i + 1  < (n); i++) {
       p[static_cast<size_t>(i+1)] = -matrix.c(i) / (matrix.a(i-1) * p[static_cast<size_t>(i)] + matrix.b(i));
       q[static_cast<size_t>(i+1)]  = (d[static_cast<size_t>(i)] - matrix.a(i - 1) * q[static_cast<size_t>(i)]) / (matrix.a(i - 1) * p[static_cast<size_t>(i)] + matrix.b(i));
    }

    x[static_cast<size_t>(n - 1)]  = (d[static_cast<size_t>(n - 1)] - matrix.a(n - 2) * q[static_cast<size_t>(n-1)]) / (matrix.a(n - 2) * p[static_cast<size_t>(n-1)] + matrix.b(n - 1));
    for(std::size_t i = n - 2; i >= 1; i--){
        x[i] = p[static_cast<size_t>(i+1)] * x[i + 1] + q[static_cast<size_t>(i+1)];
    }
    x[0] = p[1] * x[1] + q[1];

    return x;
}