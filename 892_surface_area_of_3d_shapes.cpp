#include <iostream>
#include <vector>
#include <algorithm>

using std::cout;
using std::endl;
using std::vector;

/*
    任意形状的网格
*/
class Solution {
public:
    int surfaceArea(vector<vector<int>> &grid) {
        if (grid.empty())
            return 0;

        int area = 0;

        // 第一行，每个立方体只考虑和左边重叠的部分
        if (!grid[0].empty()) {
            if (grid[0][0] != 0)
                area += grid[0][0] * 4 + 2;
            for (int j = 1; j < grid[0].size(); ++j) {
                if (grid[0][j] != 0)
                    area += grid[0][j] * 4 + 2 -
                            2 * std::min(grid[0][j], grid[0][j - 1]);
            }
        }

        // 其它行，每个立方体需要考虑和左边及上行重叠的部分
        for (int i = 1; i < grid.size(); ++i) {
            if (!grid[0].empty()) {
                if (grid[i][0] != 0)
                    area += grid[i][0] * 4 + 2;
                if (!grid[i - 1].empty())  // 上一行要有这个立方体，否则可能越界
                    area -= 2 * std::min(grid[i][0], grid[i - 1][0]);
                for (int j = 1; j < grid[i].size(); ++j) {
                    if (grid[i][j] != 0)
                        area += grid[i][j] * 4 + 2 -
                                2 * std::min(grid[i][j], grid[i][j - 1]);
                    if (j < grid[i - 1].size())
                        area -= 2 * std::min(grid[i][j], grid[i - 1][j]);
                }
            }
        }

        return area;
    }
};

/*
    N * N的方形网格
*/
class Solution1 {
public:
    int surfaceArea(vector<vector<int>> &grid) {
        if (grid.empty())
            return 0;

        const int N = static_cast<int>(grid.size());
        int area = 0;

        // 第一行，每个立方体只考虑和左边重叠的部分
        if (grid[0][0] != 0)
            area += grid[0][0] * 4 + 2;
        for (int j = 1; j < N; ++j) {
            if (grid[0][j] != 0)
                area += grid[0][j] * 4 + 2
                        - 2 * std::min(grid[0][j], grid[0][j - 1]);
        }

        // 其它行，每个立方体需要考虑和左边及上行重叠的部分
        for (int i = 1; i < N; ++i) {
            if (grid[i][0] != 0)
                area += grid[i][0] * 4 + 2
                        - 2 * std::min(grid[i][0], grid[i - 1][0]);
            for (int j = 1; j < N; ++j) {
                if (grid[i][j] != 0)
                    area += grid[i][j] * 4 + 2
                            - 2 * std::min(grid[i][j], grid[i][j - 1])
                            - 2 * std::min(grid[i][j], grid[i - 1][j]);
            }
        }

        return area;
    }
};

/*
    N * N的方形网格，计算每个立方体对总面积的贡献量累加起来
*/
class Solution2 {
public:
    int surfaceArea(vector<vector<int>> &grid) {
        if (grid.empty())
            return 0;

        const int N = static_cast<int>(grid.size());
        int area = 0;

        for (int i = 0; i < N; ++i) {
            for (int j = 0; j < N; ++j) {
                if (grid[i][j] > 0) {
                    // 上下两面
                    area += 2;

                    // 左边
                    int overlap = 0;
                    if (j > 0)
                        overlap = std::min(grid[i][j - 1], grid[i][j]);
                    area += grid[i][j] - overlap;

                    // 右边
                    overlap = 0;
                    if (j < N - 1)
                        overlap = std::min(grid[i][j + 1], grid[i][j]);
                    area += grid[i][j] - overlap;

                    // 上一行
                    overlap = 0;
                    if (i > 0)
                        overlap = std::min(grid[i - 1][j], grid[i][j]);
                    area += grid[i][j] - overlap;

                    // 下一行
                    overlap = 0;
                    if (i < N - 1)
                        overlap = std::min(grid[i + 1][j], grid[i][j]);
                    area += grid[i][j] - overlap;
                }
            }
        }

        return area;
    }
};

int main() {
    // 10
    vector<vector<int>> grid1 = {{2}};

    // 34
    vector<vector<int>> grid2 = {{1, 2},
                                 {3, 4}};

    // 74
    vector<vector<int>> grid3 = {{5, 3, 0},
                                 {3, 3, 5},
                                 {2, 1, 5}};

    Solution1 solution;
    cout << solution.surfaceArea(grid1) << endl;
    cout << solution.surfaceArea(grid2) << endl;
    cout << solution.surfaceArea(grid3) << endl;

    return 0;
}
