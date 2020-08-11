#include <iostream>
#include <string>
#include <vector>
#include <unordered_set>
#include <unordered_map>
#include <algorithm>
#include <functional>

using std::string;
using std::vector;

class Solution {
public:
    vector<vector<string>> findLadders(const string &beginWord, const string &endWord,
                                       const vector<string> &wordList) {
        auto it = std::find(wordList.begin(), wordList.end(), endWord);
        if (it == wordList.end())
            return {};

        const int end_word_loc = it - wordList.begin();

        // 单词表构成一个无向图，只相差一个字母的单词之间有边
        vector<vector<int>> graph(wordList.size());
        for (int i = 0; i < wordList.size(); ++i) {
            for (int j = i + 1; j < wordList.size(); ++j) {
                if (adjacent(wordList[i], wordList[j])) {
                    graph[i].push_back(j);
                    graph[j].push_back(i);
                }
            }
        }

        // 广度优先使用的队列，记录每层的节点
        vector<int> curr_level;
        vector<int> next_level;

        // 记录每个节点是否已经访问过
        vector<bool> visited(wordList.size(), false);

        // 每个节点的最短路径，即动态规划的表
        vector<vector<vector<int>>> paths(wordList.size());

        // 计算入口，即和beginWord只差一个字母的单词，如果endWord也在其中，那就只有这一条路径
        for (int i = 0; i < wordList.size(); ++i) {
            if (adjacent(beginWord, wordList[i])) {
                if (i == end_word_loc) {
                    return {{beginWord, endWord}};
                }
                curr_level.push_back(i);
                visited[i] = true;

                paths[i].push_back({i});
            }
        }

        // 是否已经到达目标节点
        bool reached = false;

        // 广度优先
        while (!reached && !curr_level.empty()) {
            // 处理一层
            vector<bool> visited_curr_level(wordList.size(), false);
            for (int curr_vertex : curr_level) {
                if (visited_curr_level[curr_vertex])
                    continue;
                visited_curr_level[curr_vertex] = true;  // 避免本层重复访问

                // 处理后继
                for (int next_vertex : graph[curr_vertex]) {
                    if (visited[next_vertex])
                        continue;

                    if (reached && next_vertex != end_word_loc)
                        continue;

                    if (next_vertex == end_word_loc)
                        reached = true;

                    next_level.push_back(next_vertex);
                    for (vector<int> path : paths[curr_vertex]) {
                        path.push_back(next_vertex);
                        paths[next_vertex].push_back(path);
                    }
                }
            }

            for (int next_vertex : next_level)
                visited[next_vertex] = true;

            curr_level = next_level;
            next_level.clear();
        }

        if (!reached)
            return {};

        vector<vector<string>> result(paths[end_word_loc].size(), {beginWord});
        for (int i = 0; i < paths[end_word_loc].size(); ++i) {
            for (int vertex : paths[end_word_loc][i])
                result[i].push_back(wordList[vertex]);
        }

        return result;
    }

private:
    /*
        假设：
        1、单词具有相同的长度。
        2、单词只由小写字母组成。
        3、不存在重复的单词。
    */
    bool adjacent(const string &word1, const string &word2) {
        int different_count = 0;
        for (int i = 0; i < word1.size(); ++i) {
            if (word1[i] != word2[i]) {
                ++different_count;
                if (different_count > 1)
                    return false;
            }
        }
        return different_count == 1;  // beginWord可能在字典中，但不应当作为入口
    }
};

