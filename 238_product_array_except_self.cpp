#include <iostream>
#include <vector>

using std::cout;
using std::endl;
using std::vector;

/*
 * 时间复杂度O(n)，空间复杂度O(1)。
 */
class Solution {
public:
    vector<int> productExceptSelf(const vector<int> &nums) {
        const int n = static_cast<int>(nums.size());
        vector<int> output(n);

        output[0] = 1;
        for (int i = 1; i < n; ++i) {  // 先计算每个数左边的乘积保存在output中
            output[i] = output[i - 1] * nums[i - 1];
        }

        output[0] = nums[n - 1];  // 使用output[0]来存储每个数右边的乘积
        for (int i = n - 2; i > 0; --i) {  // 再把右边的乘积乘上去
            output[i] *= output[0];
            output[0] *= nums[i];
        }

        return output;
    }
};

/*
 * 和Solution是一样的思路，稍微好理解一点。
 */
class Solution1 {
public:
    vector<int> productExceptSelf(const vector<int> &nums) {
        const int n = static_cast<int>(nums.size());
        vector<int> output(n);

        // 计算左边的乘积
        int left = 1;
        for (int i = 0; i < n; ++i) {
            output[i] = left;
            left *= nums[i];
        }

        // 乘上右边的乘积
        int right = 1;
        for (int i = n - 1; i >= 0; --i) {
            output[i] *= right;
            right *= nums[i];
        }

        return output;
    }
};

/*
 * 两边的乘积同时计算。
 */
class Solution2 {
public:
    vector<int> productExceptSelf(const vector<int> &nums) {
        const int n = static_cast<int>(nums.size());
        vector<int> output(n, 1);

        int left = 1;
        int right = 1;
        for (int i = 0; i < n; ++i) {
            output[i] *= left;
            left *= nums[i];

            output[n - 1 - i] *= right;
            right *= nums[n - 1 - i];
        }

        return output;
    }
};

std::ostream &operator<<(std::ostream &out, const vector<int> &nums) {
    if (nums.empty())
        return out;
    for (int i = 0; i + 1 < nums.size(); ++i)
        out << nums[i] << ", ";
    return out << nums.back();
}

int main() {
    // 24, 12, 8, 6
    vector<int> nums1 = {1, 2, 3, 4};

    Solution1 solution;
    cout << solution.productExceptSelf(nums1) << endl;

    return 0;
}
