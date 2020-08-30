#ifndef GRAPH_HPP
#define GRAPH_HPP

#include <vector>
#include <unordered_map>
#include <queue>
#include <algorithm>

class Node {
public:
    int val;

    // 邻接表。显然list更好，问就是leetcode规定的
    std::vector<Node *> neighbors;

    Node() {
        val = 0;
    }

    Node(int _val) {
        val = _val;
    }

    Node(int _val, std::vector<Node *> _neighbors) {
        val = _val;
        neighbors = _neighbors;
    }
};

class Graph {
public:
    std::vector<Node *> nodes;

    std::unordered_map<Node *, int> nodes_map;

    // 从邻接表构建图
    Graph(const std::vector<std::vector<int>> &adj_list) :
            nodes(adj_list.size()) {
        if (adj_list.empty())
            return;

        for (int i = 0; i < nodes.size(); ++i) {
            nodes[i] = new Node{i};
            nodes_map[nodes[i]] = i;
        }

        for (int i = 0; i < nodes.size(); ++i) {
            nodes[i]->neighbors.resize(adj_list[i].size());
            for (int j = 0; j < adj_list[i].size(); ++j)
                nodes[i]->neighbors[j] = nodes[adj_list[i][j] - 1];
        }
    }

    ~Graph() {
        for (auto node : nodes)
            delete node;
    }

    // 将图转化成邻接表
    std::vector<std::vector<int>> toAdjList() const {
        std::vector<std::vector<int>> adj_list(nodes.size());
        for (int i = 0; i < nodes.size(); ++i) {
            adj_list[i].resize(nodes[i]->neighbors.size());
            for (int j = 0; j < nodes[i]->neighbors.size(); ++j) {
                auto node_to_ind = nodes_map.find(nodes[i]->neighbors[j]);
                if (node_to_ind != nodes_map.end())
                    adj_list[i][j] = node_to_ind->second + 1;
            }
        }
        return adj_list;
    }

    // 从图的一个节点构建连通图，以node的val为节点编号(问就是leetcode133题规定的)
    // 此后图的所有节点的资源所有权转交给此图，不应当在外部通过节点指针直接操作图，
    // 尤其是释放节点内存。
    void buildFromNode(Node *node) {
        std::unordered_map<Node *, int> temp_map;
        std::queue<Node *> q;
        q.push(node);
        while (!q.empty()) {
            Node *t = q.front();
            q.pop();
            auto node_to_ind = temp_map.find(t);
            if (node_to_ind != temp_map.end())
                continue;

            temp_map[t] = t->val;
            for (Node *neighbor : t->neighbors)
                q.push(neighbor);
        }

        // 将原来的图中的不再使用的节点删除
        for (auto &p : nodes_map) {
            if (temp_map.find(p.first) == temp_map.end())
                delete p.first;
        }
        nodes_map = temp_map;

        // 节点的编号可能是不连续的，因此nodes的大小不是nodes_map的大小，而是最大的编号+1
        int max_num = 0;
        for (auto p : nodes_map)
            max_num = std::max(max_num, p.second);

        nodes.resize(max_num + 1);
        std::fill(nodes.begin(), nodes.end(), nullptr);

        for (auto p : nodes_map)
            nodes[p.second] = p.first;
    }
};

#endif // GRAPH_HPP
