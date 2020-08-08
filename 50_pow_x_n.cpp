#include <iostream>
#include <functional>

class Solution {
public:
    double myPow(double x, int n) {
        if (n == 0)
            return 1;

        double half = myPow(x, n / 2);
        if (n % 2 != 0) {
            if (n > 0)
                return half * half * x;
            else
                return half * half / x;
        }
        else {
            return half * half;
        }
    }
};

/* TODO:有一个bug，当n是INT_MIN时，-n溢出 */
class Solution1 {
public:
    double myPow(double x, int n) {
        std::function<double(double, int)> PowPositive = [&PowPositive](double _x, int _n) -> double {
            if (_n == 0)
                return 1;

            double half = PowPositive(_x, _n / 2);
            if (_n % 2 == 0)
                return half * half;
            else
                return half * half * _x;
        };

        if (n < 0)
            return PowPositive(1 / x, -n);
        else
            return PowPositive(x, n);
    }
};

/* 循环实现，将x^n分解为x^(2^a+2^b+...+2^m) */
class Solution2 {
public:
    double myPow(double x, int n) {
        if (n < 0)
            x = 1 / x;

        double result = 1;
        while (n != 0) {
            if (n % 2 != 0)
                result *= x;
            n = n / 2;
            x = x * x;
        }

        return result;
    }
};

int main() {
    //1024.0000
    double x1 = 2.00000;
    int n1 = 10;

    //9.26100
    double x2 = 2.10000;
    int n2 = 3;

    //0.25000
    double x3 = 2.00000;
    int n3 = -2;

    Solution2 solution;
    std::cout << solution.myPow(x1, n1) << std::endl;
    std::cout << solution.myPow(x2, n2) << std::endl;
    std::cout << solution.myPow(x3, n3) << std::endl;

    return 0;
}
