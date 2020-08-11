#include <iostream>
#include <vector>

class Solution {
public:
    std::vector<std::vector<int>> generateMatrix(int n) {
        std::vector<std::vector<int>> matrix((size_t)n, std::vector<int>(n, 0));
        int curr = 1;
        for (int i = 0; i < (n + 1) / 2; ++i) {
            //上方一横
            for (int j = i; j < n - i; ++j)
                matrix[i][j] = curr++;
            //右方一竖
            for (int j = i + 1; j < n - i; ++j)
                matrix[j][n - 1 - i] = curr++;
            //下方一横
            for (int j = n - 2 - i; j >= i; --j)
                matrix[n - 1 - i][j] = curr++;
            //左方一竖
            for (int j = n - 2 - i; j > i; --j)
                matrix[j][i] = curr++;
        }
        return matrix;
    }
};

std::ostream &operator<<(std::ostream &out, const std::vector<std::vector<int>> &matrix)
{
    for (const auto &row : matrix) {
        for (int i : row)
            out << i << " ";
        out << std::endl;
    }
    return out;
}

int main()
{
    // [ 1, 2, 3 ],
    // [ 8, 9, 4 ],
    // [ 7, 6, 5 ]
    std::cout << Solution().generateMatrix(3) << std::endl;
    std::cout << Solution().generateMatrix(4);

    return 0;
}
