#include <iostream>
#include <vector>
#include <queue>

using std::vector;

/*
 * 主要的难点在于如果当前方块周围没有雷时如何处理，此处使用广度优先遍历，对每个方块计算其周围八
 * 个位置有多少个地雷，如果大于0就标记为地雷的个数，如果为0就标记为B然后处理周围八个位置。
 * 时间复杂度O(mn)，空间复杂度O(mn)。
 * 超时！对每个位置都要遍历周围8个方块来计算地雷个数，开销太大。
 */
class Solution {
public:
    vector<vector<char>> updateBoard(const vector<vector<char>> &board,
                                     const vector<int> &click) {
        vector<vector<char>> grid = board;

        // 挖到地雷
        if (grid[click[0]][click[1]] == 'M') {
            grid[click[0]][click[1]] = 'X';
            return grid;
        }

        const int dx[] = {1, 1, 0, -1, -1, -1, 0, 1};
        const int dy[] = {0, 1, 1, 1, 0, -1, -1, -1};

        // 没有挖到地雷，计算它的周围的地雷个数，如果没有地雷，把它标记为B然后寻找处理周围的
        // 方块，如果有地雷就将它标记为地雷的个数，不再处理它周围的方块
        std::queue<std::pair<int, int>> q;
        q.emplace(click[0], click[1]);
        while (!q.empty()) {
            auto curr = q.front();
            q.pop();

            // 队列中可能有重复的，不要重复处理，提升性能关键一步！
            if (grid[curr.first][curr.second] != 'E')
                continue;

            int mines_count = 0;
            for (int i = 0; i < 8; ++i) {
                int x = curr.first + dx[i];
                int y = curr.second + dy[i];
                if (x < 0 || y < 0 || x >= grid.size() || y >= grid[0].size())
                    continue;
                if (grid[x][y] == 'M')
                    ++mines_count;
            }

            if (mines_count > 0)
                grid[curr.first][curr.second] = '0' + mines_count;

            if (mines_count == 0) {
                grid[curr.first][curr.second] = 'B';

                // 处理它周围的未翻开的方块
                for (int i = 0; i < 8; ++i) {
                    int x = curr.first + dx[i];
                    int y = curr.second + dy[i];
                    if (x < 0 || y < 0 || x >= grid.size() || y >= grid[0].size())
                        continue;
                    if (grid[x][y] == 'E')
                        q.emplace(x, y);
                }
            }
        }

        return grid;
    }
};


std::ostream &operator<<(std::ostream &os, const vector<char> &vec) {
    if (vec.empty())
        return os;
    for (int i = 0; i + 1 < vec.size(); ++i)
        os << "'" << vec[i] << "', ";
    return os << "'" << vec.back() << "'";
}

std::ostream &operator<<(std::ostream &os, const vector<vector<char>> &vec) {
    for (const auto &v : vec)
        os << v << "\n";
    return os;
}

int main() {
    // 'B', '1', 'E', '1', 'B'
    // 'B', '1', 'M', '1', 'B'
    // 'B', '1', '1', '1', 'B'
    // 'B', 'B', 'B', 'B', 'B'

    vector<vector<char>> board1 = {
            {'E', 'E', 'E', 'E', 'E'},
            {'E', 'E', 'M', 'E', 'E'},
            {'E', 'E', 'E', 'E', 'E'},
            {'E', 'E', 'E', 'E', 'E'}
    };

    vector<int> click1 = {3, 0};


    // 'B', '1', 'E', '1', 'B',
    // 'B', '1', 'X', '1', 'B',
    // 'B', '1', '1', '1', 'B',
    // 'B', 'B', 'B', 'B', 'B'

    vector<vector<char>> board2 = {
            {'B', '1', 'E', '1', 'B'},
            {'B', '1', 'M', '1', 'B'},
            {'B', '1', '1', '1', 'B'},
            {'B', 'B', 'B', 'B', 'B'}
    };

    vector<int> click2 = {1, 2};


    Solution solution;
    std::cout << solution.updateBoard(board1, click1) << "\n";
    std::cout << solution.updateBoard(board2, click2) << "\n";

    return 0;
}
