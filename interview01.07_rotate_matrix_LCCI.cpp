#include <iostream>
#include <vector>
#include <algorithm>

using std::cout;
using std::endl;
using std::vector;

class Solution {
public:
    void rotate(vector<vector<int>> &matrix) {
        if (matrix.empty())
            return;

        const int N = static_cast<int>(matrix.size());

        // 先沿主对角线翻转
        for (int i = 0; i < N; ++i) {
            for (int j = i + 1; j < N; ++j)
                std::swap(matrix[i][j], matrix[j][i]);
        }

        // 再左右翻转
        for (int i = 0; i < N; ++i) {
            for (int j = 0; j < N / 2; ++j)
                std::swap(matrix[i][j], matrix[i][N - j - 1]);
        }
    }
};

class Solution1 {
public:
    void rotate(vector<vector<int>> &matrix) {
        if (matrix.empty())
            return;

        const int N = static_cast<int>(matrix.size());

        for (int i = 0; i < N / 2; ++i) {
            for (int j = 0; j < (N + 1) / 2; ++j) {
                int temp = matrix[i][j];
                matrix[i][j] = matrix[N - 1 - j][i];
                matrix[N - 1 - j][i] = matrix[N - 1 - i][N - 1 - j];
                matrix[N - 1 - i][N - 1 - j] = matrix[j][N - 1 - i];
                matrix[j][N - 1 - i] = temp;
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
        [7, 4, 1],
        [8, 5, 2],
        [9, 6, 3]
    */
    vector<vector<int>> matrix1 = {
            {1, 2, 3},
            {4, 5, 6},
            {7, 8, 9}
    };

    /*
        [15, 13,  2,  5],
        [14,  3,  4,  1],
        [12,  6,  8,  9],
        [16,  7, 10, 11]
    */
    vector<vector<int>> matrix2 = {
            {5,  1,  9,  11},
            {2,  4,  8,  10},
            {13, 3,  6,  7},
            {15, 14, 12, 16}
    };

    Solution1 solution;
    solution.rotate(matrix1);
    solution.rotate(matrix2);

    cout << matrix1 << endl;
    cout << matrix2 << endl;

    return 0;
}
