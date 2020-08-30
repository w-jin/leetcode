#include <iostream>
#include <string>
#include <vector>

using std::cout;
using std::endl;
using std::string;
using std::vector;

/*
 * 逐个子串s.substr(0, i)尝试，如果i不是s.size()的因子则不可能构成s，如果i是s.size()的
 * 因子则比较一下s是否是s.substr(0, i)构成的。
 * 时间复杂度O(n^2)，空间复杂度O(1)。
 */
class Solution {
public:
    bool repeatedSubstringPattern(const string &s) {
        for (int i = 1; i <= s.size() / 2; ++i) {
            if (s.size() % i != 0)
                continue;
            int j = i;
            while (j < s.size()) {
                // 子串到末尾时再回到开头，实际也可以不回到开头，因为当前字符向左偏移i是
                // 必然等于子串相应位置的字符，否则早就已经失配了。(s[j] != s[j-i])
                if (s[j] != s[(j - i) % i])
                    break;
                ++j;
            }
            if (j == s.size())
                return true;
        }

        return false;
    }
};


/*
 * 若s可由长为l的子串重复构成，则s向右移动l与s本身可以匹配，或者说s+s中第l个位置开始长
 * 为s.size()的子串是s本身，如s=abab，则s+s=abababab，从第2个位置开始长为4的子串为
 * abab，即s本身。反过来，如果s+s中能找到不以0和s.size()开头子串与s相等，则s可以由子
 * 串重复构成，证明略。因此要判断s是否可由子串重复构成，可在s+s中查找不以0和s.size()开
 * 头的子串与s相等，如果能找到s可由子串重复构成，否则不能。
 * 查找的过程使用kmp算法，时间复杂度O(n)，空间复杂度O(n)。
 * 实测还没有朴素方法快！
 */
class Solution1 {
public:
    bool repeatedSubstringPattern(const string &s) {
        return kmp(s + s, s)  != s.size();
    }

private:
    int kmp(const string &s, const string &t) {
        int i = 1;  // 从1开始找
        int j = 0;
        vector<int> next = getNext(t);
        const int N = t.size();
        while (i < s.size() && j < N) {
            if (j == -1 || s[i] == t[j]) {
                ++i;
                ++j;
            } else {
                j = next[j];
            }
        }
        return j == N ? i - j : -1;
    }

    vector<int> getNext(const string &t) {
        if (t.empty())
            return {};
        vector<int> next(t.size());
        next[0] = -1;
        int k = -1;
        for (int j = 0; j < t.size() - 1; ++j) {
            while (k != -1 && t[j] != t[k])
                k = next[k];
            ++k;
            if (t[j + 1] == t[k])
                next[j + 1] = next[k];
            else
                next[j + 1] = k;
        }
        return next;
    }
};

int main() {
    // true
    string s1 = "abab";

    // false
    string s2 = "aba";

    // true
    string s3 = "abcabcabcabc";

    Solution1 solution;
    cout << std::boolalpha;
    cout << solution.repeatedSubstringPattern(s1) << endl;
    cout << solution.repeatedSubstringPattern(s2) << endl;
    cout << solution.repeatedSubstringPattern(s3) << endl;

    return 0;
}
