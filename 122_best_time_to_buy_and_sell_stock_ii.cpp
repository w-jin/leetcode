#include <iostream>
#include <vector>

using std::vector;
using std::cout;
using std::endl;

class Solution {
public:
    int maxProfit(const vector<int> &prices) {
        if (prices.empty())
            return 0;

        int max_profit = 0;
        for (int i = 1; i < prices.size(); ++i) {
            if (prices[i] > prices[i - 1])
                max_profit += prices[i] - prices[i - 1];
        }

        return max_profit;
    }
};

int main() {
    // 7
    vector<int> prices1 = {7, 1, 5, 3, 6, 4};

    // 4
    vector<int> prices2 = {1, 2, 3, 4, 5};

    Solution solution;
    cout << solution.maxProfit(prices1) << endl;
    cout << solution.maxProfit(prices2) << endl;

    return 0;
}
