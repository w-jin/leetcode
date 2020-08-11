#include <iostream>
#include <vector>
#include <queue>
#include <functional>

using std::cout;
using std::endl;
using std::vector;
using std::priority_queue;

/*
    对整个数组建立优先队列(小顶堆)，然后弹出前k小的元素。
    时间复杂度O(N)，空间复杂度O(N)。
    最慢！80ms
*/
class Solution {
public:
    vector<int> getLeastNumbers(vector<int> &arr, int k) {
        if (k == 0)
            return {};

        vector<int> result(k);

        priority_queue<int, vector<int>, std::greater<int>> q(arr.begin(), arr.end());
        for (int i = 0; i < k; ++i) {
            result[i] = q.top();
            q.pop();
        }

        return result;
    }
};

/*
    维护一个保存最小的k个数的优先队列(大顶堆)，遍历数组，把小于堆顶的元素加入堆中，并把堆顶弹出。
    时间复杂度O(N log k)，空间复杂度O(k)。
    比solution2慢！68ms
*/
class Solution1 {
public:
    vector<int> getLeastNumbers(vector<int> &arr, int k) {
        if (k == 0)
            return {};

        priority_queue<int> q;  // 保存最小的k个数，堆顶为最大元素，可快速判断新元素是否更小
        for (int i = 0; i < k; ++i)
            q.push(arr[i]);
        for (int i = k; i < arr.size(); ++i) {
            if (arr[i] < q.top()) {
                q.pop();
                q.push(arr[i]);
            }
        }

        vector<int> result(k);
        for (int i = 0; i < k; ++i) {
            result[i] = q.top();
            q.pop();
        }

        return result;
    }
};

/*
    使用快排的划分操作快速查找第k小的数，同时此数前面的数必然全部小于k，返回这些数即可。
    时间复杂度O(N)，空间复杂度O(1)。
    次优！24ms
*/
class Solution2 {
public:
    vector<int> getLeastNumbers(vector<int> &arr, int k) {
        if (k == 0)
            return {};

        int left = 0;
        int right = static_cast<int>(arr.size()) - 1;
        int pos = partition(arr, left, right);

        while (pos != k - 1) {
            if (pos < k - 1)
                left = pos + 1;
            else
                right = pos - 1;
            pos = partition(arr, left, right);
        }

        vector<int> result(k);
        for (int i = 0; i < k; ++i)
            result[i] = arr[i];

        return result;
    }

private:
    int partition(vector<int> &nums, int left, int right) {
        int pivot = nums[left];
        int l = left;
        int r = right;
        while (l < r) {
            while (l < r && nums[r] >= pivot)
                --r;
            if (l == r)
                break;
            nums[l] = nums[r];

            while (l < r && nums[l] <= pivot)
                ++l;
            if (l == r)
                break;
            nums[r] = nums[l];
        }
        nums[l] = pivot;
        return l;
    }
};

/*
    仍然使用优先队列维护最小的k个数，但是自己实现小顶堆，以减少不必要的操作：
        1、直接把堆存储在结果数组里
        2、替换堆的最大元素时直接替换堆顶然后做一个siftDown，而不是先弹出再入队
    效果最好！16ms
 */
class Solution3 {
public:
    vector<int> getLeastNumbers(vector<int> &arr, int k) {
        if (k == 0)
            return {};

        vector<int> heap(arr.begin(), arr.begin() + k);
        makeHeap(heap.data(), k);
        for (int i = k; i < arr.size(); ++i) {
            if (arr[i] < heap[0]) {
                replaceTop(heap.data(), k, arr[i]);
            }
        }

        return heap;
    }

private:
    void siftDown(int A[], int n, int i) {
        int temp = A[i];
        int j = 2 * i + 1;
        while (j < n) {
            if (j + 1 < n && A[j] <= A[j + 1])
                ++j;
            if (A[j] <= temp)
                break;
            A[i] = A[j];
            i = j;
            j = 2 * i + 1;
        }
        A[i] = temp;
    }

    void makeHeap(int A[], int n) {
        for (int i = n / 2 - 1; i >= 0; --i)
            siftDown(A, n, i);
    }

    void replaceTop(int A[], int n, int value) {
        A[0] = value;
        siftDown(A, n, 0);
    }
};

std::ostream &operator<<(std::ostream &out, const vector<int> &vec) {
    if (vec.empty())
        return out;

    for (int i = 0; i + 1 < vec.size(); ++i)
        out << vec[i] << ", ";
    out << vec.back();

    return out;
}

int main() {
    // 1, 2或者2, 1
    vector<int> arr1 = {3, 2, 1};
    int k1 = 2;

    // 0
    vector<int> arr2 = {0, 1, 2, 1};
    int k2 = 1;

    Solution3 solution;
    cout << solution.getLeastNumbers(arr1, k1) << endl;
    cout << solution.getLeastNumbers(arr2, k2) << endl;

    return 0;
}
