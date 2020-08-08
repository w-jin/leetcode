#include <iostream>
#include <vector>
#include <unordered_set>
#include <algorithm>

class Solution {
public:
    std::vector<std::vector<int>> permuteUnique(std::vector<int> &nums) {
        permutations.clear();
        std::sort(nums.begin(), nums.end());
        permuteUniqueRecursive(nums, 0);
        return permutations;
    }

private:
    void permuteUniqueRecursive(std::vector<int> &nums, int start) {
        if (start == nums.size()) {
            permutations.push_back(nums);
            return;
        }

        for (int i = start; i < nums.size(); ++i) {
            if (i != start && nums[i] == nums[i - 1])
                continue;

            //将nums[i]放到nums[start]来，同时保证后面有序
            int temp = nums[i];
            for (int j = i; j > start; --j)
                nums[j] = nums[j - 1];
            nums[start] = temp;

            permuteUniqueRecursive(nums, start + 1);

            //恢复原状
            for (int j = start; j < i; ++j)
                nums[j] = nums[j + 1];
            nums[i] = temp;
        }
    }

    std::vector<std::vector<int>> permutations;
};

/* 使用哈希表来保存已经用过的数字，避免重复 */
class Solution1 {
public:
    std::vector<std::vector<int>> permuteUnique(std::vector<int> &nums) {
        permutations.clear();
        std::sort(nums.begin(), nums.end()); //虽然不影响正确性，但排序之后哈希性能更好
        permuteUniqueRecursive(nums, 0);
        return permutations;
    }

private:
    void permuteUniqueRecursive(std::vector<int> &nums, int start) {
        if (start == nums.size()) {
            permutations.push_back(nums);
            return;
        }

        std::unordered_set<int> used;
        for (int i = start; i < nums.size(); ++i) {
            if (used.find(nums[i]) != used.end())
                continue;

            used.insert(nums[i]);
            std::swap(nums[start], nums[i]);
            permuteUniqueRecursive(nums, start + 1);
            std::swap(nums[start], nums[i]);
        }
    }

    std::vector<std::vector<int>> permutations;
};

/* 使用一个数组来记录各个数字是否用过，从nums中逐个选取未用过的数字组成全排列 */
class Solution2 {
public:
    std::vector<std::vector<int>> permuteUnique(std::vector<int> &nums) {
        permutations.clear();
        used = std::vector<bool>(nums.size(), false);
        sequence.resize(nums.size());
        std::sort(nums.begin(), nums.end());
        permuteUniqueRecursive(nums, 0);
        return permutations;
    }

private:
    void permuteUniqueRecursive(std::vector<int> &nums, int curr) {
        if (curr == nums.size()) {
            permutations.push_back(sequence);
            return;
        }

        for (int i = 0; i < nums.size(); ++i) {
            if (i > 0 && nums[i] == nums[i - 1] && used[i - 1])
                continue;

            if (not used[i]) {
                used[i] = true;
                sequence[curr] = nums[i];
                permuteUniqueRecursive(nums, curr + 1);
                used[i] = false;
            }
        }
    }

    std::vector<std::vector<int>> permutations;
    std::vector<int> sequence;
    std::vector<bool> used;
};

std::ostream &operator<<(std::ostream &out, const std::vector<std::vector<int>> &vec)
{
    for (const auto &v : vec) {
        for (int i : v)
            out << i << " ";
        out << std::endl;
    }
    return out;
}

int main()
{
    Solution2 solution;
    std::vector<int> nums1 = {1, 1, 2};
    std::vector<int> nums2 = {0, 1, 0, 0, 9};
    std::cout << solution.permuteUnique(nums1) << std::endl;
    std::cout << solution.permuteUnique(nums2) << std::endl;

    return 0;
}
