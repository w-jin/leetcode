#include <iostream>
#include <vector>

using std::cout;
using std::endl;
using std::vector;

class Solution {
public:
    int numRookCaptures(vector<vector<char>> &board) {
        const int N = 8;

        int rook = 0;
        for (rook = 0; rook < N * N - 1; ++rook) {
            int i = rook / N;
            int j = rook % N;
            if (board[i][j] == 'R')
                break;
        }

        int rook_i = rook / N;
        int rook_j = rook % N;

        int captures = 0;

        // 同行的
        for (int j = rook_j - 1; j >= 0; --j) {
            if (board[rook_i][j] == 'p')       // 敌方的卒
                ++captures;
            else if (board[rook_i][j] == '.')
                continue;
            break;  // 只有空格才能继续往下走
        }
        for (int j = rook_j + 1; j < N; ++j) {
            if (board[rook_i][j] == 'p')       // 敌方的卒
                ++captures;
            else if (board[rook_i][j] == '.')
                continue;
            break;  // 只有空格才能继续往下走
        }

        // 同列的
        for (int i = rook_i - 1; i >= 0; --i) {
            if (board[i][rook_j] == 'p')       // 敌方的卒
                ++captures;
            else if (board[i][rook_j] == '.')
                continue;
            break;  // 只有空格才能继续往下走
        }
        for (int i = rook_i + 1; i < N; ++i) {
            if (board[i][rook_j] == 'p')       // 敌方的卒
                ++captures;
            else if (board[i][rook_j] == '.')
                continue;
            break;  // 只有空格才能继续往下走
        }

        return captures;
    }
};

int main() {
    // 3
    vector<vector<char>> board1 = {
            {'.', '.', '.', '.', '.', '.', '.', '.'},
            {'.', '.', '.', 'p', '.', '.', '.', '.'},
            {'.', '.', '.', 'R', '.', '.', '.', 'p'},
            {'.', '.', '.', '.', '.', '.', '.', '.'},
            {'.', '.', '.', '.', '.', '.', '.', '.'},
            {'.', '.', '.', 'p', '.', '.', '.', '.'},
            {'.', '.', '.', '.', '.', '.', '.', '.'},
            {'.', '.', '.', '.', '.', '.', '.', '.'}
    };

    // 3
    vector<vector<char>> board2 = {
            {'.', '.', '.', '.', '.', '.', '.', '.'},
            {'.', '.', '.', 'p', '.', '.', '.', '.'},
            {'.', '.', '.', 'p', '.', '.', '.', '.'},
            {'p', 'p', '.', 'R', '.', 'p', 'B', '.'},
            {'.', '.', '.', '.', '.', '.', '.', '.'},
            {'.', '.', '.', 'B', '.', '.', '.', '.'},
            {'.', '.', '.', 'p', '.', '.', '.', '.'},
            {'.', '.', '.', '.', '.', '.', '.', '.'}
    };

    Solution solution;
    cout << solution.numRookCaptures(board1) << endl;
    cout << solution.numRookCaptures(board2) << endl;

    return 0;
}
