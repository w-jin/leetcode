#include <iostream>
#include <vector>

using std::cout;
using std::endl;
using std::vector;

class Solution {
public:
    int singleNumber(vector<int>& nums) {
        int result = 0;
        for (int num : nums)
            result = result ^ num;
        return result;
    }
};

int main() {
    // 1
    vector<int> nums1 = {2, 2, 1};

    // 4
    vector<int> nums2 = {4, 1, 2, 1, 2};

    Solution solution;
    cout << solution.singleNumber(nums1) << endl;
    cout << solution.singleNumber(nums2) << endl;

    return 0;
}
