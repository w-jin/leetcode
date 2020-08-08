#include <iostream>
#include <vector>
#include <algorithm>

class Solution {
public:
    std::vector<int> plusOne(const std::vector<int> &digits) {
        std::vector<int> result;

        int carry = 1;
        for (int i = static_cast<int>(digits.size()) - 1; i >= 0; --i) {
            result.push_back((digits[i] + carry) % 10);
            carry = (digits[i] + carry) / 10;
        }
        if (carry != 0)
            result.push_back(carry);

        std::reverse(result.begin(), result.end());

        return result;
    }
};

std::ostream &operator<<(std::ostream &out, std::vector<int> vec) {
    for (int i = 0; i < vec.size(); ++i) {
        out << vec[i];
        if (i != vec.size() - 1)
            out << " ";
    }
    return out;
}

int main() {
    std::vector<int> digits1 = {1, 2, 3}; //124
    std::vector<int> digits2 = {2, 9, 9}; //300
    std::vector<int> digits3 = {9, 9, 9}; //1000

    Solution solution;
    std::cout << solution.plusOne(digits1) << std::endl;
    std::cout << solution.plusOne(digits2) << std::endl;
    std::cout << solution.plusOne(digits3) << std::endl;

    return 0;
}
