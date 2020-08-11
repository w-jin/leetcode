#include <iostream>
#include <string>
#include <algorithm>

using std::cout;
using std::endl;
using std::string;

class Solution {
public:
    string addStrings(const string &num1, const string &num2) {
        // 保证num1比较短
        if (num1.size() < num2.size())
            return addStrings(num2, num1);

        string result(num1.size() + 1, 0);
        int carry = 0;

        int i = num1.size() - 1;
        int j = num2.size() - 1;
        int k = 0;
        while (j >= 0) {
            int curr = carry + (num1[i] - '0') + (num2[j] - '0');
            result[k++] = curr % 10 + '0';
            carry = curr / 10;
            --i;
            --j;
        }
        while (i >= 0) {
            int curr = carry + (num1[i] - '0');
            result[k++] = curr % 10 + '0';
            carry = curr / 10;
            --i;
        }
        if (carry > 0)
            result[k] = '1';
        else
            result.erase(result.begin() + k, result.end());

        std::reverse(result.begin(), result.end());

        return result;
    }
};

int main() {
    // 354824301772949654
    string num1_1 = "723334565476";
    string num2_1 = "354823578438384178";

    // 1132601301772949654
    string num1_2 = "777777723334565476";
    string num2_2 = "354823578438384178";

    Solution solution;
    cout << solution.addStrings(num1_1, num2_1) << endl;
    cout << solution.addStrings(num1_2, num2_2) << endl;

    return 0;
}
