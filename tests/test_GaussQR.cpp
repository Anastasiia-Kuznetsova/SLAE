#include "gtest/gtest.h"
#include "Solvers/GaussQR.hpp"


TEST(GAUSS_QR, TEST_1) {
    std::vector<std::vector<double>> a{{1, 2, 3}, {4, 5, 6}, {7, 8,7}};
    std::vector<double> b{1,2,1};
    DenseMatrix matrix(a);
    std::vector ans = gauss_qr(matrix, b);
    std::cout << ans;
    std::vector<double> ans_{0.66666666666667 , -1.3333333333333333, 1};
    for (std::size_t i = 0; i < ans_.size(); i ++) {
        ASSERT_NEAR(ans[i], ans_[i], 1e-12);
    }
}

