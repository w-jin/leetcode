#include <vector>
#include <unordered_map>
#include <stack>
#include "tree.hpp"

using std::vector;

/*
 * 最坏情况下，二叉树严重左斜，每次在中序遍历中查找根节点时需要遍历数组节点个数为剩余节点个数，
 * 所以时间复杂度O(n^2)。空间复杂度为O(h)，其中h是二叉树高度，这些空间用于保存运行时栈。
 */
class Solution {
public:
    TreeNode *buildTree(vector<int> &preorder, vector<int> &inorder) {
        return buildTree(preorder, 0, static_cast<int>(preorder.size()) - 1,
                         inorder, 0, static_cast<int>(inorder.size()) - 1);
    }

private:
    TreeNode *buildTree(vector<int> &preorder, int pre_first, int pre_last,
                        vector<int> &inorder, int in_first, int in_last) {
        if (pre_first > pre_last)
            return nullptr;

        // 前序遍历第一个必为根节点
        auto *root = new TreeNode(preorder[pre_first]);

        // 在中序中找到根节点，根节点之前为左子树，之后为右子树
        int root_pos = in_first;
        while (inorder[root_pos] != root->val)
            ++root_pos;

        // 创建左子树
        root->left = buildTree(preorder, pre_first + 1, pre_first + root_pos - in_first,
                               inorder, in_first, root_pos - 1);

        // 创建右子树
        root->right = buildTree(preorder, pre_first + root_pos - in_first + 1, pre_last,
                                inorder, root_pos + 1, in_last);

        return root;
    }
};

/*
 * 优化：使用哈希表快速定位根节点在inorder中的位置。
 * 时间复杂度O(n)，空间复杂度O(n+h)。
 */
class Solution1 {
public:
    TreeNode *buildTree(vector<int> &preorder, vector<int> &inorder) {
        inorder_map.clear();
        for (int i = 0; i < inorder.size(); ++i)
            inorder_map[inorder[i]] = i;
        return buildTree(preorder, 0, static_cast<int>(preorder.size()) - 1,
                         inorder, 0, static_cast<int>(inorder.size()) - 1);
    }

private:
    std::unordered_map<int, int> inorder_map;

    TreeNode *buildTree(vector<int> &preorder, int pre_first, int pre_last,
                        vector<int> &inorder, int in_first, int in_last) {
        if (pre_first > pre_last)
            return nullptr;

        // 前序遍历第一个必为根节点
        auto *root = new TreeNode(preorder[pre_first]);

        // 在中序中找到根节点，根节点之前为左子树，之后为右子树
        int root_pos = inorder_map[root->val];

        // 创建左子树
        root->left = buildTree(preorder, pre_first + 1, pre_first + root_pos - in_first,
                               inorder, in_first, root_pos - 1);

        // 创建右子树
        root->right = buildTree(preorder, pre_first + root_pos - in_first + 1, pre_last,
                                inorder, root_pos + 1, in_last);

        return root;
    }
};

/*
 * 迭代实现。
 */
class Solution2 {
public:
    TreeNode *buildTree(vector<int> &preorder, vector<int> &inorder) {
        if (preorder.empty())
            return nullptr;

        std::unordered_map<int, int> inorder_map;
        for (int i = 0; i < inorder.size(); ++i)
            inorder_map[inorder[i]] = i;

        auto *root = new TreeNode(preorder[0]);
        std::stack<TreeNode *> s;       // 保存等待创建右子树的节点
        TreeNode *p = root;
        for (int i = 1; i < preorder.size(); ++i) {
            // 它是p的左孩子
            if (inorder_map[preorder[i]] < inorder_map[p->val]) {
                p->left = new TreeNode(preorder[i]);
                s.push(p);
                p = p->left;
            } else {   // 它不是p的左孩子，则它是p或者p某个祖先的右孩子
                // 若它是节点q的右孩子，则它必在q之后且在q的上一个等待创建右子树的节点之前
                while (!s.empty() && inorder_map[preorder[i]] > inorder_map[s.top()->val]) {
                    p = s.top();
                    s.pop();
                }
                p->right = new TreeNode(preorder[i]);
                p = p->right;
            }
        }

        return root;
    }
};

int main() {
    // 3, 9, 20, 0, 0, 15, 7
    vector<int> preorder1 = {3, 9, 20, 15, 7};
    vector<int> inorder1 = {9, 3, 15, 20, 7};

    Solution1 solution;
    TreeNode *tree1 = solution.buildTree(preorder1, inorder1);

    PrintTreeByLevel(tree1);

    DestroyTree(tree1);
    return 0;
}
