#include <stack>
#include "tree.hpp"

class Solution {
public:
    void recoverTree(TreeNode *root) {
        last = first = second = nullptr;  // 同一个对象上多次调用此方法需作初始化

        // 中序遍历找出两个需要交换的节点，即第一个逆序的较大者和
        // 第二个逆序的较小者，或者一个逆序的两个节点
        InOder(root);

        // 交换它们的值
        if (first && second)
            std::swap(first->val, second->val);
    }

private:
    void InOder(TreeNode *root) {
        if (!root)
            return;

        // 处理左子树
        if (root->left)
            InOder(root->left);

        // 处理根节点，和中序遍历的前一个节点比较
        if (last && last->val > root->val) {
            if (!first) {
                first = last;
                second = root;  // 中序遍历中相邻两个节点需要交换的情况
            } else {
                second = root;  // 中序遍历中不相邻的两个节点需要交换的情况
            }
        }
        last = root;

        // 处理右子树
        if (root->right)
            InOder(root->right);
    }

    TreeNode *last = nullptr;
    TreeNode *first = nullptr;
    TreeNode *second = nullptr;
};

/*
    采用循环来做中序遍历。
*/
class Solution1 {
public:
    void recoverTree(TreeNode *root) {
        TreeNode *last = nullptr;
        TreeNode *first = nullptr;
        TreeNode *second = nullptr;

        std::stack<TreeNode *> st;
        TreeNode *p = root;
        while (p || !st.empty()) {
            if (p) {
                st.push(p);
                p = p->left;
            } else {
                p = st.top();
                st.pop();

                if (last && p->val < last->val) {
                    if (!first)
                        first = last;
                    second = p;
                }
                last = p;

                p = p->right;
            }
        }

        if (first && second)
            std::swap(first->val, second->val);
    }
};

int main() {
    // 3, 1, null, null, 2
    TreeNode *tree1 = CreateTree({1, 3, 0, 0, 2});

    // 2, 1, 4, null, null, 3
    TreeNode *tree2 = CreateTree({3, 1, 4, 0, 0, 2});

    Solution1 solution;

    solution.recoverTree(tree1);
    PrintTreeByLevel(tree1);

    solution.recoverTree(tree2);
    PrintTreeByLevel(tree2);

    DestroyTree(tree1);
    DestroyTree(tree2);
    return 0;
}
