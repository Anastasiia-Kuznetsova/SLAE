#include"Matrix/CSR.hpp"

template<typename T>
std::vector<double> gauss_seidel( CSR<T>& matrix, const std::vector<T>& b, std::vector<T> x_0, double break_condition){
    double tmp = 0;
    double r_cur = 1e8;
    std::vector<double> res(x_0.size()); 
    T d = 0;
    for(; r_cur > break_condition;){
        for(std::size_t j = 0; j < x_0.size(); j++){
            tmp = 0;
            for(std::size_t k = matrix.get_rows(j); k < matrix.get_rows(j + 1); k++){
                if(matrix.get_cols(k) != j)
                    tmp += matrix.get_values(k) * x_0[matrix.get_cols(k)];
                else d =  matrix.get_values(k);
            }
            x_0[j] = (b[j] - tmp) / d;
        }
         res = (matrix * x_0) - b;
         r_cur = std::sqrt(dot(res, res));
    }
    return x_0;
}


template<typename T>
std::vector<double> gauss_seidel_iter(CSR<T>& matrix, const std::vector<T>& b, std::vector<T> x_0){
    double tmp = 0;
    T d = 0;
    for(std::size_t i = 0; i < x_0.size(); i++){
        std::size_t j = x_0.size() - 1 - i ;
        tmp = 0;
        for(std::size_t k = matrix.get_rows(j); k < matrix.get_rows(j + 1); k++){
            if(matrix.get_cols(k) != j)
                tmp += matrix.get_values(k) * x_0[matrix.get_cols(k)];
            else d =  matrix.get_values(k);
        }
        x_0[j] = (b[j] - tmp) / d;
    }

    for(std::size_t j = 0; j < x_0.size(); j++){
        tmp = 0;
        for(std::size_t k = matrix.get_rows(j); k < matrix.get_rows(j + 1); k++){
            if(matrix.get_cols(k) != j)
                tmp += matrix.get_values(k) * x_0[matrix.get_cols(k)];
            else d =  matrix.get_values(k);
        }
        x_0[j] = (b[j] - tmp) / d;
    }
    return x_0;
}


template<typename T>
std::vector<double> symmetric_gauss_seidel( CSR<T>& matrix, const std::vector<T>& b, std::vector<T> x_0, double break_condition){
    double r_cur = 1e8;
    std::vector<double> res(x_0.size()); 
    for(; r_cur > break_condition;){
         x_0 = gauss_seidel_iter(matrix, b, x_0);
         res = (matrix * x_0) - b;
         r_cur = std::sqrt(dot(res, res));
    }
    return x_0;
}


template<typename T>
std::vector<double> fast_gauss_seidel( CSR<T>& matrix, const std::vector<T>& b, std::vector<T> y_0, double rho, double break_condition){
    double r_cur = 1e8;
    std::vector<double> res(y_0.size()); 

    double mu_0 = 1, mu_1 = 1 / rho;

    std::vector<double> y_1 = gauss_seidel_iter(matrix, b, y_0);
    res = (matrix * y_1) - b;
    r_cur = std::sqrt(dot(res, res));

    std::vector<T> y(y_0.size());
    for(; r_cur > break_condition;){
        y = 2 * mu_1 / rho * y_1 - mu_0 * y_0;
        mu_0 = 2 / rho * mu_1 - mu_0;
        y /= mu_0;

        y_0 = y_1;
        y_1 = y;

        std::swap(mu_0, mu_1);


        res = (matrix * y) - b;
        r_cur = std::sqrt(dot(res, res));
        std::cout << r_cur << std::endl;

    }

    return y_1;
}