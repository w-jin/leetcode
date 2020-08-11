#include <iostream>
#include <string>

using std::cout;
using std::endl;
using std::string;

class Solution {
public:
    bool patternMatching(string pattern, string value) {
        int count_a = 0, count_b = 0;
        for (char ch: pattern) {
            if (ch == 'a') {
                ++count_a;
            } else {
                ++count_b;
            }
        }
        if (count_a < count_b) {
            std::swap(count_a, count_b);
            for (char& ch: pattern) {
                ch = (ch == 'a' ? 'b' : 'a');
            }
        }
        if (value.empty()) {
            return count_b == 0;
        }
        if (pattern.empty()) {
            return false;
        }
        for (int len_a = 0; count_a * len_a <= value.size(); ++len_a) {
            int rest = value.size() - count_a * len_a;
            if ((count_b == 0 && rest == 0) || (count_b != 0 && rest % count_b == 0)) {
                int len_b = (count_b == 0 ? 0 : rest / count_b);
                int pos = 0;
                bool correct = true;
                string value_a, value_b;
                for (char ch: pattern) {
                    if (ch == 'a') {
                        string sub = value.substr(pos, len_a);
                        if (!value_a.size()) {
                            value_a = move(sub);
                        } else if (value_a != sub) {
                            correct = false;
                            break;
                        }
                        pos += len_a;
                    } else {
                        string sub = value.substr(pos, len_b);
                        if (!value_b.size()) {
                            value_b = move(sub);
                        } else if (value_b != sub) {
                            correct = false;
                            break;
                        }
                        pos += len_b;
                    }
                }
                if (correct && value_a != value_b) {
                    return true;
                }
            }
        }
        return false;
    }
};

int main() {
    // true
    string pattern1 = "abba", value1 = "dogcatcatdog";

    // false
    string pattern2 = "abba", value2 = "dogcatcatfish";

    // false
    string pattern3 = "aaaa", value3 = "dogcatcatdog";

    // true
    string pattern4 = "abba", value4 = "dogdogdogdog";

    Solution solution;
    cout << std::boolalpha;
    cout << solution.patternMatching(pattern1, value1) << endl;
    cout << solution.patternMatching(pattern2, value2) << endl;
    cout << solution.patternMatching(pattern3, value3) << endl;
    cout << solution.patternMatching(pattern4, value4) << endl;

    return 0;
}
