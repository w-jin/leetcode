#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>

using std::cout;
using std::endl;
using std::vector;

/*
 * 反向动态规划。设dp[i][j]为从位置(i, j)到右下角所需的最低初始健康点数，假定已经计算出
 * dp[i+1][j]和dp[i][j+1]，现在计算dp[i][j]。设到位置(i, j)时健康点数为m，则到达位置
 * (i+1, j)和(i, j+1)时的的健康点数为m + dungeon[i][j]，要保证通过这两个位置能够到达
 * 右下角，则必须满足m + dungeon[i][j] > min{dp[i+1][j], dp[i][j+1]}，因此
 * m > min{dp[i+1][j], dp[i][j+1]} - dungeon[i][j]。按定义，
 * dp[i][j] = min{dp[i+1][j], dp[i][j+1]} - dungeon[i][j]。当它小于1时取1以保证出生
 * 时不死。
 */
class Solution {
public:
    int calculateMinimumHP(const vector<vector<int>> &dungeon) {
        if (dungeon.empty() || dungeon[0].empty())
            return 0;

        const int M = dungeon.size();
        const int N = dungeon[0].size();

        vector<int> min_HP(N, INT_MAX);
        min_HP[N - 1] = 1;
        for (int i = M - 1; i >= 0; --i) {
            min_HP[N - 1] = std::max(min_HP[N - 1] - dungeon[i][N - 1], 1);
            for (int j = N - 2; j >= 0; --j)
                min_HP[j] = std::max(std::min(min_HP[j], min_HP[j + 1]) - dungeon[i][j], 1);
        }

        return min_HP[0];
    }
};

int main() {
    // 7
    vector<vector<int>> dungeon1 = {
            {-2, -3,  3},
            {-5, -10, 1},
            {10, 30,  -5}
    };

    // 3
    vector<vector<int>> dungeon2 = {
            {1,  -3, 3},
            {0,  -2, 0},
            {-3, -3, -3}
    };

    Solution solution;
    cout << solution.calculateMinimumHP(dungeon1) << endl;
    cout << solution.calculateMinimumHP(dungeon2) << endl;

    return 0;
}
