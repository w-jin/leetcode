#include <iostream>
#include <vector>
#include <algorithm>

class Solution {
public:
    std::vector<std::vector<int>> permute(std::vector<int> &nums) {
        permuteRecursive(nums, 0);
        return permutations;

    }

private:
    void permuteRecursive(std::vector<int> &nums, int start) {
        if (start == nums.size()) {
            permutations.push_back(nums);
            return;
        }

        std::vector<int> backup(nums.begin() + start, nums.end());
        for (int i : backup) {
            int j = start;
            while (start < nums.size() && nums[j] != i)
                ++j;
            std::swap(nums[start], nums[j]);
            permuteRecursive(nums, start + 1);
        }
    }

    std::vector<std::vector<int>> permutations;
};

/* 改进：不对nums后半部分进行备份，而是将交换到后面的元素再换回来，那么交换回来的元素还是先前换到后面去的吗？
 * 答案是肯定的，并且每次函数permuteRecursive返回时，nums[start,...,n]将恢复原状。
 * 证明：1、start=n时，即nums中只有一个元素时，函数显然不更改nums；2、假定start=m(m<=n)时函数不更改nums，
 * 那么，当start=m-1，即nums多一个元素时，函数先将nums[m-1]和nums[i]交换，然后对nums[m...n]
 * 执行这个函数，函数不更改nums，所以先前的nums[i]还在原位，然后函数再将nums[m-1]和nums[i]交换，于是又将
 * nums恢复成了原来的样子，其中i=m-1...n，函数对任意一个i都是如此，因此start=m-1时，函数仍然不更改nums。
 * 综上所述，对于任意start，函数反选完成后，nums将恢复原状。
 */
class Solution1 {
public:
    std::vector<std::vector<int>> permute(std::vector<int> &nums) {
        permuteRecursive(nums, 0);
        return permutations;

    }

private:
    void permuteRecursive(std::vector<int> &nums, int start) {
        if (start == nums.size()) {
            permutations.push_back(nums);
            return;
        }

        for (int i = start; i < nums.size(); ++i) {
            std::swap(nums[start], nums[i]);
            permuteRecursive(nums, start + 1);
            std::swap(nums[start], nums[i]);
        }
    }

    std::vector<std::vector<int>> permutations;
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
    // 1 2 3
    // 1 3 2
    // 2 1 3
    // 2 3 1
    // 3 1 2
    // 3 2 1
    std::vector<int> nums = {1, 2, 3};
    Solution1 solution;
    std::cout << solution.permute(nums);
    return 0;
}

