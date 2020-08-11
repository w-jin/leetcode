#include <iostream>
#include <vector>
#include <algorithm>

using std::cout;
using std::endl;
using std::vector;

class Solution {
public:
    int translateNum(int num) {
        vector<int> dec_bit;
        while (num != 0) {
            dec_bit.push_back(num % 10);
            num /= 10;
        }
        std::reverse(dec_bit.begin(), dec_bit.end());

        int last = 1;
        int curr = 1;
        for (int i = 1; i < dec_bit.size(); ++i) {
            int t = 10 * dec_bit[i - 1] + dec_bit[i];
            int next = 0;
            if (10 <= t && t <= 25)
                next += last;
            next += curr;
            last = curr;
            curr = next;
        }

        return curr;
    }
};

int main() {
    // 5
    int num1 = 12258;

    Solution solution;
    cout << solution.translateNum(num1) << endl;

    return 0;
}
