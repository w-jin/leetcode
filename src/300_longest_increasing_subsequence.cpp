#include <iostream>
#include <vector>
#include <algorithm>

using std::cout;
using std::endl;
using std::vector;

/*
    计算以每个元素开头的上升序列的长度，取最大的一个，显然可以用动态规划来解。
    设length[i]表示以nums[i]开头的上升序列的最大长度，则
    length[i] = max{length[j]} + 1，其中j=i+1,...，且nums[j]>nums[i]，
    最后返回length数组的最大值即可。
    时间复杂度O(N^2)，空间复杂度O(N)。
*/
class Solution {
public:
    int lengthOfLIS(const vector<int> &nums) {
        if (nums.empty())
            return 0;

        vector<int> length(nums.size(), 1);
        for (int i = static_cast<int>(nums.size()) - 1; i >= 0; --i) {
            int max_elem = 0;   // 如果此元素后面没有比它大的，则length[i]=1
            for (int j = i + 1; j < length.size(); ++j) {
                if (nums[j] > nums[i] && length[j] > max_elem)
                    max_elem = length[j];
            }
            length[i] = max_elem + 1;
        }

        return *std::max_element(length.begin(), length.end());
    }
};

/*
    单调栈算法的反例：
    4, 5, 2, 6
    使用单调递减栈，栈内元素从栈顶到栈底递减，构成上升序列。上例中，首先4、5入栈，然后2要入栈，
    则4、5需要先出栈，最后栈内元素为2、6，栈的最大长度也只有2，但所求长度为3(4, 5, 6)。
*/


/*
    另一个线性规划算法。设length[i]表示以nums[i]为末尾的最长上升子序列的长度，则
    length[i] = max{length[j] + 1}, 其中j = 0, 1, ..., i-1，且nums[j] < nums[i]。
    时间复杂度O(N^2)，空间复杂度O(N)。
    注意不能用length[i]表示子数组nums[0, ..., i]的最长上升子序列的长度，否则无法递推。
*/
class Solution1 {
public:
    int lengthOfLIS(const vector<int> &nums) {
        if (nums.empty())
            return 0;

        vector<int> length(nums.size(), 1);
        for (int i = 1; i < nums.size(); ++i) {
            for (int j = 0; j < i; ++j) {
                if (nums[j] < nums[i])
                    length[i] = std::max(length[i], length[j] + 1);
            }
        }

        return *std::max_element(length.begin(), length.end());
    }
};

/*
    动态规则+贪心。
    贪心策略：维护数组到当前位置时的所有长度的上升子序列的最小末尾，当处理一个新的数组元素时可以
    通过这些最小末尾直接判断它可以加入到哪个上升子序列末尾。

    令min_tail[i]表示长度为i的上升子序列的最小末尾，则min_tail是单调递增序列。
    证明：假设min_tail不是单调递增序列，即存在一个i使得min_tail[i] >= min_tail[i+1]，则
    min_tail所记录的长度为i+1的上升子序列中，倒数第二个数显然小于min_tail[i+1]和min_tail[i]，
    而它的下标不会大于i，所以序列的前i个数可以构成一个长度为i的上升子序列，所以min_tail[i]的值
    不符合定义。故min_tail是单调递增序列。

    当新添加一个元素nums[i]到数组nums末尾时，有：
        1、若nums[i] > min_tail[max_len]，则此元素可以加入当前最长上升子序列中构成一个更长
    的上升子序列，因此应当使min_tail[++max_len]=nums[i]；
        2、若nums[i] <= min_tail[max_len]，则此元素不能加入当前最长上升子序列，但它可以替
    换某个上升子序列的末尾元素，使它更短，若存在一个j满足min_tail[j] < nums[i] < min_tail[j+1]，
    则长度为j+1的上升子序列的末尾元素可以替换为nums[i]使得它有更小的末尾。

    上面的算法中，2中查找j时应当使用二分查找，所以算法时间复杂度为O(N log N)，空间复杂度O(N)。
*/
class Solution2 {
public:
    int lengthOfLIS(const vector<int> &nums) {
        if (nums.empty())
            return 0;

        vector<int> min_tail(nums.size() + 1);
        int max_len = 1;
        min_tail[1] = nums[0];
        for (int i = 1; i < nums.size(); ++i) {
            if (nums[i] > min_tail[max_len])
                min_tail[++max_len] = nums[i];
            else {
                int l = 1;
                int r = max_len;
                int pos = 0; // 如果找不到说明所有的数都比nums[i]大，此时要更新d[1]，所以这里将pos设为0
                while (l <= r) {
                    int mid = l + (r - l) / 2;
                    if (min_tail[mid] < nums[i]) {
                        pos = mid;
                        l = mid + 1;
                    }
                    else r = mid - 1;
                }
                min_tail[pos + 1] = nums[i];
            }
        }

        return max_len;
    }
};

int main() {
    // 4
    vector<int> nums1 = {10, 9, 2, 5, 3, 7, 101, 18};

    // 3
    vector<int> nums2 = {4, 10, 4, 3, 8, 9};

    Solution1 solution;
    cout << solution.lengthOfLIS(nums1) << endl;
    cout << solution.lengthOfLIS(nums2) << endl;

    return 0;
}
