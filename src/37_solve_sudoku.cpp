#include <iostream>
#include <vector>

class Solution {
public:
    void solveSudoku(std::vector<std::vector<char>> &board) {
        solve(board, 0);
    }

private:
    //逐行求解
    bool solve(std::vector<std::vector<char>> &board, int pos) {
        //每个位置都已经有数字了
        if (pos == 81)
            return true;

        int i = pos / 9; //行
        int j = pos % 9; //列

        //跳过填了数字的格子
        if (board[i][j] != '.')
            return solve(board, pos + 1);

        //统计所在行、列、九宫格数字情况
        int count[10] = {0};
        for (int k = 0; k < 9; ++k) {
            if (board[i][k] != '.')
                ++count[board[i][k] - '0'];
        }

        for (int k = 0; k < 9; ++k)
            if (board[k][j] != '.')
                ++count[board[k][j] - '0'];

        for (int k = 0; k < 3; ++k) {
            for (int l = 0; l < 3; ++l)
                if (board[i / 3 * 3 + k][j / 3 * 3 + l] != '.')
                    ++count[board[i / 3 * 3 + k][j / 3 * 3 + l] - '0'];
        }

        //没有出现过的数字是可选的，每个数字都尝试一次
        for (int k = 1; k < 10; ++k) {
            if (count[k] == 0) {
                board[i][j] = static_cast<char>('0' + k);
                if (solve(board, pos + 1))
                    return true;
            }
        }

        //没有可选数字或者每个数字都不行，进行回溯
        board[i][j] = '.';
        return false;
    }
};

/* 动态维护各行各列已有的数字，性能比上个Solution好一些 */
class Solution1 {
public:
    void solveSudoku(std::vector<std::vector<char>> &board) {
        //统计各行各列各九宫格数字分布情况
        for (int i = 0; i < 9; ++i) {
            for (int j = 0; j < 9; ++j) {
                char c = board[i][j];
                if (c != '.') {
                    ++row[i][c - '1'];
                    ++col[j][c - '1'];
                    ++grid[i / 3 * 3 + j / 3][c - '1'];
                }
            }
        }

        solve(board, 0);
    }

private:
    bool solve(std::vector<std::vector<char>> &board, int pos) {
        //跳过填了数字的格子
        while (pos < 81 && board[pos / 9][pos % 9] != '.')
            ++pos;

        //每个位置都已经有数字了
        if (pos == 81)
            return true;

        int i = pos / 9; //行
        int j = pos % 9; //列

        //尝试所有可能的数字
        for (int k = 0; k < 9; ++k) {
            if (row[i][k] == 0 && col[j][k] == 0 && grid[i / 3 * 3 + j / 3][k] == 0) {
                board[i][j] = static_cast<char>('1' + k);
                row[i][k] = 1;
                col[j][k] = 1;
                grid[i / 3 * 3 + j / 3][k] = 1;

                if (solve(board, pos + 1))
                    return true;

                row[i][k] = 0;
                col[j][k] = 0;
                grid[i / 3 * 3 + j / 3][k] = 0;
            }
        }

        //所有数字都不能解出数独
        board[i][j] = '.';
        return false;
    }

    int row[9][9] = {0}; //各行数字个数
    int col[9][9] = {0}; //各列数字个数
    int grid[9][9] = {0}; //各九宫格数字个数，按行编号
};

std::ostream &operator<<(std::ostream &out, const std::vector<std::vector<char>> &mat)
{
    for (const auto &line : mat) {
        for (char c : line)
            out << c << " ";
        out << std::endl;
    }
    return out;
}

int main()
{
    // answer is :
    // 5 3 4 6 7 8 9 1 2
    // 6 7 2 1 9 5 3 4 8
    // 1 9 8 3 4 2 5 6 7
    // 8 5 9 7 6 1 4 2 3
    // 4 2 6 8 5 3 7 9 1
    // 7 1 3 9 2 4 8 5 6
    // 9 6 1 5 3 7 2 8 4
    // 2 8 7 4 1 9 6 3 5
    // 3 4 5 2 8 6 1 7 9
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

    Solution1 solution;
    solution.solveSudoku(board1);
    std::cout << board1;

    return 0;
}
