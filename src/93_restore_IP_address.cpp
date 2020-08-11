#include <iostream>
#include <string>
#include <vector>
#include <functional>

using std::string;
using std::vector;

class Solution {
public:
    vector<string> restoreIpAddresses(const string &s) {
        if (s.size() < 4)
            return {};

        vector<string> ips;
        string ip(s.size() + 3, 0);

        // 依次放置.，然后判断各段数值是否满足要求，其次各段可以为0，但不能是以0开头的多位数
        // 第一个点放在i1后面
        int ip1 = 0;
        for (int i1 = 0; i1 < s.size() - 3 && (i1 == 0 || s[0] != '0'); ++i1) {
            ip1 = ip1 * 10 + s[i1] - '0';
            if (ip1 > 255)
                break;

            ip[i1] = s[i1];
            ip[i1 + 1] = '.';

            // 第二个点放在i2后面
            int ip2 = 0;
            for (int i2 = i1 + 1; i2 < s.size() - 2 && (i2 == i1 + 1 || s[i1 + 1] != '0'); ++i2) {
                ip2 = ip2 * 10 + s[i2] - '0';
                if (ip2 > 255)
                    break;

                ip[i2 + 1] = s[i2];
                ip[i2 + 2] = '.';

                // 第三个点放在i3后面
                int ip3 = 0;
                for (int i3 = i2 + 1; i3 < s.size() - 1 && (i3 == i2 + 1 || s[i2 + 1] != '0'); ++i3) {
                    ip3 = ip3 * 10 + s[i3] - '0';
                    if (ip3 > 255)
                        break;

                    ip[i3 + 2] = s[i3];
                    ip[i3 + 3] = '.';

                    if (s[i3 + 1] == '0' && i3 + 2 < s.size())
                        continue;

                    int ip4 = 0;
                    for (int i4 = i3 + 1; i4 < s.size(); ++i4) {
                        ip4 = ip4 * 10 + s[i4] - '0';
                        if (ip4 > 255)
                            break;
                        ip[i4 + 3] = s[i4];
                    }

                    if (ip4 <= 255)
                        ips.push_back(ip);
                }
            }
        }

        return ips;
    }
};

std::ostream &operator<<(std::ostream &os, const vector<string> &vec) {
    if (vec.empty())
        return os << "{}";
    os << "{";
    for (int i = 0; i + 1 < vec.size(); ++i)
        os << vec[i] << ", ";
    return os << vec.back() << "}";
}

int main() {
    // {"255.255.11.135", "255.255.111.35"}
    string s1 = "25525511135";

    // {"0.10.0.10", "0.100.1.0"}
    string s2 = "010010";

    string s3 = "101023";

    Solution solution;
    std::cout << solution.restoreIpAddresses(s1) << std::endl;
    std::cout << solution.restoreIpAddresses(s2) << std::endl;
    std::cout << solution.restoreIpAddresses(s3) << std::endl;

    return 0;
}
