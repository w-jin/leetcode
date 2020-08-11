#include <iostream>

/* 二分查找，最终要找到一个数a满足：a^2<=x且(a+1)^2>x
 * 注意：当x非常大时，mid*mid可能溢出！
 */
class Solution {
public:
    int mySqrt(int x) {
        int left = 0, right = x, mid = 0;
        while (left < right) {
            mid = left + (right - left) / 2;
            if (mid * mid == x)
                return mid;
            else if (mid * mid < x) {
                if ((mid + 1) * (mid + 1) > x)
                    return mid;
                else
                    left = mid + 1;
            }
            else {
                right = mid - 1;
            }
        }

        return left;
    }
};

/* 二分查找的改进版，将判断mid^2==x改为判断mid==x/mid，以避免溢出，但是这种方法和前一个不是等
 * 价的！因为整数除法截断小数部分，所以mid==x/mid时，mid^2==x不一定成立，但是这种算法仍然是正
 * 确的：约定/为整数除法，//为实数除法，对于每次迭代，
 * 1、mid=x/mid时，则mid<=x//mid<mid+1，所以mid^2<=x<mid(mid+1)<(mid+1)^2，所以x的
 *   平方根取整的结果为mid；
 * 2、mid<x/mid时，x//mid>=mid+1，x>=mid(mid+1)>mid^2，
 *   若mid+1>x/(mid+1)，则mid+1>x//(mid+1)，所以(mid+1)^2>x>mid^2，所以x的平方根取整的
 *     结果为mid，
 *   若mid+1<=x/(mid+1)，则mid+1<=x//(mid+1)，所以(mid+1)^2<=x，所以x的平方根取整的结果
 *     至少为mid+1，
 * 3、mid>x/mid时，mid>x//mid，所以mid^2>x，所以x的平方根取整之后至多为mid-1.
 */
class Solution1 {
public:
    int mySqrt(int x) {
        if (0 == x)
            return 0;
        if (1 == x)
            return 1;

        int left = 0, right = x, mid = 0;
        while (left < right) {
            mid = left + (right - left) / 2;
            if (mid == x / mid)
                return mid;
            else if (mid < x / mid) {
                if ((mid + 1) > x / (mid + 1))
                    return mid;
                else
                    left = mid + 1;
            }
            else {
                right = mid - 1;
            }
        }

        return left;
    }
};

/* 牛顿迭代法计算平方根：令f(s)=s^2-x，x的平方根即为f(s)的正零点，由牛顿迭代法计算f(s)的零点，
 * 迭代式为s2=s1-f'(s1)/f(s1)=0.5*(s1 + x/s1)。如果选择s0=x，s2-s1=-f'(s1)/f(s1)=
 * -2s1/(s1^2-x)<0，所以迭代过程中s是一个递减的序列，因此s^2>x，记[s]为s的整数部分，则
 * [s]<=s<[s]+1，所以([s]+1)^2>x，所以只需要满足[s]^2<=x，则x的平方根取整的结果为[s]。
 * 但是计算[s]^2时可能发生溢出，所以需要转化为长整型计算。
 */
class Solution2 {
public:
    int mySqrt(int x) {
        if (0 == x)
            return 0;

        double s = x;
        while ((long)s * (long)s > x)
            s = 0.5 * (s + x / s);

        return static_cast<int>(s);
    }
};

/* 牛顿迭代法优化初始值 */
class Solution3 {
public:
    int mySqrt(int x) {
        long t = x;
        t = 0x5f3759df - (t >> 1);
        while (!(t * t <= x && (t + 1) * (t + 1) > x))
            t = (x / t + t) / 2;
        return static_cast<int>(t);
    }
};

int main() {
    Solution3 solution;

    int x1 = 4; //2
    int x2 = 8; //2

    std::cout << x1 << ": " << solution.mySqrt(x1) << std::endl;
    std::cout << x2 << ": " << solution.mySqrt(x2) << std::endl;

    return 0;
}
