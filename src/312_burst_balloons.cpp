#include <iostream>
#include <vector>

using std::cout;
using std::endl;
using std::vector;

/*
 * 暴力方法。时间复杂度O(n^n)，空间复杂度O(n)。
 */
class Solution {
public:
    int maxCoins(vector<int> &nums) {
        if (nums.empty())
            return 0;
        else if (nums.size() == 1)
            return nums[0];

        int result = 0;
        int i = 0;
        while (i < nums.size()) {
            if (nums[i] < 0) {
                ++i;
                continue;
            }

            // 标记nums[i]为-1以删除nums[i]，递归处理剩余的元素
            int temp = nums[i];
            nums[i] = -1;

            // 找左边第一个未删除的数
            int left = i - 1;
            while (left >= 0 && nums[left] < 0)
                --left;

            // 找右边第一个未删除的数
            int right = i + 1;
            while (right < nums.size() && nums[right] < 0)
                ++right;

            // 将连续的三个数乘起来
            int prod = temp;
            if (left >= 0)
                prod *= nums[left];
            if (right < nums.size())
                prod *= nums[right];

            // 递归处理剩余元素
            prod += maxCoins(nums);
            if (prod > result)
                result = prod;

            // 复原
            nums[i] = temp;

            // 下一个未删除的元素
            i = right;
        }

        return result;
    }
};


/*
 * 递归+备忘录。时间复杂度O(n^3)，空间复杂度O(n^2)。区间个数有n^2个，每个区间进行n次分割。
 */
class Solution1 {
public:
    int maxCoins(vector<int> &nums) {
        if (nums.empty())
            return 0;

        vector<int> nums2(nums.size() + 2);
        nums2[0] = nums2.back() = 1;
        for (int i = 1; i <= nums.size(); ++i)
            nums2[i] = nums[i - 1];

        vector<vector<int>> cache(nums2.size(), vector<int>(nums2.size(), 0));

        return maxCoins(nums2, 0, nums2.size() - 1, cache);
    }

private:
    int maxCoins(vector<int> &nums, int begin, int end, vector<vector<int>> &cache) {
        // 回归条件，问题分解到最小子问题
        if (begin == end - 1)
            return 0;

        // 缓存，避免重复计算
        if (cache[begin][end] != 0)
            return cache[begin][end];

        // 维护一个最大值
        int max_coins = 0;

        // 状态转移方程f(i, j) = max{f(i, k) + f(k, j) + nums[i]*nums[k]*nums[j]}, i<k<j
        for (int i = begin + 1; i < end; i++) {
            int temp = maxCoins(nums, begin, i, cache)
                       + maxCoins(nums, i, end, cache)
                       + nums[begin] * nums[i] * nums[end];  // 最后戳破nums[i]
            if (temp > max_coins)
                max_coins = temp;
        }

        // 缓存，避免重复计算
        cache[begin][end] = max_coins;

        return max_coins;
    }
};


/*
 * 动态规划。即Solution1更改计算次序。
 */
class Solution2 {
public:
    int maxCoins(const vector<int> &nums) {
        const int n = nums.size();

        vector<vector<int>> cache(n + 2, vector<int>(n + 2, 0));
        vector<int> val(n + 2);
        val[0] = val[n + 1] = 1;
        for (int i = 1; i <= n; ++i)
            val[i] = nums[i - 1];

        // 必须从后向前，i是区间起点，应当先计算长度为3的区间，然后是4，...
        for (int i = n + 1; i >= 0; --i) {
            for (int j = i + 2; j < n + 2; ++j) {
                for (int k = i + 1; k < j; ++k) {
                    int temp = val[i] * val[k] * val[j] + cache[i][k] + cache[k][j];
                    cache[i][j] = std::max(cache[i][j], temp);
                }
            }
        }

        // 也可以这样写。遍历可能的区间长度，比如当len为2时，区间为[i,i+2]，此时长度实际为3。
        // 为保证右边界不越界，必须满足i+len < n+2，即i<n+2-len
        // for (int len = 2; len < n + 2; ++len) {
        //     for (int i = 0; i < n + 2 - len; ++i) {
        //         for (int k = i + 1; k < i + len; ++k) {
        //             int temp = val[i] * val[k] * val[i + len] + cache[i][k] + cache[k][i + len];
        //             cache[i][i + len] = std::max(cache[i][i + len], temp);
        //         }
        //     }
        // }

        return cache[0][n + 1];
    }
};


int main() {
    // 167
    vector<int> nums1 = {3, 1, 5, 8};

    // 1654
    vector<int> nums2 = {7, 9, 8, 0, 7, 1, 3, 5, 5, 2, 3};

    Solution1 solution;
    cout << solution.maxCoins(nums1) << endl;
    cout << solution.maxCoins(nums2) << endl;

    return 0;
}
