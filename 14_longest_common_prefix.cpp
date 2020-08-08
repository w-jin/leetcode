#include <iostream>
#include <string>
#include <vector>

using std::string;
using std::vector;

class Solution {
public:
    std::string longestCommonPrefix(std::vector<std::string> &strs) {
        if (strs.empty())
            return "";

        std::string prefix;
        for (int i = 0; i < strs[0].size(); ++i) {
            char curr = strs[0][i];
            for (int j = 1; j < strs.size(); ++j) {
                if (curr != strs[j][i])
                    return prefix;
            }
            prefix.push_back(curr);
        }

        return prefix;
    }
};

class Solution1 {
public:
    string longestCommonPrefix(vector<string>& strs) {
        if (strs.empty())
            return "";
        int i = 0;
        for (i = 0; i < strs[0].size(); ++i) {
            char c = strs[0][i];
            int n = 1;
            while (n < strs.size() && i < strs[n].size() && strs[n][i] == c)
                ++n;
            if (n != strs.size())
                break;
        }
        return strs[0].substr(0, i);
    }
};

int main() {
    // fl
    std::vector<std::string> strs1 = {"flower", "flow", "flight"};
    std::vector<std::string> strs2 = {"dog", "race-car", "car"};

    Solution solution;
    std::cout << solution.longestCommonPrefix(strs1) << std::endl;
    std::cout << solution.longestCommonPrefix(strs2) << std::endl;

    return 0;
}
