#include <iostream>
#include <vector>

using std::vector;
using std::cout;
using std::endl;

/*
    先计算可以交易的波谷和波峰，然后直接使用波谷和波峰进行计算，直接使用原数组进行计算也是一样的，
    但使用波谷和波峰可以减小遍历的长度。对于两次交易的最大收益，从某个位置分开，前面进行一次交易，
    后面进行一次交易，然后取两者收益和的最大值。各个位置划分后，前面和后面进行一次交易的最大收益
    先计算出来保存在数组中，这样就可以达到O(N)时间复杂度。空间复杂度也为O(N)。
*/
class Solution {
public:
    int maxProfit(vector<int> &prices) {
        if (prices.empty())
            return 0;

        // 计算出来的谷可能比峰多一个，但这个谷买入已无机会卖出，直接忽略即可。
        // 一开始可能会有一个峰，但无股票卖出，不予计算
        vector<int> valleys;
        vector<int> peaks;
        int i = 0;
        while (i < prices.size() - 1) {
            while (i < prices.size() - 1 && prices[i] >= prices[i + 1])
                ++i;
            valleys.push_back(prices[i]);
            while (i < prices.size() - 1 && prices[i] <= prices[i + 1])
                ++i;
            peaks.push_back(prices[i]);
        }

        // 递减序列没有峰，不进行交易
        if (peaks.empty())
            return 0;

        // 需要计算的波谷和波峰个数
        const int N = static_cast<int>(peaks.size());

        int max_profit = 0;

        // max_profit_left[i]表示[0,i]内一次交易的最大收益
        vector<int> max_profit_left(N);

        // max_profit_right[i]表示[i,N-1]内一次交易的最大收益
        vector<int> max_profit_right(N);

        // 从左往右算一次
        max_profit = 0;
        int min_left = valleys[0];
        for (int j = 0; j < N; ++j) {
            if (min_left > valleys[j])
                min_left = valleys[j];
            if (max_profit < peaks[j] - min_left)
                max_profit = peaks[j] - min_left;
            max_profit_left[j] = max_profit;
        }

        // 从右往左算一次
        max_profit = 0;
        int max_right = peaks.back();
        for (int j = N - 1; j >= 0; --j) {
            if (max_right < peaks[j])
                max_right = peaks[j];
            if (max_profit < max_right - valleys[j])
                max_profit = max_right - valleys[j];
            max_profit_right[j] = max_profit;
        }

        // 两次交易从k的后面划开
        for (int k = 0; k < N - 1; ++k) {
            if (max_profit_left[k] + max_profit_right[k + 1] > max_profit)
                max_profit = max_profit_left[k] + max_profit_right[k + 1];
        }

        return max_profit;
    }
};

int main() {
    // 6
    vector<int> prices1 = {3, 3, 5, 0, 0, 3, 1, 4};

    // 4
    vector<int> prices2 = {1, 2, 3, 4, 5};

    // 0
    vector<int> prices3 = {7, 6, 4, 3, 1};

    Solution solution;
    cout << solution.maxProfit(prices1) << endl;
    cout << solution.maxProfit(prices2) << endl;
    cout << solution.maxProfit(prices3) << endl;

    return 0;
}
