#include <iostream>
#include <string>
#include <algorithm>

using std::string;

class Solution {
public:
    string reverseWords(string s) {
        int i = 0;
        while (i < s.size()) {
            // 跳过空白
            while (i < s.size() && s[i] == ' ')
                ++i;
            if (i == s.size())
                break;

            // 找到单词后面的第一个空白
            int j = i + 1;
            while (j < s.size() && s[j] != ' ')
                ++j;

            // 反转s[i,...j)
            int left = i;
            int right = j - 1;
            while (left < right) {
                std::swap(s[left], s[right]);
                ++left;
                --right;
            }
            // std::reverse(s.begin() + i, s.begin() + j);

            i = j + 1;
        }

        return s;
    }
};

int main() {
    // s'teL ekat edoCteeL tsetnoc
    string s1 = "Let's take LeetCode contest";

    Solution solution;
    std::cout << solution.reverseWords(s1) << std::endl;

    return 0;
}
