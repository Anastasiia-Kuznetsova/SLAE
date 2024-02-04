cmake_minimum_required(VERSION 3.20)
project(TridiagonalMatrixSolver)

set(CMAKE_CXX_STANDARD 17)

find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})

add_executable(TridiagonalMatrixSolverTest TridiagonalMatrixSolverTest.cpp)
add_test(NAME TridiagonalMatrixSolverTest COMMAND TridiagonalMatrixSolverTest.cpp)
target_link_libraries(TridiagonalMatrixSolverTest  gtest gtest_main) 