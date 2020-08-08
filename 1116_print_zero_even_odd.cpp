#include <iostream>
#include <functional>
#include <thread>
#include <mutex>
#include <condition_variable>

class ZeroEvenOdd {
public:
    ZeroEvenOdd(int n) {
        this->n = n;
    }

    // printNumber(x) outputs "x", where x is an integer.
    void zero(std::function<void(int)> printNumber) {
        for (int i = 0; i < n; ++i) {
            std::unique_lock<std::mutex> lk(g_m);
            cv.wait(lk, [this]() { return m % 2 == 0; });
            printNumber(0);
            ++m;
            cv.notify_all();
        }
    }

    void even(std::function<void(int)> printNumber) {
        for (int i = 2; i <= n; i += 2) {
            std::unique_lock<std::mutex> lk(g_m);
            cv.wait(lk, [this]() { return m % 4 == 3; });
            printNumber(i);
            ++m;
            cv.notify_all();
        }
    }

    void odd(std::function<void(int)> printNumber) {
        for (int i = 1; i <= n; i += 2) {
            std::unique_lock<std::mutex> lk(g_m);
            cv.wait(lk, [this]() { return m % 4 == 1; });
            printNumber(i);
            ++m;
            cv.notify_all();
        }
    }

private:
    int n;
    int m = 0;
    std::mutex g_m;
    std::condition_variable cv;
};

int main() {
    auto printNumber = [](int i) { std::cout << i; };

    int n = 0;
    std::cin >> n;

    ZeroEvenOdd ZEO(n);

    std::thread thread1 {
        [&ZEO, &printNumber]() { ZEO.zero(printNumber); }
    };
    std::thread thread2 {
        [&ZEO, &printNumber]() { ZEO.even(printNumber); }
    };
    std::thread thread3 {
        [&ZEO, &printNumber]() { ZEO.odd(printNumber); }
    };

    thread1.join();
    thread2.join();
    thread3.join();

    std::cout << std::endl;

    return 0;
}
