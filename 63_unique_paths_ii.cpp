#include <iostream>
#include <vector>

/* 动态规划：paths[i][j]=paths[i-1][j]+paths[i][j-1]，有障碍的地方直接置0 */
class Solution {
public:
    int uniquePathsWithObstacles(const std::vector<std::vector<int>> &obstacleGrid) {
        if (obstacleGrid.empty() || obstacleGrid[0].empty())
            return 0;

        const size_t m = obstacleGrid.size();
        const size_t n = obstacleGrid[0].size();
        std::vector<long> paths(n, 0);

        //填第一行
        for (int j = 0; j < n; ++j) {
            if (obstacleGrid[0][j])
                break;
            paths[j] = 1;
        }
        //填剩余的行
        for (int i = 1; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                if (obstacleGrid[i][j] == 1)
                    paths[j] = 0;
                else {
                    if (j == 0)
                        continue;
                    paths[j] = paths[j] + paths[j - 1];
                }
            }
        }
        //计算过程中可能出现比INT_MAX大的值，但结果不会
        return static_cast<int>(paths[n - 1]);
    }
};

int main() {
    //2
    std::vector<std::vector<int>> obstacleGrid = {
            {0, 0, 0},
            {0, 1, 0},
            {0, 0, 0},
    };

    Solution solution;
    std::cout << solution.uniquePathsWithObstacles(obstacleGrid) << std::endl;

    return 0;
}
