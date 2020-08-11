#include <iostream>
#include <string>

class Solution {
public:
    int myAtoi(const std::string &str) {
        int result = 0;
        bool isNegative = false;
        int i = 0;
        //跳过开头的空白
        while (' ' == str[i])
            ++i;
        //判断正负号
        if ('-' == str[i]) {
            isNegative = true;
            ++i;
        }
        else if ('+' == str[i])
            ++i;
        //读取数字
        while ('0' <= str[i] && str[i] <= '9') {
            if (isNegative) {
                if (result < (MIN + (str[i] - '0')) / 10)
                    return MIN; //溢出
                result = result * 10 - (str[i] - '0');
            }
            else {
                if (result > (MAX - (str[i] - '0')) / 10)
                    return MAX; //溢出
                result = result * 10 + (str[i] - '0');
            }
            ++i;
        }

        return result;
    }

private:
    const int MAX = 0x7fffffff;
    const int MIN = 0x80000000;
};

int main()
{
    //4193
    std::string str = " 4193 with words";
    Solution solution;
    std::cout << solution.myAtoi(str) << std::endl;
    return 0;
}
