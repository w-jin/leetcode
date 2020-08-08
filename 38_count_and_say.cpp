#include <iostream>
#include <string>
#include <vector>

/* 此版本适用于一个对象多次调用 */
class Solution {
public:
    std::string countAndSay(int n) {
        if (cache.empty())
            cache.emplace_back("1");

        if (n > 0 && n <= cache.size())
            return cache[n - 1];

        for (int i = static_cast<int>(cache.size()); i < n; ++i) {
            std::string next;
            int j = 0;
            while (j < cache.back().size()) {
                int k = j + 1;
                while (k < cache.back().size() && cache.back()[k] == cache.back()[k - 1])
                    ++k;
                next.push_back(static_cast<char>('0' + k - j));
                next.push_back(cache.back()[j]);
                j = k;
            }
            cache.push_back(next);
        }

        return cache.back();
    }

private:
    std::vector<std::string> cache;
};

class Solution1 {
public:
    std::string countAndSay(int n) {
        std::string prev = "1", curr;
        for (int i = 1; i < n; ++i) {
            curr.clear();
            int j = 0;
            while (j < prev.size()) {
                int k = j + 1;
                while (k < prev.size() && prev[k] == prev[k - 1])
                    ++k;
                curr.push_back(static_cast<char>('0' + k - j));
                curr.push_back(prev[j]);
                j = k;
            }
            prev = curr;
        }
        return prev;
    }
};

int main()
{
    Solution1 solution;

    // 1: 1
    // 2: 11
    // 3: 21
    // 4: 1211
    // 5: 111221
    for (int i : {1, 2, 3, 4, 5})
        std::cout << i << ": " << solution.countAndSay(i) << std::endl;

    return 0;
}
