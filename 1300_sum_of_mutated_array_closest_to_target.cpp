#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>

using std::cout;
using std::endl;
using std::vector;

/*
 * 最小的可能值是最小元素和target/n中的较小者，最大的可能值是最大元素，而且选择的最佳元素越大，
 * 和越大，因此可以使用二分查找。
 * 时间复杂度O(N log C)，其中N是数组长度，C是查找区间大小，依赖于数组元素元素分布，大致为最大值
 * 减去最小值。
 * 空间复杂度O(1)。
 */
class Solution {
public:
    int findBestValue(vector<int> &arr, int target) {
        int n = static_cast<int>(arr.size());
        // 使用左开右闭区间进行二分查找
        int m1 = *std::min_element(arr.begin(), arr.end());
        int m2 = *std::max_element(arr.begin(), arr.end()) + 1;
        if (target / n < m1)  // 最佳元素有可能比最小元素小，但不会比最大元素大
            m1 = target / n;
        int closest = m1;
        int error = INT_MAX;
        while (m1 < m2) {
            int mid = m1 + (m2 - m1) / 2;
            int sum = 0;
            for (int a : arr) {
                if (a > mid)
                    sum += mid;
                else
                    sum += a;
            }
            if (abs(sum - target) <= error) {
                closest = mid;
                error = abs(sum - target);
            }
            if (sum <= target)
                m1 = mid + 1;
            else
                m2 = mid;
        }
        return closest;
    }
};

/*
 * 二分查找时，对每个候选值求和进行优化：先对数组排序，然后计算前缀和保存在数组中，对于候选值，
 * 使用二分查找查找它在排序后的数组中的位置，然后计算此位置的前缀和再加上候选值乘剩余元素个数。
 * 时间复杂度O(N log N + C)，其中N是数组长度，C是二分查找的范围，大致为数组元素最大值减去最小
 * 值。空间复杂度O(N)。
 */
class Solution1 {
public:
    int findBestValue(vector<int> &arr, int target) {
        int n = static_cast<int>(arr.size());
        std::sort(arr.begin(), arr.end());
        int m1 = arr[0];
        int m2 = arr[n - 1] + 1;  // 使用左开右闭区间进行二分查找
        if (target / n < m1)  // 最佳元素有可能比最小元素小，但不会比最大元素大
            m1 = target / n;

        vector<int> prefix(n + 1);
        prefix[0] = 0;
        for (int i = 1; i <= n; ++i)
            prefix[i] = prefix[i - 1] + arr[i - 1];

        int closest = m1;
        int error = INT_MAX;
        while (m1 < m2) {
            int mid = m1 + (m2 - m1) / 2;
            int i = std::lower_bound(arr.begin(), arr.end(), mid) - arr.begin();
            int sum = prefix[i] + mid * (n - i);
            if (abs(sum - target) <= error) {
                closest = mid;
                error = abs(sum - target);
            }
            if (sum <= target)
                m1 = mid + 1;
            else
                m2 = mid;
        }
        return closest;
    }
};

int main() {
    // 3
    vector<int> arr1 = {4, 3, 9};
    int target1 = 10;

    // 5
    vector<int> arr2 = {2, 3, 5};
    int target2 = 10;

    // 11361
    vector<int> arr3 = {60864, 25176, 27249, 21296, 20204};
    int target3 = 56803;

    Solution1 solution;
    cout << solution.findBestValue(arr1, target1) << endl;
    cout << solution.findBestValue(arr2, target2) << endl;
    cout << solution.findBestValue(arr3, target3) << endl;

    return 0;
}
