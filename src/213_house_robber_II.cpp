#include <iostream>
#include <vector>

using std::cout;
using std::endl;
using std::vector;

class Solution {
public:
    int rob(const vector<int> &nums) {
        if (nums.empty())
            return 0;
        if (nums.size() == 1)
            return nums[0];
        const int n = static_cast<int>(nums.size());
        return std::max(rob(nums, 0, n - 1), rob(nums, 1, n));
    }

private:
    // 左闭右开区间[first, last)
    int rob(const vector<int> &nums, int first, int last) {
        if (first >= last)
            return 0;
        if (first + 1 == last)
            return nums[first];

        int prev2 = nums[first];
        int prev = std::max(nums[first], nums[first + 1]);
        for (int i = first + 2; i < last; ++i) {
            int t = std::max(prev, prev2 + nums[i]);
            prev2 = prev;
            prev = t;
        }
        return prev;
    }
};

int main() {
    // 3
    vector<int> nums1 = {2, 3, 2};

    // 4
    vector<int> nums2 = {1, 2, 3, 1};

    Solution solution;
    cout << solution.rob(nums1) << endl;
    cout << solution.rob(nums2) << endl;

    return 0;
}
