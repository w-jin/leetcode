#include <iostream>
#include <vector>
#include <cmath>
#include <functional>

using std::cout;
using std::endl;
using std::vector;

class Solution {
public:
    bool judgePoint24(vector<int> &nums) {
        enum OpName {Add, Minus, Prod, Div};

        std::function<double(double, double)> arithmetic[4] = {
                std::plus<double>{},
                std::minus<double>{},
                std::multiplies<double>{},
                std::divides<double>{}
        };

        // 计算任意两个数的加减乘除的结果
        vector<vector<vector<double>>> temp(4, vector<vector<double>>(4, vector<double>(4)));
        for (int i = 0; i < 4; ++i) {
            for (int j = 0; j < 4; ++j) {
                for (int op = 0; op < 4; ++op)
                    temp[op][i][j] = arithmetic[op](nums[i], nums[j]);
            }
        }

        // 最外层两个for选出任意两个数
        for (int i = 0; i < 4; ++i) {
            for (int j = 0; j < 4; ++j) {
                if (i == j)
                    continue;

                // 选出剩下的两个数是哪两个
                int k1 = -1;
                int k2 = -1;
                for (int k = 0; k < 4; ++k) {
                    if (k != i && k != j) {
                        if (-1 == k1)
                            k1 = k;
                        else {
                            k2 = k;
                            break;
                        }
                    }
                }

                // 第三四个数先结合再和前两个数结合，看看是否有结果为24的
                for (int op1 = 0; op1 < 4; ++op1) {      // op1是i和j的运算
                    for (int op2 = 0; op2 < 4; ++op2) {  // op2是k1和k2的运算
                        for (int op = 0; op < 4; ++op) { // op是ij和k12的自动
                            double t1 = arithmetic[op](temp[op1][i][j], temp[op2][k1][k2]);
                            double t2 = arithmetic[op](temp[op1][i][j], temp[op2][k2][k1]);
                            if (check(t1) || check(t2))
                                return true;
                        }
                    }
                }

                // 对两个数计算的结果和第三、四个数依次结合，看看结果是否有24的
                for (int op1 = 0; op1 < 4; ++op1) {          // op1是i和j的运算
                    for (int op2 = 0; op2 < 4; ++op2) {      // op2是ij和k1或k2的运算
                        for (int op3 = 0; op3 < 4; ++op3) {  // op3是ijk和剩下那个的运算
                            double t1 = arithmetic[op2](temp[op1][i][j], nums[k1]);
                            double t2 = arithmetic[op2](nums[k1], temp[op1][i][j]);
                            if (check(arithmetic[op3](t1, nums[k2]))
                                || check(arithmetic[op3](nums[k2], t1))
                                || check(arithmetic[op3](t2, nums[k2]))
                                || check(arithmetic[op3](nums[k2], t2)))
                                return true;

                            double t3 = arithmetic[op2](temp[op1][i][j], nums[k2]);
                            double t4 = arithmetic[op2](nums[k2], temp[op1][i][j]);
                            if (check(arithmetic[op3](t3, nums[k1]))
                                || check(arithmetic[op3](nums[k1], t3))
                                || check(arithmetic[op3](t4, nums[k1]))
                                || check(arithmetic[op3](nums[k1], t4)))
                                return true;
                        }
                    }
                }
            }
        }


        return false;
    }

private:
    bool check(double d) {
        return fabs(d - 24) < 1e-2;
    }
};

int main() {
    // true
    vector<int> nums1 = {4, 1, 8, 7};

    // false
    vector<int> nums2 = {1, 2, 1, 2};

    // true
    vector<int> nums3 = {3, 9, 7, 7};

    // false
    vector<int> nums4 = {3, 4, 6, 7};

    Solution solution;
    cout << std::boolalpha;
    cout << solution.judgePoint24(nums1) << endl;
    cout << solution.judgePoint24(nums2) << endl;
    cout << solution.judgePoint24(nums3) << endl;
    cout << solution.judgePoint24(nums4) << endl;

    return 0;
}
