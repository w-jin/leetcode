#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>

using std::vector;
using std::cout;
using std::endl;

/*
    模拟方法
*/
class Solution {
public:
    vector<int> distributeCandies(int candies, int num_people) {
        vector<int> result(num_people, 0);

        int n = 1;
        while (candies > 0) {
            result[(n - 1) % num_people] += std::min(candies, n);
            candies -= n;
            ++n;
        }

        return result;
    }
};

/*
    计算方法
*/
class Solution1 {
public:
    vector<int> distributeCandies(int candies, int num_people) {
        vector<int> result(num_people);

        // 最后一个够的人得到几个糖，通过k(k+1)/2<=candies解出
        int k = static_cast<int>(sqrt(0.25 + 2.0 * candies) - 0.5);
        int levels = k / num_people;   // 第一个不够的是第几轮，从0计
        int first = k % num_people;    // 第一个不够的是哪个人，从0计
        int r = candies - k * (k + 1) / 2;  // 第一个不够的人不够时剩几个糖

        // 每列都是以i+1为首项、num_people为公差的等差数列，每列的和是以levels为公差的等差数列
        if (first != 0) {
            result[0] = (2 + levels * num_people) * (levels + 1) / 2;
            for (int i = 1; i < first; ++i)
                result[i] = result[i - 1] + levels + 1;
        }
        result[first] = (2 * (first + 1) + (levels - 1) * num_people) * levels / 2 + r;
        if (first != num_people - 1) {
            result[first + 1] = result[first] - r + levels;
            for (int i = first + 2; i < num_people; ++i)
                result[i] = result[i - 1] + levels;
        }
/*      也可以这样计算，运算量稍大，不如上面的递推
        for (int i = 0; i < first; ++i)
            result[i] = (2 * (i + 1) + levels * num_people) * (levels + 1) / 2;
        result[first] = (2 * (first + 1) + (levels - 1) * num_people) * levels / 2 + r;
        for (int i = first + 1; i < num_people; ++i)
            result[i] = (2 * (i + 1) + (levels - 1) * num_people) * levels / 2;
*/

        return result;
    }
};


std::ostream &operator<<(std::ostream &out, const vector<int> &vec) {
    if (!vec.empty()) {
        for (int i = 0; i + 1 < vec.size(); ++i)
            out << vec[i] << ", ";
        out << vec.back();
    }

    return out;
}

int main() {
    // [1, 2, 3, 1]
    int candies1 = 7;
    int num_people1 = 4;

    // [5, 2, 3]
    int candies2 = 10;
    int num_people2 = 3;

    // [27, 18, 21, 24]
    int candies3 = 90;
    int num_people3 = 4;

    Solution1 solution;
    cout << solution.distributeCandies(candies1, num_people1) << std::endl;
    cout << solution.distributeCandies(candies2, num_people2) << std::endl;
    cout << solution.distributeCandies(candies3, num_people3) << std::endl;

    return 0;
}
