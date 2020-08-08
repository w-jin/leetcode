#include <iostream>
#include <vector>
#include <queue>

using std::cout;
using std::endl;
using std::vector;
using std::pair;

/*
 * 参考23，合并这n行，直到找到第k小的元素。
 * 时间复杂度O(k log n)，空间复杂度O(n)。
 */
class Solution {
public:
    int kthSmallest(vector<vector<int>> &matrix, int k) {
        // 以matrix的各行首元素建立小顶堆
        auto compare = [&matrix](pair<int, int> a, pair<int, int> b) -> bool {
            // 越界的认为它比较大
            if (a.first >= matrix.size() || a.second >= matrix.size())
                return true;
            if (b.first >= matrix.size() || b.second >= matrix.size())
                return false;
            return matrix[a.first][a.second] > matrix[b.first][b.second];
        };
        std::priority_queue<pair<int, int>,
                vector<pair<int, int>>, decltype(compare)> min_heap(compare);
        for (int i = 0; i < matrix.size(); ++i)
            min_heap.emplace(i, 0);

        // 寻找第k小的元素
        pair<int, int> p;
        for (int i = 0; i < k; ++i) {
            p = min_heap.top();
            min_heap.pop();
            min_heap.emplace(p.first, p.second + 1);
        }

        return matrix[p.first][p.second];
    }
};


/*
 * 二分搜索。matrix[0][0]中是最小的一个数，而matrix[n-1][n-1]中是最大的一个数，所求的数必然
 * 在这两个数之间，对于每个数，求出有多少个数小于等于它，若不到k个，则所求的数比它大，否则比它小。
 * Q1: 如何保证最后得到的数必然在数组中?
 * A1: 参考upper_bound的实现，当小于等于m的数刚好k个时，令last=m，则m仍然在搜索范围内，
 *     如果m不在数组中，则first会逐渐逼近m，直到某个mid在数组中且mid和last之间无其它元素在
 *     数组中，然后刚好有k个数小于等于mid，然后last=mid则已经定位到数组中的元素了。
 *
 * Q2: 如何计算数组中有多少个元素小于等于mid?
 * A2: 假设mid=7，而数组为：
 *         1  2  3  4  5  6  7  8
 *         2  3  4  5  6  7  8  9
 *         3  4  5  6  7  8  9 10
 *         4  5  6  7  8  9 10 11
 *         5  6  7  8  9 10 11 12
 *         6  7  8  9 10 11 12 13
 *         7  8  9 10 11 12 13 14
 *         8  9 10 11 12 13 14 15
 *     可以看到小于等于7的数都集中在左上角，沿副对角线分布，这是因为假定M[i][j]>7，则
 *     M[i+1][j]>M[i][j]>7，所以下一行刚好大于7的元素必然更靠前。这样在计算每行有多少个元素
 *     小于等于mid时只需要从当前列向前找第一个小于等于mid的元素位置即可。
 *
 * 每次计算有多少个元素小于等于mid最多需要查找n次，所以时间复杂度O(n * log(max - min))，
 * 空间复杂度O(1)。
 */
class Solution1 {
public:
    int kthSmallest(vector<vector<int>> &matrix, int k) {
        int first = matrix.front().front();
        int last = matrix.back().back();
        while (first < last) {
            int mid = first + (last - first) / 2;

            // 计算有多少个数比mid小，这些数集中在左上角，连续分布
            int min_nums = 0;
            int j = static_cast<int>(matrix.size()) - 1;
            for (int i = 0; i < matrix.size(); ++i) {
                while (j >= 0 && matrix[i][j] > mid)
                    --j;
                min_nums += j + 1;
            }

            if (min_nums < k)
                first = mid + 1;
            else
                last = mid;
        }

        return first;
    }
};

int main() {
    // 13
    vector<vector<int>> matrix1 = {
            {1,  5,  9},
            {10, 11, 13},
            {12, 13, 15}
    };
    int k1 = 8;

    Solution1 solution;
    cout << solution.kthSmallest(matrix1, k1) << endl;

    return 0;
}
