#include <iostream>
#include <vector>

using std::cout;
using std::endl;
using std::vector;

class Solution {
public:
    int numberOfSubarrays(vector<int> &nums, int k) {
        int count = 0;

        int i = 0;
        int j = 0;
        int even_count = 0;
        while (j < nums.size()) {
            if (nums[j] % 2 != 0)
                ++even_count;
            if (even_count == k)
                break;
            ++j;
        }
        while (j < nums.size()) {
            int left = 1;   // 应当包含边界上的奇数
            while (i <= j && nums[i] % 2 == 0) {
                ++i;
                ++left;
            }
            ++i;

            int right = 0;  // 下面的循环已经计算了边界上的奇数
            do {
                ++right;
                ++j;
            } while (j < nums.size() && nums[j] % 2 == 0);

            count += left * right;
        }

        return count;
    }
};

/*
    将上面的解法进一步优化，只处理奇数。
*/
class Solution1 {
public:
    int numberOfSubarrays(vector<int> &nums, int k) {
        vector<int> evens;
        for (int i = 0; i < nums.size(); ++i) {
            if (nums[i] % 2 != 0)
                evens.push_back(i);
        }

        int count = 0;
        for (int i = 0; i + k <= evens.size(); ++i) {  // [i, i + k - 1]恰好k个数
            int left = i > 0 ? evens[i] - evens[i - 1] : evens[i] + 1;
            int right = i + k < evens.size() ?
                        evens[i + k] - evens[i + k - 1] :
                        static_cast<int>(nums.size()) - evens[i + k - 1];
            count += left * right;
        }

        return count;
    }
};

class Solution2 {
public:
    int numberOfSubarrays(vector<int> &nums, int k) {
        vector<int> evens;
        evens.push_back(-1);
        for (int i = 0; i < nums.size(); ++i) {
            if (nums[i] % 2 != 0)
                evens.push_back(i);
        }
        evens.push_back(static_cast<int>(nums.size()));

        int count = 0;
        for (int i = 1; i + k < evens.size(); ++i)  // [i, i + k - 1]恰好k个数
            count += (evens[i] - evens[i - 1]) * (evens[i + k] - evens[i + k - 1]);

        return count;
    }
};

int main() {
    // 2
    vector<int> nums1 = {1, 1, 2, 1, 1};
    int k1 = 3;

    // 0
    vector<int> nums2 = {2, 4, 6};
    int k2 = 1;

    // 16
    vector<int> nums3 = {2, 2, 2, 1, 2, 2, 1, 2, 2, 2};
    int k3 = 2;

    Solution1 solution;
    cout << solution.numberOfSubarrays(nums1, k1) << endl;
    cout << solution.numberOfSubarrays(nums2, k2) << endl;
    cout << solution.numberOfSubarrays(nums3, k3) << endl;

    return 0;
}
