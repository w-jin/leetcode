#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>

using std::cout;
using std::endl;
using std::vector;

/*
 * 对当前的数nums[i]，如果已经求出nums[0, ..., i-1]的递增子序，那么对每个子
 * 序列，如果nums[i]大于其末尾元素，那么将nums[i]加入序列中仍然是递增的。其次，
 * 如果nums[j]<=nums[i]，且j<i，则{nums[j], nums[i]}也可构成一个递增子序
 * 列。但是如{4, 7, 7}这样的数组将会产生两个{4, 7}，因此必须对它去重。
 * 时间复杂度O(n * 2^n)，空间复杂度O(n)。子序列最多2^n个，每个子序列需要花费
 * O(n)的时间添加到答案中，排序的时间复杂度为O(2^n log 2^n) = O(n * 2^n)。
 */
class Solution {
public:
    vector<vector<int>> findSubsequences(vector<int> &nums) {
        vector<vector<int>> result;

        for (int i = 1; i < nums.size(); ++i) {
            int n = result.size();
            for (int j = 0; j < n; ++j) {
                if (result[j].back() <= nums[i]) {
                    auto temp = result[j];
                    temp.push_back(nums[i]);
                    result.push_back(temp);
                }
            }

            for (int j = 0; j < i; ++j) {
                if (nums[j] <= nums[i])
                    result.push_back({nums[j], nums[i]});
            }
        }

        std::sort(result.begin(), result.end());
        result.erase(std::unique(result.begin(), result.end()), result.end());

        return result;
    }
};

/*
 * 回溯算法。对于每个数，都有选和不选两个选择，如果nums[curr]>=last则可以选，也可以不选，
 * 否则不能选。为了去重，如果当前值与上次最后一个值相同时不再往下递归，这是因为递归的结果和
 * 不选last而选了curr的结果是一样的，如{..., 4, 4, 6}，如果选了第一个4，到第二个4时，
 * 如果不选它继续向下递归，则会找到递增子序列{4, 6}，如果没选第一个4，到第二个4时，如果选了
 * 它继续向下递归，也会找到递增子序列{4, 6}，这样就重复了。而且如果没选第一个4，到第二个4时，
 * 是无法得知上一个4的存在的，也就无法去重，因此最好的办法就是当前值和上一个值相同的时候，不
 * 再继续向下递归，以排除第一种情况产生的递增子序列。
 * 时间复杂度O(n * 2^n)，空间复杂度O(n)。
 */
class Solution1 {
public:
    vector<int> temp;
    vector<vector<int>> ans;

    void dfs(int curr, int last, vector<int> &nums) {
        if (curr == nums.size()) {
            if (temp.size() >= 2)
                ans.push_back(temp);
            return;
        }

        if (nums[curr] >= last) {
            temp.push_back(nums[curr]);
            dfs(curr + 1, nums[curr], nums);
            temp.pop_back();
        }

        if (nums[curr] != last) {
            dfs(curr + 1, last, nums);
        }
    }

    vector<vector<int>> findSubsequences(vector<int>& nums) {
        temp.clear();
        ans.clear();
        dfs(0, INT_MIN, nums);
        return ans;
    }
};

std::ostream &operator<<(std::ostream &os, const vector<int> &vec) {
    if (vec.empty())
        return os;
    for (int i = 0; i + 1 < vec.size(); ++i)
        os << vec[i] << ", ";
    return os << vec.back();
}

std::ostream &operator<<(std::ostream &os, const vector<vector<int>> &vec) {
    for (int i = 0; i < vec.size(); ++i)
        os << "[" << vec[i] << "]\n";
    return os;
}

int main() {
    // [4, 6], [4, 7], [4, 6, 7], [4, 6, 7, 7], [6, 7], [6, 7, 7], [7,7], [4,7,7]
    vector<int> nums1 = {4, 6, 7, 7};

    Solution1 solution;
    cout << solution.findSubsequences(nums1) << endl;

    return 0;
}
