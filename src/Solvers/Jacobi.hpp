#include"../Matrix/CSR.hpp"

template<typename T>
std::vector<double> jacobi( CSR<T>& matrix, const std::vector<T>& b, const std::vector<T>& x_s, long double break_condition){
    std::vector<double> x(x_s.size());
    double tmp = 0;
    double r_cur = 1e8;
    std::vector<double> res(x_s.size()); 
    std::vector<double> x_0(x_s.size()); 
    std::copy(x_s.begin(), x_s.end(), x_0.begin());
    for(; r_cur > break_condition;){
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
         r_cur = std::sqrt(dot(res, res));
    }
    return x_0;
}
