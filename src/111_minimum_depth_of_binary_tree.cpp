#include <iostream>
#include "tree.hpp"

class Solution {
public:
    int minDepth(TreeNode *root) {
        if (!root)
            return 0;
        else if (root->left && root->right)
            return std::min(minDepth(root->left), minDepth(root->right)) + 1;
        else if (root->left && !root->right)
            return minDepth(root->left) + 1;
        else if (!root->left && root->right)
            return minDepth(root->right) + 1;
        else // if (!root->left && !root->right)
            return 1;
    }
};

int main() {
    // 2
    TreeNode *root1 = CreateTree({3, 9, 20, 0, 0, 15, 7});

    Solution solution;
    std::cout << solution.minDepth(root1) << std::endl;

    DestroyTree(root1);

    return 0;
}
