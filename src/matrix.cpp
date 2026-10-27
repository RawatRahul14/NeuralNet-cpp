#include "neuralnet/matrix.hpp"

#include <stdexcept>

namespace neuralnet {

    Matrix::Matrix(
        std::size_t rows,
        std::size_t cols,
        double initial_value
    )
        : rows_(rows),
        cols_(cols),
        data_(rows * cols, initial_value) {

        if (rows == 0 || cols == 0) {
            throw std::invalid_argument(
                "Matrix dimensions must be greater than zero"
            );
        }
    }

    Matrix::Matrix(
        std::initializer_list<std::initializer_list<double>> values
    )
        : rows_(values.size()),
        cols_(values.size() == 0 ? 0 : values.begin()->size()) {

        if (rows_ == 0 || cols_ == 0) {
            throw std::invalid_argument(
                "Matrix must contain at least one row and one column"
            );
        }

        data_.reserve(rows_ * cols_);

        for (const auto& row_values : values) {
            if (row_values.size() != cols_) {
                throw std::invalid_argument(
                    "All matrix rows must have the same number of columns"
                );
            }

            data_.insert(
                data_.end(),
                row_values.begin(),
                row_values.end()
            );
        }
    }

    std::size_t Matrix::rows() const noexcept {
        return rows_;
    }

    std::size_t Matrix::cols() const noexcept {
        return cols_;
    }

    std::size_t Matrix::index(
        std::size_t row,
        std::size_t col
    ) const {
        if (row >= rows_ || col >= cols_) {
            throw std::out_of_range(
                "Matrix index is out of range"
            );
        }

        return row * cols_ + col;
    }

    double& Matrix::operator()(
        std::size_t row,
        std::size_t col
    ) {
        return data_[index(row, col)];
    }

    const double& Matrix::operator()(
        std::size_t row,
        std::size_t col
    ) const {
        return data_[index(row, col)];
    }

    Matrix Matrix::transpose() const {
        Matrix result(cols_, rows_);

        for (std::size_t r = 0; r < rows_; ++r) {
            for (std::size_t c = 0; c < cols_; ++c) {
                result(c, r) = (*this)(r, c);
            }
        }

        return result;
    }

    void Matrix::ensure_same_shape(const Matrix& other) const {
        if (rows_ != other.rows_ || cols_ != other.cols_) {
            throw std::invalid_argument(
                "Matrix dimensions must match for this operation"
            );
        }
    }

    Matrix Matrix::operator+(const Matrix& other) const {
        ensure_same_shape(other);

        Matrix result(rows_, cols_);

        for (std::size_t r = 0; r < rows_; ++r) {
            for (std::size_t c = 0; c < cols_; ++c) {
                result(r, c) = (*this)(r, c) + other(r, c);
            }
        }

        return result;
    }

    Matrix Matrix::operator-(const Matrix& other) const {
        ensure_same_shape(other);

        Matrix result(rows_, cols_);

        for (std::size_t r = 0; r < rows_; ++r) {
            for (std::size_t c = 0; c < cols_; ++c) {
                result(r, c) = (*this)(r, c) - other(r, c);
            }
        }

        return result;
    }

    Matrix Matrix::operator*(const Matrix& other) const {
        if (cols_ != other.rows_) {
            throw std::invalid_argument(
                "Left matrix columns must equal right matrix rows"
            );
        }

        Matrix result(rows_, other.cols_);

        for (std::size_t r = 0; r < rows_; ++r) {
            for (std::size_t k = 0; k < cols_; ++k) {
                const double left_value = (*this)(r, k);

                for (std::size_t c = 0; c < other.cols_; ++c) {
                    result(r, c) +=
                        left_value * other(k, c);
                }
            }
        }

        return result;
    }
} // namespace neuralnet