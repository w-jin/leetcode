#include <iostream>
#include <string>
#include <vector>
#include <unordered_set>

using std::cout;
using std::endl;
using std::string;
using std::vector;

class Solution {
public:
    bool wordBreak(const string &s, const vector<string> &wordDict) {
        std::unordered_set<string> wordDictSet;
        for (const string& word: wordDict) {
            wordDictSet.insert(word);
        }

        auto dp = vector<bool>(s.size() + 1, false);
        dp[0] = true;
        for (int i = 1; i <= s.size(); ++i) {
            for (int j = 0; j < i; ++j) {
                if (dp[j] && wordDictSet.find(s.substr(j, i - j)) != wordDictSet.end()) {
                    dp[i] = true;
                    break;
                }
            }
        }

        return dp[s.size()];
    }
};


int main() {
    // true
    string s1 = "leetcode";
    vector<string> wordDict1 = {"leet", "code"};

    // false
    string s2 = "applepenapple";
    vector<string> wordDict2 = {"apple", "pen"};

    // false
    string s3 = "catsandog";
    vector<string> wordDict3 = {"cats", "dog", "sand", "and", "cat"};

    Solution solution;
    cout << std::boolalpha;
    cout << solution.wordBreak(s1, wordDict1) << endl;
    cout << solution.wordBreak(s2, wordDict2) << endl;
    cout << solution.wordBreak(s3, wordDict3) << endl;

    return 0;
}
