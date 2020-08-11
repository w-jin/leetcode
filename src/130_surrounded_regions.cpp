#include <iostream>
#include <vector>
#include <queue>
#include <utility>

using std::vector;

class Solution {
public:
    void solve(vector<vector<char>> &board) {
        if (board.empty() || board[0].empty())
            return;

        const int M = board.size();
        const int N = board[0].size();

        // 将所有与边界相连的O标记为S
        std::queue<std::pair<int, int>> q;
        for (int i = 0; i < M; ++i) {
            if (board[i][0] == 'O')
                q.emplace(i, 0);
            if (board[i][N - 1] == 'O')
                q.emplace(i, N - 1);
        }

        for (int j = 0; j < N; ++j) {
            if (board[0][j] == 'O')
                q.emplace(0, j);
            if (board[M - 1][j] == 'O')
                q.emplace(M - 1, j);
        }

        const int dx[] = {1, 0, -1, 0};
        const int dy[] = {0, 1, 0, -1};

        while (!q.empty()) {
            auto p = q.front();
            q.pop();

            board[p.first][p.second] = 'S';

            for (int i = 0; i < 4; ++i) {
                int x = p.first + dx[i];
                int y = p.second + dy[i];

                if (x < 0 || x >= M || y < 0 || y >= N || board[x][y] != 'O')
                    continue;

                q.emplace(x, y);
            }
        }

        // 把所有O改成X
        for (int i = 0; i < M; ++i) {
            for (int j = 0; j < N; ++j) {
                if (board[i][j] == 'O')
                    board[i][j] = 'X';
            }
        }

        // 把所有S改回O
        for (int i = 0; i < M; ++i) {
            for (int j = 0; j < N; ++j) {
                if (board[i][j] == 'S')
                    board[i][j] = 'O';
            }
        }
    }
};

std::ostream &operator<<(std::ostream &os, const vector<vector<char>> &board) {
    for (int i = 0; i < board.size(); ++i) {
        for (int j = 0; j < board[i].size(); ++j)
            os << board[i][j] << " ";
        os << "\n";
    }
    return os;
}

int main() {
    // X X X X
    // X X X X
    // X X X X
    // X O X X
    vector<vector<char>> board1 = {
            {'X', 'X', 'X', 'X'},
            {'X', 'O', 'O', 'X'},
            {'X', 'X', 'O', 'X'},
            {'X', 'O', 'X', 'X'}
    };

    // X O X O X O
    // O X X X X X
    // X X X X X O
    // O X O X O X
    vector<vector<char>> board2 = {
            {'X', 'O', 'X', 'O', 'X', 'O'},
            {'O', 'X', 'O', 'X', 'O', 'X'},
            {'X', 'O', 'X', 'O', 'X', 'O'},
            {'O', 'X', 'O', 'X', 'O', 'X'}
    };

    Solution solution;
    solution.solve(board1);
    solution.solve(board2);

    std::cout << board1;
    std::cout << board2;

    return 0;
}
