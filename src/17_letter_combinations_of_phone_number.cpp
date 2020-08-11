#include <iostream>
#include <string>
#include <vector>
#include <stack>

class Solution {
public:
    std::vector<std::string> letterCombinations(const std::string &digits) {
        if (digits.empty())
            return combinations;
        path.resize(digits.size());
        letterCombinationsRecursive(digits, 0); //从第一个字符开始进行深度优先遍历找出所有的字符组合
        return combinations;
    }

private:
    //字符映射表，0和1不对应任何字符
    const std::string char_map[10] = {"", "", "abc", "def", "ghi", "jkl", "mno", "pqrs", "tuv", "wxyz"};

    std::vector<std::string> combinations;
    std::string path;

    void letterCombinationsRecursive(const std::string &digits, size_t curr) {
        //已经找到一个组合
        if (curr == digits.size()) {
            combinations.push_back(path);
            return;
        }
        //继续往下遍历
        for (char i : char_map[digits[curr] - '0']) {
            path[curr] = i;
            letterCombinationsRecursive(digits, curr + 1);
        }
    }
};

class Solution1 {
public:
    std::vector<std::string> letterCombinations(const std::string &digits) {
        //仍然使用深度优先遍历，但以循环来实现
        std::vector<std::string> combinations;
        if (digits.empty())
            return combinations;

        //字符映射表，0和1不对应任何字符
        const std::string char_map[10] = {"", "", "abc", "def", "ghi", "jkl", "mno", "pqrs", "tuv", "wxyz"};
        std::string path(digits.size(), '0');
        std::stack<std::pair<int, int>> s; //栈顶表示当前访问到第几个数字对应的第几个字母
        s.push(std::make_pair(0, 0));
        while (!s.empty()) {
            std::pair<int, int> curr = s.top();
            s.pop();
            //已经找到一个组合
            if (curr.first == digits.size()) {
                combinations.push_back(path);
            }
            //继续向下遍历
            else if (curr.second < char_map[digits[curr.first] - '0'].size()) {
                path[curr.first] = char_map[digits[curr.first] - '0'][curr.second];
                s.push(std::make_pair(curr.first, curr.second + 1));
                s.push(std::make_pair(curr.first + 1, 0));
            }
        }

        return combinations;
    }
};

int main()
{
    //["ad", "ae", "af", "bd", "be", "bf", "cd", "ce", "cf"]
    std::string digits = "23";
    Solution1 solution;
    std::vector<std::string> result = solution.letterCombinations(digits);
    for (const auto &s : result)
        std::cout << s << std::endl;
    return 0;
}
