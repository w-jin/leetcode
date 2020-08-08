#include <iostream>
#include <vector>
#include <algorithm>

using std::cout;
using std::endl;
using std::vector;

/*
 * 暴力解法。时间复杂度O(n^2)，空间复杂度O(1)。
 * 超时!
 */
class Solution {
public:
    vector<int> countSmaller(vector<int> &nums) {
        const int N = nums.size();

        vector<int> counts(nums.size());
        for (int i = N - 1; i >= 0; --i) {
            counts[i] = 0;
            for (int j = i + 1; j < N; ++j) {
                if (nums[j] < nums[i])
                    ++counts[i];
            }
        }

        return counts;
    }
};

class Solution1 {
private:
    //原数组为nums，
    //将nums离散化，此处是排序+去重，转化为数组a
    vector<int> a;
    //将nums对应a的元素update到树状数组c
    vector<int> c;

    //resize树状数组大小
    void init(int len) {
        c.resize(len);
    }

    //lowbit为二进制中最低位的1的值
    int lowbit(int x) {
        return x & (-x);
    }

    //单点更新，从子节点更新到所有父节点(祖父节点等一直往上到上限c.size())
    void update(int pos) {
        while (pos < c.size()) {
            c[pos] += 1;
            pos += lowbit(pos);
        }
    }

    //查询，实际是求和[0,...,pos]，即求1~pos的元素数量
    //如c[8]，在update时，a[1],a[2],a[3],...,a[8]都会使c[8]增加一个value（该题中我们设置为1）
    //res += c[8]，然后8减去lowbit为0。
    //也可以拿c[6]举例，c[6] =a[5]+a[6]，lowbit后，c[4] = a[1]+a[2]+a[3]+a[4]
    int query(int pos) {
        int res = 0;
        while (pos) {
            res += c[pos];
            pos -= lowbit(pos);
        }
        return res;
    }

    //离散化处理
    void Discretization(vector<int>& nums) {
        //拷贝数组 [5,4,5,3,2,1,1,1,1,1]
        a.assign(nums.begin(), nums.end());
        //排序[1,1,1,1,1,2,3,4,5,5]
        sort(a.begin(), a.end());
        //去重[1,2,3,4,5]
        a.erase(unique(a.begin(), a.end()), a.end());
    }

    int getId(int x) {
        //lower_bound返回第一个不小于x的迭代器
        //[1,2,3,4,5]中1，减去begin()再加1，得到id（1-5）
        return lower_bound(a.begin(), a.end(), x) - a.begin() + 1;
    }

public:
    vector<int> countSmaller(vector<int>& nums) {
        vector<int> res;
        int n = nums.size();
        //题解是+5，其实+1就够了，树状数组中我们不使用0下标，所以需扩展1位空间
        //当然直接用n结果也是对的。这里再推敲推敲
        init(n+1);

        //将nums转化为a
        Discretization(nums);

        for (int i=n-1; i>=0; --i) {
            //倒序处理
            int id = getId(nums[i]);
            //查询严格小于id的元素数量，所以使用id-1
            res.push_back(query(id-1));
            //更新id，其实更新也可以提前，因为查询是id-1，所以更新操作不影响当前结果
            update(id);
        }
        //倒序处理再倒序回来。如果不是用push_back，直接用下标可以不用在这里再倒序
        reverse(res.begin(), res.end());
        return res;
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
    // 2, 1, 1, 0
    vector<int> nums1 = {5, 2, 6, 1};

    Solution1 solution;
    cout << solution.countSmaller(nums1) << endl;

    return 0;
}
