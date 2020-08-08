#include <iostream>
#include <vector>
#include <algorithm>

class Solution {
public:
    int minPathSum(const std::vector<std::vector<int>> &grid) {
        if (grid.empty() || grid[0].empty())
            return 0;

        const size_t m = grid.size();
        const size_t n = grid[0].size();

        std::vector<int> min_sum(n);

        //计算第一行
        min_sum[0] = grid[0][0];
        for (int j = 1; j < n; ++j)
            min_sum[j] = min_sum[j - 1] + grid[0][j];

        //计算其它行
        for (int i = 1; i < m; ++i) {
            //计算第一列
            min_sum[0] += grid[i][0];
            //计算其余列
            for (int j = 1; j < n; ++j)
                min_sum[j] = std::min(min_sum[j - 1], min_sum[j]) + grid[i][j];
        }

        return min_sum[n - 1];
    }
};

int main() {
    //7
    std::vector<std::vector<int>> grid = {
            {1, 3, 1},
            {1, 5, 1},
            {4, 2, 1},
    };

    Solution solution;
    std::cout << solution.minPathSum(grid) << std::endl;

    return 0;
}
