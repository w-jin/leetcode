#include <iostream>
#include <vector>

class MountainArray {
public:
    MountainArray(std::initializer_list<int> list) : data{list} {}

    int get(int index) const {
        ++query_count;
        return data[index];
    }

    int length() const {
        return static_cast<int>(data.size());
    }

    int getQueryCount() const {
        return query_count;
    }

private:
    std::vector<int> data;
    mutable int query_count = 0;
};

class Solution {
public:
    int findInMountainArray(int target, MountainArray &mountainArr) {
        // 先查找峰顶：find i, such that A[0] < A[1] < ... A[i-1] < A[i],
        // and A[i] > A[i+1] > ... > A[A.length - 1].
        // 题目保证A.length >= 3，且存在0 < i < A.length-1满足上述条件
        int first = 0;
        int last = mountainArr.length() - 1;  // 开区间可能越界
        while (first < last) {
            int mid = first + (last - first) / 2;  // mid、mid-1、mid+1都不越界
            int mid_num = mountainArr.get(mid);
            int left_num = mountainArr.get(mid - 1);
            int right_num = mountainArr.get(mid + 1);
            if (left_num < mid_num && mid_num > right_num) {
                first = mid;
                break;
            } else if (left_num < mid_num && mid_num < right_num) {
                first = mid + 1;
            } else {
                last = mid;
            }
        }

        int peak = first;
        first = 0;
        last = peak;
        while (first < last) {
            int mid = first + (last - first) / 2;
            int mid_num = mountainArr.get(mid);
            if (mid_num == target)
                return mid;
            else if (mid_num < target)
                first = mid + 1;
            else
                last = mid;
        }

        first = peak;
        last = mountainArr.length();
        while (first < last) {
            int mid = first + (last - first) / 2;
            int mid_num = mountainArr.get(mid);
            if (mid_num == target)
                return mid;
            else if (mid_num < target)
                last = mid;
            else
                first = mid + 1;
        }

        return -1;
    }
};

int main() {
    // 2
    MountainArray array1 = {1, 2, 3, 4, 5, 3, 1};
    int target1 = 3;

    // -1
    MountainArray array2 = {0, 1, 2, 4, 2, 1};
    int target2 = 3;

    // -1
    MountainArray array3 = {1, 2, 3, 5, 3};
    int target3 = 0;

    Solution solution;
    std::cout << solution.findInMountainArray(target1, array1) << std::endl;
    std::cout << solution.findInMountainArray(target2, array2) << std::endl;
    std::cout << solution.findInMountainArray(target3, array3) << std::endl;

    return 0;
}
