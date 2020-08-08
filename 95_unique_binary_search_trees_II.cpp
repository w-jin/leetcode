#include <iostream>
#include <vector>
#include "tree.hpp"

using std::cout;
using std::endl;
using std::vector;

/*
 * 因为所部分节点的内存重复使用了，所以释放内存非常困难。需要注意：在拼接左右两部分时
 * 不能复用根节点的内存，否则之前的树就被破坏了。
 */
class Solution {
public:
    vector<TreeNode *> generateTrees(int n) {
        return generateTrees(1, n);
    }

private:
    vector<TreeNode *> generateTrees(int first, int last) {
        if (first > last)
            return {};
        else if (first == last)
            return {new TreeNode{first}};

        vector<TreeNode *> result;
        vector<TreeNode *> left;
        vector<TreeNode *> right;

        // 将first作为根节点
        right = generateTrees(first + 1, last);
        for (int k = 0; k < right.size(); ++k) {
            TreeNode *root = new TreeNode{first};
            root->right = right[k];
            result.push_back(root);
        }

        // 将(first, last)作为根节点
        for (int i = first; i <= last; ++i) {
            left = generateTrees(first, i - 1);
            right = generateTrees(i + 1, last);

            for (int j = 0; j < left.size(); ++j) {
                for (int k = 0; k < right.size(); ++k) {
                    TreeNode *root = new TreeNode{i};
                    root->left = left[j];
                    root->right = right[k];
                    result.push_back(root);
                }
            }
        }

        // 将last作为根节点
        left = generateTrees(first, last - 1);
        for (int j = 0; j < left.size(); ++j) {
            TreeNode *root = new TreeNode{last};
            root->left = left[j];
            result.push_back(root);
        }

        return result;
    }
};

std::ostream &operator<<(std::ostream &out, const vector<TreeNode *> &vec) {
    for (int i = 0; i < vec.size(); ++i)
        PrintBinaryTree(out, vec[i]);
    return out;
}

/*
 * 有内存泄露！因为有部分节点重复使用了。
 */
void Destroy(const vector<TreeNode *> &vec) {
    for (int i = 0; i < vec.size(); ++i)
        DestroyTree(vec[i]);
}

int main() {
    // [1, null, 3, 2],
    // [3, 2, null, 1],
    // [3, 1, null, null, 2],
    // [2, 1, 3],
    // [1, null, 2, null, 3]
    int n1 = 3;

    Solution solution;
    auto result1 = solution.generateTrees(n1);

    cout << result1 << endl;

    Destroy(result1);

    return 0;
}
