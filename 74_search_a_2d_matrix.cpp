#include <iostream>
#include <vector>

/* 二分搜索，先搜索到在哪一行，再在此行中搜索在哪一列，时间复杂度O(log(mn)) */
class Solution {
public:
    bool searchMatrix(const std::vector<std::vector<int>> & matrix, int target) {
        if (matrix.empty() || matrix[0].empty())
            return false;

        // 先搜索在哪行
        int left = 0, right = static_cast<int>(matrix.size()) - 1;
        while (left < right) {
            int mid = left + (right - left) / 2;
            if (target == matrix[mid][0])
                return true;
            else if (target > matrix[mid][0]) {
                // 下一行行首大于target，则target就在mid这一行内
                if (target < matrix[mid + 1][0]) {
                    left = mid;
                    break;
                }
                // 否则在第[mid+1, right]行内
                left = mid + 1;
            }
            else
                right = mid - 1;
        }

        if (left > right)
            return false;

        int row = left;
        left = 0;
        right = static_cast<int>(matrix[0].size()) - 1;
        while (left <= right) {
            int mid = left + (right - left) / 2;
            if (target == matrix[row][mid])
                return true;
            else if (target > matrix[row][mid])
                left = mid + 1;
            else
                right = mid - 1;
        }

        return false;
    }
};

/* 二分搜索，直接将矩阵看成一维的来搜索，时间复杂度O(log(mn)) */
class Solution1 {
public:
    bool searchMatrix(const std::vector<std::vector<int>> & matrix, int target) {
        if (matrix.empty() || matrix[0].empty())
            return false;

        int m = static_cast<int>(matrix.size());
        int n = static_cast<int>(matrix[0].size());
        int left = 0, right = m * n - 1;
        while (left <= right) {
            int mid = left + (right - left) / 2;
            int i = mid / n, j = mid % n;
            if (target == matrix[i][j])
                return true;
            else if (target > matrix[i][j])
                left = mid + 1;
            else
                right = mid - 1;
        }

        return false;
    }
};

/* 线性搜索，先找到在哪一行，再在此行内找在哪一列，时间复杂度O(m+n) */
class Solution2 {
public:
    bool searchMatrix(const std::vector<std::vector<int>> & matrix, int target) {
        if (matrix.empty() || matrix[0].empty())
            return false;

        int i = static_cast<int>(matrix.size()) - 1;
        while (i >= 0 && matrix[i][0] > target)
            --i;

        if (i < 0)
            return false;

        int j = 0;
        while (j < matrix[0].size() && matrix[i][j] < target)
            ++j;

        return j < matrix[0].size() && target == matrix[i][j];
    }
};

int main() {
    // true
    int target1 = 3;
    std::vector<std::vector<int>> matrix1 = {
            {1,  3,  5,  7},
            {10, 11, 16, 20},
            {23, 30, 34, 50}
    };

    // false
    int target2 = 13;
    std::vector<std::vector<int>> matrix2 = {
            {1,  3,  5,  7},
            {10, 11, 16, 20},
            {23, 30, 34, 50}
    };

    Solution2 solution;
    std::cout << std::boolalpha;
    std::cout << solution.searchMatrix(matrix1, target1) << std::endl;
    std::cout << solution.searchMatrix(matrix2, target2) << std::endl;

    return 0;
}
