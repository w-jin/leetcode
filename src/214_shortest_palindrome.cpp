#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using std::cout;
using std::endl;
using std::string;
using std::vector;

/*
 * 从后向前使用Manacher算法计算以每个位置为中心的最长回文串，当触及的最远位置到达0时退出，
 * 此时的中心即为转换后的最短回文串的中心位置，将字符串的从此位置的2倍到末尾的子串反序加在
 * 原串开头即为所示最短回文串。
 * 时间复杂度O(n)，空间复杂度O(n)。
 */
class Solution {
public:
    string shortestPalindrome(string s) {
        // 先在s的每两个字符中间插入#
        string str(2 * s.size() + 1, 0);
        for (int i = 0; i < str.size(); ++i) {
            if (i % 2 == 0)
                str[i] = '#';
            else
                str[i] = s[i / 2];
        }

        // 从后向前使用Manacher算法
        const int N = str.size();
        vector<int> radius(N);  // radius[i]是以i为中心的最长回文串的长度(原串s中，str中是半径)
        int left = N;           // 当前触及的最远位置
        int pos = N - 1;        // 触及最远位置的下标
        for (int i = N - 1; i >= 0; --i) {
            // 如果i在已经触及的区域内，那么它附近的字符与关于pos的对称位置的字符相同
            if (i > left)
                radius[i] = std::min(radius[2 * pos - i], i - left);
            else
                radius[i] = 1;

            // 向两边拓展
            while (i - radius[i] >= 0 && i + radius[i] < N && str[i - radius[i]] == str[i + radius[i]])
                ++radius[i];
            --radius[i];

            // 如果以i为中心的回文串触及的区域更远，则更新最远触及距离
            if (i - radius[i] < left) {
                left = i - radius[i];
                pos = i;

                // 如果left已经到达0，则此位置即为所求，无需再继续算下去
                if (left == 0)
                    break;
            }
        }

        // radius[pos]是以pos为中心的最大回文长度，那么s.size()-radius[pos]就是需要复制的字符个数
        const int M = s.size() - radius[pos];
        string result(s.size() + M, 0);
        for (int i = 0; i < M; ++i)
            result[i] = s[s.size() - i - 1];
        for (int i = 0; i < s.size(); ++i)
            result[i + M] = s[i];
        return result;
    }
};

/*
 * 从前向后使用Manacher算法，只需要计算前一半，然后从一半的位置向前找第一个i-radius[i]为0的
 * 位置，此位置即为转换后的最短回文串的中心位置，将字符串的从此位置的2倍到末尾的子串反序加在
 * 原串开头即为所示最短回文串。
 * 时间复杂度O(n)，空间复杂度O(n)。
 */
class Solution1 {
public:
    string shortestPalindrome(string s) {
        // 从前向后使用Manacher算法，只需要计算前一半，然后从一半的位置向前找第一个i-radius[i]为的
        // 位置，此位置即为转换后的最短回文串的中心位置，将字符串的从此位置的2倍到末尾的子串反序加在
        // 原串开头即为所示最短回文串

        // 先在s的每两个字符中间插入#
        string str(2 * s.size() + 1, 0);
        for (int i = 0; i < str.size(); ++i) {
            if (i % 2 == 0)
                str[i] = '#';
            else
                str[i] = s[i / 2];
        }

        // 使用Manacher算法计算以前一半字符为中心的最长回文串的半径
        const int N = str.size();
        vector<int> radius(N);   // radius[i]是以i为中心的最长回文串的长度(原串s中，str中是半径)
        int right = -1;          // 当前触及的最远位置
        int pos = -1;            // 触及最远位置的下标
        for (int i = 0; i <= N / 2; ++i) {
            // 如果i在已经触及的区域内，那么它附近的字符与关于pos的对称位置的字符相同
            if (i < right)
                radius[i] = std::min(radius[2 * pos - i], right - i);
            else
                radius[i] = 1;

            // 向两边拓展
            while (i - radius[i] >= 0 && i + radius[i] < N && str[i - radius[i]] == str[i + radius[i]])
                ++radius[i];
            --radius[i];

            // 如果以i为中心的回文串触及的区域更远，则更新最远触及距离
            if (i + radius[i] > right) {
                right = i + radius[i];
                pos = i;
            }
        }

        // 从一半位置开始向前找第一个触及字符串开头位置的中心
        pos = N / 2;
        while (pos >= 0) {
            if (pos - radius[pos] == 0)
                break;
            else
                --pos;
        }

        // radius[pos]是以pos为中心的最大回文长度，那么s.size()-radius[pos]就是需要复制的字符个数
        const int M = s.size() - radius[pos];
        string result(s.size() + M, 0);
        for (int i = 0; i < M; ++i)
            result[i] = s[s.size() - i - 1];
        for (int i = 0; i < s.size(); ++i)
            result[i + M] = s[i];
        return result;
    }
};

