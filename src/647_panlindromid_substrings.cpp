#include <iostream>
#include <string>
#include <vector>

using std::cout;
using std::endl;
using std::string;

/*
 * 从所有可能的中点向两边查找。
 * 时间复杂度O(n^2)，空间复杂度O(1)。
 */
class Solution {
public:
    int countSubstrings(const string &s) {
        int count = 0;

        const int n = s.size();

        // 以i为中心向两边查找
        for (int i = 0; i < n; ++i) {
            int left = i;
            int right = i;
            while (left >= 0 && right < n && s[left] == s[right]) {
                ++count;
                --left;
                ++right;
            }
        }

        // 以i和i+1中间为中心位置，向两边查找
        for (int i = 0; i < n - 1; ++i) {
            int left = i;
            int right = i + 1;
            while (left >= 0 && right < n && s[left] == s[right]) {
                ++count;
                --left;
                ++right;
            }
        }

        return count;
    }
};


/*
 * 从所有可能的中点向两边查找。将两个循环合成一个。
 * 时间复杂度O(n^2)，空间复杂度O(1)。
 */
class Solution1 {
public:
    int countSubstrings(const string &s) {
        int count = 0;

        const int n = s.size();

        // i为偶数时以s[i/2]为中心，i为奇数时以s[i/2]和s[i/2+1]的中间为中心
        for (int i = 0; i < 2 * n - 1; ++i) {
            int left = i / 2;
            int right = (i + 1) / 2;
            while (left >= 0 && right < n && s[left] == s[right]) {
                --left;
                ++right;
            }
            count += (right - left) / 2;
        }

        return count;
    }
};

/*
 * Manacher算法，找到从任意中点出发的最长子串，将长度加1除以2即为对回文串个数的贡献。
 * 时间复杂度O(n)，空间复杂度O(n)。
 */
class Solution2 {
public:
    int countSubstrings(const string &s) {
        string str(1 + 2 * s.size(), '#');
        for (int i = 0; i < s.size(); ++i)
            str[2 * i + 1] = s[i];

        int count = 0;

        // RL[i]表示以str[i]为中心的最长回文串最右一个字符与i的距离，也是最长回文串的长度(不算#)
        std::vector<int> RL(str.size(), 0);
        int max_right = -1;  // 当前触及的最远下标
        int pos = -1;        // 触及最远下标的中心位置
        for (int i = 0; i < str.size(); ++i) {
            if (i < max_right)
                RL[i] = std::min(RL[2 * pos - i], max_right - i);
            else
                RL[i] = 1;

            while (i - RL[i] >= 0 && i + RL[i] < str.size() && str[i - RL[i]] == str[i + RL[i]])
                ++RL[i];
            --RL[i];

            if (i + RL[i] > max_right) {
                max_right = i + RL[i];
                pos = i;
            }

            count += (RL[i] + 1) / 2;
        }

        return count;
    }
};

int main() {
    // 3
    string s1 = "abc";

    // 6
    string s2 = "aaa";

    Solution2 solution;
    cout << solution.countSubstrings(s1) << endl;
    cout << solution.countSubstrings(s2) << endl;

    return 0;
}
