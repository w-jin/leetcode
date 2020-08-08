#include <iostream>
#include <vector>
#include <algorithm>

using std::cout;
using std::endl;
using std::vector;

/*
    动态规划算法，用coin_change[amount]表示最小硬币数量，则
    coin_change[amount] = min{coin_change[amount - Ci]} + 1，其中Ci遍历所有硬币面值，
    当然Ci需要跳过大于amount的硬币。
    如果某个amount无法用硬币表示出来，则amount-Ci也无法表示，直到到达一个小于所有面额的amount，
    它将保持初始值，所以将数组coin_change的初始值设置为一个比较大的值，在递推过程中，所有无法表示
    的金额对应的数组元素值都是较大的值，可以轻松判断出它们无法表示。
*/
class Solution {
public:
    int coinChange(vector<int> &coins, int amount) {
        vector<int> coin_change(amount + 1, amount + 1);
        coin_change[0] = 0;

        for (int i = 1; i <= amount; ++i) {
            for (int coin : coins) {
                if (coin > i) // 硬币面值太大
                    continue;
                coin_change[i] = std::min(coin_change[i], coin_change[i - coin] + 1);
            }
        }

        return coin_change[amount] > amount ? -1 : coin_change[amount];
    }
};

/*
    深度优先+剪枝。
    优先选择面额较大的硬币可以有效减少硬币数量：选出面额最大的硬币c并将它从硬币堆中移除，然后依次
    选择amount/c到0个c，求解coinChange(coins, amount - i * c)，如果它返回-1则不能表示，
    否则结果为返回值加i。
    但这样可能无法得到最优解，如硬币为[1, 3, 4]，amount为6，按照这种方法得到的结果为4+1+1，
    共3个，而3+3显然为一个更好的选择，因此仍然需要遍历所有情况，但可以根据当前最少硬币数量记录
    进行剪枝，一旦数量即将超过最少记录，即可直接返回-1不用再算。
*/
class Solution1 {
public:
    int coinChange(vector<int> &coins, int amount) {
        min_coins = amount + 1;
        std::sort(coins.begin(), coins.end());
        coinChangeRecursive(coins, amount, 0);
        return min_coins > amount ? -1 : min_coins;
    }

private:
    void coinChangeRecursive(vector<int> &coins, int amount, int num_coins) {
        if (amount == 0) {
            min_coins = std::min(min_coins, num_coins);
            return;
        }
        if (coins.empty() || coins.front() > amount)
            return;

        int max_coin = coins.back();
        coins.pop_back();

        for (int i = amount / max_coin; i >= 0; --i) {
            // 看上去应当写continue，因为当i减小时可以满足num_coins + i < min_coins，
            // 其实不然，当i减小时势必要用更多小额硬币来凑足总额，所以减小i无异于饮鸠止渴。
            if (num_coins + i >= min_coins)
                break;
            coinChangeRecursive(coins, amount - i * max_coin, num_coins + i);
        }

        coins.push_back(max_coin);
    }

    int min_coins = 0;
};

int main() {
    // 3. 11 = 5 + 5 + 1
    vector<int> coins1 = {1, 2, 5};
    int amount1 = 11;

    // -1
    vector<int> coins2 = {2};
    int amount2 = 3;

    // 20
    vector<int> coins3 = {186, 419, 83, 408};
    int amount3 = 6249;

    Solution1 solution;
    cout << solution.coinChange(coins1, amount1) << endl;
    cout << solution.coinChange(coins2, amount2) << endl;
    cout << solution.coinChange(coins3, amount3) << endl;

    return 0;
}
