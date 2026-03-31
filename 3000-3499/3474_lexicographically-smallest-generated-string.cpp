#include <iostream>
#include <vector>

class Solution
{
public:
    std::string generateString(std::string str1, std::string str2)
    {
        int n = str1.size(), m = str2.size();
        std::string ans(n + m - 1, '?');    // ?表示待定位置
        for (int i = 0; i < n; ++i)
        {
            if (str1[i] == 'T')
            {
                for (int j = 0; j < m; ++j)
                {
                    if (ans[i + j] != '?' && ans[i + j] != str2[j])
                    {
                        return "";
                    }
                    ans[i + j] = str2[j];
                }
            }
        }

        std::string oldAns = ans;
        for (int i = 0; i < ans.size(); ++i)
        {
            if (ans[i] == '?')
            {
                ans[i] = 'a';   // 待定位置的初始值为a
            }
        }

        // 处理F
        for (int i = 0; i < n; ++i)
        {
            if (str1[i] != 'F')
            {
                continue;
            }

            // 子串必须不等于str2
            bool isEq = true;
            for (int j = 0; j < m; ++j)
            {
                if (ans[i + j] != str2[j])
                {
                    isEq = false;
                    break;
                }
            }
            if (!isEq)
            {
                continue;
            }

            // 找最后一个待定位置
            bool ok = false;
            for (int j = i + m - 1; j >= i; --j)
            {
                if (oldAns[j] == '?')   // 之前填a，现在改成b
                {
                    ans[j] = 'b';
                    ok = true;
                    break;
                }
            }
            if (!ok)
            {
                return "";
            }
        }

        return ans;
    }
};

int main()
{
    std::cout << "For Kirie" << std::endl;
    return 0;
}