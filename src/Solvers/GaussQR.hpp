#include"../Decomposition/Householder.hpp"
#include<iostream>

template<typename T>
std::vector<double> gauss_qr(const DenseMatrix<T>& A, const std::vector<T>& b){
    std::vector<double> x(b.size());
    std::pair<DenseMatrix<double>, DenseMatrix<double>> QR = householder(A);
    std::vector<double> y = QR.first.transpose() * b;
    double tmp;
    for(std::size_t i = b.size() - 1; i > 0; --i){
        tmp = 0;
        for(std::size_t  j = i + 1; j < b.size(); j++){
            tmp += QR.second(i, j) * x[j];
        }
        x[i] = (y[i] - tmp) / QR.second(i,i);
    }
    tmp = 0;
    for(std::size_t j =  1; j < b.size(); j++){
            tmp += QR.second(0, j) * x[j];
        }
    x[0] = (y[0] - tmp) / QR.second(0,0);
    std::cout << x;
    return x;
}
