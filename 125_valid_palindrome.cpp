#include <iostream>
#include <string>

using std::cout;
using std::endl;
using std::string;

class Solution {
public:
    bool isPalindrome(const string &s) {
        int i = 0;
        int j = static_cast<int>(s.size()) - 1;
        while (i < j) {
            while (i < j && !isalpha(s[i]) && !isdigit(s[i]))
                ++i;
            while (i < j && !isalpha(s[j]) && !isdigit(s[j]))
                --j;
            if (i == j)
                break;
            if (tolower(s[i]) != tolower(s[j]))
                return false;
            else {
                ++i;
                --j;
            }
        }

        return true;
    }
};

int main() {
    // true
    string s1 = "A man, a plan, a canal: Panama";

    // false
    string s2 = "race a car";

    Solution solution;
    cout << std::boolalpha;
    cout << solution.isPalindrome(s1) << endl;
    cout << solution.isPalindrome(s2) << endl;

    return 0;
}
