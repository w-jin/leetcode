#include <iostream>
#include <vector>
#include <queue>

using std::cout;
using std::endl;
using std::vector;

class UnionFindSet {
public:
    explicit UnionFindSet(int n) : parent(n, -1) {}

    int Find(int x) {
        if (parent[x] < 0)
            return x;
        else
            return parent[x] = Find(parent[x]);
    }

    void Union(int x, int y) {
        x = Find(x);
        y = Find(y);
        if (x == y)
            return;
        if (parent[x] < parent[y]) {
            parent[y] = x;
        } else if (parent[x] > parent[y]) {
            parent[x] = y;
        } else {
            parent[x] = y;
            --parent[y];
        }
    }

private:
    std::vector<int> parent;
};

/*
 * 使用并查集表示节点集合。对每个节点，先检查其相邻节点有无冲突，若有冲突则返回false，
 * 没有冲突则将它们放入同一个集合。
 * 此算法利用无向图邻接矩阵的对称性，切不可只判断上三角或者下三角，如
 * 0    3
 * 1    2, 4   // 2、4划在一起
 * 2    1
 * 3    0, 4   // 0、2、4划在一起，同时1、3也必须划在一起，1、3的检查依赖于对称性
 * 4    1, 3   // 1、3之所以必须划在一起是因为它们都和4有边(4同时出现在1、3后面)，
 *                反过来，4也与它们有边，因此1、3的检查延迟到节点4处。
 * 时间复杂度O(|V| + |E|)，空间复杂度O(|V|)。
 */
class Solution {
public:
    bool isBipartite(const vector<vector<int>> &graph) {
        UnionFindSet ufs(graph.size());
        for (int i = 0; i < graph.size(); ++i) {
            int root = ufs.Find(i);
            for (int j : graph[i]) {
                if (ufs.Find(j) == root)
                    return false;
            }
            for (int j = 1; j < graph[i].size(); ++j)
                ufs.Union(graph[i][j - 1], graph[i][j]);
        }
        return true;
    }
};

/*
 * 染色算法。任意选择一个起点，将它染成红色，然后将它的相邻节点染成黑色，若染色过程
 * 中某个节点已经染色且不是当前该染的颜色则返回false，否则进行深度优先或者广度优先
 * 遍历将所有节点染色。需要注意：所给的图不一定是连通的，所以必须遍历所有节点，从任
 * 意一个未染色的节点出发进行染色。
 * 可以使用深度优先遍历或者广度优先遍历。时间杂度O(|V| + |E|)，空间复杂度O(|V|)。
 */
class Solution1 {
public:
    bool isBipartite(const vector<vector<int>> &graph) {
        vector<Color> color(graph.size(), UNCOLORED);
        for (int i = 0; i < graph.size(); ++i) {
            if (color[i] == UNCOLORED) {
                color[i] = WHITE;   // 任意染色
                if (!dye(graph, color, i))
                    return false;
            }
        }
        return true;
    }

private:
    enum Color {UNCOLORED, RED, WHITE};

    bool dye(const vector<vector<int>> &graph, vector<Color> &color, int i) {
        Color next_color = color[i] == RED ? WHITE : RED;
        for (int next : graph[i]) {
            if (color[next] == UNCOLORED) {
                color[next] = next_color;
                if (!dye(graph, color, next))
                    return false;
            } else if (color[next] != next_color) {
                return false;
            }
        }
        return true;
    }
};

class Solution2 {
public:
    bool isBipartite(const vector<vector<int>> &graph) {
        vector<Color> color(graph.size(), UNCOLORED);
        std::queue<int> q;
        for (int i = 0; i < graph.size(); ++i) {
            if (color[i] != UNCOLORED)
                continue;
            else if (!dye(graph, color, i))
                return false;
        }
        return true;
    }

private:
    enum Color {UNCOLORED, RED, WHITE};

    bool dye(const vector<vector<int>> &graph, vector<Color> &color, int i) {
        std::queue<int> q;
        q.push(i);
        color[i] = WHITE;  // 任意染色
        Color next_color = color[i] == RED ? WHITE : RED;
        while (!q.empty()) {
            int n = q.size();
            for (int k = 0; k < n; ++k) {
                int curr = q.front();
                q.pop();

                for (int next : graph[curr]) {
                    if (color[next] == UNCOLORED) {
                        color[next] = next_color;
                        q.push(next);
                    } else if (color[next] != next_color)
                        return false;
                }
            }

            next_color = next_color == RED ? WHITE : RED;
        }
        return true;
    }
};

int main() {
    // true，分成{0,2}和{1,3}两组节点
    // 0----1
    // |    |
    // |    |
    // 3----2
    vector<vector<int>> graph1 = {
            {1, 3},
            {0, 2},
            {1, 3},
            {0, 2}
    };

    // false
    // 0----1
    // | \  |
    // |  \ |
    // 3----2
    vector<vector<int>> graph2 = {
            {1, 2, 3},
            {0, 2},
            {0, 1, 3},
            {0, 2}
    };

    // true，分成{0,2,4}和{1,3}两组节点
    vector<vector<int>> graph3 = {
            {3},
            {2, 4},
            {1},
            {0, 4},
            {1, 3}
    };

    Solution1 solution;
    cout << std::boolalpha;
    cout << solution.isBipartite(graph1) << endl;
    cout << solution.isBipartite(graph2) << endl;
    cout << solution.isBipartite(graph3) << endl;

    return 0;
}
