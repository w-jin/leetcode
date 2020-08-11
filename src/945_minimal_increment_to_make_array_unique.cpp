#include <iostream>
#include <vector>
#include <unordered_map>
#include <algorithm>

using std::cout;
using std::endl;
using std::vector;
using std::unordered_map;

/*
    排序，然后一个一个的增大数组元素，并记录当前的最大值，对于数组中的元素x，如果x大于当前最大值，
    则它不需要调整，如果x小于等于当前最大值，则将大增大到最大值加1。
    时间复杂度O(N log N)，空间复杂度O(1)。
*/
class Solution {
public:
    int minIncrementForUnique(vector<int> &A) {
        if (A.empty())
            return 0;

        std::sort(A.begin(), A.end());

        int minimum = A[0];
        int min_increment = 0;
        for (int i = 1; i < A.size(); ++i) {
            if (A[i] > minimum) {
                minimum = A[i];
                continue;
            }
            ++minimum;
            min_increment += minimum - A[i];
            // A[i] = minimum;
        }

        return min_increment;
    }
};

/*
    使用哈希表存储所有数，以快速查找某个元素是否已在数组中。
    注意：不要一边遍历哈希表，又一边插入元素到哈希表。
    超时！
 */
class Solution1 {
public:
    int minIncrementForUnique(vector<int> &A) {
        if (A.empty())
            return 0;

        unordered_map<int, int> counts;
        for (int n : A)
            ++counts[n];

        int increment = 0;
        for (int n : A) {
            auto p = counts.find(n);
            int i = 1;
            while (p->second > 1) {
                while (counts.find(p->first + i) != counts.end())
                    ++i;
                counts[p->first + i] = 1;
                --(p->second);
                increment += i;
                ++i;
            }
        }

        return increment;
    }
};

/*
    使用一个长度为80000的数组记录各个数字出现的次数，然后对出现次数多于1次的部分全部加1，然后处理
    下一个位置。之所以长度是80000，是因为如果有40000个40000，则最后一个元素将调整到79999，所以数组
    长度应当为80000以保证不越界。
*/
class Solution2 {
public:
    int minIncrementForUnique(vector<int> &A) {
        if (A.empty())
            return 0;

        int counts[80000] = {0};
        for (int n : A)
            ++counts[n];

        int increment = 0;
        for (int i = 0; i < 80000; ++i) {
            if (counts[i] <= 1)
                continue;
            counts[i + 1] += counts[i] - 1;
            increment += counts[i] - 1;
        }

        return increment;
    }
};

int main() {
    // 1
    vector<int> A1 = {1, 2, 2};

    // 6
    vector<int> A2 = {3, 2, 1, 2, 1, 7};

    Solution1 solution;
    cout << solution.minIncrementForUnique(A1) << endl;
    cout << solution.minIncrementForUnique(A2) << endl;

    return 0;
}
