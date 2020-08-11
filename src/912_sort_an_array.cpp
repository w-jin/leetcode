#include <iostream>
#include <vector>
#include <algorithm>

using std::cout;
using std::endl;
using std::vector;

class Solution {
public:
    vector<int> sortArray(vector<int> &nums) {
        quickSort(nums.begin(), nums.end());
        return nums;
    }

private:
    template<class ForwardIt>
    ForwardIt partition(ForwardIt first, ForwardIt last) {
        auto pivot = *first;  // 不处理
        --last;  // 改为闭区间
        while (first < last) {
            while (first < last && *last >= pivot)
                --last;
            if (first == last)
                break;
            *first = *last;
            ++first;
            while (first < last && *first <= pivot)
                ++first;
            if (first == last)
                break;
            *last = *first;
        }
        *first = pivot;
        return first;
    }

    template<class ForwardIt>
    void quickSort(ForwardIt first, ForwardIt last) {
        if (first < last) {
            ForwardIt pivot_iter = partition(first, last);
            quickSort(first, pivot_iter);
            quickSort(pivot_iter + 1, last);
        }
    }


    void selectSort() {

    }
};

std::ostream &operator<<(std::ostream &out, const vector<int> &vec) {
    if (vec.empty())
        return out;
    for (int i = 0; i + 1 < vec.size(); ++i)
        out << vec[i] << ", ";
    out << vec.back();
    return out;
}

int main() {
    // 1, 2, 3, 5
    vector<int> nums1 = {5, 2, 3, 1};

    // 0, 0, 1, 1, 2, 5
    vector<int> nums2 = {5, 1, 1, 2, 0, 0};

    Solution solution;
    cout << solution.sortArray(nums1) << endl;
    cout << solution.sortArray(nums2) << endl;

    return 0;
}
