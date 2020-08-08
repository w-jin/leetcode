#include <iostream>
#include <vector>
#include <algorithm>

using std::vector;
using std::cout;
using std::endl;

class Solution {
public:
    int maxProfit(const vector<int> &prices) {
        if (prices.empty())
            return 0;

        int max_profit = 0;
        int min_pre = prices[0];
        for (int i = 1; i < prices.size(); ++i) {
            if (min_pre < prices[i])
                max_profit = std::max(max_profit, prices[i] - min_pre);
            else
                min_pre = prices[i];
        }

        return max_profit;
    }
};

int main() {
    // 5
    vector<int> prices1 = {7, 1, 5, 3, 6, 4};

    // 0
    vector<int> prices2 = {7, 6, 4, 3, 1};

    Solution solution;
    cout << solution.maxProfit(prices1) << endl;
    cout << solution.maxProfit(prices2) << endl;

    return 0;
}
