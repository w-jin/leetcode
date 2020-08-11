#include <iostream>
#include <string>
#include <vector>

/* 暴力算法，匹配不成功就回溯，每个*尝试匹配任意长度，时间复杂度O(n^m)，m是*的个数 */
class Solution {
public:
    bool isMatch(const std::string &s, const std::string &p) {
        return isMatchRecursive(s, p, 0, 0);
    }

private:
    bool isMatchChar(char a, char b) {
        return a == b || b == '?';
    }

    bool isMatchRecursive(const std::string &s, const std::string &p, int i_s, int i_p) {
        if (i_p == p.size())
            return i_s == s.size();

        if (p[i_p] != '*') {
            if (i_s == s.size() || !isMatchChar(s[i_s], p[i_p]))
                return false;
            return isMatchRecursive(s, p, i_s + 1, i_p + 1);
        }

        //多个连续的*相当于一个
        while (i_p + 1 < p.size() && p[i_p + 1] == '*')
            ++i_p;

        //*匹配0次
        if (isMatchRecursive(s, p, i_s, i_p + 1))
            return true;
        //*匹配一次或多次
        return i_s < s.size() && isMatchRecursive(s, p, i_s + 1, i_p);
    }
};

/* 暴力算法，与上个Solution没有本质区别，仅可减小部分函数调用开销 */
class Solution1 {
public:
    bool isMatch(const std::string &s, const std::string &p) {
        return isMatchRecursive(s, p, 0, 0);
    }

private:
    bool isMatchChar(char a, char b) {
        return a == b || b == '?';
    }

    bool isMatchRecursive(const std::string &s, const std::string &p, int i_s, int i_p) {
        if (i_s == s.size() && i_p == p.size())
            return true;
        if (i_s == s.size() && p[i_p] != '*')
            return false;
        if (i_p == p.size())
            return false;

        if (isMatchChar(s[i_s], p[i_p]))
            return isMatchRecursive(s, p, i_s + 1, i_p + 1);

        if (p[i_p] == '*') {
            while (i_p + 1 < p.size() && p[i_p + 1] == '*')
                ++i_p;
            for (int k = 0; i_s + k <= s.size(); ++k) {
                if (isMatchRecursive(s, p, i_s + k, i_p + 1))
                    return true;
            }
        }

        return false;
    }
};

/* 动态规划，时间复杂度O(n^2) */
class Solution2 {
public:
    bool isMatch(const std::string &s, const std::string &p) {
        //match[i][j]表示s[1..i]和p[1..j]是否能匹配，match[0][0]表示s和p为空的情况
        std::vector<std::vector<bool>> match(s.size() + 1, std::vector<bool>(p.size() + 1, false));

        //p为空时，只有s也为空才能匹配，所以match[i][0]中只有match[0][0]为true，其余为false
        match[0][0] = true;
        //s为空时，p只能为空或者全为*才能匹配，只要p中出现一个非*的字母，后面的就全为false
        for (int j = 1; j <= p.size() && p[j - 1] == '*'; ++j)
            match[0][j] = true;

        for (int i = 1; i <= s.size(); ++i) {
            for (int j = 1; j <= p.size(); ++j) {
                if (p[j - 1] != '*')
                    match[i][j] = isMatchChar(s[i - 1], p[j - 1]) && match[i - 1][j - 1];
                else
                    match[i][j] = match[i - 1][j] || match[i][j - 1];
            }
        }

        return match.back().back();
    }

private:
    bool isMatchChar(char a, char b) {
        return a == b || b == '?';
    }
};

/* 性能最好的版本，仍然是回溯算法，但与前述回溯算法的区别在于，只对最近一个*进行回溯，时间复杂度O(m+n)，m
 * 和n分别为s和p的长度。
 * 证明只对最近一个*进行回溯即可：假定s的部分结构为...s1...s1...，p的部分结构为...*...s1...*...，其中s1
 * 为一个子串。当算法使p中s1匹配到s中第一个s1时，p中第二个*将匹配s的后半部分...s1...，若在p的第二个*之后匹配
 * 失败，算法将只对第二个*进行回溯，要证明算法正确，只需要说明只对第二个*回溯和对两个*都回溯是等价的，这显然成立：
 * 如果对p的第一个*也进行回溯，则p的s1将匹配s的第二个s1，p的第二个*将匹配s的后半部分...，这对于再后面的匹配显
 * 然没有影响，因此仅需要对最近一个*进行回溯即可。
 */
class Solution3 {
public:
    bool isMatch(const std::string &s, const std::string &p) {
        if (p.empty())
            return s.empty();

        int i_s = 0, i_p = 0;
        int p_star = -1, s_star = -1;
        while (i_s < s.size()) {
            //p中不是*，看看s和p的字符是否能匹配
            if (s[i_s] == p[i_p] || p[i_p] == '?') {
                ++i_s;
                ++i_p;
            }
            //p遇到了*，记录其位置，并且先匹配空串试试
            else if (p[i_p] == '*') {
                while (i_p + 1 < p.size() && p[i_p + 1] == '*')
                    ++i_p;
                p_star = i_p++;
                s_star = i_s;
            }
            //回溯，上一个*多匹配一个字符
            else if (p_star != -1) {
                i_p = p_star + 1;
                i_s = ++s_star;
            }
            else {
                return false;
            }
        }

        //s快到末尾，如果p的末尾剩余的都是*，还是能匹配
        while (i_p < p.size()) {
            if (p[i_p] != '*')
                return false;
            ++i_p;
        }
        return true;
    }
};

int main()
{
    std::string s1 = "aa", p1 = "a"; //false
    std::string s2 = "aa", p2 = "*"; //true
    std::string s3 = "cb", p3 = "?a"; //false
    std::string s4 = "adceb", p4 = "*a*b"; //true
    std::string s5 = "acdcb", p5 = "a*c?b"; //false
    std::string s6 = "abefcdgiescdfimde", p6 = "ab*cd?i*de";

    Solution3 solution;
    std::cout << std::boolalpha
              << solution.isMatch(s1, p1) << std::endl
              << solution.isMatch(s2, p2) << std::endl
              << solution.isMatch(s3, p3) << std::endl
              << solution.isMatch(s4, p4) << std::endl
              << solution.isMatch(s5, p5) << std::endl
              << solution.isMatch(s6, p6) << std::endl;

    return 0;
}
