#include <iostream>
#include <string>
#include <vector>

/*
    分治解法
*/
class Solution {
public:
    bool isScramble(std::string &in_s1, std::string &in_s2) {
        if (in_s1.size() != in_s2.size())
            return false;
        if (in_s1.empty())
            return true;
        if (in_s1 == in_s2)
            return true;

        this->s1 = in_s1;
        this->s2 = in_s2;
        const int N = static_cast<int>(in_s1.size());

        // 检查两个字符串所含字符是否相同，假定它们只含小写字母。此措施可大幅提高效率
        alphabet_s1.resize(26);
        alphabet_s2.resize(26);
        for (int i = 0; i < 26; ++i) {
            alphabet_s1[i] = 0;
            alphabet_s2[i] = 0;
        }
        for (char c : s1)
            ++alphabet_s1[c - 'a'];
        for (char c : s2)
            ++alphabet_s2[c - 'a'];
        for (int i = 0; i < 26; ++i) {
            if (alphabet_s1[i] != alphabet_s2[i])
                return false;
        }

        // 尝试所有可能的划分，如果不交换两部分则为第一个if，如果交换两个部分则为第二个if
        // 划分的位置为s1[i]后
        for (int i = 0; i < N - 1; ++i) {
            if (isScramble(0, i, 0, i) && isScramble(i + 1, N - 1, i + 1, N - 1))
                return true;
            if (isScramble(0, i, N - 1 - i, N - 1) && isScramble(i + 1, N - 1, 0, N - i - 2))
                return true;
        }
        return false;
    }

private:
    // 和bool isScramble(std::string, std::string)一样的思路，处理的范围不同，所以参数不同
    bool isScramble(int ai, int aj, int bi, int bj) {
        if (ai == aj)
            return s1[ai] == s2[bi];

        for (int i = 0; i < 26; ++i) {
            alphabet_s1[i] = 0;
            alphabet_s2[i] = 0;
        }
        for (int i = ai; i <= aj; ++i)
            ++alphabet_s1[s1[i] - 'a'];
        for (int i = bi; i <= bj; ++i)
            ++alphabet_s2[s2[i] - 'a'];
        for (int i = 0; i < 26; ++i) {
            if (alphabet_s1[i] != alphabet_s2[i])
                return false;
        }

        for (int i = 0; i < aj - ai; ++i) {
            if (isScramble(ai, ai + i, bi, bi + i) && isScramble(ai + i + 1, aj, bi + i + 1, bj))
                return true;
            if (isScramble(ai, ai + i, bj - i, bj) && isScramble(ai + i + 1, aj, bi, bj - i - 1))
                return true;
        }
        return false;
    }

    std::string s1;
    std::string s2;
    std::vector<int> alphabet_s1;
    std::vector<int> alphabet_s2;
};


/*
    动态规划解法。动态规划解法遍历了所有情况，即使对于那些所含字符都不相同的字符串也是一样，
    所以即使它利用了最优子结构，效率也不一定有递归解法快。
    时间复杂度O(N^4)，空间O(N^3)
*/
class Solution1 {
public:
    bool isScramble(std::string &s1, std::string &s2) {
        if (s1.size() != s2.size())
            return false;
        if (s1.empty())
            return true;
        if (s1 == s2)
            return true;

        const int N = static_cast<int>(s1.size());

        // is_scramble[len][i][j]表示s1从i开始s2从j开始的长度为len的字符串是否互相为扰乱字符串
        std::vector<std::vector<std::vector<bool>>> is_scramble(
                N + 1, std::vector<std::vector<bool>>(N, std::vector<bool>(N, false)));

        // 长度为1的
        for (int i = 0; i < N; ++i) {
            for (int j = 0; j < N; ++j)
                is_scramble[1][i][j] = (s1[i] == s2[j]);
        }

        // 长度大于等于2的
        for (int len = 2; len <= N; ++len) {
            for (int i = 0; i <= N - len; ++i) {
                for (int j = 0; j <= N - len; ++j) {
                    // 遍历每一个分割位置，在s1[i+k]前分割
                    for (int k = 1; k < len; ++k) {
                        // 两个部分不交换
                        if (is_scramble[k][i][j] && is_scramble[len - k][i + k][j + k]) {
                            is_scramble[len][i][j] = true;
                            break;
                        }
                        // 两部分交换
                        if (is_scramble[k][i][j + len - k] && is_scramble[len - k][i + k][j]) {
                            is_scramble[len][i][j] = true;
                            break;
                        }
                    }
                }
            }
        }

        return is_scramble[N][0][0];
    }
};

/*
    动态规划解法，尝试优化内存。对长度为len的子字符串，起始位置范围为[0, N-len]，所以只需要
    O(N-len+1)的空间，所以此动态规划需要的内存区域不需要为方形。
    实测：Solution1消耗内存12.8M，Solution2消耗内存为11M，效果不理想。
*/
class Solution2 {
public:
    bool isScramble(std::string &s1, std::string &s2) {
        if (s1.size() != s2.size())
            return false;
        if (s1.empty())
            return true;
        if (s1 == s2)
            return true;

        const int N = static_cast<int>(s1.size());

        // is_scramble[len][i][j]表示s1从i开始s2从j开始的长度为len的字符串是否互相为扰乱字符串
        std::vector<std::vector<std::vector<bool>>> is_scramble;
        is_scramble.emplace_back();

        // 长度为1的
        is_scramble.emplace_back(N, std::vector<bool>(N, false));
        for (int i = 0; i < N; ++i) {
            for (int j = 0; j < N; ++j)
                is_scramble[1][i][j] = (s1[i] == s2[j]);
        }

        // 长度大于等于2的
        for (int len = 2; len <= N; ++len) {
            is_scramble.emplace_back(N - len + 1, std::vector<bool>(N - len + 1, false));
            for (int i = 0; i <= N - len; ++i) {
                for (int j = 0; j <= N - len; ++j) {
                    // 遍历每一个分割位置，在s1[i+k]前分割
                    for (int k = 1; k < len; ++k) {
                        // 两个部分不交换
                        if (is_scramble[k][i][j] && is_scramble[len - k][i + k][j + k]) {
                            is_scramble[len][i][j] = true;
                            break;
                        }
                        // 两部分交换
                        if (is_scramble[k][i][j + len - k] && is_scramble[len - k][i + k][j]) {
                            is_scramble[len][i][j] = true;
                            break;
                        }
                    }
                }
            }
        }

        return is_scramble[N][0][0];
    }
};

int main() {
    // true
    std::string s1_1 = "great";
    std::string s2_1 = "rgeat";

    // false
    std::string s1_2 = "abcde";
    std::string s2_2 = "caebd";

    // false
    std::string s1_3 = "ccabcbabcbabbbbcbb";
    std::string s2_3 = "bbbbabccccbbbabcba";

    Solution solution;
    std::cout << std::boolalpha;
    std::cout << solution.isScramble(s1_1, s2_1) << std::endl;
    std::cout << solution.isScramble(s1_2, s2_2) << std::endl;
    std::cout << solution.isScramble(s1_3, s2_3) << std::endl;

    return 0;
}
