#include <iostream>
#include <vector>
#include <algorithm>

class Solution {
public:
    std::vector<std::vector<int>> threeSum(std::vector<int> &nums) {
        std::vector<std::vector<int>> result;
        if (nums.size() < 3)
            return result;

        std::sort(nums.begin(), nums.end());
        if (nums.front() > 0 || nums.back() < 0)
            return result;

        for (size_t i = 0; i < nums.size() - 2 && nums[i] <= 0; ++i) {
            size_t j = i + 1, k = nums.size() - 1;
            while (j < k) {
                if (nums[i] + nums[j] + nums[k] == 0) {
                    result.push_back({nums[i], nums[j], nums[k]});
                    ++j;
                    --k;
                    while (j < k && nums[j] == nums[j - 1])
                        ++j;
                    while (j < k && nums[k] == nums[k + 1])
                        --k;
                } else if (nums[i] + nums[j] + nums[k] < 0) {
                    ++j;
                    while (j < k && nums[j] == nums[j - 1])
                        ++j;
                } else {
                    --k;
                    while (j < k && nums[k] == nums[k + 1])
                        --k;
                }
            }
            while (i < nums.size() - 2 && nums[i] == nums[i + 1])
                ++i;
        }

        return result;
    }
};

int main() {
    // [-1, 0, 1], [-1, -1, 2]
    std::vector<int> nums = {-1, 0, 1, 2, -1, -4};
    Solution solution;
    std::vector<std::vector<int>> result = solution.threeSum(nums);
    for (const auto &v : result) {
        for (int i : v)
            std::cout << i << " ";
        std::cout << std::endl;
    }

    return 0;
}
