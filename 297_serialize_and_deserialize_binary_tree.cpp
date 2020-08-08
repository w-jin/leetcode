#include <iostream>
#include <string>
#include <queue>
#include "tree.hpp"

using std::cout;
using std::endl;
using std::string;

/*
 * 层序遍历
 */
class Codec {
public:
    string serialize(TreeNode* root) {
        string result;
        std::queue<TreeNode *> q;
        q.push(root);
        while (!q.empty()) {
            TreeNode *p = q.front();
            q.pop();

            if (!p)
                result += "null,";
            else
                result += std::to_string(p->val) + ",";

            if (p) {
                q.push(p->left);
                q.push(p->right);
            }
        }

        return result;
    }

    TreeNode* deserialize(const string &data) {
        if (data.empty())
            return nullptr;

        // 先生成根节点
        TreeNode *root = nullptr;

        int i = 0;
        string node = getNode(data, i);
        if (node == "null")
            return nullptr;
        else
            root = new TreeNode(std::stoi(node));

        std::queue<TreeNode *> q;
        q.push(root);
        while (i < data.size()) {
            // if (q.empty())  // 不检查错误
            //     std::cerr << "not a binary tree!" << std::endl;

            TreeNode *p = q.front();
            q.pop();

            // 左子树
            node = getNode(data, i);
            if (node != "null") {
                p->left = new TreeNode(std::stoi(node));
                q.push(p->left);
            }

            if (i >= data.size())
                break;

            // 右子树
            node = getNode(data, i);
            if (node != "null") {
                p->right = new TreeNode(std::stoi(node));
                q.push(p->right);
            }
        }

        return root;
    }

private:
    // 取出一个节点
    string getNode(const string &data, int &i) {
        int j = i;
        while (i < data.size() && data[i] != ',')
            ++i;
        string node = data.substr(j, i - j);
        ++i;
        return node;
    }
};

/*
 * 先序遍历
 */
class Codec1 {
public:
    string serialize(TreeNode *root) {
        string str;
        serialize(root, str);
        return str;
    }

    TreeNode *deserialize(const string &data) {
        int i = 0;
        return deserialize(data, i);
    }

private:
    void serialize(TreeNode *root, string &str) {
        if (!root) {
            str += "N,";
        } else {
            str += std::to_string(root->val) + ",";
            serialize(root->left, str);
            serialize(root->right, str);
        }
    }

    TreeNode *deserialize(const string &data, int &i) {
        string node = getNode(data, i);
        if ("N" == node)
            return nullptr;
        else {
            TreeNode *root = new TreeNode(std::stoi(node));

            // 左子树
            root->left = deserialize(data, i);

            // 右子树
            root->right = deserialize(data, i);

            return root;
        }
    }

    // 取出一个节点
    string getNode(const string &data, int &i) {
        int j = i;
        while (i < data.size() && data[i] != ',')
            ++i;
        string node = data.substr(j, i - j);
        ++i;
        return node;
    }
};

int main() {
    // 1, 2, 3, null, null, 4, 5
    TreeNode *root1 = CreateTree({1, 2, 3, 0, 0, 4, 5});

    Codec1 codec;
    string serial1 = codec.serialize(root1);
    TreeNode *result1 = codec.deserialize(serial1);

    cout << serial1 << endl;
    PrintTreeByLevel(result1);

    DestroyTree(root1);
    DestroyTree(result1);

    return 0;
}
