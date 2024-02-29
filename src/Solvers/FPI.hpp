#include"../Matrix/CSR.hpp"

template<typename T>
std::vector<double> FPI(CSR<T>& matrix, const std::vector<T>& b,  const std::vector<T>& x_s, double tau, long double break_condition){
    std::vector<double> x(x_s.size());
    double r_cur = 1e8;
    std::vector<double> res(x_s.size()); 
    std::vector<double> x_0(x_s.size()) ;
    std::copy(x_s.begin(), x_s.end(), x_0.begin());
    for(; r_cur > break_condition;){
        res = (matrix * x_0 - b);
        x = x_0 - tau * res;
        std::copy(x.begin(), x.end(), x_0.begin());

        r_cur = std::sqrt(dot(res, res));
    }
    return x_0;
}



