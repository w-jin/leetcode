#include <iostream>
#include <limits>
#include "tree.hpp"

class Solution {
public:
    int maxPathSum(TreeNode *root) {
        if (!root)
            return 0;

        // 不包含root的，左右里面取较大者
        int left = std::numeric_limits<int>::min();
        int right = std::numeric_limits<int>::min();
        if (root->left)
            left = maxPathSum(root->left);
        if (root->right)
            right = maxPathSum(root->right);
        int exclude_root = std::max(left, right);

        // 包含root的，以左右孩子为根的路径最大权重加上root
        left = maxPathSumRoot(root->left);
        right = maxPathSumRoot(root->right);
        int include_root = left + right + root->val;

        return std::max(exclude_root, include_root);
    }

private:
    // 计算以root为根的路径的最大权重和
    int maxPathSumRoot(TreeNode *root) {
        if (!root)
            return 0;

        int left = maxPathSumRoot(root->left);
        int right = maxPathSumRoot(root->right);
        int curr = std::max(left, right) + root->val;
        curr = std::max(curr, 0);

        return curr;
    }
};

/*
    提升性能，只用遍历一次。使用分治算法，对于一棵树root，最大路径有两种情况：1、包含root节点，
    则此路径横跨左右子树，且在左右子树的部分为一条从根节点向下的路径；2、不包含root节点，则此路径
    位于左子树中或者右子树中。

    问题分为两个部分，首先解决从根节点向下的路径中的最大权重和问题。设函数f(TreeNode *root)返
    回从root向下的路径中的最大权重和，则有
    f(root) = max{f(root->left), f(root->right), 0} + root->val;
    之所以和0比较是因为不要求每条路径都到叶子节点，因此如果没有权重和为正数的子路径，可以直接把根
    节点自身当作最大路径。

    接下来解决整个问题。设函数maxPathSum返回最大路径权重和，则有
    maxPathSum(root) = max{max{0, f(root->left)} + max{0, f(root->right)} + root->val,
            maxPathSum(root->left), maxPathSum(root->right)}

    把两个问题合并到一个函数中：
    {f, max_sum} = maxPathSum(root) {
        fl, ml = maxPathSum(root->left);
        fr, mr = maxPathSum(root->right);
        return {
            max{fl, fr, 0} + root->val,
            max{max{fl, 0} + max{fr, 0} + root->val, ml, mr};
        };
    }
*/
class Solution1 {
public:
    int maxPathSum(TreeNode *root) {
        if (!root)
            return 0;

        int root_path = 0;
        int max_sum = 0;

        maxPathSum(root, root_path, max_sum);
        return max_sum;
    }

private:
    void maxPathSum(TreeNode *root, int &root_path, int &max_sum) {
        // 防止最小路径和是负数，初始值应当设置为负无穷
        int left_path = std::numeric_limits<int>::min();
        int right_path = std::numeric_limits<int>::min();
        int left_max_sum = std::numeric_limits<int>::min();
        int right_max_sum = std::numeric_limits<int>::min();

        if (root->left)
            maxPathSum(root->left, left_path, left_max_sum);
        if (root->right)
            maxPathSum(root->right, right_path, right_max_sum);

        left_path = std::max(0, left_path);
        right_path = std::max(0, right_path);

        root_path = std::max(left_path, right_path) + root->val;

        int with_root = left_path + right_path + root->val;
        max_sum = std::max(with_root, std::max(left_max_sum, right_max_sum));
    }
};

/*
    另一种写法，在遍历左子树和右子树时直接比较它们的最大路径和(结果记录在全局变量中)，而不是返回后比较。
*/
class Solution2 {
public:
    int maxPathSum(TreeNode *root) {
        if (!root)
            return 0;

        max_sum = std::numeric_limits<int>::min();
        maxPathSumRecursive(root);
        return max_sum;
    }

private:
    int maxPathSumRecursive(TreeNode *root) {
        // 防止最小路径和是负数，初始值应当设置为负无穷
        int left_path = std::numeric_limits<int>::min();
        int right_path = std::numeric_limits<int>::min();

        if (root->left)
            left_path = maxPathSumRecursive(root->left);
        if (root->right)
            right_path = maxPathSumRecursive(root->right);

        left_path = std::max(0, left_path);
        right_path = std::max(0, right_path);

        max_sum = std::max(left_path + right_path + root->val, max_sum);

        return std::max(left_path, right_path) + root->val;
    }

    int max_sum = 0;
};

int main() {
    // 6
    TreeNode *tree1 = CreateTree({1, 2, 3});

    // 42
    TreeNode *tree2 = CreateTree({-10, 9, 20, 0, 0, 15, 7});

    // -3
    TreeNode *tree3 = CreateTree({-3});

    // 2
    TreeNode *tree4 = CreateTree({2, -1});

    // 48
    TreeNode *tree5 = CreateTree({5, 4, 8, 11, 0, 13, 4, 7, 2, 0, 0, 0, 1});

    // 16
    TreeNode *tree6 = CreateTree({9, 6, -3, 0, 0, -6, 2, 0, 0, 2, 0, -6, -6, -6});

    Solution1 solution;
    std::cout << solution.maxPathSum(tree1) << std::endl;
    std::cout << solution.maxPathSum(tree2) << std::endl;
    std::cout << solution.maxPathSum(tree3) << std::endl;
    std::cout << solution.maxPathSum(tree4) << std::endl;
    std::cout << solution.maxPathSum(tree5) << std::endl;
    std::cout << solution.maxPathSum(tree6) << std::endl;

    DestroyTree(tree1);
    DestroyTree(tree2);
    DestroyTree(tree3);
    DestroyTree(tree4);
    DestroyTree(tree5);
    DestroyTree(tree6);

    return 0;
}
