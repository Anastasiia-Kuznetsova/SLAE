#include"../src/Matrix/CSR.hpp"
#include <vector>
#include <chrono>
#include <iostream>
#include <random>
#include <fstream>


template<typename T>
std::vector<double> gauss_seidel( CSR<T>& matrix, const std::vector<T>& b, const std::vector<T>& x_s, long double break_condition){
    std::ofstream file;
    file.open ("Gauss_Seidel.csv");
    double tmp = 0;
    double r_cur = 1e8;
    int k = 1;
    std::vector<double> res(x_s.size()); 
    std::vector<double> x_0(x_s.size()) ;
    std::copy(x_s.begin(), x_s.end(), x_0.begin());
    for(; r_cur > break_condition;){
        for(std::size_t j = 0; j < x_0.size(); j++){
            tmp = 0;
            for(std::size_t k = matrix.get_rows()[j]; k < matrix.get_rows()[j+1]; k++){
                if(matrix.get_cols()[k] != j){
                    tmp += matrix.get_values()[k] * x_0[matrix.get_cols()[k]];
                }
            }
            x_0[j] = (b[j] - tmp) / matrix(j,j);
        }

         res = (matrix * x_0) - b;
         r_cur = dot(res, res);
         file << k << ", ";
         k++;
         file << r_cur  << std::endl;
    }
    file.close();
    return x_0;
}


template<typename T>
std::vector<double> jacobi( CSR<T>& matrix, const std::vector<T>& b, const std::vector<T>& x_s, long double break_condition){
    std::ofstream file;
    file.open ("Jacobi.csv");
    std::vector<double> x(x_s.size());
    double tmp = 0;
    double r_cur = 1e8;
    int k = 1;
    std::vector<double> res(x_s.size());
    std::vector<double> x_0(x_s.size()) ;
    std::copy(x_s.begin(), x_s.end(), x_0.begin()); 
    for(; r_cur  > break_condition;){
        for(std::size_t j = 0; j < x_0.size(); j++){
            tmp = 0;
            for(std::size_t k = matrix.get_rows()[j]; k < matrix.get_rows()[j+1]; k++){
                if(matrix.get_cols()[k] != j)
                    tmp += matrix.get_values()[k] * x_0[matrix.get_cols()[k]];
              }
            x[j] = (b[j] - tmp) / matrix(j,j);
        }
         std::copy(x.begin(), x.end(), x_0.begin());
         res = (matrix * x) - b;
         r_cur = dot(res, res);
         file << k << ", ";
         k++;
         file << r_cur  << std::endl;
    }
    return x_0;
}



template<typename T>
std::vector<double> FPI(CSR<T>& matrix, const std::vector<T>& b,  const std::vector<T>& x_s, double tau, long double break_condition){
    std::ofstream file;
    file.open ("FPI.csv");
    std::vector<double> x(x_s.size());
    double r_cur = 1e8;
    int k = 0;
    std::vector<double> res(x_s.size()); 
    std::vector<double> x_0(x_s.size()) ;
    std::copy(x_s.begin(), x_s.end(), x_0.begin());
    for(; r_cur > break_condition;){
        res = (matrix * x_0 - b);
        x = x_0 - tau * res;
        std::copy(x.begin(), x.end(), x_0.begin());

        r_cur = dot(res, res);
        file << k << ", ";
        k++;
        file << r_cur  << std::endl;
    }
    return x_0;
}

int main(){
    std::vector<std::vector<double>> a{{10, 2,3,1,1}, {9,20, 1,6,1},{9,7,30,2,3}, {3,4,10,40,12}, {1,3,6,2,50}};
    CSR mat(a);
    std::vector<double> x{1,1,1,1,1};
    std::vector<double> b{4,2,2,3,8};
    std::vector<double>x_1 = gauss_seidel(mat,b, x, 1e-15);
    std::vector<double>x_2 = FPI(mat,b, x, 0.018, 1e-15);
    std::vector<double>x_3 = jacobi(mat,b, x, 1e-15);



    return 0;
}
