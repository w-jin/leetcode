#include <string>
#include <stack>
#include "tree.hpp"

using std::string;

/*
 * 递归实现。
 * 时间复杂度O(|s|)，空间复杂度O(log |s|)。
 */
class Solution {
public:
    TreeNode *recoverFromPreorder(const string &S) {
        size_t i = 0;
        return recoverFromPreorder(S, i, 0);
    }

private:
    TreeNode *recoverFromPreorder(const string &S, size_t &i, int level) {
        size_t j = 0;
        int value = std::stoi(S.substr(i), &j);
        i += j;

        TreeNode *root = new TreeNode(value);

        if (i == S.size())
            return root;

        // -的个数
        int count = getCountOf_(S, i);

        if (count <= level)  // 去建立某个祖先节点的右子树
            return root;
        else {               // count > level
            i += count;      // i移到下一个数字

            // 左孩子
            root->left = recoverFromPreorder(S, i, count);

            // 右子树，S[i...]以"--..."开头
            count = getCountOf_(S, i);
            if (count <= level)  // 仍然是祖先节点的右子树
                return root;
            else {
                i += count;
                root->right = recoverFromPreorder(S, i, count);
            }
        }

        return root;
    }

private:
    int getCountOf_(const string &S, size_t i) {
        int count = 0;
        while (S[i] == '-') {
            ++count;
            ++i;
        }
        return count;
    }
};

/*
 * 循环实现。
 */
class Solution1 {
public:
    TreeNode *recoverFromPreorder(const string &S) {
        int value = 0;
        size_t i = 0;
        while (i < S.size() && isdigit(S[i])) {
            value = 10 * value + (S[i] - '0');
            ++i;
        }
        TreeNode *root = new TreeNode(value);

        std::stack<TreeNode *> path;
        path.push(root);
        while (i < S.size()) {
            int count = 0;
            while (S[i] == '-') {
                ++i;
                ++count;
            }

            value = 0;
            while (i < S.size() && isdigit(S[i])) {
                value = 10 * value + (S[i] - '0');
                ++i;
            }

            if (count >= path.size()) {
                path.top()->left = new TreeNode(value);
                path.push(path.top()->left);
            } else {
                while (count < path.size())
                    path.pop();
                path.top()->right = new TreeNode(value);
                path.push(path.top()->right);
            }
        }

        return root;
    }
};

int main() {
    // 1, 2, 5, 3, 4, 6, 7
    string S1 = "1-2--3--4-5--6--7";

    // 1, 2, 5, 3, null, 6, null, 4, null, 7
    string S2 = "1-2--3---4-5--6---7";

    // 1, 401, null, 349, 88, 90
    string S3 = "1-401--349---90--88";

    Solution1 solution;
    TreeNode *tree1 = solution.recoverFromPreorder(S1);
    TreeNode *tree2 = solution.recoverFromPreorder(S2);
    TreeNode *tree3 = solution.recoverFromPreorder(S3);

    // PrintTreeByLevel(tree1);
    // PrintTreeByLevel(tree2);
    // PrintTreeByLevel(tree3);

    // 以更直观的方式打印
    PrintBinaryTree(tree1);
    PrintBinaryTree(tree2);
    PrintBinaryTree(tree3);

    DestroyTree(tree1);
    DestroyTree(tree2);
    DestroyTree(tree3);

    return 0;
}