/*
    不构造图，直接遍历单词表寻找相邻节点，负优化！
*/
class Solution1 {
public:
    vector<vector<string>> findLadders(const string &beginWord, const string &endWord,
                                       const vector<string> &wordList) {
        auto it = std::find(wordList.begin(), wordList.end(), endWord);
        if (it == wordList.end())
            return {};

        const int end_word_loc = it - wordList.begin();

        // 广度优先使用的队列，记录每层的节点
        vector<int> curr_level;
        vector<int> next_level;

        // 记录每个节点是否已经访问过
        vector<bool> visited(wordList.size(), false);

        // 每个节点的最短路径，即动态规划的表
        vector<vector<vector<int>>> paths(wordList.size());

        // 计算入口，即和beginWord只差一个字母的单词，如果endWord也在其中，那就只有这一条路径
        for (int i = 0; i < wordList.size(); ++i) {
            if (adjacent(beginWord, wordList[i])) {
                if (i == end_word_loc) {
                    return {{beginWord, endWord}};
                }
                curr_level.push_back(i);
                visited[i] = true;

                paths[i].push_back({i});
            }
        }

        // 是否已经到达目标节点
        bool reached = false;

        // 广度优先
        while (!reached && !curr_level.empty()) {
            // 处理一层
            vector<bool> visited_curr_level(wordList.size(), false);
            for (int curr_vertex : curr_level) {
                if (visited_curr_level[curr_vertex])
                    continue;
                visited_curr_level[curr_vertex] = true;  // 避免本层重复访问

                // 处理后继
                for (int next_vertex = 0; next_vertex < wordList.size(); ++next_vertex) {
                    if (visited[next_vertex])
                        continue;
                    if (!adjacent(wordList[curr_vertex], wordList[next_vertex]))
                        continue;

                    next_level.push_back(next_vertex);

                    if (reached && next_vertex != end_word_loc)
                        continue;

                    if (next_vertex == end_word_loc)
                        reached = true;

                    for (vector<int> path : paths[curr_vertex]) {
                        path.push_back(next_vertex);
                        paths[next_vertex].push_back(path);
                    }
                }
            }

            for (int next_vertex : next_level)
                visited[next_vertex] = true;

            curr_level = next_level;
            next_level.clear();
        }

        if (!reached)
            return {};

        vector<vector<string>> result(paths[end_word_loc].size(), {beginWord});
        for (int i = 0; i < paths[end_word_loc].size(); ++i) {
            for (int vertex : paths[end_word_loc][i])
                result[i].push_back(wordList[vertex]);
        }

        return result;
    }

private:
    /*
        假设：
        1、单词具有相同的长度。
        2、单词只由小写字母组成。
        3、不存在重复的单词。
    */
    bool adjacent(const string &word1, const string &word2) {
        int different_count = 0;
        for (int i = 0; i < word1.size(); ++i) {
            if (word1[i] != word2[i]) {
                ++different_count;
                if (different_count > 1)
                    return false;
            }
        }
        return different_count == 1;  // beginWord可能在字典中，但不应当作为入口
    }
};

