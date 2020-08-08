#include <iostream>
#include <string>
#include <vector>

using std::string;
using std::vector;
using std::cout;
using std::endl;

class Solution {
public:
    int numDistinct(string &s, string &t) {
        // 对于s或t为空的情况，题目未规定
        if (t.empty())
            return 1;
        if (s.empty())
            return 0;

        const int M = static_cast<int>(s.size());
        const int N = static_cast<int>(t.size());

        // num_distinct[i][j]表示s.substr(0,i+1)的子序列(不连续)中t.substr(0,j+1)出现的次数
        // 计算过程中，当j比较小而i比较大时，这个数可能比较大，所以中间结果用long long来存储
        vector<vector<long long>> num_distinct(M, vector<long long>(N, 0));

        if (s[0] == t[0])
            num_distinct[0][0] = 1;
        for (int i = 1; i < M; ++i) {
            num_distinct[i][0] = num_distinct[i - 1][0] + (s[i] == t[0] ? 1 : 0);
            for (int j = 1; j < N && j <= i; ++j) {  // j>i时，t比s长，s的子序列中不可能含有t
                if (s[i] == t[j])
                    num_distinct[i][j] = num_distinct[i - 1][j - 1] + num_distinct[i - 1][j];
                else
                    num_distinct[i][j] = num_distinct[i - 1][j];
            }
        }

        return static_cast<int>(num_distinct[M - 1][N - 1]);
    }
};

/*
    优化空间
*/
class Solution1 {
public:
    int numDistinct(string &s, string &t) {
        // 对于s或t为空的情况，题目未规定
        if (t.empty())
            return 1;
        if (s.empty())
            return 0;

        const int M = static_cast<int>(s.size());
        const int N = static_cast<int>(t.size());

        // num_distinct[i][j]表示s.substr(0,i+1)的子序列(不连续)中t.substr(0,j+1)出现的次数
        // 计算过程中，当j比较小而i比较大时，这个数可能比较大，所以中间结果用long long来存储
        vector<long long> num_distinct(N, 0);

        if (s[0] == t[0])
            num_distinct[0] = 1;
        for (int i = 1; i < M; ++i) {
            for (int j = std::min(i, N - 1); j > 0; --j) {  // j>i时，t比s长，s的子序列中不可能含有t
                if (s[i] == t[j])
                    num_distinct[j] = num_distinct[j - 1] + num_distinct[j];
                // else
                //    num_distinct[j] = num_distinct[j];
            }
            num_distinct[0] = num_distinct[0] + (s[i] == t[0] ? 1 : 0);
        }

        return static_cast<int>(num_distinct[N - 1]);
    }
};

/*
    优化动态规划，
*/
class Solution2 {
public:
    int numDistinct(string &s, string &t) {
        // 对于s或t为空的情况，题目未规定
        if (t.empty())
            return 1;
        if (s.empty())
            return 0;

        const int M = static_cast<int>(s.size());
        const int N = static_cast<int>(t.size());

        // 计算t中各个字符最后一次出现的位置，和这个字符在当前位置的前面何处出现
        vector<int> last(128, -1);
        vector<int> next(N, -1);
        for (int i = 0; i < N; ++i) {
            next[i] = last[t[i]];
            last[t[i]] = i;
        }

        // num_distinct[i][j]表示s.substr(0,i)的子序列(不连续)中t.substr(0,j)出现的次数
        // 当i=0时，num_distinct除num_distinct[0]为1外全为0，所以循环中无i=0的情况，而是将i当作遍历s的下标
        vector<long long> num_distinct(N + 1, 0);
        num_distinct[0] = 1;
        for (int i = 0; i < M; ++i) {
            // 只有t[j]==s[i]的位置(j+1)才需要改变
            int j = last[s[i]];
            while (j > i)  // j>i时，t比s长，s的子序列中不可能含有t
                j = next[j];
            for (; j >= 0; j = next[j])
                num_distinct[j + 1] += num_distinct[j];  // j是t中的下标，长度需要加1
        }

        return static_cast<int>(num_distinct[N]);
    }
};

int main() {
    // 3
    string s1 = "rabbbit";
    string t1 = "rabbit";

    // 5
    string s2 = "babgbag";
    string t2 = "bag";

    Solution1 solution;
    cout << solution.numDistinct(s1, t1) << endl;
    cout << solution.numDistinct(s2, t2) << endl;

    return 0;
}
