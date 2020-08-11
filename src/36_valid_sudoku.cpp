#include <iostream>
#include <vector>

class Solution {
public:
    bool isValidSudoku(std::vector<std::vector<char>> &board) {
        //先看每行有无重复元素
        std::vector<int> count(10, 0);
        for (int i = 0; i < 9; ++i) {
            for (int &c : count)
                c = 0;
            for (int j = 0; j < 9; ++j) {
                if (board[i][j] != '.') {
                    if (count[board[i][j] - '0'] != 0)
                        return false;
                    else
                        ++count[board[i][j] - '0'];
                }
            }
        }

        //每列是否有重复元素
        for (int j = 0; j < 9; ++j) {
            for (int &c : count)
                c = 0;
            for (int i = 0; i < 9; ++i) {
                if (board[i][j] != '.') {
                    if (count[board[i][j] - '0'] != 0)
                        return false;
                    else
                        ++count[board[i][j] - '0'];
                }
            }
        }

        //每个九宫格是否有重复元素
        for (int i = 0; i < 3; ++i) //横三格
            for (int j = 0; j < 3; ++j) { //纵三格
                for (int &c : count)
                    c = 0;
                for (int k = 0; k < 3; ++k) //每格横三个元素
                    for (int l = 0; l < 3; ++l) { //每格纵三个元素
                        char c = board[3 * i + k][3 * j + l];
                        if (c != '.') {
                            if (count[c - '0'] != 0)
                                return false;
                            else
                                ++count[c - '0'];
                        }
                    }
            }
        
        return true;
    }
};

int main()
{
    //true
    std::vector<std::vector<char>> board1 = {
        {'5', '3', '.', '.', '7', '.', '.', '.', '.'},
        {'6', '.', '.', '1', '9', '5', '.', '.', '.'},
        {'.', '9', '8', '.', '.', '.', '.', '6', '.'},
        {'8', '.', '.', '.', '6', '.', '.', '.', '3'},
        {'4', '.', '.', '8', '.', '3', '.', '.', '1'},
        {'7', '.', '.', '.', '2', '.', '.', '.', '6'},
        {'.', '6', '.', '.', '.', '.', '2', '8', '.'},
        {'.', '.', '.', '4', '1', '9', '.', '.', '5'},
        {'.', '.', '.', '.', '8', '.', '.', '7', '9'}
    };
    //false
    std::vector<std::vector<char>> board2 = {
        {'8', '3', '.', '.', '7', '.', '.', '.', '.'},
        {'6', '.', '.', '1', '9', '5', '.', '.', '.'},
        {'.', '9', '8', '.', '.', '.', '.', '6', '.'},
        {'8', '.', '.', '.', '6', '.', '.', '.', '3'},
        {'4', '.', '.', '8', '.', '3', '.', '.', '1'},
        {'7', '.', '.', '.', '2', '.', '.', '.', '6'},
        {'.', '6', '.', '.', '.', '.', '2', '8', '.'},
        {'.', '.', '.', '4', '1', '9', '.', '.', '5'},
        {'.', '.', '.', '.', '8', '.', '.', '7', '9'}
    };

    Solution solution;
    std::cout << std::boolalpha
              << solution.isValidSudoku(board1) << std::endl
              << solution.isValidSudoku(board2) << std::endl;

    return 0;
}
