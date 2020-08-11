#include <iostream>
#include <vector>
#include <algorithm>

using std::cout;
using std::endl;
using std::vector;

class Solution {
public:
    vector<int> singleNumbers(vector<int> &nums) {
        int m = 0;
        for (int n : nums)
            m = m ^ n;
        int pivot = m & -m;
        int left = 0;
        int right = static_cast<int>(nums.size()) - 1;
        while (left <= right) {
            while (left <= right && (nums[left] & pivot) == 0)
                ++left;
            if (left > right)
                break;
            while (left <= right && (nums[right] & pivot) != 0)
                --right;
            if (left > right)
                break;
            std::swap(nums[left], nums[right]);
            ++left;
            --right;
        }

        vector<int> result(2, 0);
        for (int i = 0; i < left; ++i)
            result[0] = result[0] ^ nums[i];
        for (int i = left; i < nums.size(); ++i)
            result[1] = result[1] ^ nums[i];
        return result;
    }
};

/*
    其实根本不需要修改数组，直接判断每个元素属于哪一组就行了
 */
class Solution1 {
public:
    vector<int> singleNumbers(vector<int> &nums) {
        int m = 0;
        for (int n : nums)
            m = m ^ n;
        int pivot = m & -m;
        vector<int> result(2, 0);
        for (int i = 0; i < nums.size(); ++i) {
            if (nums[i] & pivot)
                result[0] = result[0] ^ nums[i];
            else
                result[1] = result[1] ^ nums[i];
        }

        return result;
    }
};

std::ostream &operator<<(std::ostream &out, const vector<int> &vec) {
    return out << "[" << vec[0] << ", " << vec[1] << "]";
}

int main() {
    // [6, 1] or [1, 6]
    vector<int> nums1 = {4, 1, 4, 6};

    // [2, 10] or [10, 2]
    vector<int> nums2 = {1, 2, 10, 4, 1, 4, 3, 3};

    // [6, 4] or [4, 6]
    vector<int> nums3 = {6, 5, 5, 9, 10, 9, 4, 10};

    Solution1 solution;
    cout << solution.singleNumbers(nums1) << endl;
    cout << solution.singleNumbers(nums2) << endl;
    cout << solution.singleNumbers(nums3) << endl;

    return 0;
}
