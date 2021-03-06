#include <iostream>
#include <stack>

class CQueue {
public:
    CQueue() {}

    void appendTail(int value) {
        while (!s2.empty()) {
            s1.push(s2.top());
            s2.pop();
        }
        s1.push(value);
    }

    int deleteHead() {
        if (s1.empty() && s2.empty())
            return -1;
        while (!s1.empty()) {
            s2.push(s1.top());
            s1.pop();
        }
        int temp = s2.top();
        s2.pop();
        return temp;
    }

private:
    std::stack<int> s1;  // 逆序
    std::stack<int> s2;  // 正序
};

/**
 * Your CQueue object will be instantiated and called as such:
 * CQueue* obj = new CQueue();
 * obj->appendTail(value);
 * int param_2 = obj->deleteHead();
 */

int main() {
    std::cout << "测试代码复杂程序超过题解，直接查看题解即可！" << std::endl;
    return 0;
}
