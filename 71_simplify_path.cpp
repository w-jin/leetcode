#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <numeric>

class Solution {
public:
    std::string simplifyPath(const std::string & path) {
        if (path.empty())
            return "";

        std::vector<std::string> stack;

        int i = 0;
        while (i < path.size()) {
            //跳过连续的“/”
            while (i + 1 < path.size() && '/' == path[i + 1])
                ++i;

            //找到当前的目录为“path[i...j)”
            int j = i + 1;
            while (j < path.size() && '/' != path[j])
                ++j;

            std::string curr = path.substr((size_t)i, (size_t)j - i);
            //上层目录，只有上层目录存在时才回退到上层目录
            if (curr == "/..") {
                if (!stack.empty())
                    stack.pop_back();
            }
            //当前目录，简单跳过就好
            else if (curr == "/.")
                ;
            //已到末尾且有多余的“/”
            else if (curr == "/")
                ;
            //斜杠加目录名
            else
                stack.push_back(curr);

            i = j;
        }

        if (stack.empty())
            return "/";
        return std::accumulate(stack.begin(), stack.end(), std::string());
    }
};

class Solution1 {
public:
    std::string simplifyPath(const std::string & path) {
        std::string res, t;
        std::stringstream ss(path);
        std::vector<std::string> v;
        while (getline(ss, t, '/')) {
            if (t.empty() || t == ".")
                continue;
            if (t == ".." && !v.empty())
                v.pop_back();
            else if (t != "..")
                v.push_back(t);
        }
        for (const std::string & s : v)
            res += "/" + s;
        return res.empty() ? "/" : res;
    }
};

int main() {
    std::string path1 = "/home/"; //"/home"
    std::string path2 = "/../"; //"/"
    std::string path3 = "/home//foo/"; //"/home/foo"
    std::string path4 = "/a/./b/../../c/"; //"/c"
    std::string path5 = "/a/../../b/../c//.//"; //"/c"
    std::string path6 = "/a//b////c/d//././/.."; //"/a/b/c"

    Solution1 solution;
    std::cout << solution.simplifyPath(path1) << std::endl;
    std::cout << solution.simplifyPath(path2) << std::endl;
    std::cout << solution.simplifyPath(path3) << std::endl;
    std::cout << solution.simplifyPath(path4) << std::endl;
    std::cout << solution.simplifyPath(path5) << std::endl;
    std::cout << solution.simplifyPath(path6) << std::endl;

    return 0;
}
