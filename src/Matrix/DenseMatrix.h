#pragma once
#include "Vector.h"

template <typename T>
class DenseMatrix{
private:
    std::vector<T> matrix;
    std::size_t height, width;   
public:
    DenseMatrix(const std::vector<T>& matrix, const std::size_t height, const std::size_t width):
          matrix(matrix), height(height), width(width){}
    DenseMatrix(const std::vector<std::vector<T>>& data){
          height = data.size();
          width = data[0].size();
          for(size_t i = 0; i < height; i++){
            matrix.insert(matrix.end(), data[i].begin(), data[i].end());
          }
    }

    const size_t get_width() const  {return width;}
    const size_t get_height() const {return height;}
    const std::vector<T>& get_values() const {return matrix;}

    std::vector<T> operator*(std::vector<T> &vector) {
        std::vector<T> result(height, 0);
        for (std::size_t i = 0; i < height; i++) {
            for (std::size_t j = 0; j < width; j++) {
                result[i] += matrix[width * i + j] * vector[j];
                }
            }
        return result;
    }

    DenseMatrix<T> operator*(T a){
        std::vector<T> res;
        for (std::size_t i = 0; i < matrix.size(); i++) {
            res.push_back(matrix[i] * a);
        }
        DenseMatrix<T> ans(res,height,width);
        return ans;
    }

    T operator()(unsigned int i, unsigned int j) const{
        return(matrix[i * width + j]);
    }
    
};

template <typename T>
DenseMatrix<T> operator+(DenseMatrix<T> & left, DenseMatrix<T> & right){
    std::vector<T> res;
    for (std::size_t i = 0; i < left.get_height(); i ++){
        for (std::size_t j = 0; j < left.get_width(); j ++){
                res.push_back(left(i,j) + right(i, j));
        }
    }
    DenseMatrix<T> ans(res, left.get_height(), left.get_width());
    return ans; 
}

template <typename T>
DenseMatrix<T> operator-(DenseMatrix<T> & left, DenseMatrix<T> & right){
    std::vector<T> res;
    for (std::size_t i = 0; i < left.get_height(); i ++){
        for (std::size_t j = 0; j < left.get_width(); j ++){
                res.push_back(left(i,j) - right(i, j));
        }
    }
    DenseMatrix<T> ans(res, left.get_height(), left.get_width());
    return ans; 
}

template<typename T>
DenseMatrix<T> operator*(T a, DenseMatrix<T> matrix){
    return matrix * a;
}

template <typename T>   
std::ostream& operator<<(std::ostream& os, const DenseMatrix<T>& dense_matrix){
    for (size_t i = 0; i < dense_matrix.get_height(); i++) {
        for(size_t j = 0; j < dense_matrix.get_width(); j++) os << dense_matrix(i,j) << " ";
        std::cout << std::endl;
    }
    return os;
}