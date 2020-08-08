#include <iostream>
#include <vector>
#include <algorithm>

using std::cout;
using std::endl;
using std::vector;

/*
 * 时间复杂度O(n^2)，空间复杂度O(1)。
 * 超时！
 */
class Solution {
public:
    int maxScoreSightseeingPair(vector<int> &A) {
        int max_score = 0;
        for (int i = 0; i < A.size(); ++i) {
            for (int j = i + 1; j < A.size(); ++j)
                max_score = std::max(A[i] + A[j] + i - j, max_score);
        }

        return max_score;
    }
};

/*
 * 分治：递归计算左半部分和右半部分，然后计算横跨中间的组合。计算横跨中间的组合时，从中点开始计
 * 算，将较小的数往边上推。
 * 反例：
 *  6 4 1 0 2
 * 首先尝试(4, 1)，为4
 * 然后是(4, 0)，为3
 * 然后是(4, 2)，为3
 * 然后是(6, 2)，为4
 * 结果为4, 3, 3, 4中的最大值4。但是正确答案为(6, 1)，结果为5
 */

/*
 * 分治：递归计算左半部分和右半部分，然后计算横跨中间的组合。计算横跨中间的组合时，从中点开始计
 * 算，两边往外推时选择能带来正收益的一边，如果两边都能带来正收益，则两边同时往外推，如果都不能
 * 则结束计算。
 * 如何计算是否有正收益？当前位置i往右推至j时，如果A[j]-(j-i)>A[i]则有正收益。当前位置i往左
 * 推至j时，如果A[j]-(i-j)>A[i]则有正收益。
 * 时间复杂度O(n log n)，空间复杂度O(log n)。
 */
class Solution1 {
public:
    int maxScoreSightseeingPair(const vector<int> &A) {
        if (A.empty())
            return 0;
        return maxScoreSightseeingPair(A, 0, static_cast<int>(A.size()) - 1);
    }

private:
    int maxScoreSightseeingPair(const vector<int> &A, int first, int last) {
        if (first >= last)
            return 0;

        int mid = first + (last - first) / 2;
        int left_score = maxScoreSightseeingPair(A, first, mid);
        int right_score = maxScoreSightseeingPair(A, mid + 1, last);

        int left = mid;
        int j = left - 1;
        while (j >= first) {
            while (j >= first && A[j] - (left - j) <= A[left])
                --j;
            if (j >= first) {
                left = j;
                --j;
            }
        }

        int right = mid + 1;
        j = right + 1;
        while (j <= last) {
            while (j <= last && A[j] - (j - right) <= A[right])
                ++j;
            if (j <= last) {
                right = j;
                ++j;
            }
        }

        return std::max(A[left] + A[right] - (right - left), std::max(left_score, right_score));
    }
};

/*
 * 对任意元素A[j]，在其左边选择A[i]+i最大的元素进行组合。这是因为当前位置curr往左推至i时，
 * 如果A[i]-(curr-i)>A[curr]则有正收益，即A[i]+i>A[curr]+curr，所以A[i]+i最大的元素具有最大收益。
 * 时间复杂度O(n)，空间复杂度O(1)。
 */
class Solution2 {
public:
    int maxScoreSightseeingPair(const vector<int> &A) {
        int max_score = 0;
        int left_max = 0;
        for (int j = 1; j < A.size(); ++j) {
            left_max = std::max(left_max, A[j - 1] + j - 1);
            max_score = std::max(max_score, left_max + A[j] - j);
        }

        return max_score;
    }
};

int main() {
    // 11
    vector<int> A1 = {8, 1, 5, 2, 6};

    // 9
    vector<int> A2 = {3, 7, 2, 3};

    // 13
    vector<int> A3 = {4, 7, 5, 8};

    Solution1 solution;
    cout << solution.maxScoreSightseeingPair(A1) << endl;
    cout << solution.maxScoreSightseeingPair(A2) << endl;
    cout << solution.maxScoreSightseeingPair(A3) << endl;

    return 0;
}
