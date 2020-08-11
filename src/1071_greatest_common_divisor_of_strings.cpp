#include <iostream>
#include <string>

using std::cout;
using std::endl;
using std::string;

/*
    时间复杂度O((n1 + n2) * s(n1, n2))，其中s(n1, n2)表示n1和n2的公因数的个数，
    亦即gcd(n1, n2)的因子个数。
*/
class Solution {
public:
    string gcdOfStrings(const string &str1, const string &str2) {
        if (str1.size() < str2.size())
            return gcdOfStrings(str2, str1);

        for (auto i = str2.size(); i > 0; --i) {
            string gcd_string = str2.substr(0, i);
            if (isFactor(str1, gcd_string) && isFactor(str2, gcd_string))
                return gcd_string;
        }

        return "";
    }

private:
    bool isFactor(const string &str1, const string &str2) {
        if (str1.size() % str2.size() != 0)
            return false;
        for (int i = 0; i < str1.size(); ++i) {
            if (str1[i] != str2[i % str2.size()])
                return false;
        }
        return true;
    }
};

/*
    设n=gcd(n1, n2)，m为n的一个约数，令s=str1.substr(0, N)，s'=str1.substr(0, m)，
    且满足str1和str2都可以由s'重复得到，则s为s'重复n/m次的字符串，而str1和str2分别为s'重复
    n1/m和n2/m次的字符串，所以str1和str2分别为s重复n1/n和n2/n次的字符串，这两个数显然是整数，
    所以s才是所求的最长公约串。所以如果存在不为空串的最大公约串，它必然为str1或者str2长度为这两
    个字符串的最大公约数的前缀，因此只需要判断这一个字符串即可。
    其次，可以证明如果str1+str2=str2+str1则存在非空公约串，否则则不存在。
    时间复杂度O(n1+n2)。
*/
class Solution1 {
public:
    string gcdOfStrings(const string &str1, const string &str2) {
        if (str1.empty() || str2.empty() || str1 + str2 != str2 + str1)
            return "";

        // 辗转相除法求最大公约数，时间复杂度O(log N)
        int n1 = static_cast<int>(str1.size());
        int n2 = static_cast<int>(str2.size());
        while (n2 != 0) {
            int r = n1 % n2;
            n1 = n2;
            n2 = r;
        }

        return str1.substr(0, n1);
    }
};

int main() {
    // "ABC"
    string str1_1 = "ABCABC";
    string str2_1 = "ABC";

    // "AB"
    string str1_2 = "ABABAB";
    string str2_2 = "ABAB";

    // ""
    string str1_3 = "LEET";
    string str2_3 = "CODE";

    Solution1 solution;
    cout << solution.gcdOfStrings(str1_1, str2_1) << endl;
    cout << solution.gcdOfStrings(str1_2, str2_2) << endl;
    cout << solution.gcdOfStrings(str1_3, str2_3) << endl;

    return 0;
}

