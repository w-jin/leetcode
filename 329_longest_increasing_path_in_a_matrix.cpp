#include <iostream>
#include <vector>
#include <functional>

using std::cout;
using std::endl;
using std::vector;

/*
 * 从每个点出发，寻找以它为起点的最长递增路径，将计算过的点缓存起来，后面直接用。
 * 时间复杂度O(mn)，空间复杂度O(mn)。
 */
class Solution {
public:
    int longestIncreasingPath(const vector<vector<int>> &matrix) {
        if (matrix.empty() || matrix[0].empty())
            return 0;

        const int M = matrix.size();
        const int N = matrix[0].size();

        vector<vector<int>> cache(M, vector<int>(N, 0));

        std::function<int(int,int)> f;
        f = [&f, &matrix, &cache, M, N](int i, int j) -> int {
            if (cache[i][j] != 0)
                return cache[i][j];

            int longest = 0;
            if (i > 0 && matrix[i - 1][j] > matrix[i][j])
                longest = std::max(longest, f(i - 1, j));
            if (j > 0 && matrix[i][j - 1] > matrix[i][j])
                longest = std::max(longest, f(i, j - 1));
            if (i < M - 1 && matrix[i + 1][j] > matrix[i][j])
                longest = std::max(longest, f(i + 1, j));
            if (j < N - 1 && matrix[i][j + 1] > matrix[i][j])
                longest = std::max(longest, f(i, j + 1));

            cache[i][j] = longest + 1;
            return longest + 1;
        };

        int longest = 0;
        for (int i = 0; i < M; ++i) {
            for (int j = 0; j < N; ++j)
                longest = std::max(longest, f(i, j));
        }

        return longest;
    }
};

int main() {
    // 4
    vector<vector<int>> matrix1 = {
            {9, 9, 4},
            {6, 6, 8},
            {2, 1, 1}
    };

    // 4
    vector<vector<int>> matrix2 = {
            {3, 4, 5},
            {3, 2, 6},
            {2, 2, 1}
    };

    Solution solution;
    cout << solution.longestIncreasingPath(matrix1) << endl;
    cout << solution.longestIncreasingPath(matrix2) << endl;

    return 0;
}
