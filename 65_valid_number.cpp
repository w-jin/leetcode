#include <iostream>
#include <string>
#include <regex>

/* 经过多次尝试，此题所能接受的数字并不是c/c++标准中所规定的数字字面值常量，而是由此解答中的正则
 * 表达式所描述的语言。
 */
class Solution {
public:
    bool isNumber(const std::string &s) {
        std::regex reg(" *[+-]?([0-9]+(\\.[0-9]*)?|\\.[0-9]+)([Ee][+-]?[0-9]+)? *");
        return std::regex_match(s, reg);
    }
};

/* 使用自动机的算法，性能比上个正则表达式好很多 */
class Solution1 {
public:
    enum class TypeId {
        notAcceptable = -1,
        number = 0, //单个数字
        plusOrMinus = 1,   //加号减号
        dot = 2,    //小数点
        Ee = 3, //科学计数法的底
    };

    enum class State {
        start, s0, s1, s2, s3, s4, s5, s6, s7, s8, error
    };

    //状态转移表，第一维为状态，第二维为输入
    const State delta[10][4] = {
            //number, plusOrMinus, dot, Ee
            {State::s1, State::s0, State::s4, State::error}, //start
            {State::s1, State::error, State::s4, State::error}, //s0
            {State::s1, State::error, State::s2, State::s6}, //s1
            {State::s3, State::error, State::error, State::s6}, //s2
            {State::s3, State::error, State::error, State::s6}, //s3
            {State::s5, State::error, State::error, State::error}, //s4
            {State::s5, State::error, State::error, State::s6}, //s5
            {State::s8, State::s7, State::error, State::error}, //s6
            {State::s8, State::error, State::error, State::error}, //s7
            {State::s8, State::error, State::error, State::error} //s8
    };

    TypeId getTypeId(char c) {
        if ('0' <= c && c <= '9')
            return TypeId::number;
        if (c == '+' || c == '-')
            return TypeId::plusOrMinus;
        if (c == '.')
            return TypeId::dot;
        if (c == 'E' || c == 'e')
            return TypeId::Ee;
        return TypeId::notAcceptable;
    }

    bool isAcceptable(State state) {
        return state == State::s1 || state == State::s2 || state == State::s3
               || state == State::s5 || state == State::s8;
    }

    bool isNumber(const std::string &s) {
        if (s.empty())
            return false;

        //跳过首尾的空格
        int i = 0, n = static_cast<int>(s.size());
        while (i < s.size() && s[i] == ' ')
            ++i;
        if (i == s.size())
            return false;
        while (n > 0 && s[n - 1] == ' ')
            --n;

        State state = State::start;
        while (i < n) {
            TypeId t = getTypeId(s[i]);
            if (t == TypeId::notAcceptable)
                return false;

            state = delta[static_cast<int>(state)][static_cast<int>(t)];

            if (state == State::error)
                return false;

            ++i;
        }

        return isAcceptable(state);
    }
};

int main() {
    Solution1 solution;
    std::cout << std::boolalpha;
    std::cout << ".:\t" << solution.isNumber(".") << std::endl;               //false
    std::cout << "0:\t" << solution.isNumber("0") << std::endl;               //true
    std::cout << "1 :\t" << solution.isNumber("1 ") << std::endl;             //true
    std::cout << ".1:\t" << solution.isNumber(".1") << std::endl;             //true
    std::cout << "+12:\t" << solution.isNumber("+12") << std::endl;           //true
    std::cout << "0.1:\t" << solution.isNumber("0.1") << std::endl;           //true
    std::cout << "abc:\t" << solution.isNumber("abc") << std::endl;           //false
    std::cout << "1 a:\t" << solution.isNumber("1 a") << std::endl;           //false
    std::cout << "2e10:\t" << solution.isNumber("2e10") << std::endl;         //true
    std::cout << "-90e3:\t" << solution.isNumber("-90e3") << std::endl;       //true
    std::cout << "1e:\t" << solution.isNumber("1e") << std::endl;             //false
    std::cout << "e3:\t" << solution.isNumber("e3") << std::endl;             //false
    std::cout << "6e-1:\t" << solution.isNumber("6e-1") << std::endl;         //true
    std::cout << "99e2.5:\t" << solution.isNumber("99e2.5") << std::endl;     //false
    std::cout << "53.5e9:\t" << solution.isNumber("53.5e93") << std::endl;    //true
    std::cout << "--6:\t" << solution.isNumber("--6") << std::endl;           //false
    std::cout << "-+3:\t" << solution.isNumber("-+3") << std::endl;           //false
    std::cout << "95a54e53:\t" << solution.isNumber("95a54e53") << std::endl; //false
    std::cout << "40949e2471:\t" << solution.isNumber("40949e2471") << std::endl; //true

    return 0;
}