/*
 * 使用哈希来判断两个字符串是否相等，取哈希函数为：
 *    hash(s) = hash(s[1,...,n-1]) * base + s[n]  mod P
 * base应当取一个大于字符集大小的质数，如s中的字符范围为ASCII码值，则可取base为131(大于
 * 128的质数)。P应当取大质数，取大于字符串长度平方级别的质数即可，如1000000007(十亿零七)。
 *
 * 这样在判断s的前缀是否为回文时可以递推计算它和它的反转的哈希值，然后比较是否相等，如果相等
 * 则认为两个串相同，否则认为不同，找到某个前缀与其反转相同，且保证它最长，然后将末尾剩余字符
 * 反转加在字符串前面就得到了所示最短回文串。
 *
 * 时间复杂度O(n)，空间复杂度O(1)。
 *
 * 警告：切勿在工程中使用这种方法，如果要用，至少应当在哈希值相同的时候再比较一次原串，以保证
 *      在哈希冲突时不会出错。
 */
class Solution2 {
public:
    string shortestPalindrome(string s) {
        const int base = 131;
        const int mod = 1000000007;

        int max_len = 0;
        int base_i = 1;
        int hash_s = 0;
        int hash_rs = 0;
        for (int i = 0; i < s.size(); ++i) {
            hash_s = ((long long)hash_s * base + s[i]) % mod;
            hash_rs = (hash_rs + (long long)s[i] * base_i) % mod;
            base_i = (long long)base_i * base % mod;
            if (hash_s == hash_rs)
                max_len = i + 1;
        }

        string tail = s.substr(max_len);
        std::reverse(tail.begin(), tail.end());
        return tail + s;
    }
};

/*
 * 在反转串中查找原串，如果从位置i开始可以匹配到反转串的末尾去，则匹配的这一部分是回文串，如
 * s=aacecaaa，反转后为s1=aaacecaa，在s1中查找s，从位置1开始匹配，直到s1的末尾都是匹配的，
 * 因此s1中从1到末尾的子串，即aacecaa是回文串，s中未匹配的剩余部分反转后加在开头即为所求回
 * 文串。要保证最后的回文串最短，则s1中开始匹配的位置要尽量靠前。
 * 匹配过程使用KMP算法，时间复杂度O(n)，空间复杂度O(n)。
 */
class Solution3 {
public:
    string shortestPalindrome(string s) {
        string rs = s;
        std::reverse(rs.begin(), rs.end());
        int pos = kmp(rs, s);   // 第一个能匹配到rs末尾的位置，即rs前面失配的字符数量
        return rs.substr(0, pos) + s;
    }

private:
    int kmp(const string &s, const string &t) {
        vector<int> next = getNext(t);
        int i = 0;
        int j = 0;
        const int N = s.size();
        const int M = t.size();   // 必须转成有符号数！
        while (i < N && j < M) {
            if (j == -1 || s[i] == t[j]) {
                ++i;
                ++j;
            } else {
                j = next[j];
            }
        }
        return i - j;
    }

    vector<int> getNext(const string &t) {
        if (t.empty())
            return {};
        vector<int> next(t.size());
        next[0] = -1;
        int k = -1;
        for (int j = 1; j < t.size(); ++j) {
            while (k >= 0 && t[j - 1] != t[k])
                k = next[k];
            ++k;
            if (t[j] == t[k])
                next[j] = next[k];
            else
                next[j] = k;
        }
        return next;
    }
};

int main() {
    // aaacecaaa
    string s1 = "aacecaaa";

    // dcbabcd
    string s2 = "abcd";

    Solution3 solution;
    cout << solution.shortestPalindrome(s1) << endl;
    cout << solution.shortestPalindrome(s2) << endl;

    return 0;
}
