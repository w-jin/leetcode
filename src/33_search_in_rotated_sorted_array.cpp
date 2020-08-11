#include <iostream>
#include <vector>

class Solution {
public:
    int search(const std::vector<int> &nums, int target) {
        if (nums.empty())
            return -1;

        //int已经足够大
        int left = 0, right = static_cast<int>(nums.size()) - 1, mid = 0;
        while (left <= right) {
            mid = left + (right - left) / 2;
            if (nums[mid] == target)
                return mid;
            else if (nums[mid] < target) {
                //只有数组的确有部分翻转，且mid在后半部分而target在且前半部分时情况才与普通二分搜索不一样
                if (nums.front() >= nums.back() && nums[mid] <= nums.back() && target >= nums.front())
                    right = mid - 1;
                else
                    left = mid + 1;
            }
            else {
                //只有数组的确有部分翻转，且mid在前半部分而target在后半部分时情况才与普通二分搜索不一样
                if (nums.front() >= nums.back() && nums[mid] >= nums.front() && target <= nums.back())
                    left = mid + 1;
                else
                    right = mid - 1;
            }
        }

        return -1;
    }
};

/* 整理Solution1的逻辑，减少不必要的比较 */
class Solution1 {
public:
    int search(const std::vector<int> &nums, int target) {
        if (nums.empty())
            return -1;

        int left = 0, right = static_cast<int>(nums.size()) - 1, mid = 0;
        if (nums.front() >= nums.back() && target >= nums.front()) {
            while (left <= right) {
                mid = left + (right - left) / 2;
                if (nums[mid] == target)
                    return mid;
                else if (nums[mid] < target) {
                    if (nums[mid] <= nums.back())
                        right = mid - 1;
                    else
                        left = mid + 1;
                }
                else
                    right = mid - 1;
            }
        }
        else if (nums.front() >= nums.back() && target <= nums.back()) {
            while (left <= right) {
                mid = left + (right - left) / 2;
                if (nums[mid] == target)
                    return mid;
                else if (nums[mid] < target)
                    left = mid + 1;
                else {
                    if (nums[mid] >= nums.front())
                        left = mid + 1;
                    else
                        right = mid - 1;
                }
            }
        }
        else { //nums.front() < nums.back()，未翻转
            while (left <= right) {
                mid = left + (right - left) / 2;
                if (nums[mid] == target)
                    return mid;
                else if (nums[mid] < target)
                    left = mid + 1;
                else
                    right = mid - 1;
            }
        }

        return -1;
    }
};

/* 更简洁的逻辑，对未翻转的数组处理的较好 */
class Solution2 {
public:
    int search(const std::vector<int> &nums, int target) {
        if (nums.empty())
            return -1;
        
        int left = 0, right = static_cast<int>(nums.size()) - 1, mid = 0;
        while (left <= right) {
            mid = left + (right - left) / 2;
            if (nums[mid] == target)
                return mid;
            if (nums[mid] >= nums.front()) {
                if (nums[mid] > target && target >= nums.front())
                    right = mid - 1;
                else
                    left = mid + 1;
            }
            else {
                if (nums[mid] < target && target <= nums.back())
                    left = mid + 1;
                else
                    right = mid - 1;
            }
        }

        return -1;
    }
};

/*
    二刷时写出的算法，主要想法在于找出与普通二分法不同的情况。与上面的算法不同之
    处在于使用左闭右开区间。
*/
class Solution3 {
public:
    int search(std::vector<int>& nums, int target) {
        if (nums.empty())
            return -1;
        if (target == nums.back())
            return static_cast<int>(nums.size()) - 1;

        int first = 0;
        int last = static_cast<int>(nums.size());
        while (first < last) {
            int mid = first + (last - first) / 2;
            if (target == nums[mid])
                return mid;
            else if (target > nums[mid]) {
                if (nums[mid] <= nums.back() && target > nums.back())
                    last = mid;
                else
                    first = mid + 1;
            } else {
                if (nums[mid] > nums.back() && target < nums.back())
                    first = mid + 1;
                else
                    last = mid;
            }
        }

        return -1;
    }
};

int main()
{
    Solution2 solution;
    std::vector<int> nums1 = {4, 5, 6, 7, 0, 1, 2};
    int target1 = 0; //4
    int target2 = 3; //-1
    std::vector<int> nums2 = {1, 3};
    int target3 = 3; //1
    std::cout << solution.search(nums1, target1) << std::endl
              << solution.search(nums1, target2) << std::endl
              << solution.search(nums2, target3) << std::endl;
    
    return 0;
}
