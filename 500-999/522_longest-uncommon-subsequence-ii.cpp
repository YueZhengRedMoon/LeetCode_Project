#include <iostream>
#include <vector>
#include <algorithm>

class Solution
{
public:
    int findLUSlength(std::vector<std::string>& strs)
    {
        std::sort(strs.begin(), strs.end(),
                  [](const std::string& a, const std::string& b) {
            if (a.size() == b.size())
                return a > b;
            else
                return a.size() > b.size();
        });
        int n = strs.size();
        for (int i = 1; i < n; ++i)
        {
            const std::string& cur = strs[i - 1];
            const std::string& next = strs[i];
            if (cur.size() > next.size() || cur != next)
            {
                bool isSpecial = true;
                for (int j = 0; j < i - 1 && isSpecial; ++j)
                {
                    isSpecial = !isSubsequence(strs[j], cur);
                }
                if (isSpecial)
                    return cur.size();
            }
        }
        for (int i = 0; i < n - 1; ++i)
        {
            if (isSubsequence(strs[i], strs.back()))
                return -1;
        }
        return strs.back().size();
    }

private:
    // 判断b是否是a的子序列
    bool isSubsequence(const std::string& a, const std::string & b)
    {
        int aLen = a.size(), bLen = b.size(), i = 0, j = 0;
        while (i < aLen && j < bLen)
        {
            if (a[i] == b[j])
                ++j;
            ++i;
        }
        return j == bLen;
    }
};

int main()
{
    std::cout << "For Kirie!" << std::endl;
    return 0;
}
