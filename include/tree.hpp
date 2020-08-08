/*
 * 此头文件实现一个简单的二叉树及相关操作
 */
#ifndef TREE_H
#define TREE_H

#include <iostream>
#include <initializer_list>
#include <string>
#include <queue>

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;

    explicit TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};

// 默认以0为null，即此分支为空
inline TreeNode *CreateTree(std::initializer_list<int> l, int null = 0) {
    auto *root = new TreeNode(*l.begin());

    std::queue<TreeNode *> level;
    level.push(root);
    const auto *it = l.begin() + 1;
    while (it != l.end()) {
        if (level.empty())
            throw std::runtime_error("The input is not a binary tree!");
        TreeNode *node = level.front();
        level.pop();
        if (*it != null) {
            node->left = new TreeNode(*it);
            level.push(node->left);
        }
        ++it;
        if (it == l.end())
            break;

        if (*it != null) {
            node->right = new TreeNode(*it);
            level.push(node->right);
        }
        ++it;
    }

    return root;
}

// 按层序打印二叉树，无节点的位置打印null，和leetcode比起来，末尾可能有多余的null
inline void PrintTreeByLevel(TreeNode *root) {
    std::queue<TreeNode *> level;
    level.push(root);
    while (!level.empty()) {
        TreeNode *node = level.front();
        level.pop();

        if (node) {
            std::cout << node->val;
            level.push(node->left);
            level.push(node->right);
        } else {
            std::cout << "null";
        }

        if (!level.empty())
            std::cout << ", ";
    }
    std::cout << std::endl;
}

// 按树形打印二叉树，效果类似于linux中的tree命令。
// 如果终端不能很好的支持utf-8编码的排版，可以指定ligature为false，函数将使用ASCII码代替。
inline void PrintBinaryTree(TreeNode *root, const std::string &path = "", bool ligature = true) {
    const std::string before_left_value = ligature ? "├─── " : "|--- ";
    const std::string before_left = ligature ? "│    " : "|    ";
    const std::string before_right_value = ligature ? "└─── " : "`--- ";
    const std::string before_right = "     ";

    if (!root)
        return;

    std::cout << root->val << "\n";
    if (root->left && root->right) {
        std::cout << path << before_left_value;
        PrintBinaryTree(root->left, path + before_left, ligature);
        std::cout << path << before_right_value;
        PrintBinaryTree(root->right, path + before_right, ligature);
    } else if (root->left && !root->right) {
        std::cout << path << before_left_value;
        PrintBinaryTree(root->left, path + before_left, ligature);
        std::cout << path << before_right_value << "missing\n";
    } else if (!root->left && root->right) {
        std::cout << path << before_left_value << "missing\n";
        std::cout << path << before_right_value;
        PrintBinaryTree(root->right, path + before_right, ligature);
    } else {
        // 无孩子，什么都不做
    }
}

// 按树形打印二叉树，效果类似于linux中的tree命令。
// 如果终端不能很好的支持utf-8编码的排版，可以指定ligature为false，函数将使用ASCII码代替。
inline void PrintBinaryTree(std::ostream &out, TreeNode *root,
                     const std::string &path = "", bool ligature = true) {
    const std::string before_left_value = ligature ? "├─── " : "|--- ";
    const std::string before_left = ligature ? "│    " : "|    ";
    const std::string before_right_value = ligature ? "└─── " : "`--- ";
    const std::string before_right = "     ";

    if (!root)
        return;

    out << root->val << "\n";
    if (root->left && root->right) {
        out << path << before_left_value;
        PrintBinaryTree(root->left, path + before_left, ligature);
        out << path << before_right_value;
        PrintBinaryTree(root->right, path + before_right, ligature);
    } else if (root->left && !root->right) {
        out << path << before_left_value;
        PrintBinaryTree(root->left, path + before_left, ligature);
        out << path << before_right_value << "missing\n";
    } else if (!root->left && root->right) {
        out << path << before_left_value << "missing\n";
        out << path << before_right_value;
        PrintBinaryTree(root->right, path + before_right, ligature);
    } else {
        // 无孩子，什么都不做
    }
}

// 释放一棵二叉树的内存
inline void DestroyTree(TreeNode *root) {
    if (!root)
        return;
    if (root->left)
        DestroyTree(root->left);
    if (root->right)
        DestroyTree(root->right);
    delete root;
}

#endif // TREE_H
