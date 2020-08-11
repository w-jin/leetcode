#include <iostream>
#include <algorithm>
#include <utility>
#include "tree.hpp"

using std::pair;

class Solution {
public:
    int diameterOfBinaryTree(TreeNode *root) {
        if (!root || (!root->left && !root->right))
            return 0;

        return diameterOfBinaryTreeRecursive(root).first - 1;
    }

private:
    // 计算一棵树的直径和它的高度，以节点个数计
    pair<int, int> diameterOfBinaryTreeRecursive(TreeNode *root) {
        if (!root)
            return {0, 0};

        auto left = diameterOfBinaryTreeRecursive(root->left);
        auto right = diameterOfBinaryTreeRecursive(root->right);

        int diameter = std::max(std::max(left.first, right.first),
                                left.second + right.second + 1);
        int height = std::max(left.second, right.second) + 1;
        return {diameter, height};
    }
};

int main() {
    // 3
    TreeNode *root1 = CreateTree({1, 2, 3, 4, 5});

    Solution solution;
    std::cout << solution.diameterOfBinaryTree(root1) << std::endl;

    DestroyTree(root1);

    return 0;
}

