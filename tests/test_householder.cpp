#include "gtest/gtest.h"
#include "../src/Decomposition/Householder.hpp"
#include "../src/Matrix/DenseMatrix.hpp"

TEST(HOUSEHOLDER, TEST_1) {
    std::vector<std::vector<double>> a{{1, 2, 3}, {4, 5, 6}, {7, 8,9}};
    std::vector<std::vector<double>> q{{-0.123091490979333, 0.904534033733291, 0.40824890463863}, {-0.492365963917331, 0.301511344577764, -0.816496580927726}, {-0.8616404368553292, -0.3015113445777631, 0.4082482904638634}};
    std::vector<std::vector<double>> r{{-8.124038404635959, -9.601136296387955, -11.07823418813995}, {0, 0.9045340337332926,1.809068067466585}, {0,0,0}};
    DenseMatrix matrix(a);
    DenseMatrix Q(q);
    DenseMatrix R(r);
    std::pair<DenseMatrix<double>, DenseMatrix<double>> QR = householder(matrix);
    for(std::size_t i = 0; i < Q.get_height() * Q.get_width(); i++)
        ASSERT_NEAR(QR.first.get_values()[i], Q.get_values()[i], 1e-6);
    for(std::size_t i = 0; i < R.get_height() * R.get_width(); i++)
        ASSERT_NEAR(QR.second.get_values()[i], R.get_values()[i], 1e-6);
}
