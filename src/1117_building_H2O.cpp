#include <iostream>
#include <string>
#include <functional>
#include <thread>
#include <mutex>
#include <condition_variable>

class H2O {
public:
    H2O() {

    }

    void hydrogen(std::function<void()> releaseHydrogen) {
        std::unique_lock<std::mutex> lk(m);
        cv.wait(lk, [this]() { return H_available > 0; });
        releaseHydrogen();
        --H_available;
        cv.notify_one();
    }

    void oxygen(std::function<void()> releaseOxygen) {
        std::unique_lock<std::mutex> lk(m);
        cv.wait(lk, [this]() { return H_available <= 2; });
        releaseOxygen();
        H_available += 2;
        cv.notify_one();
    }

private:
    int H_available = 2;
    std::mutex m;
    std::condition_variable cv;
};

int main() {
    std::string HOS;
    std::cin >> HOS;

    size_t Os = HOS.size() / 3;
    size_t Hs = Os * 2;

    auto releaseHydrogen = []() { std::cout << "H"; };
    auto releaseOxygen = []() { std::cout << "O"; };

    H2O h2o;
    std::thread hydrogen_thread{
        [&h2o, Hs, &releaseHydrogen]() {
            for (int i = 0; i < Hs; ++i)
                h2o.hydrogen(releaseHydrogen);
        }
    };

    std::thread oxygen_thread{
        [&h2o, Os, &releaseOxygen]() {
            for (int i = 0; i < Os; ++i)
                h2o.oxygen(releaseOxygen);
        }
    };

    hydrogen_thread.join();
    oxygen_thread.join();

    return 0;
}
