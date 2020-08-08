#include <iostream>
#include <cmath>

/* 动态规划：有爬1步到n和爬2步到n两种情况，所以f[n]=f[n-1]+f[n-2]，即斐波拉契数列。 */
class Solution {
public:
    int climbStairs(int n) {
        int f0 = 1, f1 = 1;
        while (n >= 2) {
            int f2 = f0 + f1;
            f0 = f1;
            f1 = f2;
            --n;
        }
        return f1;
    }
};

/* 使用斐波拉契数列的通项公式来算 */
class Solution1 {
public:
    int climbStairs(int n) {
        double sqrt_5 = sqrt(5);
        double a1 = (1 + sqrt_5) / 2;
        double a2 = (1 - sqrt_5) / 2;
        return static_cast<int>(1 / sqrt_5 * (pow(a1, n + 1) - pow(a2, n + 1)) + 0.5);
    }
};

int main() {
    Solution1 solution;
    std::cout << solution.climbStairs(2) << std::endl; //2
    std::cout << solution.climbStairs(3) << std::endl; //3
    return 0;
}
