#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

using std::cout;
using std::endl;
using std::vector;
using std::pair;

constexpr int INF = 100000;

class Solution {
public:
    vector<vector<int>> updateMatrix(const vector<vector<int>> &matrix) {
        if (matrix.empty() || matrix[0].empty())
            return {};

        const int M = static_cast<int>(matrix.size());
        const int N = static_cast<int>(matrix[0].size());
        vector<vector<int>> result(M, vector<int>(N, INF));

        // 从左上角算到右下角
        if (matrix[0][0] == 0)
            result[0][0] = 0;
        for (int j = 1; j < N; ++j) {
            if (0 == matrix[0][j])
                result[0][j] = 0;
            else
                result[0][j] = result[0][j - 1] + 1;
        }
        for (int i = 1; i < M; ++i) {
            if (matrix[i][0] == 0)
                result[i][0] = 0;
            else
                result[i][0] = result[i - 1][0] + 1;
            for (int j = 1; j < N; ++j) {
                if (matrix[i][j] == 0)
                    result[i][j] = 0;
                else
                    result[i][j] = std::min(result[i - 1][j], result[i][j - 1]) + 1;
            }
        }

        // 从右下角算到左上角
        for (int j = N - 2; j >= 0; --j)
            result[M - 1][j] = std::min(result[M - 1][j], result[M - 1][j + 1] + 1);
        for (int i = M - 2; i >= 0; --i) {
            result[i][N - 1] = std::min(result[i][N - 1], result[i + 1][N - 1] + 1);
            for (int j = N - 2; j >= 0; --j)
                result[i][j] = std::min(result[i][j],
                                        std::min(result[i + 1][j], result[i][j + 1]) + 1);
        }

        return result;
    }
};

class Solution1 {
public:
    vector<vector<int>> updateMatrix(const vector<vector<int>> &matrix) {
        if (matrix.empty() || matrix[0].empty())
            return {};

        const int M = static_cast<int>(matrix.size());
        const int N = static_cast<int>(matrix[0].size());
        vector<vector<int>> result(M, vector<int>(N, INF));

        for (int i = 0; i < M; ++i) {
            for (int j = 0; j < N; ++j) {
                if (matrix[i][j] == 0)
                    result[i][j] = 0;
            }
        }

        // 从左上角算到右下角
        for (int i = 0; i < M; ++i) {
            for (int j = 0; j < N; ++j) {
                if (i < M - 1)
                    result[i + 1][j] = std::min(result[i + 1][j], result[i][j] + 1);
                if (j < N - 1)
                    result[i][j + 1] = std::min(result[i][j + 1], result[i][j] + 1);
            }
        }

        // 从右下角算到左上角
        for (int i = M - 1; i >= 0; --i) {
            for (int j = N - 1; j >= 0; --j) {
                if (i > 0)
                    result[i - 1][j] = std::min(result[i - 1][j], result[i][j] + 1);
                if (j > 0)
                    result[i][j - 1] = std::min(result[i][j - 1], result[i][j] + 1);
            }
        }

        return result;
    }
};

/*
    广度优先搜索。
*/
class Solution2 {
public:
    vector<vector<int>> updateMatrix(const vector<vector<int>> &matrix) {
        if (matrix.empty() || matrix[0].empty())
            return {};

        const int M = static_cast<int>(matrix.size());
        const int N = static_cast<int>(matrix[0].size());
        vector<vector<int>> result(M, vector<int>(N, -1));

        std::queue<pair<int, int>> q;
        for (int i = 0; i < M; ++i) {
            for (int j = 0; j < N; ++j) {
                if (0 == matrix[i][j])
                    q.emplace(i, j);
            }
        }

        int distance = 0;
        while (!q.empty()) {
            int size = q.size();
            for (int n = 0; n < size; ++n) {
                int i = q.front().first;
                int j = q.front().second;
                q.pop();

                if (-1 == result[i][j])
                    result[i][j] = distance;

                if (i > 0 && 1 == matrix[i - 1][j] && -1 == result[i - 1][j])
                    q.emplace(i - 1, j);
                if (i < M - 1 && 1 == matrix[i + 1][j] && -1 == result[i + 1][j])
                    q.emplace(i + 1, j);
                if (j > 0 && 1 == matrix[i][j - 1] && -1 == result[i][j - 1])
                    q.emplace(i, j - 1);
                if (j < N - 1 && 1 == matrix[i][j + 1] && -1 == result[i][j + 1])
                    q.emplace(i, j + 1);
            }
            ++distance;
        }

        return result;
    }
};

std::ostream &operator<<(std::ostream &out, const vector<int> &vec) {
    if (vec.empty())
        return out;
    for (int i = 0; i + 1 < vec.size(); ++i)
        out << vec[i] << ", ";
    return out << vec.back();
}

std::ostream &operator<<(std::ostream &out, const vector<vector<int>> &vec) {
    if (vec.empty())
        return out << "{}";
    out << "{\n";
    for (const vector<int> &v : vec)
        out << v << endl;
    return out << "}";
}

int main() {
    /*
        0 0 0
        0 1 0
        0 0 0
    */
    vector<vector<int>> matrix1 = {
            {0, 0, 0},
            {0, 1, 0},
            {0, 0, 0}
    };

    /*
        0 0 0
        0 1 0
        1 2 1
    */
    vector<vector<int>> matrix2 = {
            {0, 0, 0},
            {0, 1, 0},
            {1, 1, 1}
    };

    /*
        0 1 0
        0 1 0
        0 1 0
        0 1 0
        0 1 0
    */
    vector<vector<int>> matrix3 = {
            {0, 1, 0},
            {0, 1, 0},
            {0, 1, 0},
            {0, 1, 0},
            {0, 1, 0}
    };

    Solution1 solution;
    cout << solution.updateMatrix(matrix1) << endl;
    cout << solution.updateMatrix(matrix2) << endl;
    cout << solution.updateMatrix(matrix3) << endl;

    return 0;
}
