#include <iostream>
#include <vector>
#include <functional>

using std::cout;
using std::endl;
using std::vector;

class Solution {
public:
    int numIslands(vector<vector<char>> &grid) {
        if (grid.empty() || grid[0].empty())
            return 0;

        const int M = grid.size();
        const int N = grid[0].size();

        std::function<void(int, int)> setZero;
        setZero = [&setZero, M, N, &grid](int i, int j) {
            grid[i][j] = '0';
            if (i > 0 && grid[i - 1][j] == '1')
                setZero(i - 1, j);
            if (i < M - 1 && grid[i + 1][j] == '1')
                setZero(i + 1, j);
            if (j > 0 && grid[i][j - 1] == '1')
                setZero(i, j - 1);
            if (j < N - 1 && grid[i][j + 1] == '1')
                setZero(i, j + 1);
        };

        int count = 0;
        for (int i = 0; i < M; ++i) {
            for (int j = 0; j < N; ++j) {
                if (grid[i][j] == '1') {
                    ++count;
                    setZero(i, j);
                }
            }
        }

        return count;
    }
};

int main() {
    // 1
    vector<vector<char>> grid1 = {
            {'1', '1', '1', '1', '0'},
            {'1', '1', '0', '1', '0'},
            {'1', '1', '0', '0', '0'},
            {'0', '0', '0', '0', '0'}
    };

    // 3
    vector<vector<char>> grid2 = {
            {'1', '1', '0', '0', '0'},
            {'1', '1', '0', '0', '0'},
            {'0', '0', '1', '0', '0'},
            {'0', '0', '0', '1', '1'}
    };

    Solution solution;
    cout << solution.numIslands(grid1) << endl;
    cout << solution.numIslands(grid2) << endl;

    return 0;
}
