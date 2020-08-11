#include <iostream>
#include <vector>
#include <climits>

using std::cout;
using std::endl;
using std::vector;

/*
 * 时间复杂度O(n^2)，超时！
 */
class Solution {
public:
    int maxProduct(vector<int> &nums) {
        int max_product = INT_MIN;
        for (int i = 0; i < nums.size(); ++i) {
            int product = nums[i];
            max_product = std::max(max_product, product);
            for (int j = i + 1; j < nums.size(); ++j) {
                product *= nums[j];
                max_product = std::max(max_product, product);
            }
        }

        return max_product;
    }
};

/*
 * 和连续子数组最大积类似，但是是错误的。{-2, 3, -4}的结果不正确。
 */
class Solution1 {
public:
    int maxProduct(vector<int> &nums) {
        if (nums.empty())
            return 0;
        int prev = 1;
        int max_product = nums[0];
        for (int num : nums) {
            prev = std::max(prev * num, num);
            max_product = std::max(max_product, prev);
        }
        return max_product;
    }
};

/*
 * 在Solution1的基础上引入正负性的考虑：令fa(i)返回以ai结尾的子数组的最大积，fi(i)返回以ai
 * 结尾的子数组的最小积(负得最多)，则
 * fa(i) = max{fa(i-1) x ai, fi(i-1) x ai, ai}
 * fi(i) = min{fa(i-1) x ai, fi(i-1) x ai, ai}
 * 当ai为负数时，fi(i-1) x ai为正数，反而得到最大值，fa(i-1) x ai为负数，取得最小值。
 * 而maxProduct = max{fa(i)}。
 */
class Solution2 {
public:
    int maxProduct(vector<int> &nums) {
        if (nums.empty())
            return 0;
        int fa = 1;
        int fi = 1;
        int max_product = nums[0];
        for (int num : nums) {
            int t1 = fa * num;
            int t2 = fi * num;
            fa = std::max(t1, std::max(t2, num));
            fi = std::min(t1, std::min(t2, num));
            max_product = std::max(max_product, fa);
        }
        return max_product;
    }
};

int main() {
    // 6
    vector<int> nums1 = {2, 3, -2, 4};

    // 0
    vector<int> nums2 = {-2, 0, -1};

    // 24
    vector<int> nums3 = {-2, 3, -4};

    Solution1 solution;
    cout << solution.maxProduct(nums1) << endl;
    cout << solution.maxProduct(nums2) << endl;
    cout << solution.maxProduct(nums3) << endl;

    return 0;
}
