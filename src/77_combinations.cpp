#include <iostream>
#include <vector>

class Solution {
public:
    std::vector<std::vector<int>> combine(int n, int k) {
        K = k;
        combination.resize(k);
        CombineRecursive(1, n, k);
        return result;
    }

    // 范围[m, N]中选k个数的组合
    void CombineRecursive(int m, int n, int k) {
        if (k == 0) {
            result.push_back(combination);
            return;
        }

        for (int i = m; i <= n; ++i) {
            combination[K - k] = i;
            CombineRecursive(i + 1, n, k - 1);
        }
    }

private:
    int K = 0;
    std::vector<int> combination;
    std::vector<std::vector<int>> result;
};

int main() {
    int n = 4;
    int k = 2;

    Solution solution;
    auto result = solution.combine(n, k);
    for (const auto &combination : result) {
        for (int i : combination)
            std::cout << i << "\t";
        std::cout << "\n";
    }

    return 0;
}
