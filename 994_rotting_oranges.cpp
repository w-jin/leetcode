#include <iostream>
#include <vector>
#include <queue>
#include <utility>

using std::cout;
using std::endl;
using std::vector;
using std::pair;

class Solution {
public:
    int orangesRotting(vector<vector<int>> &grid) {
        if (grid.empty() || grid[0].empty())
            return 0;

        const int M = static_cast<int>(grid.size());
        const int N = static_cast<int>(grid[0].size());

        std::queue<pair<int, int>> q;

        // 将所有腐烂的橘子作为出发点
        int ones_count = 0;
        for (int i = 0; i < M; ++i) {
            for (int j = 0; j < N; ++j) {
                if (2 == grid[i][j])
                    q.emplace(i, j);
                else if (1 == grid[i][j])
                    ++ones_count;
            }
        }
        if (!ones_count)  // 如果一个好的橘子都没有，则0分钟就可以了
            return 0;

        // 从腐烂的橘子出发逐层感染周围的橘子
        int minutes = 0;
        while (!q.empty()) {
            int size = q.size();
            for (int i = 0; i < size; ++i) {
                auto p = q.front();
                q.pop();

                // 上
                if (p.first > 0 && 1 == grid[p.first - 1][p.second]) {
                    grid[p.first - 1][p.second] = 2;
                    q.emplace(p.first - 1, p.second);
                    --ones_count;
                }

                // 下
                if (p.first < M - 1 && 1 == grid[p.first + 1][p.second]) {
                    grid[p.first + 1][p.second] = 2;
                    q.emplace(p.first + 1, p.second);
                    --ones_count;
                }

                // 左
                if (p.second > 0 && 1 == grid[p.first][p.second - 1]) {
                    grid[p.first][p.second - 1] = 2;
                    q.emplace(p.first, p.second - 1);
                    --ones_count;
                }

                // 右
                if (p.second < N - 1 && 1 == grid[p.first][p.second + 1]) {
                    grid[p.first][p.second + 1] = 2;
                    q.emplace(p.first, p.second + 1);
                    --ones_count;
                }
            }

            //  ones_count -= size;  // 不能这样写，会把烂橘子的数量也减掉
            ++minutes;
        }

        return ones_count > 0 ? -1 : minutes - 1;
    }
};

int main() {
    // 4
    vector<vector<int>> grid1 = {
            {2, 1, 1},
            {1, 1, 0},
            {0, 1, 1}
    };

    // -1
    vector<vector<int>> grid2 = {
            {2, 1, 1},
            {0, 1, 1},
            {1, 0, 1}
    };

    // 0
    vector<vector<int>> grid3 = {
            {0, 2}
    };

    // 0
    vector<vector<int>> grid4 = {
            {0}
    };

    Solution solution;
    cout << solution.orangesRotting(grid1) << endl;
    cout << solution.orangesRotting(grid2) << endl;
    cout << solution.orangesRotting(grid3) << endl;
    cout << solution.orangesRotting(grid4) << endl;

    return 0;
}
