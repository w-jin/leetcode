#include <iostream>
#include <vector>

class Solution {
public:
    int removeDuplicates(std::vector<int> &nums) {
        if (nums.empty())
            return 0;
        int no_duplicate = 0;
        for (size_t i = 1; i < nums.size(); ++i) {
            if (nums[i] != nums[no_duplicate])
                nums[++no_duplicate] = nums[i];
        }
        return no_duplicate + 1;
    }
};

int main()
{
    //0, 1, 2, 3, 4
    std::vector<int> nums = {0, 0, 1, 1, 1, 2, 2, 3, 3, 4};
    Solution solution;
    int n = solution.removeDuplicates(nums);
    for (int i = 0; i < n; ++i)
        std::cout << nums[i] << " ";
    std::cout << std::endl;

    return 0;
}
