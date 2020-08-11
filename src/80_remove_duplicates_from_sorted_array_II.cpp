#include <iostream>
#include <vector>

class Solution {
public:
    int removeDuplicates(std::vector<int> &nums) {
        if (nums.empty())
            return 0;

        int n = 1;
        int count = 1;
        for (int i = 1; i < nums.size(); ++i) {
            if (nums[i] == nums[i - 1]) {
                ++count;
                if (count > 2)
                    continue;
                nums[n++] = nums[i];
            } else {
                count = 1;
                nums[n++] = nums[i];
            }

        }

        return n;
    }
};

class Solution1 {
public:
    int removeDuplicates(std::vector<int> &nums) {
        const int N = static_cast<int>(nums.size());
        if (N < 3)
            return N;

        int n = 2;
        for (int i = 2; i < N; ++i) {
            if (nums[i] != nums[n - 2])
                nums[n++] = nums[i];
        }

        return n;
    }
};

int main() {
    // {1, 1, 2, 2, 3}, length = 5
    std::vector<int> nums1 = {1, 1, 1, 2, 2, 3};

    // {0, 0, 1, 1, 2, 3, 3}, length = 7
    std::vector<int> nums2 = {0, 0, 1, 1, 1, 1, 2, 3, 3};

    Solution1 solution;
    int length = 0;

    length = solution.removeDuplicates(nums1);
    for (int i = 0; i < length; ++i)
        std::cout << nums1[i] << "\t";
    std::cout << std::endl;

    length = solution.removeDuplicates(nums2);
    for (int i = 0; i < length; ++i)
        std::cout << nums2[i] << "\t";
    std::cout << std::endl;

    return 0;
}
