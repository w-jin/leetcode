#include <iostream>
#include <string>
#include <vector>

using std::string;
using std::vector;

/*
    回溯解法，遍历所有情况
*/
class Solution {
public:
    bool isInterleave(string &s1, string &s2, string &s3) {
        if (s1.size() + s2.size() != s3.size())
            return false;
        if (s1.empty())
            return s2 == s3;
        if (s2.empty())
            return s1 == s3;

        // 检查所含字符是否相同
        if (!CheckLetters(s1, s2, s3))
            return false;

        return isInterleave(s1, 0, s2, 0, s3);
    }

private:
    bool isInterleave(string &s1, int i1, string &s2, int i2, string &s3) {
        if (i1 == s1.size())
            return s2.substr(i2) == s3.substr(s1.size() + i2);
        if (i2 == s2.size())
            return s1.substr(i1) == s3.substr(i1 + s2.size());

        if (s1[i1] == s3[i1 + i2] && isInterleave(s1, i1 + 1, s2, i2, s3))
            return true;
        return s2[i2] == s3[i1 + i2] && isInterleave(s1, i1, s2, i2 + 1, s3);
    }

    bool CheckLetters(const string &s1, const string &s2, const string &s3) {
        static vector<int> letters12(26);
        static vector<int> letters3(26);

        for (int &i : letters12)
            i = 0;
        for (int &i : letters3)
            i = 0;

        for (char c : s1)
            ++letters12[c - 'a'];
        for (char c : s2)
            ++letters12[c - 'a'];
        for (char c : s3)
            ++letters3[c - 'a'];

        for (int i = 0; i < 26; ++i) {
            if (letters12[i] != letters3[i])
                return false;
        }
        return true;
    }
};

/*
    动态规划解法
*/
class Solution1 {
public:
    bool isInterleave(string &s1, string &s2, string &s3) {
        if (s1.size() + s2.size() != s3.size())
            return false;
        if (s1.empty())
            return s2 == s3;
        if (s2.empty())
            return s1 == s3;

        const int M = static_cast<int>(s1.size());
        const int N = static_cast<int>(s2.size());

    /* 这段代码没有问题，只是它是从后往前计算的，可能不太好看
        // is_interleave[i][j]表示s1.substr(i)和s2.substr(j)能否交错成s3.substr(i+j)
        vector<vector<bool>> is_interleave(M + 1, vector<bool>(N + 1, false));
        is_interleave[M][N] = true;
        for (int j = N - 1; j >= 0; --j)
            is_interleave[M][j] = s2[j] == s3[M + j] && is_interleave[M][j + 1];

        for (int i = M - 1; i >= 0; --i) {
            is_interleave[i][N] = s1[i] == s3[i + N] && is_interleave[i + 1][N];
            for (int j = N - 1; j >= 0; --j) {
                if (s1[i] == s3[i + j] && is_interleave[i + 1][j]) {
                    is_interleave[i][j] = true;
                    continue;
                }
                if (s2[j] == s3[i + j] && is_interleave[i][j + 1]) {
                    is_interleave[i][j] = true;
                    continue;
                }
            }
        }

        return is_interleave[0][0];
    */
        // is_interleave[i][j]表示s1.substr(0,i)和s2.substr(0,j)是否能交错成s3.substr(0,i+j)
        vector<vector<bool>> is_interleave(M + 1, vector<bool>(N + 1, false));
        is_interleave[0][0] = true;
        for (int j = 1; j <= N; ++j)
            is_interleave[0][j] = s2[j - 1] == s3[j - 1] && is_interleave[0][j - 1];

        for (int i = 1; i <= M; ++i) {
            is_interleave[i][0] = s1[i - 1] == s3[i - 1] && is_interleave[i - 1][0];
            for (int j = 1; j <= N; ++j) {
                if (s1[i - 1] == s3[i + j - 1] && is_interleave[i - 1][j]) {
                    is_interleave[i][j] = true;
                    continue;
                }
                if (s2[j - 1] == s3[i + j - 1] && is_interleave[i][j - 1]) {
                    is_interleave[i][j] = true;
                    continue;
                }
            }
        }

        return is_interleave[M][N];
    }
};

/*
    动态规划解法，减少内存使用。但leetcode实测仅将内存从8.8M减小到8.4M，可能有优化。
*/
class Solution2 {
public:
    bool isInterleave(string &s1, string &s2, string &s3) {
        if (s1.size() + s2.size() != s3.size())
            return false;
        if (s1.empty())
            return s2 == s3;
        if (s2.empty())
            return s1 == s3;

        const int M = static_cast<int>(s1.size());
        const int N = static_cast<int>(s2.size());

        // is_interleave[i][j]表示s1.substr(0,i)和s2.substr(0,j)是否能交错成s3.substr(0,i+j)
        vector<bool> is_interleave(N + 1);
        is_interleave[0] = true;
        for (int j = 1; j <= N; ++j)
            is_interleave[j] = s2[j - 1] == s3[j - 1] && is_interleave[j - 1];

        for (int i = 1; i <= M; ++i) {
            is_interleave[0] = s1[i - 1] == s3[i - 1] && is_interleave[0];
            for (int j = 1; j <= N; ++j) {
                if (s1[i - 1] == s3[i + j - 1] && is_interleave[j]) {
                    is_interleave[j] = true;
                    continue;
                }
                if (s2[j - 1] == s3[i + j - 1] && is_interleave[j - 1]) {
                    is_interleave[j] = true;
                    continue;
                }
                is_interleave[j] = false;
            }
        }

        return is_interleave[N];
    }
};

int main() {
    // true
    string s1_1 = "aabcc";
    string s2_1 = "dbbca";
    string s3_1 = "aadbbcbcac";

    // false
    string s1_2 = "aabcc";
    string s2_2 = "dbbca";
    string s3_2 = "aadbbbaccc";

    // false
    string s1_3 = "bbbbbabbbbabaababaaaabbababbaaabbabbaaabaaaaababbbababbbbbabbbbababbabaabababbbaabababababbbaaababaa";
    string s2_3 = "babaaaabbababbbabbbbaabaabbaabbbbaabaaabaababaaaabaaabbaaabaaaabaabaabbbbbbbbbbbabaaabbababbabbabaab";
    string s3_3 = "babbbabbbaaabbababbbbababaabbabaabaaabbbbabbbaaabbbaaaaabbbbaabbaaabababbaaaaaabababbababaababbababb"
                  "bababbbbaaaabaabbabbaaaaabbabbaaaabbbaabaaabaababaababbaaabbbbbabbbbaabbabaabbbbabaaabbababbabbabbab";

    Solution1 solution;
    std::cout << std::boolalpha;
    std::cout << solution.isInterleave(s1_1, s2_1, s3_1) << std::endl;
    std::cout << solution.isInterleave(s1_2, s2_2, s3_2) << std::endl;
    std::cout << solution.isInterleave(s1_3, s2_3, s3_3) << std::endl;

    return 0;
}
