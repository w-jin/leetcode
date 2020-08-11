#include <iostream>
#include <vector>
#include <unordered_map>
#include <algorithm>

using std::cout;
using std::endl;
using std::vector;
using std::unordered_map;

class Solution {
public:
    bool hasGroupsSizeX(vector<int> &deck) {
        int counts[10001] = {0};
        for (int n : deck)
            ++counts[n];

        int x = 0;
        for (int n : counts)
            x = gcd(x, n);
        return x >= 2;
    }

private:
    int gcd(int a, int b) {
        if (a < b)
            std::swap(a, b);

        while (b != 0) {
            int r = a % b;
            a = b;
            b = r;
        }
        return a;
    }
};

class Solution1 {
public:
    bool hasGroupsSizeX(vector<int> &deck) {
        unordered_map<int, int> counts;
        for (int n : deck)
            ++counts[n];

        int x = 0;
        for (auto p : counts)
            x = gcd(x, p.second);
        return x >= 2;
    }

private:
    int gcd(int a, int b) {
        if (a < b)
            std::swap(a, b);

        while (b != 0) {
            int r = a % b;
            a = b;
            b = r;
        }
        return a;
    }
};

int main() {
    // true
    vector<int> deck1 = {1, 2, 3, 4, 4, 3, 2, 1};

    // false
    vector<int> deck2 = {1, 1, 1, 2, 2, 2, 3, 3};

    // false
    vector<int> deck3 = {1};

    // true
    vector<int> deck4 = {1, 1};

    // true
    vector<int> deck5 = {1, 1, 2, 2, 2, 2};

    Solution1 solution;
    cout << std::boolalpha;
    cout << solution.hasGroupsSizeX(deck1) << endl;
    cout << solution.hasGroupsSizeX(deck2) << endl;
    cout << solution.hasGroupsSizeX(deck3) << endl;
    cout << solution.hasGroupsSizeX(deck4) << endl;
    cout << solution.hasGroupsSizeX(deck5) << endl;

    return 0;
}
