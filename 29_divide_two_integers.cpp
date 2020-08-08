#include <iostream>
#include <climits>

class Solution {
public:
    int divide(int dividend, int divisor) {
        if (dividend == INT_MIN && divisor == -1)
            return INT_MAX;
        if (divisor == -1)
            return -dividend;
        
        //处理符号，负数结果转化为正数来算，但是INT_MIN转化为正数将上溢，必须以long long来保存
        long long positive_dividend = dividend;
        long long positive_divisor = divisor;
        bool is_positive = true;
        if (dividend < 0) {
            is_positive = !is_positive;
            positive_dividend = -positive_dividend;
        }
        if (divisor < 0) {
            is_positive = !is_positive;
            positive_divisor = -positive_divisor;
        }

        int result = 0;
        while (positive_dividend >= positive_divisor) {
            int i = 1;
            while (positive_dividend >= (positive_divisor << i))
                ++i;
            --i;
            positive_dividend -= (positive_divisor << i);
            result += (1 << i);
        }

        return is_positive ? result : -result;
    }
};

int main()
{
    int dividend1 = 10, divisor1 = 3; //3
    int dividend2 = 7, divisor2 = -3; //-2
    int dividend3 = 0x80000000, divisor3 = -1; //溢出

    Solution solution;

    std::cout << dividend1 << " / " << divisor1 << " = " << 
            solution.divide(dividend1, divisor1) << std::endl;
    std::cout << dividend2 << " / " << divisor2 << " = " <<
            solution.divide(dividend2, divisor2) << std::endl;
    std::cout << dividend3 << " / " << divisor3 << " = " <<
            solution.divide(dividend3, divisor3) << std::endl;
    
    return 0;
}
