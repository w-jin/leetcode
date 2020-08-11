#include <iostream>
#include <string>
#include <vector>

class Solution {
public:
    std::vector<std::string> generateParenthesis(int n) {
        if (n <= 0)
            return combinations;
        parenthesis.resize(2 * n);
        this->N = n;
        parenthesis[0] = '(';
        generateParenthesisRecursive(1, 0);
        return combinations;
    }

private:
    int N = 0;
    std::string parenthesis;
    std::vector<std::string> combinations;

    //left为目前左括号个数，right为目前右括号个数
    void generateParenthesisRecursive(int left, int right) {
        //左括号已用完，剩余右括号直接加到后面
        if (left == N) {
            while (right < N) {
                parenthesis[right + N] = ')';
                ++right;
            }
            combinations.push_back(parenthesis);
        }
        //左括号未用完，可以选择插入一个左括号或者若干右括号(一次插入一个，否则引起重复)，但右括号个数不能超过左括号个数
        else {
            //插入左括号
            parenthesis[left + right] = '(';
            generateParenthesisRecursive(left + 1, right);

            //插入右括号
            if (right < left) {
                parenthesis[left + right] = ')';
                generateParenthesisRecursive(left, right + 1);
            }
        }
    }
};

using std::vector;
using std::string;

class Solution1 {
public:
    vector<string> generateParenthesis(int n) {
        results.clear();
        if (0 == n)
            return results;
        generateParenthesis(n, 0);
        return results;
    }

private:
    vector<string> results;
    string parenthesis;

    // 传入剩余的左括号数量和未匹配的左括号数量
    void generateParenthesis(int open_left, int open_no_match) {
        if (!open_left && !open_no_match) {
            results.push_back(parenthesis);
            return;
        }
        if (open_left) {
            parenthesis.push_back('(');
            generateParenthesis(open_left - 1, open_no_match + 1);
            parenthesis.pop_back();
        }
        if (open_no_match) {
            parenthesis.push_back(')');
            generateParenthesis(open_left, open_no_match - 1);
            parenthesis.pop_back();
        }
    }
};

int main() {
    int n = 3;
    Solution1 solution;
    std::vector<std::string> result = solution.generateParenthesis(n);
    for (const std::string &s : result)
        std::cout << s << std::endl;

    return 0;
}
