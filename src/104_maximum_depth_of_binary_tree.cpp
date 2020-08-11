#include <iostream>
#include <queue>
#include "tree.hpp"

class Solution {
public:
    int maxDepth(TreeNode *root) {
        if (!root)
            return 0;
        else
            return std::max(maxDepth(root->left), maxDepth(root->right)) + 1;
    }
};

class Solution1 {
public:
    int maxDepth(TreeNode *root) {
        if (!root)
            return 0;

        std::queue<TreeNode *> q;
        q.push(root);

        int depth = 0;
        while (!q.empty()) {
            size_t n = q.size();
            for (int i = 0; i < n; ++i) {
                TreeNode *p = q.front();
                q.pop();

                if (p->left)
                    q.push(p->left);
                if (p->right)
                    q.push(p->right);
            }
            ++depth;
        }

        return depth;
    }
};

int main() {
    // 3
    TreeNode *root1 = CreateTree({3, 9, 20, 0, 0, 15, 7});

    Solution1 solution;
    std::cout << solution.maxDepth(root1) << std::endl;

    DestroyTree(root1);

    return 0;
}
