#pragma once
#include <iostream>
#include <vector>
#include <gtest/gtest.h>

template <typename T>
class TridiagonalMatrix {
private:
    std::vector<T> a_;
    std::vector<T> b_;
    std::vector<T> c_;
    std::size_t matrix_size;  
public:
    TridiagonalMatrix(const std::vector<T> &a,
                      const std::vector<T> &b,
                      const std::vector<T> &c) : a_(a), b_(b), c_(c), matrix_size(b.size()) {}
    
    
    size_t size() const {return matrix_size;}

    T a(std::size_t i) const{return a_[static_cast<size_t>(i)];}
    T b(std::size_t  i) const{return b_[static_cast<size_t>(i)];}
    T c(std::size_t i) const{return c_[static_cast<size_t>(i)];}

   };

template<typename T>
std::ostream& operator<<(std::ostream& os, const TridiagonalMatrix<T>& matrix) {
    os << matrix.b(0) << ' ' <<  matrix.c(0) << std::endl;
    for (int i = 0; i + 2 < matrix.matrix_size; i++) {
        os << matrix.a(i) << ' ' <<  matrix.b(i + 1) << ' ' <<  matrix.c(i + 1) << std::endl;
    }
    os << matrix.a(matrix.matrix_size - 2) << ' ' <<  matrix.b(matrix.matrix_size - 1) << std::endl;
    return os;
}
