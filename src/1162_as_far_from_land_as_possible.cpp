#include <iostream>
#include <vector>
#include <queue>
#include <tuple>
#include <algorithm>
#include <functional>
#include <climits>

using std::cout;
using std::endl;
using std::vector;
using std::pair;
using std::tuple;

/*
    对每个0，以广度优先搜索查找最近的一个1，搜索的层数就是距离，取这些距离的最大值即可。
    时间复杂度O(4^max_distance * N^2)，其中max_distance是所示最大距离，每个点都有上下左右
    四个搜索方向，因此从某个0出发的搜索的时间复杂度大约为O(4^max_distance)。
    空间复杂度O(N^2)，需要一个二维数组记录节点是否被处理过了。
    超时！
*/
class Solution {
public:
    int maxDistance(vector<vector<int>> &grid) {
        const int N = static_cast<int>(grid.size());

        int max_distance = -1;
        for (int i = 0; i < N; ++i) {
            for (int j = 0; j < N; ++j) {
                if (grid[i][j] == 1)
                    continue;

                int distance = -1;

                std::queue<pair<int, int>> q;
                q.emplace(i, j);
                pair<int, int> next_last{i, j};   // 下一层最后一个
                int levels = 0;
                vector<vector<bool>> visited(N, vector<bool>(N, false));

                while (!q.empty()) {
                    auto p = q.front();
                    q.pop();

                    if (visited[p.first][p.second])
                        continue;

                    visited[p.first][p.second] = true;
                    if (grid[p.first][p.second] == 1) {
                        distance = levels;  // 只有遇到1退出才有效
                        break;
                    }

                    // 上
                    if (p.first > 0 && !visited[p.first - 1][p.second])
                        q.emplace(p.first - 1, p.second);

                    // 下
                    if (p.first < N - 1 && !visited[p.first + 1][p.second])
                        q.emplace(p.first + 1, p.second);

                    // 左
                    if (p.second > 0 && !visited[p.first][p.second - 1])
                        q.emplace(p.first, p.second - 1);

                    // 右
                    if (p.second < N - 1 && !visited[p.first][p.second + 1])
                        q.emplace(p.first, p.second + 1);

                    if (p == next_last) {
                        next_last = q.back();
                        ++levels;
                    }
                }

                max_distance = std::max(max_distance, distance);
            }
        }

        return max_distance;
    }
};

/*
    深度优先搜索+剪枝，即回溯算法，从0出发使用深度优先遍历查找1，如果路径长度超出当前最小记录则
    提前返回，如果遇到1就更新最小记录。最后在最小记录中选择最大的返回。
    超时！
*/
class Solution1 {
public:
    int maxDistance(vector<vector<int>> &grid) {
        const int N = grid.size();
        int min_dist = INT_MAX;
        vector<vector<bool>> visited(N, vector<bool>(N, false));

        std::function<void(int, int, int)> dfs;
        dfs = [&dfs, &grid, &visited, &min_dist, N](int i, int j, int curr_dist) mutable {
            if (curr_dist >= min_dist)
                return;

            if (grid[i][j] == 1) {
                min_dist = curr_dist;
                return;
            }

            visited[i][j] = true;

            // 上面
            if (i > 0 && !visited[i - 1][j])
                dfs(i - 1, j, curr_dist + 1);

            // 下面
            if (i < N - 1 && !visited[i + 1][j])
                dfs(i + 1, j, curr_dist + 1);

            // 左边
            if (j > 0 && !visited[i][j - 1])
                dfs(i, j - 1, curr_dist + 1);

            // 右边
            if (j < N - 1 && !visited[i][j + 1])
                dfs(i, j + 1, curr_dist + 1);

            visited[i][j] = false;
        };

        int distance = -1;
        for (int i = 0; i < N; ++i) {
            for (int j = 0; j < N; ++j) {
                if (grid[i][j] == 1)
                    continue;
                min_dist = INT_MAX;

                visited[i][j] = true;
                dfs(i, j, 0);
                visited[i][j] = false;

                distance = std::max(distance, min_dist);
            }
        }

        return distance == INT_MAX ? -1 : distance;
    }
};

