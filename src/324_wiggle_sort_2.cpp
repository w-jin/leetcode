#include <iostream>
#include <vector>
#include <algorithm>

class Solution {
public:
    void wiggleSort(std::vector<int> &nums) {
        std::sort(nums.begin(), nums.end());

        // 前半部分可能多一个元素
        std::vector<int> nums1(nums.begin(), nums.begin() + (nums.size() + 1) / 2);
        std::vector<int> nums2(nums.begin() + (nums.size() + 1) / 2, nums.end());

        for (int i = 0; i < nums2.size(); ++i) {
            nums[2 * i] = nums1[nums1.size() - 1 - i];
            nums[2 * i + 1] = nums2[nums2.size() - 1 - i];
        }

        if (nums.size() % 2 != 0)
            nums.back() = nums1.front();
    }
};

std::ostream &operator<<(std::ostream &out, const std::vector<int> &vec) {
    for (auto &i : vec)
        out << i << "\t";
    return out;
}

class Solution1 {
public:
    void wiggleSort(std::vector<int> &nums) {
        int n = nums.size();
        std::nth_element(nums.begin(), nums.begin() + n / 2, nums.end());
        int mid = nums[n / 2];

        int i = 0;
        int j = 0;
        int k = n - 1;

        auto A = [&nums, n](int i) -> int & { return nums[(2 * i + 1) % (n | 1)]; };

        while (j <= k) {
            if (A(i) > mid) {
                std::swap(A(i), A(j));
                ++i;
                ++j;
            } else if (A(j) < mid) {
                std::swap(A(j), A(k));
                --k;
            } else {
                ++j;
            }
        }
    }
};

int main() {
    std::vector<int> nums1 = {1, 5, 1, 1, 6, 4};
    std::vector<int> nums2 = {1, 3, 2, 2, 3, 1};
    std::vector<int> nums3 = {1, 1, 2, 1, 2, 2, 1};
    std::vector<int> nums4 = {4, 5, 5, 6};

    Solution1 solution;
    solution.wiggleSort(nums1);
    solution.wiggleSort(nums2);
    solution.wiggleSort(nums3);
    solution.wiggleSort(nums4);

    std::cout << nums1 << "\n";
    std::cout << nums2 << "\n";
    std::cout << nums3 << "\n";
    std::cout << nums4 << "\n";

    return 0;
}
