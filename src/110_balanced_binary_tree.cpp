#include <iostream>
#include "tree.hpp"

class Solution {
public:
    bool isBalanced(TreeNode *root) {
        return isBalancedRecursive(root) >= 0;
    }

private:
    int isBalancedRecursive(TreeNode *root) {
        if (!root)
            return 0;

        int d1 = isBalancedRecursive(root->left);
        if (d1 < 0)
            return -1;

        int d2 = isBalancedRecursive(root->right);
        if (d2 < 0 || abs(d1 - d2) > 1)
            return -1;

        return 1 + std::max(d1, d2);
    }
};

int main() {
    // true
    TreeNode *root1 = CreateTree({3, 9, 20, 0, 0, 15, 7});

    // false
    TreeNode *root2 = CreateTree({1, 2, 2, 3, 3, 0, 0, 4, 4});

    Solution solution;
    std::cout << std::boolalpha;
    std::cout << solution.isBalanced(root1) << std::endl;
    std::cout << solution.isBalanced(root2) << std::endl;

    DestroyTree(root1);
    DestroyTree(root2);

    return 0;
}
