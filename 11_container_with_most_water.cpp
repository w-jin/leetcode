#include <iostream>
#include <vector>
#include <algorithm>

class Solution {
public:
    int maxArea(std::vector<int> &height) {
        int i = 0, j = static_cast<int>(height.size() - 1);
        int min_height = std::min(height[i], height[j]);
        int max_area = (j - i) * min_height;
        while (i < j) {
            if (height[i] <= height[j]) {
                do {
                    ++i;
                } while (i < j && height[i] <= min_height);
            } else {
                do {
                    --j;
                } while (i < j && height[j] <= min_height);
            }
            min_height = std::min(height[i], height[j]);
            if (i < j && (j - i) * min_height > max_area)
                max_area = (j - i) * min_height;
        }
        return max_area;
    }
};

class Solution1 {
public:
    int maxArea(std::vector<int> &height) {
        int i = 0, j = static_cast<int>(height.size() - 1);
        int max_area = 0;
        while (i < j) {
            max_area = std::max(max_area, (j - i) * std::min(height[i], height[j]));
            if (height[i] <= height[j])
                ++i;
            else
                --j;
        }
        return max_area;
    }
};

int main() {
    // 49
    std::vector<int> height1 = {1, 8, 6, 2, 5, 4, 8, 3, 7};

    Solution1 solution;
    std::cout << solution.maxArea(height1) << std::endl;

    return 0;
}
