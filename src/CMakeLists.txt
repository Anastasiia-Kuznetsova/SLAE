set(HEADERS
    TridiagonalMatrixSolver/TridiagonalMatrixSolver.h
)

set(SOURCES
    TridiagonalMatrixSolver/TridiagonalMatrixSolver.cpp
)

add_library(TridiagonalMatrixSolver ${HEADERS} ${SOURCES})

target_include_directories(TridiagonalMatrixSolver PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
