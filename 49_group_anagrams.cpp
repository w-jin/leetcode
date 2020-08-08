#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
#include <algorithm>

class Solution {
public:
    std::vector<std::vector<std::string>> groupAnagrams(const std::vector<std::string> &strs) {
        std::unordered_map<std::string, std::vector<std::string>> cache;
        for (const auto &str : strs) {
            std::string temp = str;
            std::sort(temp.begin(), temp.end());
            cache[temp].push_back(str);
        }

        std::vector<std::vector<std::string>> result;
        for (const auto &it : cache)
            result.push_back(it.second);

        return result;
    }
};

std::ostream &operator<<(std::ostream &out, const std::vector<std::vector<std::string>> &strs)
{
    for (const auto &v : strs) {
        for (const auto &s : v)
            out << s << " ";
        out << std::endl;
    }
    return out;
}

int main()
{
    // ["ate","eat","tea"],
    // ["nat","tan"],
    // ["bat"]
    std::vector<std::string> strs = {"eat", "tea", "tan", "ate", "nat", "bat"};
    Solution solution;
    std::cout << solution.groupAnagrams(strs);

    return 0;
}
