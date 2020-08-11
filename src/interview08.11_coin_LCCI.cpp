#include <iostream>

using std::cout;
using std::endl;

class Solution {
public:
    int waysToChange(int n) {
        int count = 0;
        for (int i = 0; i <= n / 25; ++i) {
            int a = (n - 25 * i) / 10;
            int b = n / 5 - 5 * i + 1;
            count += static_cast<int>(static_cast<long long>((a + 1)) * (b - a) % 1000000007);
            count %= 1000000007;
        }

        return count;
    }
};

int main() {
    // 2
    int n1 = 5;

    // 4
    int n2 = 10;

    Solution solution;
    cout << solution.waysToChange(n1) << endl;
    cout << solution.waysToChange(n2) << endl;

    return 0;
}
