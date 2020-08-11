#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>

using std::cout;
using std::endl;
using std::vector;

class Solution {
public:
    int minimumTotal(const vector<vector<int>> &triangle) {
        if (triangle.empty())
            return 0;

        const int N = triangle.size();

        vector<int> minimum_total(N, INT_MAX);
        minimum_total[0] = triangle[0][0];
        for (int i = 1; i < N; ++i) {
            for (int j = i; j > 0; --j)
                minimum_total[j] = std::min(minimum_total[j], minimum_total[j - 1]) + triangle[i][j];
            minimum_total[0] += triangle[i][0];
        }

        return *std::min_element(minimum_total.begin(), minimum_total.end());
    }
};

int main() {
    // 11
    vector<vector<int>> triangle1 = {
            {2},
            {3, 4},
            {6, 5, 7},
            {4, 1, 8, 3}
    };

    Solution solution;
    cout << solution.minimumTotal(triangle1) << endl;

    return 0;
}
