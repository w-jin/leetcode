#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <functional>

using std::vector;

/*
 * 使用广度优先进行拓扑排序。时间复杂度O(n+e)，空间复杂度O(n+e)，其中n和e分别为节点数和边数。
 */
class Solution {
public:
    vector<int> findOrder(int num_courses, vector<vector<int>> &prerequisites) {
        // 每节课的后继课程
        vector<vector<int>> next_course(num_courses);

        // 每节课的入度
        vector<int> in_degree(num_courses, 0);

        for (auto &prerequisite: prerequisites) {
            // [0]依赖于[1]，即[1]先上，然后才能上[0]
            next_course[prerequisite[1]].push_back(prerequisite[0]);
            ++in_degree[prerequisite[0]];
        }

        std::queue<int> q;

        // 入度为0的课无前驱课程，可以直接上
        for (int i = 0; i < num_courses; ++i) {
            if (in_degree[i] == 0)
                q.push(i);
        }

        // 课程序列，q中的课都是已经没有前驱的课，依次学习(放入result中)，然后看后继是否可以上
        vector<int> result;
        while (!q.empty()) {
            int t = q.front();
            q.pop();

            result.push_back(t);

            for (int next : next_course[t]) {
                --in_degree[next];
                if (in_degree[next] == 0)
                    q.push(next);
            }
        }

        // 课程没有上完则无法完成
        return result.size() < num_courses ? vector<int>{} : result;
    }
};

/*
 * 使用深度优先进行拓扑排序。时间复杂度O(n+e)，空间复杂度O(n+e)，其中n和e分别为节点数和边数。
 */
class Solution1 {
public:
    vector<int> findOrder(int num_courses, vector<vector<int>> &prerequisites) {
        // prev_course[i]中保存课程i的前驱课程
        vector<vector<int>> prev_course(num_courses);
        for (auto &v : prerequisites)
            prev_course[v[0]].push_back(v[1]);

        vector<int> visited(num_courses, 0);  // 0表示未访问，1表示访问过，-1表示可完成
        vector<int> result;   // 课程的顺序

        std::function<bool(int)> can_finish;
        can_finish = [&can_finish, &prev_course, &visited,
                      &result, num_courses](int curr) -> bool {
            if (visited[curr] == -1)  // 这个节点可以完成
                return true;
            if (visited[curr] == 1)   // 这个节点之前访问过，出现环了
                return false;

            visited[curr] = 1;        // 标记为访问过的
            for (int prev : prev_course[curr]) {   // 依次计算其前驱是否能完成
                if (!can_finish(prev))
                    return false;
            }

            visited[curr] = -1;      // 其前驱都能完成，那么它也能完成
            result.push_back(curr);  // 其前驱都已经放入result

            return true;
        };

        for (int i = 0; i < num_courses; ++i) {
            if (!can_finish(i))    // 依次计算每个节点是否能完成
                return {};
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

int main() {
    // 0, 1
    int num_courses1 = 2;
    vector<vector<int>> prerequisites1 = {{1, 0}};

    // 0, 1, 2, 3 or 0, 2, 1, 3
    int num_courses2 = 4;
    vector<vector<int>> prerequisites2 = {{1, 0}, {2, 0}, {3, 1}, {3, 2}};

    Solution1 solution;
    std::cout << solution.findOrder(num_courses1, prerequisites1) << std::endl;
    std::cout << solution.findOrder(num_courses2, prerequisites2) << std::endl;

    return 0;
}
