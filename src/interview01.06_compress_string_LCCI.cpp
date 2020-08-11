#include <iostream>
#include <string>

using std::cout;
using std::endl;
using std::string;

class Solution {
public:
    string compressString(const string &s) {
        string compressed_s;
        int i = 0;
        while (i < s.size()) {
            int j = i + 1;
            while (j < s.size() && s[j] == s[i])
                ++j;
            compressed_s += s[i];
            compressed_s += std::to_string(j - i);
            i = j;
        }

        return compressed_s.size() < s.size() ? compressed_s : s;
    }
};

int main() {
    // a2b1c5a3
    string s1 = "aabcccccaaa";

    // abbccd
    string s2 = "abbccd";

    Solution solution;
    cout << solution.compressString(s1) << endl;
    cout << solution.compressString(s2) << endl;

    return 0;
}
