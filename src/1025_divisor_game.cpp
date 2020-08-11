#include <iostream>
#include <vector>

using std::cout;
using std::endl;
using std::vector;

class Solution {
public:
    bool divisorGame(int N) {
        vector<int> win(N + 1, false);  // 为true则先手赢，后手输
        for (int i = 2; i <= N; ++i) {
            for (int k = 1; k <= i / 2; ++k) {
                if (i % k == 0 && !win[i - k]) {  // Alice选择一次变后手
                    win[i] = true;
                    break;
                }
            }
        }
        return win[N];
    }
};

/*
 * 若N为偶数，则Alice可选择1；到Bob时N为奇数，N的因子只有奇数，所以Bob只能选择奇数；
 * 再到Alice时N又是偶数，所以Alice可以使自己一直拿到偶数，当N减小到2时，下一轮Bob拿
 * 到1，故Alice必胜。同理，如果N是奇数，Alice只能选择奇数，到Bob时N为偶数，故Alice
 * 必输。
 */
class Solution1 {
public:
    bool divisorGame(int N) {
        return N % 2 == 0;
    }
};

int main() {
    // true
    int N1 = 2;

    // false
    int N2 = 3;

    // true
    int N3 = 4;

    Solution1 solution;
    cout << std::boolalpha;
    cout << solution.divisorGame(N1) << endl;
    cout << solution.divisorGame(N2) << endl;
    cout << solution.divisorGame(N3) << endl;

    return 0;
}
