#include <iostream>
#include "CSR.h"
#include "DenseMatrix.h"

int main(){
    std::vector<std::vector<int>> matrixt {{1,2,0, 3, 4},{0, 0,4,0,5}, {0,1,0,11,1}};
    CSR matt(matrixt);
    CSR matt1(matrixt);
    std::vector<int> at = {1,2,3,4, 5};
    std::vector bt = matt*at;
    std::cout << bt;
    std::cout << matt + matt1;
    std::cout << matt * 3;
    std::cout << matt;
    std::cout << "-----" << std::endl;
    std::vector<int> a = {1,2,3,4,5,6,7,8,9};
    std::vector<int> b = {5,4,3,1,8,9,1,2,3};
    std::vector<std::vector<int>> matrix {{1,2,0, 3, 4},{0, 0,4,0,5}, {0,1,0,11,1}};
    

    DenseMatrix mat1(a,3,3);
    DenseMatrix mat2(b,3,3);
    std::cout << mat1 + mat2;
    std::cout << mat1;
    std::vector<int> c = {1,2,3,4,5};
    std::vector<int> d = {1,2,3,4,5};
    std::cout << c + d;
    c+=d;
    std::cout << c;
    std::cout << c-d;
    c-=d;
    std::cout << c;
    std::cout<< c * 3;
    c *=3;
    std::cout << c;

    DenseMatrix mat3(matrix);
    std::cout << mat3 * c;

    std::cout << mat3 * 3;
    std::cout << 3 * mat3;

    
}