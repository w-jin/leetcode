#include <iostream>
#include <string>

using std::cout;
using std::endl;
using std::string;

class Solution {
public:
    int countBinarySubstrings(const string &s) {
        int result = 0;
        int prev = 0;
        int curr = 1;
        for (int i = 1; i < s.size(); ++i) {
            if (s[i] == s[i - 1])
                ++curr;
            else {
                result += std::min(prev, curr);
                prev = curr;
                curr = 1;
            }
        }
        result += std::min(prev, curr);

        return result;
    }
};

int main() {
    // 6
    string s1 = "00110011";

    // 4
    string s2 = "10101";

    Solution solution;
    cout << solution.countBinarySubstrings(s1) << endl;
    cout << solution.countBinarySubstrings(s2) << endl;

    return 0;
}
