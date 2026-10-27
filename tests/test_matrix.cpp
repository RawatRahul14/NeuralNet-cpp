#include "neuralnet/matrix.hpp"

#include <gtest/gtest.h>
#include <stdexcept>

using neuralnet::Matrix;

TEST(MatrixTest, CreatesMatrixAndReadsValues) {
    const Matrix matrix{
        {1.0, 2.0},
        {3.0, 4.0}
    };

    EXPECT_EQ(matrix.rows(), 2U);
    EXPECT_EQ(matrix.cols(), 2U);
    EXPECT_DOUBLE_EQ(matrix(0, 1), 2.0);
    EXPECT_DOUBLE_EQ(matrix(1, 0), 3.0);
}

TEST(MatrixTest, RejectsRaggedInitializer) {
    EXPECT_THROW(
        (Matrix{{1.0, 2.0}, {3.0}}),
        std::invalid_argument
    );
}

TEST(MatrixTest, RejectsZeroDimensions) {
    EXPECT_THROW(
        (Matrix(0, 2)),
        std::invalid_argument
    );
}

TEST(MatrixTest, BoundsChecksIndices) {
    const Matrix matrix{
        {1.0, 2.0},
        {3.0, 4.0}
    };

    EXPECT_THROW(matrix(2, 0), std::out_of_range);
    EXPECT_THROW(matrix(0, 2), std::out_of_range);
}

TEST(MatrixTest, AddsMatrices) {
    const Matrix result =
        Matrix{{1.0, 2.0}, {3.0, 4.0}}
        + Matrix{{10.0, 20.0}, {30.0, 40.0}};

    EXPECT_DOUBLE_EQ(result(0, 0), 11.0);
    EXPECT_DOUBLE_EQ(result(1, 1), 44.0);
}

TEST(MatrixTest, SubtractsMatrices) {
    const Matrix result =
        Matrix{{5.0, 7.0}} - Matrix{{2.0, 3.0}};

    EXPECT_DOUBLE_EQ(result(0, 0), 3.0);
    EXPECT_DOUBLE_EQ(result(0, 1), 4.0);
}

TEST(MatrixTest, RejectsAdditionWithDifferentShapes) {
    EXPECT_THROW(
        (Matrix{{1.0, 2.0}} + Matrix{{1.0}, {2.0}}),
        std::invalid_argument
    );
}

TEST(MatrixTest, TransposesMatrix) {
    const Matrix result =
        Matrix{{1.0, 2.0, 3.0}, {4.0, 5.0, 6.0}}
        .transpose();

    EXPECT_EQ(result.rows(), 3U);
    EXPECT_EQ(result.cols(), 2U);
    EXPECT_DOUBLE_EQ(result(0, 1), 4.0);
    EXPECT_DOUBLE_EQ(result(2, 1), 6.0);
}

TEST(MatrixTest, MultipliesCompatibleMatrices) {
    const Matrix result =
        Matrix{{1.0, 2.0, 3.0}, {4.0, 5.0, 6.0}}
        * Matrix{{7.0, 8.0}, {9.0, 10.0}, {11.0, 12.0}};

    EXPECT_EQ(result.rows(), 2U);
    EXPECT_EQ(result.cols(), 2U);

    EXPECT_DOUBLE_EQ(result(0, 0), 58.0);
    EXPECT_DOUBLE_EQ(result(0, 1), 64.0);
    EXPECT_DOUBLE_EQ(result(1, 0), 139.0);
    EXPECT_DOUBLE_EQ(result(1, 1), 154.0);
}

TEST(MatrixTest, RejectsIncompatibleMultiplication) {
    EXPECT_THROW(
        (Matrix{{1.0, 2.0}} * Matrix{{1.0, 2.0}}),
        std::invalid_argument
    );
}