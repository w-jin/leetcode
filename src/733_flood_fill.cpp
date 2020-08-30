#include <iostream>
#include <vector>
#include <queue>

using std::cout;
using std::endl;
using std::vector;

class Solution {
public:
    vector<vector<int>> floodFill(const vector<vector<int>> &image,
                                  int sr, int sc, int new_color) {
       // 不检查sr和sc是否越界

       vector<vector<int>> new_image = image;

       // 每个位置的四个方向
       const int dx[] = {1, 0, -1, 0};
       const int dy[] = {0, 1, 0, -1};

       int color = new_image[sr][sc];
       if (color == new_color)
           return new_image;

       // 使用广度优先遍历处理
       std::queue<std::pair<int, int>> q;
       q.emplace(sr, sc);
       while (!q.empty()) {
           auto p = q.front();
           q.pop();

           new_image[p.first][p.second] = new_color;

           for (int i = 0; i < 4; ++i) {
               int x = p.first + dx[i];
               int y = p.second + dy[i];

               if (x < 0 || y < 0 || x >= image.size() || y >= image[0].size())
                   continue;
               if (new_image[x][y] != color)
                   continue;

                q.emplace(x, y);
           }
       }

       return new_image;
    }
};

std::ostream &operator<<(std::ostream &os, const vector<int> &vec) {
    if (vec.empty())
        return os;
    for (int i = 0; i + 1 < vec.size(); ++i)
        os << vec[i] << ", ";
    return os << vec.back();
}

std::ostream &operator<<(std::ostream &os, const vector<vector<int>> &vec) {
    for (int i = 0; i < vec.size(); ++i)
        os << vec[i] << "\n";
    return os;
}

int main() {
    // 2, 2, 2
    // 2, 2, 0
    // 2, 0, 1
    vector<vector<int>> image1 = {
            {1, 1, 1},
            {1, 1, 0},
            {1, 0, 1}
    };
    int sr1 = 1;
    int sc1 = 1;
    int new_color1 = 2;

    Solution solution;
    cout << solution.floodFill(image1, sr1, sc1, new_color1);

    return 0;
}
