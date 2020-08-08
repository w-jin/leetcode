#include <iostream>
#include <vector>
#include <stack>
#include <queue>
#include <algorithm>
#include <utility>

using std::cout;
using std::endl;
using std::vector;
using std::stack;
using std::queue;
using std::pair;

/*
    从每个1开始进行深度优先遍历，将所有找到的1置为0。
    每个点最多遍历两次，时间复杂度为O(m * N)；没有使用额外的数组，但有递归且最大递归层数为最大
    岛屿面积，所以空间复杂度O(max_area)。
 */
class Solution {
public:
    int maxAreaOfIsland(vector<vector<int>> &grid) {
        if (grid.empty() || grid[0].empty())
            return 0;

        this->M = static_cast<int>(grid.size());
        this->N = static_cast<int>(grid[0].size());

        int max_area = 0;
        for (int i = 0; i < M; ++i) {
            for (int j = 0; j < N; ++j) {
                if (grid[i][j] == 0)
                    continue;
                max_area = std::max(max_area, dfs(grid, i, j));
            }
        }

        return max_area;
    }

private:
    int dfs(vector<vector<int>> &grid, int i, int j) {
        int area = 1;
        grid[i][j] = 0;  // 已计算

        // 上边
        if (i > 0 && grid[i - 1][j] == 1)
            area += dfs(grid, i - 1, j);

        // 下边
        if (i < M - 1 && grid[i + 1][j] == 1)
            area += dfs(grid, i + 1, j);

        // 左边
        if (j > 0 && grid[i][j - 1] == 1)
            area += dfs(grid, i, j - 1);

        // 右边
        if (j < N - 1 && grid[i][j + 1] == 1)
            area += dfs(grid, i, j + 1);

        return area;
    }

    int M = 0;  // 行数
    int N = 0;  // 列数
};

/*
    循环版本的深度优先遍历。
*/
class Solution1 {
public:
    int maxAreaOfIsland(vector<vector<int>> &grid) {
        if (grid.empty() || grid[0].empty())
            return 0;

        const int M = static_cast<int>(grid.size());
        const int N = static_cast<int>(grid[0].size());

        int max_area = 0;
        for (int i = 0; i < M; ++i) {
            for (int j = 0; j < N; ++j) {
                if (0 == grid[i][j])
                    continue;

                int area = 0;
                stack<pair<int, int>> s;
                s.emplace(i, j);

                while (!s.empty()) {
                    int row = s.top().first;
                    int col = s.top().second;
                    s.pop();

                    // 有可能在入栈之后经其它路径访问
                    if (0 == grid[row][col])
                        continue;

                    ++area;
                    grid[row][col] = 0;

                    // 左边
                    if (col > 0 && grid[row][col - 1] == 1)
                        s.emplace(row, col - 1);

                    // 上边
                    if (row > 0 && grid[row - 1][col] == 1)
                        s.emplace(row - 1, col);

                    // 右边
                    if (col < N - 1 && grid[row][col + 1] == 1)
                        s.emplace(row, col + 1);

                    // 下边
                    if (row < M - 1 && grid[row + 1][col] == 1)
                        s.emplace(row + 1, col);
                }

                max_area = std::max(max_area, area);
            }
        }

        return max_area;
    }
};

/*
    广度优先遍历版本
*/
class Solution2 {
public:
    int maxAreaOfIsland(vector<vector<int>> &grid) {
        if (grid.empty() || grid[0].empty())
            return 0;

        const int M = static_cast<int>(grid.size());
        const int N = static_cast<int>(grid[0].size());

        int max_area = 0;
        for (int i = 0; i < M; ++i) {
            for (int j = 0; j < N; ++j) {
                if (0 == grid[i][j])
                    continue;

                int area = 0;
                queue<pair<int, int>> q;
                q.emplace(i, j);

                while (!q.empty()) {
                    int row = q.front().first;
                    int col = q.front().second;
                    q.pop();

                    // 有可能在入栈之后经其它路径访问
                    if (0 == grid[row][col])
                        continue;

                    ++area;
                    grid[row][col] = 0;

                    // 左边
                    if (col > 0 && grid[row][col - 1] == 1)
                        q.emplace(row, col - 1);

                    // 上边
                    if (row > 0 && grid[row - 1][col] == 1)
                        q.emplace(row - 1, col);

                    // 右边
                    if (col < N - 1 && grid[row][col + 1] == 1)
                        q.emplace(row, col + 1);

                    // 下边
                    if (row < M - 1 && grid[row + 1][col] == 1)
                        q.emplace(row + 1, col);
                }

                max_area = std::max(max_area, area);
            }
        }

        return max_area;
    }
};

int main() {
    // 6
    vector<vector<int>> grid1 = {
            {0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0},
            {0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0},
            {0, 1, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0},
            {0, 1, 0, 0, 1, 1, 0, 0, 1, 0, 1, 0, 0},
            {0, 1, 0, 0, 1, 1, 0, 0, 1, 1, 1, 0, 0},
            {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0},
            {0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0},
            {0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0}
    };

    // 0
    vector<vector<int>> grid2 = {
            {0, 0, 0, 0, 0, 0, 0, 0}
    };

    Solution1 solution;
    cout << solution.maxAreaOfIsland(grid1) << endl;
    cout << solution.maxAreaOfIsland(grid2) << endl;

    return 0;
}