/*
    双向搜索，从beginWord的邻居和endWord分别进行广度优先遍历，直到两者在某些节点相遇
*/
class Solution2 {
public:
    vector<vector<string>> findLadders(const string &beginWord, const string &endWord,
                                       const vector<string> &wordList) {
        auto it = std::find(wordList.begin(), wordList.end(), endWord);
        if (it == wordList.end())
            return {};

        const int end_word_loc = it - wordList.begin();

        // 单词表构成一个无向图，只相差一个字母的单词之间有边
        vector<vector<int>> graph(wordList.size());
        for (int i = 0; i < wordList.size(); ++i) {
            for (int j = i + 1; j < wordList.size(); ++j) {
                if (adjacent(wordList[i], wordList[j])) {
                    graph[i].push_back(j);
                    graph[j].push_back(i);
                }
            }
        }

        // 广度优先使用的队列，记录每层的节点
        vector<int> curr_level;
        vector<int> next_level;

        vector<int> reverse_curr_level;
        vector<int> reverse_next_level;

        // 记录每个节点是否已经访问过
        vector<bool> visited(wordList.size(), false);
        vector<bool> reverse_visited(wordList.size(), false);

        // 每个节点的最短路径，即动态规划的表
        vector<vector<vector<int>>> paths(wordList.size());
        vector<vector<vector<int>>> reverse_paths(wordList.size());

        // 计算入口，即和beginWord只差一个字母的单词，如果endWord也在其中，那就只有这一条路径
        for (int i = 0; i < wordList.size(); ++i) {
            if (adjacent(beginWord, wordList[i])) {
                if (i == end_word_loc) {
                    return {{beginWord, endWord}};
                }
                curr_level.push_back(i);
                visited[i] = true;

                paths[i].push_back({i});
            }
        }

        // 反向的起点
        reverse_curr_level.push_back(end_word_loc);
        reverse_visited[end_word_loc] = true;
        reverse_paths[end_word_loc].push_back({end_word_loc});

        // 是否已经到达目标节点
        bool reached = false;
        std::unordered_set<int> reached_node;

        // 广度优先，如果正向或者反向有一个没有下层节点了，则两部分不连通
        while (!curr_level.empty() && !reverse_curr_level.empty()) {
            // 处理正向的一层
            vector<bool> visited_curr_level(wordList.size(), false);
            for (int curr_vertex : curr_level) {
                if (visited_curr_level[curr_vertex])
                    continue;
                visited_curr_level[curr_vertex] = true;  // 避免本层重复访问

                // 处理后继
                for (int next_vertex : graph[curr_vertex]) {
                    if (visited[next_vertex])
                        continue;

                    if (reached && !reverse_visited[next_vertex])
                        continue;

                    if (reverse_visited[next_vertex]) {
                        reached = true;
                        reached_node.insert(next_vertex);
                    }

                    next_level.push_back(next_vertex);
                    for (vector<int> path : paths[curr_vertex]) {
                        path.push_back(next_vertex);
                        paths[next_vertex].push_back(path);
                    }
                }
            }

            if (reached)
                break;

            for (int next_vertex : next_level)
                visited[next_vertex] = true;

            std::swap(curr_level, next_level);
            next_level.clear();

            // 处理反向的一层
            vector<bool> reverse_visited_curr_level(wordList.size(), false);
            for (int curr_vertex : reverse_curr_level) {
                if (reverse_visited_curr_level[curr_vertex])
                    continue;
                reverse_visited_curr_level[curr_vertex] = true;  // 避免本层重复访问

                // 处理后继
                for (int next_vertex : graph[curr_vertex]) {
                    if (reverse_visited[next_vertex])
                        continue;

                    if (reached && !visited[next_vertex])
                        continue;

                    if (visited[next_vertex]) {
                        reached = true;
                        reached_node.insert(next_vertex);
                    }

                    reverse_next_level.push_back(next_vertex);
                    for (vector<int> path : reverse_paths[curr_vertex]) {
                        path.push_back(next_vertex);
                        reverse_paths[next_vertex].push_back(path);
                    }
                }
            }

            if (reached)
                break;

            for (int next_vertex : reverse_next_level)
                reverse_visited[next_vertex] = true;

            std::swap(reverse_curr_level, reverse_next_level);
            reverse_next_level.clear();

        }

        if (!reached)
            return {};

        vector<vector<string>> result;
        for (int i : reached_node) {
            for (const vector<int> &path : paths[i]) {
                for (const vector<int> &reverse_path : reverse_paths[i]) {
                    vector<string> temp;
                    temp.push_back(beginWord);
                    for (int j : path)
                        temp.push_back(wordList[j]);
                    for (auto j = reverse_path.rbegin() + 1; j != reverse_path.rend(); ++j) {
                        temp.push_back(wordList[*j]);
                    }
                    result.push_back(temp);
                }
            }
        }

        return result;
    }

private:
    /*
        假设：
        1、单词具有相同的长度。
        2、单词只由小写字母组成。
        3、不存在重复的单词。
    */
    bool adjacent(const string &word1, const string &word2) {
        int different_count = 0;
        for (int i = 0; i < word1.size(); ++i) {
            if (word1[i] != word2[i]) {
                ++different_count;
                if (different_count > 1)
                    return false;
            }
        }
        return different_count == 1;  // beginWord可能在字典中，但不应当作为入口
    }
};

