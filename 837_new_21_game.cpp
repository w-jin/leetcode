#include <iostream>
#include <vector>

using std::cout;
using std::endl;
using std::vector;

/*
 * 不正确!
class Solution {
public:
    double new21Game(int N, int K, int W) {
        vector<double> P(N + 1);
        P[0] = 1.0;
        for (int i = 1; i < K; ++i)
            P[i]  = 0;
        P[K] = 1.0 / W;
        for (int i = K + 1; i <= N; ++i) {
            int s = i <= K ? i - 1 : K - 1;
            int e = i >= W ? i - W : 0;
            P[i] = 0;
            for (int j = s; j >= e; --j)
                P[i] += double(i - j) / W * P[j];
        }
        return P[N];
    }
};
*/

/*
 * 模拟方法。超时！
 */
class Solution {
public:
    double new21Game(int N, int K, int W) {
        vector<double> P(N + 1, 0);
        P[0] = 1;

        int positive_count = 0;
        do {
            positive_count = 0;
            for (int i = K - 1; i >= 0; --i) {
                if (P[i] == 0)
                    continue;
                ++positive_count;
                for (int j = 1; j <= W; ++j) {
                    if (i + j > N)
                        break;
                    P[i + j] += 1.0 / W * P[i];
                }
                P[i] = 0;
            }
        } while (positive_count > 0);
        
        double result = 0;
        for (int i = K; i <= N; ++i)
            result += P[i];
        return result;
    }
};


/*
 * 动态规划算法。设P[x]表示从分数x开始游戏获得胜利的概率，题目要求求的为P[0]。
 * 要计算P[x]，可以用递推公式：从x开始进行游戏，下一轮的分数可能为x+1, x+2, ...,
 * x+W，再下一轮就是从这些分数开始游戏，所以
 *   P[x] = (P[x+1] + P[x+2] + ... + P[x+W]) / W
 * 对于边界条件，
 *   0、当N >= K+W-1时，游戏结束必有x <= K+W-1 <= N，所以P[0]=1；
 *   1、当K <= x <= N < K+W-1时，游戏结束且分数小于等于N，所以P[x]=1；
 *   2、当N < x <= K+W-1时，游戏结束且分数超过N，所以P[x]=0。
 * 所以应当从x=K-1开始计算直到x=0，对P的访问，最大的下标为K-1+W，所以P的空间大小
 * 为K+W。
 * 时间复杂度O(N + KW)，空间复杂度O(K + W)。
 * 超时！
 */
class Solution1 {
public:
    double new21Game(int N, int K, int W) {
        if (N >= K + W - 1)
            return 1.0;
        vector<double> P(K + W, 0);
        for (int i = K; i <= N; ++i)
            P[i] = 1.0;
        for (int i = K - 1; i >= 0; --i) {
            for (int j = 1; j <= W; ++j)
                P[i] += P[i + j] / W;
        }
        return P[0];
    }
};

/*
 * 动态规划算法优化。在Solution1中，P[x]的递推公式为：
 *   P[x] = (P[x+1] + P[x+2] + ... + P[x+W]) / W;
 * 所以
 *   P[x+1] = (P[x+2] + P[x+3] + ... + P[x+W+1]) / W;
 * 两式相减可得：
 *   P[x] - P[x+1] = (P[x+1] - P[x+W+1]) / W
 *                 = (W+1)P[x+1]/W - P[x+W+1]/W
 * 需要注意P[K-1]不能用上面的公式计算，可以按下面的公式计算：
 *   P[K-1] = (P[K] + P[K+1] + ... + P[K+W-1]) / W;
 * 当N >= K+W-1时，游戏结束必有x <= K+W-1 <= N，所以P[0]=1，可以提前判断并返回，
 * 然后只考虑N < K+W-1的情况，所以
 *   P[K-1] = (P[K] + P[K+1] + ... + P[N]) / W = (N - K + 1) / W;
 * 
 * 时间复杂度O(N + K)，空间复杂度O(K + W)。
 */
class Solution2 {
public:
    double new21Game(int N, int K, int W) {
        if (0 == K || N >= K + W - 1)
            return 1.0;
        vector<double> P(K + W, 0);
        for (int i = K; i <= N; ++i)
            P[i] = 1.0;
        P[K - 1] = static_cast<double>(N - K + 1) / W;
        for (int i = K - 2; i >= 0; --i)
            P[i] = (W + 1) * P[i + 1] / W - P[i + W + 1] / W;
        return P[0];
    }
};

int main() {
    // 1
    int N1 = 10;
    int K1 = 1;
    int W1 = 10;

    // 0.6
    int N2 = 6;
    int K2 = 1;
    int W2 = 10;

    // 0.73278
    int N3 = 21;
    int K3 = 17;
    int W3 = 10;

    Solution1 solution;
    cout << solution.new21Game(N1, K1, W1) << endl;
    cout << solution.new21Game(N2, K2, W2) << endl;
    cout << solution.new21Game(N3, K3, W3) << endl;

    return 0;
} 


