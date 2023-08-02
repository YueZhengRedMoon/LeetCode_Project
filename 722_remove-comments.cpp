#include <iostream>
#include <vector>
#include "debug.h"

class Solution
{
public:
    std::vector<std::string> removeComments(std::vector<std::string> &source)
    {
        std::vector<std::string> ans;
        int row = source.size(), col, i = 0, j;
        bool isOutputted;   // 这一行已经输出过了

        auto outputLine = [&](std::string &line) {
            if (!line.empty())
            {
                line.shrink_to_fit();
                ans.push_back(std::move(line));
                isOutputted = true;
            }
        };

        while (i < row)
        {
            col = source[i].size();     // 这一行原始代码的长度
            j = 0;      // 当前检查到的字符
            std::string line;           // 这一行去掉注释后的结果
            line.reserve(col);
            isOutputted = false;

            while (j < col)
            {
                // 可能遇到了注释符
                if (source[i][j] == '/' && j + 1 < col)
                {
                    // 遇到"//"
                    if (source[i][j + 1] == '/')
                    {
                        outputLine(line);
                        break;
                    }
                    // 遇到“/*”
                    else if (source[i][j + 1] == '*')
                    {
                        // 在这一行中寻找“*/”
                        j += 2;
                        while (j + 1 < col)
                        {
                            if (source[i][j] == '*' && source[i][j + 1] == '/')
                                break;
                            ++j;
                        }

                        // 在这一行中找到了"*/"
                        if (j + 1 < col)
                        {
                            ++j;
                        }
                        // 在这一行没有找到"*/"，跨行寻找"*/"
                        else
                        {
                            bool notFoundEnd = true;
                            while (notFoundEnd)
                            {
                                col = source[++i].size();
                                j = 0;
                                while (j + 1 < col)
                                {
                                    if (source[i][j] == '*' && source[i][j + 1] == '/')
                                    {
                                        notFoundEnd = false;
                                        ++j;
                                        break;
                                    }
                                    ++j;
                                }
                            }
                        }
                    }
                    // 不是注释符号
                    else
                    {
                        line.push_back(source[i][j]);
                    }
                }
                else
                {
                    line.push_back(source[i][j]);
                }

                ++j;
            }

            if (!isOutputted)
            {
                outputLine(line);
            }

            ++i;
        }

        return ans;
    }
};

int main()
{
    Solution solution;
    std::vector<std::string> source = {"/*Test program */",
                                       "int main()",
                                       "{ ",
                                       "  // variable declaration ",
                                       "int a, b, c;",
                                       "/* This is a test",
                                       "   multiline  ",
                                       "   comment for ",
                                       "   testing */",
                                       "a = b + c;",
                                       "}"};
    std::vector<std::string> source2 = {"struct Node{",
                                        "    /*/ declare members;/**/",
                                        "    int size;",
                                        "    /**/int val;",
                                        "};"};
    std::vector<std::string> ans = solution.removeComments(source2);
    debug::printVector(ans, '\n');
    return 0;
}