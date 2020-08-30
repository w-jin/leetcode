#include <iostream>

using std::cout;
using std::endl;

/*
 * 求[m, n]内所有数字按位与的结果，实际上不需要遍历每个数。假定m和n的二进制位中某位不同，由于
 * 相邻两个数是加1得到的，所以中间必须有一个数的低位是11...11，然后加1变成00...00，它们与的
 * 结果为00...00，比如[9, 14]，二进制为[1001, 1110]，次高位不同，则区间内符合上面情况的数
 * 是11，二进制为1011，加1变成12即1100，11和12按位与的结果为1000。又9和14的最高位一样，因
 * 此整个区间内所有数的最高位都是1，所以范围按位与的结果是1000，即8。
 * 对于任意情况，就是将m和n的二进制中最长前缀找出来，可以将m和n同时右移，直到它们相等，再将结
 * 果左移即可将低位置0。
 * 时间复杂度O(1)，空间复杂度O(1)。
 */
class Solution {
public:
    int rangeBitwiseAnd(int m, int n) {
        if (m > n)
            return 0;

        int c = 0;
        while (m != n) {
            m = m >> 1;
            n = n >> 1;
            ++c;
        }

        return m << c;
    }
};

/*
 * 为求出m和n的二进制的最长前缀，实际上不需要逐位右移，可以不断将n的最右一个1变成0直到n小于等
 * 于m时，则n就是所求。
 * 将n的最右一个1变成0有两种做法：
 *  1、使用n & (-n)将最右一个1找出来，然后减掉，即n = n - (n & -n)。
 *  2、Brian Kernighan算法：n = n & (n - 1)。比如n = 12 = 0b1100，则n-1 = 0b1011，
 *    两者按位与的结果为n & (n-1) = 0b1000。
 */
class Solution1 {
public:
    int rangeBitwiseAnd(int m, int n) {
        while (m < n) {
            // n -= n & (-n);
            n = n & (n - 1);
        }
        return n;
    }
};

int main() {
    // 4
    int m1 = 5;
    int n1 = 7;

    // 0
    int m2 = 0;
    int n2 = 1;

    Solution1 solution;
    cout << solution.rangeBitwiseAnd(m1, n1) << endl;
    cout << solution.rangeBitwiseAnd(m2, n2) << endl;

    return 0;
}
