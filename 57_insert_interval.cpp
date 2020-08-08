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
    std::vector<Interval> insert(std::vector<Interval> &intervals, Interval newInterval) {
        std::vector<Interval> result;
        if (intervals.empty()) {
            result.push_back(newInterval);
            return result;
        }

        int i = 0;
        while (i < intervals.size() && intervals[i].end < newInterval.start) {
            result.push_back(intervals[i]);
            ++i;
        }

        if (i == intervals.size()) {
            result.push_back(newInterval);
            return result;
        }

        int start = std::min(intervals[i].start, newInterval.start);
        int end = newInterval.end;
        while (i < intervals.size() && intervals[i].start <= end) {
            end = std::max(end, intervals[i].end);
            ++i;
        }
        result.emplace_back(start, end);

        while (i < intervals.size()) {
            result.push_back(intervals[i]);
            ++i;
        }

        return result;
    }
};

std::ostream &operator<<(std::ostream &out, const std::vector<Interval> &intervals) {
    for (const auto &i : intervals)
        out << "[" << i.start << ", " << i.end << "] ";
    return out;
}

int main()
{
    //[1, 5], [6, 9]
    std::vector<Interval> intervals1 = {{1, 3}, {6, 9}};
    Interval newInterval1 = {2, 5};
    std::cout << Solution().insert(intervals1, newInterval1) << std::endl;

    //[1, 2], [3, 10], [12, 16]
    std::vector<Interval> intervals2 = {{1, 2}, {3, 5}, {6, 7}, {8, 10}, {12, 16}};
    Interval newInterval2 = {4, 8};
    std::cout << Solution().insert(intervals2, newInterval2) << std::endl;

    //[1, 5], [6, 8]
    std::vector<Interval> intervals3 = {{1, 5}};
    Interval newInterval3 = {6, 8};
    std::cout << Solution().insert(intervals3, newInterval3) << std::endl;

    return 0;
}
