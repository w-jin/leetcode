#include <iostream>
#include <string>
#include <unordered_map>

using std::cout;
using std::endl;
using std::string;
using std::unordered_map;
using std::pair;

class Solution {
public:
    int getMaxRepetitions(const string &s1, int n1, const string &s2, int n2) {
        string S1;
        for (int n = 0; n < n1; ++n)
            S1 += s1;
        string S2;
        for (int n = 0; n < n2; ++n)
            S2 += s2;

        int M = static_cast<int>(S1.size() / S2.size());
        while (M > 0) {
            string S;
            for (int n = 0; n < M; ++n)
                S += S2;
            if (isSubStr(S1, S))
                return M;
            --M;
        }

        return 0;
    }

private:
    // s1删除某些字符后能否得到s2
    bool isSubStr(const string &s1, const string &s2) {
        int i1 = 0;
        int i2 = 0;
        while (i1 < s1.size() && i2 < s2.size()) {
            if (s1[i1] == s2[i2]) {
                ++i1;
                ++i2;
            } else {
                ++i1;
            }
        }
        return i2 == s2.size();
    }
};

class Solution1 {
public:
    int getMaxRepetitions(const string &s1, int n1, const string &s2, int n2) {
        if (n1 == 0) {
            return 0;
        }
        int s1cnt = 0, index = 0, s2cnt = 0;
        // recall 是我们用来找循环节的变量，它是一个哈希映射
        // 我们如何找循环节？假设我们遍历了 s1cnt 个 s1，此时匹配到了第 s2cnt 个 s2 中的第 index 个字符
        // 如果我们之前遍历了 s1cnt' 个 s1 时，匹配到的是第 s2cnt' 个 s2 中同样的第 index 个字符，那么就有循环节了
        // 我们用 (s1cnt', s2cnt', index) 和 (s1cnt, s2cnt, index) 表示两次包含相同 index 的匹配结果
        // 那么哈希映射中的键就是 index，值就是 (s1cnt', s2cnt') 这个二元组
        // 循环节就是；
        //    - 前 s1cnt' 个 s1 包含了 s2cnt' 个 s2
        //    - 以后的每 (s1cnt - s1cnt') 个 s1 包含了 (s2cnt - s2cnt') 个 s2
        // 那么还会剩下 (n1 - s1cnt') % (s1cnt - s1cnt') 个 s1, 我们对这些与 s2 进行暴力匹配
        // 注意 s2 要从第 index 个字符开始匹配
        unordered_map<int, pair<int, int>> recall;
        pair<int, int> pre_loop, in_loop;
        while (true) {
            // 我们多遍历一个 s1，看看能不能找到循环节
            ++s1cnt;
            for (char ch: s1) {
                if (ch == s2[index]) {
                    index += 1;
                    if (index == s2.size()) {
                        ++s2cnt;
                        index = 0;
                    }
                }
            }
            // 还没有找到循环节，所有的 s1 就用完了
            if (s1cnt == n1) {
                return s2cnt / n2;
            }
            // 出现了之前的 index，表示找到了循环节
            if (recall.count(index)) {
                int s1cnt_prime = recall[index].first;
                int s2cnt_prime = recall[index].second;
                // 前 s1cnt' 个 s1 包含了 s2cnt' 个 s2
                pre_loop = {s1cnt_prime, s2cnt_prime};
                // 以后的每 (s1cnt - s1cnt') 个 s1 包含了 (s2cnt - s2cnt') 个 s2
                in_loop = {s1cnt - s1cnt_prime, s2cnt - s2cnt_prime};
                break;
            }
            else {
                recall[index] = {s1cnt, s2cnt};
            }
        }
        // ans 存储的是 S1 包含的 s2 的数量，考虑的之前的 pre_loop 和 in_loop
        int ans = pre_loop.second + (n1 - pre_loop.first) / in_loop.first * in_loop.second;
        // S1 的末尾还剩下一些 s1，我们暴力进行匹配
        int rest = (n1 - pre_loop.first) % in_loop.first;
        for (int i = 0; i < rest; ++i) {
            for (char ch: s1) {
                if (ch == s2[index]) {
                    ++index;
                    if (index == s2.size()) {
                        ++ans;
                        index = 0;
                    }
                }
            }
        }
        // S1 包含 ans 个 s2，那么就包含 ans / n2 个 S2
        return ans / n2;
    }
};

int main() {
    // 2
    string s1_1 = "acb";
    int n1_1 = 4;
    string s2_1 = "ab";
    int n2_1 = 2;

    // 2468
    string s1_2 = "niconiconi";
    int n1_2 = 99981;
    string s2_2 = "nico";
    int n2_2 = 81;

    Solution1 solution;
    cout << solution.getMaxRepetitions(s1_1, n1_1, s2_1, n2_1) << endl;
    cout << solution.getMaxRepetitions(s1_2, n1_2, s2_2, n2_2) << endl;

    return 0;
}
