#include <iostream>

using std::cout;
using std::endl;

/*
    考虑每次删除一个元素，然后对剩余元素重新编号，如
    N = 5, m = 3，元素序列为0, 1, 2, 3, 4，第一个删除2，然后重新编号为2, 3, -, 0, 1，
    再下一次仍然删除编号为2的元素，依此类推，直到最后只剩余一个元素，此元素编号必然为0，现在考虑
    它在上一次的编号是多少。
    首先，假定长度为n，则删除的元素的编号必然为m % N，然后剩余n-1个元素，假定这n-1个元素的幸存者
    编号为x，则它在长度为n的序列中的编号为m%N + x，它有可能超出n，超出n时应当回到序列开头，所以
    应当为(m%N + x) % N。因此使用这个表达式递推到序列长度为n的情况即可。
    时间复杂度O(N)，空间复杂度O(1)。
*/
class Solution {
public:
    int lastRemaining(int n, int m) {
        int f = 0;  // f(1, m)
        for (int i = 2; i <= n; ++i)
            f = (f + m) % i;
        return f;
    }
};

int main() {
    // 3
    int n1 = 5;
    int m1 = 3;

    // 2
    int n2 = 10;
    int m2 = 17;

    Solution solution;
    cout << solution.lastRemaining(n1, m1) << endl;
    cout << solution.lastRemaining(n2, m2) << endl;

    return 0;
}
