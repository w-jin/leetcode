#include <iostream>
#include <vector>
#include <algorithm>
#include <functional>

using std::vector;

/*
 * 错误的思路：用f(l, r)来表示移除区间[l, r]内所有的盒子能得到的最大积分，无最优子结构！
 *
 * 使用f(l, r, k)表示区间A[l, ..., r]及r右侧等于A[r]的k个元素组成的序列可以得到的最大分数。
 * 那么有：
 *   f(l, r, k) = max{
 *      f(l, r-1, 0) + (k+1)^2,  // 将Ar和右侧的k个元素去掉
 *      max_{i=l, i<r, A[i]==A[r]} {f(l, i, k + 1) + f(i+1, r-1, 0)} // 去掉A[i+1, ..., r-1]
 *   }
 * 递归递归计算加上缓存即可。需要注意：1、k增大不影响收敛性，只要区间[l, r]的长度缩小就可以收敛，
 * 不会死循环。
 *
 * 优化：
 * 1、如果区间A[l, ..., r]的尾部有多个与A[r]相等的元素，如..., x, x, A[r]=x, ...，则
 *   可以将这些x一起统计到区间右侧x的个数中，以缩小区间长度。这是因为(k+m)^2 > k^2 + m^2。
 * 2、使用静态数组比vector快。
 * 3、遍历i时可以只取连续相同元素的最右一个来算，比如x, x, y, ..., A[r]=x，两个连续的x中可
 *   以只取第二个来算，但几乎没什么效果。
 * 4、当A[r]前面有许多和A[r]相等的元素时可以将区间的边界向左缩小，缩小过程中可以检查是否有计
 *   算过的dp[l][r][k]，如果有则直接返回，但几乎没有什么效果。
 */
class Solution {
public:
    int removeBoxes(const vector<int> &boxes) {
        if (boxes.empty())
            return 0;

        int dp[100][100][100] = {0};

        std::function<int(int, int, int)> removeBoxesRecursive;
        removeBoxesRecursive = [&removeBoxesRecursive, &boxes, &dp](
                int l, int r, int k) -> int {
            if (l > r)
                return 0;
            if (dp[l][r][k] != 0)
                return dp[l][r][k];
            while (r > l && boxes[r] == boxes[r - 1]) {
                --r;
                ++k;
            }

            dp[l][r][k] = removeBoxesRecursive(l, r - 1, 0) + (k + 1) * (k + 1);
            for (int i = l; i < r; ++i) {
                if (boxes[i] == boxes[r]) {
                    dp[l][r][k] = std::max(
                            dp[l][r][k],
                            removeBoxesRecursive(l, i, k + 1)
                                + removeBoxesRecursive(i + 1, r - 1, 0)
                    );
                }
            }
            return dp[l][r][k];
        };

        return removeBoxesRecursive(0, boxes.size() - 1, 0);
    }
};

int main() {
    // 23
    vector<int> boxes1 = {1, 3, 2, 2, 2, 3, 4, 3, 1};

    Solution solution;
    std::cout << solution.removeBoxes(boxes1) << std::endl;

    return 0;
}
