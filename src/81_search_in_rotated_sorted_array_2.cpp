#include <iostream>
#include <vector>

class Solution {
public:
    bool search(std::vector<int> &nums, int target) {
        if (nums.empty())
            return false;

        int left = 0, right = static_cast<int>(nums.size()) - 1, mid = 0;
        while (left <= right) {
            while (left < right && nums[left] == nums[left + 1])
                ++left;
            while (left < right && nums[right] == nums[right - 1])
                --right;

            mid = left + (right - left) / 2;
            if (nums[mid] == target)
                return true;

            if (nums[mid] >= nums[left]) {
                if (nums[mid] > target && target >= nums[left])
                    right = mid - 1;
                else
                    left = mid + 1;
            }
            else {
                if (nums[mid] < target && target <= nums[right])
                    left = mid + 1;
                else
                    right = mid - 1;
            }
        }

        return false;
    }
};

class Solution1 {
public:
    bool search(std::vector<int>& nums, int target) {
        int size = nums.size();
        int left = 0;
        int right = size - 1;

        while(left < right) {
            int mid = left + (right - left) / 2;
            if(nums[mid] > nums[right]) {
                left = mid + 1;
            } else if(nums[mid] < nums[right]) {
                right = mid;
            } else {
                if(nums[right - 1] > nums[right]) {
                    left = right;
                    break;
                }
                right--;
            }
        }

        int lowest = left;
        left = 0;
        right = size - 1;
        while(left <= right) {
            int mid = left + (right - left) / 2;
            int realMid = (mid + lowest) % size;
            if(nums[realMid] == target)
                return true;
            if(nums[realMid] > target) {
                right = mid - 1;
            } else {
                left = mid + 1;
            }
        }

        return false;
    }

};

int main() {
    // true
    std::vector<int> nums1 = {2, 5, 6, 0, 0, 1, 2};
    int target1 = 0;

    // false
    std::vector<int> nums2 = {2, 5, 6, 0, 0, 1, 2};
    int target2 = 3;

    Solution solution;
    std::cout << std::boolalpha
              << solution.search(nums1, target1) << "\n"
              << solution.search(nums2, target2) << "\n";

    return 0;
}

