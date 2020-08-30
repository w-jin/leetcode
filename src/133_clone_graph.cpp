#include <iostream>
#include <vector>
#include <queue>
#include <unordered_map>
#include "graph.hpp"

using std::vector;

class Solution {
public:
    Node *cloneGraph(Node *node) {
        if (!node)
            return nullptr;

        vector<Node *> nodes(101, nullptr);

        // 使用广度优先遍历将节点内存分配好，并将邻接表拷贝到新节点中
        std::queue<Node *> q;
        q.push(node);
        while (!q.empty()) {
            Node *t = q.front();
            q.pop();

            if (!nodes[t->val]) {
                nodes[t->val] = new Node{t->val};
                nodes[t->val]->neighbors = t->neighbors;
                for (Node *neighbor : t->neighbors)
                    q.push(neighbor);
            }
        }

        // 将新节点的邻接表中的指针改为指向新节点
        for (int i = 0; i < nodes.size(); ++i) {
            if (!nodes[i])
                continue;
            for (int j = 0; j < nodes[i]->neighbors.size(); ++j)
                nodes[i]->neighbors[j] = nodes[nodes[i]->neighbors[j]->val];
        }

        // 任意找一个非nullptr的节点返回，最简单地办法是直接返回node对应的新节点
        return nodes[node->val];
    }
};

/*
 * 使用哈希表保存旧节点到新节点的映射。适用范围更广泛，如果节点的编号不是val，val的取值范围
 * 比较大时，使用数组保存新节点的指针就行不通了。
 */
class Solution1 {
public:
    Node *cloneGraph(Node *node) {
        if (!node)
            return nullptr;

        std::unordered_map<Node *, Node *> old_to_new;
        old_to_new[node] = new Node{node->val};

        std::queue<Node *> q;
        q.push(node);
        while (!q.empty()) {
            Node *t = q.front();
            q.pop();

            for (Node *neighbor : t->neighbors) {
                if (old_to_new.find(neighbor) == old_to_new.end()) {
                    old_to_new[neighbor] = new Node{neighbor->val};
                    q.push(neighbor);
                }
                old_to_new[t]->neighbors.push_back(old_to_new[neighbor]);
            }
        }

        return old_to_new[node];
    }
};

std::ostream &operator<<(std::ostream &os, const vector<int> &vec) {
    for (int i = 0; i + 1 < vec.size(); ++i)
        os << vec[i] << ", ";
    if (!vec.empty())
        os << vec.back();
    return os;
}

std::ostream &operator<<(std::ostream &os, const vector<vector<int>> &vec) {
    for (int i = 0; i < vec.size(); ++i) {
        os << i + 1 << ": " << vec[i] << "\n";
    }
    return os;
}

int main() {
    vector<vector<int>> adj_list1 = {
            {2, 4}, {1, 3}, {2, 4}, {1, 3}
    };

    Graph G1{adj_list1};

    Solution1 solution;
    Node *result1 = solution.cloneGraph(G1.nodes[0]);

    G1.buildFromNode(result1);

    vector<vector<int>> res_adj_list1 = G1.toAdjList();

    std::cout << res_adj_list1 << std::endl;

    return 0;
}
