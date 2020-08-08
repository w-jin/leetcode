#include <iostream>

class Solution {
public:
    int reverse(int x) {
        /* 溢出的判定：
         * 正数：r*10 + Si > MAX => r > (MAX - Si) / 10，注意不能用Si > MAX - r*10，因为r*10可能溢出
         * 负数：r*10 + Si < MIN => r < (MIN - Si) / 10，注意此处除法应向0取整(c++11之前为依赖实现的行为)
         */
        int result = 0;
        while (x != 0) {
            if (x > 0 && result > (MAX - x % 10) / 10)
                return 0;   //溢出
            if (x < 0 && result < (MIN - x % 10) / 10)
                return 0;   //溢出
            result = result * 10 + x % 10;
            x /= 10;
        }

        return result;
    }

private:
    const int MAX = 0x7fffffff;
    const int MIN = 0x80000000;
};

int main()
{
    //-321
    int x = -123;
    Solution solution;
    std::cout << solution.reverse(x) << std::endl;
    return 0;
}
