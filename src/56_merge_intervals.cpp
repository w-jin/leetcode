#include <iostream>
#include <vector>
#include <algorithm>

struct Interval {
    int start;
    int end;

    Interval() : start(0), end(0) {}

    Interval(int s, int e) : start(s), end(e) {}
};

class Solution {
public:
    std::vector<Interval> merge(std::vector<Interval> &intervals) {
        std::sort(intervals.begin(), intervals.end(),
                  [](Interval a, Interval b) { return a.start < b.start; });

        std::vector<Interval> merged;
        int curr_start = 0, max_end = 0;
        int i = 0;
        while (i < intervals.size()) {
            curr_start = intervals[i].start;
            max_end = intervals[i].end;
            while (++i < intervals.size() && intervals[i].start <= max_end)
                max_end = std::max(max_end, intervals[i].end);
            merged.emplace_back(curr_start, max_end);
        }

        return merged;
    }
};

/*
    这道题被改过了，没有Interval这个类了，直接使用vector来保存区间端点。
 */
using std::vector;

class Solution1 {
public:
    vector<vector<int>> merge(vector<vector<int>> &intervals) {
        std::sort(intervals.begin(), intervals.end());
        vector<vector<int>> merged;
        int i = 0;
        while (i < intervals.size()) {
            int start = intervals[i][0];
            int end = intervals[i][1];
            while (++i < intervals.size() && intervals[i][0] <= end)
                end = std::max(end, intervals[i][1]);
            merged.push_back({start, end});
        }
        return merged;
    }
};

std::ostream &operator<<(std::ostream &out, const std::vector<Interval> &intervals) {
    for (const auto &i : intervals)
        out << "[" << i.start << ", " << i.end << "] ";
    return out;
}

std::ostream &operator<<(std::ostream &out, const std::vector<vector<int>> &intervals) {
    for (const auto &interval : intervals)
        out << "[" << interval[0] << ", " << interval[1] << "] ";
    return out;
}

int main() {
/*
    // [[1, 6], [8, 10], [15, 18]]
    std::vector<Interval> intervals1 = {{1,  3},
                                        {2,  6},
                                        {8,  10},
                                        {15, 18}};
    // [[1,5]]
    std::vector<Interval> intervals2 = {{1, 4},
                                        {4, 5}};
*/

    // [[1, 6], [8, 10], [15, 18]]
    std::vector<vector<int>> intervals1 = {{1,  3},
                                           {2,  6},
                                           {8,  10},
                                           {15, 18}};
    // [[1,5]]
    std::vector<vector<int>> intervals2 = {{1, 4},
                                           {4, 5}};

    Solution1 solution;
    std::cout << solution.merge(intervals1) << std::endl;
    std::cout << solution.merge(intervals2) << std::endl;

    return 0;
}
