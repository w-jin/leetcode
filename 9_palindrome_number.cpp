#include <iostream>

/*
 * 反转后一半数字得到一个整数，将它与前一半数字比较即可知道是否是回文数字
 * 如1221反转后一半为12，与前一半(12)相等，因此是回文数字
 * 注意：将反转所有数字得到的整数与原数字比较也能得到结果，但可能溢出
 */
class Solution {
public:
    bool isPalindrome(int x) {
        if (x < 0 || (x != 0 && x % 10 == 0))
            return false;

        int reverse = 0;
        while (x > reverse) {
            reverse = reverse * 10 + x % 10;
            x = x / 10;
        }

        //1221这种偶数个数字的是x==reverse，12321这种奇数个数字的是x==reverse/10
        return x == reverse || x == reverse / 10;
    }
};

int main() {
    int x = 1221; //true
    Solution solution;
    std::cout << std::boolalpha << solution.isPalindrome(x) << std::endl;
    return 0;
}
