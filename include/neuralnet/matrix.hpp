#pragma once

#include <cstddef>
#include <initializer_list>
#include <vector>

namespace neuralnet{

    class Matrix {
        public:
        Matrix(
            std::size_t rows,
            std::size_t cols,
            double initial_value = 0.0
        );

        Matrix(
            std::initializer_list<std::initializer_list<double>> values
        );

        [[nodiscard]] std::size_t rows() const noexcept;
        [[nodiscard]] std::size_t cols() const noexcept;

        double& operator()(std::size_t rows, std::size_t cols);

        const double& operator()(
            std::size_t rows,
            std::size_t cols
        ) const;

        [[nodiscard]] Matrix transpose() const;

        [[nodiscard]] Matrix operator+(const Matrix& other) const;
        [[nodiscard]] Matrix operator-(const Matrix& other) const;
        [[nodiscard]] Matrix operator*(const Matrix& other) const;

        private:
        std::size_t rows_;
        std::size_t cols_;
        std::vector<double> data_;

        [[nodiscard]] std::size_t index(
            std::size_t row,
            std::size_t col
        ) const;

        void ensure_same_shape(const Matrix& other) const;
    };
}