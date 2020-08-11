#include <iostream>
#include <vector>

class Solution {
public:
    double findMedianSortedArrays(std::vector<int> &nums1, std::vector<int> &nums2) {
        //较短的是A，较长的是B
        std::vector<int> &A = nums1.size() <= nums2.size() ? nums1 : nums2;
        std::vector<int> &B = nums1.size() > nums2.size() ? nums1 : nums2;

        //二分搜索找到合适的i
        size_t bottom = 0, top = A.size();
        size_t half = (nums1.size() + nums2.size() + 1) / 2;
        while (bottom <= top) {
            size_t i = (bottom + top) / 2;
            size_t j = half - i;

            if (i < top && B[j - 1] > A[i])	//j过大，i过小
                bottom = i + 1;
            else if (i > bottom && A[i - 1] > B[j]) //i过大，j过小
                top = i - 1;
            else {  //i已满足要求
                int left_max = 0;
                if (i == 0)
                    left_max = B[j - 1];
                else if (j == 0)
                    left_max = A[i - 1];
                else
                    left_max = A[i - 1] >= B[j - 1] ? A[i - 1] : B[j - 1];
                //奇数个
                if ((A.size() + B.size()) % 2 == 1)
                    return left_max;

                int right_min = 0;
                if (i == A.size())
                    right_min = B[j];
                else if (j == B.size())
                    right_min = A[i];
                else
                    right_min = A[i] <= B[j] ? A[i] : B[j];
                //偶数个
                return (left_max + right_min) / 2.0;
            }
        }
        return 0;
    }
};

int main()
{
    //2.0
    std::vector<int> nums1 = {1, 3};
    std::vector<int> nums2 = {2};
    Solution solution;
    std::cout << solution.findMedianSortedArrays(nums1, nums2) << std::endl;

    return 0;
}
