#include <iostream>
#include <vector>
#include <string>

class Solution {
public:
    bool exist(std::vector<std::vector<char>> &board, std::string &word) {
        if (board.empty())
            return false;
        if (word.empty())
            return true;

        row_size = board.size();
        col_size = board.front().size();

        visited.resize(row_size);
        for (auto &row : visited) {
            row.resize(col_size);
            for (int &i : row)
                i = 0;
        }

        for (int i = 0; i < row_size; ++i) {
            for (int j = 0; j < col_size; ++j) {
                if (board[i][j] == word.front() && SearchRecursive(board, word, i * col_size + j, 1))
                    return true;
            }
        }

        return false;
    }

    bool SearchRecursive(const std::vector<std::vector<char>> &board,
                         const std::string &word,
                         int curr, int i) {
        if (i == word.size())
            return true;

        int row = curr / col_size;
        int col = curr % col_size;

        visited[row][col] = 1;

        // 向上查找
        if (row != 0 && !visited[row - 1][col] && board[row - 1][col] == word[i]) {
            if (SearchRecursive(board, word, curr - col_size, i + 1))
                return true;
        }

        // 向下查找
        if (row != row_size - 1 && !visited[row + 1][col] && board[row + 1][col] == word[i]) {
            if (SearchRecursive(board, word, curr + col_size, i + 1))
                return true;
        }

        // 向左查找
        if (col != 0 && !visited[row][col - 1] && board[row][col - 1] == word[i]) {
            if (SearchRecursive(board, word, curr - 1, i + 1))
                return true;
        }

        // 向右查找
        if (col != col_size - 1 && !visited[row][col + 1] && board[row][col + 1] == word[i]) {
            if (SearchRecursive(board, word, curr + 1, i + 1))
                return true;
        }

        visited[row][col] = 0;
        return false;
    }

private:
    std::vector<std::vector<int>> visited;
    int row_size = 0;
    int col_size = 0;
};


int main() {
    std::vector<std::vector<char>> board = {
            {'A', 'B', 'C', 'E'},
            {'S', 'F', 'C', 'S'},
            {'A', 'D', 'E', 'E'}
    };

    std::string word1 = "ABCCED";   // true
    std::string word2 = "SEE";      // true
    std::string word3 = "ABCB";     // false

    Solution solution;
    std::cout << std::boolalpha;
    std::cout << solution.exist(board, word1) << "\n";
    std::cout << solution.exist(board, word2) << "\n";
    std::cout << solution.exist(board, word3) << "\n";

    return 0;
}
