#include <iostream>

class MaxQueue {
public:
    int max_value() {
        if (begin == end)
            return -1;
        int max = data[begin];
        for (int i = begin + 1; i < end; ++i)
            max = std::max(data[i], max);
        return max;
    }

    void push_back(int value) {
        data[end++] = value;
    }

    int pop_front() {
        if (begin == end)
            return -1;
        return data[begin++];
    }

private:
    int begin = 0;
    int end = 0;
    int data[10000] = {0};
};

class MaxQueue1 {
public:
    int max_value() {
        if (begin == end)
            return -1;
        return max_elements[max_begin];
    }

    void push_back(int value) {
        while (max_end > max_begin && max_elements[max_end - 1] < value)
            --max_end;
        max_elements[max_end++] = value;
        data[end++] = value;
    }

    int pop_front() {
        if (begin == end)
            return -1;
        if (data[begin] == max_elements[max_begin])
            ++max_begin;
        return data[begin++];
    }

private:
    int begin = 0;
    int end = 0;
    int data[10000] = {0};

    int max_begin = 0;
    int max_end = 0;
    int max_elements[10000] = {0};
};

int main() {
    // 测试太过麻烦，远远超过问题的实现难度

    return 0;
}
