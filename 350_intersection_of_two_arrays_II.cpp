#include <iostream>
#include <vector>
#include <unordered_map>
#include <algorithm>

using std::cout;
using std::endl;
using std::vector;

/*
 * 先排序然后合并时取出相同元素。时间复杂度O(n1 log n1 + n2 log n2)，空间复杂度O(1)。
 */
class Solution {
public:
    vector<int> intersect(vector<int> &nums1, vector<int> &nums2) {
        std::sort(nums1.begin(), nums1.end());
        std::sort(nums2.begin(), nums2.end());

        vector<int> result;
        int i = 0;
        int j = 0;
        while (i < nums1.size() && j < nums2.size()) {
            if (nums1[i] == nums2[j]) {
                result.push_back(nums1[i]);
                ++i;
                ++j;
            } else if (nums1[i] < nums2[j]) {
                ++i;
            } else {
                ++j;
            }
        }

        return result;
    }
};

/*
 * 使用哈希表存储较短的数组，然后对较长数组中的每一个元素查找较短数组中是否还有剩余的相同数字。
 * 时间复杂度O(n1 + n2)，空间复杂度O(min{n1, n2})。
 * 如果内存不足也应该优先考虑此法，只将较短的数组加载进内存，而较长的数组分段加载。
 */
class Solution1 {
public:
    vector<int> intersect(const vector<int> &nums1, const vector<int> &nums2) {
        // 总是认为nums1比较短
        if (nums1.size() > nums2.size())
            return intersect(nums2, nums1);

        std::unordered_map<int, int> counts;
        for (int num : nums1)
            ++counts[num];

        vector<int> result;
        for (int num : nums2) {
            auto it = counts.find(num);
            if (it != counts.end() && it->second > 0) {
                result.push_back(num);
                --it->second;
            }
        }

        return result;
    }
};


std::ostream &operator<<(std::ostream &out, const vector<int> &vec) {
    if (vec.empty())
        return out;
    for (int i = 0; i + 1 < vec.size(); ++i)
        out << vec[i] << ", ";
    return out << vec.back();
}

int main() {
    // 2, 2
    vector<int> nums1_1 = {1, 2, 2, 1};
    vector<int> nums2_1 = {2, 2};

    // 4, 9
    vector<int> nums1_2 = {4, 9, 5};
    vector<int> nums2_2 = {9, 4, 9, 8, 4};

    Solution1 solution;
    cout << solution.intersect(nums1_1, nums2_1) << endl;
    cout << solution.intersect(nums1_2, nums2_2) << endl;

    return 0;
}
