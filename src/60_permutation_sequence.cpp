#include <iostream>
#include <vector>
#include <string>
#include <functional>
#include <algorithm>

class Solution {
public:
    std::string getPermutation(int n, int k) {
        std::string permutation;
        for (int i = 1; i <= n; ++i)
            permutation.push_back(static_cast<char>(i + '0'));

        std::function<void(std::string &)> next_permutation;
        next_permutation = [](std::string &str) -> void {
            auto i = str.rbegin() + 1;
            while (i != str.rend() && *i >= *(i - 1))
                ++i;
            if (i == str.rend())
                std::reverse(str.begin(), str.end());
            else {
                auto j = str.rbegin();
                while (*j <= *i)
                    ++j;
                std::swap(*i, *j);
                std::reverse(str.rbegin(), i);
            }
        };

        for (int i = 1; i < k; ++i)
            next_permutation(permutation);

        return permutation;
    }
};

class Solution1 {
public:
    std::string getPermutation(int n, int k) {
        const int factorial[] = {1, 1, 2, 6, 24, 120, 720, 5040, 40320, 362880};

        std::string permutation;
        for (int i = 0; i < n; ++i)
            permutation.push_back(static_cast<char>('1' + i));

        //根据k和n的阶乘大小关系可以逐个确定当前数字
        --k; //从0开始计数
        for (int curr = 0; curr < n; ++curr) {
            int i = k / factorial[n - 1 - curr];
            char temp = permutation[i + curr];
            for (int j = i + curr; j > curr; --j)
                permutation[j] = permutation[j - 1];
            permutation[curr] = temp;
            k = k % factorial[n - 1 - curr];
        }

        return permutation;
    }
};

class Solution2 {
public:
    std::string getPermutation(int n, int k) {
        const int factorial[] = {1, 1, 2, 6, 24, 120, 720, 5040, 40320, 362880};
        std::vector<int> rest(n, 0);
        for (int i = 0; i < n; ++i)
            rest[i] = i + 1;

        //根据k和n的阶乘大小关系可以逐个确定当前数字
        --k; //从0开始计数
        std::string permutation;
        for (int curr = 0; curr < n; ++curr) {
            int i = k / factorial[n - 1 - curr];
            k = k % factorial[n - 1 - curr];
            permutation += std::to_string(rest[i]);
            rest.erase(rest.begin() + i);
        }

        return permutation;
    }
};

int main()
{
    Solution2 solution;
    //213
    std::cout << solution.getPermutation(3, 3) << std::endl;
    //2314
    std::cout << solution.getPermutation(4, 9) << std::endl;
    //1423
    std::cout << solution.getPermutation(4, 5) << std::endl;

    return 0;
}

