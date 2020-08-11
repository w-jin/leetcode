#include <iostream>
#include <cmath>

class Solution {
public:
    int integerBreak(int n) {
        if (2 == n)
            return 1;
        else if (3 == n)
            return 2;
        else if (4 == n)
            return 4;
        else {
            int m = n / 3;
            int r = n % 3;
            if (1 == r)
                return powl(3, m - 1) * 4;
            else if (2 == r)
                return powl(3, m) * 2;
            else
                return powl(3, m);
        }
    }
};

int main() {
    // 36
    int n1 = 10;

    Solution solution;
    std::cout << solution.integerBreak(n1) << std::endl;

    return 0;
}
