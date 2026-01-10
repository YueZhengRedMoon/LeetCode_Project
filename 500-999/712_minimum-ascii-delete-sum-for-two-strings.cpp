#include <iostream>
#include <vector>

class Solution
{
public:
    int minimumDeleteSum(std::string s1, std::string s2)
    {
        int len1 = s1.size(), len2 = s2.size();
        // f[i][j]:使s1[0,i)与s2[0,j)相等所需删除字符的ASCII值的最小和
        std::vector<std::vector<int>> f(len1 + 1, std::vector<int>(len2 + 1, 0));

        // 初始化，删除所有字符以变成空串
        for (int j = 1; j <= len2; ++j)
        {
            f[0][j] = f[0][j - 1] + s2[j - 1];
        }
        for (int i = 1; i <= len1; ++i)
        {
            f[i][0] = f[i - 1][0] + s1[i - 1];
        }

        for (int i = 1; i <= len1; ++i)
        {
            for (int j = 1; j <= len2; ++j)
            {
                if (s1[i - 1] == s2[j - 1])
                {
                    f[i][j] = f[i - 1][j - 1];
                }
                else
                {
                    // f[i][j] = std::min({f[i - 1][j] + s1[i - 1], f[i][j - 1] + s2[j - 1], f[i - 1][j - 1] + s1[i - 1] + s2[j - 1]});
                    f[i][j] = std::min(f[i - 1][j] + s1[i - 1], f[i][j - 1] + s2[j - 1]);
                }
            }
        }
        return f[len1][len2];
    }
};

int main()
{
    std::cout << "For Kirie" << std::endl;
    return 0;
}