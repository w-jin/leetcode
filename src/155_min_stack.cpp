#include <stack>
#include <iostream>

using std::stack;

class MinStack {
public:
    void push(int x) {
        data.push(x);
        if (min_data.empty() || min_data.top() >= x)
            min_data.push(x);
    }

    void pop() {
        if (min_data.top() == data.top())
            min_data.pop();
        data.pop();
    }

    int top() {
        return data.top();
    }

    int getMin() {
        return min_data.top();
    }

private:
    stack<int> data;
    stack<int> min_data;
};

int main() {
    std::cout << "测试代码复杂程序超过题解，请直接查看题解！" << std::endl;

    return 0;
}
