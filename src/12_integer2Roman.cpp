#include <iostream>
#include <string>
#include <algorithm>

class Solution {
public:
    std::string intToRoman(int num) {
        std::string nums;
        std::string roman;
        //取出所有数字
        while (num != 0) {
            nums.push_back(static_cast<char>(num % 10 + '0'));
            num /= 10;
        }
        std::reverse(nums.begin(), nums.end());
        //从高位开始生成罗马数字，不检查错误
        for (int i = 0; i < nums.size(); ++i) {
            if (nums[i] <= '3') {
                //重复对应字符若干次
                for (int j = 0; j < nums[i] - '0'; ++j)
                    roman.push_back(dec[nums.size() - 1 - i]);
            }
            else if ('4' == nums[i]) {
                //5-1
                roman.push_back(dec[nums.size() - 1 - i]);
                roman.push_back(half[nums.size() - 1 - i]);
            }
            else if ('5' == nums[i])
                roman.push_back(half[nums.size() - 1 - i]);
            else if ('6' <= nums[i] && nums[i] <= '8') {
                //5+1*
                roman.push_back(half[nums.size() - 1 - i]);
                for (int j = 0; j < nums[i] - '5'; ++j)
                    roman.push_back(dec[nums.size() - 1 - i]);
            }
            else if (nums[i] == '9') {
                //10-1
                roman.push_back(dec[nums.size() - 1 - i]);
                roman.push_back(dec[nums.size() - i]);
            }
            else {
                //nothing!
                ;
            }
        }
        return roman;
    }

private:
    //如果需要支持更大的数的转换，扩展这两个字符串即可
    const char *dec = "IXCM";   //1, 10, 100, 1000
    const char *half = "VLD";   //5, 50, 500
};

/* 以下所有解答均为此题而设，扩展性极差 */
class Solution1 {
public:
    std::string intToRoman(int num) {
        std::string roman;
        while (num >= 1000) {
            roman += 'M';
            num -= 1000;
        }
        if (num >= 900) {
            roman += "CM";
            num -= 900;
        }
        else if (num >= 500) {
            roman += 'D';
            num -= 500;
        }
        else if (num >= 400) {
            roman += "CD";
            num -= 400;
        }
        while (num >= 100) {
            roman += 'C';
            num -= 100;
        }
        if (num >= 90) {
            roman += "XC";
            num -= 90;
        }
        else if (num >= 50) {
            roman += 'L';
            num -= 50;
        }
        else if (num >= 40) {
            roman += "XL";
            num -= 40;
        }
        while (num >= 10) {
            roman += 'X';
            num -= 10;
        }
        if (num == 9) {
            roman += "IX";
            num = 0;
        }
        else if (num >= 5) {
            roman += 'V';
            num -= 5;
        }
        else if (num == 4) {
            roman += "IV";
            num = 0;
        }
        while (num >= 1) {
            roman += 'I';
            num -= 1;
        }
        return roman;
    }
};

class Solution2 {
public:
    std::string intToRoman(int num) {
        //const优化很大
        const std::string m[4][10] =
            {{"", "M", "MM", "MMM"},
             {"", "C", "CC", "CCC", "CD", "D", "DC", "DCC", "DCCC", "CM"},
             {"", "X", "XX", "XXX", "XL", "L", "LX", "LXX", "LXXX", "XC"},
             {"", "I", "II", "III", "IV", "V", "VI", "VII", "VIII", "IX"}};
        const int d[4] = {1000, 100, 10, 1};

        std::string roman;
        for (int i = 0; i < 4; ++i) {
            roman += m[i][num / d[i]];
            num %= d[i];
        }
        return roman;
    }
};

int main()
{
    int num1 = 3; //III
    int num2 = 4; //IV
    int num3 = 9; //IX
    int num4 = 58; //LVIII
    int num5 = 1994; //MCMXCIV

    Solution2 solution;
    std::cout << num1 << " = " << solution.intToRoman(num1) << std::endl
              << num2 << " = " << solution.intToRoman(num2) << std::endl
              << num3 << " = " << solution.intToRoman(num3) << std::endl
              << num4 << " = " << solution.intToRoman(num4) << std::endl
              << num5 << " = " << solution.intToRoman(num5) << std::endl;
    return 0;
}
