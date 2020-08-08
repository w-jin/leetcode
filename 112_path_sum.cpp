#include <iostream>
#include "tree.hpp"

using std::cout;
using std::endl;

class Solution {
public:
    bool hasPathSum(TreeNode *root, int sum) {
        if (!root)
            return false;
        else if (!root->left && !root->right)
            return root->val == sum;
        else if (root->left && !root->right)
            return hasPathSum(root->left, sum - root->val);
        else if (!root->left && root->right)
            return hasPathSum(root->right, sum - root->val);
        else
            return hasPathSum(root->left, sum - root->val) ||
                   hasPathSum(root->right, sum - root->val);
    }
};

int main() {
    // true
    TreeNode *root1 = CreateTree({5, 4, 8, 11, 0, 13, 4, 7, 2, 0, 0, 0, 1});
    int sum1 = 22;

    // false
    TreeNode *root2 = CreateTree({1, 2});
    int sum2 = 1;

    Solution solution;
    cout << std::boolalpha;
    cout << solution.hasPathSum(root1, sum1) << endl;
    cout << solution.hasPathSum(root2, sum2) << endl;

    DestroyTree(root1);
    return 0;
}
