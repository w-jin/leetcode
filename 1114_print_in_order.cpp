#include <iostream>
#include <functional>
#include <thread>
#include <mutex>
#include <condition_variable>

class Foo {
public:
    void first(std::function<void()> printFirst) {
        std::unique_lock<std::mutex> lk(order123);
        printFirst();
        ++finished;
        cv.notify_all();
    }

    void second(std::function<void()> printSecond) {
        std::unique_lock<std::mutex> lk(order123);
        cv.wait(lk, [this]() { return finished == 2; });
        printSecond();
        ++finished;
        cv.notify_all();
    }

    void third(std::function<void()> printThird) {
        std::unique_lock<std::mutex> lk(order123);
        cv.wait(lk, [this]() { return finished == 3; });
        printThird();
    }

private:
    std::mutex order123;
    std::condition_variable cv;
    int finished = 1;
};

class Foo1 {
public:
    void first(std::function<void()> printFirst) {
        std::unique_lock<std::mutex> lk(order123);
        printFirst();
        first_finished = true;
        cv.notify_all();
    }

    void second(std::function<void()> printSecond) {
        std::unique_lock<std::mutex> lk(order123);
        while (!first_finished)
            cv.wait(lk);
        printSecond();
        second_finished = true;
        cv.notify_all();
    }

    void third(std::function<void()> printThird) {
        std::unique_lock<std::mutex> lk(order123);
        while (!second_finished)
            cv.wait(lk);
        printThird();
    }

private:
    std::mutex order123;
    std::condition_variable cv;
    bool first_finished = false;
    bool second_finished = false;
};


int main() {
    auto printFirst = []() { std::cout << "First"; };
    auto printSecond = []() { std::cout << "Second"; };
    auto printThird = []() { std::cout << "Third"; };

    Foo1 foo;
    std::function<void()> functions[3] = {
            [&foo, &printFirst]() { foo.first(printFirst); },
            [&foo, &printSecond]() { foo.second(printSecond); },
            [&foo, &printThird]() { foo.third(printThird); }
    };

    int t[3] = {3, 2, 1};
//     std::cin >> t[0] >> t[1] >> t[2];

    std::thread threads[3];
    threads[0] = std::thread(functions[t[0] - 1]);
    threads[1] = std::thread(functions[t[1] - 1]);
    threads[2] = std::thread(functions[t[2] - 1]);

    threads[0].join();
    threads[1].join();
    threads[2].join();

    std::cout << std::endl;

    return 0;
}
