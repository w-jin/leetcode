#include <iostream>
#include <vector>
#include <algorithm>

class Solution {
public:
    void sortColors(std::vector<int> & nums) {
        int red = 0, blue = 0;
        int i = 0;
        while (i + blue < nums.size()) {
            // 0移动到表头
            if (0 == nums[i]) {
                std::swap(nums[i], nums[red]);
                ++red;
                ++i;
            }
            // 1不管
            else if (1 == nums[i]) {
                ++i;
            }
            // 2移动到末尾
            else { // 2 == nums[i]
                std::swap(nums[i], nums[nums.size() - blue - 1]);
                ++blue;
            }
        }
    }
};

std::ostream & operator<<(std::ostream & out, const std::vector<int> & nums) {
    for (int i = 0; i < nums.size(); ++i) {
        out << nums[i];
        if (i + 1 != nums.size())
            out << " ";
    }
    return out;
}

int main() {
    // 0, 0, 1, 1, 2, 2
    std::vector<int> nums1 = {2, 0, 2, 1, 1, 0};

    Solution solution;
    solution.sortColors(nums1);
    std::cout << nums1 << std::endl;

    return 0;
}
