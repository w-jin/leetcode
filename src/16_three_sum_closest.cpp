#include <iostream>
#include <vector>
#include <algorithm>

class Solution {
public:
    int threeSumClosest(std::vector<int> &nums, int target) {
        if (nums.size() < 3)
            return 0;
        std::sort(nums.begin(), nums.end());

        int min_gap = 0x7fffffff;
        int closest_sum = 0;
        for (size_t i = 0; i < nums.size() - 2; ++i) {
            size_t j = i + 1, k = nums.size() - 1;
            while (j < k) {
                int sum = nums[i] + nums[j] + nums[k];
                if (sum == target)
                    return target;
                else if (sum < target) {
                    if (target - sum < min_gap) {
                        min_gap = target - sum;
                        closest_sum = sum;
                    }
                    ++j;
                } else { //sum > target
                    if (sum - target < min_gap) {
                        min_gap = sum - target;
                        closest_sum = sum;
                    }
                    --k;
                }
            }
        }

        return closest_sum;
    }
};

class Solution1 {
public:
    int threeSumClosest(std::vector<int> &nums, int target) {
        if (nums.size() < 3)
            return 0;
        std::sort(nums.begin(), nums.end());

        int min_gap = 0x7fffffff;
        int closest_sum = 0;
        for (size_t i = 0; i < nums.size() - 2; ++i) {
            size_t j = i +1, k = nums.size() - 1;
            while (j < k) {
                int sum = nums[i] + nums[j] + nums[k];
                if (sum == target)
                    return target;
                else if (sum < target) {
                    if (target - sum < min_gap) {
                        min_gap = target - sum;
                        closest_sum = sum;
                    }
                    ++j;
                    while (j < k && nums[j] == nums[j - 1])
                        ++j;
                }
                else { //sum > target
                    if (sum - target < min_gap) {
                        min_gap = sum - target;
                        closest_sum = sum;
                    }
                    --k;
                    while (j < k && nums[k] == nums[k + 1])
                        --k;
                }
            }
            while (i < nums.size() - 2 && nums[i] == nums[i + 1])
                ++i;
        }

        return closest_sum;
    }
};

int main()
{
    //2
    std::vector<int> nums = {-1, 2, 1, -4};
    int target = 1;
    Solution solution;
    std::cout << solution.threeSumClosest(nums, target) << std::endl;

    return 0;
}
