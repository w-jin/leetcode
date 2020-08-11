#include <iostream>
#include <vector>
#include <stack>
#include <utility>
#include <functional>
#include "tree.hpp"

using std::cout;
using std::endl;
using std::vector;
using std::stack;
using std::pair;

// 递归版本
class Solution {
public:
    vector<int> postorderTraversal(TreeNode *root) {
        if (!root)
            return {};

        vector<int> result;

        std::function<void(TreeNode *)> traversal;
        traversal = [&traversal, &result](TreeNode *root) mutable -> void {
            // if (!root)   // 不处理空树
            //     return;
            if (root->left)
                traversal(root->left);
            if (root->right)
                traversal(root->right);
            result.push_back(root->val);
        };

        traversal(root);
        return result;
    }
};

// 迭代版本
class Solution1 {
public:
    vector<int> postorderTraversal(TreeNode *root) {
        vector<int> result;

        stack<pair<TreeNode *, bool>> s;
        TreeNode *p = root;
        while (p || !s.empty()) {
            if (p) {
                s.emplace(p, false);
                p = p->left;
            } else {
                if (s.top().second) { // 节点第二次出栈访问它并弹掉
                    result.push_back(s.top().first->val);
                    s.pop();
                } else {  // 节点第一次出栈，走右边，下一次为第二次出栈
                    p = s.top().first->right;
                    s.top().second = true;
                }
            }
        }

        return result;
    }
};

std::ostream &operator<<(std::ostream &out, const vector<int> &vec) {
    if (vec.empty())
        return out;

    for (int i = 0; i + 1 < vec.size(); ++i)
        out << vec[i] << ", ";
    out << vec.back();

    return out;
}

int main() {
    // 3, 2, 1
    TreeNode *tree1 = CreateTree({1, 0, 2, 3});

    Solution1 solution;

    vector<int> result = solution.postorderTraversal(tree1);
    cout << result << endl;


    return 0;
}

