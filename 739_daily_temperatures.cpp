#include <iostream>
#include <vector>
#include <stack>

using std::cout;
using std::endl;
using std::vector;

/*
 * 不考虑暴力法，使用单调栈求解。
 * 从后向前遍历，如果T中存在两个元素x>y，且x位置靠近0，则遍历越过x之后，不可能存在某个元素，从
 * 它起向右数第一个大于它的元素是y，因此遍历过程中，靠右的较小元素应当从工作集中剔除，这恰好是
 * 单调递增栈的功能。
 * 每个元素最多入栈一次出栈一次，所以时间复杂度为O(n)，空间复杂度为O(n)。
 */
class Solution {
public:
    vector<int> dailyTemperatures(vector<int> &T) {
        int n = static_cast<int>(T.size());
        vector<int> result(n);
        std::stack<int> ascending_stack;
        for (int i = n - 1; i >= 0; --i) {
            while (!ascending_stack.empty() && T[ascending_stack.top()] <= T[i])
                ascending_stack.pop();
            if (ascending_stack.empty())
                result[i] = 0;
            else
                result[i] = ascending_stack.top() - i;
            ascending_stack.push(i);
        }

        return result;
    }
};

/*
 * 单调栈算法。从前往后遍历，采用单调递减栈，对当前元素x，若栈中元素y<x，则x是y右边第一个大于y
 * 的元素，严格证明可用数学归纳法，此处不再赘述。
 * 时间复杂度O(n)，空间复杂度O(n)。
 */
class Solution1 {
public:
    vector<int> dailyTemperatures(vector<int> &T) {
        vector<int> result(T.size(), 0);
        std::stack<int> descending_stack;
        for (int i = 0; i < T.size(); ++i) {
            while (!descending_stack.empty() && T[descending_stack.top()] < T[i]) {
                result[descending_stack.top()] = i - descending_stack.top();
                descending_stack.pop();
            }
            descending_stack.push(i);
        }
        return result;
    }
};

std::ostream &operator<<(std::ostream &out, const vector<int> &vec) {
    if (vec.empty())
        return out;
    for (int i = 0; i + 1 < vec.size(); ++i)
        out << vec[i] << ", ";
    return out << vec.back();
}

int main() {
    // 1, 1, 4, 2, 1, 1, 0, 0
    vector<int> T1 = {73, 74, 75, 71, 69, 72, 76, 73};

    // 8, 1, 5, 4, 3, 2, 1, 1, 0, 0
    vector<int> T2 = {89, 62, 70, 58, 47, 47, 46, 76, 100, 70};

    Solution1 solution;
    cout << solution.dailyTemperatures(T1) << endl;
    cout << solution.dailyTemperatures(T2) << endl;

    return 0;
}