class Solution2 {
public:
    int maxDistance(vector<vector<int>> &grid) {
        const int N = static_cast<int>(grid.size());

        int length = 1;
        bool stop = false;

        while (!stop) {
            stop = true;
            for (int i = 0; i < N; ++i) {
                for (int j = 0; j < N; ++j) {
                    if (grid[i][j] == length) {
                        // 上
                        if (i > 0 && grid[i - 1][j] == 0) {
                            grid[i - 1][j] = length + 1;
                            stop = false;
                        }

                        // 下
                        if (i < N - 1 && grid[i + 1][j] == 0) {
                            grid[i + 1][j] = length + 1;
                            stop = false;
                        }

                        // 左
                        if (j > 0 && grid[i][j - 1] == 0) {
                            grid[i][j - 1] = length + 1;
                            stop = false;
                        }

                        // 右
                        if (j < N - 1 && grid[i][j + 1] == 0) {
                            grid[i][j + 1] = length + 1;
                            stop = false;
                        }
                    }
                }
            }
            ++length;
        }

        return length == 2 ? -1 : length - 2;
    }
};

/*
    Solution2的改进，不再每次遍历地图，使用队列保存下一次要处理的点，即一次广度优先搜索解决问题。
*/
class Solution3 {
public:
    int maxDistance(vector<vector<int>> &grid) {
        const int N = static_cast<int>(grid.size());

        std::queue<tuple<int, int, int>> q;
        for (int i = 0; i < N; ++i) {
            for (int j = 0; j < N; ++j) {
                if (grid[i][j] == 1)
                    q.emplace(i, j, 0);
            }
        }

        // 没有1或者全是1
        if (q.empty() || q.size() == N * N)
            return -1;

        tuple<int, int, int> p;
        while (!q.empty()) {
            p = q.front();
            q.pop();

            int i = std::get<0>(p);
            int j = std::get<1>(p);
            int v = std::get<2>(p);

            // 上
            if (i > 0 && !grid[i - 1][j]) {
                q.emplace(i - 1, j, v + 1);
                grid[i - 1][j] = 1;
            }

            // 下
            if (i < N - 1 && !grid[i + 1][j]) {
                q.emplace(i + 1, j, v + 1);
                grid[i + 1][j] = 1;
            }

            // 左
            if (j > 0 && !grid[i][j - 1]) {
                q.emplace(i, j - 1, v + 1);
                grid[i][j - 1] = 1;
            }

            // 右
            if (j < N - 1 && !grid[i][j + 1]) {
                q.emplace(i, j + 1, v + 1);
                grid[i][j + 1] = 1;
            }
        }

        return std::get<2>(p);
    }
};


/*
    Solution3的改进，仍然使用队列保存下一次要处理的点，即一次广度优先搜索解决问题，
    但改为计算有多少层，方法为每层处理之前先计算有多少个点需要处理。
*/
class Solution4 {
public:
    int maxDistance(vector<vector<int>> &grid) {
        const int N = static_cast<int>(grid.size());

        std::queue<pair<int, int>> q;
        for (int i = 0; i < N; ++i) {
            for (int j = 0; j < N; ++j) {
                if (grid[i][j] == 1)
                    q.emplace(i, j);
            }
        }

        // 没有1或者全是1
        if (q.empty() || q.size() == N * N)
            return -1;

        int max_distance = 0;
        while (!q.empty()) {
            int size = q.size();  // 本层节点个数

            for (int k = 0; k < size; ++k) {
                auto p = q.front();
                q.pop();

                int i = p.first;
                int j = p.second;

                // 上
                if (i > 0 && !grid[i - 1][j]) {
                    q.emplace(i - 1, j);
                    grid[i - 1][j] = 1;
                }

                // 下
                if (i < N - 1 && !grid[i + 1][j]) {
                    q.emplace(i + 1, j);
                    grid[i + 1][j] = 1;
                }

                // 左
                if (j > 0 && !grid[i][j - 1]) {
                    q.emplace(i, j - 1);
                    grid[i][j - 1] = 1;
                }

                // 右
                if (j < N - 1 && !grid[i][j + 1]) {
                    q.emplace(i, j + 1);
                    grid[i][j + 1] = 1;
                }
            }
            ++max_distance;
        }

        return max_distance - 1;
    }
};

