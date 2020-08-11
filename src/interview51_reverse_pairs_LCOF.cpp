#include <iostream>
#include <vector>
#include <algorithm>
#include <unordered_map>

using std::cout;
using std::endl;
using std::vector;

/*
    使用归并排序来做。时间复杂度O(n log n)，空间复杂度O(n)。
*/
class Solution {
public:
    int reversePairs(vector<int> &nums) {
        if (nums.empty() || nums.size() == 1)
            return 0;

        const int M = static_cast<int>(nums.size()) / 2;
        vector<int> A{nums.begin(), nums.begin() + M};
        vector<int> B{nums.begin() + M, nums.end()};

        int m1 = reversePairs(A);
        int m2 = reversePairs(B);

        int count = 0;
        int i = static_cast<int>(A.size()) - 1;
        int j = static_cast<int>(B.size()) - 1;
        while (i >= 0 && j >= 0) {
            if (A[i] <= B[j]) {
                nums[i + j + 1] = B[j];
                --j;
            } else {
                count += j + 1;
                nums[i + j + 1] = A[i];
                --i;
            }
        }
        while (i >= 0) {
            nums[i] = A[i];
            --i;
        }
        while (j >= 0) {
            nums[j] = B[j];
            --j;
        }

        return m1 + m2 + count;
    }
};

class BIT {
public:
    explicit BIT(int n) : n(n), tree(n + 1, 0) {}

    explicit BIT(const vector<int> &nums) {
        this->n = static_cast<int>(nums.size());
        this->tree = vector<int>(n + 1, 0);
        for (int i = 0; i < n; ++i)
            tree[i + 1] = nums[i];
        for (int i = 1; i <= n; ++i) {
            int j = i + (i & -i);
            if (j <= n)
                tree[j] += tree[i];
        }
    }

    void update(int idx, int delta) {
        ++idx;  // 0-based to 1-based
        while (idx <= n) {
            tree[idx] += delta;
            idx += (idx & -idx);
        }
    }

    int prefixSum(int idx) {
        ++idx;  // 0-based to 1-based
        int sum = 0;
        while (idx > 0) {
            sum += tree[idx];
            idx -= (idx & -idx);
        }
        return sum;
    }

    // sum for [first, last]
    int rangeSum(int first, int last) {
        return prefixSum(last) - prefixSum(first - 1);
    }

private:
    int n;
    vector<int> tree;
};

/*
    使用树状数组来做，用时和内存都比使用归并排序好很多。
*/
class Solution1 {
public:
    int reversePairs(vector<int> &nums) {
        vector<int> temp = nums;
        std::sort(temp.begin(), temp.end());
        std::unordered_map<int, int> map;
        for (int i = 0; i < temp.size(); ++i)
            map[temp[i]] = i;

        int count = 0;
        const int N = static_cast<int>(nums.size());
        BIT bit(N);
        for (int i = N - 1; i >= 0; --i) {
            count += bit.prefixSum(map[nums[i]] - 1);
            bit.update(map[nums[i]], 1);
        }

        return count;
    }
};


int main() {
    // 5
    vector<int> nums1 = {7, 5, 6, 4};

    // 4
    vector<int> nums2 = {1, 3, 2, 3, 1};

    Solution1 solution;
    cout << solution.reversePairs(nums1) << endl;
    cout << solution.reversePairs(nums2) << endl;

    return 0;
}
