#include <iostream>
#include <vector>
#include <unordered_map>

using std::cout;
using std::endl;
using std::vector;

/*
 * 先计算出数组的最大子序和P以及最小子序和Q，然后遍历Q和P之间的每一个K的倍数M，求子序和等于M的个数。
 * 时间复杂度O(n * M)，其中n为数组长度，M为Q和P之间K的倍数的个数。空间复杂度O(n)。
 */
class Solution {
public:
    int subarraysDivByK(const vector<int> &A, int K) {
        if (A.empty())
            return 0;

        int P = A[0];
        int Q = A[0];
        int max_sum = 0;
        int min_sum = 0;
        for (int num : A) {
            if (max_sum < 0)
                max_sum = 0;
            if (min_sum > 0)
                min_sum = 0;
            max_sum += num;
            min_sum += num;

            if (max_sum > P)
                P = max_sum;
            if (min_sum < Q)
                Q = min_sum;
        }

        int count = 0;
        for (int i = Q / K; i <= P / K; ++i) {
            int M = i * K;
            count += subarraySum(A, M);
        }

        return count;
    }

private:
    int subarraySum(const vector<int> &A, int k) {
        std::unordered_map<int, int> prefix_sum;
        int sum = 0;
        int count = 0;
        prefix_sum[0] = 1;   // 必不可少，表示从子数组开头到当前位置
        for (int num : A) {
            sum += num;
            auto it = prefix_sum.find(sum - k);
            if (it != prefix_sum.end())
                count += it->second;
            ++prefix_sum[sum];
        }
        return count;
    }
};

/*
 * 不用遍历每个可能的K的倍数，只需要将上面的函数subarraySum中的sum-k改一下使它能找到所有K的倍
 * 数的前缀和即可。子序和为prefix[j]-prefix[i]=mK，所以prefix[j]%K - prefix[i]%K = 0，
 * 使用哈希表M缓存当前位置j之前的所有prefix[i]%K的每个值的个数，则以A[j]结尾的子序和为K的倍数的
 * 个数就是M[prefix[j]%K]。
 * 此处需要考虑含负数的除法取余的问题，c++11规定，整数除法的结果向0截断，因此取余数的结果可能为
 * 负数，此处如果余数既有正数又有负数显然会出问题，如K=5，某个前缀和为-3，保存其模5的结果为-3，
 * 后面某个前缀和为7，则它们之间的子序和恰好为5，需要计数，但7%5=2，而查找2无法找到-3，因此答案
 * 错误。解决办法是都取正的余数，sum%K可能有负数，将其加K可得正数，但原来为正则超过K了，需要再
 * 对K取一次模，所以改成(sum%K + K)%K即可。
 */
class Solution1 {
public:
    int subarraysDivByK(const vector<int> &A, int K) {
        std::unordered_map<int, int> prefix_sum;
        int sum = 0;
        int count = 0;
        prefix_sum[0] = 1;   // 必不可少，表示从子数组开头到当前位置
        for (int num : A) {
            sum += num;
            auto it = prefix_sum.find((sum % K + K) % K);
            if (it != prefix_sum.end())
                count += it->second;
            ++prefix_sum[(sum % K + K) % K];
        }
        return count;
    }
};

/*
 * 与Solution1的思路完全一样，但直接使用数组来存储前缀和的余数等于某个数的个数：prefix_sum[i]
 * 表示前缀和模K后为i的个数。
 */
class Solution2 {
public:
    int subarraysDivByK(const vector<int> &A, int K) {
        vector<int> prefix_sum(K, 0);
        int sum = 0;
        int count = 0;
        prefix_sum[0] = 1;   // 必不可少，表示从子数组开头到当前位置
        for (int num : A) {
            sum += num;
            int mod = (sum % K + K) % K;
            count += prefix_sum[mod];
            ++prefix_sum[mod];
        }
        return count;
    }
};

int main() {
    // 7
    vector<int> A1 = {4, 5, 0, -2, -3, 1};
    int K1 = 5;

    Solution1 solution;
    cout << solution.subarraysDivByK(A1, K1) << endl;

    return 0;
}
