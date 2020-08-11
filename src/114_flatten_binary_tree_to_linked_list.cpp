#include "tree.hpp"

/*
 * 递归算法。时间复杂度O(n)，空间复杂度O(n)。
 * 也可以使用递归或循环版本的前序遍历来实现，时间复杂度和空间复杂度和本算法一样。
 */
class Solution {
public:
    void flatten(TreeNode *root) {
        flattenRecursive(root);
    }

public:
    TreeNode *flattenRecursive(TreeNode *root) {
        if (!root)
            return nullptr;

        if (!root->left && !root->right)
            return root;
        else if (!root->left && root->right) {
            return flattenRecursive(root->right);
        } else if (root->left && !root->right) {
            TreeNode *left_tail = flattenRecursive(root->left);
            root->right = root->left;
            root->left = nullptr;
            return left_tail;
        } else {
            TreeNode *left_tail = flattenRecursive(root->left);
            TreeNode *right_tail = flattenRecursive(root->right);
            left_tail->right = root->right;
            root->right = root->left;
            root->left = nullptr;
            return right_tail;
        }
    }
};

/*
 * 寻找每个节点的前驱节点，然后将它链接到前驱节点后面，以减小空间复杂度。
 * 如果root只有右孩子，则什么也不做，如果root有左孩子，将右子树链接到左子树中的最后一个节点
 * 的右边，而左子树的最后一个节点的寻找也比较复杂，可以先将它放到从上到下第一个无右孩子的节点
 * 右边，留到以后处理。
 * 时间复杂度O(n)，空间复杂度O(1)。
 */
class Solution1 {
public:
    void flatten(TreeNode *root) {
        TreeNode *p = root;
        while (p) {
            if (p->left && !p->right) {
                p->right = p->left;
                p->left = 0;
            } else if (p->left && p->right) {
                TreeNode *prev = p->left;
                while (prev->right)
                    prev = prev->right;
                prev->right = p->right;
                p->right = p->left;
                p->left = nullptr;
            }
            p = p->right;
        }
    }

    void flatten1(TreeNode *root) {   // 简化逻辑
        TreeNode *p = root;
        while (p) {
            if (p->left) {
                TreeNode *prev = p->left;
                while (prev->right)
                    prev = prev->right;
                prev->right = p->right;
                p->right = p->left;
                p->left = nullptr;
            }
            p = p->right;
        }
    }
};

int main() {
    TreeNode *root1 = CreateTree({1, 2, 5, 3, 4, 0, 6});

    Solution1 solution;
    solution.flatten(root1);

    PrintBinaryTree(root1);

    DestroyTree(root1);

    return 0;
}
