#include <iostream>
#include <vector>
#include <algorithm>

using std::cout;
using std::endl;
using std::vector;

/*
    时间复杂度O(N)，空间复杂度O(N)。
*/
class Solution {
public:
    int massage(const vector<int> &nums) {
        if (nums.empty())
            return 0;
        if (nums.size() == 1)
            return nums[0];

        vector<int> dp(nums.size());
        dp[0] = nums[0];
        dp[1] = std::max(nums[0], nums[1]);
        for (int i = 2; i < dp.size(); ++i)
            dp[i] = std::max(dp[i - 1], dp[i - 2] + nums[i]);

        return dp.back();
    }
};

/*
    时间复杂度O(N)，空间复杂度O(1)。
*/
class Solution1 {
public:
    int massage(const vector<int> &nums) {
        if (nums.empty())
            return 0;
        if (nums.size() == 1)
            return nums[0];

        int last = nums[0];
        int curr = std::max(nums[0], nums[1]);
        for (int i = 2; i < nums.size(); ++i) {
            int next = std::max(curr, last + nums[i]);
            last = curr;
            curr = next;
        }

        return curr;
    }
};

int main() {
    // 4
    vector<int> nums1 = {1, 2, 3, 1};

    // 12
    vector<int> nums2 = {2, 7, 9, 3, 1};

    Solution1 solution;
    cout << solution.massage(nums1) << endl;
    cout << solution.massage(nums2) << endl;

    return 0;
}
