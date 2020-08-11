#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>

class Solution {
public:
    std::vector<int> findSubstring(const std::string &s, std::vector<std::string> &words) {
        std::vector<int> result;
        if (words.empty() || words[0].empty())
            return result;

        std::unordered_map<std::string, unsigned int> words_count;
        for (const auto &word : words)
            ++words_count[word];

        std::string::size_type word_len = words[0].size(), count = words.size();
        std::string::size_type start = 0, end = word_len * count - 1; //end不会溢出
        std::unordered_map<std::string, unsigned int> words_count_s;
        while (end < s.size()) {
            words_count_s = words_count;
            for (std::string::size_type i = start; i <= end; i += word_len) {
                std::string temp(&s[i], &s[i + word_len]);
                auto it = words_count_s.find(temp);
                if (it == words_count_s.end())
                    break;
                --(it->second);
                if (it->second == 0)
                    words_count_s.erase(it);
            }
            if (words_count_s.empty())
                result.push_back(static_cast<int>(start));
            ++start;
            ++end;
        }

        return result;
    }
};

class Solution1 {
public:
    std::vector<int> findSubstring(const std::string &s, std::vector<std::string> &words) {
        std::vector<int> result;
        if (words.empty() || words[0].empty())
            return result;

        std::unordered_map<std::string, unsigned int> words_count;
        for (const auto &word : words)
            ++words_count[word];

        const size_t word_len = words[0].size(), count = words.size();
        const size_t s_len = s.size(), sub_len = word_len * count;
        size_t left = 0, right = 0, curr_count = 0;
        std::string left_substr, right_substr;
        for (size_t start = 0; start < word_len; ++start) {
            left = right = start;
            curr_count = 0;
            while (right < s_len && left <= s_len - sub_len) {
                right_substr = s.substr(right, word_len);
                auto it = words_count.find(right_substr);
                if (it != words_count.end() && it->second != 0) {
                    --(it->second);
                    ++curr_count;
                }
                else {
                    left_substr = s.substr(left, word_len);
                    while (left_substr != right_substr) {
                        ++words_count[left_substr];
                        --curr_count;
                        left += word_len;
                        left_substr = s.substr(left, word_len);
                    }
                    left += word_len;
                }
                if (curr_count == count)
                    result.push_back(left);
                right += word_len;
            }
            while (left < right) {
                ++words_count[s.substr(left, word_len)];
                left += word_len;
            }
        }

        return result;
    }
};

std::ostream &operator<<(std::ostream &out, const std::vector<int> &v)
{
    for (int i : v)
        out << i << " ";
    return out;
}

int main()
{
    //{0, 9}
    std::string s1 = "barfoothefoobarman";
    std::vector<std::string> words1 = {"foo", "bar"};

    //{}
    std::string s2 = "wordgoodgoodgoodbestword";
    std::vector<std::string> words2 = {"word", "good", "best", "word"};

    //{0, 1, 2}
    std::string s3 = "aaaaaaaa";
    std::vector<std::string> words3 = {"aa", "aa", "aa"};

    Solution1 solution;
    std::cout << solution.findSubstring(s1, words1) << std::endl;
    std::cout << solution.findSubstring(s2, words2) << std::endl;
    std::cout << solution.findSubstring(s3, words3) << std::endl;
    
    return 0;
}
