#include <iostream>
#include <string>

using std::cout;
using std::endl;
using std::string;

class Solution {
public:
    string reverseWords(const string &s) {
        string result;

        int i = static_cast<int>(s.size()) - 1;
        while (i >= 0) {
            // 跳过连续的空格
            while (i >= 0 && ' ' == s[i])
                --i;
            if (i < 0)
                break;

            // 查找下一个空格得到一个单词
            int j = i - 1;
            while (j >= 0 && ' ' != s[j])
                --j;
            result += s.substr(j + 1, i - j);
            result += ' ';
            i = j;
        }

        // 删除末尾可能存在的多余空格
        if (result.empty())
            return "";
        result.pop_back();
        return result;
    }
};

int main() {
    // blue is sky the
    string s1 = "the sky is blue";

    // world! hello
    string s2 = "  hello world!  ";

    // example good a
    string s3 = "a good   example";

    Solution solution;
    cout << solution.reverseWords(s1) << endl;
    cout << solution.reverseWords(s2) << endl;
    cout << solution.reverseWords(s3) << endl;

    return 0;
}
