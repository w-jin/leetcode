#include <iostream>
#include <vector>

class Solution {
public:
    bool canJump(std::vector<int> &nums) {
        int i = 0;
        while (i < nums.size()) {
            if (i + nums[i] >= nums.size() - 1)
                return true;
            if (nums[i] == 0)
                return false;

            int max_pos = -1;
            for (int j = i + 1; j <= nums[i] + i; ++j) {
                if (max_pos == -1 || nums[max_pos] + max_pos <= nums[j] + j)
                    max_pos = j;
            }
            i = max_pos;
        }

        //永远不会到达
        return false;
    }
};

int main() {
    //true
    std::vector<int> nums1 = {2, 3, 1, 1, 4};
    //false
    std::vector<int> nums2 = {3, 2, 1, 0, 4};
    //true
    std::vector<int> nums3 = {0};

    std::cout << std::boolalpha
              << Solution().canJump(nums1) << std::endl
              << Solution().canJump(nums2) << std::endl
              << Solution().canJump(nums3) << std::endl;

    return 0;
}
