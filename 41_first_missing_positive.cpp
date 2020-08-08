#include <iostream>
#include <vector>
#include <unordered_set>
#include <algorithm>

/* 使用哈希表保存所有数字，然后从1开始进行查找，如果某个数字未找到，就返回它，时间复杂度O(n)，空间复杂度O(n) */
class Solution {
public:
    int firstMissingPositive(std::vector<int> &nums) {
        std::unordered_set<int> cache(nums.begin(), nums.end());
        int i = 1;
        auto it = cache.find(i);
        while (it != cache.end()) {
            ++i;
            it = cache.find(i);
        }
        return i;
    }
};

/* 改进：所有非正数和大于n的数字不再存储，非正数显示没有存储的必要，而大于n的数字一旦出现，那么剩下的n-1个数不可能
 * 覆盖1到n的所有数字，所以缺失的最小正整数必然在1到n之间出现，不可能为大于n的数，所以大于n的数也没有存储的必要。
 * 时间复杂度O(n)，空间复杂度O(n)。 */
class Solution1 {
public:
    int firstMissingPositive(std::vector<int> &nums) {
        std::vector<int> count(nums.size(), 0);
        //统计1到n的各个数字出现的次数
        for (int i : nums) {
            if (i > nums.size() || i <= 0)
                continue;
            ++count[i - 1];
        }
        //寻找第一个没有出现过的数字
        for (int i = 0; i < count.size(); ++i) {
            if (count[i] == 0)
                return i + 1;
        }
        //如果都出现过，那nums中一定是1, 2, 3, ..., n，第一个未出现的正整数就是n+1
        return static_cast<int>(nums.size()) + 1;
    }
};

/* 改进：使用nums本身来存储各个数字是否出现，遍历nums，将数字i保存在下标为i-1的位置，然后再遍历nums一次，
 * 如果某个位置i保存的数不是i+1，那么i+1就没有出现过。时间复杂度O(n)，空间复杂度O(1)。 */
class Solution2 {
public:
    int firstMissingPositive(std::vector<int> &nums) {
        int i = 0;
        while (i < nums.size()) {
            //跳过不在1到n之间的数
            if (nums[i] <= 0 || nums[i] > nums.size()) {
                ++i;
                continue;
            }
            //跳过已经出现的过的数
            if (nums[nums[i] - 1] == nums[i]) {
                ++i;
                continue;
            }

            std::swap(nums[i], nums[nums[i] - 1]);
        }

        for (int j = 0; j < nums.size(); ++j) {
            if (nums[j] != j + 1)
                return j + 1;
        }

        return static_cast<int>(nums.size()) + 1;
    }
};

int main()
{
    Solution2 solution;

    std::vector<int> nums1 = {1, 2, 0}; //3
    std::vector<int> nums2 = {3, 4, -1, 1}; //2
    std::vector<int> nums3 = {7, 8, 9, 11, 12}; //1

    std::cout << solution.firstMissingPositive(nums1) << std::endl;
    std::cout << solution.firstMissingPositive(nums2) << std::endl;
    std::cout << solution.firstMissingPositive(nums3) << std::endl;

    return 0;
}
