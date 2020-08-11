#include <queue>
#include <iostream>

using std::queue;

class MyStack {
public:
    // 时间复杂度O(N)
    void push(int x) {
        int n = q.size();
        q.push(x);
        for (int i = 0; i < n; ++i) {
            q.push(q.front());
            q.pop();
        }
    }

    // 时间复杂度O(1)
    int pop() {
        int t = q.front();
        q.pop();
        return t;
    }

    // 时间复杂度O(1)
    int top() {
        return q.front();
    }

    bool empty() {
        return q.empty();
    }

private:
    // 以栈的顺序保存
    queue<int> q;
};

int main() {
    std::cout << "测试代码复杂程度超过题解，请直接查看题解！" << std::endl;
    return 0;
}
