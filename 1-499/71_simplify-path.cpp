#include <iostream>
#include <stack>
#include <string>
#include <deque>
#include <sstream>

class Solution
{
public:
    std::string simplifyPath(std::string path)
    {
        int begin = -1, len = 0;
        std::deque<std::string> stack;
        auto switchDir = [&](){
            std::string dir = path.substr(begin, len);
            begin = -1;
            if (dir == ".")
            {
                return;
            }
            else if (dir == "..")
            {
                if (!stack.empty())
                {
                    stack.pop_back();
                }
            }
            else
            {
                stack.push_back(dir);
            }
        };
        for (int i = 1; i < path.size(); ++i)
        {
            if (path[i] == '/')
            {
                if (path[i - 1] == '/')
                    continue;

                switchDir();
            }
            else if (begin == -1)
            {
                begin = i;
                len = 1;
            }
            else
            {
                ++len;
            }
        }
        if (begin != -1)
        {
            switchDir();
        }

        std::ostringstream oss;
        oss << '/';
        if (!stack.empty())
        {
            for (int i = 0; i < stack.size() - 1; ++i)
            {
                oss << stack[i] << "/";
            }
            oss << stack.back();
        }

        return oss.str();
    }
};

int main()
{
    std::cout << "For Kirie!" << std::endl;
    return 0;
}
