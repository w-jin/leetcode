#include <iostream>
#include <vector>
#include <string>
#include <stack>
#include <algorithm>

/* 使用一个数组来记录每个后括号对应的前括号的位置，每次从一对已经匹配的括号出发向两边搜索，
 * 搜索时跳过已经匹配的括号，直到搜索无法进行下去时计算这个已经匹配的子串长度，与记录的最大长度比较。
 */
class Solution {
public:
    int longestValidParentheses(std::string s) {
        if (s.empty())
            return 0;
        
        std::string::size_type size = s.size();
        std::vector<std::string::size_type> match(size, size);
        
        std::string::size_type max_match = 0;
        std::string::size_type i = 0, j = 0, front = 0;
        while (i < size - 1) {
            if (s[i] == '(' && s[i + 1] == ')') {
                j = i + 1;
                while (true) {
                    if (s[i] != '(' || s[j] != ')') {
                        max_match = std::max(j - i - 1, max_match);
                        i = j;
                        break;
                    }
                    if (i == 0) {
                        match[j] = 0;
                        max_match = std::max(j - i + 1, max_match);
                        i = j + 1;
                        break;
                    }
                    if (j == size - 1) {
                        front = i;
                        while (front != 0 && match[front - 1] != size)
                            front = match[front - 1];
                        max_match = std::max(j - front + 1, max_match);
                        i = j + 1;
                        break;
                    }
                    match[j] = i;
                    front = i;
                    while (front != 0 && match[front - 1] != size)
                        front = match[front - 1];
                    if (front == 0) {
                        match[j] = i;
                        max_match = std::max(j + 1, max_match);
                        i = j + 1;
                        break;
                    }
                    i = front - 1;
                    ++j;
                }
            }
            else {
                ++i;
            }
        }

        return static_cast<int>(max_match);
    }
};

class Solution1 {
public:
    int longestValidParentheses(std::string s) {
        std::stack<std::string::size_type> st;
        std::string::size_type start = 0, max_match = 0;
        for (std::string::size_type i = 0; i < s.size(); ++i) {
            if (s[i] == '(')
                st.push(i);
            else {
                if (st.empty())
                    start = i + 1;
                else {
                    st.pop();
                    if (st.empty())
                        max_match = std::max(max_match, i - start + 1);
                    else
                        max_match = std::max(max_match, i - st.top());
                }
            }
        }
        return static_cast<int>(max_match);
    }
};



int main()
{
    Solution1 solution;
    std::string s1 = "(()"; //2
    std::string s2 = ")()())"; //4
    std::string s3 = "()()"; //4
    std::string s4 = "(()()"; //4
    std::string s5 = ")(((((()())()()))()(()))("; //22
    std::cout << solution.longestValidParentheses(s1) << std::endl;
    std::cout << solution.longestValidParentheses(s2) << std::endl;
    std::cout << solution.longestValidParentheses(s3) << std::endl;
    std::cout << solution.longestValidParentheses(s4) << std::endl;
    std::cout << solution.longestValidParentheses(s5) << std::endl;
    return 0;
}
