#include <iostream>
#include <vector>
#include <stack>
#include <algorithm>

/*
    时间复杂度T(N)=2T(N/2)+O(N)=O(N log N)
*/
class Solution {
public:
    int largestRectangleArea(std::vector<int> &heights) {
        if (heights.empty())
            return 0;
        return LargestRectangleAreaRecursive(heights, 0, static_cast<int>(heights.size()) - 1);
    }

private:
    int LargestRectangleAreaRecursive(std::vector<int> &heights, int left, int right) {
        if (left == right)
            return heights[left];

        int mid = left + (right - left) / 2;

        int left_largest = LargestRectangleAreaRecursive(heights, left, mid);
        int right_largest = LargestRectangleAreaRecursive(heights, mid + 1, right);

        // 跨过mid和mid+1的最大面积，往左和往右两个方向尽量选择高度较高的
        int min_height = heights[mid] < heights[mid + 1] ? heights[mid] : heights[mid + 1];
        int mid_largest = 2 * min_height;
        int i = mid - 1;
        int j = mid + 2;
        while (i >= left && j <= right) {
            if (heights[i] > heights[j]) {   // 左边高，往左
                if (min_height > heights[i])
                    min_height = heights[i];
                if ((j - i) * min_height > mid_largest)
                    mid_largest = (j - i) * min_height;
                --i;
            } else {                        // 右边高，往右
                if (min_height > heights[j])
                    min_height = heights[j];
                if ((j - i) * min_height > mid_largest)
                    mid_largest = (j - i) * min_height;
                ++j;
            }
        }
        // 左右可能有一个方向会剩余一些没有尝试过，这两个循环最多只会执行一个
        while (i >= left) {
            if (min_height > heights[i])
                min_height = heights[i];
            if ((j - i) * min_height > mid_largest)
                mid_largest = (j - i) * min_height;
            --i;
        }
        while (j <= right) {
            if (min_height > heights[j])
                min_height = heights[j];
            if ((j - i) * min_height > mid_largest)
                mid_largest = (j - i) * min_height;
            ++j;
        }

        // 返回三者中最大的一个
        int left_right_largest = left_largest > right_largest ? left_largest : right_largest;
        return left_right_largest > mid_largest ? left_right_largest : mid_largest;
    }
};

/*
    时间复杂度O(N^2)
*/
class Solution1 {
public:
    int largestRectangleArea(std::vector<int> &heights) {
        if (heights.empty())
            return 0;

        int largest = 0;
        for (int i = 0; i < heights.size(); ++i) {
            int min_height = heights[i];
            if (largest < heights[i])
                largest = heights[i];
            for (int j = i + 1; j < heights.size(); ++j) {
                if (min_height > heights[j])
                    min_height = heights[j];
                if (largest < (j - i + 1) * min_height)
                    largest = (j - i + 1) * min_height;
            }
        }

        return largest;
    }
};

/*
    对第i根柱子，往左找第一个比它低的，往右找第一个比它低的，比较当前最大矩阵面积和两者之间的柱子
    能构成的最大矩形面积。如果越过第一个比它低的，找的最大矩形面积和以第一个比它低的为中心，按上
    面方法找到的最大矩形面积是一样的，所以能遍历所有可能的解。
    寻找第i根柱子往左数第一个比它低的柱子时，如果它比第i-1根柱子低，则它一定比第left_min[i-1]+1
    到第i-1根柱子都低，所以可以令j=left_min[i-1]来跳过这些柱子。同样地，如果它比第left_min[i-1]
    根柱子低，则它比第left_min[ left_min[i-1] ]+1根柱子到第left_min[i-1]根柱子都低，可以令
    j=left_min[ left_min[i-1] ]来跳过这些柱子。依此类推可得此解法。
    时间复杂度O(N)，空间复杂度O(N)
*/
class Solution2 {
public:
    int largestRectangleArea(std::vector<int> &heights) {
        if (heights.empty())
            return 0;

        const int N = static_cast<int>(heights.size());
        std::vector<int> left_min(N);
        std::vector<int> right_min(N);

        left_min[0] = -1;
        for (int i = 1; i < left_min.size(); ++i) {
            int j = i - 1;
            while (j >= 0 && heights[j] >= heights[i])
                j = left_min[j];
            left_min[i] = j;
        }

        right_min[N - 1] = N;
        for (int i = N - 2; i >= 0; --i) {
            int j = i + 1;
            while (j < N && heights[j] >= heights[i])
                 j = right_min[j];
            right_min[i] = j;
        }

        int largest = 0;
        for (int i = 0; i < N; ++i)
            largest = std::max(largest, heights[i] * (right_min[i] - left_min[i] - 1));

        return largest;
    }
};

/*
    单调栈算法，每个元素入栈一次，出栈一次，时间复杂度O(N)
*/
class Solution3 {
public:
    int largestRectangleArea(std::vector<int> &heights) {
        if (heights.empty())
            return 0;

        const int N = static_cast<int>(heights.size());

        // 严格单调递减栈，保存严格单调递增柱子的下标
        std::stack<int> descending_stack;
        descending_stack.push(0);

        int largest = 0;
        for (int i = 1; i < N; ++i) {
            // 将所有高于本柱子的元素出栈
            while (true) {
                int top = descending_stack.top();
                if (heights[i] > heights[top])
                    break;
                descending_stack.pop();

                if (descending_stack.empty()) {
                    largest = std::max(largest, heights[top] * i);
                    break;
                }
                largest = std::max(largest, heights[top] * (i - descending_stack.top() - 1));
            }
            descending_stack.push(i);
        }

        while (!descending_stack.empty()) {
            int top = descending_stack.top();
            descending_stack.pop();
            if (descending_stack.empty())
                largest = std::max(largest, heights[top] * N);
            else
                largest = std::max(largest, heights[top] * (N - descending_stack.top() - 1));
        }

        return largest;
    }
};


int main() {
    // 10
    std::vector<int> heights1 = {2, 1, 5, 6, 2, 3};

    // 3
    std::vector<int> heights2 = {2, 1, 2};

    // 9
    std::vector<int> heights3 = {1, 2, 3, 4, 5};

    Solution3 solution;
    std::cout << solution.largestRectangleArea(heights1) << "\n";
    std::cout << solution.largestRectangleArea(heights2) << "\n";
    std::cout << solution.largestRectangleArea(heights3) << "\n";

    return 0;
}
