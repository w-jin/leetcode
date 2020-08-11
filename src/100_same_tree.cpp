#include <iostream>
#include "tree.hpp"

using std::cout;
using std::endl;

class Solution {
public:
    bool isSameTree(TreeNode* p, TreeNode* q) {
        if (!p && !q)
            return true;
        if (!(p && q) || p->val != q->val)
            return false;
        return isSameTree(p->left, q->left) && isSameTree(p->right, q->right);
    }
};

int main() {
    // true
    TreeNode *root1_1 = CreateTree({1, 2, 3});
    TreeNode *root2_1 = CreateTree({1, 2, 3});

    // false
    TreeNode *root1_2 = CreateTree({1, 2});
    TreeNode *root2_2 = CreateTree({1, 0, 2});

    // false
    TreeNode *root1_3 = CreateTree({1, 2, 1});
    TreeNode *root2_3 = CreateTree({1, 1, 2});

    Solution solution;
    cout << std::boolalpha;
    cout << solution.isSameTree(root1_1, root2_1) << endl;
    cout << solution.isSameTree(root1_2, root2_2) << endl;
    cout << solution.isSameTree(root1_3, root2_3) << endl;

    return 0;
}
