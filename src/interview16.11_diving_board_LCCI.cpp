#include <iostream>
#include <vector>

using std::cout;
using std::endl;
using std::vector;

class Solution {
public:
    vector<int> divingBoard(int shorter, int longer, int k) {
        if (0 == k)
            return {};
        if (shorter == longer)
            return {k * longer};
        vector<int> result(k + 1);
        for (int a = 0; a <= k; ++a)
            result[a] = k * shorter + a * (longer - shorter);
        return result;
    }
};

std::ostream &operator<<(std::ostream &out, const vector<int> &vec) {
    if (vec.empty())
        return out;
    for (int i = 0; i + 1 < vec.size(); ++i)
        out << vec[i] << ", ";
    return out << vec.back();
}

int main() {
    // {3, 4, 5, 6}
    int shorter1 = 1;
    int longer1 = 2;
    int k1 = 3;

    Solution solution;
    cout << solution.divingBoard(shorter1, longer1, k1) << endl;

    return 0;
}
