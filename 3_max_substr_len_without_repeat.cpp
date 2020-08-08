#include <iostream>
#include <string>

class Solution {
public:
    int lengthOfLongestSubstring(const std::string &s) {
        int max_len = 0;
        bool repeat[127] = {false};
        int i = 0, j = 0;
        while (j < s.size()) {
            while (repeat[s[j]]) {
                repeat[s[i]] = false;
                ++i;
            }
            if (j - i + 1 > max_len)
                max_len = j - i + 1;
            repeat[s[j]] = true;
            ++j;
        }
        return max_len;
    }
};

int main()
{
    //3
    std::string str = "abcabcbb";
    Solution solution;
    std::cout << solution.lengthOfLongestSubstring(str) << std::endl;

    return 0;
}
