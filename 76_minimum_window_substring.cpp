#include <iostream>
#include <string>
#include <unordered_map>
#include <climits>

class Solution {
public:
    bool include(const std::unordered_map<char, int> &alphabet_s,
                 const std::unordered_map<char, int> &alphabet_t) {
        for (auto i = alphabet_t.begin(); i != alphabet_t.end(); ++i) {
            auto j = alphabet_s.find(i->first);
            if (j == alphabet_s.end() || j->second < i->second)
                return false;
        }
        return true;
    }

    std::string minWindow(const std::string &s, const std::string &t) {
        if (t.empty())
            return "";

        std::unordered_map<char, int> alphabet_t, alphabet_s;

        // 统计t中的字母
        for (int i = 0; i < t.size(); ++i)
            ++alphabet_t[t[i]];

        // 以滑动窗口逐个记录子串的字符数
        std::string min_substring;
        int curr_min = INT_MAX;
        int i = 0, j = 0;    // 窗口为[j, i]
        for (i = 0; i < s.size(); ++i) {
            if (alphabet_t.find(s[i]) == alphabet_t.end())
                continue;
            ++alphabet_s[s[i]];

            // 窗口左边界右移
            while (j < i && (alphabet_t.find(s[j]) == alphabet_t.end() ||
                             alphabet_s[s[j]] > alphabet_t[s[j]])) {
                if (alphabet_t.find(s[j]) != alphabet_t.end())
                    --alphabet_s[s[j]];
                ++j;
            }

            if (include(alphabet_s, alphabet_t) && i - j + 1 < curr_min) {
                curr_min = i - j + 1;
                min_substring = s.substr(j, curr_min);
            }
        }

        if (include(alphabet_s, alphabet_t))
            return min_substring;
        return "";     // s不包含t
    }
};

/*
    假定t中的字符不重复
*/
class Solution1 {
public:
    std::string minWindow(const std::string &s, const std::string &t) {
        if (t.empty())
            return "";

        int map[128] = {0};
        for (auto c : t)
            ++map[c];

        int i = 0, j = 0;
        int count = t.size();
        int start = 0;
        int curr_min = INT_MAX;
        for (i = 0; i < s.size(); ++i) {
            if (map[s[i]]-- > 0)
                --count;
            while (count == 0) {
                if (curr_min > i - j + 1) {
                    start = j;
                    curr_min = i - j + 1;
                }
                if (map[s[j++]]++ == 0)
                    ++count;
            }
        }

        return curr_min == INT_MAX ? "" : s.substr(start, curr_min);
    }
};

int main() {
    // "BANC"
    std::string s1 = "ADOBECODEBANC", t1 = "ABC";

    Solution1 solution;
    std::cout << solution.minWindow(s1, t1) << std::endl;

    return 0;
}
