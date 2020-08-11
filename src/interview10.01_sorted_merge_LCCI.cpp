#include <iostream>
#include <vector>

using std::vector;

class Solution {
public:
    void merge(vector<int> &A, int m, vector<int> &B, int n) {
        if (m == 0) {
            A = B;
            return;
        }
        if (n == 0) {
            return;
        }

        int i_merge = m + n - 1;
        int iA = m - 1;
        int iB = n - 1;
        while (iA >= 0 && iB >= 0) {
            if (A[iA] < B[iB])
                A[i_merge--] = B[iB--];
            else
                A[i_merge--] = A[iA--];
        }
        while (iB >= 0)
            A[i_merge--] = B[iB--];
    }
};

int main() {
    Solution solution;

    // 1, 2, 2, 3, 5, 6
    const int m = 3;
    const int n = 3;
    vector<int> A = {1, 2, 3, 0, 0, 0};
    vector<int> B = {2, 5, 6};
    solution.merge(A, m, B, n);

    for (int i = 0; i < m + n - 1; ++i)
        std::cout << A[i] << ", ";
    std::cout << A[m + n - 1] << std::endl;

    return 0;
}
