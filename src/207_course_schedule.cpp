#include <iostream>
#include <vector>
#include <queue>
#include <functional>

using std::cout;
using std::endl;
using std::vector;

/*
 * 拓扑排序。时间复杂度O(n+e)，空间复杂度O(n+e)，其中n和e分别为节点数和边数。
 */
class Solution {
public:
    bool canFinish(int num_courses, vector<vector<int>> &prerequisites) {
        // next_course[i]中保存课程i的后继课程
        vector<vector<int>> next_course(num_courses);

        // 每个节点的入度
        vector<int> in_degree(num_courses, 0);

        for (auto &v : prerequisites) {
            next_course[v[1]].push_back(v[0]);
            ++in_degree[v[0]];
        }

        // 使用拓扑排序来找图中是否有环
        std::queue<int> q;

        // 将入度为0的节点入队，它们不需要任何前驱课程
        for (int i = 0; i < num_courses; ++i) {
            if (0 == in_degree[i])
                q.push(i);
        }

        // 依次访问入度为0的节点，减小其后继节点的度，度为减为0的节点入队，下次访问
        while (!q.empty()) {
            int curr = q.front();
            q.pop();

            for (int n : next_course[curr]) {
                --in_degree[n];
                if (0 == in_degree[n])
                    q.push(n);
            }
        }

        for (int d : in_degree) {
            if (d > 0)
                return false;
        }
        return true;
    }
};

/*
 * 深度优先遍历。时间复杂度O(n+e)，空间复杂度O(n+e)，其中n和e分别为节点个数和边的个数。
 */
class Solution1 {
public:
    bool canFinish(int num_courses, vector<vector<int>> &prerequisites) {
        // prev_course[i]中保存课程i的前驱课程
        vector<vector<int>> prev_course(num_courses);
        for (auto &v : prerequisites)
            prev_course[v[0]].push_back(v[1]);

        vector<int> visited(num_courses, 0);  // 0表示未访问，1表示访问过，-1表示可完成

        std::function<bool(int)> can_finish;
        can_finish = [&can_finish, &prev_course, &visited, num_courses](int curr) -> bool {
            if (visited[curr] == -1)  // 这个节点可以完成
                return true;
            if (visited[curr] == 1)   // 这个节点之前访问过，出现环了
                return false;

            visited[curr] = 1;        // 标记为访问过的
            for (int prev : prev_course[curr]) {   // 依次计算其前驱是否能完成
                if (!can_finish(prev))
                    return false;
            }

            visited[curr] = -1;    // 其前驱都能完成，那么它也能完成
            return true;
        };

        for (int i = 0; i < num_courses; ++i) {
            if (!can_finish(i))    // 依次计算每个节点是否能完成
                return false;
        }
        return true;
    }
};

int main() {
    // true
    int numCourses1 = 2;
    vector<vector<int>> prerequisites1 = {
            {1, 0}
    };

    // false
    int numCourses2 = 2;
    vector<vector<int>> prerequisites2 = {
            {1, 0},
            {0, 1}
    };

    Solution1 solution;
    cout << std::boolalpha;
    cout << solution.canFinish(numCourses1, prerequisites1) << endl;
    cout << solution.canFinish(numCourses2, prerequisites2) << endl;

    return 0;
}
