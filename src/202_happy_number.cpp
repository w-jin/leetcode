#include <iostream>
#include <unordered_set>

class Solution {
public:
    bool isHappy(int n) {
        std::unordered_set<int> nums;
        while (1 != n) {
            if (nums.find(n) != nums.end())
                return false;
            nums.insert(n);
            int t = 0;
            while (n > 0) {
                t += (n % 10) * (n % 10);
                n = n / 10;
            }
            n = t;
        }
        return true;
    }
};

class Solution1 {
public:
    bool isHappy(int n) {
        std::unordered_set<int> circles = {4, 16, 27, 58, 89, 145, 42, 20};
        while (1 != n) {
            if (circles.find(n) != circles.end())
                return false;
            int t = 0;
            while (n > 0) {
                t += (n % 10) * (n % 10);
                n = n / 10;
            }
            n = t;
        }
        return true;
    }
};

int main() {
    // true
    int n1 = 19;

    Solution1 solution;
    std::cout << std::boolalpha;
    std::cout << solution.isHappy(n1) << std::endl;

    return 0;
}
