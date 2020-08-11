#include <iostream>
#include <vector>
#include <algorithm>

using std::cout;
using std::endl;
using std::vector;

class Solution {
public:
    int superEggDrop(int K, int N) {
        vector<vector<int>> f(N + 1, vector<int>(K + 1, 0));
        for (int n = 1; n <= N; ++n)
            f[n][1] = n;
        for (int k = 1; k <= K; ++k) {
            f[0][k] = 0;
            f[1][k] = 1;
        }
        for (int n = 2; n <= N; ++n) {
            for (int k = 2; k <= K; ++k) {
                int t = 10000000;
                for (int x = 1; x <= n - 1; ++x)
                    t = std::min(t, std::max(f[x - 1][k - 1], f[n - x][k]) + 1);
                f[n][k] = t;
            }
        }

        return f[N][K];
    }
};

int main() {
    // 2
    int K1 = 1;
    int N1 = 2;

    // 3
    int K2 = 3;
    int N2 = 14;

    Solution solution;
    cout << solution.superEggDrop(K1, N1) << endl;
    cout << solution.superEggDrop(K2, N2) << endl;

    return 0;
}
