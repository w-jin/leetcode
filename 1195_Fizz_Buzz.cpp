#include <iostream>
#include <thread>
#include <functional>
#include <mutex>
#include <condition_variable>

class FizzBuzz {
public:
    FizzBuzz(int n) {
        this->n = n;
    }

    // printFizz() outputs "fizz".
    void fizz(std::function<void()> printFizz) {

    }

    // printBuzz() outputs "buzz".
    void buzz(std::function<void()> printBuzz) {

    }

    // printFizzBuzz() outputs "fizzbuzz".
    void fizzbuzz(std::function<void()> printFizzBuzz) {

    }

    // printNumber(x) outputs "x", where x is an integer.
    void number(std::function<void(int)> printNumber) {

    }

private:
    int n;
    
};

int main() {
    int n = 0;
    std::cin >> n;

    FizzBuzz fizzBuzz(n);

    auto printFizz = []() { std::cout << "fizz"; };
    auto printBuzz = []() { std::cout << "buzz"; };
    auto printFizzBuzz = []() { std::cout << "fizzbuzz"; };
    auto printNumber = [](int i) { std::cout << i; };

    std::thread fizz {
        [&fizzBuzz, &printFizz]() {
            fizzBuzz.fizz(printFizz);
        }
    };

    std::thread buzz {
        [&fizzBuzz, &printBuzz]() {
            fizzBuzz.buzz(printBuzz);
        }
    };

    std::thread fizzbuzz {
        [&fizzBuzz, &printFizzBuzz]() {
            fizzBuzz.fizzbuzz(printFizzBuzz);
        }
    };

    std::thread number {
        [&fizzBuzz, &printNumber]() {
            fizzBuzz.number(printNumber);
        }
    };

    fizz.join();
    buzz.join();
    fizzbuzz.join();
    number.join();

    return 0;
}
