#pragma once
#include "Vector.hpp"

template <typename T>
class DenseMatrix{
private:
    std::vector<T> matrix_;
    std::size_t height_, width_;   
public:
    DenseMatrix(const std::vector<T>& matrix, const std::size_t height, const std::size_t width):
          matrix_(matrix), height_(height), width_(width){}
    DenseMatrix(const std::vector<std::vector<T>>& data){
          height_ = data.size();
          width_ = data[0].size();
          for(size_t i = 0; i < height_; i++){
            matrix_.insert(matrix_.end(), data[i].begin(), data[i].end());
          }
    }

    size_t get_width() const  {return width_;}
    size_t get_height() const {return height_;}
    const std::vector<T>& get_values() const {return matrix_;}

    std::vector<T> operator*(std::vector<T> &vector) {
        std::vector<T> result(height_, 0);
        for (std::size_t i = 0; i < height_; i++) {
            for (std::size_t j = 0; j < width_; j++) {
                result[i] += matrix_[width_ * i + j] * vector[j];
                }
            }
        return result;
    }

    template<typename U>
    DenseMatrix<T> operator*(U a){
        std::vector<T> res;
        for (std::size_t i = 0; i < matrix_.size(); i++) {
            res.push_back(matrix_[i] * a);
        }
        DenseMatrix<T> ans(res,height_,width_);
        return ans;
    }

    T operator()(long unsigned int i,  long unsigned int j) const{
        return(matrix_[i * width_ + j]);
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

template<typename T, typename U>
DenseMatrix<T> operator*(U a, DenseMatrix<T> matrix){
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