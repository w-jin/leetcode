#include <iostream>
#include <vector>
#include <string>

class Solution {
public:
    std::string multiply(const std::string &num1, const std::string &num2) {
        std::string result(num1.size() + num2.size(), '0');

        int carry = 0;
        int curr = 0;
        for (int i = static_cast<int>(num1.size()) - 1; i >= 0; --i) {
            for (int j = static_cast<int>(num2.size()) - 1; j >= 0; --j) {
                curr = (num1[i] - '0') * (num2[j] - '0') + result[i + j + 1] - '0' + carry;
                carry = curr / 10;
                result[i + j + 1] = static_cast<char>(curr % 10 + '0');
            }
            int j = i;
            while (carry != 0) {
                curr = result[j] - '0' + carry;
                carry = curr / 10;
                result[j] = static_cast<char>(curr % 10 + '0');
            }
        }

        //去掉多余的0
        unsigned int i = 0;
        while (i < result.size() && result[i] == '0')
            ++i;
        if (i == result.size())
            return "0";
        return result.substr(i);
    }
};

/* 上面的写法太丑 */
class Solution1 {
public:
    std::string multiply(const std::string &num1, const std::string &num2) {
        //各位乘出来
        std::vector<int> temp(num1.size() + num2.size(), 0);
        for (int i = 0; i < num1.size(); ++i) {
            for (int j = 0; j < num2.size(); ++j)
                temp[i + j + 1] += (num1[i] - '0') * (num2[j] - '0');
        }

        //进位
        int carry = 0, curr = 0;
        for (auto it = temp.rbegin(); it != temp.rend(); ++it) {
            curr = *it + carry;
            *it = curr % 10;
            carry = curr / 10;
        }

        //去掉多余的0，生成结果
        int i = 0;
        while (i < temp.size() && temp[i] == 0)
            ++i;
        if (i == temp.size())
            return "0";

        std::string result;
        while (i < temp.size())
            result.push_back(static_cast<char>(temp[i++] + '0'));
        return result;
    }
};

int main() {
    std::string num11 = "2", num21 = "3"; //6
    std::string num12 = "123", num22 = "456"; //56088
    std::string num13 = "0", num23 = "0"; //0

    Solution1 solution;
    std::cout << solution.multiply(num11, num21) << std::endl;
    std::cout << solution.multiply(num12, num22) << std::endl;
    std::cout << solution.multiply(num13, num23) << std::endl;

    return 0;
}
