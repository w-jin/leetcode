#include <iostream>
#include <string>
#include <vector>
#include <functional>

class Solution {
public:
    int totalNQueens(int n) {
        int count = 0;

        std::vector<std::string> chessboard((size_t)n, std::string((size_t)n, '.'));
        //逐行求解
        std::function<void(int)> solve = [&solve, &chessboard, &count, n](int i) -> void {
            if (i == n) {
                ++count;
                return;
            }

            //逐个位置尝试
            for (int j = 0; j < n; ++j) {
                bool available = true;

                //检查是否可放queen
                for (int row = 0; row < i; ++row) {
                    int col = 0;
                    while (chessboard[row][col] == '.')
                        ++col;
                    //此列已有queen
                    if (col == j) {
                        available = false;
                        break;
                    }
                    //能被攻击到
                    if (i - row + col == j || row - i + col == j) {
                        available = false;
                        break;
                    }
                }
                if (!available)
                    continue;

                chessboard[i][j] = 'Q';
                solve(i + 1);
                chessboard[i][j] = '.';
            }
        };

        solve(0);
        return count;
    }
};

int main()
{
    //2
    std::cout << Solution().totalNQueens(4) << std::endl;
    return 0;
}

