#include <iostream>
#include <vector>
#include <algorithm>

class Solution {
public:
    std::vector<int> searchRange(std::vector<int> &nums, int target) {
        if (nums.empty())
            return {-1, -1};
        
        //int已经足够大
        int left = 0, right = static_cast<int>(nums.size() - 1), mid = 0;
        while (left < right) {
            mid = left + (right - left) / 2;
            if (nums[mid] >= target)
                right = mid;
            else
                left = mid + 1;
        }

        if (nums[left] != target)
            return {-1, -1};

        std::vector<int> result;
        result.push_back(left);

        right = static_cast<int>(nums.size()) - 1;
        while (left < right) {
            mid = left + (right - left + 1) / 2;
            if (nums[mid] > target)
                right = mid - 1;
            else
                left = mid;
        }
        result.push_back(right);

        return result;
    }
};

/* 优化收敛速度 */
class Solution1 {
public:
    std::vector<int> searchRange(std::vector<int> &nums, int target) {
        if (nums.empty())
            return {-1, -1};
        
        int left = 0, right = static_cast<int>(nums.size()) - 1, mid = 0;
        while (left < right) {
            mid = left + (right - left) / 2;
            //mid已经是第一个了
            if (nums[mid] == target && (mid == 0 || nums[mid - 1] != target)) {
                left = mid;
                break;
            }
            if (nums[mid] >= target)
                right = mid - 1;
            else
                left = mid + 1;
        }

        if (nums[left] != target)
            return {-1, -1};

        std::vector<int> result;
        result.push_back(left);

        right = static_cast<int>(nums.size()) - 1;
        while (left < right) {
            mid = left + (right - left + 1) / 2;
            //mid已经是最后一个了
            if (nums[mid] == target && (mid == nums.size() - 1 || nums[mid + 1] != target)) {
                right = mid;
                break;
            }
            if (nums[mid] > target)
                right = mid - 1;
            else
                left = mid + 1;
        }
        result.push_back(right);

        return result;
    }
};

std::ostream &operator<<(std::ostream &out, const std::vector<int> &nums)
{
    for (const int i : nums)
        out << i << " ";
    return out;
}

int main()
{
    //{3, 4}
    std::vector<int> nums1 = {5, 7, 7, 8, 8, 10};
    int target1 = 8;
    //{-1, -1}
    std::vector<int> nums2 = {5, 7, 7, 8, 8, 10};
    int target2 = 6;

    Solution1 solution;
    std::cout << solution.searchRange(nums1, target1) << std::endl;
    std::cout << solution.searchRange(nums2, target2) << std::endl;

    return 0;
}
