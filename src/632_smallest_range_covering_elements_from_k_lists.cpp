#include <iostream>
#include <vector>
#include <queue>
#include <unordered_map>
#include <climits>

using std::cout;
using std::endl;
using std::vector;
using std::pair;

/*
 * 每个数组都取一个数放入优先队列，队列中的最小值和最大值作为区间端点，该区间是满足题目要求的
 * 区间，且可能为最小区间。然后将区间右移，具体做法为将队列的最小值弹出，将它所在数组的下一个
 * 元素入队，然后将队列的最小值和最大值作为区间端点，这样就得到了下一个可能的区间。最后一个区
 * 间是取下个区间对应的优先队列时，下标越界之前的那个区间，即优先队列中的最小值在数组中是最后
 * 一个元素，此时可以返回。
 * 时间复杂度O(nk log k)，空间复杂度O(k)。其中k为列表个数，n为列表元素个数的平均值。
 */
class Solution {
public:
    vector<int> smallestRange(const vector<vector<int>> &nums) {
        vector<int> min_interval = {-100000, 100000};
        vector<int> interval = {-100000, -100000};

        // 小顶堆，大于比较
        auto cmp = [&nums](pair<int, int> a, pair<int, int> b) -> bool {
            return nums[a.first][a.second] > nums[b.first][b.second];
        };

        std::priority_queue<pair<int, int>, vector<pair<int, int>>, decltype(cmp)> q(cmp);

        for (int i = 0; i < nums.size(); ++i) {
            if (!nums[i].empty()) {
                q.emplace(i, 0);
                interval[1] = std::max(interval[1], nums[i][0]);
            } else {
                return {-1, -1};  // 某个列表为空，不应当有这种情况出现
            }
        }
        interval[0] = nums[q.top().first][q.top().second];
        min_interval = interval;

        while (true) {
            auto p = q.top();
            q.pop();

            int next = p.second + 1;
            if (next == nums[p.first].size())
                return min_interval;

            q.emplace(p.first, next);
            interval[0] = nums[q.top().first][q.top().second];
            interval[1] = std::max(interval[1], nums[p.first][next]);

            if (interval[1] - interval[0] < min_interval[1] - min_interval[0])
                min_interval = interval;
        }
    }
};

/*
 * 使用哈希表+滑动窗口。时间复杂度O(kn + V)，空间复杂度O(nk)。其中k是列表数量，n是列表平均
 * 长度，V是列表元素值域，此处V<=200000。
 * 本方法时间复杂度看上去比另一个方法好，但实测效果不咋样！
 */
class Solution1 {
public:
    vector<int> smallestRange(vector<vector<int>>& nums) {
        int n = nums.size();
        std::unordered_map<int, vector<int>> indices;
        int xMin = INT_MAX, xMax = INT_MIN;
        for (int i = 0; i < n; ++i) {
            for (const int& x: nums[i]) {
                indices[x].push_back(i);
                xMin = std::min(xMin, x);
                xMax = std::max(xMax, x);
            }
        }

        vector<int> freq(n);
        int inside = 0;
        int left = xMin, right = xMin - 1;
        int bestLeft = xMin, bestRight = xMax;

        while (right < xMax) {
            ++right;
            if (indices.count(right)) {
                for (const int& x: indices[right]) {
                    ++freq[x];
                    if (freq[x] == 1) {
                        ++inside;
                    }
                }
                while (inside == n) {
                    if (right - left < bestRight - bestLeft) {
                        bestLeft = left;
                        bestRight = right;
                    }
                    if (indices.count(left)) {
                        for (const int& x: indices[left]) {
                            --freq[x];
                            if (freq[x] == 0) {
                                --inside;
                            }
                        }
                    }
                    ++left;
                }
            }
        }

        return {bestLeft, bestRight};
    }
};


std::ostream &operator<<(std::ostream &out, const vector<int> &vec) {
    return out << "[" << vec[0] << ", " << vec[1] << "]";
}

int main() {
    // [20, 24]
    vector<vector<int>> nums1 = {
            {4, 10, 15, 24, 26},
            {0, 9,  12, 20},
            {5, 18, 22, 30}
    };

    Solution solution;
    cout << solution.smallestRange(nums1) << endl;

    return 0;
}
