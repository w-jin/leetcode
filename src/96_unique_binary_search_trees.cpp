#include <iostream>

using std::cout;
using std::endl;

/*
 * 选择1~n内的任意一个数i作为根节点，则它的左边有i-1个节点，右边有n-i个节点，各自成树，问题
 * 被递归定义。设f(n)为n个节点的二叉搜索树的个数，则
 * f(n) = f(0)f(n-1) + f(1)f(n-2) + ... + f(n-2)f(1) + f(n-1)f(0)
 * 且f(0) = f(1) = 1
 * 这正是卡特兰数的递推式。所以
 * f(n) = C(2n, n) / (n+1)
 */
class Solution {
public:
    int numTrees(int n) {
        if (0 == n)
            return 0;

        long long fac_n = 1;
        for (int i = 2; i <= n; ++i)
            fac_n *= i;

        long long fac_2n_div_fac_n1 = 1;   // 如果用int在n=10时溢出，用long long在n=19时溢出
        for (int i = n + 2; i <= 2 * n; ++i)
            fac_2n_div_fac_n1 *= i;

        return static_cast<int>(fac_2n_div_fac_n1 / fac_n);
    }
};

/*
 * 为避免溢出，在计算组合数C(2n, n)时不能直接使用阶乘计算。
 * C(2n, n) = (2n)! / n! / n! = n*(n+1)*(n+2)*...*(2n) / (1*2*3*...*n)，
 * 分子首的项的乘积必能整除1，前两项的乘积必能整除2，前三项的乘积必能整除3，...
 * 因此每乘一项再除一项即可。
 */
class Solution1 {
public:
    int numTrees(int n) {
        if (0 == n)
            return 0;

        long long C_2n_n = 1;   // 用int在n=19时溢出
        for (int i = 1; i <= n; ++i) {
            C_2n_n *= (n + i);
            C_2n_n /= i;
        }

        return static_cast<int>(C_2n_n / (n + 1));
    }
};

int main() {
    // 5
    int n1 = 3;

    Solution1 solution;
    cout << solution.numTrees(n1) << endl;

    return 0;
}
