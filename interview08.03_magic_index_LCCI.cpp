#include <iostream>
#include <vector>

using std::cout;
using std::endl;
using std::vector;

class Solution {
public:
    int findMagicIndex(vector<int>& nums) {
        int i = 0;
        while (i < nums.size() && nums[i] != i)
            ++i;
        return i < nums.size() ? i : -1;
    }
};

int main() {
    // 0
    vector<int> nums1 = {0, 2, 3, 4, 5};

    // 1
    vector<int> nums2 = {1, 1, 1};

    Solution solution;
    cout << solution.findMagicIndex(nums1) << endl;
    cout << solution.findMagicIndex(nums2) << endl;

    return 0;
}

