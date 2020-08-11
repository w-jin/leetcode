#include <iostream>
#include <string>

class Solution {
public:
    int romanToInt(const std::string &s) {
        int integer = 0;
        int i = 0;
        while (i < s.size()) {
            switch (s[i]) {
                case 'M':
                    integer += 1000;
                    ++i;
                    break;
                case 'C':
                    if (i < s.size() - 1 && s[i + 1] == 'M') {
                        integer += 900;
                        i += 2;
                    }
                    else if (i < s.size() - 1 && s[i + 1] == 'D') {
                        integer += 400;
                        i += 2;
                    }
                    else {
                        integer += 100;
                        ++i;
                    }
                    break;
                case 'X':
                    if (i < s.size() - 1 && s[i + 1] == 'C') {
                        integer += 90;
                        i += 2;
                    }
                    else if (i < s.size() - 1 && s[i + 1] == 'L') {
                        integer += 40;
                        i += 2;
                    }
                    else {
                        integer += 10;
                        ++i;
                    }
                    break;
                case 'I':
                    if (i < s.size() - 1 && s[i + 1] == 'X') {
                        integer += 9;
                        i += 2;
                    }
                    else if (i < s.size() - 1 && s[i + 1] == 'V') {
                        integer += 4;
                        i += 2;
                    }
                    else {
                        integer += 1;
                        ++i;
                    }
                    break;
                case 'D':
                    integer += 500;
                    ++i;
                    break;
                case 'L':
                    integer += 50;
                    ++i;
                    break;
                case 'V':
                    integer += 5;
                    ++i;
                    break;
                default:
                    ;
            }
        }
        return integer;
    }
};

class Solution1 {
public:
    Solution1() {
        char_map['I'] = 1;
        char_map['V'] = 5;
        char_map['X'] = 10;
        char_map['L'] = 50;
        char_map['C'] = 100;
        char_map['D'] = 500;
        char_map['M'] = 1000;
    }

    int romanToInt(const std::string &s) {
        int integer = 0;
        for (int i = 0; i < s.size() - 1; ++i) {
            if (char_map[s[i]] >= char_map[s[i + 1]])
                integer += char_map[s[i]];
            else
                integer -= char_map[s[i]];
        }
        integer += char_map[s[s.size() - 1]];
        return integer;
    }

private:
    int char_map[128] = {0};
};

int main()
{
    std::string r1 = "III"; //3
    std::string r2 = "IV"; //4
    std::string r3 = "IX"; //9
    std::string r4 = "LVIII"; //58
    std::string r5 = "MCMXCIV"; //1994

    Solution1 solution;
    std::cout << r1 << " = " << solution.romanToInt(r1) << std::endl
              << r2 << " = " << solution.romanToInt(r2) << std::endl
              << r3 << " = " << solution.romanToInt(r3) << std::endl
              << r4 << " = " << solution.romanToInt(r4) << std::endl
              << r5 << " = " << solution.romanToInt(r5) << std::endl;
    return 0;
}
