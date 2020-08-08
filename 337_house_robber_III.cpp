#include <iostream>
#include <unordered_map>
#include <functional>
#include <gtest/gtest.h>
#include "tree.hpp"

using std::cout;
using std::endl;

/*
 * 时间复杂度O(n)，空间复杂度O(n)。
 */
class Solution {
public:
    int rob(TreeNode *root) {
        std::unordered_map<TreeNode *, int> cache;

        std::function<int(TreeNode *)> robRecursive;
        robRecursive = [&robRecursive, &cache](TreeNode *root) -> int {
            if (!root)
                return 0;

            auto it = cache.find(root);
            if (it != cache.end())
                return it->second;

            int skip_root = robRecursive(root->left) + robRecursive(root->right);
            int rob_root = root->val;
            if (root->left)
                rob_root += robRecursive(root->left->left) + robRecursive(root->left->right);
            if (root->right)
                rob_root += robRecursive(root->right->left) + robRecursive(root->right->right);

            int result = std::max(skip_root, rob_root);
            cache[root] = result;

            return result;
        };

        return robRecursive(root);
    }
};

/*
 * 优化空间，省掉哈希表。时间复杂度O(n)，空间复杂度O(log n)。
 */
#include <utility>

using std::pair;

class Solution1 {
public:
    int rob(TreeNode *root) {
        // 返回值为pair，其中first表示跳过root的收益，second表示掠夺root的收益。
        std::function<pair<int, int>(TreeNode *)> robRecursive;
        robRecursive = [&robRecursive](TreeNode *root) -> pair<int, int> {
            if (!root)
                return {0, 0};

            pair<int, int> left_profit = robRecursive(root->left);
            pair<int, int> right_profit = robRecursive(root->right);

            // 跳过root，其孩子可以选，也可以不选，取较大者
            int skip_root = std::max(left_profit.first, left_profit.second)
                            + std::max(right_profit.first, right_profit.second);

            // 掠夺root，则孩子不能选
            int rob_root = root->val + left_profit.first + right_profit.first;

            return {skip_root, rob_root};
        };

        pair<int, int> p = robRecursive(root);
        return std::max(p.first, p.second);
    }
};

int main(int argc, char *argv[]) {
    // 7
    TreeNode *root1 = CreateTree({3, 2, 3, 0, 3, 0, 1});

    // 9
    TreeNode *root2 = CreateTree({3, 4, 5, 1, 3, 0, 1});

    // 7
    TreeNode *root3 = CreateTree({4, 1, 0, 2, 0, 3});

    // 7
    TreeNode *root4 = CreateTree({2, 1, 3, 0, 4});

    Solution1 solution;
    cout << solution.rob(root1) << endl;
    cout << solution.rob(root2) << endl;
    cout << solution.rob(root3) << endl;
    cout << solution.rob(root4) << endl;

    DestroyTree(root1);
    DestroyTree(root2);
    DestroyTree(root3);
    DestroyTree(root4);

    return 0;
}
