#include <iostream>
#include <vector>

using std::cout;
using std::endl;
using std::vector;

/*
    搜索方向可以缩减为向右和向下两个方向。
    时间复杂度O(mn)，空间复杂度O(mn)。
*/
class Solution {
public:
    int movingCount(int m, int n, int k) {
        this->M = m;
        this->N = n;
        this->K = k;
        visited = vector<vector<bool>>(m, vector<bool>(n, false));
        return movingCountRecursive(0, 0);
    }

private:
    vector<vector<bool>> visited;
    int M = 0;
    int N = 0;
    int K = 0;

    int movingCountRecursive(int i, int j) {
        int count = 1;
        visited[i][j] = true;

        // 上方
        if (i > 0 && !visited[i - 1][j] && isAvailable(i - 1, j))
            count += movingCountRecursive(i - 1, j);

        // 下方
        if (i < M - 1 && !visited[i + 1][j] && isAvailable(i + 1, j))
            count += movingCountRecursive(i + 1, j);

        // 左边
        if (j > 0 && !visited[i][j - 1] && isAvailable(i, j - 1))
            count += movingCountRecursive(i, j - 1);

        // 右边
        if (j < N - 1 && !visited[i][j + 1] && isAvailable(i, j + 1))
            count += movingCountRecursive(i, j + 1);

        return count;
    }

    int isAvailable(int i, int j) const {
        int sum = 0;
        while (i > 0) {
            sum += i % 10;
            i /= 10;
        }
        while (j > 0) {
            sum += j % 10;
            j /= 10;
        }
        return sum <= K;
    }
};

/*
    由于每个点只用搜索向右和向下两个方向，因此可以使用一个二维数组记录每个点是否可以到达。
    时间复杂度O(mn)，空间复杂度O(mn)。
 */
class Solution1 {
public:
    int movingCount(int m, int n, int k) {
        vector<vector<bool>> available(m, vector<bool>(n, false));
        available[0][0] = true;
        for (int j = 1; j < n; ++j)
            available[0][j] = isAvailable(0, j, k) && available[0][j - 1];
        for (int i = 1; i < m; ++i) {
            available[i][0] = isAvailable(i, 0, k) && available[i - 1][0];
            for (int j = 1; j < n; ++j)
                available[i][j] = isAvailable(i, j, k) &&
                                  (available[i - 1][j] || available[i][j - 1]);
        }

        int count = 0;
        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                if (available[i][j])
                    ++count;
            }
        }
        return count;
    }

private:
    int isAvailable(int i, int j, int k) const {
        int sum = 0;
        while (i > 0) {
            sum += i % 10;
            i /= 10;
        }
        while (j > 0) {
            sum += j % 10;
            j /= 10;
        }
        return sum <= k;
    }
};

int main() {
    // 3
    int m1 = 2;
    int n1 = 3;
    int k1 = 1;

    // 1
    int m2 = 3;
    int n2 = 1;
    int k2 = 0;

    Solution1 solution;
    cout << solution.movingCount(m1, n1, k1) << endl;
    cout << solution.movingCount(m2, n2, k2) << endl;

    return 0;
}
