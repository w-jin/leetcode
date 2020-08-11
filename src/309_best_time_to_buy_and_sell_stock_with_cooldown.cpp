#include <iostream>
#include <vector>
#include <algorithm>

using std::cout;
using std::endl;
using std::vector;

class Solution {
public:
    int maxProfit(const vector<int> &prices) {
        if (prices.empty())
            return 0;

        int profit0 = 0;
        int profit1 = -prices[0];
        int profit0_prev = 0;
        for (int i = 1; i < prices.size(); ++i) {
            int temp = profit0;
            profit0 = std::max(profit0, profit1 + prices[i]);
            profit1 = std::max(profit1, profit0_prev - prices[i]);
            profit0_prev = temp;
        }

        return profit0;
    }
};

int main() {
    // 3
    vector<int> prices1 = {1, 2, 3, 0, 2};

    Solution solution;
    cout << solution.maxProfit(prices1) << endl;

    return 0;
}
