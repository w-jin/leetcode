#include <iostream>
#include <string>
#include <vector>
#include <queue>
#include <unordered_map>
#include <algorithm>
#include <functional>

using std::cout;
using std::endl;
using std::string;
using std::vector;

class Solution {
public:
    vector<string> findItinerary(const vector<vector<string>> &tickets) {
        // 用哈希表保存每个节点的后继节点，并使小顶堆将后继节点的最小值选出，即邻接表
        std::unordered_map<string,
                           std::priority_queue<string, vector<string>, std::greater<string>>> edges;
        for (const auto &ticket : tickets) {
            edges[ticket[0]].push(ticket[1]);
        }

        // 栈，将没有后继节点的节点入栈
        vector<string> stk;

        // 深度优先遍历。选择最小的后继节点向下遍历，同时删除这条边，如果某个节点没有后继则说明到达终点，
        // 将终点加入stk末尾，向上回溯后，如果节点没有后继则它是下一个终点，这样可以得到逆序的遍历顺序。
        std::function<void(const string &)> dfs;
        dfs = [&dfs, &stk, &edges](const string &curr) -> void {
            auto it = edges.find(curr);
            if (it != edges.end()) {
                while (!it->second.empty()) {
                    string next = it->second.top();
                    it->second.pop();
                    dfs(next);
                }
            }
            stk.push_back(curr);
        };

        dfs("JFK");
        std::reverse(stk.begin(), stk.end());
        return stk;
    }
};

std::ostream &operator<<(std::ostream &os, const vector<string> &vec) {
    if (vec.empty())
        return os;
    for (int i= 0; i + 1 < vec.size(); ++i)
        os << "\"" << vec[i] << "\", ";
    return os << "\"" << vec.back() << "\"";
}

int main() {
    // "JFK", "MUC", "LHR", "SFO", "SJC"
    vector<vector<string>> tickets1 = {
            {"MUC", "LHR"},
            {"JFK", "MUC"},
            {"SFO", "SJC"},
            {"LHR", "SFO"}
    };

    // "JFK", "ATL", "JFK", "SFO", "ATL", "SFO"
    vector<vector<string>> tickets2 = {
            {"JFK","SFO"},
            {"JFK","ATL"},
            {"SFO","ATL"},
            {"ATL","JFK"},
            {"ATL","SFO"}
    };

    Solution solution;
    cout << solution.findItinerary(tickets1) << endl;
    cout << solution.findItinerary(tickets2) << endl;

    return 0;
}
