#include "gtest/gtest.h"
#include "Solvers/Conjugate_Gradient.hpp"



TEST(CG, TEST_1) {
    std::vector<std::vector<double>> a{{10, 16, 4}, {17,150, 30},{3,30,300}};
    CSR mat(a);
    std::vector<double> x{1,1,1};
    std::vector<double> b{1,2,3};
 
    std::vector<double>x_1 = CG(mat, x, b, 1e-15);
    std::vector<double> ans{0.10884014622798267, -0.0062423839592334078, 0.0028691702669768463};
    for (std::size_t i = 0; i < ans.size(); i ++) {
        ASSERT_NEAR(ans[i], x_1[i], 1e-8);
    }
}

