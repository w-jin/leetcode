#include <iostream>
#include <vector>
#include <unordered_map>

using std::vector;

/*
 * 时间复杂度O(n^2)，超出时间限制。
 */
class Solution {
public:
    int subarraySum(const vector<int> &nums, int k) {
        if (nums.empty())
            return 0;

        int count = 0;
        for (int i = 0; i < nums.size(); ++i) {
            int sum = 0;
            for (int j = i; j < nums.size(); ++j) {
                sum += nums[j];
                if (sum == k)
                    ++count;
            }
        }

        return count;
    }
};

class Solution1 {
public:
    int subarraySum(const vector<int> &nums, int k) {
        int count = 0;
        std::unordered_map<int, int> prefix_sum = {{0, 1}};
        int sum = 0;
        for (int num : nums) {
            sum += num;
            if (prefix_sum.find(sum - k) != prefix_sum.end())
                count += prefix_sum[sum - k];
            ++prefix_sum[sum];
        }
        return count;
    }
};

int main() {
    // 2
    vector<int> nums1 = {1, 1, 1};
    int k1 = 2;

    // 2
    vector<int> nums2 = {1, 2, 3};
    int k2 = 3;

    Solution1 solution;
    std::cout << solution.subarraySum(nums1, k1) << std::endl;
    std::cout << solution.subarraySum(nums2, k2) << std::endl;

    return 0;
}
