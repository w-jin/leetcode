#include <iostream>
#include <vector>

class Solution {
public:
    int searchInsert(std::vector<int> &nums, int target) {
        if (nums.empty())
            return 0;

        //int已经足够大
        int left = 0, right = static_cast<int>(nums.size()), mid = 0;
        while (left < right) {
            mid = left + (right - left) / 2;
            if (nums[mid] == target)
                return mid;
            if (nums[mid] < target) {
                if (mid == nums.size() - 1 || nums[mid + 1] >= target)
                    return mid + 1;
                else
                    left = mid + 1;
            }
            else {
                if (mid == 0 || nums[mid - 1] < target)
                    return mid;
                else
                    right = mid - 1;
            }
        }

        return left; //只有nums只有一个元素时才会执行它，否则都是循环内返回
    }
};

/*
 * 采用左闭右开区间。思路来源于c++ stl中的lower_bound。
 */
class Solution1 {
public:
    int searchInsert(std::vector<int> &nums, int target) {
        int first = 0;
        int last = nums.size();
        while (first < last) {
            int mid = first + (last - first) / 2;
            if (nums[mid] < target)
                first = mid + 1;
            else
                last = mid;
        }
        return first;
    }
};

int main() {
    std::vector<int> nums1 = {1, 3, 5, 6};
    //2
    int target1 = 5;
    //1
    int target2 = 2;
    //4
    int target3 = 7;
    //0
    int target4 = 0;
    
    Solution solution;
    std::cout << solution.searchInsert(nums1, target1) << std::endl;
    std::cout << solution.searchInsert(nums1, target2) << std::endl;
    std::cout << solution.searchInsert(nums1, target3) << std::endl;
    std::cout << solution.searchInsert(nums1, target4) << std::endl;

    return 0;
}
