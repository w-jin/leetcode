#include <iostream>
#include <vector>

using std::cout;
using std::endl;
using std::vector;

class Solution {
public:
    vector<int> twoSum(vector<int> &numbers, int target) {
        int i = 0;
        int j = numbers.size() - 1;
        while (i < j) {
            if (numbers[i] + numbers[j] == target)
                return {i + 1, j + 1};
            else if (numbers[i] + numbers[j] < target)
                ++i;
            else
                --j;
        }

        return {-1, -1};  // error: no suitable indices
    }
};

std::ostream &operator<<(std::ostream &out, const vector<int> &vec) {
    if (vec.size() != 2)
        throw std::runtime_error{"the size of vec is not 2!"};
    return out << "{" << vec[0] << ", " << vec[1] << "}";
}

int main() {
    // {1, 2}
    vector<int> numbers1 = {2, 7, 11, 15};
    int target1 = 9;

    Solution solution;
    cout << solution.twoSum(numbers1, target1) << endl;

    return 0;
}
