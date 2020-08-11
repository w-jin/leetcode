#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <algorithm>

using std::cout;
using std::endl;
using std::string;
using std::vector;

/*
 * 尝试所有组合，时间复杂度O(n^2*m)，其中n和m分别为单词个数和单词平均长度。
 * 超时！
 */
class Solution {
public:
    vector<vector<int>> palindromePairs(vector<string> &words) {
        vector<vector<int>> result;
        for (int i = 0; i < words.size(); ++i) {
            for (int j = 0; j < words.size(); ++j) {
                if (i != j && isPalindrome(words[i] + words[j]))
                    result.push_back({i, j});
            }
        }

        return result;
    }

private:
    bool isPalindrome(const string &str) {
        int i = 0;
        int j = static_cast<int>(str.size()) - 1;
        while (i < j) {
            if (str[i] != str[j])
                return false;
            ++i;
            --j;
        }
        return true;
    }
};

/*
 * 有四种情况：
 * 1、数组里有空字符串，并且数组里还有自己就是回文的字符串，每出现一个可与空字符串组成两对。
 * 2、如果自己的翻转后的字符串也在数组里，可以组成一对，注意翻转后不能是自己。
 * 3、如果某个字符串能找到一个分割点，分割点前的部分是回文，后半部分翻转后也在数组里，可组成一对。
 * 4、把3反过来，如果后部分是回文，前半部分翻转后在数组里，可组成一对。
 * 时间复杂度O(n * m^2)，空间复杂度O(n * m)，其中n和m分别为单词数量和单词平均长度。
 */
class Solution1 {
public:
    vector<vector<int>> palindromePairs(const vector<string> &words) {
        std::unordered_map<string, int> indices;
        for (int i = 0; i < words.size(); ++i) {
            string word = words[i];
            std::reverse(word.begin(), word.end());
            indices[word] = i;
        }

        vector<vector<int>> result;

        for (int i = 0; i < words.size(); ++i) {
            // 将单词words[i]在j前面分开
            for (int j = 0; j <= words[i].size(); ++j) {
                // 前半段是回文，看后半段的翻转是否在words中
                // j=0时此分支查找单词的翻转是否在words中，和下一个分支j=len时重复
                if (j > 0 && isPalindrome(words[i], 0, j - 1)) {
                    auto it = indices.find(words[i].substr(j));
                    if (it != indices.end())
                        result.push_back({it->second, i});
                }

                // 后半段是回文，看前半段的翻转是否在words中
                // 当j=len时尝试查找它本身的翻转是否在words中，如果找到的是它自身(单个字符)则不行
                // 当j=0时如果它本身是回文则可以和空串组成回文，因此查找空串
                if (isPalindrome(words[i], j, words[i].size() - 1)) {
                    auto it = indices.find(words[i].substr(0, j));
                    if (it != indices.end() && it->second != i)
                        result.push_back({i, it->second});
                }
            }
        }

        return result;
    }

private:
    // 判断子串str[first, ..., last]是否为回文串
    bool isPalindrome(const string &str, int first, int last) {
        while (first < last) {
            if (str[first] != str[last])
                return false;
            ++first;
            --last;
        }
        return true;
    }
};

std::ostream &operator<<(std::ostream &out, const vector<int> &vec) {
    if (vec.empty())
        return out;
    for (int i = 0; i + 1 < vec.size(); ++i)
        out << vec[i] << ", ";
    return out << vec.back();
}

std::ostream &operator<<(std::ostream &out, const vector<vector<int>> &vec) {
    if (vec.empty())
        return out << "{}\n";
    out << "{";
    for (int i = 0; i + 1 < vec.size(); ++i)
        out << "{" << vec[i] << "}, ";
    return out << "{" << vec.back() << "}}";
}

int main() {
    // {{0, 1}, {1, 0}, {3, 2}, {2, 4}}
    vector<string> words1 = {"abcd", "dcba", "lls", "s", "sssll"};

    // {{0, 1}, {1, 0}}
    vector<string> words2 = {"bat", "tab", "cat"};

    Solution1 solution;
    cout << solution.palindromePairs(words1) << endl;
    cout << solution.palindromePairs(words2) << endl;
}
