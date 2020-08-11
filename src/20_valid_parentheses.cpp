#include <iostream>
#include <string>
#include <stack>
#include <unordered_map>

class Solution {
public:
    bool isValid(const std::string &s) {
        std::stack<char> st;
        for (const char c : s) {
            //左括号
            if (c == '(' || c == '[' || c == '{')
                st.push(c);
            //右括号，栈顶和这个右括号必须匹配
            else {
                if (st.empty())
                    return false;
                if ((c == ')' && st.top() != '(') || (c == ']' && st.top() != '[') ||
                        (c == '}' && st.top() != '{'))
                    return false;
                st.pop();
            }
        }
        //看看是否还有未匹配的左括号
        return st.empty();
    }
};

class Solution1 {
public:
    bool isValid(const std::string &s) {
        std::unordered_map<char, char> parent_map = {{'(', ')'}, {'[', ']'}, {'{', '}'}};
        std::stack<char> st;
        for (const char c : s) {
            //左括号
            if (parent_map[c])
                st.push(c);
            //右括号
            else {
                if (st.empty() || c != parent_map[st.top()])
                    return false;
                st.pop();
            }
        }
        return st.empty();
    }
};

int main()
{
    std::string s1 = "{[]}"; //true
    std::string s2 = "([)]"; //false
    std::string s3 = "()[]{}"; //true

    Solution1 solution;
    std::cout << std::boolalpha
              << solution.isValid(s1) << std::endl
            << solution.isValid(s2) << std::endl
              << solution.isValid(s3) << std::endl;

    return 0;
}
