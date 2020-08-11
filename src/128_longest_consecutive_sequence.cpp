#include <iostream>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <algorithm>

using std::cout;
using std::endl;
using std::vector;
using std::unordered_set;
using std::unordered_map;

class Solution {
public:
    int longestConsecutive(const vector<int> &nums) {
        unordered_set<int> numbers(nums.begin(), nums.end());  // 去重
        unordered_map<int, int> left2right;  // 以区间左边界为键，以右边界为值
        unordered_map<int, int> right2left;  // 以区间右边界为键，以右边界为值

        int longest = 0;
        for (int num : numbers) {
            auto left_interval = right2left.find(num - 1);   // 相邻左区间
            auto right_interval = left2right.find(num + 1);  // 相邻右区间

            if (left_interval == right2left.end()
                && right_interval == left2right.end()) {
                left2right[num] = num;
                right2left[num] = num;
                longest = std::max(longest, 1);
            } else if (left_interval != right2left.end()
                       && right_interval == left2right.end()) {
                int temp = left_interval->second;
                right2left.erase(left_interval);
                right2left[num] = temp;
                left2right[temp] = num;
                longest = std::max(longest, num - temp + 1);
            } else if (left_interval == right2left.end()
                       && right_interval != left2right.end()) {
                int temp = right_interval->second;
                left2right.erase(right_interval);
                left2right[num] = temp;
                right2left[temp] = num;
                longest = std::max(longest, temp - num + 1);
            } else {
                right2left[right_interval->second] = left_interval->second;
                left2right[left_interval->second] = right_interval->second;
                longest = std::max(longest,
                                   right_interval->second - left_interval->second + 1);
                right2left.erase(left_interval);
                left2right.erase(right_interval);
            }
        }

        return longest;
    }
};

class Solution1 {
public:
    int longestConsecutive(const vector<int> &nums) {
        unordered_set<int> numbers(nums.begin(), nums.end());

        int longest = 0;
        for (int num : numbers) {
            // 如果没有num-1，则num没有处理过，计算以num为起点的序列长度
            if (numbers.find(num - 1) == numbers.end()) {
                int last = num + 1;
                while (numbers.find(last) != numbers.end())
                    ++last;
                longest = std::max(longest, last - num);
            }
        }

        return longest;
    }
};

int main() {
    // 4
    vector<int> nums1 = {100, 4, 200, 1, 3, 2};

    // 3
    vector<int> nums2 = {-1, 1, 0};

    Solution1 solution;
    cout << solution.longestConsecutive(nums1) << endl;
    cout << solution.longestConsecutive(nums2) << endl;

    return 0;
}
