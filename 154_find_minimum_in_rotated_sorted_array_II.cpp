#include <iostream>
#include <vector>

using std::cout;
using std::endl;
using std::vector;

/*
 * 从后向前找第一个非递减的元素。时间复杂度O(n)，空间复杂度O(1)。
 */
class Solution {
public:
    int findMin(const vector<int> &nums) {
        if (nums.empty())
            return -1;
        for (int i = nums.size() - 1; i > 0; --i) {
            if (nums[i] < nums[i - 1])
                return nums[i];
        }
        return nums[0];
    }
};

/*
 * 二分搜索。
 * 需要注意逻辑，从旋转处将数组划分为两段，则有：
 * 1、如果nums[mid] < nums[last]，则mid位于后半段，要找的元素在mid前面，且mid也有可能；
 * 2、如果nums[mid] > nums[last]，则mid位于前半段，要找的元素在mid后面，而mid无可能；
 * 3、如果nums[mid]==nums[last]，无法判断mid位于哪段，为了缩小区间，可以将last自减1，
 *    这样即使nums[last]为所求，还有一个相同的元素在区间中，但此处必须假设mid!=last，否
 *    则可能将所有所求元素都排除出去。
 *
 * 此处如果与nums[first]进行比较，逻辑会比较复杂。第一个问题是如果数组没有旋转，则有
 * nums[mid]>nums[first]，算法认为旋转点位于mid后面，区间选择错误。第二个问题是mid==first
 * 时，令first自增1可能把所有等于nums[mid]的元素排除出去，这个问题可以通过取上中位数来解决。
 *
 * 平均时间复杂度O(log n)，最坏时间复杂度产生于大多数元素都相同的时候，为O(n)。空间复杂度O(1)。
 */
class Solution1 {
public:
    int findMin(const vector<int> &nums) {
        if (nums.empty())
            return -1;

        int first = 0;
        int last = nums.size() - 1;
        while (first < last) {  // 区间长度至少为2保证不越界
            int mid = first + (last - first) / 2;
            if (nums[mid] < nums[last])
                last = mid;
            else if (nums[mid] > nums[last])
                first = mid + 1;
            else
                --last;
        }

        return nums[first];
    }
};

int main() {
    // 1
    vector<int> nums1 = {1, 3, 5};

    // 0
    vector<int> nums2 = {2, 2, 2, 0, 1};

    Solution1 solution;
    cout << solution.findMin(nums1) << endl;
    cout << solution.findMin(nums2) << endl;

    return 0;
}