/*
    动态规划。遍历两次，从前往后遍历计算左上过来的最小值，从后往前计算右下过来的最小值。
 */
class Solution5 {
public:
    int maxDistance(vector<vector<int>> &grid) {
        constexpr int INF = 1e5;

        const int N = static_cast<int>(grid.size());
        vector<vector<int>> distances(N, vector<int>(N, INF));

        // 左边或者上边的
        // 第一行
        distances[0][0] = grid[0][0] == 1 ? 0 : INF;
        for (int j = 1; j < N; ++j)
            distances[0][j] = grid[0][j] == 1 ? 0 : distances[0][j - 1] + 1;
        // 其它行
        for (int i = 1; i < N; ++i) {
            distances[i][0] = grid[i][0] == 1 ? 0 : distances[i - 1][0] + 1;
            for (int j = 1; j < N; ++j) {
                if (grid[i][j] == 1)
                    distances[i][j] = 0;
                else  // 如果此处增加与自身的比较则不会有超过INF的值产生
                    distances[i][j] = std::min(distances[i - 1][j],
                                               distances[i][j - 1]) + 1;
            }
        }

        // 右边或者下边
        // 最后一行
        for (int j = N - 2; j >= 0; --j)
            distances[N - 1][j] = std::min(distances[N - 1][j],
                                           distances[N - 1][j + 1] + 1);
        // 其它行
        for (int i = N - 2; i >= 0; --i) {
            distances[i][N - 1] = std::min(distances[i][N - 1],
                                           distances[i + 1][N - 1] + 1);
            for (int j = N - 2; j >= 0; --j) {
                if (!grid[i][j]) {
                    distances[i][j] = std::min(std::min(distances[i][j],
                                                        distances[i + 1][j] + 1),
                                               distances[i][j + 1] + 1);
                }
            }
        }

        // 返回distances的最大值
        int max_distance = -1;
        for (int i = 0; i < N; ++i) {
            for (int j = 0; j < N; ++j)
                if (!grid[i][j])  // 跳过1，如果全1则为-1
                    max_distance = std::max(max_distance, distances[i][j]);
        }

        return max_distance >= INF ? -1 : max_distance;
    }
};

int main() {
    // 2
    vector<vector<int>> grid1 = {
            {1, 0, 1},
            {0, 0, 0},
            {1, 0, 1}
    };

    // 4
    vector<vector<int>> grid2 = {
            {1, 0, 0},
            {0, 0, 0},
            {0, 0, 0}
    };

    // -1
    vector<vector<int>> grid3 = {
            {0, 0, 0, 0},
            {0, 0, 0, 0},
            {0, 0, 0, 0},
            {0, 0, 0, 0}
    };

    // -1
    vector<vector<int>> grid4 = {
            {1, 1, 1, 1, 1},
            {1, 1, 1, 1, 1},
            {1, 1, 1, 1, 1},
            {1, 1, 1, 1, 1},
            {1, 1, 1, 1, 1}
    };

    Solution4 solution;
    cout << solution.maxDistance(grid1) << endl;
    cout << solution.maxDistance(grid2) << endl;
    cout << solution.maxDistance(grid3) << endl;
    cout << solution.maxDistance(grid4) << endl;

    return 0;
}
