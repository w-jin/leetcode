#include <iostream>
#include <vector>

using std::cout;
using std::endl;
using std::vector;

class Solution {
public:
    bool canThreePartsEqualSum(vector<int> &A) {
        if (A.empty())
            return true;

        int sum = 0;
        for (int num : A)
            sum += num;

        if (sum % 3 != 0)
            return false;

        int part = sum / 3;
        sum = A[0];
        int i = 1;
        while (i < A.size() && sum != part) {
            sum += A[i];
            ++i;
        }
        if (i == A.size() || sum != part)
            return false;

        sum = A[i];
        ++i;
        while (i < A.size() && sum != part) {
            sum += A[i];
            ++i;
        }

        return i < A.size() && sum == part;
    }
};

int main() {
    // true
    vector<int> A1 = {0, 2, 1, -6, 6, -7, 9, 1, 2, 0, 1};

    // false
    vector<int> A2 = {0, 2, 1, -6, 6, 7, 9, -1, 2, 0, 1};

    // true
    vector<int> A3 = {3, 3, 6, 5, -2, 2, 5, 1, -9, 4};

    // true
    vector<int> A4 = {18, 12, -18, 18, -19, -1, 10, 10};

    // false
    vector<int> A5 = {1, -1, 1, -1};

    Solution solution;

    cout << std::boolalpha;
    cout << solution.canThreePartsEqualSum(A1) << endl;
    cout << solution.canThreePartsEqualSum(A2) << endl;
    cout << solution.canThreePartsEqualSum(A3) << endl;
    cout << solution.canThreePartsEqualSum(A4) << endl;
    cout << solution.canThreePartsEqualSum(A5) << endl;

    return 0;
}
