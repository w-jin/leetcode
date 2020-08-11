#include <iostream>
#include "tree.hpp"

class Solution {
public:
    TreeNode *lowestCommonAncestor(TreeNode *root, TreeNode *p, TreeNode *q) {
        helper(root, p, q);
        return result;
    }

private:
    TreeNode *result = nullptr;

    int helper(TreeNode *root, TreeNode *p, TreeNode *q) {
        if (!root)
            return 0;
        int r1 = helper(root->left, p, q);
        int r2 = helper(root->right, p, q);
        int r3 = (root == p || root == q) ? 1 : 0;
        if (1 == r1 && 1 == r2 || 1 == r1 && 1 == r3 || 1 == r2 && 1 == r3)
            result = root;
        return r1 + r2 + r3;
    }
};

int main() {
    return 0;
}
