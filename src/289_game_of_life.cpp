#include <iostream>
#include <vector>

using std::cout;
using std::endl;
using std::vector;

class Solution {
public:
    void gameOfLife(vector<vector<int>> &board) {
        if (board.empty() || board[0].empty())
            return;

        const int M = static_cast<int>(board.size());
        const int N = static_cast<int>(board[0].size());

        // 八个方向：左上、上、右上、右、右下、下、左下、左
        int di[] = {-1, -1, -1, 0, 1, 1, 1, 0};
        int dj[] = {-1, 0, 1, 1, 1, 0, -1, -1};

        // 统计board[i][j]周围八个位置中1的数量并将它乘2加到board[i][j]上，这样board[i][j]
        // 本身的值可以通过board[i][j]%2得到，而1的数量可以通过board[i][j]/2得到。
        for (int i = 0; i < M; ++i) {
            for (int j = 0; j < N; ++j) {
                int count = 0;

                for (int k = 0; k < 8; ++k) {
                    int ni = i + di[k];
                    int nj = j + dj[k];
                    if (0 <= ni && ni < M && 0 <= nj && nj < N && 1 == board[ni][nj] % 2)
                        ++count;
                }

                board[i][j] += count * 2;
            }
        }

        // 各位置根据1的数量count来决定它的值：
        // 1、count < 2，为0；
        // 2、count = 2，保持原值；
        // 3、count = 3，为1；
        // 4、count > 3，为0。
        for (int i = 0; i < M; ++i) {
            for (int j = 0; j < N; ++j) {
                if (board[i][j] / 2 == 2)
                    board[i][j] = board[i][j] % 2;
                else if (board[i][j] / 2 == 3)
                    board[i][j] = 1;
                else
                    board[i][j] = 0;
            }
        }
    }
};

class Solution1 {
public:
    void gameOfLife(vector<vector<int>> &board) {
        if (board.empty() || board[0].empty())
            return;

        const int M = static_cast<int>(board.size());
        const int N = static_cast<int>(board[0].size());

        // 八个方向：左上、上、右上、右、右下、下、左下、左
        int di[] = {-1, -1, -1, 0, 1, 1, 1, 0};
        int dj[] = {-1, 0, 1, 1, 1, 0, -1, -1};

        // 计算board[i][j]周围八个位置中1的个数，然后得到新的board[i][j]的值，但这个值不能
        // 直接写入，因为其它位置的计算需要依赖它的旧值，可以使用额外的状态来表示旧值到新值的变化：
        // 1、用0表示0到0的变化，1表示1到1的变化；
        // 2、用-1表示1到0的变化；
        // 3、用2表示0到1的变化。
        for (int i = 0; i < M; ++i) {
            for (int j = 0; j < N; ++j) {
                int count = 0;

                for (int k = 0; k < 8; ++k) {
                    int ni = i + di[k];
                    int nj = j + dj[k];
                    if (0 <= ni && ni < M && 0 <= nj && nj < N) {
                        if (1 == board[ni][nj] || -1 == board[ni][nj])
                            ++count;
                    }
                }

                if (3 == count)
                    board[i][j] = board[i][j] == 1 ? 1 : 2;
                else if (count < 2 || count > 3)
                    board[i][j] = board[i][j] == 0 ? 0 : -1;
            }
        }

        // 把board中不为0和1的编码转化一下
        for (int i = 0; i < M; ++i) {
            for (int j = 0; j < N; ++j) {
                if (2 == board[i][j])
                    board[i][j] = 1;
                else if (-1 == board[i][j])
                    board[i][j] = 0;
            }
        }
    }
};

std::ostream &operator<<(std::ostream &out, const vector<int> &vec) {
    if (vec.empty())
        return out;
    for (int i = 0; i + 1 < vec.size(); ++i)
        out << vec[i] << ",";
    out << vec.back();
    return out;
}

std::ostream &operator<<(std::ostream &out, const vector<vector<int>> &vec) {
    out << "[\n";
    for (const auto &v : vec)
        out << "[" << v << "],\n";
    out << "]";
    return out;
}

int main() {
    /*
        [0, 0, 0],
        [1, 0, 1],
        [0, 1, 1],
        [0, 1, 0]
    */
    vector<vector<int>> board1 = {
            {0, 1, 0},
            {0, 0, 1},
            {1, 1, 1},
            {0, 0, 0}
    };

    Solution1 solution;
    solution.gameOfLife(board1);
    cout << board1 << endl;

    return 0;
}
