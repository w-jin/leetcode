#include <iostream>
#include <string>
#include <vector>

using std::cout;
using std::endl;
using std::string;

/*
 * 听说暴力做法超时，我偏要试试。时间复杂度O(n^2)，空间复杂度O(1)。最后果然超时。
 */
class Solution {
public:
    int findTheLongestSubstring(const string &s) {
        int longest = 0;
        for (int i = 0; i < s.size(); ++i) {
            int count[5] = {0};
            for (int j = i; j < s.size(); ++j) {
                switch (s[j]) {
                    case 'a':
                        ++count[0];
                        break;
                    case 'e':
                        ++count[1];
                        break;
                    case 'i':
                        ++count[2];
                        break;
                    case 'o':
                        ++count[3];
                        break;
                    case 'u':
                        ++count[4];
                        break;
                    default:;
                }
                bool is_odd = true;
                for (int k = 0; k < 5; ++k) {
                    if (0 != count[k] % 2) {
                        is_odd = false;
                        break;
                    }
                }
                if (is_odd && j - i + 1 > longest)
                    longest = j - i + 1;
            }
        }
        return longest;
    }
};

/*
 * 参考1248统计优美子数组那题的解法，可以令prefix[i]表示奇偶性为i的最早位置，然后在遍历时计算
 * 当前的奇偶性，查询此奇偶性最早出现的位置，这段子串可以保证所有要求的字母都出现偶数次。需要注
 * 意的是不能给每个字母都设置一个prefix，因为无法将它们查询的结果组合起来，prefix的键应当为5个
 * 元音字母出现次数奇偶性的组合，类似于以下结构体：
 * struct Parity {
 *     bool a_odd;
 *     bool e_odd;
 *     bool i_odd;
 *     bool o_odd;
 *     bool u_odd;
 * };
 * unordered_map<Parity, int> prefix;
 * 由于结构体Parity每个成员都只有一位，可以将它精简一个整型变量，以它的一个二进制位表示一个字母
 * 出现次数的奇偶性，这样在状态的数量不是太多的时候，哈希表可以用一个数组代替(需要统计的字母太多
 * 的话，组合出来的状态个数太多，数组会非常长，当然哈希表也可能遇到这个问题)。这样就可以得到此
 * Solution所描述的算法。
 * 时间复杂度O(n)，空间复杂度O(s)，其中n为字符串长度，而s为状态个数，如果有5个需要统计的字母，
 * 则需要2^5=32个单元的空间。
 */
class Solution1 {
public:
    int findTheLongestSubstring(const string &s) {
        unsigned int status = 0;
        std::vector<int> pos(1 << 5, -1);  // -1表示没出现这个奇偶性组合
        pos[0] = 0;    // 全0表示5个元音都出现偶数次，开始于开头
        int longest = 0;
        for (int i = 0; i < s.size(); ++i) {
            switch (s[i]) {
                case 'a':
                    status ^= 1 << 0;
                    break;
                case 'e':
                    status ^= 1 << 1;
                    break;
                case 'i':
                    status ^= 1 << 2;
                    break;
                case 'o':
                    status ^= 1 << 3;
                    break;
                case 'u':
                    status ^= 1 << 4;
                    break;
                default:;
            }
            if (pos[status] == -1)  // 先前无此组合，此位置为第一个
                pos[status] = i + 1;
            else
                longest = std::max(longest, i - pos[status] + 1);
        }

        return longest;
    }
};

int main() {
    // 13
    string s1 = "eleetminicoworoep";

    // 5
    string s2 = "leetcodeisgreat";

    // 6
    string s3 = "bcbcbc";

    Solution1 solution;
    cout << solution.findTheLongestSubstring(s1) << endl;
    cout << solution.findTheLongestSubstring(s2) << endl;
    cout << solution.findTheLongestSubstring(s3) << endl;

    return 0;
}
