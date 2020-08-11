#include <iostream>
#include <vector>

class Solution {
public:
    std::vector<std::vector<int>> subsets(std::vector<int> &nums) {
        std::vector<std::vector<int>> result;
        result.emplace_back();

        for (int num : nums) {
            auto n = result.size();
            for (int i = 0; i < n; ++i) {
                auto subset = result[i];
                subset.push_back(num);
                result.push_back(subset);
            }
        }

        return result;
    }
};

class Solution1 {
public:
    std::vector<std::vector<int>> subsets(std::vector<int> &nums) {
        auto length = nums.size();
        auto n = (1u << length);
        std::vector<std::vector<int>> result(n);

        for (auto i = 0u; i < n; ++i) {
            std::vector<int> temp;
            for (auto j = 0u; j < length; ++j) {
                if ((1u << j) & i)
                    temp.push_back(nums[j]);
            }
            result[i] = temp;
        }

        return result;
    }
};

int main() {
    std::vector<int> nums = {1, 2, 3};

    Solution1 solution;
    auto result = solution.subsets(nums);
    for (const auto &subset : result) {
        for (int i : subset)
            std::cout << i << "\t";
        std::cout << "\n";
    }

    return 0;
}
