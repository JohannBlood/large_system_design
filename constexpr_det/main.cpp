#include <array>
#include <iostream>

template <int N>
constexpr int Det(const std::array<std::array<int, N>, N> &matrix){
    int det = 0;
    for (int k = 0; k != N; ++k){
        std::array<std::array<int, N - 1>, N - 1> sub_matrix{};
        for (int i = 0; i != N - 1; ++i){
            for (int j = 0; j!= k; ++j)
                (&std::get<0>(((&std::get<0>(sub_matrix))[i])))[j] = matrix[i + 1][j];
            for (int j = k; j != N - 1; ++j)
                (&std::get<0>(((&std::get<0>(sub_matrix))[i])))[j] = matrix[i + 1][j + 1];
        }
        if (k % 2)
            det -= matrix[0][k] * Det<N - 1>(sub_matrix);
        else
            det += matrix[0][k] * Det<N - 1>(sub_matrix);
    }
    return det;
}

template <>
constexpr int Det<1>(const std::array<std::array<int, 1>, 1> &matrix){
    return matrix[0][0];
}


int main()
{
    constexpr std::array<std::array<int, 3>, 3> matrix = {{{0, 1, 2},
                                                           {1, 2, 3},
                                                           {2, 3, 7}}};
    constexpr int result = Det<3>(matrix);
    std::cout << result << std::endl;
    return 0;
}