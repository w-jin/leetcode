#include <iostream>
#include <string>
#include <vector>
#include <limits>
#include <unordered_set>

using std::cout;
using std::endl;
using std::string;
using std::vector;

/*
 * 动态规划。设unknown[i]表示s[0, .., i - 1]有多少个不能识别的字符数，则
 * unknown[i + 1] = max{
 *      unknown[j], s[j, .., i]在字典中；
 *      unknown[j] + (i - j + 1), s[j, .., i]不在字典中
 * } for 0 <= j <= i
 * 时间复杂度O(n^2)，空间复杂度O(length(sentence))。
 */
class Solution {
public:
    int respace(vector<string> &dictionary, string sentence) {
        std::unordered_set<string> dict(dictionary.begin(), dictionary.end());

        vector<int> unknown(sentence.size() + 1, std::numeric_limits<int>::max());
        unknown[0] = 0;  // 空串

        for (int i = 0; i < sentence.size(); ++i) { // 以sentence[i]结尾的串
            for (int j = 0; j <= i; ++j) {
                if (dict.find(sentence.substr(j, i - j + 1)) != dict.end())
                    unknown[i + 1] = std::min(unknown[i + 1], unknown[j]);
                else
                    unknown[i + 1] = std::min(unknown[i + 1], unknown[j] + (i - j + 1));
            }
        }

        return unknown.back();
    }
};


/*
 * 字典树。
 */
class Trie {
public:
    Trie *next[26] = {nullptr};
    bool isEnd;

    Trie() {
        isEnd = false;
    }

    ~Trie() {
        for (int i = 0; i < 26; ++i)
            delete next[i];
    }

    void insert(const string &s) {
        Trie *curPos = this;

        for (int i = s.length() - 1; i >= 0; --i) {
            int t = s[i] - 'a';
            if (curPos->next[t] == nullptr) {
                curPos->next[t] = new Trie();
            }
            curPos = curPos->next[t];
        }
        curPos->isEnd = true;
    }
};

class Solution1 {
public:
    int respace(vector<string> &dictionary, const string &sentence) {
        int n = sentence.length();

        Trie *root = new Trie();
        for (auto &word: dictionary) {
            root->insert(word);
        }

        vector<int> dp(n + 1);
        dp[0] = 0;
        for (int i = 1; i <= n; ++i) {
            dp[i] = dp[i - 1] + 1;

            Trie *curPos = root;
            for (int j = i; j >= 1; --j) {
                int t = sentence[j - 1] - 'a';
                if (curPos->next[t] == nullptr) {
                    break;
                } else if (curPos->next[t]->isEnd) {
                    dp[i] = std::min(dp[i], dp[j - 1]);
                }
                if (dp[i] == 0) {
                    break;
                }
                curPos = curPos->next[t];
            }
        }

        delete root;
        return dp[n];
    }
};


int main() {
    // 7
    vector<string> dictionary1 = {"looked", "just", "like", "her", "brother"};
    string sentence1 = "jesslookedjustliketimherbrother";

    Solution1 solution;
    cout << solution.respace(dictionary1, sentence1) << endl;

    return 0;
}
