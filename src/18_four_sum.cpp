#include <iostream>
#include <vector>
#include <unordered_map>
#include <utility>
#include <algorithm>

/* 先用哈希表缓存两个数的和，然后对每两个数的和，在哈希表中查找target减去它的值，然后由下标判断是否有数是同一个，
 * 若不是，将它们从小到大放入结果中，最后去掉重复的结果。时间复杂度平均为O(n^2)，最坏O(n^4)，空间复杂度O(n^2)。
 * 从时间复杂度上看很快，但在测试中的实际效果并不如Solution1好。
 */
class Solution {
public:
    std::vector<std::vector<int>> fourSum(std::vector<int> &nums, int target) {
        std::vector<std::vector<int>> result;
        if (nums.size() <4)
            return result;

        std::sort(nums.begin(), nums.end());

        //缓存两个数的和
        std::unordered_multimap<int, std::pair<int, int>> cache;
        for (int i = 0; i < nums.size(); ++i)
            for (int j = i + 1; j < nums.size(); ++j)
                cache.insert({nums[i] + nums[j], {i, j}});

        //遍历缓存，寻找所有和为target的组合
        for (auto &i : cache) {
            auto range = cache.equal_range(target - i.first);
            for (auto j = range.first; j != range.second; ++j) {
                int a = i.second.first;
                int b = i.second.second;
                int c = j->second.first;
                int d = j->second.second;
                if (a != c && a != d && b != c && b != d) {
                    std::vector<int> v = {nums[a], nums[b], nums[c], nums[d]};
                    std::sort(v.begin(), v.end());
                    result.push_back(v);
                }
            }
        }

        //去除重复的
        std::sort(result.begin(), result.end());
        result.erase(std::unique(result.begin(), result.end()), result.end());

        return result;
    }
};

/* 和3-sum一样的做法，用两层循环计算两个数的和，然后在剩下的数里寻找两个数之和等于target送去它的剩余量，
 * 跳过重复元素的逻辑和3-sum一样。时间复杂度为O(n^2)，空间复杂度为O(1)。实际运行效果比Solution1好。
 * 注意：注释中所有跳过重复是不仅指跳过不必要测试的元素，更是指result中不出现重复的组合
 */
class Solution1 {
public:
    std::vector<std::vector<int>> fourSum(std::vector<int> &nums, int target) {
        std::vector<std::vector<int>> result;
        if (nums.size() < 4)
            return result;

        int n = static_cast<int>(nums.size());
        std::sort(nums.begin(), nums.end());
        for (int i = 0; i < n - 3; ++i) {
            //跳过重复
            if (i > 0 && nums[i] == nums[i - 1])
                continue;

            for (int j = i + 1; j < n - 2; ++j) {
                //跳过重复
                if (j > i + 1 && nums[j] == nums[j - 1])
                    continue;

                int k = j + 1, l = n - 1;
                while (k < l) {
                    if (nums[i] + nums[j] + nums[k] + nums[l] == target) {
                        result.push_back({nums[i], nums[j], nums[k], nums[l]});
                        ++k;
                        --l;
                        //以下两个循环有一个即可跳过重复，但nums[k]和nums[l]中有一个变化而另一个不变化，和变化，不成立
                        while (k < l && nums[k] == nums[k - 1])
                            ++k;
                        while (k < l && nums[l] == nums[l + 1])
                            --l;
                    }
                    else if (nums[i] + nums[j] + nums[k] + nums[l] < target) {
                        ++k;
                        //这些元素不可能满足，不是为跳过重复而设
                        while (k < l && nums[k] == nums[k - 1])
                            ++k;
                    }
                    else {
                        --l;
                        //这些元素不可能满足，不是为跳过重复而设
                        while (k < l && nums[l] == nums[l + 1])
                            --l;
                    }
                }
            }
        }

        return result;
    }
};

/* 在Solution1的基础上改进而来，有一些显然不可能存在四个数之和等于target的纵使被排除掉，实际表现非常好。 */
class Solution2 {
public:
    std::vector<std::vector<int>> fourSum(std::vector<int> &nums, int target) {
        std::vector<std::vector<int>> result;
        if (nums.size() < 4)
            return result;

        int n = static_cast<int>(nums.size());
        std::sort(nums.begin(), nums.end());
        for (int i = 0; i < n - 3; ++i) {
            if (i > 0 && nums[i] == nums[i - 1])
                continue;
            //优化
            if (nums[i] + nums[i + 1] + nums[i + 2] + nums[i + 3] > target)
                break;
            if (nums[i] + nums[n - 1] + nums[n - 2] + nums[n - 3] < target)
                continue;

            for (int j = i + 1; j < n - 2; ++j) {
                if (j > i + 1 && nums[j] == nums[j - 1])
                    continue;
                //优化
                if (nums[i] + nums[j] + nums[j + 1] + nums[j + 2] > target)
                    break;
                if (nums[i] + nums[j] + nums[n - 1] + nums[n - 2] < target)
                    continue;

                int k = j + 1, l = n - 1;
                while (k < l) {
                    if (nums[i] + nums[j] + nums[k] + nums[l] == target) {
                        result.push_back({nums[i], nums[j], nums[k], nums[l]});
                        ++k;
                        --l;
                        while (k < l && nums[k] == nums[k - 1])
                            ++k;
                        while (k < l && nums[l] == nums[l + 1])
                            --l;
                    }
                    else if (nums[i] + nums[j] + nums[k] + nums[l] < target) {
                        ++k;
                        while (k < l && nums[k] == nums[k - 1])
                            ++k;
                    }
                    else {
                        --l;
                        while (k < l && nums[l] == nums[l + 1])
                            --l;
                    }
                }
            }
        }

        return result;
    }
};

int main() {
    // [-1,  0, 0, 1],
    // [-2, -1, 1, 2],
    // [-2,  0, 0, 2]
    std::vector<int> nums1 = {1, 0, -1, 0, -2, 2};
    int target1 = 0;

    Solution1 solution;
    std::vector<std::vector<int>> result = solution.fourSum(nums1, target1);

    for (const auto &v : result) {
        for (int i : v)
            std::cout << i << " ";
        std::cout << std::endl;
    }

    return 0;
}
