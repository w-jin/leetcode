#include <iostream>
#include <stack>
#include <climits>
#include "tree.hpp"

/*
    中序遍历得到递增序列
*/
class Solution {
public:
    bool isValidBST(TreeNode *root) {
        if (!root)
            return true;

        int prev_val = 0;
        std::stack<TreeNode *> s;
        TreeNode *p = root;

        // 先一直往左遍历，直到没有左子树
        while (p->left) {
            s.push(p);
            p = p->left;
        }
        prev_val = p->val;
        p = p->right;

        while (p || !s.empty()) {
            if (p) {
                s.push(p);
                p = p->left;
            } else {
                p = s.top();
                s.pop();

                if (p->val <= prev_val)
                    return false;
                prev_val = p->val;

                p = p->right;
            }
        }

        return true;
    }
};


/*
    由定义判断，向下递归时判断
*/
class Solution1 {
public:
    bool isValidBST(TreeNode *root) {
        if (!root)
            return true;
        return isValidBST(root, LONG_MIN, LONG_MAX);
    }

private:
    bool isValidBST(TreeNode *root, long long lower, long long upper) {
        if (!root)
            return true;
        if (root->val <= lower || root->val >= upper)
            return false;
        return isValidBST(root->left, lower, root->val) && isValidBST(root->right, root->val, upper);
    }
};


int main() {
    // true
    TreeNode *root1 = CreateTree({2, 1, 3});

    // false
    TreeNode *root2 = CreateTree({5, 1, 4, 0, 0, 3, 6});

    Solution solution;
    std::cout << std::boolalpha;
    std::cout << solution.isValidBST(root1) << std::endl;
    std::cout << solution.isValidBST(root2) << std::endl;

    DestroyTree(root1);
    DestroyTree(root2);
    return 0;
}
