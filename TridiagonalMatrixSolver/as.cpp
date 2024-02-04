#include <iostream>
#include <vector>

class TridiagonalMatrix {
private:
    std::vector<double> a;
    std::vector<double> b;
    std::vector<double> c;
    std::size_t matrix_size;

    
public:
    TridiagonalMatrix(const std::vector<double> &a,
                      const std::vector<double> &b,
                      const std::vector<double> &c) : a(a), b(b), c(c), matrix_size(b.size()) {}
    
    size_t size() const{
        return matrix_size;
    }

    double operator()(char i, unsigned int j) const{
        switch(i) {
            case 'a':
                if (matrix_size <= ((unsigned int)j + 1)) throw std::out_of_range{"a index out of range"};
                return a[j];
            case 'b':
                if (matrix_size <= ((unsigned int)j)) throw std::out_of_range{"b index out of range"};
                return b[j];
            case 'c':
                return c[j];
            default:
                if (matrix_size <= ((unsigned int)j + 1)) throw std::out_of_range{"c index out of range"};
                throw std::invalid_argument("Value does not match");
        }   
    }

    friend std::ostream& operator<<(std::ostream& os, const TridiagonalMatrix& matrix) {
        os << matrix.b[0] << ' ' <<  matrix.c[0] << std::endl;
        for (size_t i = 0; i + 2 < matrix.matrix_size; i++) {
            os << matrix.a[i] << ' ' <<  matrix.b[i + 1] << ' ' <<  matrix.c[i + 1] << std::endl;
        }
        os << matrix.a[matrix.matrix_size - 2] << ' ' <<  matrix.b[matrix.matrix_size - 1] << std::endl;
        return os;
    }
};

std::vector<double> solve_tridiagonal_matrix(const TridiagonalMatrix& matrix, const std::vector<double>& d){
    size_t n = matrix.size();
    std::vector<double> x(n);
    std::vector<double> p(n);
    std::vector<double> q(n);

    p[1] = -matrix('c', 0u) / matrix('b', 0u);
    q[1] = d[0] /  matrix('b', 0u);
    for (size_t i = 1; i + 1  < n; i++) {
       p[i + 1] = -matrix('c', i) / (matrix('a', i - 1) * p[i] + matrix('b', i));
       q[i + 1]  = (d[i] - matrix('a', i - 1) * q[i]) / (matrix('a', i - 1) * p[i] + matrix('b', i));
    }

    x[n - 1]  = (d[n - 1] - matrix('a', n - 2) * q[n - 1]) / (matrix('a', n - 2) * p[n - 1] + matrix('b', n - 1));
    for(int i = n - 2; i >= 0; i--){
        x[i] = p[i + 1] * x[i + 1] + q[i + 1];
    }

    return x;
}



int main(){
    std::vector<double> vect1{0.1,0.2};
    std::vector<double> vect2{0.5,2.1,2.2};
    std::vector<double> vect3{1.5,1.1};
    std::vector<double> d{1.1,1.2,1.3};
    TridiagonalMatrix matrix(vect1, vect2, vect3);
    std::vector<double> x = solve_tridiagonal_matrix(matrix, d);
    for(unsigned int i = 0; i < matrix.size(); i++){
        std::cout << x[i] << std::endl;
    }

    return 0;
}