#include <iostream>
#include <vector>
#include <limits>

class Solution {
public:
    int maxSubArray(std::vector<int> &nums) {
        int max_sub_sum = std::numeric_limits<int>::min();
        int sub_sum = 0;
        for (int num : nums) {
            sub_sum += num;
            if (sub_sum > max_sub_sum)
                max_sub_sum = sub_sum;
            if (sub_sum < 0)
                sub_sum = 0;
        }
        return max_sub_sum;
    }
};

class Solution1 {
public:
    int maxSubArray(std::vector<int> &nums) {
        if (nums.empty())
            return 0;
        int sum = nums[0];     // 表示以i结尾的子数组的最大和，f(i)=max{f(i-1)+ai, ai}
        int max_sum = nums[0];
        for (int i = 1; i < nums.size(); ++i) {
            sum = std::max(sum + nums[i], nums[i]);
            max_sum = std::max(max_sum, sum);
        }
        return max_sum;
    }
};

int main() {
    //6
    std::vector<int> nums = {-2, 1, -3, 4, -1, 2, 1, -5, 4};
    std::cout << Solution1().maxSubArray(nums) << std::endl;

    return 0;
}
