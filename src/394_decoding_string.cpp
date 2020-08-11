#include <iostream>
#include <string>
#include <stack>

using std::cout;
using std::endl;
using std::string;
using std::stack;

/*
* 时间复杂度O(|s| + |S|)，其中|s|和|S|分别为s和答案的长度。
* 空间复杂度O(|token|)，即[或者]的个数。
*/
class Solution {
public:
    string decodeString(const string &s) {
        string result;
        stack<int> times;   // 记录[前的数字
        int i = 0;
        while (i < s.size()) {
            // 出现一个数字就代表即将出现[，先将数字耗尽，计算出次数，它不一定马上使用，先记录下来
            if (isdigit(s[i])) {
                int digit = s[i] - '0';
                ++i;
                while (isdigit(s[i])) {
                    digit = 10 * digit + s[i] - '0';
                    ++i;
                }
                times.push(digit);
            } else if (']' == s[i]) {  // 查找最后一个[，将它到当前位置的子串弹出重复后再压入
                int sub_pos = result.find_last_of('[');
                string sub = result.substr(sub_pos + 1);
                result.erase(sub_pos);
                for (int j = 0; j < times.top(); ++j)
                    result += sub;
                times.pop();
                ++i;
            } else {
                result.push_back(s[i]);
                ++i;
            }
        }

        return result;
    }
};

int main() {
    // aaabcbc
    string s1 = "3[a]2[bc]";

    // accaccacc
    string s2 = "3[a2[c]]";

    // abcabccdcdcdef
    string s3 = "2[abc]3[cd]ef";

    // leetcode x 11
    string s4 = "11[leetcode]";

    Solution solution;
    cout << solution.decodeString(s1) << endl;
    cout << solution.decodeString(s2) << endl;
    cout << solution.decodeString(s3) << endl;
    cout << solution.decodeString(s4) << endl;

    return 0;
}
