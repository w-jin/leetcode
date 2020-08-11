#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

class Solution {
public:
    std::string longestPalindrome(std::string s) {
        //从中心开始向两边搜索，共有2n-1个中心，时间复杂度O(n^2)，空间复杂度O(1)
        int start = 0, end = 0; //回文串始末位置
        int max_len = 0; //回文串最大长度
        //以字母s[i]为中心
        for (int i = 0; i < s.size(); ++i) {
            int width = 1;
            while (i - width >= 0 && i + width < s.size() && s[i - width] == s[i + width])
                ++width;
            if (max_len < 2 * width - 1) {
                start = i - width + 1;
                end = i + width - 1;
                max_len = 2 * width - 1;
            }
        }
        //以字母s[i-1]和s[i]的中点为中心
        for (int i = 1; i < s.size(); ++i) {
            int width = 0;
            while (i - 1 - width >= 0 && i + width < s.size() && s[i - 1 - width] == s[i + width])
                ++width;
            if (max_len < 2 * width) {
                start = i - width;
                end = i + width - 1;
                max_len = 2 * width;
            }
        }

        return std::string(s.begin() + start, s.begin() + end + 1);
    }
};

class Solution1 {
public:
    std::string longestPalindrome(std::string s) {
        //使用manacher算法改进搜索的次数，时间复杂度O(n)，空间复杂度O(n)
        if (s.empty())
            return "";

        //每个字符间插入'\0'
        std::string str(2 * s.size() + 1, '\0');
        for (int i = 0; i < s.size(); ++i)
            str[2 * i + 1]  = s[i];

        //求出每个字符的RL，RL[i]表示以str[i]为中心的最长回文串最右一个字符与i的距离，如"#a#b#a#"，RL['b']=3，
        //所以以b为中心的最长回文串长度为3
        std::vector<int> RL(str.size(), 0);
        int max_right = -1; //当前回文串所触及的最远下标
        int pos = -1;       //当前回文串所触及的最远下标的回文串中心
        int max_len_i = -1; //最长回文串中心的下标
        for (int i = 0; i < str.size(); ++i) {
            if (i < max_right)
                RL[i] = std::min(RL[2 * pos - i], max_right - i);
            else
                RL[i] = 1;
            
            while (i - RL[i] >= 0 && i + RL[i] < str.size() && str[i - RL[i]] == str[i + RL[i]])
                ++RL[i];
            --RL[i];

            if (i + RL[i] > max_right) {
                max_right = i + RL[i];
                pos = i;
            }

            if (max_len_i < 0)
                max_len_i = i;
            else if (RL[max_len_i] < RL[i])
                max_len_i = i;
        }

        /*
        std::string result;
        for (int i = max_len_i - RL[max_len_i]; i <= max_len_i + RL[max_len_i]; ++i)
            if (str[i] != '\0')
                result.push_back(str[i]);
        return result;
        */

        //与上面那个几乎没有性能差距
        int start = (max_len_i - RL[max_len_i]) / 2;
        int end = (max_len_i + RL[max_len_i] - 1) / 2;
        return std::string(s.begin() + start, s.begin() + end + 1);
    }
};

int main()
{
    //bab
    std::string str = "babad";
    Solution1 solution;
    std::cout << solution.longestPalindrome(str) << std::endl;
    return 0;
}
