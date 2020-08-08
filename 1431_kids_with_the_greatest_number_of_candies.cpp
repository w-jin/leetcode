#include <iostream>
#include <vector>
#include <algorithm>

using std::cout;
using std::endl;
using std::vector;

class Solution {
public:
    vector<bool> kidsWithCandies(vector<int> &candies, int extraCandies) {
        if (candies.empty())
            return {};

        vector<bool> result(candies.size());
        int max_candies = *std::max_element(candies.begin(), candies.end());
        for (int i = 0; i < result.size(); ++i)
            result[i] = candies[i] + extraCandies >= max_candies;

        return result;
    }
};

std::ostream &operator<<(std::ostream &out, const vector<bool> &vec) {
    if (vec.empty())
        return out;
    for (int i = 0; i + 1 < vec.size(); ++i)
        out << vec[i] << ", ";
    return out << vec.back();
}

int main() {
    // true, true, true, false, true
    vector<int> candies1 = {2, 3, 5, 1, 3};
    int extraCandies1 = 3;

    Solution solution;
    cout << std::boolalpha;
    cout << solution.kidsWithCandies(candies1, extraCandies1);

    return 0;
}
