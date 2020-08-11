#include <iostream>
#include <string>
#include <vector>

using std::cout;
using std::endl;
using std::string;
using std::vector;

class Solution {
public:
    int countCharacters(const vector<string> &words, const string &chars) {
        vector<int> alphabet(26, 0);
        for (char c : chars)
            ++alphabet[c - 'a'];

        int length_sum = 0;
        for (const string &word : words) {
            bool good = true;
            vector<int> temp = alphabet;
            for (char c : word) {
                --temp[c - 'a'];
                if (temp[c - 'a'] < 0) {
                    good = false;
                    break;
                }
            }
            if (good)
                length_sum += static_cast<int>(word.size());
        }

        return length_sum;
    }
};

int main() {
    // 6
    vector<string> words1 = {"cat", "bt", "hat", "tree"};
    string chars1 = "atach";

    // 10
    vector<string> words2 = {"hello", "world", "leetcode"};
    string chars2 = "welldonehoneyr";

    Solution solution;
    cout << solution.countCharacters(words1, chars1) << endl;
    cout << solution.countCharacters(words2, chars2) << endl;

    return 0;
}
