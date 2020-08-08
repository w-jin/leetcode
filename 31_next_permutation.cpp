#include <iostream>
#include <vector>
#include <algorithm>

class Solution {
public:
    void nextPermutation(std::vector<int> &nums) {
        if (nums.empty())
            return;
        std::vector<int>::size_type i = nums.size() - 1, j = nums.size() - 1;
        while (i != 0 && nums[i] <= nums[i - 1])
            --i;
        if (0 == i)
            std::reverse(nums.begin(), nums.end());
        if (i != 0) {
            --i;
            while (nums[i] >= nums[j])
                --j;
            std::swap(nums[i], nums[j]);
            std::reverse(nums.begin() + i + 1, nums.end());
        }
    }
};

class Solution1 {
public:
    void nextPermutation(std::vector<int> &nums) {
        if (nums.empty())
            return;
        auto i = nums.rbegin() + 1;
        while (i != nums.rend() && *(i - 1) <= *i)
            ++i;
        if (i == nums.rend())
            std::reverse(nums.begin(), nums.end());
        else {
            auto j = std::upper_bound(nums.rbegin(), i - 1, *i);
            int temp = *i;
            *i = *j;
            *j = temp;
            std::reverse(nums.rbegin(), i);
        }
    }
};

std::ostream &operator<<(std::ostream &out, const std::vector<int> &v)
{
    for (int i : v)
        out << i << " ";
    return out;
}

int main()
{
    std::vector<int> nums1 = {1, 4, 3, 2}; //2, 1, 3, 4
    std::vector<int> nums2 = {4, 3, 2, 1}; //1, 2, 3, 4

    Solution1 solution;
    solution.nextPermutation(nums1);
    solution.nextPermutation(nums2);
    std::cout << nums1 << std::endl << nums2 << std::endl;
    
    return 0;
}
