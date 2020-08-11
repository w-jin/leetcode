#include <iostream>
#include <vector>
#include <limits>

/* 动态规划，时间复杂度O(n^2)，空间复杂度O(n)。 */
class Solution {
public:
    int jump(const std::vector<int> &nums) {
        //nums为空时没意义
        if (nums.empty())
            return 0;

        //从0出发到各个位置的最小步数
        std::vector<int> min_step(nums.size(), std::numeric_limits<int>::max());
        min_step[0] = 0;
        for (int i = 0; i < nums.size(); ++i) {
            for (int j = 1; j <= nums[i]; ++j) {
                if (i + j >= nums.size())
                    break;
                min_step[i + j] = std::min(min_step[i] + 1, min_step[i + j]);
            }
        }

        return min_step.back();
    }
};

/* 贪心算法，最坏时间复杂度O(n^2)，空间复杂度O(1)。
 * 证明：要使从位置0跳到位置i的步数最小，最后一步应该选择最靠前的能跳到i的位置j，假定再上一步没有选择跳到j，而是选择
 * 跳到位置k，对此，分两种情况讨论：1、k<j，显然，k无法一步跳到i，至少需要两步才能跳到位置i，而j只需要一步，因此选择
 * 跳到位置j是更优的选择；2、k>j，k可能一步跳到i，也可能无法一步跳到i，但无论如何，不可能比位置j更优，并且观察再上一
 * 步，可能无法一步跳到k，则步数更多；综上所述，位置j是最优选择。
 */
class Solution1 {
public:
    int jump(const std::vector<int> &nums) {
        int steps = 0;
        int curr = static_cast<int>(nums.size()) - 1;
        while (curr != 0) {
            //找到最左一个可以跳到curr的位置
            int i = 0;
            while (nums[i] + i < curr)
                ++i;
            ++steps;
            curr = i;
        }
        return steps;
    }
};

/* 贪心算法，每一步选择下一步能够跳得最远的位置。时间复杂度O(n)，空间复杂度O(1)。
 * 证明：从位置i住后跳，选择下一步能够跳得最远的位置j(即nums[j]+j最大)，假定不选择j，而是选择位置k，
 */
class Solution2 {
public:
    int jump(const std::vector<int> &nums) {
        int steps = 0;
        int curr = 0;
        while (curr < nums.size() - 1) {
            int max_pos = curr + 1;
            for (int i = curr + 1; i <= curr + nums[curr]; ++i) {
                if (i == nums.size() - 1)
                    return steps + 1;
                if (i + nums[i] >= max_pos + nums[max_pos])
                    max_pos = i;
            }
            ++steps;
            curr = max_pos;
        }

        return steps;
    }
};

int main()
{
    std::vector<int> nums1 = {2, 3, 1, 1, 4}; //2

    Solution1 solution;
    std::cout << solution.jump(nums1) << std::endl;

    return 0;
}
