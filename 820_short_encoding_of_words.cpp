#include <iostream>
#include <string>
#include <vector>
#include <stack>
#include <unordered_map>
#include <algorithm>

using std::cout;
using std::endl;
using std::string;
using std::vector;

/*
    设单词平均长度为w，则排序的时间复杂度为O(N log N * w)，而跳过后缀的时间复杂度为O(N w)，
    所以总的时间复杂度为O(N log N * w)。空间复杂度O(1)。
*/
class Solution {
public:
    int minimumLengthEncoding(vector<string> &words) {
        // 从尾部开始按字典序排序
        std::sort(words.begin(), words.end(), [](const string &a, const string &b) {
            int i = static_cast<int>(a.size()) - 1;
            int j = static_cast<int>(b.size()) - 1;
            while (i >= 0 && j >= 0) {
                if (a[i] != b[j])
                    return a[i] < b[j];
                --i;
                --j;
            }
            return j >= 0;  // b较长时也认为它比较大，相等的情况判到了小于里面
        });

        int length = 0;
        for (int i = 0; i < words.size(); ++i) {
            // 如果words[i]是某个字符串的后缀，就不用保存它，这个字符串只能是后面的那个
            if (i + 1 < words.size() && isSuffix(words[i + 1], words[i]))
                continue;
            length += static_cast<int>(words[i].size()) + 1;
        }

        return length;
    }

private:
    // b是否是a的后缀，不考虑空串
    bool isSuffix(const string &a, const string &b) {
        int i = static_cast<int>(a.size()) - 1;
        int j = static_cast<int>(b.size()) - 1;
        while (i >= 0 && j >= 0) {
            if (a[i] != b[j])
                return false;
            --i;
            --j;
        }
        return (i >= 0) || (i == -1 && j == -1);  // a比b长或者两者一样长
    }
};

/*
    以单词的反序字符串构造字典树，字典树的叶子个数就是需要存储的单词个数，从根节点到叶子节点的路径
    长度就是单词长度。
*/
class Solution1 {
public:
    int minimumLengthEncoding(vector<string> &words) {
        TrieNode *root = createTrie(words);

        // 遍历字典树统计单词长度之和
        int length = 0;
        std::stack<TrieNode *> s;
        s.push(root);
        while (!s.empty()) {
            TrieNode *p = s.top();
            s.pop();

            bool is_leaf = true;
            for (TrieNode *child : p->children) {
                if (child) {
                    is_leaf = false;
                    s.push(child);
                }
            }
            if (is_leaf)
                length += p->length + 1;
        }

        delete root;
        return length;
    }

    // 字典树实现
    struct TrieNode {
        int length = 0;  // 从根节点到此节点的单词长度
        TrieNode *children[26] = {nullptr};

        // 递归删除子节点
        ~TrieNode() {
            for (TrieNode *child : children) {
                delete child;
                child = nullptr;
            }
        }
    };

    TrieNode *createTrie(const vector<string> &words) {
        auto *root = new TrieNode{};

        for (const string &word : words) {
            TrieNode *p = root;
            for (auto it = word.rbegin(); it != word.rend(); ++it) {
                if (p->children[*it - 'a'] == nullptr) {
                    p->children[*it - 'a'] = new TrieNode{};
                    p->children[*it - 'a']->length = p->length + 1;
                }
                p = p->children[*it - 'a'];
            }
        }

        return root;
    }

    void destroyTrie(TrieNode *root) {
        delete root;
    }
};

/*
    字典树实现与前面不一样，使用哈希缓存所有节点。
    字典树节点中的get函数的设计值得参考！
    注意：此份代码来自于官方题解，字典树没有内存释放功能！
*/
class Solution2 {
public:
    class TrieNode {
        TrieNode *children[26] = {nullptr};
    public:
        int count = 0;

        TrieNode *get(char c) {
            if (children[c - 'a'] == nullptr) {
                children[c - 'a'] = new TrieNode();
                count++;
            }
            return children[c - 'a'];
        }
    };

    int minimumLengthEncoding(vector<string> &words) {
        auto *trie = new TrieNode();
        std::unordered_map<TrieNode *, int> nodes;

        for (int i = 0; i < (int) words.size(); ++i) {
            string word = words[i];
            TrieNode *cur = trie;
            for (auto it = word.rbegin(); it != word.rend(); ++it)
                cur = cur->get(*it);
            nodes[cur] = i;
        }

        int length = 0;
        for (auto node : nodes) {
            if (node.first->count == 0) {
                length += static_cast<int>(words[node.second].length()) + 1;
            }
        }
        return length;
    }
};

class Solution3 {
public:
    int minimumLengthEncoding(vector<string> &words) {
        for (string &word : words)
            std::reverse(word.begin(), word.end());

        std::sort(words.begin(), words.end());

        int length = 0;
        for (int i = 0; i < words.size(); ++i) {
            if (i + 1 < words.size()
                && words[i] == words[i + 1].substr(0, words[i].size()))
                continue;
            length += static_cast<int>(words[i].size()) + 1;
        }

        return length;
    }
};

int main() {
    // 10
    vector<string> words1 = {"time", "me", "bell"};

    // 5
    vector<string> words2 = {"time", "time", "time", "time"};

    Solution3 solution;
    cout << solution.minimumLengthEncoding(words1) << endl;
    cout << solution.minimumLengthEncoding(words2) << endl;

    return 0;
}
