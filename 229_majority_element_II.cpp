#include <iostream>
#include <vector>

using std::cout;
using std::endl;
using std::vector;

class Solution {
public:
    vector<int> majorityElement(vector<int> &nums) {
        // 投票，抵消逻辑有问题，不应当只抵消一个人的票数，应当是三张不同的票一起抵消。
        vector<int> temp(2);
        vector<int> count(2, 0);
        for (int num : nums) {
            if (0 == count[0]) {
                temp[0] = num;
                count[0] = 1;
            } else {
                if (num == temp[0])
                    ++count[0];
                else {
                    if (0 == count[1]) {
                        temp[1] = num;
                        count[1] = 1;
                    } else {
                        if (num == temp[1])
                            ++count[1];
                        else {
                            if (0 == count[1])
                                --count[0];
                            else
                                --count[1];
                        }
                    }
                }
            }
        }

        // 统计剩下的候选人是否真的票数超过1/3
        bool flag0 = count[0] > 0;
        bool flag1 = count[1] > 0;
        count[0] = count[1] = 0;
        for (int num : nums) {
            if (flag0 && num == temp[0])
                ++count[0];
            else if (flag1 && num == temp[1])
                ++count[1];
        }

        vector<int> result;
        if (count[0] > nums.size() / 3)
            result.push_back(temp[0]);
        if (count[1] > nums.size() / 3)
            result.push_back(temp[1]);

        return result;
    }
};

class Solution1 {
public:
    vector<int> majorityElement(vector<int> &nums) {
        if (nums.empty())
            return {};

        int candidate1 = nums[0];
        int candidate2 = nums[0];
        int count1 = 0;
        int count2 = 0;
        for (int num : nums) {
        /*    // 必须先检查是否num是否为候选元素再检查是否有空位，否则可能造成一个候选元素占两个位置的情况
            if (num == candidate1) {
                ++count1;
                continue;
            }
            if (num == candidate2) {
                ++count2;
                continue;
            }

            if (0 == count1) {
                candidate1 = num;
                count1 = 1;
                continue;
            }
            if (0 == count2) {
                candidate2 = num;
                count2 = 1;
                continue;
            }

            --count1;
            --count2;
        */
            if (num == candidate1)
                ++count1;
            else if (num == candidate2)
                ++count2;
            else if (0 == count1) {
                candidate1 = num;
                count1 = 1;
            } else if (0 == count2) {
                candidate2 = num;
                count2 = 1;
            } else {
                --count1;
                --count2;
            }
        }

        count1 = 0;
        count2 = 0;
        for (int num : nums) {
            if (num == candidate1)
                ++count1;
            else if (num == candidate2)
                ++count2;
        }

        vector<int> result;
        if (count1 > nums.size() / 3)
            result.push_back(candidate1);
        if (count2 > nums.size() / 3)
            result.push_back(candidate2);

        return result;
    }
};

/*
 * 推广到1/m的情况。
 */
class Solution2 {
public:
    vector<int> majorityElement(vector<int> &nums) {
        return majorityElement(nums, 3);
    }

private:
    vector<int> majorityElement(vector<int> &nums, int m) {
        if (nums.empty())
            return {};

        vector<int> candidates(m - 1, nums[0]);
        vector<int> counts(m - 1, 0);
        for (int num : nums) {
            for (int i = 0; i < m - 1; ++i) {
                if (num == candidates[i]) {
                    ++counts[i];
                    goto next;
                }
            }

            for (int i = 0; i < m - 1; ++i) {
                if (0 == counts[i]) {
                    candidates[i] = num;
                    counts[i] = 1;
                    goto next;
                }
            }

            for (int i = 0; i < m - 1; ++i)
                --counts[i];

            next:;
        }

        for (int i = 0; i < m - 1; ++i)
            counts[i] = 0;
        for (int num : nums) {
            for (int i = 0; i < m - 1; ++i) {
                if (num == candidates[i]) {
                    ++counts[i];
                    break;
                }
            }
        }

        vector<int> result;
        for (int i = 0; i < m - 1; ++i) {
            if (counts[i] > nums.size() / m)
                result.push_back(candidates[i]);
        }

        return result;
    }
};

/*
 * 推广到1/m的情况。且n和m都比较大时，可以使用哈希表优化。
 */
#include <unordered_map>

class Solution3 {
public:
    vector<int> majorityElement(vector<int> &nums) {
        return majorityElement(nums, 3);
    }

private:
    vector<int> majorityElement(vector<int> &nums, int m) {
        if (nums.empty())
            return {};

        std::unordered_map<int, int> candidates;
        for (int num : nums) {
            if (candidates.find(num) != candidates.end())
                ++candidates[num];
            else if (candidates.size() < m - 1)
                candidates[num] = 1;
            else {
                for (auto it = candidates.begin(); it != candidates.end(); ) {
                    --(it->second);
                    if (0 == it->second)
                        it = candidates.erase(it);
                    else
                        ++it;
                }
            }
        }

        for (auto &p : candidates)
            p.second = 0;
        for (int num : nums) {
            auto it = candidates.find(num);
            if (it != candidates.end())
                ++(it->second);
        }

        vector<int> result;
        for (auto p : candidates) {
            if (p.second > nums.size() / m)
                result.push_back(p.first);
        }

        return result;
    }
};

std::ostream &operator<<(std::ostream &out, const vector<int> &vec) {
    if (vec.empty())
        return out << "null";
    for (int i = 0; i + 1 < vec.size(); ++i)
        out << vec[i] << ", ";
    return out << vec.back();
}

int main() {
    // 3
    vector<int> nums1 = {3, 2, 3};

    // 1, 2
    vector<int> nums2 = {1, 1, 1, 3, 3, 2, 2, 2};

    // 2, 1
    vector<int> nums3 = {1, 2, 2, 3, 2, 1, 1, 3};

    // 3
    vector<int> nums4 = {1, 2, 1, 1, 1, 3, 3, 4, 3, 3, 3, 4, 4, 4};

    Solution3 solution;
    cout << solution.majorityElement(nums1) << endl;
    cout << solution.majorityElement(nums2) << endl;
    cout << solution.majorityElement(nums3) << endl;
    cout << solution.majorityElement(nums4) << endl;

    return 0;
}
