#include "Vector.hpp"
#include "CSR.hpp"
#include "DenseMatrix.hpp"

template <typename T>
void ArnoldiIter(CSR<T> &matrix, DenseMatrix<T> &K,
                      DenseMatrix<T> &Hessenberg, const int i){
    std::vector<T> t = matrix * K.get_col(i);
    T h;
    for (std::size_t k = 0; k <= i; k++){
        h = dot(t, K.get_col(k));
        t = t - h * K.get_col(k);
        Hessenberg.change_elem(k, i) = h;
    }

    h = norm(t);
    Hessenberg.change_elem(i + 1, i) = h;
    t = 1 / h * t;
    K.write_col(t, i + 1);
}

template <typename T>
void GivensRotation(DenseMatrix<T> &Hessenberg, 
                        std::vector<std::pair<double, double>>& rotations, const int i){
    std::cout << "rotations" << std::endl;
    for (std::size_t k = 0; k < i; k++){
        double h = rotations[k].first * Hessenberg(k, i) - rotations[k].second * Hessenberg(k + 1, i);
        double h_n = rotations[k].first * Hessenberg(k+1, i) + rotations[k].second * Hessenberg(k, i);
        Hessenberg.change_elem(k, i) = h;
        Hessenberg.change_elem(k + 1, i) = h_n;
    }

    double cos_phi = Hessenberg(i, i) / std::sqrt(Hessenberg(i, i)* Hessenberg(i, i) + Hessenberg(i + 1, i) * Hessenberg(i+1, i));
    double sin_phi = -Hessenberg(i + 1, i) / std::sqrt(Hessenberg(i, i)* Hessenberg(i, i) + Hessenberg(i + 1, i) * Hessenberg(i+1, i));

    double h  = cos_phi * Hessenberg(i, i) - sin_phi * Hessenberg(i + 1, i);
    double h_n = sin_phi * Hessenberg(i, i) + cos_phi * Hessenberg(i + 1, i);
    std::cout <<"hes: " << h << ' ' << h_n << std::endl;

    Hessenberg.change_elem(i, i) = h;
    Hessenberg.change_elem(i + 1, i) = h_n;

    rotations[i] = (std::make_pair(cos_phi, sin_phi));

    
}





