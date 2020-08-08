#include <iostream>
#include <vector>
#include <climits>

using std::cout;
using std::endl;
using std::vector;

class Solution {
public:
    int minSubArrayLen(int s, vector<int> &nums) {
        int min_len = INT_MAX;
        int i = 0;
        int j = 0;
        int sum = 0;   // 左闭右开区间[i, j)的和
        while (j < nums.size()) {
            sum += nums[j];
            ++j;
            if (sum >= s) {
                while (sum >= s) {
                    sum -= nums[i];
                    ++i;
                }
                if (j - i + 1 < min_len)
                    min_len = j - i + 1;
            }
        }

        return min_len == INT_MAX ? 0 : min_len;
    }
};

int main() {
    // 2
    int s1 = 7;
    vector<int> nums1 = {2, 3, 1, 2, 4, 3};

    // 8
    int s2 = 213;
    vector<int> nums2 = {12, 28, 83, 4, 25, 26, 25, 2, 25, 25, 25, 12};

    Solution solution;
    cout << solution.minSubArrayLen(s1, nums1) << endl;
    cout << solution.minSubArrayLen(s2, nums2) << endl;

    return 0;
}
