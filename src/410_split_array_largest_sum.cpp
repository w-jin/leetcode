#include <iostream>
#include <vector>
#include <functional>
#include <climits>

using std::cout;
using std::endl;
using std::vector;

/*
 * 暴力解法。时间复杂度O(n^m)，即使将区间的和缓存下来也无济于事。空间复杂度O(m)。
 * 超时！
 */
class Solution {
public:
    int splitArray(const vector<int> &nums, int m) {
        std::function<int(int, int, int)> f;
        f = [&f, &nums](int first, int last, int m) -> int {
            int interval_sum = 0;
            if (1 == m) {
                for (int i = first; i <= last; ++i)
                    interval_sum += nums[i];
                return interval_sum;
            }

            // 第一次划分在i的后面
            int min_sum = INT_MAX;
            for (int i = first; i <= last - m + 1; ++i) {
                interval_sum += nums[i];
                min_sum = std::min(min_sum,
                                   std::max(interval_sum, f(i + 1, last, m - 1)));
            }

            return min_sum;
        };

        return f(0, nums.size() - 1, m);
    }
};

/*
 * 动态规划。以dp[m][i][j]表示数组nums[i...j]划分m段的结果。
 * 时间复杂度O(m*n^3)，空间复杂度O(m*n^2)。
 * 超时！
 */
class Solution1 {
public:
    int splitArray(const vector<int> &nums, int m) {
        vector<vector<vector<long long>>> dp(m + 1,
                                             vector<vector<long long>>(nums.size(), vector<long long>(nums.size())));
        for (int i = 0; i < nums.size(); ++i) {
            dp[1][i][i] = nums[i];
            for (int j = i + 1; j < nums.size(); ++j)
                dp[1][i][j] = dp[1][i][j - 1] + nums[j];
        }

        for (int n = 2; n <= m; ++n) {
            // 计算区间nums[i...j]划分n段的结果
            for (int i = 0; i < nums.size(); ++i) {
                for (int j = i + n - 1; j < nums.size(); ++j) {
                    // 从k后面划分
                    dp[n][i][j] = LONG_LONG_MAX;
                    for (int k = i; k <= j - n + 1; ++k)
                        dp[n][i][j] = std::min(dp[n][i][j], std::max(dp[1][i][k], dp[n - 1][k + 1][j]));
                }
            }
        }

        return dp[m][0][nums.size() - 1];
    }
};

/*
 * 动态规划。以dp[i][j]表示数组前i个数分割为j段得到的结果。
 * 时间复杂度O(m*n^2)，空间复杂度O(m*n)。
 */
class Solution2 {
public:
    int splitArray(const vector<int> &nums, int m) {
        const int n = nums.size();

        vector<vector<long long>> dp(m + 1, vector<long long>(n));
        dp[1][0] = nums[0];
        for (int j = 1; j < n; ++j)
            dp[1][j] = dp[1][j - 1] + nums[j];

        for (int i = 2; i <= m; ++i) {
            for (int j = i - 1; j < n; ++j) {
                // 在k前面划分
                dp[i][j] = LONG_LONG_MAX;
                long long temp_sum = 0;
                for (int k = j; k >= i - 1; --k) {
                    temp_sum += nums[k];
                    dp[i][j] = std::min(dp[i][j], std::max(temp_sum, dp[i - 1][k - 1]));
                }
            }
        }

        return dp[m][nums.size() - 1];
    }
};

/*
 * 二分查找。对选定的某个值x，需要所有子数组的和都小于等于它，且至少一个子数组的和刚好为x，则x
 * 为所求。对选定的某个值x，要求子数组都不超过x，求最少分割次数。由于数组元素非负，因此可以使用
 * 贪心算法来求最小分割次数，如果最小分割次数小于等于m，则x过大，下次到左半区间查找，如果最小分
 * 割次数大于m，则x过小，下次到右半区间查找。需要注意最小分割次数等于m时，当前x可能是待求结果，
 * 所以缩小后的区间也要包含它。
 * 二分的上界为数组所有元素的和(分割为1段)，下界为数组元素最大值(分割为n段)。
 * 时间复杂度O(n log(sum - max))，空间复杂度O(1)。
 */
class Solution3 {
public:
    bool check(vector<int> &nums, int x, int m) {
        long long sum = 0;
        int cnt = 1;
        for (int num : nums) {
            if (sum + num > x) {
                cnt++;
                sum = num;
            } else {
                sum += num;
            }
        }
        return cnt <= m;
    }

    int splitArray(vector<int> &nums, int m) {
        long long left = 0, right = 0;
        for (int num : nums) {
            right += num;
            if (left < num) {
                left = num;
            }
        }
        while (left < right) {
            long long mid = left + (right - left) / 2;
            if (check(nums, mid, m)) {
                right = mid;
            } else {
                left = mid + 1;
            }
        }
        return left;
    }
};

int main() {
    // 18
    vector<int> nums1 = {7, 2, 5, 10, 8};
    int m1 = 2;

    // 2147483647
    vector<int> nums2 = {1, 2147483647};
    int m2 = 2;

    Solution3 solution;
    cout << solution.splitArray(nums1, m1) << endl;
    cout << solution.splitArray(nums2, m2) << endl;

    return 0;
}
