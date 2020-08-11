#include <iostream>
#include <string>
#include <algorithm>

class Solution {
public:
    std::string convert(const std::string &s, int numRows) {
        /* numRows = 5时：
         *    0   8   16   24...  2i*(numRows-1), i=0,1,2...，这个等差数列是第一行在s中的下标
         * 0  L   I   X
         * 1  E  ES  XX
         * 2  E D X X X X
         * 3  TO  XX  XX
         * 4  C   X   X
         *    4  12  20  28...  (2i+1)*(numRows-1), i=0,1,2...，这个数列是最后一行在s中的下标
         * 其余行关于最后一行的各个字母对称
         */
        if (1 == numRows) return s;

        std::string result(s.size(), 0);
        int i_result = 0;
        //第一行
        for (int i = 0; i * (2 * numRows - 2) < s.size(); ++i)
            result[i_result++] = s[i * (2 * numRows - 2)];
        //第二至numRows-1行
        for (int line = 1; line < numRows - 1; ++line) {
            for (int i = 0; true; ++i) {
                if ((2 * i + 1) * (numRows - 1) - numRows + line + 1 < s.size())
                    result[i_result++] = s[(2 * i + 1) * (numRows - 1) - numRows + line + 1];
                if ((2 * i + 1) * (numRows - 1) + numRows - line - 1 < s.size())
                    result[i_result++] = s[(2 * i + 1) * (numRows - 1) + numRows - line - 1];
                else
                    break;
            }
        }
        //最后一行
        for (int i = 0; (2 * i + 1) * (numRows - 1) < s.size(); ++i)
            result[i_result++] = s[(2 * i + 1) * (numRows - 1)];

        return result;
    }
};

int main()
{
    //LCIRETOESIIGEDHN
    std::string s = "LEETCODEISHIRING";
    int numRows = 3;
    Solution solution;
    std::cout << solution.convert(s, numRows) << std::endl;
    
    return 0;
}