/*
    双向搜索，选择节点数量较少的一个方向，效果并不明显。可见时间耗费不在搜索过程中。
*/
class Solution3 {
public:
    vector<vector<string>> findLadders(const string &beginWord, const string &endWord,
                                       const vector<string> &wordList) {
        auto it = std::find(wordList.begin(), wordList.end(), endWord);
        if (it == wordList.end())
            return {};

        const int end_word_loc = it - wordList.begin();

        // 单词表构成一个无向图，只相差一个字母的单词之间有边
        vector<vector<int>> graph(wordList.size());
        for (int i = 0; i < wordList.size(); ++i) {
            for (int j = i + 1; j < wordList.size(); ++j) {
                if (adjacent(wordList[i], wordList[j])) {
                    graph[i].push_back(j);
                    graph[j].push_back(i);
                }
            }
        }

        // 广度优先使用的队列，记录每层的节点
        vector<int> curr_level;
        vector<int> next_level;

        vector<int> reverse_curr_level;
        vector<int> reverse_next_level;

        // 记录每个节点是否已经访问过
        vector<bool> visited(wordList.size(), false);
        vector<bool> reverse_visited(wordList.size(), false);

        // 每个节点的最短路径，即动态规划的表
        vector<vector<vector<int>>> paths(wordList.size());
        vector<vector<vector<int>>> reverse_paths(wordList.size());

        // 计算入口，即和beginWord只差一个字母的单词，如果endWord也在其中，那就只有这一条路径
        for (int i = 0; i < wordList.size(); ++i) {
            if (adjacent(beginWord, wordList[i])) {
                if (i == end_word_loc) {
                    return {{beginWord, endWord}};
                }
                curr_level.push_back(i);
                visited[i] = true;

                paths[i].push_back({i});
            }
        }

        // 反向的起点
        reverse_curr_level.push_back(end_word_loc);
        reverse_visited[end_word_loc] = true;
        reverse_paths[end_word_loc].push_back({end_word_loc});

        // 是否已经到达目标节点
        bool reached = false;
        std::unordered_set<int> reached_node;

        // 广度优先，如果正向或者反向有一个没有下层节点了，则两部分不连通
        while (!curr_level.empty() && !reverse_curr_level.empty()) {
            vector<bool> visited_curr_level(wordList.size(), false);
            // 处理正向和反向中节点数量较少的一层
            if (curr_level.size() <= reverse_curr_level.size()) { // 正向
                for (int curr_vertex : curr_level) {
                    if (visited_curr_level[curr_vertex])
                        continue;
                    visited_curr_level[curr_vertex] = true;  // 避免本层重复访问

                    // 处理后继
                    for (int next_vertex : graph[curr_vertex]) {
                        if (visited[next_vertex])
                            continue;

                        if (reached && !reverse_visited[next_vertex])
                            continue;

                        if (reverse_visited[next_vertex]) {
                            reached = true;
                            reached_node.insert(next_vertex);
                        }

                        next_level.push_back(next_vertex);
                        for (vector<int> path : paths[curr_vertex]) {
                            path.push_back(next_vertex);
                            paths[next_vertex].push_back(path);
                        }
                    }
                }

                if (reached)
                    break;

                for (int next_vertex : next_level)
                    visited[next_vertex] = true;

                std::swap(curr_level, next_level);
                next_level.clear();
            } else { // 反向
                for (int curr_vertex : reverse_curr_level) {
                    if (visited_curr_level[curr_vertex])
                        continue;
                    visited_curr_level[curr_vertex] = true;  // 避免本层重复访问

                    // 处理后继
                    for (int next_vertex : graph[curr_vertex]) {
                        if (reverse_visited[next_vertex])
                            continue;

                        if (reached && !visited[next_vertex])
                            continue;

                        if (visited[next_vertex]) {
                            reached = true;
                            reached_node.insert(next_vertex);
                        }

                        reverse_next_level.push_back(next_vertex);
                        for (vector<int> path : reverse_paths[curr_vertex]) {
                            path.push_back(next_vertex);
                            reverse_paths[next_vertex].push_back(path);
                        }
                    }
                }

                if (reached)
                    break;

                for (int next_vertex : reverse_next_level)
                    reverse_visited[next_vertex] = true;

                std::swap(reverse_curr_level, reverse_next_level);
                reverse_next_level.clear();
            }
        }

        if (!reached)
            return {};

        vector<vector<string>> result;
        for (int i : reached_node) {
            for (const vector<int> &path : paths[i]) {
                for (const vector<int> &reverse_path : reverse_paths[i]) {
                    vector<string> temp;
                    temp.push_back(beginWord);
                    for (int j : path)
                        temp.push_back(wordList[j]);
                    for (auto j = reverse_path.rbegin() + 1; j != reverse_path.rend(); ++j) {
                        temp.push_back(wordList[*j]);
                    }
                    result.push_back(temp);
                }
            }
        }

        return result;
    }

private:
    /*
        假设：
        1、单词具有相同的长度。
        2、单词只由小写字母组成。
        3、不存在重复的单词。
    */
    bool adjacent(const string &word1, const string &word2) {
        int different_count = 0;
        for (int i = 0; i < word1.size(); ++i) {
            if (word1[i] != word2[i]) {
                ++different_count;
                if (different_count > 1)
                    return false;
            }
        }
        return different_count == 1;  // beginWord可能在字典中，但不应当作为入口
    }
};


using std::unordered_set;
using std::unordered_map;

