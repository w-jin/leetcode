#include <iostream>
#include <vector>
#include <queue>
#include "tree.hpp"

using std::vector;

class Solution {
public:
    vector<vector<int>> levelOrder(TreeNode *root) {
        vector<vector<int>> result;

        std::queue<TreeNode *> q;
        if (root)
            q.push(root);
        while (!q.empty()) {
            int size = q.size();
            vector<int> temp(size);
            for (int i = 0; i < size; ++i) {
                TreeNode *p = q.front();
                q.pop();

                temp[i] = p->val;

                if (p->left)
                    q.push(p->left);
                if (p->right)
                    q.push(p->right);
            }
            result.push_back(temp);
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

std::ostream &operator<<(std::ostream &out, const vector<vector<int>> &vec) {
    if (vec.empty())
        return out << "[]";
    out << "[\n";
    for (const auto &v : vec) {
        out << v << "\n";
    }
    return out << "]";
}

int main() {
    /*
        3
        9, 20
        15, 7
    */
    TreeNode *root1 = CreateTree({3, 9, 20, 0, 0, 15, 7});

    Solution solution;
    std::cout << solution.levelOrder(root1) << std::endl;

    DestroyTree(root1);
    return 0;
}
