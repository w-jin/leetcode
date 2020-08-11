#include <iostream>
#include <string>

using std::cout;
using std::endl;
using std::string;

class Solution {
public:
    bool validPalindrome(const string &s) {
        int i = 0;
        int j = static_cast<int>(s.size()) - 1;
        while (i < j) {
            if (s[i] == s[j]) {
                ++i;
                --j;
            } else {
                // 删除s[i]，或者删除s[j]
                return validPalindrome(s, i + 1, j) ||
                       validPalindrome(s, i, j - 1);
            }
        }
        return true;
    }

private:
    // 验证s[first, last]是否是回文串，不能更改s
    bool validPalindrome(const string &s, int first, int last) {
        while (first < last) {
            if (s[first] != s[last])
                return false;
            else {
                ++first;
                --last;
            }
        }
        return true;
    }
};

int main() {
    // true
    string s1 = "aba";

    // true
    string s2 = "abca";

    Solution solution;
    cout << std::boolalpha;
    cout << solution.validPalindrome(s1) << endl;
    cout << solution.validPalindrome(s2) << endl;

    return 0;
}
