#include <iostream>
#include <stack>
#include <unordered_set>
#include <algorithm>
#include <utility>
#include <functional>

using std::cout;
using std::endl;
using std::stack;
using std::unordered_set;
using std::pair;

/*
    深度优先搜索，也是模拟方法。
    时间复杂度O(xy)，空间复杂度O(xy)。
*/
class Solution {
public:
    bool canMeasureWater(int x, int y, int z) {
        // pair无hash
        auto hash_pair = [](pair<int, int> p) {
            return std::hash<int>{}(p.first) ^ std::hash<int>{}(p.second);
        };
        unordered_set<pair<int, int>, decltype(hash_pair)> remains{0, hash_pair};

        stack<pair<int, int>> s;
        s.emplace(0, 0);
        while (!s.empty()) {
            // 重复
            if (remains.find(s.top()) != remains.end()) {
                s.pop();
                continue;
            }

            remains.emplace(s.top());
            int remain_x = s.top().first;
            int remain_y = s.top().second;
            s.pop();

            if (remain_x == z || remain_y == z || remain_x + remain_y == z)
                return true;

            // 处理六个基本动作，不用这些if语句也没问题，它们用于提前规避没有效果的动作
            // 把x倒掉
            if (remain_x > 0)
                s.emplace(0, remain_y);

            // 把y倒掉
            if (remain_y > 0)
                s.emplace(remain_x, 0);

            // 把x灌满
            if (remain_x < x)
                s.emplace(x, remain_y);

            // 把y灌满
            if (remain_y < y)
                s.emplace(remain_x, y);

            // 把x倒入y中，直到x空或者y满
            if (remain_x > 0 && remain_y < y) {
                int t = std::min(remain_x, y - remain_y);
                s.emplace(remain_x - t, remain_y + t);
            }

            // 把y倒入x中，直到y空或者x满
            if (remain_y > 0 && remain_x < x) {
                int t = std::min(remain_y, x - remain_x);
                s.emplace(remain_x + t, remain_y - t);
            }
        }

        return false;
    }
};

/*
    数学解法。
    最终量出的水显然要装在水壶中，所以只需要考虑水壶中的水量。题目定义的三种操作中，观察水壶中水量的变化情况：
    1、装满任意一个水壶
    2、倒掉任意一个水壶
    3、从一个水壶向另外一个水壶倒水，直到装满或者倒空
    最简单的是第3种情况，水壶中的总水量显然不变。对于第1、2种情况，首先在任意时刻，两个水壶不可能
    同时有水而不满，从上面三种操作的结果来看这是显然的；其次，装满或者倒掉一个不满的水壶没有任何
    意义，因为如果另一个水壶是满的，装满这个水壶就相当于一开始直接装满两个水壶，倒掉这个水壶就相当
    于一开始直接装满另一个水壶，如果另一个水壶是空的，装满这个水壶相当于一开始直接装满这个水壶，
    倒掉这个水壶相当于回到初始状态，所以只有装满一个空水壶和倒掉一个满水壶才是有意义的，此时总水量
    的变化为增加x或y或者减小x或y。因此有意义的操作下水壶的总水量总是以x和y为单位进行增减的，所以
    任意一步之后水壶的水量为ax+by，其中a和b为整数。注意：如果a和b中有负数，比如a为负表示y壶装水，
    然后倒入x壶中，然后x壶倒空，此类过程。
    因此能否得到z升水，相当于方程ax+by=z有无整数解，由裴蜀定理：此方程有整数解当且仅当z是gcd(a, b)
    的整数倍。
    时间复杂度O(log(min{x, y}))，空间复杂度O(1)。
*/
class Solution1 {
public:
    bool canMeasureWater(int x, int y, int z) {
        if (x + y < z)
            return false;
        if (x == 0 || y == 0)
            return z == 0 || x + y == z;

        // 辗转相除法求x和y的最大公约数
        if (x < y)
            std::swap(x, y);
        while (y != 0) {
            int r = x % y;
            x = y;
            y = r;
        }

        return z % x == 0;
    }
};

int main() {
    // true
    int x1 = 3, y1 = 4, z1 = 5;

    // false
    int x2 = 2, y2 = 6, z2 = 5;

    Solution1 solution;
    cout << std::boolalpha;
    cout << solution.canMeasureWater(x1, y1, z1) << endl;
    cout << solution.canMeasureWater(x2, y2, z2) << endl;

    return 0;
}
