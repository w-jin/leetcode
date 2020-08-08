#include <iostream>
#include <vector>

class Solution {
public:
    int removeElement(std::vector<int> &nums, int val) {
        if (nums.empty())
            return 0;
        int n = 0;
        for (size_t i = 0; i < nums.size(); ++i) {
            if (nums[i] != val)
                nums[n++] = nums[i];
        }
        return n;
    }
};

int main()
{
    //0, 1, 3, 0, 4
    std::vector<int> nums = {0, 1, 2, 2, 3, 0, 4, 2};
    int val = 2;

    Solution solution;
    int n = solution.removeElement(nums, val);
    for (int i = 0; i < n; ++i)
        std::cout << nums[i] << " ";
    std::cout << std::endl;

    return 0;
}
