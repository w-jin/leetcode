#include <iostream>
#include <vector>
#include <algorithm>

class Solution {
public:
    void rotate(std::vector<std::vector<int>> &matrix) {
        //先转置
        const int n = static_cast<const int>(matrix.size());
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < i; ++j)
                std::swap(matrix[i][j], matrix[j][i]);
        }
        //再左右翻转
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n / 2; ++j)
                std::swap(matrix[i][j], matrix[i][n - 1 - j]);
        }
    }
};

std::ostream &operator<<(std::ostream &out, const std::vector<std::vector<int>> &matrix)
{
    for (const auto &v : matrix) {
        for (int i : v)
            out << i << " ";
        out << std::endl;
    }
    return out;
}

int main()
{
    // 7, 4, 1
    // 8, 5, 2
    // 9, 6, 3
    std::vector<std::vector<int>> matrix1 = {
            {1, 2, 3},
            {4, 5, 6},
            {7, 8, 9},
    };

    // 15, 13,  2,  5
    // 14,  3,  4,  1
    // 12,  6,  8,  9
    // 16,  7, 10, 11
    std::vector<std::vector<int>> matrix2 = {
            { 5,  1,  9, 11},
            { 2,  4,  8, 10},
            {13,  3,  6,  7},
            {15, 14, 12, 16},
    };

    Solution solution;
    solution.rotate(matrix1);
    solution.rotate(matrix2);

    std::cout << matrix1 << std::endl;
    std::cout << matrix2 << std::endl;

    return 0;
}
