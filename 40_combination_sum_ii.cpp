#include <iostream>
#include <vector>
#include <algorithm>

class Solution {
public:
    std::vector<std::vector<int>> combinationSum2(std::vector<int> &candidates, int target) {
        std::sort(candidates.begin(), candidates.end());
        combination.clear();
        result.clear();
        solve(candidates, target, 0);
        return result;
    }

private:
    void solve(const std::vector<int> &candidates, int target, int step) {
        if (target == 0) {
            result.push_back(combination);
            return;
        }

        //如果当前要入栈的元素和刚刚出栈的元素的相等就会造成重复的组合
        int just_pop = 0;
        for (int i = step; i < candidates.size(); ++i) {
            if (candidates[i] > target)
                return;
            if (candidates[i] == just_pop)
                continue;
            combination.push_back(candidates[i]);
            solve(candidates, target - candidates[i], i + 1);
            just_pop = combination.back();
            combination.pop_back();
        }
    }

    std::vector<int> combination;
    std::vector<std::vector<int>> result;
};

std::ostream &operator<<(std::ostream &out, const std::vector<std::vector<int>> &vec)
{
    for (const auto &v : vec) {
        for (int i : v)
            out << i << " ";
        out << std::endl;
    }
    return out;
}

int main()
{
    // 1, 7
    // 1, 2, 5
    // 2, 6
    // 1, 1, 6
    std::vector<int> candidates1 = {10, 1, 2, 7, 6, 1, 5};
    int target1 = 8;

    // 1, 2, 2
    // 5
    std::vector<int> candidates2 = {2, 5, 2, 1, 2};
    int target2 = 5;

    Solution solution;
    std::vector<std::vector<int>> result1 = solution.combinationSum2(candidates1, target1),
                                  result2 = solution.combinationSum2(candidates2, target2);

    std::cout << result1 << std::endl << result2 << std::endl;

    return 0;
}
