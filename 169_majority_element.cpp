#include <iostream>
#include <vector>
#include <unordered_map>
#include <algorithm>
#include <random>
#include <functional>

using std::cout;
using std::endl;
using std::vector;
using std::unordered_map;

/*
    投票法，时间复杂度O(N)，空间复杂度O(1)
*/
class Solution {
public:
/*
    // 假设数组非空，且主元素必定存在
    int majorityElement(const vector<int> &nums) {
        int major_element = nums[0];
        int count = 1;

        for (int i = 1; i < nums.size(); ++i) {
            if (major_element == nums[i]) {
                ++count;
            } else {
                --count;
                if (0 == count) {
                    major_element = nums[i];
                    count = 1;
                }
            }
        }

        return major_element;
    }
*/
    // 假设数组非空，且主元素必定存在。上面的那个也是对的，但不太好理解。
    int majorityElement(const vector<int> &nums) {
        int major = 0;
        int count = 0;
        for (int num : nums) {
            if (0 == count) {
                major = num;
                count = 1;
            } else {
                if (major == num)
                    ++count;
                else
                    --count;
            }
        }
        return major;
    }
};

/*
    排序，中点处的元素必定为主元素。分奇偶两种情况：
    N=5: 0 1 [2] 3 4   主元素至少出现3次
    N=6: 0 1 2 [3] 4 5 主元素至少出现4次
    这两种情况下，即使主元素是最大值或者最小值，也能覆盖到中点处的值。
    时间复杂度O(N log N)，空间复杂度O(1)。
*/
class Solution1 {
public:
    int majorityElement(vector<int> &nums) {
        std::sort(nums.begin(), nums.end());
        return nums[nums.size() / 2];
    }
};

/*
    随机法。每次随机挑选一个元素来验证，它是主元素的概率不小于0.5，因此期望次数不大于2，所以平均
    时间复杂度O(N)，空间复杂度O(1)。
*/
class Solution2 {
public:
    int majorityElement(const vector<int> &nums) {
        auto die = std::bind(std::uniform_int_distribution<size_t>{0, nums.size()},
                             std::default_random_engine{std::random_device{}()});
        while (true) {
            int candidate = nums[die() % nums.size()];
            int count = 0;
            for (int i : nums) {
                if (i == candidate)
                    ++count;
            }
            if (count > nums.size() / 2)
                return candidate;
        }
    }
};

/*
    哈希表记录每个数字出现的次数，选择出现次数最多的一个。
    时间复杂度O(N)，空间复杂度O(N)。
*/
class Solution3 {
public:
    int majorityElement(const vector<int> &nums) {
        unordered_map<int, int> count;
        int max_count = 0;
        int major_element = 0;
        for (int n : nums) {
            ++count[n];
            if (count[n] > max_count) {
                max_count = count[n];
                major_element = n;
            }
        }
        return major_element;
    }
};

/*
    快速选择算法，选择第n/2+1小的元素，即排序后位于下标n/2处的元素
    时间复杂度O(N)，空间复杂度O(log N)，空间复杂度由递归造成。
    实际效果并不好！
*/
class Solution4 {
public:
    // 不处理数组为空的情况
    int majorityElement(vector<int> &nums) {
        int n = static_cast<int>(nums.size());
        return selectKthLeastNumber(nums, 0, n - 1, n / 2 + 1);
    }

private:
    // 返回从小到大数的第k个元素
    int selectKthLeastNumber(vector<int> &nums, int left, int right, int k) {
        if (left == right)
            return nums[left];

        int pivot_index = partition(nums, left, right);
        if (pivot_index - left + 1 == k)
            return nums[pivot_index];
        else if (pivot_index - left + 1 > k)
            return selectKthLeastNumber(nums, left, pivot_index - 1, k);
        else
            return selectKthLeastNumber(nums, pivot_index + 1, right, k - (pivot_index - left + 1));
    }

    int partition(vector<int> &nums, int left, int right) {
        int pivot = nums[left];
        int l = left;
        int r = right;
        while (l < r) {
            while (l < r && nums[r] >= pivot)
                --r;
            if (l == r)
                break;
            nums[l] = nums[r];

            while (l < r && nums[l] <= pivot)
                ++l;
            if (l == r)
                break;
            nums[r] = nums[l];
        }
        nums[l] = pivot;
        return l;
    }
};

/*
 * 调用库函数中的快速选择算法
 */
class Solution5 {
public:
    int majorityElement(vector<int> &nums) {
        std::nth_element(nums.begin(), nums.begin() + nums.size() / 2, nums.end());
        return nums[nums.size() / 2];
    }
};

int main() {
    // 3
    vector<int> nums1 = {3, 2, 3};

    // 2
    vector<int> nums2 = {2, 2, 1, 1, 1, 2, 2};

    // 3
    vector<int> nums3 = {3, 3, 4};

    Solution5 solution;
    cout << solution.majorityElement(nums1) << endl;
    cout << solution.majorityElement(nums2) << endl;
    cout << solution.majorityElement(nums3) << endl;

    return 0;
}