/*
    优化：1、使用哈希表缓存所有单词，查找后继时依次更改每个字母，然后看看它是否在字典中；
         2、把后继关系存放在哈希表hash中，找到目标后，使用深度优先遍历hash生成所有路径；
         3、双向查找，查找s到e的所有最短路径，从节点数量较少的一个方向查找
*/
class Solution4 {
public:
    vector<vector<string>> findLadders(const string &begin_word, const string &end_word,
                                       const vector<string> &word_list) {
        unordered_set<string> dict(word_list.begin(), word_list.end());
        if (dict.find(end_word) == dict.end())
            return {};

        unordered_map<string, vector<string>> graph;
        unordered_set<string> begin_set{begin_word};
        unordered_set<string> end_set{end_word};
        bool reached = false;
        bool flip = false;

        while (!begin_set.empty()) {
            for (const auto &word : begin_set)  // 处理下一层时不考虑本层及之前的单词
                dict.erase(word);

            unordered_set<string> next;  // 下一层单词
            for (const auto &word : begin_set) {
                for (int i = 0; i < word.size(); ++i) { // 改变任意位置的一个字母
                    string str = word;
                    for (int j = 'a'; j <= 'z'; ++j) { // 如果仍然是它自身则不在dict中
                        str[i] = j;
                        if (dict.find(str) == dict.end())
                            continue;
                        if (end_set.find(str) != end_set.end())
                            reached = true;
                        else
                            next.insert(str);
                        if (!flip)  // 正向搜索
                            graph[word].push_back(str);
                        else        // 反向搜索
                            graph[str].push_back(word);
                    }
                }
            }
            if (reached)
                break;
            // 下一轮从单词个数少的方向搜索，注意这个if-else表示是否反转方向，不是绝对的正向和反向
            if (next.size() <= end_set.size()) { // 下一轮仍然从当前方向搜索
                begin_set = next;
            } else {   // 下一轮从反转的方向搜索
                begin_set = end_set;
                end_set = next;
                flip = !flip;
            }
        }

        // 使用深度优先遍历生成路径
        vector<vector<string>> result;
        vector<string> path;
        path.push_back(begin_word);

        std::function<void(const string &)> dfs;
        dfs = [&dfs, &graph, &result, &path, &end_word](const string &curr) mutable {
            if (curr == end_word) {
                result.push_back(path);
                return;
            }
            if (graph.find(curr) == graph.end())
                return;
            for (const auto &next : graph[curr]) {
                path.push_back(next);
                dfs(next);
                path.pop_back();
            }
        };

        dfs(begin_word);

        return result;
    }
};


void printResult(const vector<vector<string>> &result) {
    if (result.empty()) {
        std::cout << "[];\n";
        return;
    }

    std::cout << "[\n";
    for (const auto &v : result) {
        std::cout << "  [ ";
        for (int i = 0; i + 1 < v.size(); ++i)
            std::cout << v[i] << ", ";
        std::cout << v.back() << " ]\n";
    }
    std::cout << "];\n";
}

int main() {
    /*
    [
        ["hit", "hot", "dot", "dog", "cog"],
        ["hit", "hot", "lot", "log", "cog"]
    ]
    */
    string beginWord1 = "hit";
    string endWord1 = "cog";
    vector<string> wordList1 = {"hot", "dot", "dog", "lot", "log", "cog"};

    // []
    string beginWord2 = "hit";
    string endWord2 = "cog";
    vector<string> wordList2 = {"hot", "dot", "dog", "lot", "log"};

    /*
    [
        ["red", "ted", "tad", "tax"],
        ["red", "ted", "tex", "tax"],
        ["red", "rex", "tex", "tax"]
    ]
    */
    string beginWord3 = "red";
    string endWord3 = "tax";
    vector<string> wordList3 = {"ted", "tex", "red", "tax", "tad", "den", "rex", "pee"};

    // []
    string beginWord4 = "hot";
    string endWord4 = "dog";
    vector<string> wordList4 = {"hot", "dog"};

    Solution4 solution;
    vector<vector<string>> result;

    result = solution.findLadders(beginWord1, endWord1, wordList1);
    printResult(result);

    result = solution.findLadders(beginWord2, endWord2, wordList2);
    printResult(result);

    result = solution.findLadders(beginWord3, endWord3, wordList3);
    printResult(result);

    result = solution.findLadders(beginWord4, endWord4, wordList4);
    printResult(result);

    return 0;
}
