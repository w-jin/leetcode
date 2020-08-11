#include <iostream>
#include <string>

class Solution {
public:
    int lengthOfLastWord(const std::string &s) {
        if (s.empty())
            return 0;

        int i = static_cast<int>(s.size()) - 1;
        while (i >= 0 && s[i] == ' ')
            --i;

        int len = 0;
        while (i >= 0 && s[i] != ' ') {
            --i;
            ++len;
        }

        return len;
    }
};

int main()
{
    //5
    std::cout << Solution().lengthOfLastWord("Hello World") << std::endl;

    //1
    std::cout << Solution().lengthOfLastWord("a ") << std::endl;

    return 0;
}
