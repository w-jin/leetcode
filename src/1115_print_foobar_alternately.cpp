#include <iostream>
#include <functional>
#include <thread>
#include <mutex>
#include <condition_variable>

class FooBar {
public:
    FooBar(int n) {
        this->n = n;
    }

    void foo(std::function<void()> printFoo) {
        for (int i = 0; i < n; i++) {
            std::unique_lock<std::mutex> lk(m);
            if (foo_printed)
                cv.wait(lk);
            printFoo();
            foo_printed = true;
            cv.notify_one();
        }
    }

    void bar(std::function<void()> printBar) {
        for (int i = 0; i < n; i++) {
            std::unique_lock<std::mutex> lk(m);
            if (!foo_printed)
                cv.wait(lk);
            printBar();
            foo_printed = false;
            cv.notify_one();
        }
    }


private:
    int n;
    bool foo_printed = false;
    std::mutex m;
    std::condition_variable cv;
};

int main() {
    auto printFoo = []() { std::cout << "foo"; };
    auto printBar = []() { std::cout << "bar"; };

    int n = 0;
    std::cin >> n;
    FooBar foobar(n);

    std::thread thread1 {
        [&foobar, &printFoo]() { foobar.foo(printFoo); }
    };
    std::thread thread2 {
        [&foobar, &printBar]() { foobar.bar(printBar); }
    };

    thread1.join();
    thread2.join();

    std::cout << std::endl;

    return 0;
}
