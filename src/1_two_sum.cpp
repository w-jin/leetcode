#include <iostream>
#include <vector>
#include <unordered_map>

class Solution {
public:
    std::vector<int> twoSum(std::vector<int> &nums, int target) {
        std::unordered_map<int, int> numbers;
        for (int i = 0; i < nums.size(); ++i)
            numbers.insert(std::make_pair(nums[i], i));
        for (int i = 0; i < nums.size(); ++i) {
            int rest = target - nums[i];
            auto it = numbers.find(rest);
            if (it != numbers.end() && it->second != i)
                return {i, it->second};
        }
        return {-1, -1};
    }
};

int main() {
    //0, 1
    std::vector<int> nums = {2, 7, 11, 15};
    int target = 9;

    Solution solution;
    std::vector<int> result = solution.twoSum(nums, target);
    std::cout << result[0] << ", " << result[1] << std::endl;
    
    return 0;
}
