#include <iostream>
#include <vector>
#include <string>
#include <functional>

class Solution {
public:
    std::vector<std::vector<std::string>> solveNQueens(int n) {
        std::vector<std::vector<std::string>> result;
        std::vector<std::string> chessboard((size_t)n, std::string((size_t)n, '.'));
        //记录各列queen所在的行
        std::vector<int> queens_col(n, -1);
        //记录各行queen所在的列
        std::vector<int> queens_row(n, -1);
        //逐行求解
        std::function<void(int)> solve;
        solve = [&solve, &chessboard, &result, &queens_col, &queens_row, n](int i) -> void {
            if (i == n) {
                result.push_back(chessboard);
                return;
            }

            //计算可能的位置
            std::vector<bool> available(static_cast<unsigned long>(n), true);
            //排除已有元素的列
            for (int j = 0; j < n; ++j) {
                if (queens_col[j] != -1)
                    available[j] = false;
            }
            //排除能被攻击到的位置
            for (int j = 0; j < i; ++j) {
                if (i - j + queens_row[j] < n)
                    available[i - j + queens_row[j]] = false;
                if (j - i + queens_row[j] >= 0)
                    available[j - i + queens_row[j]] = false;
            }

            //逐个尝试这些可能的位置
            for (int j = 0; j < n; ++j) {
                if (!available[j])
                    continue;

                chessboard[i][j] = 'Q';
                queens_col[j] = i;
                queens_row[i] = j;

                solve(i + 1);

                chessboard[i][j] = '.';
                queens_col[j] = -1;
                queens_row[i] = -1;
            }
        };

        solve(0);
        return result;
    }
};

/* 上个solution的函数实现 */
class Solution1 {
public:
    std::vector<std::vector<std::string>> solveNQueens(int n) {
        chessboard = std::vector<std::string>((size_t)n, std::string((size_t)n, '.'));
        queens_col = std::vector<int>((size_t)n, -1);
        queens_row = std::vector<int>((size_t)n, -1);
        solve(n, 0);
        return result;
    }

private:
    void solve(int n, int i) {
        if (i == n) {
            result.push_back(chessboard);
            return;
        }

        //计算可能的位置
        std::vector<bool> available(static_cast<unsigned long>(n), true);
        //排除已有元素的列
        for (int j = 0; j < n; ++j) {
            if (queens_col[j] != -1)
                available[j] = false;
        }
        //排除能被攻击到的位置
        for (int j = 0; j < i; ++j) {
            if (i - j + queens_row[j] < n)
                available[i - j + queens_row[j]] = false;
            if (j - i + queens_row[j] >= 0)
                available[j - i + queens_row[j]] = false;
        }

        //逐个尝试这些可能的位置
        for (int j = 0; j < n; ++j) {
            if (!available[j])
                continue;

            chessboard[i][j] = 'Q';
            queens_col[j] = i;
            queens_row[i] = j;

            solve(n, i + 1);

            chessboard[i][j] = '.';
            queens_col[j] = -1;
            queens_row[i] = -1;
        }
    }

    std::vector<std::vector<std::string>> result;
    std::vector<std::string> chessboard;
    std::vector<int> queens_col;
    std::vector<int> queens_row;
};

/* oj实测中，这种方法反而比上面两种方法快，可能是数据规模不够大 */
class Solution2 {
public:
    std::vector<std::vector<std::string>> solveNQueens(int n) {
        std::vector<std::vector<std::string>> result;
        std::vector<std::string> chessboard((size_t)n, std::string((size_t)n, '.'));

        //逐行求解
        std::function<void(int)> solve = [&solve, &chessboard, &result, n](int i) -> void {
            if (i == n) {
                result.push_back(chessboard);
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
        return result;
    }
};

class Solution3 {
public:
    std::vector<std::vector<std::string>> solveNQueens(int n) {
        std::vector<std::vector<std::string>> result;
        std::vector<std::string> chessboard((size_t)n, std::string((size_t)n, '.'));
        //记录各列是否有queen
        std::vector<bool> cols((size_t)n, false);
        //记录各对角线是否有queen
        std::vector<bool> dia1((size_t)n * 2 - 1, false);    //主对角线
        std::vector<bool> dia2((size_t)n * 2 - 1, false);    //副对角线
        //逐行求解
        std::function<void(int)> solve;
        solve = [&solve, &chessboard, &result, &cols, &dia1, &dia2, n](int i) -> void {
            if (i == n) {
                result.push_back(chessboard);
                return;
            }

            //逐个尝试可能的位置
            for (int j = 0; j < n; ++j) {
                if (cols[j] || dia1[i - j + n - 1] || dia2[i + j])
                    continue;

                chessboard[i][j] = 'Q';
                cols[j] = true;
                dia1[i - j + n - 1] = true;
                dia2[i + j] = true;

                solve(i + 1);

                chessboard[i][j] = '.';
                cols[j] = false;
                dia1[i - j + n - 1] = false;
                dia2[i + j] = false;
            }
        };

        solve(0);
        return result;
    }
};

/* 使用位运算来代替Solution3的数组操作 */
class Solution4 {
public:
    std::vector<std::vector<std::string>> solveNQueens(int n) {
        std::vector<std::vector<std::string>> result;
        std::vector<std::string> chessboard((size_t)n, std::string((size_t)n, '.'));
        unsigned long long int cols = 0, dia1 = 0, dia2 = 0;

        std::function<void(int)> solve;
        solve = [&solve, &result, &chessboard, n, &cols, &dia1, &dia2](int i) -> void {
            if (i == n) {
                result.push_back(chessboard);
                return;
            }

            for (int j = 0; j < n; ++j) {
                int k = i - j + n - 1, l = i + j;
                if (((cols >> j) | (dia1 >> k) | (dia2 >> l)) & 1)
                    continue;

                cols |= (1 << j);
                dia1 |= (1 << k);
                dia2 |= (1 << l);
                chessboard[i][j] = 'Q';

                solve(i + 1);

                cols &= ~(1 << j);
                dia1 &= ~(1 << k);
                dia2 &= ~(1 << l);
                chessboard[i][j] = '.';
            }
        };

        solve(0);
        return result;
    }
};

std::ostream &operator<<(std::ostream &out, const std::vector<std::vector<std::string>> &vec)
{
    for (const auto &v : vec) {
        for (const auto &s : v)
            out << s << std::endl;
        out << std::endl;
    }
    return out;
}

int main()
{
    // ".Q..",  // 解法 1
    // "...Q",
    // "Q...",
    // "..Q.".
    //
    // "..Q.",  // 解法 2
    // "Q...",
    // "...Q",
    // ".Q..".
    std::cout << Solution4().solveNQueens(4);

    return 0;
}
