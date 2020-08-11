#include <iostream>
#include <vector>
#include <algorithm>

/* 暴力算法，尝试所有组合，如果当前组合已经超过target，则不再继续向里面增加数字，直接尝试下一个数字 */
class Solution {
public:
    std::vector<std::vector<int>> combinationSum(std::vector<int> &candidates, int target) {
        result.clear();
        combination.clear();
        solve(candidates, target, 0);
        return result;
    }

private:
    void solve(const std::vector<int> &candidates, int target, int step) {
        if (target == 0) {
            result.push_back(combination);
            return;
        }

        for (int i = step; i < candidates.size(); ++i) {
            if (candidates[i] <= target) {
                combination.push_back(candidates[i]);
                solve(candidates, target - candidates[i], i);
                combination.pop_back();
            }
        }
    }

    std::vector<int> combination;
    std::vector<std::vector<int>> result;
};

/* 改进，先对数组进行排序，如果当前组合已经超过target，不仅不再向里面增加数字，后面的数字也不用再尝试，直接回溯即可 */
class Solution1 {
public:
    std::vector<std::vector<int>> combinationSum(std::vector<int> &candidates, int target) {
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

        for (int i = step; i < candidates.size(); ++i) {
            if (candidates[i] > target)
                return;
            combination.push_back(candidates[i]);
            solve(candidates, target - candidates[i], i);
            combination.pop_back();
        }
    }

    std::vector<int> combination;
    std::vector<std::vector<int>> result;
};

/* 改进，使用循环实现，节省函数调用开销 */
class Solution2 {
public:
    //TODO:此版本未完成
    std::vector<std::vector<int>> combinationSum(std::vector<int> &candidates, int target) {
        std::vector<std::vector<int>> result;
        if (target == 0 || candidates.empty())
            return result;

        std::sort(candidates.begin(), candidates.end());
        if (candidates.front() > target)
            return result;

        std::vector<int> combination;
        std::vector<int> step;
        combination.push_back(candidates.front());
        step.push_back(0);
        target -= candidates.front();

        while (!combination.empty()) {
            if (target == 0) {
                result.push_back(combination);
                target = combination.back();
                combination.pop_back();
                step.pop_back();
                ++step.back();
            }
            else if (target < 0) {
                target += combination.back();
                combination.pop_back();
                step.pop_back();
                ++step.back();
            }
            else {
                target -= candidates[step.back()];
                combination.push_back(candidates[step.back()]);
                step.push_back(step.back());
            }
        }

        return result;
    }
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
    // 7
    // 2, 2, 3
    std::vector<int> candidates1 = {2, 3, 6, 7};
    int target1 = 7;

    // 2, 2, 2, 2
    // 2, 3, 3
    // 3, 5
    std::vector<int> candidates2 = {2, 3, 5};
    int target2 = 8;

    Solution2 solution;
    std::vector<std::vector<int>> result1 = solution.combinationSum(candidates1, target1),
                                  result2 = solution.combinationSum(candidates2, target2);

    std::cout << result1 << std::endl << result2 << std::endl;

    return 0;
}
