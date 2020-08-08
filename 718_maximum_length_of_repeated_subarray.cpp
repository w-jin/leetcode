#include <iostream>
#include <vector>

using std::cout;
using std::endl;
using std::vector;

/*
 * 动态规划。以length[i][j]表示以A[i-1]和B[j-1]结尾的最长公共子串长度，则
 * length[0][..]=0，length[..][0]=0。且有
 *   1、若A[i-1]!=B[j-1]，则length[i][j]=0；
 *   2、若A[i-1]==B[j-1]，则length[i][j]=length[i-1][j-1]+1
 * A和B的最长公共子数组为max{length[i][j]} for any i, j。
 * 时间复杂度O(mn)，空间复杂度O(mn)，其中m和n分别为A和B的长度。
 */
class Solution {
public:
    int findLength(vector<int> &A, vector<int> &B) {
        // length[i][j]表示以A[i-1]和B[j-1]结尾的最长公共子串长度
        vector<vector<int>> length(A.size() + 1, vector<int>(B.size() + 1));

        // A为空串时
        for (int j = 0; j <= B.size(); ++j)
            length[0][j] = 0;

        int max_length = 0;
        for (int i = 1; i <= A.size(); ++i) {
            length[i][0] = 0;
            for (int j = 1; j <= B.size(); ++j) {
                if (A[i - 1] == B[j - 1])
                    length[i][j] = length[i - 1][j - 1] + 1;
                else
                    length[i][j] = 0;
                if (max_length < length[i][j])
                    max_length = length[i][j];
            }
        }

        return max_length;
    }
};

/*
 * 优化内存使用。时间复杂度O(mn)，空间复杂度O(n)。
 */
class Solution1 {
public:
    int findLength(vector<int> &A, vector<int> &B) {
        // length[i][j]表示以A[i-1]和B[j-1]结尾的最长公共子串长度
        vector<int> length(B.size() + 1, 0);

        int max_length = 0;
        for (int i = 1; i <= A.size(); ++i) {
            for (int j = static_cast<int>(B.size()); j >= 1; --j) {
                if (A[i - 1] == B[j - 1])
                    length[j] = length[j - 1] + 1;
                else
                    length[j] = 0;
                if (length[j] > max_length)
                    max_length = length[j];
            }
        }

        return max_length;
    }
};

/*
 * 滑动窗口。时间复杂度O((m+n) * min(m,n))，空间复杂度O(1)。
 */
class Solution2 {
public:
    int findLength(const vector<int> &A, const vector<int> &B) {
        int ans = 0;
        for (int iA = 0; iA < A.size(); ++iA)
            ans = std::max(ans, findLength(A, iA, B, 0));
        for (int iB = 1; iB < B.size(); ++iB)
            ans = std::max(ans, findLength(A, 0, B, iB));
        return ans;
    }

private:
    int findLength(const vector<int> &A, int iA, const vector<int> &B, int iB) {
        int ans = 0;
        int curr = 0;
        for (int i = 0; i + iA < A.size() && i + iB < B.size(); ++i) {
            if (A[i + iA] == B[i + iB])
                ++curr;
            else {
                ans = std::max(ans, curr);
                curr = 0;
            }
        }
        return std::max(ans, curr);  // 可能直到某个数组的末尾也能匹配
    }
};

int main() {
    // 3
    vector<int> A1 = {1, 2, 3, 2, 1};
    vector<int> B1 = {3, 2, 1, 4, 7};

    // 2
    vector<int> A2 = {0, 1, 1, 1, 1};
    vector<int> B2 = {1, 0, 1, 0, 1};

    Solution1 solution;
    cout << solution.findLength(A1, B1) << endl;
    cout << solution.findLength(A2, B2) << endl;

    return 0;
}
