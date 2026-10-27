#include "neuralnet/matrix.hpp"

#include <iostream>

int main() {
    using neuralnet::Matrix;

    const Matrix inputs{
        {1.0, 2.0},
        {3.0, 4.0}
    };

    const Matrix weights{
        {0.5, -1.0},
        {1.5, 2.0}
    };

    const Matrix output = inputs * weights;

    std::cout << "Matrix multiplication result:\n";

    for (std::size_t r = 0; r < output.rows(); ++r) {
        for (std::size_t c = 0; c < output.cols(); ++c) {
            std::cout << output(r, c);

            if (c + 1 == output.cols()) {
                std::cout << '\n';
            } else {
                std::cout << ' ';
            }
        }
    }

    return 0;
}