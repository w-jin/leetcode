#include <iostream>
#include <vector>
#include <cmath>

using std::cout;
using std::endl;
using std::vector;

class Solution {
public:
    vector<vector<int>> findContinuousSequence(int target) {
        if (target <= 0)
            return {};

        vector<vector<int>> result;
        for (int start = 1; start < (target + 1) / 2; ++start) {
            int sum = 0;
            int i = start;
            while (sum < target) {
                sum += i;
                ++i;
            }
            if (sum == target) {
                vector<int> seq(i - start);
                for (int j = 0; j < seq.size(); ++j)
                    seq[j] = start + j;
                result.push_back(seq);
            }
        }

        return result;
    }
};

class Solution1 {
public:
    vector<vector<int>> findContinuousSequence(int target) {
        if (target <= 2)
            return {};

        vector<vector<int>> result;

        int left = 1;
        int right = 2;
        int sum = 3;
        while (left < (target + 1) / 2) {
            if (sum == target) {
                result.emplace_back();
                for (int i = left; i <= right; ++i)
                    result.back().push_back(i);

                sum -= left;
                ++left;
                ++right;
                sum += right;
            } else if (sum < target) {
                ++right;
                sum += right;
            } else {
                sum -= left;
                ++left;
            }
        }

        return result;
    }
};

class Solution2 {
public:
    vector<vector<int>> findContinuousSequence(int target) {
        if (target <= 2)
            return {};

        vector<vector<int>> result;

        for (int x = 1; x < (target + 1) / 2; ++x) {
            long long delta = 1 + 4 * (1ll * x * x - x + 2 * target);
            auto sqrt_delta = static_cast<int>(0.5 + sqrt(static_cast<double>(delta)));
            if (1ll * sqrt_delta * sqrt_delta != delta)
                continue;
            int y = (sqrt_delta - 1) / 2;

            result.emplace_back();
            for (int i = x; i <= y; ++i)
                result.back().push_back(i);
        }

        return result;
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

std::ostream &operator<<(std::ostream &out, const vector<vector<int>> &vec) {
    if (vec.empty()) {
        out << "[]";
        return out;
    }

    out << "[";
    for (int i = 0; i + 1 < vec.size(); ++i)
        out << "[" << vec[i] << "], ";
    out << "[" << vec.back() << "]]";

    return out;
}

int main() {
    // [[2, 3, 4], [4, 5]]
    int target1 = 9;

    // [[1, 2, 3, 4, 5], [4, 5, 6], [7, 8]]
    int target2 = 15;

    Solution1 solution;
    cout << solution.findContinuousSequence(target1) << endl;
    cout << solution.findContinuousSequence(target2) << endl;

    return 0;
}
