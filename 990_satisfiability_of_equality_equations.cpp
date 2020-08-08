#include <iostream>
#include <string>
#include <vector>

using std::cout;
using std::endl;
using std::string;
using std::vector;

/*
 * 并查集。使用按秩合并和路径压缩优化。
 */
class UnionFindSet {
public:
    UnionFindSet(int n) : parent(n, -1) {}

    int Find(int x) {
        if (parent[x] < 0)
            return x;
        else
            return parent[x] = Find(parent[x]);  // 压缩路径
    }

    void Union(int x, int y) {
        x = Find(x);
        y = Find(y);
        if (x == y)  // 位于同一棵树
            return;
        if (parent[x] < parent[y])  // 秩越大，parent[x]负得越多
            parent[y] = x;
        else if (parent[x] > parent[y])
            parent[x] = y;
        else {
            parent[x] = y;
            parent[y] -= 1;
        }
    }

private:
    // parent[x]>=0时是x的父节点，<0时表示x为根节点且它为x的秩。
    vector<int> parent;
};

/*
 * 先遍历一遍，处理所有等式，将等于关系表示成并查集，然后再遍历一次，处理所有不等式，看看是否有
 * 同一棵树中的变量需要不相等，如果有就不可能满足，没有就可以满足。
 */
class Solution {
public:
    bool equationsPossible(const vector<string> &equations) {
        UnionFindSet ufs(26);
        for (const string &equation : equations) {
            if (equation[1] == '=')
                ufs.Union(equation[0] - 'a', equation[3] - 'a');
        }
        for (const string &equation : equations) {
            if (equation[1] == '!') {
                int a = ufs.Find(equation[0] - 'a');
                int b = ufs.Find(equation[3] - 'a');
                if (a == b)
                    return false;
            }
        }

        return true;
    }
};

int main() {
    // false
    vector<string> equations1 = {"a==b", "b!=a"};

    // true
    vector<string> equations2 = {"b==a", "a==b"};

    // true
    vector<string> equations3 = {"a==b", "b==c", "a==c"};

    // false
    vector<string> equations4 = {"a==b", "b!=c", "c==a"};

    // true
    vector<string> equations5 = {"c==c", "b==d", "x!=z"};

    Solution solution;
    cout << std::boolalpha;
    cout << solution.equationsPossible(equations1) << endl;
    cout << solution.equationsPossible(equations2) << endl;
    cout << solution.equationsPossible(equations3) << endl;
    cout << solution.equationsPossible(equations4) << endl;
    cout << solution.equationsPossible(equations5) << endl;

    return 0;
}
