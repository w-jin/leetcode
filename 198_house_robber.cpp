#include <iostream>
#include <vector>

using std::cout;
using std::endl;
using std::vector;

/*
* 时间复杂度O(n)，空间复杂度O。
*/
class Solution {
public:
    int rob(vector<int> &nums) {
        if (nums.empty())
            return 0;
        if (nums.size() == 1)
            return nums[0];

        vector<int> max_rob(nums.size());
        max_rob[0] = nums[0];
        max_rob[1] = std::max(nums[0], nums[1]);
        for (int i = 2; i < nums.size(); ++i)
            max_rob[i] = std::max(max_rob[i - 1], max_rob[i - 2] + nums[i]);
        return max_rob.back();
    }
};

/*
* 优化空间。时间复杂度O(n)，空间复杂度O(1)。
*/
class Solution1 {
public:
    int rob(vector<int> &nums) {
        if (nums.empty())
            return 0;
        if (nums.size() == 1)
            return nums[0];

        int prev2 = nums[0];
        int prev = std::max(nums[0], nums[1]);
        for (int i = 2; i < nums.size(); ++i) {
            int t = std::max(prev, prev2 + nums[i]);
            prev2 = prev;
            prev = t;
        }
        return prev;
    }
};

int main() {
    // 4
    vector<int> nums1 = {1, 2, 3, 1};

    // 12
    vector<int> nums2 = {2, 7, 9, 3, 1};

    Solution1 solution;
    cout << solution.rob(nums1) << endl;
    cout << solution.rob(nums2) << endl;

    return 0;
}
