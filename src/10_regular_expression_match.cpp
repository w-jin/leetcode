#include <iostream>
#include <string>
#include <vector>

class Solution {
public:
    bool isMatch(const std::string &s, const std::string &p) {
        //s可能为空，且只包含a-z的小写字母。p可能为空，且只包含a-z的小写字母，以及字符.和*。
        //回溯法，只要遇到*就尝试匹配0次或多次的所有可能
        return isMatch(s, 0, p, 0);
    }

private:
    bool isMatch(const std::string &s, int i_s, const std::string &p, int i_p) {
        //如果p为空，只有s也为空时才能匹配成功
        if (i_p == p.size())
            return i_s == s.size();
        //如果p只有一个元素，只有s也只有一个元素且和p的元素匹配时才成功
        if (i_p == p.size() - 1)
            return i_s == s.size() - 1 && isMatchChar(s[i_s], p[i_p]);
        //p有两个以上元素
        //如果p的第二个元素不是*，s和p的第一个元素必须匹配，然后再尝试匹配剩余的元素
        if ('*' != p[i_p + 1]) {
            if (i_s == s.size())
                return false;
            return isMatchChar(s[i_s], p[i_p]) && isMatch(s, i_s + 1, p, i_p + 1);
        }
        //如果p的第二个元素是*
        //   0 1 2 3 4 5 6 7
        //s: m i s s i s s s
        //p: m i s * i s *
        //i_s=2,i_p=2时执行这个循环，直到i_s=4，在这之间尝试匹配ssisss和is*以及sisss和is*，即*匹配0次和1次
        while (i_s < s.size() && isMatchChar(s[i_s], p[i_p])) {
            if (isMatch(s, i_s, p, i_p + 2))
                return true;
            ++i_s;
        }
        //对于上例，i_s=4,i_p+2=4，即匹配2次
        //若上个循环一次都不执行，即s[i_s]!=p[i_p]，则*一次都不匹配
        return isMatch(s, i_s, p, i_p + 2);
    }

    bool isMatchChar(char s, char p) {
        return s == p || '.' == p;
    }
};

class Solution1 {
public:
    bool isMatch(const std::string &s, const std::string &p) {
        //s可能为空，且只包含a-z的小写字母。p可能为空，且只包含a-z的小写字母，以及字符.和*。
        //动态规划，match[i][j]表示s[0,i)和p[0,j)是否匹配
        std::vector<std::vector<bool>> match(s.size() + 1, std::vector<bool>(p.size() + 1, false));
        match[0][0] = true;
        // 计算第一行
        for (int j = 1; j <= p.size(); ++j)
            match[0][j] = '*' == p[j - 1] && match[0][j - 2];
        //i和j从0开始，表示空串的情况，对于每个非0的i、j，s和p中对应的字符为s[i-1]和p[j-1]
        for (int i = 1; i <= s.size(); ++i)
            for (int j = 1; j <= p.size(); ++j) {
                if (j > 1 && p[j - 1] == '*')
                    //p的当前字符为*，可以匹配0次或者多次，0次即看s[0,i)和p[0,j-2)是否能匹配，多次即j不动，i-1重复多次
                    match[i][j] = match[i][j - 2] || (i > 0 && isMatchChar(s[i - 1], p[j - 2]) && match[i - 1][j]);
                else
                    //p的当前字符不是*，只能和p的当前字符匹配，并且在此之前的字符也必须能够匹配
                    match[i][j] = isMatchChar(s[i - 1], p[j - 1]) && i > 0 && match[i - 1][j - 1];
            }
        return match[s.size()][p.size()];
    }

private:
    bool isMatchChar(char s, char p) {
        return s == p || '.' == p;
    }
};

class Solution2 {
public:
    bool isMatch(const std::string &s, const std::string &p) {
        //动态规划改进版本，采用动态内存分配减小vector的开销，
        //注意：bool数组没有int数组快！
        int **match = new int*[s.size() + 1];
        int *raw = new int[(s.size() + 1) * (p.size() + 1)];
        for (int i = 0; i <= s.size(); ++i) {
            match[i] = raw + i * (p.size() + 1);
            //初始化第一列
            match[i][0] = 0;
        }
        match[0][0] = 1;
        //初始化第一行
        for (int j = 1; j <= p.size(); ++j)
            match[0][j] =  '*' == p[j - 1] && match[0][j - 2];
        //i和j从0开始，表示空串的情况，对于每个非0的i、j，s和p中对应的字符为s[i-1]和p[j-1]
        for (int i = 1; i <= s.size(); ++i)
            for (int j = 1; j <= p.size(); ++j) {
                if (isMatchChar(s[i - 1], p[j - 1]))
                    match[i][j] = match[i - 1][j - 1];
                else if (j > 1 && p[j - 1] == '*')
                    //p的当前字符为*，可以匹配0次或者多次，0次即看s[0,i)和p[0,j-2)是否能匹配，多次即j不动，i-1重复多次
                    match[i][j] = match[i][j - 2] || (isMatchChar(s[i - 1], p[j - 2]) && match[i - 1][j]);
                else
                    match[i][j] = 0;
            }
        bool result = match[s.size()][p.size()] != 0;
        delete [] match;
        delete [] raw;
        return result;
    }

private:
    bool isMatchChar(char s, char p) {
        return s == p || '.' == p;
    }
};

int main() {
    std::string s1 = "aa", p1 = "a"; //false
    std::string s2 = "aa", p2 = "a*"; //true
    std::string s3 = "ab", p3 = ".*"; //true
    std::string s4 = "aab", p4 = "c*a*b"; //true
    std::string s5 = "mississippi", p5 = "mis*is*p*."; //false

    Solution1 solution;
    std::cout << std::boolalpha
              << solution.isMatch(s1, p1) << std::endl
              << solution.isMatch(s2, p2) << std::endl
              << solution.isMatch(s3, p3) << std::endl
              << solution.isMatch(s4, p4) << std::endl
              << solution.isMatch(s5, p5) << std::endl;
    return 0;
}
