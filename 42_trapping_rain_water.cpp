#include <iostream>
#include <vector>
#include <stack>
#include <algorithm>

class Solution {
public:
    int trap(const std::vector<int> &height) {
        if (height.size() < 3)
            return 0;

        //生成各柱子右侧所有柱子的最大高度
        std::vector<int> right_max(height.size());
        right_max.back() = 0;
        for (int i = static_cast<int>(height.size()) - 2; i >= 0; --i)
            right_max[i] = std::max(right_max[i + 1], height[i + 1]);

        //各柱子上方能接的雨水水位就是左右两侧柱子最大高度的较小值
        int rain = 0;
        int left_max = 0;
        for (int i = 1; i < height.size(); ++i) {
            left_max = std::max(left_max, height[i - 1]);
            //如果左右两侧柱子最大高度的较小值比当前柱子矮，这根柱子上方装不下雨水
            rain += std::max(std::min(left_max, right_max[i]) - height[i], 0);
        }

        return rain;
    }
};

/*
    单调栈算法
*/
class Solution1 {
public:
    int trap(const std::vector<int> &height) {
        if (height.size() < 3)
            return 0;

        // 严格单调递增栈，记录递减的柱子下标
        std::stack<int> ascending_stack;
        ascending_stack.push(0);

        int rain = 0;
        for (int i = 1; i < height.size(); ++i) {
            // 将比height[i]小的元素出栈
            int top = 0;
            while (true) {
                top = ascending_stack.top();  // 不会出错
                if (height[top] > height[i])
                    break;

                ascending_stack.pop();
                if (ascending_stack.empty()) {
                    rain -= (height[i] - height[top]) * (i - top - 1);
                    break;
                }

                rain += (height[i] - height[top]) * (top - ascending_stack.top());
            }

            ascending_stack.push(i);
        }

        return rain;
    }
};

int main() {
    Solution1 solution;
    std::vector<int> height = {0, 1, 0, 2, 1, 0, 1, 3, 2, 1, 2, 1}; // 6
    std::cout << solution.trap(height) << std::endl;

    return 0;
}
