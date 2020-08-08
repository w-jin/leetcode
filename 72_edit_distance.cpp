#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

class Solution {
public:
    int minDistance(const std::string & word1, const std::string & word2) {
        if (word1.empty())
            return static_cast<int>(word2.size());
        if (word2.empty())
            return static_cast<int>(word1.size());

        // distance[i][j]表示将word1[0, ..., i-1]更改为word2[0, ..., j-1]所需操作数，
        // ij为0时表示空串
        std::vector<std::vector<int>> distance(word1.size() + 1,
                std::vector<int>(word2.size() + 1, 0));

        // 第一行，将空串改为word2[0, ..., j-1]所需操作数
        for (int j = 0; j <= word2.size(); ++j)
            distance[0][j] = j;
        // 第一列，将word1[0, ..., i-1]改为空串所需操作数
        for (int i = 0; i <= word1.size(); ++i)
            distance[i][0] = i;
        // 其余行
        for (int i = 1; i <= word1.size(); ++i) {
            for (int j = 1; j <= word2.size(); ++j)
                // 对应位置匹配，它们之前的字符匹配好即可
                if (word1[i - 1] == word2[j - 1])
                    distance[i][j] = distance[i - 1][j - 1];
                // 对应位置不匹配，就取这三种方案中最优一种：1、word1[i-1]改为word2[j-1]；
                // 2、删去word1[i-1]，匹配word1[0,...,i-2]和word2[0,...,j-1]
                // 3、插入word2[j-1]，匹配word1[0,...i-1]和word2[0,...,j-2]
                else
                    distance[i][j] = 1 + std::min(distance[i - 1][j - 1],
                            std::min(distance[i - 1][j], distance[i][j - 1]));
        }

        return distance[word1.size()][word2.size()];
    }
};

/* 只开一行的内存以节约空间 */
class Solution1 {
public:
    int minDistance(const std::string &word1, const std::string &word2) {
        if (word1.empty())
            return static_cast<int>(word2.size());
        if (word2.empty())
            return static_cast<int>(word1.size());

        // distance[i][j]表示将word1[0, ..., i-1]更改为word2[0, ..., j-1]所需操作数，
        // ij为0时表示空串
        std::vector<int> distance(word2.size() + 1, 0);

        // 第一行，将空串改为word2[0, ..., j-1]所需操作数
        for (int j = 0; j <= word2.size(); ++j)
            distance[j] = j;

        for (int i = 1; i <= word1.size(); ++i) {
            // 第一列，将word1[0, ..., i-1]改为空串所需操作数
            distance[0] = i;

            // 左上角的元素，计算过程中会破坏，因此需要备份一下
            int distance_i_1_j_1 = i - 1;
            for (int j = 1; j <= word2.size(); ++j) {
                int backup = distance[j];

                // 对应位置匹配，它们之前的字符匹配好即可
                if (word1[i - 1] == word2[j - 1])
                    distance[j] = distance_i_1_j_1;
                // 对应位置不匹配，就取这三种方案中最优一种：1、word1[i-1]改为word2[j-1]
                // 2、删去word1[i-1]，匹配word1[0,...,i-2]和word2[0,...,j-1]
                // 3、插入word2[j-1]，匹配word1[0,...i-1]和word2[0,...,j-2]
                else
                    distance[j] = 1 + std::min(distance_i_1_j_1,
                                                  std::min(distance[j], distance[j - 1]));

                distance_i_1_j_1 = backup;
            }
        }

        return distance[word2.size()];
    }
};

int main() {
    Solution1 solution;
    std::cout << solution.minDistance("horse", "ros") << std::endl; //3
    std::cout << solution.minDistance("intention", "execution") << std::endl; //5

    return 0;
}
