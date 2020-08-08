#include <iostream>
#include <queue>
#include "tree.hpp"

using std::cout;
using std::endl;

/*
 * 递归版本。时间复杂度O(n)，空间复杂度O(log n)。其中n为节点个数。
 */
class Solution {
public:
    bool isSymmetric(TreeNode *root) {
        if (!root)
            return true;
        return isSymmetric(root->left, root->right);
    }

private:
    /*
     * 递归比较两棵树是否镜像对称。需要满足：1、根节点值相等；2、左树的右子树与右树的左子树对称，
     * 且左树的左子树与右树的右子树对称。
     */
    bool isSymmetric(TreeNode *left, TreeNode *right) {
        if (!left && !right)  // 两个都空树
            return true;
        if (!left || !right)  // 一个为空一个不为空
            return false;
        if (left->val != right->val)  // 左树与右树根节点值不等
            return false;
        // 左树的右子树与右树的左子树对称，且左树的左子树与右树的右子树对称
        return isSymmetric(left->right, right->left)
               && isSymmetric(left->left, right->right);
    }
};

/*
 * 迭代版本。时间复杂度O(n)，空间复杂度O(n)。
 */
class Solution1 {
public:
    bool isSymmetric(TreeNode *root) {
        if (!root)
            return true;
        return isSymmetric(root->left, root->right);
    }

private:
    /*
     * 比较两棵树是否镜像对称。采用层序遍历，left遍历时先左后右，right遍历时先右后左，遍历过程
     * 中的所有节点的值都相等则对称，否则不对称。
     */
    bool isSymmetric(TreeNode *left, TreeNode *right) {
        std::queue<TreeNode *> queue_left;
        std::queue<TreeNode *> queue_right;
        queue_left.push(left);
        queue_right.push(right);
        while (!queue_left.empty() /* && !queue_right.empty() */) {  // size相同
            TreeNode *l = queue_left.front();
            TreeNode *r = queue_right.front();
            queue_left.pop();
            queue_right.pop();

            if (!l && !r)
                continue;
            if (!l || !r)
                return false;
            if (l->val != r->val)
                return false;

            queue_left.push(l->left);
            queue_left.push(l->right);
            queue_right.push(r->right);
            queue_right.push(r->left);
        }

        // return queue_left.empty() && queue_right.empty();
        return true;
    }
};

/*
 * 迭代版本，只使用一个队列。时间复杂度O(n)，空间复杂度O(n)。
 */
class Solution2 {
public:
    bool isSymmetric(TreeNode *root) {
        if (!root)
            return true;
        return isSymmetric(root->left, root->right);
    }

private:
    /*
     * 比较两棵树是否镜像对称。采用层序遍历，left遍历时先左后右，right遍历时先右后左，遍历过程
     * 中的所有节点的值都相等则对称，否则不对称。
     */
    bool isSymmetric(TreeNode *left, TreeNode *right) {
        std::queue<TreeNode *> q;
        q.push(left);
        q.push(right);
        while (!q.empty()) {
            left = q.front();
            q.pop();
            right = q.front();
            q.pop();

            if (!left && !right)
                continue;
            if (!left || !right)
                return false;
            if (left->val != right->val)
                return false;

            q.push(left->left);
            q.push(right->right);
            q.push(left->right);
            q.push(right->left);
        }

        return true;
    }
};

int main() {
    // true
    TreeNode *root1 = CreateTree({1, 2, 2, 3, 4, 4, 3});

    // false
    TreeNode *root2 = CreateTree({1, 2, 2, 0, 3, 0, 3});

    // false
    TreeNode *root3 = CreateTree({1, 2, 3});

    Solution1 solution;
    cout << std::boolalpha;
    cout << solution.isSymmetric(root1) << endl;
    cout << solution.isSymmetric(root2) << endl;
    cout << solution.isSymmetric(root3) << endl;

    DestroyTree(root1);
    DestroyTree(root2);
    DestroyTree(root3);

    return 0;
}
