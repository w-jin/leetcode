#include <iostream>
#include <vector>
#include <algorithm>
#include <functional>

using std::cout;
using std::endl;
using std::vector;

/*
 * 快速查找算法。平均时间复杂度O(n)，最坏时间复杂度O(n^2)，如果使用BFPRT算法选择主元则可把最坏
 * 时间复杂度降低至O(n)，但常数变大。
 */
class Solution {
public:
    int findKthLargest(vector<int> &nums, int k) {
        if (nums.empty())  // 无意义
            return -1;
        return findKthLargest(nums, 0, static_cast<int>(nums.size()) - 1, k);
    }

private:
    int partition(vector<int> &nums, int first, int last) {
        int pivot = nums[first];
        while (first < last) {
            while (first < last && nums[last] <= pivot)
                --last;
            if (first == last)
                break;
            nums[first] = nums[last];
            ++first;

            while (first < last && nums[first] >= pivot)
                ++first;
            if (first == last)
                break;
            nums[last] = nums[first];
            --last;
        }
        nums[first] = pivot;
        return first;
    }

    int findKthLargest(vector<int> &nums, int first, int last, int k) {
        if (first == last)
            return nums[first];
        int pivot_index = partition(nums, first, last);
        if (pivot_index - first + 1 == k)
            return nums[pivot_index];
        else if (pivot_index - first + 1 > k)
            return findKthLargest(nums, first, pivot_index - 1, k);
        else
            return findKthLargest(nums, pivot_index + 1, last, k - (pivot_index - first + 1));
    }
};


/*
 * 堆操作，默认大顶堆
 */

// 向上调整一次
void siftUp(int nums[], int n, int i,
            std::function<bool(int, int)> Compare = std::less<int>()) {
    int temp = nums[i];
    int j = (i - 1) / 2;
    while (j > 0 && Compare(nums[j], temp)) {
        nums[i] = nums[j];
        i = j;
        j = (i - 1) / 2;
    }
    nums[i] = temp;
}

// 向下调整一次
void siftDown(int nums[], int n, int i,
              std::function<bool(int, int)> Compare = std::less<int>()) {
    int temp = nums[i];
    int j = 2 * i + 1;
    while (j < n) {
        if (j + 1 < n && Compare(nums[j], nums[j + 1]))
            ++j;
        if (Compare(nums[j], temp))
            break;
        nums[i] = nums[j];
        i = j;
        j = 2 * i + 1;
    }
    nums[i] = temp;
}

// 建堆
void makeHeap(vector<int> &nums,
        std::function<bool(int, int)> Compare = std::less<int>()) {
    int n = static_cast<int>(nums.size());
    for (int i = n / 2 - 1; i >= 0; --i)
        siftDown(nums.data(), n, i, Compare);
}

// 添加元素到堆
void pushHeap(vector<int> &nums, int value,
              std::function<bool(int, int)> Compare = std::less<int>()) {
    nums.push_back(value);
    int n = static_cast<int>(nums.size());
    siftUp(nums.data(), n, n - 1, Compare);
}

// 将堆顶元素移动到末尾并使前n-1个元素成堆
void popHeap(vector<int> &nums,
             std::function<bool(int, int)> Compare = std::less<int>()) {
    if (nums.empty())
        return;
    std::swap(nums.front(), nums.back());
    siftDown(nums.data(), static_cast<int>(nums.size()) - 1, 0, Compare);
}

// 替换堆顶元素
void replaceHeapTop(vector<int> &nums, int value,
                    std::function<bool(int, int)> Compare = std::less<int>()) {
    nums.front() = value;
    siftDown(nums.data(), static_cast<int>(nums.size()), 0, Compare);
}

/*
 * 原数组上建大顶堆，然后弹出k-1个数，此时堆顶元素即可第k大的数。时间复杂度O(n log n)。
 */
class Solution1 {
public:
    int findKthLargest(vector<int> &nums, int k) {
        makeHeap(nums);
        for (int i = 0; i < k - 1; ++i) {
            popHeap(nums);
            nums.pop_back();
        }
        return nums[0];
    }
};

/*
 * 取数组前k个数建小顶堆，然后对数组剩下的元素，逐个与堆顶比较，如果比堆顶大则替换堆顶，这样
 * 可以得到最大的k个数，且堆顶元素为这k个数中的最小者，即为所求元素。
 * 时间复杂度O(n log k + k)。
 */
class Solution2 {
public:
    int findKthLargest(vector<int> &nums, int k) {
        vector<int> heap(nums.begin(), nums.begin() + k);
        makeHeap(heap, std::greater<int>());
        for (int i = k; i < nums.size(); ++i) {
            if (nums[i] > heap[0])
                replaceHeapTop(heap, nums[i], std::greater<int>());
        }
        return heap.front();
    }
};

int main() {
    // 5
    vector<int> nums1 = {3, 2, 1, 5, 6, 4};
    int k1 = 2;

    // 4
    vector<int> nums2 = {3, 2, 3, 1, 2, 4, 5, 5, 6};
    int k2 = 4;

    // 2
    vector<int> nums3 = {-1, 2, 0};
    int k3 = 1;

    // 5
    vector<int> nums4 = {3, 2, 1, 5, 6, 4};
    int k4 = 2;

    // 1
    vector<int> nums5 = {2, 1};
    int k5 = 2;

    Solution1 solution;
    cout << solution.findKthLargest(nums1, k1) << endl;
    cout << solution.findKthLargest(nums2, k2) << endl;
    cout << solution.findKthLargest(nums3, k3) << endl;
    cout << solution.findKthLargest(nums4, k4) << endl;
    cout << solution.findKthLargest(nums5, k5) << endl;

    return 0;
}
