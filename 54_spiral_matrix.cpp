#include <iostream>
#include <vector>

class Solution {
public:
    std::vector<int> spiralOrder(std::vector<std::vector<int>> &matrix) {
        std::vector<int> spiral;
        if (matrix.empty() || matrix.front().empty())
            return spiral;

        int m = static_cast<int>(matrix.size());
        int n = static_cast<int>(matrix.front().size());

        //从外向里逐圈遍历
      for (int i = 0; i < (m + 1) / 2 && i < (n + 1) / 2; ++i) {
            //上方一横
            for (int j = i; j < n - i; ++j)
                spiral.push_back(matrix[i][j]);
            //右边一竖
            for (int j = i + 1; j < m - i; ++j)
                spiral.push_back(matrix[j][n - i - 1]);
            //下方一横
            if (2 * i + 1 == m) //与上方一横重合
                break;
            for (int j = n - i - 2; j >= i; --j)
                spiral.push_back(matrix[m - 1 - i][j]);
            //左边一竖
            if (2 * i + 1 == n) //与右边一竖重合
                break;
            for (int j = m - i - 2; j > i; --j)
                spiral.push_back(matrix[j][i]);
        }

        return spiral;
    }
};

std::ostream &operator<<(std::ostream &out, const std::vector<int> &vec)
{
    for (int i : vec)
        out << i << " ";
    return out;
}

int main()
{
    //1, 2, 3, 6, 9, 8, 7, 4, 5
    std::vector<std::vector<int>> matrix1 = {
            {1, 2, 3},
            {4, 5, 6},
            {7, 8, 9},
    };
    //1, 2, 3, 4, 8, 12, 11, 10, 9, 5, 6, 7
    std::vector<std::vector<int>> matrix2 = {
            {1, 2, 3, 4},
            {5, 6, 7, 8},
            {9, 10, 11, 12},
    };

    std::vector<int> spiral1 = Solution().spiralOrder(matrix1);
    std::vector<int> spiral2 = Solution().spiralOrder(matrix2);

    std::cout << spiral1 << std::endl;
    std::cout << spiral2 << std::endl;

    return 0;
}
