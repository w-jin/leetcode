#include <iostream>
#include <vector>

using std::cout;
using std::endl;
using std::vector;

class Solution {
public:
    bool isRectangleOverlap(const vector<int> &rec1, const vector<int> &rec2) {
        // 竖边，左边在另一个矩阵内或者右边在另一个矩形内，或者两边把另一个矩阵包在内
        bool vertical_overlap = (rec2[0] < rec1[0] && rec1[0] < rec2[2]) ||
                                (rec2[0] < rec1[2] && rec1[2] < rec2[2]) ||
                                (rec1[0] <= rec2[0] && rec1[2] >= rec2[2]);

        // 横边，上边在另一个矩阵内或者下边在另一个矩形内，或者两边把另一个矩阵包在内
        bool horizontal_overlap = (rec2[1] < rec1[1] && rec1[1] < rec2[3]) ||
                                  (rec2[1] < rec1[3] && rec1[3] < rec2[3]) ||
                                  (rec1[1] <= rec2[1] && rec1[3] >= rec2[3]);

        return vertical_overlap && horizontal_overlap;
    }
};

/*
    从反面考虑，即考虑不重叠的情况
*/
class Solution1 {
public:
    bool isRectangleOverlap(const vector<int> &rec1, const vector<int> &rec2) {
        return !(rec1[0] >= rec2[2] || rec1[2] <= rec2[0] ||
                 rec1[1] >= rec2[3] || rec1[3] <= rec2[1]);
    }
};

int main() {
    // true
    vector<int> rec1_1 = {0, 0, 2, 2};
    vector<int> rec2_1 = {1, 1, 3, 3};

    // false
    vector<int> rec1_2 = {0, 0, 1, 1};
    vector<int> rec2_2 = {1, 0, 2, 1};

    // true
    vector<int> rec1_3 = {7, 8, 13, 15};
    vector<int> rec2_3 = {10, 8, 12, 20};

    Solution1 solution;
    cout << std::boolalpha;
    cout << solution.isRectangleOverlap(rec1_1, rec2_1) << endl;
    cout << solution.isRectangleOverlap(rec1_2, rec2_2) << endl;
    cout << solution.isRectangleOverlap(rec1_3, rec2_3) << endl;

    return 0;
}
