#include <iostream>
#include <string>
#include <algorithm>

class Solution {
public:
    std::string addBinary(const std::string &a, const std::string &b) {
        int i = static_cast<int>(a.size()) - 1, j = static_cast<int>(b.size()) - 1;
        int carry = 0;
        std::string sum;
        while (i >= 0 && j >= 0) {
            int curr = a[i] - '0' + b[j] - '0' + carry;
            sum.push_back(static_cast<char>(curr % 2 + '0'));
            carry = curr / 2;
            --i;
            --j;
        }
        while (i >= 0) {
            int curr = a[i] - '0' + carry;
            sum.push_back(static_cast<char>(curr % 2 + '0'));
            carry = curr / 2;
            --i;
        }
        while (j >= 0) {
            int curr = b[j] - '0' + carry;
            sum.push_back(static_cast<char>(curr % 2 + '0'));
            carry = curr / 2;
            --j;
        }
        if (carry != 0)
            sum.push_back('1');

        std::reverse(sum.begin(), sum.end());

        return sum;
    }
};

class Solution1 {
public:
    std::string addBinary(const std::string &a, const std::string &b) {
        int carry = 0;
        int i = static_cast<int>(a.size()) - 1;
        int j = static_cast<int>(b.size()) - 1;
        std::string sum;
        while (i >= 0 || j >= 0 || carry > 0) {
            carry += (i >= 0) ? a[i--] - '0' : 0;
            carry += (j >= 0) ? b[j--] - '0' : 0;
            sum.push_back(static_cast<char>(carry % 2 + '0'));
            carry /= 2;
        }
        std::reverse(sum.begin(), sum.end());
        return sum;
    }
};

int main() {
    std::string a1 = "11", b1 = "1"; //100
    std::string a2 = "1010", b2 = "1011"; //10101

    Solution solution;
    std::cout << solution.addBinary(a1, b1) << std::endl;
    std::cout << solution.addBinary(a2, b2) << std::endl;

    return 0;
}
