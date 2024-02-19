#pragma once
#include "Vector.hpp"

template<typename T>
class CSR {
private:
    std::vector<T> values_;
    std::vector<long unsigned int> cols_;
    std::vector<long unsigned int> rows_;

public:
    CSR (const std::vector<T>& values, const std::vector<long unsigned int>& cols,const std::vector<long unsigned int>& rows):
        values_(values), cols_(cols), rows_(rows) {}
    CSR (const std::vector<std::vector<T>>& data){
        long unsigned int amount = 0;
        rows_.push_back(amount);
        for(std::size_t i = 0; i < data.size(); i++){
            for(std::size_t j = 0; j< data[0].size(); j++){
                if (data[i][j] != 0) {
                    values_.push_back(data[i][j]);
                    cols_.push_back(j);
                    amount ++;
                   }
            }
            rows_.push_back(amount);
        }
    }
    CSR (const std::vector<T>& data, size_t height, size_t width){
        long unsigned int amount = 0;
        rows_.push_back(amount);
        for(std::size_t i = 0; i < height; i++){
            for(std::size_t j = 0; j< width; j++){
                if (data[i * width + j] != 0) {
                    values_.push_back(data[i * width + j]);
                    cols_.push_back(j);
                    amount ++;
                   }
            }
            rows_.push_back(amount);
        }
    }

    const std::vector<long unsigned int>& get_cols() const {return cols_;}
    const std::vector<long unsigned int>& get_rows() const {return rows_;}

    std::vector<T> operator*(std::vector<T> &vec){
        std::vector<T> res;
        T item;
        for (std::size_t i = 0; i + 1 < rows_.size(); i++) {
            item = 0;
            for (std::size_t j = rows_[i]; j < rows_[i + 1]; j++) {
                item += values_[j] * vec[cols_[j]];
            }
            res.push_back(item);
        }
        return res;
    }

    template<typename U>
    CSR<T> operator*(U a){
        std::vector<T> res;
        for (std::size_t i = 0; i < values_.size(); i++) {
            res.push_back(values_[i] * a);
        }
        CSR<T> ans(res,cols_,rows_);
        return ans;
    }

    T operator()(unsigned int i, unsigned int j) const{
        for (long unsigned int k = rows_[i]; k < rows_[i + 1]; k++) {
            if (cols_[k] == j) {
                return values_[k];
            }
        }
        return 0;
    }

    void print_CSR(){
        std::cout << "values: ";
        for(std::size_t i = 0; i < values_.size(); i++) std::cout << values_[i] << " ";
        std::cout << std::endl;
        std::cout << "cols: ";
        for(std::size_t i = 0; i < cols_.size(); i++) std::cout << cols_[i] << " ";
        std::cout << std::endl;
        std::cout << "rows: ";
        for(std::size_t i = 0; i < rows_.size(); i++) std::cout << rows_[i] << " ";
        std::cout << std::endl;    
    }

};

template<typename T>
CSR<T> operator+ (CSR<T>& left, CSR<T>& right){
    long unsigned int n = std::max(right.get_rows().size(), left.get_rows().size());
    long unsigned int m = std::max(*std::max_element(left.get_cols().begin(), left.get_cols().end()), *std::max_element(right.get_cols().begin(), right.get_cols().end()));
    std::vector<T> res_values;
    std::vector<long unsigned int> res_cols;
    std::vector<long unsigned int> res_rows;
    long unsigned int amount = 0;
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
    long unsigned int n = std::max(right.get_rows().size(), left.get_rows().size());
    long unsigned int m = std::max(*std::max_element(left.get_cols().begin(), left.get_cols().end()), *std::max_element(right.get_cols().begin(), right.get_cols().end()));
    std::vector<T> res_values;
    std::vector<long unsigned int> res_cols;
    std::vector<long unsigned int> res_rows;
    long unsigned int amount = 0;
    res_rows.push_back(amount);
    for (unsigned int i = 0; i + 1 < n; i ++){
        for (unsigned int j = 0; j <= m; j++){
            if ((right(i,j) - left(i,j))!=0){
                amount++;
                res_values.push_back(left(i,j) - right(i,j));
                res_cols.push_back(j);
            }
        }
    res_rows.push_back(amount);
    }
    return CSR(res_values, res_cols, res_rows);
} 

template<typename T, typename U>
CSR<T> operator*(U a, CSR<T> matrix){
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
