#include <iostream>
#include <string>
#include <vector>

using std::cout;
using std::endl;
using std::string;
using std::vector;

class Solution {
public:
    bool isSubsequence(const string &s, const string &t) {
        int i = 0;
        int j = 0;
        while (i < s.size() && j < t.size()) {
            if (s[i] == t[j])
                ++i;
            ++j;
        }
        return i == s.size();
    }
};

int main() {
    // true
    string s1 = "abc";
    string t1 = "ahbgdc";

    // false
    string s2 = "axc";
    string t2 = "ahbgdc";

    Solution solution;
    cout << std::boolalpha;
    cout << solution.isSubsequence(s1, t1) << endl;
    cout << solution.isSubsequence(s2, t2) << endl;

    return 0;
}
