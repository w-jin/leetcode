#include <iostream>
#include <vector>
#include <stack>
#include <algorithm>

/*
    动态规划算法。先计算第i行在范围[0,j]中以j结尾的最大宽度保存在max_width[i][j]中，然后遍历
    所有点，对每个点，计算以它为右下角的最大矩形面积，具体方法为：高度为1的矩形最大面积为
    max_width[i][j]，高度为2的矩形最大面积为2 * min{max_width[i][j-1, j]}，高度为3的矩
    形最大面积为3 * min{max_width[i][j-2, j-1, j]}，以此类推。
    时间复杂度O(M^2 * N)，空间复杂度O(MN)，其中M和N分别为行数(高)和列数(宽)。
*/
class Solution {
public:
    int maximalRectangle(std::vector<std::vector<char>> &matrix) {
        if (matrix.empty())
            return 0;
        if (matrix.front().empty())
            return 0;

        const int M = static_cast<int>(matrix.size());
        const int N = static_cast<int>(matrix.front().size());

        std::vector<std::vector<int>> max_width(M, std::vector<int>(N));
        for (int i = 0; i < M; ++i) {
            if (matrix[i][0] == '0')
                max_width[i][0] = 0;
            else
                max_width[i][0] = 1;
            for (int j = 1; j < N; ++j) {
                if (matrix[i][j] == '0')
                    max_width[i][j] = 0;
                else
                    max_width[i][j] = max_width[i][j - 1] + 1;
            }
        }

        int max_size = 0;
        for (int i = 0; i < M; ++i) {
            for (int j = 0; j < N; ++j) {
                max_size = std::max(max_size, max_width[i][j]);
                int min_width = max_width[i][j];
                for (int k = i - 1; k >= 0 && min_width > 0; --k) {
                    min_width = std::min(min_width, max_width[k][j]);
                    max_size = std::max(max_size, (i - k + 1) * min_width);
                }
            }
        }

        return max_size;
    }
};


/*
    对每层，计算以此层为底的柱形图高度，计算每列高度时从'0'处断开，然后求此柱形图的最大矩形面积，
    亦即第84题。时间复杂度O(M * N)，空间复杂度O(N)，其中M和N分别为行数(高)和列数(宽)。
*/
class Solution1 {
public:
    int maximalRectangle(std::vector<std::vector<char>> &matrix) {
        if (matrix.empty())
            return 0;
        if (matrix[0].empty())
            return 0;

        const int M = static_cast<int>(matrix.size());
        const int N = static_cast<int>(matrix[0].size());

        int max_size = 0;
        std::vector<int> heights(N, 0);
        for (int i = 0; i < M; ++i) {
            for (int j = 0; j < N; ++j) {
                if (matrix[i][j] == '0')
                    heights[j] = 0;
                else
                    heights[j] = heights[j] + 1;
            }

            max_size = std::max(max_size, maximalRectangleInHistogram(heights));
        }

        return max_size;
    }

private:
    // leetcode 84
    int maximalRectangleInHistogram(const std::vector<int> &heights) {
        if (heights.empty())
            return 0;

        int max_size = 0;
        const int N = static_cast<int>(heights.size());

        // 严格单调递减栈
        std::stack<int> descending_stack;
        descending_stack.push(0);
        for (int i = 1; i < N; ++i) {
            // 将大于heights[i]的出栈
            while (true) {
                int top = descending_stack.top();
                if (heights[i] > heights[top])
                    break;
                descending_stack.pop();
                if (descending_stack.empty()) {
                    max_size = std::max(max_size, i * heights[top]);
                    break;
                }
                max_size = std::max(max_size, (i - descending_stack.top() - 1) * heights[top]);
            }

            // 将heights[i]入栈，可以维持栈的单调性
            descending_stack.push(i);
        }

        // 栈内必定还有元素
        while (true) {
            int top = descending_stack.top();
            descending_stack.pop();
            if (descending_stack.empty()) {
                max_size = std::max(max_size, N * heights[top]);
                break;
            }
            max_size = std::max(max_size, (N - descending_stack.top() - 1) * heights[top]);
        }

        return max_size;
    }
};

/*
    动态规划算法，对每个位置，计算其上最大高度，然后向两边延伸，计算最大宽度，得到一个面积，
    最大面积必为这些面积中的一个。
    时间复杂度O(M * N)，空间复杂度O(N)，其中M和N分别为矩阵的行数(高)和列数(宽)。
*/
class Solution2 {
public:
    int maximalRectangle(std::vector<std::vector<char>> &matrix) {
        if (matrix.empty())
            return 0;
        if (matrix[0].empty())
            return 0;

        const int M = static_cast<int>(matrix.size());
        const int N = static_cast<int>(matrix[0].size());

        std::vector<int> heights(N, 0);
        std::vector<int> left(N, 0);  // 第一行只看本行，left和right的初值应分别为0和N
        std::vector<int> right(N, N);

        int max_size = 0;
        for (int i = 0; i < M; ++i) {
            int curr_left = 0;
            for (int j = 0; j < N; ++j) {
                if (matrix[i][j] == '0') {
                    heights[j] = 0;
                    curr_left = j + 1;

                    // 本行用不上，置为0是不对下一行限制，此行此列为0，下行此列高度最大为1，
                    // 向左向右延伸只看下行的左边和右边最近的0的位置，所以left[j]和right[j]
                    // 应该分别置为0和N
                    left[j] = 0;
                } else {
                    heights[j] += 1;
                    left[j] = std::max(left[j], curr_left);
                }
            }

            int curr_right = N;
            for (int j = N - 1; j >= 0; --j) {
                if (matrix[i][j] == '0') {
                    curr_right = j;
                    right[j] = N;
                } else {
                    right[j] = std::min(right[j], curr_right);
                }
            }

            for (int j = 0; j < N; ++j) {
                max_size = std::max(max_size, (right[j] - left[j]) * heights[j]);
            }
        }

        return max_size;
    }
};

int main() {
    // 6
    std::vector<std::vector<char>> matrix{
            {'1', '0', '1', '0', '0'},
            {'1', '0', '1', '1', '1'},
            {'1', '1', '1', '1', '1'},
            {'1', '0', '0', '1', '0'},
    };

    Solution1 solution;
    std::cout << solution.maximalRectangle(matrix) << "\n";

    return 0;
}
