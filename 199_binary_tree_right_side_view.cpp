#include <iostream>
#include <vector>
#include <queue>
#include "tree.hpp"

using std::cout;
using std::endl;
using std::vector;
using std::queue;

class Solution {
public:
    vector<int> rightSideView(TreeNode* root) {
        if (!root)
            return {};
        vector<int> result;

        queue<TreeNode *> q;
        q.push(root);
        while (!q.empty()) {
            TreeNode *t = nullptr;
            int size = q.size();
            for (int i = 0; i < size; ++i) {
                t = q.front();
                q.pop();
                if (t->left)
                    q.push(t->left);
                if (t->right)
                    q.push(t->right);
            }
            result.push_back(t->val);
        }

        return result;
    }
};

std::ostream &operator<<(std::ostream &out, const vector<int> &vec) {
    if (vec.empty())
        return out;
    for (int i = 0; i + 1 < vec.size(); ++i)
        out << vec[i] << ", ";
    return out << vec.back();
}

int main() {
    // 1, 3, 4
    TreeNode *root1 = CreateTree({1, 2, 3, 0, 5, 0, 4});

    Solution solution;
    cout << solution.rightSideView(root1) << endl;

    DestroyTree(root1);
    return 0;
}
