#pragma once
#include "Vector.h"

template<typename T>
class CSR {
private:
    std::vector<T> values;
    std::vector<int> cols;
    std::vector<int> rows;

public:
    CSR (const std::vector<T>& values, const std::vector<int>& cols,const std::vector<int>& rows):
        values(values), cols(cols), rows(rows) {}
    CSR (const std::vector<std::vector<T>>& data){
        int amount = 0;
        rows.push_back(amount);
        for(std::size_t i = 0; i < data.size(); i++){
            for(std::size_t j = 0; j< data[0].size(); j++){
                if (data[i][j] != 0) {
                    values.push_back(data[i][j]);
                    cols.push_back(j);
                    amount ++;
                   }
            }
            rows.push_back(amount);
        }
    }
    CSR (const std::vector<T>& data, size_t height, size_t width){
        int amount = 0;
        rows.push_back(amount);
        for(std::size_t i = 0; i < height; i++){
            for(std::size_t j = 0; j< width; j++){
                if (data[i * width + j] != 0) {
                    values.push_back(data[i * width + j]);
                    cols.push_back(j);
                    amount ++;
                   }
            }
            rows.push_back(amount);
        }
    }

    const std::vector<T>& get_cols() const {return cols;}
    const std::vector<T>& get_rows() const {return rows;}

    std::vector<T> operator*(std::vector<T> &vec){
        std::vector<T> res;
        T item;
        for (std::size_t i = 0; i + 1 < rows.size(); i++) {
            item = 0;
            for (std::size_t j = rows[i]; j < rows[i + 1]; j++) {
                item += values[j] * vec[cols[j]];
            }
            res.push_back(item);
        }
        return res;
    }

    CSR<T> operator*(T a){
        std::vector<T> res;
        for (std::size_t i = 0; i < values.size(); i++) {
            res.push_back(values[i] * a);
        }
        CSR<T> ans(res,cols,rows);
        return ans;
    }

    T operator()(unsigned int i, unsigned int j) const{
        for (unsigned int k = rows[i]; k < rows[i + 1]; k++) {
            if (cols[k] == j) {
                return values[k];
            }
        }
        return 0;
    }

    void print_CSR(){
        std::cout << "values: ";
        for(std::size_t i = 0; i < values.size(); i++) std::cout << values[i] << " ";
        std::cout << std::endl;
        std::cout << "cols: ";
        for(std::size_t i = 0; i < cols.size(); i++) std::cout << cols[i] << " ";
        std::cout << std::endl;
        std::cout << "rows: ";
        for(std::size_t i = 0; i < rows.size(); i++) std::cout << rows[i] << " ";
        std::cout << std::endl;    
    }

};

template<typename T>
CSR<T> operator+ (CSR<T>& left, CSR<T>& right){
    unsigned int n = std::max(right.get_rows().size(), left.get_rows().size());
    unsigned int m = std::max(*std::max_element(left.get_cols().begin(), left.get_cols().end()), *std::max_element(right.get_cols().begin(), right.get_cols().end()));
    std::vector<T> res_values;
    std::vector<int> res_cols;
    std::vector<int> res_rows;
    int amount = 0;
    res_rows.push_back(amount);
    for (unsigned int i = 0; i + 1 < n; i ++){
        for (unsigned int j = 0; j <= m; j++){
            if ((right(i,j) + left(i,j))!=0){
                amount++;
                res_values.push_back(right(i,j) + left(i,j));
                res_cols.push_back(j);
            }
        }
    res_rows.push_back(amount);
    }
    return CSR(res_values, res_cols, res_rows);
}


template<typename T>
CSR<T> operator- (CSR<T> left, CSR<T> right){
    unsigned int n = std::max(right.get_rows().size(), left.get_rows().size());
    unsigned int m = std::max(*std::max_element(left.get_cols().begin(), left.get_cols().end()), *std::max_element(right.get_cols().begin(), right.get_cols().end()));
    std::vector<T> res_values;
    std::vector<int> res_cols;
    std::vector<int> res_rows;
    int amount = 0;
    res_rows.push_back(amount);
    for (unsigned int i = 0; i + 1 < n; i ++){
        for (unsigned int j = 0; j <= m; j++){
            if ((right(i,j) - left(i,j))!=0){
                amount++;
                res_values.push_back(right(i,j) - left(i,j));
                res_cols.push_back(j);
            }
        }
    res_rows.push_back(amount);
    }
    return CSR(res_values, res_cols, res_rows);
} 

template<typename T>
CSR<T> operator*(T a, CSR<T> matrix){
    return matrix * a;
}

template<typename T>
std::ostream& operator<<(std::ostream& os, const CSR<T>& csr_matrix){
    for (unsigned int i = 0; i + 1 < (csr_matrix.get_rows()).size(); i ++){
        for (unsigned int j = 0; j <= *std::max_element(csr_matrix.get_cols().begin(), csr_matrix.get_cols().end()); j++) std::cout << csr_matrix(i, j) << ' ';
    std::cout << std::endl;
    }
    return os;
}
