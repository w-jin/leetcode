#include <iostream>
#include <string>
#include <vector>

using std::cout;
using std::endl;
using std::string;
using std::vector;

class Solution {
public:
    int longestPalindrome(const string &s) {
        // 统计字母数量，只有大小写字母
        vector<int> alphabet(52, 0);

        for (char c : s) {
            if ('a' <= c && c <= 'z')
                ++alphabet[c - 'a'];
            else
                ++alphabet[c - 'A' + 26];
        }

        // 统计有多少个奇数
        int odd_count = 0;
        for (int n : alphabet) {
            if (n % 2 != 0)
                ++odd_count;
        }

        // 奇数个的字母拼成回文串时会剩一个，但回文串的中间可以有一个单独的字母
        int length = static_cast<int>(s.size());
        if (0 == odd_count)
            return length;
        else
            return length - odd_count + 1;
    }
};

int main() {
    // 7
    string s1 = "abccccdd";

    Solution solution;
    cout << solution.longestPalindrome(s1) << endl;

    return 0;
}
