#include <iostream>
#include <vector>

using std::cout;
using std::endl;
using std::vector;

/*
 * 时间复杂度O(n)，空间复杂度O(1)，但更改了原数组，不符合题意要求。同样不符合题意要求的还有将
 * nums[|nums[i]|]取相反数，如果遍历过程中有某个数对应的nums[|nums[i]|]是负的，则它是重复的。
 */
class Solution {
public:
    int findDuplicate(vector<int> &nums) {
        int i = 0;
        while (i < nums.size()) {
            if (nums[i] == i + 1) {
                ++i;
                continue;
            } else if (nums[i] == nums[nums[i] - 1])
                return nums[i];
            else
                std::swap(nums[i], nums[nums[i] - 1]);
        }

        return 0;
    }
};

/*
 * 使用二分查找搜索重复的数，由于n+1的范围为[1, n]，所以小于或等于重复的那个数的元素个数大于它。
 * 具体地，设cnt[i]表示nums中小于或等于i的数的个数，则cnt必为单调递增数组，且有：当i在区间
 * [1, target-1]内时，cnt[i]<=i；当i在区间[target, n]内时，cnt[i]>i。因此使用二分查找搜索
 * 第一个使cnt[i]>i的数即可。
 */
class Solution1 {
public:
    int findDuplicate(const vector<int> &nums) {
        // 使用左闭右开区间[left, right)
        int left = 1;
        int right = static_cast<int>(nums.size());
        while (left < right) {
            int mid = left + (right - left) / 2;
            // 计算小于等于mid的个数
            int count = 0;
            for (int num : nums) {
                if (num <= mid)
                    ++count;
            }
            if (count > mid)
                right = mid;
            else
                left = mid + 1;
        }

        return left;
    }
};

/*
 * 针对数的二进制位，考虑以下两种情况：
 * 1、如果重复的数只出现了2次，则[1,n]中所有数都在场，其中某个数出现了两次，计算nums中所以数的
 * 第i位数字之和x，以及[1,n]所有数的第i位数字之和y，若x>y(x=y+1)，则重复的数第i位为1，若x==y，
 * 则重复的数第i位为0。
 * 2、如果重复的数出现次数超过2次，则[1,n]中某个数被替换成了它，假设a被替换成b，考虑第i位的变化
 * 情况，记[1,n]所有数第i位数字之和为x，nums所有数第i位数字之和为y，有
 *     (1) a的第i位为0，b的第i位为0，则替换之后x不变，x==y
 *     (2) a的第i位为0，b的第i位为1，则替换之后x增大，x>y(考虑1，x==y+1，然后x增大，故x>y)
 *     (3) a的第i位为1，b的第i位为0，则替换之后x减小，x<y(考虑1，x==y，然后x减小，故x<y)
 *     (4) a的第i位为1，b的第i位为1，则替换之后x不变，x>y(x==y+1)
 * 注意，最后一列的y==x等是叠加了1的情况的结果。
 * 综合两种情况：x<=y时b的第i位为0，x>y时b的第i位为1。按位还原b即可。
 * 时间复杂度O(n log n)，空间复杂度O(1)。
 */
class Solution2 {
public:
    int findDuplicate(const vector<int> &nums) {
        int n = static_cast<int>(nums.size()) - 1;
        int target = 0;
        int bit = 0;
        while ((1 << bit) <= n) {  // 计算第i位
            int x = 0;
            int y = 0;
            for (int i = 0; i <= n; ++i) {
                x += nums[i] & (1 << bit);
                y += i & (1 << bit);
            }
            if (x > y)
                target |= 1 << bit;
            ++bit;
        }
        return target;
    }
};

/*
 * 快慢指针法，或者Floyd判圈法。
 * 时间复杂度O(n)，空间复杂度O(1)。
 */
class Solution3 {
public:
    int findDuplicate(const vector<int> &nums) {
        int fast = 0;
        int slow = 0;
        do {
            slow = nums[slow];
            fast = nums[nums[fast]];
        } while (slow != fast);
        slow = 0;
        while (slow != fast) {
            slow = nums[slow];
            fast = nums[fast];
        }
        return slow;
    }
};

int main() {
    // 2
    vector<int> nums1 = {1, 3, 4, 2, 2};

    // 3
    vector<int> nums2 = {3, 1, 3, 4, 2};

    Solution3 solution;
    cout << solution.findDuplicate(nums1) << endl;
    cout << solution.findDuplicate(nums2) << endl;

    return 0;
}
