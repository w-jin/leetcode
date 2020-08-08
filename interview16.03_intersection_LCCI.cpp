#include <iostream>
#include <vector>
#include <algorithm>

using std::cout;
using std::endl;
using std::vector;

class Solution {
public:
    vector<double> intersection(vector<int> &start1, vector<int> &end1,
                                vector<int> &start2, vector<int> &end2) {
        // 将较小的坐标放到起点，x坐标小的点较小，x坐标相同则y坐标较小的坐标较小
        if (end1 < start1)
            std::swap(start1, end1);
        if (end2 < start2)
            std::swap(start2, end2);

        // 直线方程为：
        //   a1 * x - b1 * y = t1
        //   a2 * x - b2 * y = t2
        double a1 = end1[1] - start1[1];
        double a2 = end2[1] - start2[1];
        double b1 = end1[0] - start1[0];
        double b2 = end2[0] - start2[0];
        double t1 = start1[0] * end1[1] - end1[0] * start1[1];
        double t2 = start2[0] * end2[1] - end2[0] * start2[1];

        // 由Gramer法则解直线方程构成的方程组
        double D = -a1 * b2 + a2 * b1;
        double D1 = -t1 * b2 + t2 * b1;
        double D2 = a1 * t2 - a2 * t1;

        // 直线平行的情况
        if (-1e-6 <= D && D <= 1e-6) {
            if (-1e-6 <= D1 && D1 <= 1e-6) {    // 直线重合的情况，也可以由D2来判断
                // 以下两个if是线段有重合的情况
                if (start1 <= start2 && start2 <= end1)
                    return {static_cast<double >(start2[0]),
                            static_cast<double>(start2[1])};
                if (start2 <= start1 && start1 <= end2)
                    return {static_cast<double >(start1[0]),
                            static_cast<double>(start1[1])};
            }
            return {};
        }

        // 直线相交，先计算两条直线的交点，然后判断此交点是否在线段内部
        double x = D1 / D;
        double y = D2 / D;
        if (((start1[0] <= x && x <= end1[0]) || (start1[1] <= y && y <= end1[1])) &&
            ((start2[0] <= x && x <= end2[0]) || (start2[1] <= y && y <= end2[1])))
            return {x, y};
        else
            return {};
    }
};

std::ostream &operator<<(std::ostream &out, const vector<double> &point) {
    if (point.empty())
        return out << "{}";
    return out << "{" << point[0] << ", " << point[1] << "}";
}

int main() {
    // {0.5, 0}
    vector<int> start1_1 = {0, 0};
    vector<int> end1_1 = {1, 0};
    vector<int> start2_1 = {1, 1};
    vector<int> end2_1 = {0, -1};

    // {1, 1}
    vector<int> start1_2 = {0, 0};
    vector<int> end1_2 = {3, 3};
    vector<int> start2_2 = {1, 1};
    vector<int> end2_2 = {2, 2};

    // {}
    vector<int> start1_3 = {0, 0};
    vector<int> end1_3 = {1, 1};
    vector<int> start2_3 = {1, 0};
    vector<int> end2_3 = {2, 1};

    // {-1, 1}
    vector<int> start1_4 = {1, 1};
    vector<int> end1_4 = {-1, 1};
    vector<int> start2_4 = {1, 0};
    vector<int> end2_4 = {-3, 2};

    Solution solution;
    cout << solution.intersection(start1_1, end1_1, start2_1, end2_1) << endl;
    cout << solution.intersection(start1_2, end1_2, start2_2, end2_2) << endl;
    cout << solution.intersection(start1_3, end1_3, start2_3, end2_3) << endl;
    cout << solution.intersection(start1_4, end1_4, start2_4, end2_4) << endl;

    return 0;
}
