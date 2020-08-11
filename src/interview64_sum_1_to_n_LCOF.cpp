#include <iostream>

using std::cout;
using std::endl;

class Solution {
public:
    int sumNums(int n) {
        int r = 0;
        n == 0 || (r = n + sumNums(n - 1));
        return r;
    }
};

int main() {
    // 6
    int n1 = 3;

    // 45
    int n2 = 9;

    Solution solution;
    cout << solution.sumNums(n1) << endl;
    cout << solution.sumNums(n2) << endl;

    return 0;
}

