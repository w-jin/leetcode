#include <iostream>
#include <vector>
#include <algorithm>

/* 动态规划：paths[i][j]=paths[i-1][j]+paths[i][j-1] */
class Solution {
public:
    int uniquePaths(int m, int n) {
        std::vector<int> paths(n, 1);
        for (int i = 1; i < m; ++i) {
            for (int j = 1; j < n; ++j)
                paths[j] = paths[j] + paths[j - 1];
        }
        return paths[n - 1];
    }
};

/* 利用组合来求，机器人要从左上角走到右下角，一定要向右走m-1步，向下走n-1步，
 * 所以路径数量就是这m+n-2步中哪m-1步是向右走的组合数，C(m+n-2,m-1)。
 */
class Solution1 {
public:
    int uniquePaths(int m, int n) {
        //使n较大，减小计算量
        if (m > n)
            std::swap(m, n);

        //这样做可以计算的范围更大，但为什么每步都能整除呢？因为除数是1、2、3...，被除数是连续自然数，
        //所以1个数的积可以被1整除；两个数中必有一个是偶数，所以两个数的积能被2整除；三个数中必有一个
        //是3的倍数，所以三个数的积能被3整除，以此类推。
        long long paths = 1;
        for (int i = 1; i <= m - 1; ++i) {
            paths *= n + i - 1;
            paths /= i;
        }

        return static_cast<int>(paths);
    }
};

int main() {
    // 3, 28
    Solution1 solution;
    std::cout << solution.uniquePaths(3, 2) << std::endl
              << solution.uniquePaths(7, 3) << std::endl;
    return 0;
}
