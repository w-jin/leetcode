#include <iostream>
#include <vector>
#include <functional>

/* 时间复杂度为O(mn)，空间复杂度为O(m+n) */
class Solution {
public:
    void setZeroes(std::vector<std::vector<int>> & matrix) {
        if (matrix.empty() || matrix[0].empty())
            return;

        std::vector<bool> row_zeroes(matrix.size(), false); // 记录各行是否为0
        std::vector<bool> col_zeroes(matrix[0].size(), false); // 记录各列是否为0

        for (int i = 0; i < matrix.size(); ++i) {
            for (int j = 0; j < matrix[0].size(); ++j) {
                if (matrix[i][j] == 0) {
                    row_zeroes[i] = true;
                    col_zeroes[j] = true;
                }
            }
        }

        // 行置0
        for (int i = 0; i < matrix.size(); ++i) {
            if (row_zeroes[i]) {
                for (int j = 0; j < matrix[0].size(); ++j)
                    matrix[i][j] = 0;
            }
        }

        // 列置0
        for (int j = 0; j < matrix[0].size(); ++j) {
            if (col_zeroes[j]) {
                for (int i = 0; i < matrix.size(); ++i)
                    matrix[i][j] = 0;
            }
        }
    }
};

/* 采用回溯方法，不再需要保存哪些行列要置0，但由于某些行列重复置0，所以效率比较低 */
class Solution1 {
public:
    void setZeroes(std::vector<std::vector<int>> & matrix) {
        if (matrix.empty() || matrix[0].empty())
            return;

        std::function<void(std::vector<std::vector<int>> &, int)> setZeroesRecursive;
        setZeroesRecursive = [&setZeroesRecursive](std::vector<std::vector<int>> & matrix, int pos) -> void {
            // 跳过非0元素
            while (pos < matrix.size() * matrix[0].size()
                   && matrix[pos / matrix[0].size()][pos % matrix[0].size()] != 0)
                ++pos;
            if (pos == matrix.size() * matrix[0].size())
                return;

            int row = static_cast<int>(pos / matrix[0].size());
            int col = static_cast<int>(pos % matrix[0].size());

            setZeroesRecursive(matrix, pos + 1);

            // 把第row行和第col列置0
            for (int j = 0; j < matrix[0].size(); ++j)
                matrix[row][j] = 0;
            for (int i = 0; i < matrix.size(); ++i)
                matrix[i][col] = 0;
        };

        setZeroesRecursive(matrix, 0);
    }
};

/* 将哪些行和列要置0的信息保存在第一行和第一列中 */
class Solution2 {
public:
    void setZeroes(std::vector<std::vector<int>> & matrix) {
        if (matrix.empty() || matrix[0].empty())
            return;

        // 第一行和第一列是否置0
        bool first_row = false, first_col = false;
        for (int j = 0; j < matrix[0].size(); ++j) {
            if (0 == matrix[0][j]) {
                first_row = true;
                break;
            }
        }
        for (int i = 0; i < matrix.size(); ++i) {
            if (0 == matrix[i][0]) {
                first_col = true;
                break;
            }
        }

        // 其余行列是否置0保存在第一行和第一列中
        for (int i = 1; i < matrix.size(); ++i) {
            for (int j = 1; j < matrix[0].size(); ++j) {
                if (0 == matrix[i][j]) {
                    matrix[0][j] = 0;
                    matrix[i][0] = 0;
                }
            }
        }

        // 先将其余行列需要置0的先置0
        for (int i = 1; i < matrix.size(); ++i) {
            if (0 == matrix[i][0]) {
                for (int j = 1; j < matrix[i].size(); ++j)
                    matrix[i][j] = 0;
            }
        }
        for (int j = 1; j < matrix[0].size(); ++j) {
            if (0 == matrix[0][j]) {
                for (int i = 1; i < matrix.size(); ++i)
                    matrix[i][j] = 0;
            }
        }

        // 将第一行和第一列置0
        if (first_row) {
            for (int j = 0; j < matrix[0].size(); ++j)
                matrix[0][j] = 0;
        }
        if (first_col) {
            for (int i = 0; i < matrix.size(); ++i)
                matrix[i][0] = 0;
        }
    }
};

std::ostream & operator<<(std::ostream & out, const std::vector<std::vector<int>> & matrix) {
    for (const auto & line : matrix) {
        for (int i : line)
            out << i << " ";
        out << std::endl;
    }
    return out;
}

int main() {
    // [1, 0, 1],
    // [0, 0, 0],
    // [1, 0, 1]
    std::vector<std::vector<int>> matrix1 = {
            {1, 1, 1},
            {1, 0, 1},
            {1, 1, 1},
    };

    // [0, 0, 0, 0],
    // [0, 4, 5, 0],
    // [0, 3, 1, 0]
    std::vector<std::vector<int>> matrix2 = {
            {0, 1, 2, 0},
            {3, 4, 5, 2},
            {1, 3, 1, 5}
    };

    Solution2 solution;
    solution.setZeroes(matrix1);
    solution.setZeroes(matrix2);
    std::cout << matrix1 << std::endl;
    std::cout << matrix2 << std::endl;

    return 0;
}
