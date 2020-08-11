#include <iostream>
#include <vector>
#include <string>

/* KMP算法，时间复杂度为O(m+n)。 */
class Solution {
public:
    int strStr(const std::string &haystack, const std::string &needle) {
        if (needle.empty())
            return 0;

        generateNext(needle);

        int m = static_cast<int>(haystack.size());
        int n = static_cast<int>(needle.size());
        int i = 0, j = 0;
        while (i < m && j < n) {
            if (j == -1 || haystack[i] == needle[j]) {
                ++i;
                ++j;
            }
            else
                j = next[j];
        }
        if (j == needle.size())
            return i - n;
        else
            return -1;
    }

private:
    std::vector<int> next;

    void generateNext(const std::string &needle) {
        next.resize(needle.size());
        next[0] = -1;
        int j = -1;
        size_t i = 0;
        while (i + 1 < needle.size()) {
            if (j == -1 || needle[i] == needle[j]) {
                ++i;
                ++j;
                next[i] = j;
            }
            else
                j = next[j];
        }
    }
};

/* 暴力算法，从haystack每个字符开始的串都匹配一次。 */
class Solution1 {
public:
    int strStr(const std::string &haystack, const std::string &needle) {
        if (needle.empty())
            return 0;

        const int m = static_cast<int>(haystack.size()), n = static_cast<int>(needle.size());
        for (int i = 0; i <= m - n; ++i) {
            if (haystack[i] != needle[0])
                continue;
            int j = 0;
            for (j = 1; j < n; ++j) {
                if (haystack[i + j] != needle[j])
                    break;
            }

            if (j == n)
                return i;
        }
        return -1;
    }
};

int main()
{
    std::string haystack1 = "hello", needle1 = "ll"; //2
    std::string haystack2 = "aaaaa", needle2 = "bba"; //-1
    std::string haystack3 = "mississipi", needle3 = "issipi"; //4
    std::string haystack4 = "mississippi", needle4 = "iiiipi"; //-1
    std::string haystack5 = "mississippi", needle5 = "pi"; //9

    Solution solution;
    std::cout << solution.strStr(haystack1, needle1) << std::endl;
    std::cout << solution.strStr(haystack2, needle2) << std::endl;
    std::cout << solution.strStr(haystack3, needle3) << std::endl;
    std::cout << solution.strStr(haystack4, needle4) << std::endl;
    std::cout << solution.strStr(haystack5, needle5) << std::endl;

    return 0;
}
